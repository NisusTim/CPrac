/*
 * product.c
 *
 *  Created on: 2017/10/13
 *      Author: lenovo
 */

#include "sys_shared.h" /* include peripheral declarations */
#if defined(CTI_Z4_0)
#ifdef ENABLE_BSW_UDS_NM
#include "can_cubtek.h"
#include "Com_cfg.h"
#endif
#endif
////////////////////////////////////////////////////////////////////////////////
//
//  product information
//
////////////////////////////////////////////////////////////////////////////////

#if defined(CTI_Z4_0)

#define DEFAULT_PROD_FLAGS		0 // 
#define PROD_SLEEP_FLAG_SWITCH	TRUE// FALSE: disleep-0(sleep mode) / TRUE: disleep-1(sleep mode)

static product_pars_t __attribute__((section(".product"))) product_pars;

static const product_pars_t product_default = {
		.hdr = {
				.base = (uint32_t)&product_pars,
				.version = 0x0200,
				.size = sizeof(product_pars_t),
				.id = PROD_PARS_ID,
				.chksum = 0,
				.mask = 0
		},

		.info = {
				.name = DEFAULT_PRODUCT_NAME,
				.product = PROD_ID_93G003_Combo_Front_Radar_BV3p4,
				.customer = DEFAULT_CUSTOMER_ID,
				.revision = 0,
				.device_id = 0,
				.serial_no = "00000000001",
				.flags = DEFAULT_PROD_FLAGS,
				.manufacture_date = 0x20190101
		}
};

static const char* prod_name[]={
        "FCW_DU",                   //0
        "FCW_2p0_CBO",              //1
        "BSD_OMNI_DU",              //2
        "BSD_OMNI_1p0_CBO",         //3
        "BSD_TwoB_DU",              //4
        "BSD_TwoB_2p0_CBO",         //5
        "BSD_TwoB_3p1_CBO",         //6
        "FCW_ANT_4_CBO",            //7
        "BSD_OMNI_M_3p1_CBO",       //8
        "BSD_OMNI_S_1p1_CBO",       //9
        "BSD_OMNI_M_3p2_CBO",       //10
        "BSD_OMNI_S_1p2_CBO",       //11
        "BSD_OMNI_DU_79G",          //12
        "NA",                       //13
        "NA",                       //14
        "NA",                       //15
        "NA",                       //16
        "NA",                       //17
        "NA",                       //18
        "93G003_FR_BV3p3",          //19
        "NA",                       //20
        "NA",                       //21
        "93G014_FR_BV1p0",          //22
        "NA",                       //23
        "93G003_FR_BV3p4",          //24
        "NA",                       //25
        "NA",                       //26
        "93G014_MRR_BV2p1_274",     //27
        "93G016_MRR_BV2p1_264"      //28
};

#define JSON_PROD_INFO_NAME 		"\t\t\"name\":{\"t\":\"s%d\",\"o\":%d,\"v\":\"%s\"},\n"
#define JSON_PROD_INFO_CUSTOMER 	"\t\t\"customer\":{\"t\":\"u16\",\"o\":%d,\"v\":%u},\n"
#define JSON_PROD_INFO_PRODUCT 		"\t\t\"product\":{\"t\":\"u16\",\"o\":%d,\"v\":%u},\n"
#define JSON_PROD_INFO_REVISION 	"\t\t\"revision\":{\"t\":\"u16\",\"o\":%d,\"v\":%u},\n"
#define JSON_PROD_INFO_DEVICEID 	"\t\t\"deviceid\":{\"t\":\"u16\",\"o\":%d,\"v\":%u},\n"
#define JSON_PROD_INFO_SERIAL_NO	"\t\t\"serial_no\":{\"t\":\"s%d\",\"o\":%d,\"v\":\"%s\"},\n"
#define JSON_PROD_INFO_FLAGS		"\t\t\"flags\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_PROD_INFO_DATE			"\t\t\"manufacture_date\":{\"t\":\"u32\",\"o\":%u,\"v\":%ld}\n"

