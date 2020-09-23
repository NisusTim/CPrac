/*
 * ENET_RADAR.h
 *
 *  Created on: Feb 19, 2016
 *      Author: B46845
 *
 */

#ifndef _ENET_H_
#define _ENET_H_

/**********************************************************************************************
* Includes
**********************************************************************************************/

#include "typedefs.h"
#include "S32R274.h"



/**********************************************************************************************
* ENET Driver Configuration Macros
**********************************************************************************************/
/* Remote MAC: 37:97:F6:81:C0:FC */
#define DESTMAC1 0xFF
#define DESTMAC2 0xFF
#define DESTMAC3 0xFF
#define DESTMAC4 0xFF
#define DESTMAC5 0xFF
#define DESTMAC6 0xFF

/* DESTINATION IP ADDRESS: 192.168.10.100 */
// Set static IP of interface being transmitted to
#define DESTIP1 192
#define DESTIP2 168
#define DESTIP3 10
#define DESTIP4 100

/* ORIGIN MAC ADDRESS:  00:04:9F:22:0E:B0*/
#define ORIGMAC1 0x00
#define ORIGMAC2 0x04
#define ORIGMAC3 0x9F
#define ORIGMAC4 0x22
#define ORIGMAC5 0x0E
#define ORIGMAC6 0xB0


/* ORIGIN IP ADDRESS: 192.168.10.10 */
#define ORIGIP1 192
#define ORIGIP2 168
#define ORIGIP3 10
#define ORIGIP4 10

/* DESTINATION PORT */
#define DESTPORT 50505

/* ORIGIN PORT */
#define ORIGPORT 50506

/**********************************************************************************************
* Macros
**********************************************************************************************/
#define ENET ENET_0
#define PHY_ADDR 0x7

//{
/*
 * Legacy Bit level Buffer Descriptor definitions
 */
#define TX_BD_R         0x8000
#define TX_BD_INUSE     0x4000
#define TX_BD_TO1       0x4000
#define TX_BD_W         0x2000
#define TX_BD_TO2       0x1000
#define TX_BD_L         0x0800
#define TX_BD_TC        0x0400
#define TX_BD_DEF       0x0200
#define TX_BD_HB        0x0100
#define TX_BD_LC        0x0080
#define TX_BD_RL        0x0040
#define TX_BD_UN        0x0002
#define TX_BD_CSL       0x0001

#define RX_BD_E         0x8000
#define RX_BD_INUSE     0x4000
#define RX_BD_R01       0x4000
#define RX_BD_W         0x2000
#define RX_BD_R02       0x1000
#define RX_BD_L         0x0800
#define RX_BD_M         0x0100
#define RX_BD_BC        0x0080
#define RX_BD_MC        0x0040
#define RX_BD_LG        0x0020
#define RX_BD_NO        0x0010
#define RX_BD_SH        0x0008
#define RX_BD_CR        0x0004
#define RX_BD_OV        0x0002
#define RX_BD_TR        0x0001

/* Enhanced TX Buffer Descriptor Bit Level Definitions - Status0 */
#define TX_BD_S0_R              0x8000
#define TX_BD_S0_TO1            0x4000
#define TX_BD_S0_W              0x2000
#define TX_BD_S0_TO2            0x1000
#define TX_BD_S0_L              0x0800
#define TX_BD_S0_TC             0x0400

/* Enhanced TX Buffer Descriptor Bit Level Definitions - Status8 */
#define TX_BD_S8_INT            0x4000
#define TX_BD_S8_TS             0x2000
#define TX_BD_S8_PINS           0x1000
#define TX_BD_S8_IINS           0x0800
#define TX_BD_S8_FTYPE          0x00F0

/* Enhanced TX Buffer Descriptor Bit Level Definitions - StatusA */
#define TX_BD_SA_TXE            0x8000
#define TX_BD_SA_UE             0x2000
#define TX_BD_SA_EE             0x1000
#define TX_BD_SA_FE             0x0800
#define TX_BD_SA_LCE            0x0400
#define TX_BD_SA_OE             0x0200
#define TX_BD_SA_TSE            0x0100
/* Enhanced TX Buffer Descriptor Bit Level Definitions - Status10 */
#define TX_BD_S10_BDU           0x8000


