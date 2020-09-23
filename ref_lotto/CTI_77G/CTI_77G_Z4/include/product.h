/*
 * product.h
 *
 *  Created on: 2017/10/13
 *      Author: lenovo
 */

#ifndef PRODUCT_H_
#define PRODUCT_H_

#include "parameters.h"

#define PROD_FLAG_SLEEP_DISABLE		0x01
#define PROD_FLAG_PCAN_OUTPUT_ENABLE		0x02
#define PROD_FLAG_RADAR_FCW_OUTPUT_ENABLE	0x04

typedef struct {
	char		name[16];				// 0
	uint16_t	customer;				// 16~17
	uint16_t	product;				// 18~19
	uint16_t	revision;				// 20~21
	uint16_t	device_id;				// 22~23
	char		serial_no[19];			// 24~43
	uint8_t		flags;					// 44
	uint32_t	manufacture_date;		// 45~47
}product_info_t, *product_info_p;

typedef struct product_pars {
	pars_header_t	hdr;
	product_info_t	info;
}product_pars_t, *product_pars_p;

typedef enum {
	PROD_ID_FCW_DUAL 					    = 0,
	PROD_ID_FCW_2_0_COMBO 				    = 1,	    //Combo FCW BV2.0
	PROD_ID_BSD_OMMIT_DUAL 				    = 2,
	PROD_ID_BSD_Omni_1_0_COMBO 			    = 3,	    //Combo BSD Omni BV1.0
	PROD_ID_BSD_2BEAM_DUAL 				    = 4,
	PROD_ID_BSD_TwoB_2_0_COMBO 			    = 5,	    //Combo BSD TwoB BV2.0
	PROD_ID_BSD_TwoB_3_1_COMBO 			    = 6,	    //Combo BSD TwoB BV3.1
	PROD_ID_FCW_ANT_4_COMBO				    = 7,	    //30693G003110_Combo FCW ANT V4
	PROD_ID_BSD_Omni_Master_3p1_COMBO	    = 8,	    //30693G002150_Combo BSD-Master_BV3.1
	PROD_ID_BSD_Omni_Slave_1p1_COMBO	    = 9,	    //30693G002170_Combo BSD-Slave_BV1.1
	PROD_ID_BSD_Omni_Master_3p2_COMBO	    = 10,	    //30693G002200_Combo BSD_Master_BV3.2
	PROD_ID_BSD_Omni_Slave_1p2_COMBO	    = 11,	    //30693G002220_Combo_BSD_Slave_BV1.2
	PROD_ID_BSD_OMMIT_DUAL_79G 			    = 12,
    PROD_ID_93G003_Combo_Front_Radar_BV3p3  = 19,       //93G003_Combo Front Radar_BV3.3
	PROD_ID_93G014_MRR_BV1_0_FOR_Hirain     = 22,       //93G014_MRR BV1.0 FOR Hirain
	PROD_ID_93G003_Combo_Front_Radar_BV3p4  = 24,       //93G003_Combo Front Radar_BV3.4
    PROD_ID_93G014_MRR_BV2p1_FOR_HIRAIN     = 27,       //93G014_MRR BV2.1 FOR Hirain-S32R274
    PROD_ID_93G016_MRR_BV2p1_FOR_HIRAIN_S32R264 = 28,   //93G016_MRR BV2.1 FOR Hirain-S32R264
	PROD_ID_INVALID
} PRODUCT_ID_E;

#define DEFAULT_PRODUCT_ID				PROD_ID_FCW_ANT_4_COMBO
#define DEFAULT_PRODUCT_NAME		"Cubtek 77 Radar"

const product_info_t* product_info_get(void);
void product_init(void);

#define PROD_PARS_ID									FOURCC('p','r','o','d')

#if defined(CTI_Z4_0)
	//void product_set_customer_id(char** args, int count);
	void product_cusid_set(uint16_t id);
	void product_id_set(uint16_t id, uint8_t force);
	void product_devid_set(uint16_t id);
	void product_serial_no_get(uint8_t *sn);
	void product_serial_no_set(uint8_t *sn);
	void product_flags_set(uint8_t flags);
	void product_dis_sleep_flag_set(uint8_t disleep);
	uint8_t product_dis_sleep_flag_get(void);
	void product_en_pcan_out_flag_set(uint8_t config);
	uint8_t product_en_pcan_out_flag_get(void);
	void product_en_radar_fcw_out_flag_set(uint8_t config);
	uint8_t product_en_radar_fcw_out_flag_get(void);			
	void product_manufacture_date_set(uint32_t date);
	void product_pars_set(void);
	
	#define PROD_IDS_GET()		product_ids((prod_ids_t)((uint32_t)PROD_ID_INVALID << 16 | CUSTOM_ID_INVALID))
	#define PROD_IDS_SET(_ids)	product_ids(_ids)

	#define product_pars_info_get(_ver,_size)				pars_info_get(PROD_PARS_ID, _ver,_size)
	#define product_pars_info_set(_data,_cnt)				pars_info_set(PROD_PARS_ID, _data, _cnt)
#endif

#endif /* PRODUCT_H_ */