static int prod_info_in_jsons(char* ws)
{
	int cnt = 0;
	uint8_t sn_temp[20];
	memcpy(sn_temp,product_pars.info.serial_no,19);
	sn_temp[19]=0;
	
	if(ws){
		cnt = sprintf(ws,"{\n");
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_ID, (char)(PROD_PARS_ID>>24),(char)(PROD_PARS_ID>>16),
				(char)(PROD_PARS_ID>>8),(char)(PROD_PARS_ID));
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_VERSION, product_pars.hdr.version);
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_SIZE, product_pars.hdr.size - sizeof(pars_header_t));

		cnt += sprintf(ws+cnt,"\t\"info\":{\n");
		cnt += sprintf(ws+cnt, JSON_PROD_INFO_NAME,strlen(product_pars.info.name), offsetof(product_info_t, name), product_pars.info.name);
		cnt += sprintf(ws+cnt, JSON_PROD_INFO_CUSTOMER,offsetof(product_info_t, customer), product_pars.info.customer);
		cnt += sprintf(ws+cnt, JSON_PROD_INFO_PRODUCT,offsetof(product_info_t, product), product_pars.info.product);
		cnt += sprintf(ws+cnt, JSON_PROD_INFO_REVISION,offsetof(product_info_t, revision), product_pars.info.revision);
		cnt += sprintf(ws+cnt, JSON_PROD_INFO_DEVICEID,offsetof(product_info_t, device_id), product_pars.info.device_id);
		cnt += sprintf(ws+cnt, JSON_PROD_INFO_SERIAL_NO,strlen(product_pars.info.serial_no), offsetof(product_info_t, serial_no), sn_temp);
		cnt += sprintf(ws+cnt, JSON_PROD_INFO_FLAGS,offsetof(product_info_t, flags), product_pars.info.flags);
		cnt += sprintf(ws+cnt, JSON_PROD_INFO_DATE,offsetof(product_info_t, manufacture_date), product_pars.info.manufacture_date);
		cnt += sprintf(ws+cnt, "\t}\n}\n");
	}
	return cnt;
}

static void _product_pars_dump(void)
{
	uint8_t sn_temp[20];
	memcpy(sn_temp,product_pars.info.serial_no,19);
	sn_temp[19]=0;
	
	PRINTF("prod pars: %s\n", product_pars.info.name);
	PRINTF("prod cusid : %d(%s)\n", DEFAULT_CUSTOMER_ID, customer_name_get(DEFAULT_CUSTOMER_ID));
	PRINTF("prod pid   : %d(%s)\n", product_pars.info.product,prod_name[product_pars.info.product]);
	PRINTF("prod rev   : %d\n",product_pars.info.revision);
	PRINTF("prod devid : %d\n",product_pars.info.device_id);
	PRINTF("prod sn(19): \"%s\"\n",sn_temp);
	PRINTF("prod flags : 0x%02X, b0:disleep b1:TL_on_Pcan b2:fcw_warning\n",product_pars.info.flags);
	PRINTF("prod disleep : %d (0:normal,1:sleep)\n", (product_pars.info.flags&PROD_FLAG_SLEEP_DISABLE));
	PRINTF("prod target on PCAN : %d\n", (product_pars.info.flags&PROD_FLAG_PCAN_OUTPUT_ENABLE)>>1);
	PRINTF("prod fcw warning : %d\n", (product_pars.info.flags&PROD_FLAG_RADAR_FCW_OUTPUT_ENABLE)>>2);				
	PRINTF("prod date  : %.8lxh\n",product_pars.info.manufacture_date);

	PRINTF(" \n");
    PRINTF("prod cusid (active) : %d(%s)\n", DEFAULT_CUSTOMER_ID, customer_name_get(DEFAULT_CUSTOMER_ID));
    PRINTF("prod cusid (eeprom) : %d(%s)\n", product_pars.info.customer, customer_name_get(product_pars.info.customer));
}

static void _product_pars_tester(char** args, int count)
{
	if (count > 2) {
		uint16_t val = (uint16_t)strtoul(args[2], NULL, 10);
		if(!strcmp(args[1], "rev")) {
			product_pars.info.revision = val;
			pars_set((pars_ctx_p)&product_pars);
		}
		else if(!strcmp(args[1], "devid")) {
			product_devid_set(val);
		}
		else if(!strcmp(args[1], "sn")) {
		    uint8_t len=strlen(args[2]);
			if( len <= 19){
				memcpy(product_pars.info.serial_no,args[2],len);
				pars_set((pars_ctx_p)&product_pars);
			}
		}
		else if(!strcmp(args[1], "flags")) {
			product_flags_set((uint8_t)val);
			pars_set((pars_ctx_p)&product_pars);
		}
		else if(!strcmp(args[1], "disleep")) {
			product_dis_sleep_flag_set((uint8_t)val);
			pars_set((pars_ctx_p)&product_pars);
		}
		else if(!strcmp(args[1], "pcan")) {
			product_en_pcan_out_flag_set((uint8_t)val);
			pars_set((pars_ctx_p)&product_pars);
		}
		else if(!strcmp(args[1], "fcw")) {
			product_en_radar_fcw_out_flag_set((uint8_t)val);
			pars_set((pars_ctx_p)&product_pars);
		}						
		else if(!strcmp(args[1], "date")) {
			product_pars.info.manufacture_date = strtoul(args[2], NULL, 16);
			pars_set((pars_ctx_p)&product_pars);
		}
	}
	else
		_product_pars_dump();
}