/* Enhanced RX Buffer Descriptor Bit Level Definitions - Status0 */
#define RX_BD_S0_E              0x8000
#define RX_BD_S0_RO1            0x4000
#define RX_BD_S0_W              0x2000
#define RX_BD_S0_RO2            0x1000
#define RX_BD_S0_L              0x0800
#define RX_BD_S0_M              0x0100
#define RX_BD_S0_BC             0x0080
#define RX_BD_S0_MC             0x0040
#define RX_BD_S0_LG             0x0020
#define RX_BD_S0_NO             0x0010
#define RX_BD_S0_CR             0x0004
#define RX_BD_S0_OV             0x0002
#define RX_BD_S0_TR             0x0001

/* Enhanced RX Buffer Descriptor Bit Level Definitions - Status8 */
#define RX_BD_S8_ME             0x8000
#define RX_BD_S8_PE             0x0400
#define RX_BD_S8_CE             0x0200
#define RX_BD_S8_UC             0x0100
#define RX_BD_S8_INT            0x0080

/* Enhanced RX Buffer Descriptor Bit Level Definitions - StatusA */
#define RX_BD_SA_VPCP           0xE000
#define RX_BD_SA_ICE            0x0020
#define RX_BD_SA_PCR            0x0010
#define RX_BD_SA_VLAN           0x0004
#define RX_BD_SA_IPV6           0x0002
#define RX_BD_SA_FRAG           0x0001

/* Enhanced RX Buffer Descriptor Bit Level Definitions - StatusC */
#define RX_BD_SC_HDR_LEN        0xF800
#define RX_BD_SC_PROT_TYPE      0x00FF

/* Enhanced RX Buffer Descriptor Bit Level Definitions - Status10 */
#define RX_BD_S10_BDU           0x8000

/* Bit definitions and macros for MCF_FEC_RCR */
#define MPC_FEC_RCR_LOOP              (0x00000001)
#define MPC_FEC_RCR_DRT               (0x00000002)
#define MPC_FEC_RCR_MII_MODE          (0x00000004)
#define MPC_FEC_RCR_PROM              (0x00000008)
#define MPC_FEC_RCR_BC_REJ            (0x00000010)
#define MPC_FEC_RCR_FCE               (0x00000020)
#define MPC_FEC_RCR_MAX_FL(x)         (((x)&0x000007FF)<<16)


/* Code Definitions */
#ifndef NULL
	#define NULL    0
#endif
#define FAIL    0
#define OK  1
#define TRUE_REJ 2
#define BROADCAST 2

// Ethernet type values
#define VLAN 0x8100
#define IPv4 0x0800
#define ARP 0x0806
#define IPv6 0x86DD

// IPv4 protocol type values
#define ICMP 0x01
#define TCP 0x06
#define UDP 0x11


//}

/**********************************************************************************************
* Types
**********************************************************************************************/

typedef struct
{
    uint8_t 	destination[6];     /* Destination MAC */
    uint8_t 	source[6];     		/* Source MAC */
    uint16_t	length;				/* Data length/type */
                                    /* Payload data */
    								/* CRC is written by hardware */
} EthernetFrame;

typedef struct
{
    uint16_t htype;     /* Hardware type */
    uint16_t ptype;     /* Protocol type */
    uint8_t hlen;      /* Hardware length */
    uint8_t plen;      /* Protocol length */
    uint16_t op;        /* Opcode */
    /* Assumes 6 byte MAC addresses, 4 byte IPv4 addresses */
    uint8_t sha[6];     /* Sender hardware address */
    uint8_t spa[4];     /* Send protocol address */
    uint8_t tha[6];     /* Target hardware address */
    uint8_t tpa[4];     /* Target protocol address */
    
} ARP_Message;

typedef struct
{
    uint8_t ver_ihl;        /* Version & header length */    
    uint8_t tos;            /* Type of service */
    uint16_t len;           /* Packet length (header + payload) */
    uint16_t fid;           /* Fragment ID */
    uint16_t flags_foffset; /* Flags & fragment offse */
    uint8_t ttl;            /* Time-to-live */
    uint8_t prot;           /* Protocol ID */
    uint16_t chksm;         /* IP header checksum */
    uint8_t src[4];           /* Source IP address */
    uint8_t dest[4];          /* Destination IP address */
    uint16_t src_port;
    uint16_t dest_port;
    uint16_t udp_len;
    
} IPv4_Message;

