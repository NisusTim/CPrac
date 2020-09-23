/**************************************************************************
 * FILE NAME: ENET_RADAR.c                         COPYRIGHT (c) NXP 2016 *
 * REVISION:  0.1                                     All Rights Reserved *
 *                                                                        *
 * DESCRIPTION:                                                           *
 * ENET driver for S32R devices with specific functions for transmitting  *
 * RADAR data                                                             *
 *========================================================================*
 * UPDATE HISTORY                                                         *
 * REV      AUTHOR      DATE       DESCRIPTION OF CHANGE                  *
 * ---   -----------  ---------    ---------------------                  *
 * 0.1    G.Kerr      18-Feb-2016  Initial version for S32R274            *
 * 1.1    Gary Kerr   17 Mar 2016  Modified for RR+MR3003 Credit Card     * 
 **************************************************************************/
 
/**********************************************************************************************
* Includes
**********************************************************************************************/

#include "sys_shared.h"

//#define ENET_100M

//#define PHY_TJA1101
#define PHY_88Q2112
//#define PHY_KSZ9031

#define PHY_ADDRESS 0

/**********************************************************************************************
* Constants and macros
**********************************************************************************************/
 /* Buffer sizes in bytes -- The maximum allowable frame Ethernet frame size is 1518
 * The buffer size must be divisable by 64 so 1536 is nearest figure
 */
#define TX_INT 1

typedef struct {
	nap_header_t 	hdr;
	uint8_t 		*payload;
}enet_tx_packet_t, *enet_tx_packet_p;

#define SIZE_OF_ENET_PACKET_QUE		2048
//#define SIZE_OF_ENET_PACKET_QUE		1024

enet_tx_packet_t	__attribute__ ((section(".ebufs"))) tx_packets[SIZE_OF_ENET_PACKET_QUE];
enet_buf_t	 	__attribute__ ((section(".ebufs")))	enet_buf;

const enet_route_t default_route={
		.origip={ORIGIP1,ORIGIP2,ORIGIP3,ORIGIP4},
		.destip={DESTIP1,DESTIP2,DESTIP3,DESTIP4},
		.destmac={DESTMAC1,DESTMAC2,DESTMAC3,DESTMAC4,DESTMAC5,DESTMAC6},
		.origmac={ORIGMAC1,ORIGMAC2,ORIGMAC3,ORIGMAC4,ORIGMAC5,ORIGMAC6},
		.destport=DESTPORT, .origport=ORIGPORT};


typedef union {
	uint16_t	routed:1;
}enet_flags_t;

typedef struct {
	enet_route_t		route;
	enet_tx_packet_p	head,tail;
	event_proc_p		etx_done;
	void*				done_data;
	uint32_t			recv_cnt;
	uint32_t			send_cnt;
	uint16_t			txbd_r;	 // Point to the ready transmit buffer descriptor
	enet_flags_t		flags;
	uint16_t			identifcation;
}enet_handle_t;

static enet_handle_t 	oEnet, *enet=&oEnet;
static enet_buf_p 		ebuf=&enet_buf;
static uint8_t mii_completed_flag = 0;

/**********************************************************************************************
* Global variables - Frame + packet templates
**********************************************************************************************/

#define ETH_HEADER_LEN 14
#define IPv4_HEADER_LEN 20
#define UDP_HEADER_LEN 8

/* UDP frame
14 byte Ethernet MAC header
-------- 
20 byte IPv4 header
--------
8 byte UDP header
0-1500 byte payload
--------
4 byte Ethernet MAC footer
*/

/*
Cubtek 77G ethernet packet header definitions : 8B total
Length (2B)   : Packet Length including Packet Header
SN (1B)       : packet serial number
Data Type(1B) : adc raw(0), ranged(1), doppler(2), beamformed(3),
                peaked(4), target(5), request(6), ack(7), string(8)
Frame Number(1B): 0-59, frame offset in second
Received Number(1B): T1(0-3), T2(4-7), T3(8-11)
Sub Number(2B): chirp, ranged row, doppler row number, etc..
*/