void product_cusid_set(uint16_t id)
{
	product_pars.info.customer = id;
	pars_set((pars_ctx_p)&product_pars);
}

void product_devid_set(uint16_t id)
{
	product_pars.info.device_id = id;
	tracking_device_id_reset();
	pars_set((pars_ctx_p)&product_pars);
}

void product_serial_no_get(uint8_t *sn)
{
	memcpy((void*)sn, (void*)&product_pars.info.serial_no[0], sizeof(product_pars.info.serial_no));
}

void product_serial_no_set(uint8_t *sn)
{
	memcpy((void*)&product_pars.info.serial_no[0], (void*)sn, sizeof(product_pars.info.serial_no));
	pars_set((pars_ctx_p)&product_pars);
}

void product_flags_set(uint8_t flags)
{	
	product_pars.info.flags = flags;
	pars_set((pars_ctx_p)&product_pars);

	product_dis_sleep_flag_set( (uint8_t) (flags & PROD_FLAG_SLEEP_DISABLE) );
	product_en_pcan_out_flag_set( (uint8_t) (flags & PROD_FLAG_PCAN_OUTPUT_ENABLE) );
	product_en_radar_fcw_out_flag_set( (uint8_t) (flags & PROD_FLAG_RADAR_FCW_OUTPUT_ENABLE) );	
}

void product_dis_sleep_flag_set(uint8_t disleep)
{	
	uint8_t flags;
	uint32_t ign_status = 0;
	uint32_t ign_val = 0;
	uint8_t sleepflag = 0;	
	flags = product_pars.info.flags;

	flags = (disleep != 0) ? (flags | PROD_FLAG_SLEEP_DISABLE) : (flags & (~PROD_FLAG_SLEEP_DISABLE));

	product_pars.info.flags = flags;
	pars_set((pars_ctx_p)&product_pars);

    
	if(FALSE == PROD_SLEEP_FLAG_SWITCH)
	{
		sleepflag = disleep;
	}
	else
	{
		sleepflag = (1 == disleep) ? 0 : 1;
	}

	//Disable sleep mode
	if(1 == sleepflag)
	{
		if( (CAN_DisRx_DisTx == cubtek_faw_did_ds_can_status_get()) 
			|| (CAN_EnRx_DisTx == cubtek_faw_did_ds_can_status_get()) ) 	
		{
			AppComTxRx_Start();
		}
	}
	else
	{
		ign_status = get_ign_status();
		ign_val = get_ign_value();

		if ( (VEH_STATUS_VALID == ign_status) || (VEH_STATUS_NOT_GET_DATA == ign_status) )
		{
			if (VEH_IGN_ON == ign_val)
			{
				if( (CAN_DisRx_DisTx == cubtek_faw_did_ds_can_status_get()) 
				|| (CAN_EnRx_DisTx == cubtek_faw_did_ds_can_status_get()) ) 					
				{
					AppComTxRx_Start();
				}
			}			
			else
			{
				if( CAN_EnRx_EnTx == cubtek_faw_did_ds_can_status_get() ) 	
				{
					AppCom_DisTx_EnRx();
				}
			}

		}		
	}
}

uint8_t product_dis_sleep_flag_get(void)
{	
	uint8_t flags;
	uint8_t rev;
	flags = product_pars.info.flags;

	if(FALSE == PROD_SLEEP_FLAG_SWITCH)
	{
		rev = ( (flags & PROD_FLAG_SLEEP_DISABLE) != 0) ? TRUE : FALSE;
	}
	else
	{
		rev = ( (flags & PROD_FLAG_SLEEP_DISABLE) != 0) ? FALSE : TRUE;
	}
	return rev;
}