typedef struct
{
    uint8_t dest_mac[6] ;
    uint8_t orig_mac[6] ;
    uint16_t ethertype;
    uint8_t version;
    uint8_t services;
    uint16_t ip_len;
    uint16_t id;
    uint16_t flags;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t chksum;
    uint8_t orig_ip[4];
    uint8_t dest_ip[4];
    uint8_t src_port[2];
    uint8_t dest_port[2];
    uint16_t udp_len;
    uint16_t udp_chksm;
}UDP_header_struct;

typedef struct 
{
    uint8_t type;   /* Type information */   
    uint8_t code;   /* Code related to type */   
    uint16_t chksm; /* Checksum over datagram (header + payload) */   
    uint32_t msg;   /* Message data */   
    
} ICMP_Message;

/* Legacy Buffer Descriptor Format */
typedef struct
{
    uint16_t status;    /* control and status */
    uint16_t length;    /* transfer length */
    uint8_t  *data;     /* buffer address */
} NBUF;

/* Enhanced Buffer Descriptor Format */
typedef struct
{
    vint16_t status0;   /* control and status */
    vint16_t  length;   /* transfer length */
    vuint8_t  *data;   /* buffer address */
    vint16_t status8;   /* control and status */
    vint16_t statusA;   /* control and status */
    vint16_t statusC;   /* control and status */
    vint16_t statusE;   /* control and status */
    vint16_t status10;  /* control and status */
    vint16_t dummy12;   /* control and status */
    vint32_t timestamp; /* control and status */
    vint16_t dummy18;   /* control and status */
    vint16_t dummy1A;   /* control and status */
    vint16_t dumym1C;   /* control and status */
    vint16_t dummy1E;   /* control and status */
} eNBUF;

typedef struct{
    uint16_t vlan;
    uint16_t ipv4;
    uint16_t arp;
    uint16_t ipv6;
} Rx_count;

typedef struct {
  uint32_t reset :1;
  uint32_t loopback :1;
  uint32_t SS_LSB :1;
  uint32_t auto_neg_en :1;
  uint32_t power_down :1;
  uint32_t isolate :1;
  uint32_t reset_auto_neg :1;
  uint32_t duplex_mode :1;
  uint32_t :1;
  uint32_t SS_MSB :1;
  uint32_t :6;
} phy_reg0;


typedef struct {
	uint8_t origip[4];
	uint8_t destip[4];

	uint8_t destmac[6];
	uint8_t origmac[6];

	uint16_t destport;
	uint16_t origport;
} enet_route_t, *enet_route_p;


/* Number of Receive and Transmit Buffers and Buffer Descriptors per Queue */
#define NUM_RXBDS 					16
#define NUM_TXBDS 					4 // num of buffer descriptors are used
#define STEP_TXBDS					2
#define NUM_TXFRAME					(NUM_TXBDS >> 1)
#define NUM_TXBUF					4
#define SIZE_OF_ENET_RXBUF			1088 // 14+20+8+8+1024+4 = 1078 => 1088 for 64 align
#define SIZE_OF_ENET_PACKET_DATA 	1024

typedef void (*done_cb_p) (void*);

typedef struct {
	uint8_t		buf[SIZE_OF_ENET_PACKET_DATA];
}enet_txbuf_t, *enet_txbuf_p;

typedef struct {
	eNBUF 			txbd[NUM_TXBDS];
	eNBUF 			rxbd[NUM_RXBDS];
	vuint8_t 		rxbuf[NUM_RXBDS][SIZE_OF_ENET_RXBUF];
	enet_txbuf_t	txbuf[NUM_TXBUF];
	eNBUF			*rxbdp;
	enet_txbuf_p	txbp;
}enet_buf_t, *enet_buf_p;


void ENET_init(void);
int enet_tx_done_reg(done_cb_p, void*);
int enet_add_packet(uint8_t, uint8_t dt, uint16_t, uint16_t, uint8_t *buffer, uint32_t size);
void enet_set_route(uint8_t* origmac, uint8_t* destmac, uint8_t* origip, uint8_t* destip, uint16_t origport, uint16_t destport);
void enet_packet_info(int);
void enet_rx_handler(void*);
enet_txbuf_p enet_txbuf_get(void);

#endif /* _ENET_H_ */