uint8_t  __attribute__ ((aligned (64))) UDP_header[2][50] =
{
	{
		/* Starts Ethernet frame */
		DESTMAC1, DESTMAC2, DESTMAC3, DESTMAC4, DESTMAC5, DESTMAC6,     // Destination MAC Address
		ORIGMAC1, ORIGMAC2, ORIGMAC3, ORIGMAC4, ORIGMAC5, ORIGMAC6,     // Origin MAC Address
		0x08, 0x00,                             // EtherType (IPV4)
		/* Starts IPV4 frame */
		0x45,                                   // Version(0x4 for IPv4) and Header Length(0x5 x 4bytes)
		0x00,                                   // Services
		0x00, 0x20,                             // [16][17] Total Length, whole packet size including header and data
		0x00, 0x00,                             // Identification
		0x00, 0x00,                             // Flags
		0x80,                                   // Time To Live
		UDP,                                    // Protocol (UDP)
		0x00, 0x00,                             // IPV4 Header Checksum (calculated by ENET module)
		ORIGIP1, ORIGIP2, ORIGIP3, ORIGIP4,     // Origin IP
		DESTIP1, DESTIP2, DESTIP3, DESTIP4,     // Destination IP
		/* End of IPV4 frame */
		/* Start UDP frame */
		((ORIGPORT>>8)&0xFF), (ORIGPORT&0xFF),  // Source Port
		((DESTPORT>>8)&0xFF), (DESTPORT&0xFF),  // Dest Port
		0x00, 0x0C,                             // [38][39] Length of the UDP frame including header and data
		0x00, 0x00,                             // UDP Checksum of header and data (uses pseudo header with IPV4 frame)

		/* Cubtek 8 Bytes Packet Header start */
		0x00, 0x00,								// [42][43]= Packet Length, data length+8
		0x00, 									// [44]= Serial Number
		0x00, 									// [45]= Data Type
		0x00, 0x00, 							// [46][47] = Frame counter
		0x00, 0x00								// [48][49] = Sub number
	},
	{
			/* Starts Ethernet frame */
			DESTMAC1, DESTMAC2, DESTMAC3, DESTMAC4, DESTMAC5, DESTMAC6,     // Destination MAC Address
			ORIGMAC1, ORIGMAC2, ORIGMAC3, ORIGMAC4, ORIGMAC5, ORIGMAC6,     // Origin MAC Address
			0x08, 0x00,                             // EtherType (IPV4)
			/* Starts IPV4 frame */
			0x45,                                   // Version(0x4 for IPv4) and Header Length(0x5 x 4bytes)
			0x00,                                   // Services
			0x00, 0x20,                             // [16][17] Total Length, whole packet size including header and data
			0x00, 0x00,                             // Identification
			0x00, 0x00,                             // Flags
			0x80,                                   // Time To Live
			UDP,                                    // Protocol (UDP)
			0x00, 0x00,                             // IPV4 Header Checksum (calculated by ENET module)
			ORIGIP1, ORIGIP2, ORIGIP3, ORIGIP4,     // Origin IP
			DESTIP1, DESTIP2, DESTIP3, DESTIP4,     // Destination IP
			/* End of IPV4 frame */
			/* Start UDP frame */
			((ORIGPORT>>8)&0xFF), (ORIGPORT&0xFF),  // Source Port
			((DESTPORT>>8)&0xFF), (DESTPORT&0xFF),  // Dest Port
			0x00, 0x0C,                             // [38][39] Length of the UDP frame including header and data
			0x00, 0x00,                             // UDP Checksum of header and data (uses pseudo header with IPV4 frame)

			/* Cubtek 8 Bytes Packet Header start */
			0x00, 0x00,								// [42][43]= Packet Length, data length+8
			0x00, 									// [44]= Serial Number
			0x00, 									// [45]= Data Type
			0x00, 0x00, 							// [46][47] = Frame counter
			0x00, 0x00								// [48][49] = Sub number
		}
};

static void ENET_UDP_Tx(void);

/******************************************************************************
Function Name : register etx done callback for event handler
return : enet packet que depth/2
******************************************************************************/
int enet_tx_done_reg(event_proc_p done, void* d)
{
	if(done != NULL) {
		enet->etx_done = done;
		enet->done_data = d;
	}
	else {
		enet->etx_done = NULL;
		enet->done_data = NULL;
	}
	return SIZE_OF_ENET_PACKET_QUE;
}


/******************************************************************************
Function Name : enet_add_packet
******************************************************************************/
int enet_add_packet(uint8_t misc, uint8_t dt, uint16_t attr, uint16_t idx, uint8_t *buffer, uint32_t size)
{
	enet_tx_packet_p pkt;
	//if(!enet->flags.routed)
		//return TRUE;

	if (((enet->head - enet->tail) & (SIZE_OF_ENET_PACKET_QUE-1)) == (SIZE_OF_ENET_PACKET_QUE-1))
		return FALSE;

	pkt = enet->head;
	pkt->hdr.misc = misc;
	pkt->payload = buffer;
	pkt->hdr.type = dt;
	pkt->hdr.attr = attr;
	pkt->hdr.idx = idx;
	pkt->hdr.length = size;
	if(pkt->payload == NULL)
		pkt->payload = enet_txbuf_get()->buf;

	if(enet->head ==  (tx_packets+SIZE_OF_ENET_PACKET_QUE-1))
		enet->head = tx_packets;
	else
		enet->head++;

	enet->send_cnt++;

	if(!ENET.TDAR.B.TDAR) {
	    ENET.EIMR.B.TXF = 0;
		ENET_UDP_Tx();
		ENET.EIMR.B.TXF = 1;
	}
	return TRUE;
}

enet_txbuf_p enet_txbuf_get(void)
{
	enet_txbuf_p tb = ebuf->txbp;
	if(ebuf->txbp == (ebuf->txbuf+NUM_TXBUF-1))
		ebuf->txbp = ebuf->txbuf;
	else
		ebuf->txbp++;
	return tb;
}

/******************************************************************************
Function Name : enet_packet_route
******************************************************************************/
static void enet_route_packet(void)
{
	int i = 0;

	for ( i = 0; i < 2; i++) {
		memcpy((void*)&UDP_header[i][0], (void*)&enet->route.destmac[0], 12); // dest mac and orig mac
		memcpy((void*)&UDP_header[i][26], (void*)&enet->route.origip[0], 8); // orig ip and dest ip
		UDP_header[i][34] = enet->route.origport >> 8;
		UDP_header[i][35] = enet->route.origport;
		UDP_header[i][36] = enet->route.destport >> 8;
		UDP_header[i][37] = enet->route.destport;
	}	
}

