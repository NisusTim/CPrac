/*
 * netagent.h
 *
 *  Created on: 2017�~4��11��
 *      Author: erichu
 */

#ifndef NETAGENT_H_
#define NETAGENT_H_

typedef struct {
	uint16_t 	length;
	uint8_t		misc;
	uint8_t		type;	// high nibble is used as ack_id, low nibble is NAPT
	uint16_t 	attr;
	uint16_t	idx;
}nap_header_t, *nap_header_p;

typedef enum {
	NAMISC_GET,		//0
	NAMISC_SET,		//1
	NAMISC_CTRL,	//2
	NAMISC_ACK,		//3
	NAMISC_DONE,	//4
	NAMISC_DATA		//5
}nap_misc_e;

typedef enum {
	NAPT_RAW = 0,			// 0
	NAPT_STRING,			// 1
	NAPT_MISSED,			// 2
	NAPT_PARAMETERS,		// 3
	NAPT_RANGE,				// 4
	NAPT_DOPPLER,			// 5
	NAPT_FFT3D,				// 6
	NAPT_FFT16,				// 7
	NAPT_HIST,				// 8
	NAPT_AOA_DATA,			// 9
	NAPT_MEASUREMENTS,		// 10
	NAPT_MEM,				// 11
	NAPT_INVALID
} nap_data_type_e;

/*
 * fn: values index
 */
typedef enum {
	FRM_ATTR_PKTSZ_SEQ=0,
	FRM_ATTR_PKTSZ_TOTAL,
	FRM_ATTR_FS_TYPE,
	FRM_ATTR_FN,
	FRM_ATTR_SPEED,
	FRM_ATTR_YAW,
	FRM_ATTR_STEERING,
	FRM_ATTR_INVALID
}seq_data_e;


typedef struct {
	nap_header_t	hdr;
	uint8_t			data[SIZE_OF_ENET_PACKET_DATA];
}na_packet_t, *na_packet_p;


void na_packet_handler(na_packet_p);
void na_dcp4d_done(void*);
void na_init();

#endif /* NETAGENT_H_ */
