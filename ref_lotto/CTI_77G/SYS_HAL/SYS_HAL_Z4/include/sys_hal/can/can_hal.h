/*
 * can_hal.h
 *
 *  Created on: 2017/3/6
 *      Author: erichu
 */

#ifndef CAN_HAL_H_
#define CAN_HAL_H_

#include "sys_shared.h"

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

#define CAN_TX_CODE                     0x07
#define CAN_TX_CODE_INACTIVE            0x00
#define CAN_TX_CODE_DATA                0x04

typedef enum {
	CAN_IDE_STANDARD = 0,
	CAN_IDE_EXTENDED = 1,
	CAN_IDE_UNKNOWN,
}CAN_IDE_E;

typedef enum {
	CAN_BR_1M = 0,
	CAN_BR_500K = 1,
	CAN_BR_250K = 2,
	CAN_BR_100K = 3,
	CAN_FD_500K_2M = 4,
	CAN_FD_1M_2M = 5,
	CAN_FD_500K_4M = 6,
	CAN_FD_1M_4M = 7,
	CAN_FD_1M_8M =8,
	CAN_BR_UNKNOWN,
}CAN_BAUDRATE_E;

typedef enum {
	CAN_BR_REG_VAL_1M 	= 3,
	CAN_BR_REG_VAL_500K = 7,
	CAN_BR_REG_VAL_250K = 15,
	CAN_BR_REG_VAL_100K = 39,
}CAN_BAUDRATE_REGISTER_VALUE_E;

typedef struct {
	CAN_IDE_E ide0;
	CAN_IDE_E ide2;
	CAN_BAUDRATE_E  br0;
	CAN_BAUDRATE_E  br2;
	uint8_t can0_dlc_enable;
	uint8_t can2_dlc_enable;
	uint32_t uds_physical_request;
	uint32_t uds_physical_response;
}can_info_t, *can_info_p;

#if defined(CTI_Z4_0)

typedef struct {
	pars_header_t	hdr;
	can_info_t	info;
}can_parameters_t, *can_parameters_p;

#define CAN_PARS_ID								FOURCC('c','a','n','p')
#define can_pars_info_get(_ver,_size)			pars_info_get(CAN_PARS_ID,  _ver,_size)
#define can_pars_info_set(_data,_cnt)			pars_info_set(CAN_PARS_ID, _data, _cnt))

void can_init();
void can_tester(char** args, int count);
void can2_tester(char** args, int count);
void CAN_0_Bus_Off_Rec_InterruptHandler(void);
void can_0_boff_rec(uint32_t d);
uint8_t get_can0_ide(void);
uint8_t get_can2_ide(void);
extern void set_can0_ide0_and_br0(int16_t ide ,int16_t br);
extern void set_can2_ide2_and_br2(int16_t ide ,int16_t br);
extern int16_t get_can0_br0(void);
uint8_t get_can2_br(void);
extern uint32_t get_uds_physical_request(void);
extern uint32_t get_uds_physical_response(void);
extern void set_uds_physical_request(uint32_t canid);
extern void set_uds_physical_response(uint32_t canid);
extern void can_info_pars_save(void);
extern void can_info_pars_save_handler(void);

#elif defined(CTI_Z7_0)
uint8_t get_can0_ide(void);
uint8_t get_can2_ide(void);
uint8_t get_can0_br0(void);
uint8_t get_can2_br(void);
#elif defined(CTI_Z7_1)
uint8_t get_can0_ide(void);
uint8_t get_can2_ide(void);
uint8_t get_can0_br0(void);
uint8_t get_can2_br(void);
#endif


void SettingCAN_0_MailBoxCanId(uint8_t idx, vuint32_t canid, vuint32_t mask);
void SettingCAN_2_MailBoxCanId(uint8_t idx, vuint32_t canid, vuint32_t mask);
extern uint8_t CAN0_GetMBSt(uint8_t mb);
extern uint8_t CAN2_GetMBSt(uint8_t mb);

uint8_t get_can0_dlc_status(void);
uint8_t get_can2_dlc_status(void);
void set_can0_br_dlc(uint8_t br, uint8_t dlc_enable);
void set_can2_br_dlc(uint8_t br, uint8_t dlc_enable);

#endif /* CAN_HAL_H_ */