/******************************************************************************
Function Name : enet_set_route
******************************************************************************/
void enet_set_route(uint8_t* origmac, uint8_t* destmac, uint8_t* origip, uint8_t* destip, uint16_t origport, uint16_t destport)
{
	enet_route_p route = &enet->route;

	if(origmac)
		memcpy((void*)route->origmac, (void*)origmac, 6);

	if(destmac)
		memcpy((void*)enet->route.destmac, (void*)destmac, 6);

	if(origip)
		memcpy((void*)route->origip, (void*)origip, 4);

	if(destip)
		memcpy((void*)route->destip, (void*)destip, 4);

	if(origport)
		route->origport = origport;

	if(destport)
		route->destport = destport;

	enet->flags.routed = 1;

	enet_route_packet();

	PRINTF("route: %02X:%02X:%02X:%02X:%02X:%02X, %d.%d.%d.%d:%u\n", route->destmac[0], route->destmac[1],
			 route->destmac[2], route->destmac[3], route->destmac[4], route->destmac[5],
			 route->destip[0], route->destip[1], route->destip[2], route->destip[3],
			 route->destport);

	/*ENET.ECR.B.ETHEREN = 0;
	enet->tail = enet->head;
	Delay_us(20);
	ENET_init();*/
}

/******************************************************************************
Function Name : enet_handle_init
******************************************************************************/
void enet_handle_init()
{
	memcpy((void*)&enet->route, (void*)&default_route, sizeof(enet_route_t));
	enet_route_packet();
	enet->head = enet->tail = tx_packets;
	enet->etx_done = NULL;
	enet->done_data = NULL;
	enet->send_cnt = 0;
	enet->recv_cnt = 0;
	enet->txbd_r = 0;
	enet->flags.routed = 0;
}

void enet_packet_info(int reset)
{
	PRINTF("enet: send=%ld, recv=%ld\n", enet->send_cnt, enet->recv_cnt);
	if(reset){
		enet->send_cnt = 0;
		enet->recv_cnt = 0;
	}
}

static void enet_event_handle(uint32_t event)
{
	PRINTF("enet event: %08lX!!\n", event);
}

#if defined(PHY_88Q2112)
void ENET_access_phy_register(uint8_t device_address, uint16_t register_address)
{
	uint8_t start = 0;                       /* Start */
	uint8_t opcode = 0;                      /* Operation */
	uint8_t turn_around = 2;                 /* Turn around */

	/* ENET_MMFR_access */
	ENET.MMFR.R = (start << 30) | (opcode << 28) | (PHY_ADDRESS << 23) | (device_address << 18) | (turn_around << 16) | register_address;

	while(mii_completed_flag == 0);
	mii_completed_flag = 0;
}

uint16_t ENET_read_phy_register(uint8_t device_address)
{
	uint8_t start = 0;                       /* Start */
	uint8_t opcode = 3;                      /* Operation */
	uint16_t register_data;                  /* Data */

	/* ENET_MMFR_read */
	ENET.MMFR.R = (start << 30) | (opcode << 28) | (PHY_ADDRESS << 23) | (device_address << 18);

	while(mii_completed_flag == 0);
	mii_completed_flag = 0;

	register_data = ENET.MMFR.R;

	return register_data;
}

void ENET_write_phy_register(uint8_t device_address, uint16_t register_data)
{
	uint8_t start = 0;                       /* Start */
	uint8_t opcode = 1;                      /* Operation */
	uint8_t turn_around = 2;                 /* Turn around */

	/* ENET_MMFR_write */
	ENET.MMFR.R = (start << 30) | (opcode << 28) | (PHY_ADDRESS << 23) | (device_address << 18) | (turn_around << 16) | register_data;

	while(mii_completed_flag == 0);
	mii_completed_flag = 0;
}
#endif

