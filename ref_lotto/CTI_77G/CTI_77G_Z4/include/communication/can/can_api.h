/*
 * can_api.h
 *
 *  Created on: 2018/06/17
 *      Author: WoodLiu
 */

#ifndef SYS_HAL_CAN_CAN_API_H_
#define SYS_HAL_CAN_CAN_API_H_

#include "typedefs.h"
#include "S32R274.h"
#include "event.h"

#define INVALID_CAN0_MB								96
#define INVALID_CAN2_MB								96

#define RAM_BLOCK0_START_MB                         0
#define RAM_BLOCK1_START_MB                         32
#define RAM_BLOCK2_START_MB                         64

#define SIZE_OF_CAN_PACKET_QUE						32

#if defined(CTI_Z4_0)
#define RX_MB_START											00
#define RX_MB_END											11
#define TX_BURST_MB_START 									12
#define TX_BURST_MB_END 									15
#define TX_MB_START 										16
#define TX_MB_END 											31
#define TX_BURST_MB_DLC64_START                             64
#define TX_BURST_MB_DLC64_END                               69

#define RX2_MB_START										00
#define RX2_MB_END											11
#define TX2_BURST_MB_START 									12
#define TX2_BURST_MB_END 									15
#define TX2_MB_START 										16
#define TX2_MB_END 											31
#define TX2_BURST_MB_DLC64_START                            64
#define TX2_BURST_MB_DLC64_END                              69

#define MAX_COUNT_OF_RX_CANID_REGISTERED					12
#define MAX_COUNT_OF_TX_BURST_CANID_REGISTERED				4
#define MAX_COUNT_OF_TX_CANID_REGISTERED					16
#define MAX_COUNT_OF_TX_BURST_DLC64_CANID_REGISTERED		6

#define CAN0_RX_ISR_MASK									0x0FFF	//MB 00~11
#define CAN0_TX_ISR_MASK									0xF000	//MB 12~15
#define CAN0_TX_DLC_ISR_MASK								0x003F	//MB 64~69
#define CAN2_RX_ISR_MASK									0x0FFF	//MB 00~11
#define	CAN2_TX_ISR_MASK									0xF000	//MB 12~15
#define CAN2_TX_DLC_ISR_MASK								0x003F	//MB 64~69

#define CAN_STD_ID_MASK_FULL								0xFFFFFFFF
#define CAN_STD_ID_MASK_1									0xFFFFFFF0
#define CAN_STD_ID_MASK_2									0xFFFFFF00

#elif defined(CTI_Z7_0) || defined(CTI_Z7_1)
#define RX_MB_START											32
#define RX_MB_END											39
#define TX_BURST_MB_START 									40
#define TX_BURST_MB_END 									47
#define TX_MB_START 										48
#define TX_MB_END 											63
#define TX_BURST_MB_DLC64_START                             70
#define TX_BURST_MB_DLC64_END                               70

#define RX2_MB_START										32
#define RX2_MB_END											39
#define TX2_BURST_MB_START 									40
#define TX2_BURST_MB_END 									47
#define TX2_MB_START 										48
#define TX2_MB_END 											63
#define TX2_BURST_MB_DLC64_START                            70
#define TX2_BURST_MB_DLC64_END                              70

#define MAX_COUNT_OF_RX_CANID_REGISTERED					8
#define MAX_COUNT_OF_TX_BURST_CANID_REGISTERED				8
#define MAX_COUNT_OF_TX_CANID_REGISTERED					16
#define MAX_COUNT_OF_TX_BURST_DLC64_CANID_REGISTERED		1

#define CAN0_RX_ISR_MASK									0x00FF00000000	//MB 32~39
#define CAN0_TX_ISR_MASK									0xFF0000000000	//MB 40~47
#define CAN2_RX_ISR_MASK									0x00FF00000000	//MB 32~39
#define	CAN2_TX_ISR_MASK									0xFF0000000000	//MB 40~47

#define CAN_STD_ID_MASK_FULL								0xFFFFFFFF
#define CAN_STD_ID_MASK_1									0xFFFFFFF0
#define CAN_STD_ID_MASK_2									0xFFFFFF00
#endif

