/*
 * helios.h
 *
 *  Created on: 2020/01/20
 * 		Author: ricewu
 */
#ifndef _HELIOS_H_
#define _HELIOS_H_

#include "isotp.h"
//#include "parameters.h"

#define Transmitter_ID		0x87
#define Receiver_ID		0x78
#define SIZE_PAYLOAD		1024
#define SIZE_HELIOS_HEADER		8
#define	FOURCOMB(_a,_b,_c,_d)		((((uint32_t)_a)<<24)|(((uint32_t)_b)<<16)|(((uint32_t)_c)<<8)|((uint32_t)_d))
#define	TWOCOMB(_e,_f)		((((uint16_t)_e)<<8)|((uint16_t)_f))

typedef struct {
	uint8_t DT;			//Data Type
	uint8_t RW: 1;		//read write
	uint8_t RT: 1;		//real time
	uint8_t RSVD: 4;	//reserved
	uint8_t PDT: 2;		//PDType
	uint8_t RSVD2;		//base_addr, id, st, frame rate, packet length
	uint8_t RSVD3;		//base_addr, id, RF, packet length
	uint8_t RSVD4;		//base_addr, id, data_CB,
	uint8_t RSVD5;		//base_addr, id
	uint8_t RSVD6;		//length
	uint8_t RSVD7;		//length
}helios_header_t, *helios_header_p;

typedef struct{
	uint16_t (*play)(uint8_t nmeas, uint8_t lmeas, uint8_t rate, event_proc_p done_cb, event_proc_p new_cb);
	void (*pause)(char** args, int count);
}frame_proc_t, *frame_proc_p;

typedef struct{
	helios_header_p hdr_p;
	IsoTpLink *isotp_link;
	frame_proc_p fproc;
}helios_t, *helios_p;

typedef enum {
	DT_NULL = 0,
	DT_MMAP,		//0x01
	DT_MEM,			//0x02
	DT_TEXT,		//0x03
	DT_PARAM,		//0x04
	DT_RFSP,		//0x05
	DT_LNCH,		//0x06
	DT_PAUSE,		//0x07
	DT_PLAY,		//0x08
	DT_CONT,		//0x09
	DT_ADC = 0x11,	//0x11
	DT_RANGE,		//0x12
	DT_DPPLR,		//0x13
	DT_FFT3D,		//0x14
	DT_HIST,		//0x15
	DT_PEAK,		//0x16
	DT_MEAS,		//0x17
	DT_LNG
}dtype;

void helios_init(frame_proc_p frame_func);
helios_p get_HES_Handler(void);
void helios_rcvr_handler(IsoTpLink *isotp_link);
void aoa_printf(uint8_t *data_addr, uint16_t data_len);

#endif  // _HELIOS_H_