#if defined(PHY_TJA1101)
static void ENET_GPIO_Init()
{
	/* Initial Ethernet I/O */
	/* ENET_MDC */
	SIUL2.MSCR[105].B.SSS = 3;
	SIUL2.MSCR[105].B.OBE = 1;
	SIUL2.MSCR[105].B.SRC = 3;

	/* ENET_MDIO */
	SIUL2.MSCR[104].B.SSS = 3;
	SIUL2.MSCR[104].B.OBE = 1;
	SIUL2.MSCR[104].B.IBE = 1;
	SIUL2.MSCR[104].B.SRC = 3;

	/* ENET_RX_D0 */
	SIUL2.MSCR[53].B.SSS = 0;
	SIUL2.MSCR[53].B.IBE = 1;
	SIUL2.MSCR[53].B.SRC = 3;

	/* ENET_RX_D1 */
	SIUL2.MSCR[54].B.SSS = 0;
	SIUL2.MSCR[54].B.IBE = 1;
	SIUL2.MSCR[54].B.SRC = 3;

	/* ENET_RX_D2 */
	SIUL2.MSCR[116].B.SSS = 0;
	SIUL2.MSCR[116].B.IBE = 1;
	SIUL2.MSCR[116].B.SRC = 3;

	/* ENET_RX_D3 */
	SIUL2.MSCR[117].B.SSS = 0;
	SIUL2.MSCR[117].B.IBE = 1;
	SIUL2.MSCR[117].B.SRC = 3;

	/* ENET_RX_CLK */
	SIUL2.MSCR[125].B.SSS = 0;
	SIUL2.MSCR[125].B.IBE = 1;
	SIUL2.MSCR[125].B.SRC = 3;
	SIUL2.IMCR[90].B.SSS = 2;

	/* ENET_RX_DV */
	SIUL2.MSCR[50].B.SSS = 0;
	SIUL2.MSCR[50].B.IBE = 1;
	SIUL2.MSCR[50].B.SRC = 3;
	SIUL2.IMCR[91].B.SSS = 1;
//	SIUL2.GPDO[12].B.PDO_4n2 = 1;

	/* ENET_RX_ER */
	SIUL2.MSCR[120].B.SSS = 0;
	SIUL2.MSCR[120].B.IBE = 1;
	SIUL2.MSCR[120].B.SRC = 3;
//	SIUL2.GPDO[30].B.PDO_4n = 0;

	/* ENET_TX_D0 */
	SIUL2.MSCR[48].B.SSS = 4;
	SIUL2.MSCR[48].B.OBE = 1;
	SIUL2.MSCR[48].B.SRC = 3;

	/* ENET_TX_D1 */
	SIUL2.MSCR[51].B.SSS = 4;
	SIUL2.MSCR[51].B.OBE = 1;
	SIUL2.MSCR[51].B.SRC = 3;

	/* ENET_TX_D2 */
	SIUL2.MSCR[52].B.SSS = 4;
	SIUL2.MSCR[52].B.OBE = 1;
	SIUL2.MSCR[52].B.SRC = 3;

	/* ENET_TX_D3 */
	SIUL2.MSCR[106].B.SSS = 3;
	SIUL2.MSCR[106].B.OBE = 1;
	SIUL2.MSCR[106].B.SRC = 3;

	/* ENET_TX_CLK */
	SIUL2.MSCR[107].B.SSS = 0;
	SIUL2.MSCR[107].B.IBE = 1;
	SIUL2.MSCR[107].B.SRC = 3;
	SIUL2.IMCR[20].B.SSS = 1;

	/* ENET_TX_EN */
	SIUL2.MSCR[47].B.SSS = 4;
	SIUL2.MSCR[47].B.OBE = 1;
	SIUL2.MSCR[47].B.SRC = 3;

	/* ENET_TX_ER */
	SIUL2.MSCR[121].B.SSS = 4;
	SIUL2.MSCR[121].B.OBE = 1;
	SIUL2.MSCR[121].B.SRC = 3;
}

#elif defined(PHY_88Q2112)
static void ENET_GPIO_Init()
{
	/* Initial Ethernet I/O */
	/* ENET_MDC */
	SIUL2.MSCR[105].B.SSS = 3;
	SIUL2.MSCR[105].B.OBE = 1;
	SIUL2.MSCR[105].B.SRC = 3;

	/* ENET_MDIO */
	SIUL2.MSCR[104].B.SSS = 3;
	SIUL2.MSCR[104].B.OBE = 1;
	SIUL2.MSCR[104].B.IBE = 1;
	SIUL2.MSCR[104].B.SRC = 3;

	/* ENET_RX_D0 */
	SIUL2.MSCR[53].B.SSS = 0;
	SIUL2.MSCR[53].B.IBE = 1;
	SIUL2.MSCR[53].B.SRC = 3;

	/* ENET_RX_D1 */
	SIUL2.MSCR[54].B.SSS = 0;
	SIUL2.MSCR[54].B.IBE = 1;
	SIUL2.MSCR[54].B.SRC = 3;

	/* ENET_RX_D2 */
	SIUL2.MSCR[116].B.SSS = 0;
	SIUL2.MSCR[116].B.IBE = 1;
	SIUL2.MSCR[116].B.SRC = 3;

	/* ENET_RX_D3 */
	SIUL2.MSCR[117].B.SSS = 0;
	SIUL2.MSCR[117].B.IBE = 1;
	SIUL2.MSCR[117].B.SRC = 3;

	/* ENET_RX_CLK */
	SIUL2.MSCR[49].B.SSS = 0;
	SIUL2.MSCR[49].B.IBE = 1;
	SIUL2.MSCR[49].B.SRC = 3;
	SIUL2.IMCR[90].B.SSS = 1;

	/* ENET_RX_DV */
	SIUL2.MSCR[50].B.SSS = 0;
	SIUL2.MSCR[50].B.IBE = 1;
	SIUL2.MSCR[50].B.SRC = 3;
	SIUL2.IMCR[91].B.SSS = 1;
//	SIUL2.GPDO[12].B.PDO_4n2 = 1;

	/* ENET_RX_ER */
//	SIUL2.MSCR[120].B.SSS = 0;
//	SIUL2.MSCR[120].B.IBE = 1;
//	SIUL2.MSCR[120].B.SRC = 3;
//	SIUL2.GPDO[30].B.PDO_4n = 0;

	/* ENET_TX_D0 */
	SIUL2.MSCR[48].B.SSS = 4;
	SIUL2.MSCR[48].B.OBE = 1;
	SIUL2.MSCR[48].B.SRC = 3;

	/* ENET_TX_D1 */
	SIUL2.MSCR[51].B.SSS = 4;
	SIUL2.MSCR[51].B.OBE = 1;
	SIUL2.MSCR[51].B.SRC = 3;

	/* ENET_TX_D2 */
	SIUL2.MSCR[52].B.SSS = 4;
	SIUL2.MSCR[52].B.OBE = 1;
	SIUL2.MSCR[52].B.SRC = 3;

	/* ENET_TX_D3 */
	SIUL2.MSCR[106].B.SSS = 3;
	SIUL2.MSCR[106].B.OBE = 1;
	SIUL2.MSCR[106].B.SRC = 3;

	/* ENET_REF_CLK */
	/* ENET_REF_CLK is 125MHz input from PHY. TX_CLK is generated from this */
	SIUL2.MSCR[130].B.SSS = 0;
	SIUL2.MSCR[130].B.IBE = 1;
	SIUL2.MSCR[130].B.SRC = 3;

	/* ENET_TX_CLK */
	SIUL2.MSCR[107].B.SSS = 2;
	SIUL2.MSCR[107].B.OBE = 1;
	SIUL2.MSCR[107].B.SRC = 3;

	/* ENET_TX_EN */
	SIUL2.MSCR[47].B.SSS = 4;
	SIUL2.MSCR[47].B.OBE = 1;
	SIUL2.MSCR[47].B.SRC = 3;

	/* ENET_TX_ER */
//	SIUL2.MSCR[121].B.SSS = 4;
//	SIUL2.MSCR[121].B.OBE = 1;
//	SIUL2.MSCR[121].B.SRC = 3;
}