/*******************************************************************************
* Function prototypes
*******************************************************************************/
#define  FLEXCAN0_ESR_BERR		520
#define  FLEXCAN_ESR_BOFF		521
#define  FLEXCAN0_BUF_00_03		522
#define  FLEXCAN0_BUF_04_07		523
#define  FLEXCAN0_BUF_08_11		524
#define  FLEXCAN0_BUF_12_15		525
#define  FLEXCAN0_BUF_16_31		526
#define  FLEXCAN0_BUF_32_39		527
#define  FLEXCAN0_BUF_40_47		528
#define  FLEXCAN0_BUF_48_55		529
#define  FLEXCAN0_BUF_56_63		530
#define  FLEXCAN0_BUF_64_79		531
#define  FLEXCAN0_BUF_80_95		532

#define  FLEXCAN2_ESR_BERR		546
#define  FLEXCAN2_BUF_00_03		548
#define  FLEXCAN2_BUF_04_07		549
#define  FLEXCAN2_BUF_08_11		550
#define  FLEXCAN2_BUF_12_15		551
#define  FLEXCAN2_BUF_16_31		552
#define  FLEXCAN2_BUF_32_39		553
#define  FLEXCAN2_BUF_40_47		554
#define  FLEXCAN2_BUF_48_55		555
#define  FLEXCAN2_BUF_56_63		556
#define  FLEXCAN2_BUF_64_79		557
#define  FLEXCAN2_BUF_80_95		558

#define  VECTOR_520		FLEXCAN0_ESR_BERR
#define  VECTOR_521		FLEXCAN_ESR_BOFF
#define  VECTOR_522		FLEXCAN0_BUF_00_03	//	4	Core0 RX
#define  VECTOR_523		FLEXCAN0_BUF_04_07	//	4	Core0 RX
#define  VECTOR_524		FLEXCAN0_BUF_08_11	//	4	Core0 RX
#define  VECTOR_525		FLEXCAN0_BUF_12_15	//	4	Core0 TX - continuous data
#define  VECTOR_526		FLEXCAN0_BUF_16_31	//	16	Core0 TX - discrete data

#define  VECTOR_527		FLEXCAN0_BUF_32_39	//	8   Core1 RX
#define  VECTOR_528		FLEXCAN0_BUF_40_47 	//	8   Core1 TX - continuous data
#define  VECTOR_529		FLEXCAN0_BUF_48_55	//	8   Core1 TX - discrete data
#define  VECTOR_530		FLEXCAN0_BUF_56_63	//	8   Core1 TX - discrete data

#define  VECTOR_531		FLEXCAN0_BUF_64_79	//	16	Core2
#define  VECTOR_532		FLEXCAN0_BUF_80_95	//	16	Core2

#define  VECTOR_548		FLEXCAN2_BUF_00_03	//	4   Core0 RX
#define  VECTOR_549		FLEXCAN2_BUF_04_07	//	4   Core0 RX
#define  VECTOR_550		FLEXCAN2_BUF_08_11	//	4   Core0 RX
#define  VECTOR_551		FLEXCAN2_BUF_12_15	//	4   Core0 TX - continuous data
#define  VECTOR_552		FLEXCAN2_BUF_16_31	//	16  Core0 TX - discrete data

#define  VECTOR_553		FLEXCAN2_BUF_32_39	//	8   Core1 RX
#define  VECTOR_554		FLEXCAN2_BUF_40_47	//	8   Core1 TX - continuous data
#define  VECTOR_555		FLEXCAN2_BUF_48_55	//	8   Core1 TX - discrete data
#define  VECTOR_556		FLEXCAN2_BUF_56_63	//	8   Core1 TX - discrete data

#define  VECTOR_557		FLEXCAN2_BUF_64_79	//	16  Core2
#define  VECTOR_558		FLEXCAN2_BUF_80_95	//	16  Core2

typedef union {
	uint64_t 		dw;
	uint32_t		w[2];
	uint16_t		hw[4];
	uint8_t			b[8];
}can_packet_t, *can_packet_p;

typedef enum {
	CAN_TX_SUCCESS = 0,
	CAN_TX_FAIL_MB_BUSY,
	CAN_TX_FAIL_OUT_OF_MB_RANGE,
	CAN_TX_FAIL_ITF_OFF,
	CAN_TX_INVALID
}can_tx_state_e;

typedef struct {
	event_proc_p		proc;
	char*				name;
	uint32_t			id;
	uint32_t			mask;
	uint8_t				mb;
	uint8_t				reserved;
	uint8_t				clear_isr_flag;
} can_register_t, *can_register_p;