void product_en_pcan_out_flag_set(uint8_t config)
{	
	uint8_t flags;
	flags = product_pars.info.flags;

	flags = (config != 0) ? (flags | PROD_FLAG_PCAN_OUTPUT_ENABLE) : (flags & (~PROD_FLAG_PCAN_OUTPUT_ENABLE));

	product_pars.info.flags = flags;
	pars_set((pars_ctx_p)&product_pars);
}

uint8_t product_en_pcan_out_flag_get(void)
{	
	uint8_t flags;
	uint8_t rev;
	flags = product_pars.info.flags;

	rev = ( (flags & PROD_FLAG_PCAN_OUTPUT_ENABLE) != 0) ? TRUE : FALSE;
	return rev;
}

void product_en_radar_fcw_out_flag_set(uint8_t config)
{	
	uint8_t flags;
	flags = product_pars.info.flags;

	flags = (config != 0) ? (flags | PROD_FLAG_RADAR_FCW_OUTPUT_ENABLE) : (flags & (~PROD_FLAG_RADAR_FCW_OUTPUT_ENABLE));

	product_pars.info.flags = flags;
	pars_set((pars_ctx_p)&product_pars);
}

uint8_t product_en_radar_fcw_out_flag_get(void)
{	
	uint8_t flags;
	uint8_t rev;
	flags = product_pars.info.flags;

	rev = ( (flags & PROD_FLAG_RADAR_FCW_OUTPUT_ENABLE) != 0) ? TRUE : FALSE;
	return rev;
}

void product_manufacture_date_set(uint32_t date)
{
	product_pars.info.manufacture_date = date;
	pars_set((pars_ctx_p)&product_pars);
}

void product_pars_set(void)
{
	pars_set((pars_ctx_p)&product_pars);
}

void product_init(void)
{
	static uint16_t inited = 0;
	HW_VER_E version = HW_INVALID;
	//PRINTF("prod: init %p\n",&product_pars.info);

	if(inited)
		return;

	memcpy(&product_pars, &product_default, sizeof(product_pars_t));

	pars_get((pars_ctx_p)&product_pars, _product_pars_dump, prod_info_in_jsons);

	version = get_hw_ver();

	switch(version)
	{
        case HW_93G003_COMBO_FRONT_RADAR_BV3p3:
            product_pars.info.product = PROD_ID_93G003_Combo_Front_Radar_BV3p3;
            break;
        case HW_93G014_MRR_BV1p0_FOR_HIRAIN:
            product_pars.info.product = PROD_ID_93G014_MRR_BV1_0_FOR_Hirain;
            break;
        case HW_93G003_COMBO_FRONT_RADAR_BV3p4:
            product_pars.info.product = PROD_ID_93G003_Combo_Front_Radar_BV3p4;
            break;
        case HW_93G014_MRR_BV2p1_FOR_HIRAIN:
            product_pars.info.product = PROD_ID_93G014_MRR_BV2p1_FOR_HIRAIN;
            break;
        case HW_93G016_MRR_BV2p1_FOR_HIRAIN_S32R264:
            product_pars.info.product = PROD_ID_93G016_MRR_BV2p1_FOR_HIRAIN_S32R264;
            break;
        default:
            break;
	}

	if(product_pars.info.product >= PROD_ID_INVALID || product_pars.info.customer >= CUSTOM_ID_INVALID ||
			strncmp((char*)product_pars.info.name, DEFAULT_PRODUCT_NAME,sizeof(product_pars.info.name))){

		memcpy(&product_pars, &product_default, sizeof(product_pars_t));
		pars_set((pars_ctx_p)&product_pars);
	}

	//IPC_SEND_MSG_Z70(MSG_PRODUCT_INFO, &product_pars.info, 0);
	console_command_reg("prod", _product_pars_tester);
	PRINTF("prod: inited(%p)\n", &product_pars.info);
	inited = 1;
}

const product_info_t* product_info_get(void)
{
	product_init();
	return &product_pars.info;
}

#else

static const product_info_t* prod = NULL;

void product_info_set(void* p)
{
	prod = (const product_info_t*)(pars_ctx_get(PROD_PARS_ID)->info);
	PRINTF("prod: info@%p\n",prod);
}

void product_init(void)
{
	pars_init_proc_reg(product_info_set, NULL, "meas");
}

const product_info_t* product_info_get(void)
{
	return prod;
}

#endif