#elif defined(PHY_KSZ9031)
static void ENET_GPIO_Init(void)
{
    /* MDIO C17 */
    SIUL2.MSCR[104].B.SSS = 3;
    SIUL2.MSCR[104].B.OBE = 1;
    SIUL2.MSCR[104].B.IBE = 1;
    SIUL2.MSCR[104].B.SRC = 3;
 
    /* MDC C13 */
    SIUL2.MSCR[105].B.SSS = 3;
    SIUL2.MSCR[105].B.OBE = 1;
    SIUL2.MSCR[105].B.SRC = 3;    
    
    /* ENET_REF_CLK U12 */
    SIUL2.MSCR[130].B.SSS = 0;
    SIUL2.MSCR[130].B.IBE = 1;
    SIUL2.MSCR[130].B.SRC = 3;
    
    /* TX_CLK U11 */
    /* ENET_REF_CLK is 125MHz input from PHY. TX_CLK is generated from this */
    SIUL2.MSCR[107].B.SRC = 3;        
    SIUL2.MSCR[107].B.SSS = 2;
    //SIUL2.MSCR[107].B.IBE = 1;
    SIUL2.MSCR[107].B.OBE = 1;
    //SIUL2.IMCR[20].B.SSS = 1;

    /* TX_EN P11 */
    SIUL2.MSCR[47].B.SRC = 3;        
    SIUL2.MSCR[47].B.SSS = 4;
    SIUL2.MSCR[47].B.OBE = 1;
	
    /* TX_D0 R10 */
    SIUL2.MSCR[48].B.SRC = 3;       
    SIUL2.MSCR[48].B.SSS = 4;
    SIUL2.MSCR[48].B.OBE = 1;

    /* TX_D1 P10 */
    SIUL2.MSCR[51].B.SRC = 3;        
    SIUL2.MSCR[51].B.SSS = 4;
    SIUL2.MSCR[51].B.OBE = 1;
	
    /* TX_D2 T11*/
    SIUL2.MSCR[52].B.SRC = 3;        
    SIUL2.MSCR[52].B.SSS = 4;
    SIUL2.MSCR[52].B.OBE = 1;

    /* TX_D3 */
    SIUL2.MSCR[106].B.SRC = 3;        
    SIUL2.MSCR[106].B.SSS = 3;
    SIUL2.MSCR[106].B.OBE = 1;
    
    /* RX_CLK P14 */
    SIUL2.MSCR[125].B.SRC = 3;
    SIUL2.MSCR[125].B.SSS = 0;
    SIUL2.MSCR[125].B.IBE = 1;
    //SIUL2.MSCR[125].B.PUE = 1;
    SIUL2.IMCR[90].B.SSS = 2;

    /* RX_DV U14 */
    SIUL2.MSCR[50].B.SRC = 3;
    SIUL2.MSCR[50].B.SSS = 0;
    SIUL2.MSCR[50].B.IBE = 1;
    //SIUL2.MSCR[50].B.PUE = 1;
    SIUL2.IMCR[91].B.SSS = 1;

    /* RXD0 T12 */
    SIUL2.MSCR[53].B.SRC = 3;    
    SIUL2.MSCR[53].B.SSS = 0;
    SIUL2.MSCR[53].B.IBE = 1;
    //SIUL2.MSCR[53].B.PUE = 1;
	
    /* RXD1 U13 */
    SIUL2.MSCR[54].B.SRC = 3;    
    SIUL2.MSCR[54].B.SSS = 0;
    SIUL2.MSCR[54].B.IBE = 1;
    //SIUL2.MSCR[54].B.PUE = 1;

    /* RXD2 R13*/
    SIUL2.MSCR[116].B.SRC = 3;        
    SIUL2.MSCR[116].B.SSS = 0;
    SIUL2.MSCR[116].B.IBE = 1;
    //SIUL2.MSCR[116].B.PUE = 1;

    /* RXD3 P13 */
    SIUL2.MSCR[117].B.SRC = 3;        
    SIUL2.MSCR[117].B.SSS = 0;
    SIUL2.MSCR[117].B.IBE = 1;
    //SIUL2.MSCR[117].B.PUE = 1;
}
#endif