typedef struct {				//8-byte alignment, size = 16 byte
	can_packet_t 	pkg;		//8 byte, can data
	uint32_t		id;			//4 byte, can id
	uint8_t			dlc;		//1 byte, can data length
	uint8_t			pad[3];		//3 byte, rsvd
} can_message_t, *can_message_p;

typedef struct {
	can_message_t 		que[SIZE_OF_CAN_PACKET_QUE];
	can_message_p		msg;
	can_register_t		ids[MAX_COUNT_OF_RX_CANID_REGISTERED];
}can_rx_handle_t, *can_rx_handle_p;

typedef struct {
	uint32_t			txidx;											/*For discrete data*/
	can_register_t		mbs[MAX_COUNT_OF_TX_BURST_CANID_REGISTERED];	/*For burst tx*/
}can_tx_handle_t, *can_tx_handle_p;

typedef struct {
	uint32_t			txidx;											/*For discrete data*/
	can_register_t		mbs[MAX_COUNT_OF_TX_BURST_DLC64_CANID_REGISTERED];	/*For burst tx*/
}can_dlc_tx_handle_t, *can_dlc_tx_handle_p;

#ifdef USING_CUBTEK_CAN_0
can_tx_state_e CanTransmitMessage(uint32_t ID, uint32_t* p);
#endif
can_tx_state_e Can2TransmitMessage(uint32_t ID, uint32_t* p);

#ifdef USING_CUBTEK_CAN_0
can_tx_state_e CanTransmitBurstMessage(uint8_t mb, uint32_t ID, uint32_t* p);
#endif
can_tx_state_e Can2TransmitBurstMessage(uint8_t mb, uint32_t ID, uint32_t* p);

#ifdef USING_CUBTEK_CAN_0
uint8_t Can0TransmitMessageDlc(uint8_t mb, uint32_t ID, uint32_t* p, uint16_t remain_size);
#endif
uint8_t Can2TransmitMessageDlc(uint8_t mb, uint32_t ID, uint32_t* p, uint16_t remain_size);

#ifdef USING_CUBTEK_CAN_0
void can_rx_id_register(uint32_t id, uint32_t mask, char* name, event_proc_p proc);
#endif
void can2_rx_id_register(uint32_t id, uint32_t mask, char* name, event_proc_p proc);

#ifdef USING_CUBTEK_CAN_0
extern void can_rx_id_register_again_by_name(uint32_t id, uint32_t mask, char* name, event_proc_p proc);
#endif
extern void can2_rx_id_register_again_by_name(uint32_t id, uint32_t mask, char* name, event_proc_p proc);

#ifdef USING_CUBTEK_CAN_0
uint8_t can_tx_burst_data_register(char* name, event_proc_p proc, uint8_t clear_isr_flag);
#endif
uint8_t can2_tx_burst_data_register(char* name, event_proc_p proc, uint8_t clear_isr_flag);

#ifdef USING_CUBTEK_CAN_0
uint8_t can_tx_burst_data_register_dlc64(char* name, event_proc_p proc, uint8_t clear_isr_flag);
#endif
uint8_t can2_tx_burst_data_register_dlc64(char* name, event_proc_p proc, uint8_t clear_isr_flag);
void can_api_init(void);
void enable_can2_console_mask(uint8_t select_mb);
void disable_can2_console_mask(uint8_t select_mb);
void clear_can2_console_flags(uint8_t select_mb);



typedef union CAN_MB_DATA_DLC64_union_tag {
  vuint8_t B[64];
  vuint16_t H[32];
  vuint32_t W[16];
} CAN_MB_DATA_DLC64_tag;

typedef struct CAN_MB_DLC64_struct_tag {
  CAN_MB_CS_tag CS;                    /* Message Buffer 0 CS Register */
  CAN_MB_ID_tag ID;                    /* Message Buffer 0 ID Register */
  CAN_MB_DATA_DLC64_tag DATA;
} CAN_MB_DLC64_tag;

struct CAN_DLC_MB_tag {
    CAN_MB_DLC64_tag MB[7];
};
    
#define CAN_0_DLC (*(volatile struct CAN_DLC_MB_tag *) 0xFFEC0480UL)
#define CAN_2_DLC (*(volatile struct CAN_DLC_MB_tag *) 0xFBEC0480UL)


#endif /* SYS_HAL_CAN_CAN_API_H_ */