void ENET_buffer_init(void){
    uint32_t i;  
    
    for (i = 0; i<NUM_TXBDS; i+=STEP_TXBDS){
        /* Initialise first buffer descriptor - Ethernet MAC header */
        ebuf->txbd[i].status0 = 0x0; // Not last in frame, do not transmit CRC
        ebuf->txbd[i].status8 =
            TX_BD_S8_PINS |     // Generate protocol (UDP) checksum
            TX_BD_S8_IINS |     // Generate IPv4 header checksum
            TX_BD_S8_INT;       // Enable interrupts
            
        ebuf->txbd[i].length = 0; // sizeof(UDP_header); // 14 + 20 + 8 + 8 bytes in the header

        ebuf->txbd[i].data = 0x0;
        
        ebuf->txbd[i].statusA = 0;
        ebuf->txbd[i].statusC = 0;
        ebuf->txbd[i].statusE = 0;
        ebuf->txbd[i].status10 = 0;
        ebuf->txbd[i].timestamp = 0;
        
        /* Initialise second buffer descriptor - payload data */
        
        ebuf->txbd[i+1].status0 =
            TX_BD_S0_L |        // Last bd in frame
            TX_BD_S0_TC;       // Append CRC
        ebuf->txbd[i+1].status8 =
            TX_BD_S8_PINS |     // Generate protocol (UDP) checksum
            TX_BD_S8_IINS |     // Generate IPv4 header checksum
            TX_BD_S8_INT;       // Enable interrupts
            
        ebuf->txbd[i+1].length = 0;      // Set to size passed to transmit function
        ebuf->txbd[i+1].data = 0x0;       // Start address is added here
        
        ebuf->txbd[i+1].statusA = 0;
        ebuf->txbd[i+1].statusC = 0;
        ebuf->txbd[i+1].statusE = 0;
        ebuf->txbd[i+1].status10 = 0;
        ebuf->txbd[i+1].timestamp = 0;
    }
    ebuf->txbd[NUM_TXBDS-1].status0 |= TX_BD_S0_W;         // Last bd in ring
		
    /* Initialize receive descriptor ring */
     for (i = 0; i < NUM_RXBDS; i++)
     {
    	ebuf->rxbd[i].status0 = RX_BD_S0_E;        //Mark buffer as empty
    	ebuf->rxbd[i].length = 0;
    	ebuf->rxbd[i].status8 = RX_BD_S8_INT;      //Enable transmit and receive flags
    	ebuf->rxbd[i].data = ebuf->rxbuf[i];     //Set address of this data Buffer

    	ebuf->rxbd[i].statusA = 0;
    	ebuf->rxbd[i].statusC = 0;
    	ebuf->rxbd[i].statusE = 0;
    	ebuf->rxbd[i].status10 = 0;
    	ebuf->rxbd[i].timestamp = 0;
     }
     ebuf->rxbd[NUM_RXBDS-1].status0 |= RX_BD_S0_W;     //Set the Wrap Bit on the last BD of each queue
     ebuf->rxbdp = ebuf->rxbd;
     ebuf->txbp = ebuf->txbuf;
}    

static void ENET_mac_init()
{
    /* reset the ENET - clears EIR, etc. */
    ENET.ECR.B.RESET = 1;

    ENET.ECR.B.EN1588 = 1;      /* Enable enhanced functionalities RR*/
    //ENET.ECR.B.EN1588 = 0;      /* Disable enhanced functionalities */

    /* Set the source address for the controller */
    ENET.PALR.R = *(uint32_t*)enet->route.origmac;  //set to match DA in packet
    ENET.PAUR.R = (((uint32_t)enet->route.origmac[4])<<24) + (((uint32_t)enet->route.origmac[5])<<16);

    // No hash matching
    ENET.IALR.R = 0x00000000; //no individual hash matching
    ENET.IAUR.R = 0x00000000;
    ENET.GALR.R = 0x00000000; //no group hash matching
    ENET.GAUR.R = 0x00000000;

    // Set Receive Buffer Size
    ENET.MRBR.R = (uint16_t)SIZE_OF_ENET_RXBUF;
    // Point to the start of the circular Rx buffer descriptor queue
    ENET.RDSR.R = (uint32_t)&ebuf->rxbd[0];
    // Point to the start of the circular Tx buffer descriptor queue
    ENET.TDSR.R = (uint32_t)&ebuf->txbd[0];

    ENET.RCR.B.PADEN = 1;           	/* Enable Padding removal when receiving frames */
    
    ENET.RCR.B.MAX_FL = SIZE_OF_ENET_RXBUF; //MAX_FL = 1500 payload + 18(for DA(6), SA(6), Ethertype(2) and CRC(4))
    ENET.RCR.B.BC_REJ = 1;			// no broadcast
    ENET.RCR.B.PROM = 0;
    
    /* Set the transceiver interface to RGMII mode */

	/* 100M MII */
	/* 100M RGMII */

    ENET.RCR.B.RMII_MODE = 0;
    ENET.RCR.B.MII_MODE = 1;    // Must always be set

    /* LOOPBACK */
    ENET.RCR.B.LOOP = 0;        /* Disable loopback mode */

    /* Operate in full-duplex mode */
    ENET.TCR.R = 0x0104;

    ENET.TFWR.B.STRFWD = 0x1;
    ENET.TACC.B.PROCHK = 0x1;   // Enable insertion of protocol (UDP) checksum
    ENET.TACC.B.IPCHK = 0x1;   // Enable insertion of IP header checksum

    ENET.MIBC.B.MIB_DIS = 0x0;  // Enable MIB

    /* Set MII speed to be 60/((MSCR+1)*2) = <2.5Mhz */
    ENET.MSCR.B.HOLDTIME = 7;
    ENET.MSCR.B.DIS_PRE = 0;
    ENET.MSCR.B.MII_SPEED = 0xB;

#if defined(PHY_TJA1101)
    /* Set the transceiver interface to RGMII mode */
	ENET.RCR.B.RGMII_EN = 0;    // RGMII mode disable
#elif defined(PHY_88Q2112) || defined(PHY_KSZ9031)
    ENET.RCR.B.RGMII_EN = 1;    //RGMII mode
#endif

#if defined(ENET_100M) || defined(PHY_TJA1101)
	ENET.ECR.B.SPEED = 0;       // 10/100-Mbit/s mode (PHY TJA1101 only support 10/100-Mbit/s)
#else
    ENET.ECR.B.SPEED = 1;       //GB speed

    /* LOOPBACK */

    /* Operate in full-duplex mode */
    
    
       
    /* Set MII speed to be 60/((MSCR+1)*2) = <2.5Mhz */
    //ENET.MSCR.R = 0xB;  
#endif

    ENET.EIMR.B.TXB = 0;
    ENET.EIMR.B.TXF = 1;
    ENET.EIMR.B.RXF = 1;
    ENET.EIMR.B.RXB = 0;

    ENET.EIMR.B.BABR = 1;
    ENET.EIMR.B.BABT = 1;
    ENET.EIMR.B.GRA = 1;
    ENET.EIMR.B.MII = 1;
    ENET.EIMR.B.EBERR = 1;
    ENET.EIMR.B.LC = 1;
    ENET.EIMR.B.RL = 1;
    ENET.EIMR.B.UN = 1;

    INTC.PSR[217].R = 0x8001;
    INTC.PSR[218].R = 0x8001;
    INTC.PSR[219].R = 0x8001;

    /* enable ENET */
    ENET.ECR.B.ETHEREN = 1;

    // Indicate Empty buffers have been produced
    ENET.RDAR.B.RDAR = 1;
}

static void ENET_phy_init()
{
#if defined(PHY_88Q2112)
	/* Initial PHY 88Q2112 */
	/* Generate 125MHz */
	ENET_access_phy_register(3, 0x8004);
	ENET_write_phy_register(3, 0x0001);
#endif
}

/***********************************************************************************************
*
* @brief    ENET_RADAR_Init - ENET module, structures, descriptors and pins initialization routine
* @param    none
* @return   none
*
************************************************************************************************/
void ENET_init()
{
    enet_handle_init();
    ENET_GPIO_Init();       // Initialize pads
    ENET_buffer_init();     // Initialize buffer descriptors and data buffers
    ENET_mac_init();
	ENET_phy_init();
}

/***********************************************************************************************
* @brief    ENET_UDP_Tx
* @param    uint8_t *buffer - point to byte array to transmit in UDP payload
* @param    uint32_t size - size in bytes of the array
* @return   none
* Do not attempt to transmit an array of size>1500
************************************************************************************************/
static void ENET_UDP_Tx()
{
	if (enet->head != enet->tail) {
		enet_tx_packet_p pkt = enet->tail;
		uint16_t leng = (UDP_HEADER_LEN + sizeof(nap_header_t) + SIZE_OF_ENET_PACKET_DATA);
		uint16_t pos = enet->txbd_r;
		uint16_t idx = enet->txbd_r/STEP_TXBDS;

		//enet_route_packet();
		// Modify the UDP header to populate the IPv4 length field
		UDP_header[idx][16] = ((IPv4_HEADER_LEN + leng) >> 8) & 0xFF;
		UDP_header[idx][17] = (IPv4_HEADER_LEN + leng) & 0xFF;

		enet->identifcation++;
		UDP_header[idx][18] = enet->identifcation>>8;
		UDP_header[idx][19] = enet->identifcation;

		// Modify the UDP header to populate the UDP length field

		// src port = payload[0..1]
		UDP_header[idx][34] = pkt->payload[0];
		UDP_header[idx][35] = pkt->payload[1];

		UDP_header[idx][38] = (leng >> 8) & 0xFF;
		UDP_header[idx][39] = leng & 0xFF;
		// Clear the checksums
		UDP_header[idx][24] = 0x00;
		UDP_header[idx][25] = 0x00;
		UDP_header[idx][40] = 0x00;
		UDP_header[idx][41] = 0x00;

	    ebuf->txbd[pos].data = UDP_header[idx];
	    ebuf->txbd[pos].length = sizeof(UDP_header[idx]); // 14 + 20 + 8 + 8 bytes in the header

		ebuf->txbd[pos+1].data = pkt->payload;
		ebuf->txbd[pos+1].length = SIZE_OF_ENET_PACKET_DATA;
		pkt->hdr.length += sizeof(nap_header_t);
		memcpy((void*)&UDP_header[idx][42], (void*)&pkt->hdr, sizeof(nap_header_t));
		// Reset txbd status0
		ebuf->txbd[pos].status0 = TX_BD_S0_R;
		ebuf->txbd[pos+1].status0 = (TX_BD_S0_R | TX_BD_S0_L | TX_BD_S0_TC);
		enet->txbd_r += STEP_TXBDS;
		if (enet->txbd_r >= NUM_TXBDS) {
			enet->txbd_r = 0;
			ebuf->txbd[pos+1].status0 |= TX_BD_S0_W;
		}
		ebuf->txbd[enet->txbd_r].status0 = 0;
		ebuf->txbd[enet->txbd_r+1].status0 = TX_BD_S0_L | TX_BD_S0_TC;
		if (enet->tail == (tx_packets+SIZE_OF_ENET_PACKET_QUE-1))
			enet->tail = tx_packets;
		else
			enet->tail++;

		//PRINTF("ST: %x %x %x %x\n", ebuf->txbd[0].status0, ebuf->txbd[1].status0, ebuf->txbd[2].status0, ebuf->txbd[3].status0);
		ENET.TDAR.B.TDAR = 1;  // Start transmission
	}
	else if(enet->etx_done) {
		//ENET.TDAR.B.TDAR = 1;  // Start transmission
		put_event("e_done", (event_proc_p)enet->etx_done, enet->done_data);
	}
}

void enet_rx_frame(void* x)
{
	PRINTF("enet rx frame!\n");
}

//MAC 0 Transmit Buffer Done
void ENET_TX_BUFFER_ISR(void)
{
#if TX_INT
	if (ENET.EIR.B.TXF) {
		ENET.EIR.B.TXF = 1; //reset
		ENET_UDP_Tx();
	}
#endif
	ENET.EIR.B.TXB = 1; //reset
}

void ENET_EVENT_ISR(void)
{
	put_event("net", (event_proc_p)enet_event_handle, (void*)ENET.EIR.R);
	ENET.EIR.B.BABR = 1;	/* Babbling Receive Error */
	ENET.EIR.B.BABT = 1;	/* Babbling Transmit Error */
	ENET.EIR.B.GRA = 1;		/* Graceful Stop Complete */
	ENET.EIR.B.MII = 1;		/* MII Interrupt. */
	ENET.EIR.B.EBERR = 1;	/* Ethernet Bus Error */
	ENET.EIR.B.LC = 1;		/* Late Collision */
	ENET.EIR.B.RL = 1;		/* Collision Retry Limit */
	ENET.EIR.B.UN = 1;		/* Transmit FIFO Underrun */
	mii_completed_flag = 1;	/* MII Completed Flag */
}

void enet_dump_header(uint16_t* d)
{
	//put_string("AD 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
	PRINTF("erx: %04X %04X %04X %04X %04X %04X %04X %04X %04X %04X %04X %04X %04X %04X %04X %04X\n",
			d[0],d[1],d[2],d[3],d[4],d[5],d[6],d[7],d[8],d[9],d[10],d[11],d[12],d[13],d[14],d[15]);
	//PRINTF("10 %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
			//d[16],d[17],d[18],d[19],d[20],d[21],d[22],d[23],d[24],d[25],d[26],d[27],d[28],d[29],d[30],d[31]);
	//PRINTF("20 %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
			//d[32],d[33],d[34],d[35],d[36],d[37],d[38],d[39],d[40],d[41],d[42],d[43],d[44],d[45],d[46],d[47]);
	//PRINTF("30 %02X %02X\n\n",
			//d[48],d[49]);
}

void enet_rx_handler(void *x)
{
    // If the data buffer has not been filled do nothing
    while (!(ebuf->rxbdp->status0 & RX_BD_S0_E)) {
    	vuint8_t *rxf = ebuf->rxbdp->data;
    	uint16_t ethtype = *(uint16_t*)(rxf+12);

    	// Extract the frame
    	//enet_dump_header((uint16_t*)rxf);

    	switch (ethtype){
        	case VLAN:
        		break;
        	case IPv4: {
        		IPv4_Message* ipv4 = (IPv4_Message*) (rxf+14);
        		// Ensure we have an IPv4 datagram with no options field
        		if (ipv4->ver_ihl != 0x45)
        		    break;

        		if (ipv4->prot == ICMP){
        		    //ENET_ICMP_Handler((ICMP_Message*) (&(msg->dest)+1));
        		}
        		else if (ipv4->dest_port == (uint16_t)ORIGPORT){
        		    na_packet_p pkt = (na_packet_p)(rxf+42);
        		    enet->recv_cnt++;
        			if(enet->flags.routed == 0 && rxf[28] == 10 && rxf[29] == 100)
        				enet_set_route(NULL, (uint8_t*)rxf+6, NULL, NULL, 0, 0);
        		    na_packet_handler(pkt);
        		}
        		break;
        	}
        	case ARP:
        		break;
        	case IPv6:
        		break;
    	}

    	if (ebuf->rxbdp == &ebuf->rxbd[NUM_RXBDS-1]){
    		ebuf->rxbdp->status0 	=  RX_BD_S0_W | RX_BD_S0_E;	// Wrap and Empty
    		ebuf->rxbdp->length		= 0;
    		ebuf->rxbdp 			= ebuf->rxbd;
    	}
    	else {
    		ebuf->rxbdp->status0 	= RX_BD_S0_E;		// Empty
    		ebuf->rxbdp->length		= 0;
    		ebuf->rxbdp++;
    	}

    	ENET.RDAR.B.RDAR = 1;
    }
}

void ENET_RX_BUFFER_ISR(){
	put_event("erx", (event_proc_p)enet_rx_handler, NULL);
	// Clear interrupt
	ENET.EIR.B.RXF = 1;
	ENET.EIR.B.RXB = 1;
    // Get the active BD and increment pointer
    return;
}

