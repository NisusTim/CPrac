/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "sys_shared.h" /* include peripheral declarations */
/*******************************************************************************
* Constants and macros
*******************************************************************************/
#define MAX_MB_NUM 									96

#if defined(CTI_Z4_0)

#define PARS_VERSION_MAJOR				0x02
#define PARS_VERSION_MINOR				0x01
#define VERSION_OF_CAN_PARS    			(((uint16_t)PARS_VERSION_MAJOR<<8) | PARS_VERSION_MINOR)

can_parameters_t can_parameters = {
        .hdr = {
            .base = (uint32_t)&can_parameters,
            .version = VERSION_OF_CAN_PARS,
            .size = sizeof(can_parameters_t),
            .id=CAN_PARS_ID,
            .chksum = 0,
            .mask = 0,
        },
        .info = {
            .ide0 = CAN_IDE_STANDARD,
            .ide2 = CAN_IDE_STANDARD,
            .br0    = CAN_BR_500K,
            .br2    = CAN_BR_500K,
            .can0_dlc_enable = 0,
            .can2_dlc_enable = 0,
#if !defined(OPTION_CUSTOMER_ID)    /* Customer Hirain-FAW */
            .uds_physical_request = 0x7a0,
            .uds_physical_response = 0x7a8
#elif (OPTION_CUSTOMER_ID == 1)     /* Customer Neusoft */
            .uds_physical_request = 0x7b0,
            .uds_physical_response = 0x7b8
#elif (OPTION_CUSTOMER_ID == 3)     /* Customer Hirain-CNHTC */
            .uds_physical_request = 0x7a0,
            .uds_physical_response = 0x7a8
#elif (OPTION_CUSTOMER_ID == 4)     /* Customer TSINTEL-CNHTC */
            .uds_physical_request = 0x7c1,
            .uds_physical_response = 0x7c9
#else
            .uds_physical_request = 0x7a0,
            .uds_physical_response = 0x7a8
#endif
        }
};

static can_info_p can_pars = &can_parameters.info;

#ifdef USING_CUBTEK_CAN_0
typedef struct {
	uint32_t 				bus_off_cnt;
	uint8_t 				tBusOffSlow;
	uint8_t 				tBusOffQuick;
	timer_p 				bus_off_rec_timer;
}can_recovery_handle_t, *can_recovery_handle_p;

static can_recovery_handle_t can_rec_hld = {.bus_off_cnt = 0, .tBusOffQuick = 50, .tBusOffSlow = 200, .bus_off_rec_timer = NULL};
static can_recovery_handle_p can_rec_p = &can_rec_hld;
#endif

/*******************************************************************************
* Function prototypes
*******************************************************************************/
#ifdef USING_CUBTEK_CAN_0
void can_info_dump(void);
static void can0_bus_off_recorvry(int duration);
static void FlexCAN_0_Init();
#endif
static void FlexCAN_1_Init();
static void FlexCAN_2_Init();

#define JSON_CAN_INFO_IDE0 		"\t\t\"ide0\":{\"t\":\"u32\",\"o\":%d,\"v\":\%u},\n"
#define JSON_CAN_INFO_IDE2 		"\t\t\"ide2\":{\"t\":\"u32\",\"o\":%d,\"v\":%u},\n"
#define JSON_CAN_INFO_TXID 		"\t\t\"br0\":{\"t\":\"u32\",\"o\":%d,\"v\":%u},\n"
#define JSON_CAN_INFO_RXID 		"\t\t\"br2\":{\"t\":\"u32\",\"o\":%d,\"v\":%u},\n"
#define JSON_CAN_INFO_DLC0      "\t\t\"can0_dlc_enable\":{\"t\":\"u8\",\"o\":%d,\"v\":%u},\n"
#define JSON_CAN_INFO_DLC2      "\t\t\"can2_dlc_enable\":{\"t\":\"u8\",\"o\":%d,\"v\":%u},\n"
#define JSON_CAN_INFO_UDS_REQ 	"\t\t\"uds_physical_request\":{\"t\":\"u32\",\"o\":%d,\"v\":%ld},\n"
#define JSON_CAN_INFO_UDS_RESP	"\t\t\"uds_physical_response\":{\"t\":\"u32\",\"o\":%d,\"v\":%ld}\n"

static int can_info_in_jsons(char* ws)
{
	int cnt = 0;
	if(ws){
		cnt = sprintf(ws,"{\n");
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_ID, (char)(CAN_PARS_ID>>24),(char)(CAN_PARS_ID>>16),(char)(CAN_PARS_ID>>8),(char)(CAN_PARS_ID));
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_VERSION, can_parameters.hdr.version);
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_SIZE, can_parameters.hdr.size - sizeof(pars_header_t));

		cnt += sprintf(ws+cnt,"\t\"info\":{\n");
		cnt += sprintf(ws+cnt, JSON_CAN_INFO_IDE0, offsetof(can_info_t, ide0), can_pars->ide0);
		cnt += sprintf(ws+cnt, JSON_CAN_INFO_IDE2, offsetof(can_info_t, ide2), can_pars->ide2);
		cnt += sprintf(ws+cnt, JSON_CAN_INFO_TXID, offsetof(can_info_t, br0), can_pars->br0);
		cnt += sprintf(ws+cnt, JSON_CAN_INFO_RXID, offsetof(can_info_t, br2), can_pars->br2);
		cnt += sprintf(ws+cnt, JSON_CAN_INFO_DLC0, offsetof(can_info_t, can0_dlc_enable), can_pars->can0_dlc_enable);
		cnt += sprintf(ws+cnt, JSON_CAN_INFO_DLC2, offsetof(can_info_t, can2_dlc_enable), can_pars->can2_dlc_enable);
		cnt += sprintf(ws+cnt, JSON_CAN_INFO_UDS_REQ, offsetof(can_info_t, uds_physical_request), can_pars->uds_physical_request);
		cnt += sprintf(ws+cnt, JSON_CAN_INFO_UDS_RESP, offsetof(can_info_t, uds_physical_response), can_pars->uds_physical_response);
		cnt += sprintf(ws+cnt, "\t}\n}\n");
	}
	return cnt;
}

void can_info_dump(void)
{
	const char* ide[] = {"0:STARDAND","1:EXTENDED"};
	const char* br[] = {"0:1M","1:500K","2:250K","3:100K","4:FD(500K,2M)","5:FD(1M,2M)","6:FD(500K,4M)","7:FD(1M,4M)","8:FD(1M,8M)"};
	PRINTF("canp: show can parameters\n");
	PRINTF("ids= %s %s\n",ide[0],ide[1]);
	PRINTF("br= %s %s  %s %s  %s %s %s %s %s\n",br[0],br[1],br[2],br[3],br[4],br[5],br[6],br[7],br[8]);
	PRINTF("canp ide0: %s\n"	,ide[can_pars->ide0]);
	PRINTF("canp ide2: %s\n"	,ide[can_pars->ide2]);
	PRINTF("canp br0: %s\n"	, br[can_pars->br0]);
	PRINTF("canp br2: %s\n"	, br[can_pars->br2]);
	PRINTF("canp can0_dlc_enable: %d\n"	, can_pars->can0_dlc_enable);
	PRINTF("canp can2_dlc_enable: %d\n"	, can_pars->can2_dlc_enable);
	PRINTF("canp uds_request: 0x%lx\n"	, can_pars->uds_physical_request);
	PRINTF("canp uds_response: 0x%lx\n"	, can_pars->uds_physical_response);
}

void can_pars_info(char** args, int count)
{
	if (count > 2) {
		if(!strcmp(args[1], "ide0"))
		{
			int16_t ide = strtol(args[2], NULL, 10);
			if(ide < CAN_IDE_UNKNOWN && ide >= 0)
			{
				can_pars->ide0 = ide;
				pars_set((pars_ctx_p)&can_parameters);
			}
			else
			{
				PRINTF("can setting ide0 over range\n");
			}
		}
		else if(!strcmp(args[1], "ide2"))
		{
			int16_t ide = strtol(args[2], NULL, 10);
			if(ide < CAN_IDE_UNKNOWN && ide >= 0)
			{
				can_pars->ide2 = ide;
				pars_set((pars_ctx_p)&can_parameters);
			}
			else
			{
				PRINTF("can setting ide2 over range\n");
			}
		}
		else if(!strcmp(args[1], "br0"))
		{
			int16_t br = strtol(args[2], NULL, 10);
			if(br < CAN_BR_UNKNOWN && br >= 0)
			{
				can_pars->br0 = br;
				if(br < CAN_FD_500K_2M){
					can_pars->can0_dlc_enable=0;
				}
				pars_set((pars_ctx_p)&can_parameters);
			}
			else
			{
				PRINTF("can setting br0 over range\n");
			}
		}
		else if(!strcmp(args[1], "br2"))
		{
			int16_t br = strtol(args[2], NULL, 10);
			if(br < CAN_BR_UNKNOWN && br >= 0)
			{
				can_pars->br2 = br;
				if(br < CAN_FD_500K_2M){
					can_pars->can2_dlc_enable=0;
				}
				pars_set((pars_ctx_p)&can_parameters);
			}
			else
			{
				PRINTF("can setting br2 over range\n");
			}
		}
		else if(!strcmp(args[1], "can0_dlc_enable"))
		{
			int16_t can0_dlc_enable = strtol(args[2], NULL, 10);
			if(can0_dlc_enable ==0 || can0_dlc_enable == 1)
			{
				if(can_pars->br0 < CAN_FD_500K_2M){
					can0_dlc_enable=0;
				}
				can_pars->can0_dlc_enable = (uint8_t)can0_dlc_enable;
				pars_set((pars_ctx_p)&can_parameters);
			}
			else
			{
				PRINTF("can setting br2 over range\n");
			}
		}
		else if(!strcmp(args[1], "can2_dlc_enable"))
		{
			int16_t can2_dlc_enable = strtol(args[2], NULL, 10);
			if(can2_dlc_enable ==0 || can2_dlc_enable == 1)
			{
				if(can_pars->br2 < CAN_FD_500K_2M){
			        can2_dlc_enable=0;
			    }
				can_pars->can2_dlc_enable = (uint8_t)can2_dlc_enable;
				pars_set((pars_ctx_p)&can_parameters);
			}
			else
			{
				PRINTF("can setting br2 over range\n");
			}
		}
		else if(!strcmp(args[1], "uds_request"))
		{
			can_pars->uds_physical_request = strtol(args[2], NULL, 10);
			pars_set((pars_ctx_p)&can_parameters);
		}
		else if(!strcmp(args[1], "uds_response"))
		{
			can_pars->uds_physical_response = strtol(args[2], NULL, 10);
			pars_set((pars_ctx_p)&can_parameters);
		}
	}
	can_info_dump();
}

void set_can0_ide0_and_br0(int16_t ide ,int16_t br)
{
	if(ide != -1)
	{
		if(ide < CAN_IDE_UNKNOWN && ide >= 0)
		{
			can_pars->ide0 = ide;
		}
	}
	if(br != -1)
	{
		if(br < CAN_BR_UNKNOWN && br >= 0)
		{
			can_pars->br0 = br;
		}
	}
	pars_set((pars_ctx_p)&can_parameters);
#ifdef USING_CUBTEK_CAN_0
	FlexCAN_0_Init();
#endif
}

void set_can2_ide2_and_br2(int16_t ide ,int16_t br)
{
	if(ide != -1)
	{
		if(ide < CAN_IDE_UNKNOWN && ide >= 0)
		{
			can_pars->ide2 = ide;
		}
	}
	if(br != -1)
	{
		if(br < CAN_BR_UNKNOWN && br >= 0)
		{
			can_pars->br2 = br;
		}
	}
	pars_set((pars_ctx_p)&can_parameters);
	FlexCAN_2_Init();
}

int16_t get_can0_br0(void)
{
	return can_pars->br0;
}

void can_init()
{
	HW_VER_E hw_ver;
	hw_ver = get_hw_ver();

	pars_get((pars_ctx_p)&can_parameters, can_info_dump, can_info_in_jsons);

	can_api_init();

	if(HW_DUAL_BOARD == hw_ver)
	{
#ifdef USING_CUBTEK_CAN_0
		FlexCAN_0_Init();
		FlexCAN_1_Init();

		INTC.PSR[VECTOR_521].R = 0x8001; //set CAN 0 Busoff interrupt core and priority
		INTC.PSR[VECTOR_522].R = 0x8001; //set CAN 0 RX MB00-03 interrupt core and priority //	4	Core0 RX
		INTC.PSR[VECTOR_523].R = 0x8001; //set CAN 0 RX MB04-07 interrupt core and priority //	4	Core0 RX
		INTC.PSR[VECTOR_524].R = 0x8001; //set CAN 0 RX MB08-11 interrupt core and priority //	4	Core0 RX
		INTC.PSR[VECTOR_525].R = 0x8001; //set CAN 0 RX MB12-15 interrupt core and priority //	4	Core0 TX - continuous data
//			INTC.PSR[VECTOR_526].R = 0x8001; //set CAN 0 RX MB16-31 interrupt core and priority //	16	Core0 TX - discrete data

		if(can_pars->can0_dlc_enable==1){
			INTC.PSR[VECTOR_531].R = 0x8001; //set CAN 2 TX MB64-79 interrupt core and priority //16	CoreX TX - continuous data
		//  INTC.PSR[VECTOR_532].R = 0x8001; //set CAN 2 TX MB80-95 interrupt core and priority //16	CoreX TX - continuous data
		}
		console_command_reg("can", can_tester);
		console_command_reg("canp", can_pars_info);
#endif
	}
	else
	{
#ifdef USING_CUBTEK_CAN_0
		FlexCAN_0_Init();
		FlexCAN_1_Init();
		FlexCAN_2_Init();

		INTC.PSR[VECTOR_521].R = 0x8001; //set CAN 0 Busoff interrupt core and priority
		INTC.PSR[VECTOR_522].R = 0x8001; //set CAN 0 RX MB00-03 interrupt core and priority //	4	Core0 RX
		INTC.PSR[VECTOR_523].R = 0x8001; //set CAN 0 RX MB04-07 interrupt core and priority //	4	Core0 RX
		INTC.PSR[VECTOR_524].R = 0x8001; //set CAN 0 RX MB08-11 interrupt core and priority //	4	Core0 RX
		INTC.PSR[VECTOR_525].R = 0x8001; //set CAN 0 RX MB12-15 interrupt core and priority //	4	Core0 TX - continuous data
//			INTC.PSR[VECTOR_526].R = 0x8001; //set CAN 0 RX MB16-31 interrupt core and priority //	16	Core0 TX - discrete data
		if(can_pars->can0_dlc_enable==1){
			 INTC.PSR[VECTOR_531].R = 0x8001; //set CAN 2 TX MB64-79 interrupt core and priority //16	CoreX TX - continuous data
		//   INTC.PSR[VECTOR_532].R = 0x8001; //set CAN 2 TX MB80-95 interrupt core and priority //16	CoreX TX - continuous data
		}

		INTC.PSR[VECTOR_548].R = 0x8001; //set CAN 2 RX MB00-03 interrupt core and priority //	4	Core0 RX
		INTC.PSR[VECTOR_549].R = 0x8001; //set CAN 2 RX MB04-07 interrupt core and priority //	4	Core0 RX
		INTC.PSR[VECTOR_550].R = 0x8001; //set CAN 2 RX MB08-11 interrupt core and priority //	4	Core0 RX
		INTC.PSR[VECTOR_551].R = 0x8001; //set CAN 2 RX MB12-15 interrupt core and priority //	4	Core0 TX - continuous data
//			INTC.PSR[VECTOR_552].R = 0x8001; //set CAN 2 RX MB16-31 interrupt core and priority //	16	Core0 TX - discrete data
	    if(can_pars->can2_dlc_enable==1){
	        INTC.PSR[VECTOR_557].R = 0x8001; //set CAN 2 TX MB64-79 interrupt core and priority //16	CoreX TX - continuous data
	//      INTC.PSR[VECTOR_558].R = 0x8001; //set CAN 2 TX MB80-95 interrupt core and priority //16	CoreX TX - continuous data
	    }

		console_command_reg("can", can_tester);
		console_command_reg("can2", can2_tester);
		console_command_reg("canp", can_pars_info);
#else
		FlexCAN_1_Init();
		FlexCAN_2_Init();

		INTC.PSR[521].R = 0x8001;
		INTC.PSR[522].R = 0x8001;
		INTC.PSR[523].R = 0x8001;
		INTC.PSR[524].R = 0x8001;
		INTC.PSR[525].R = 0x8001;
		INTC.PSR[526].R = 0x8001;
		INTC.PSR[527].R = 0x8001;
		INTC.PSR[528].R = 0x8001;
		INTC.PSR[529].R = 0x8001;
		INTC.PSR[530].R = 0x8001;
		INTC.PSR[531].R = 0x8001;
		INTC.PSR[532].R = 0x8001;

		INTC.PSR[VECTOR_548].R = 0x8001; //set CAN 2 RX MB00-03 interrupt core and priority //	4	Core0 RX
		INTC.PSR[VECTOR_549].R = 0x8001; //set CAN 2 RX MB04-07 interrupt core and priority //	4	Core0 RX
		INTC.PSR[VECTOR_550].R = 0x8001; //set CAN 2 RX MB08-11 interrupt core and priority //	4	Core0 RX
		INTC.PSR[VECTOR_551].R = 0x8001; //set CAN 2 RX MB12-15 interrupt core and priority //	4	Core0 TX - continuous data
//			INTC.PSR[VECTOR_552].R = 0x8001; //set CAN 2 RX MB16-31 interrupt core and priority //	16	Core0 TX - discrete data
		if(can_pars->can2_dlc_enable==1){
			INTC.PSR[VECTOR_557].R = 0x8001; //set CAN 2 TX MB64-79 interrupt core and priority //16	CoreX TX - continuous data
			INTC.PSR[VECTOR_558].R = 0x8001; //set CAN 2 TX MB80-95 interrupt core and priority //16	CoreX TX - continuous data
		}

		console_command_reg("can2", can2_tester);
		console_command_reg("canp", can_pars_info);
#endif
	}
}


#ifdef USING_CUBTEK_CAN_0
/******************************************************************************
Function Name : FlexCAN_0_Init
Engineer      : Martin Kovar
Date          : Feb-18-2016
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : FlexCAN_0 basic initialization
Issues        : NONE
******************************************************************************/
static void FlexCAN_0_Init()
{
	static uint8_t rx_mask_inited = FALSE;
	int i = 0;
	uint8_t br[] = {CAN_BR_REG_VAL_1M, CAN_BR_REG_VAL_500K, CAN_BR_REG_VAL_250K, CAN_BR_REG_VAL_100K};

	/*Module enable*/
	CAN_0.MCR.B.MDIS = 0;

	CAN_0.MCR.B.FRZ = 1;
	CAN_0.MCR.B.HALT = 1;

	while (!CAN_0.MCR.B.FRZACK) {}/* Wait for freeze acknowledge to set */

	/*Self reception disabled*/
	CAN_0.MCR.B.SRXDIS = 1;

	CAN_0.MCR.B.MAXMB = MAX_MB_NUM-1;

	/*Bus off interrupt enable*/
	CAN_0.CTRL1.B.BOFFMSK = 1;

	/*Automatic recovering from Bus Off state disabled*/
	CAN_0.CTRL1.B.BOFFREC = 1;

	/*Source clk is oscillator clock (40MHz)*/
	CAN_0.CTRL1.B.CLKSRC = 0;

	/*Error correction configuration register enable*/
	CAN_0.CTRL2.B.ECRWRE = 1;

	/*Enable unrestricted write access to FlexCAN memory*/
	CAN_0.CTRL2.B.WRMFRZ = 1;

	/*Error configuration register write enable*/
	CAN_0.MECR.B.ECRWRDIS = 0;

	/*Disable memory error correction*/
	CAN_0.MECR.B.ECCDIS = 1;

	/*Keep normal operation*/
	CAN_0.MECR.B.NCEFAFRZ = 0;

	/*Error configuration register write disable*/
	CAN_0.MECR.B.ECRWRDIS = 1;

	/*Disable unrestricted write access to FlexCAN memory*/
	CAN_0.CTRL2.B.WRMFRZ = 0;

	/*Error correction configuration register disable*/
	CAN_0.CTRL2.B.ECRWRE = 0;

	/*Enable individual RX masking*/
	CAN_0.MCR.B.IRMQ = 1;

    if(can_pars->br0<4)
    {
    	/*CAN bit timing - 40MHz oscillator, 100kbps bitrate,*/ //yilin assume 100k->39, 200k->19, 400k->9 500k->7
    	CAN_0.CTRL1.B.PRESDIV = br[can_pars->br0];
    	//Sample Rate 80.00%
    	CAN_0.CTRL1.B.RJW = 3;
    	CAN_0.CTRL1.B.PSEG1 = 1;
    	CAN_0.CTRL1.B.PSEG2 = 1;
    	CAN_0.CTRL1.B.PROPSEG = 4;
    }
    else
    {
        CAN_0.MCR.B.FDEN=1;
        CAN_0.MCR.B.AEN=1;
        CAN_0.CTRL2.B.STFCNTEN=1;   //ISOCANFDEN=1; S32R274_RM_Rev3-NDA.pdf page 2401
	    CAN_0.FDCTRL.B.FDRATE=1;
	    CAN_0.FDCTRL.B.TDCEN=1;

	    switch(can_pars->br0)
	    {
	        case CAN_FD_500K_2M:
	            CAN_0.FDCTRL.B.TDCEN=0;
	            CAN_0.CBT.B.BTF=1;
	            CAN_0.CBT.B.EPRESDIV=1;
	            CAN_0.CBT.B.ERJW=9;
	            CAN_0.CBT.B.EPROPSEG=10;
	            CAN_0.CBT.B.EPSEG1=17;
	            CAN_0.CBT.B.EPSEG2=9;
	            CAN_0.FDCBT.B.FPRESDIV = 1;
	            CAN_0.FDCBT.B.FRJW = 1;
	            CAN_0.FDCBT.B.FPROPSEG = 6;
	            CAN_0.FDCBT.B.FPSEG1 = 0;
	            CAN_0.FDCBT.B.FPSEG2 = 1;
	        break;

	        case CAN_FD_500K_4M:
	        	CAN_0.FDCTRL.B.TDCOFF=7;
	        	CAN_0.CBT.B.BTF=1;
	        	CAN_0.CBT.B.EPRESDIV=1;
	        	CAN_0.CBT.B.ERJW=1;
	        	CAN_0.CBT.B.EPROPSEG=16;
	        	CAN_0.CBT.B.EPSEG1=9;
	        	CAN_0.CBT.B.EPSEG2=11;
	        	CAN_0.FDCBT.B.FPRESDIV = 1;
	        	CAN_0.FDCBT.B.FRJW = 1;
	        	CAN_0.FDCBT.B.FPROPSEG = 0;
	        	CAN_0.FDCBT.B.FPSEG1 = 1;
	        	CAN_0.FDCBT.B.FPSEG2 = 1;
	        break;

	        case CAN_FD_1M_2M:
	            CAN_0.FDCTRL.B.TDCEN=0;
	            CAN_0.CBT.B.BTF=1;
	            CAN_0.CBT.B.EPRESDIV=0;
	            CAN_0.CBT.B.ERJW=9;
	            CAN_0.CBT.B.EPROPSEG=20;
	            CAN_0.CBT.B.EPSEG1=7;
	            CAN_0.CBT.B.EPSEG2=9;
	            CAN_0.FDCBT.B.FPRESDIV = 0;
	            CAN_0.FDCBT.B.FRJW = 4;
	            CAN_0.FDCBT.B.FPROPSEG = 11;
	            CAN_0.FDCBT.B.FPSEG1 = 2;
	            CAN_0.FDCBT.B.FPSEG2 = 4;
	        break;

	        case CAN_FD_1M_4M:
	            CAN_0.FDCTRL.B.TDCOFF=7;
	            CAN_0.CBT.B.BTF=1;
	            CAN_0.CBT.B.EPRESDIV=0;
	            CAN_0.CBT.B.ERJW=9;
	            CAN_0.CBT.B.EPROPSEG=20;
	            CAN_0.CBT.B.EPSEG1=7;
	            CAN_0.CBT.B.EPSEG2=9;
	            CAN_0.FDCBT.B.FPRESDIV = 0;
	            CAN_0.FDCBT.B.FRJW = 1;
	            CAN_0.FDCBT.B.FPROPSEG = 3;
	            CAN_0.FDCBT.B.FPSEG1 = 3;
	            CAN_0.FDCBT.B.FPSEG2 = 1;
	        break;
	         case CAN_FD_1M_8M:
	            CAN_0.CTRL2.B.TASD= 23;
	            CAN_0.FDCTRL.B.TDCOFF=3;
	            CAN_0.CBT.B.BTF=1;
	            CAN_0.CBT.B.EPRESDIV=0;
	            CAN_0.CBT.B.ERJW=1;
	            CAN_0.CBT.B.EPSEG1=9;
	            CAN_0.CBT.B.EPSEG2=11;
	            CAN_0.CBT.B.EPROPSEG=16;
	            CAN_0.FDCBT.B.FPRESDIV = 0;
	            CAN_0.FDCBT.B.FRJW = 1;
	            CAN_0.FDCBT.B.FPSEG1 = 1;
	            CAN_0.FDCBT.B.FPSEG2 = 1;
	            CAN_0.FDCBT.B.FPROPSEG = 0;
	         break;
	    }
    }

    CAN_0.CTRL1.B.LPB = 0;		//Disable Loop-Back Mode

	/*enable interrupt for MB0~MB15*/
	CAN_0.IMASK1.R = 0xFFFF;
	if(can_pars->can0_dlc_enable==1){
        CAN_0.IMASK3.R = 0x007F;
        CAN_0.FDCTRL.B.MBDSR2 = 0x3; 	/* MB Region 2 Uses 64 Bytes per MB for data messages */
    }

	if(FALSE == rx_mask_inited)
	{
		/*Clear all RX individual Mask Registers The corresponding bit in the
				 * filter is checked*/
		for(i = 0; i < MAX_MB_NUM; i++)
		{
			CAN_0.RXIMR[i].R = 0xFFFFFFFF;
		}

		/*Set all message buffers RX inactive*/
		for(i = 0; i < MAX_MB_NUM; i++)
		{
			CAN_0.MB[i].CS.R = 0x0000;
		}

		rx_mask_inited = TRUE;
	}

//	CAN_0.RXMGMASK.R = 0x00000000;
	CAN_0.MCR.B.FRZ = 0;

	/*No freeze mode request*/
	CAN_0.MCR.B.HALT = 0;

	while (CAN_0.MCR.B.FRZACK & CAN_0.MCR.B.NOTRDY) {} /* Wait to clear */
			/* Good practice: wait for FRZACK on freeze mode entry/exit */
}
#endif

#ifdef USING_CUBTEK_CAN_0
void CAN0_BusoffInit(void)
{
	FlexCAN_0_Init();
}
#endif

void CAN0_BusoffRecovery(void)
{
	//3) Resume to normal CAN communication.
	CAN_0.CTRL1.B.BOFFREC = 0; 	//Automatic recovering from Bus Off state enable
}

unsigned char CAN0_GetFltconf(void)
{
	uint8_t st;
	st = CAN_0.ESR1.B.FLTCONF;
	return st;
	/*
	if(st == 0)
	{
		return CAN_ST_ERROR_ACTIVE;
	}
	else if(st == 1)
	{
		return CAN_ST_ERROR_PASSIVE;
	}
	else
	{
		return CAN_ST_BUS_OFF;
	}*/
}

unsigned char CAN0_GetTxErrCnt(void)
{
	uint8_t cnt;
	cnt = CAN_0.ECR.B.TXERRCNT;
	return cnt;
}

unsigned char CAN0_GetRxErrCnt(void)
{
	uint8_t cnt;
	cnt = CAN_0.ECR.B.RXERRCNT;
	return cnt;
}
/******************************************************************************
Function Name : FlexCAN_1_Init
Engineer      : Martin Kovar
Date          : Feb-18-2016
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : FlexCAN_1 basic initialization
Issues        : NONE
******************************************************************************/
static void FlexCAN_1_Init()
{
	/*Module enable*/
	CAN_1.MCR.B.MDIS = 0;
}

/******************************************************************************
Function Name : FlexCAN_2_Init
Engineer      : Cherry Yeh
Date          : Oct-26-2017
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : FlexCAN_2 basic initialization
Issues        : NONE
******************************************************************************/
static void FlexCAN_2_Init()
{
	static uint8_t rx_mask_inited = FALSE;
	int i = 0;
	uint8_t br[] = {CAN_BR_REG_VAL_1M, CAN_BR_REG_VAL_500K, CAN_BR_REG_VAL_250K, CAN_BR_REG_VAL_100K};
	/*Module enable*/
	CAN_2.MCR.B.MDIS = 0;

	CAN_2.MCR.B.FRZ = 1;
	CAN_2.MCR.B.HALT = 1;

	while (!CAN_2.MCR.B.FRZACK) {}/* Wait for freeze acknowledge to set */

	/*Self reception disabled*/
	CAN_2.MCR.B.SRXDIS = 1;

    CAN_2.MCR.B.MAXMB = MAX_MB_NUM-1;

	/*Source clk is oscillator clock (40MHz)*/
	CAN_2.CTRL1.B.CLKSRC = 0;

	/*Error correction configuration register enable*/
	CAN_2.CTRL2.B.ECRWRE = 1;

	/*Enable unrestricted write access to FlexCAN memory*/
	CAN_2.CTRL2.B.WRMFRZ = 1;

	/*Error configuration register write enable*/
	CAN_2.MECR.B.ECRWRDIS = 0;

	/*Disable memory error correction*/
	CAN_2.MECR.B.ECCDIS = 1;

	/*Keep normal operation*/
	CAN_2.MECR.B.NCEFAFRZ = 0;

	/*Error configuration register write disable*/
	CAN_2.MECR.B.ECRWRDIS = 1;

	/*Disable unrestricted write access to FlexCAN memory*/
	CAN_2.CTRL2.B.WRMFRZ = 0;

	/*Error correction configuration register disable*/
	CAN_2.CTRL2.B.ECRWRE = 0;

	/*Enable individual RX masking*/
	CAN_2.MCR.B.IRMQ = 1;

    if(can_pars->br2<4)
    {
	    /*CAN bit timing - 40MHz oscillator, 100kbps bitrate,*/ //yilin assume 100k->39, 200k->19, 400k->9 500k->7
	    CAN_2.CTRL1.B.PRESDIV = br[can_pars->br2];
	    CAN_2.CTRL1.B.RJW = 3;
	    CAN_2.CTRL1.B.PSEG1 = 1;
	    CAN_2.CTRL1.B.PSEG2 = 1;
	    CAN_2.CTRL1.B.PROPSEG = 4;
	}
	else
	{
	    CAN_2.MCR.B.FDEN=1;
        CAN_2.MCR.B.AEN=1;
        CAN_2.CTRL2.B.STFCNTEN=1;   //ISOCANFDEN=1; S32R274_RM_Rev3-NDA.pdf page 2401
	    CAN_2.FDCTRL.B.FDRATE=1;
	    CAN_2.FDCTRL.B.TDCEN=1;

	    switch(can_pars->br2)
	    {
	        case CAN_FD_500K_2M:
	            CAN_2.FDCTRL.B.TDCEN=0;
	            CAN_2.CBT.B.BTF=1;
	            CAN_2.CBT.B.EPRESDIV=1;
	            CAN_2.CBT.B.ERJW=9;
	            CAN_2.CBT.B.EPROPSEG=10;
	            CAN_2.CBT.B.EPSEG1=17;
	            CAN_2.CBT.B.EPSEG2=9;
	            CAN_2.FDCBT.B.FPRESDIV = 1;
	            CAN_2.FDCBT.B.FRJW = 1;
	            CAN_2.FDCBT.B.FPROPSEG = 6;
	            CAN_2.FDCBT.B.FPSEG1 = 0;
	            CAN_2.FDCBT.B.FPSEG2 = 1;
	        break;

	        case CAN_FD_500K_4M:
                CAN_2.FDCTRL.B.TDCOFF=5;
	            CAN_2.CBT.B.BTF=1;
	            CAN_2.CBT.B.EPRESDIV=1;
	            CAN_2.CBT.B.ERJW=9;
	            CAN_2.CBT.B.EPROPSEG=10;
	            CAN_2.CBT.B.EPSEG1=17;
	            CAN_2.CBT.B.EPSEG2=9;
	            CAN_2.FDCBT.B.FPRESDIV = 1;
	            CAN_2.FDCBT.B.FRJW = 0;
	            CAN_2.FDCBT.B.FPROPSEG = 1;
	            CAN_2.FDCBT.B.FPSEG1 = 0;
	            CAN_2.FDCBT.B.FPSEG2 = 1;
	         break;

	        case CAN_FD_1M_2M:
	            CAN_2.FDCTRL.B.TDCEN=0;
	            CAN_2.CBT.B.BTF=1;
	            CAN_2.CBT.B.EPRESDIV=0;
	            CAN_2.CBT.B.ERJW=9;
	            CAN_2.CBT.B.EPROPSEG=20;
	            CAN_2.CBT.B.EPSEG1=7;
	            CAN_2.CBT.B.EPSEG2=9;
	            CAN_2.FDCBT.B.FPRESDIV = 0;
	            CAN_2.FDCBT.B.FRJW = 4;
	            CAN_2.FDCBT.B.FPROPSEG = 11;
	            CAN_2.FDCBT.B.FPSEG1 =2;
	            CAN_2.FDCBT.B.FPSEG2 = 4;
            break;

	        case CAN_FD_1M_4M:
                CAN_2.FDCTRL.B.TDCOFF=5;
	            CAN_2.CBT.B.BTF=1;
	            CAN_2.CBT.B.EPRESDIV=0;
	            CAN_2.CBT.B.ERJW=9;
	            CAN_2.CBT.B.EPROPSEG=21;
	            CAN_2.CBT.B.EPSEG1=6;
	            CAN_2.CBT.B.EPSEG2=9;
	            CAN_2.FDCBT.B.FPRESDIV = 0;
	            CAN_2.FDCBT.B.FRJW = 1;
	            CAN_2.FDCBT.B.FPROPSEG = 3;
	            CAN_2.FDCBT.B.FPSEG1 = 3;
	            CAN_2.FDCBT.B.FPSEG2 = 1;
	         break;

	         case CAN_FD_1M_8M:
	            CAN_2.CTRL2.B.TASD= 23;
	            CAN_2.FDCTRL.B.TDCOFF=3;
	            CAN_2.CBT.B.BTF=1;
	            CAN_2.CBT.B.EPRESDIV=0;
	            CAN_2.CBT.B.ERJW=1;
	            CAN_2.CBT.B.EPSEG1=9;
	            CAN_2.CBT.B.EPSEG2=11;
	            CAN_2.CBT.B.EPROPSEG=16;
	            CAN_2.FDCBT.B.FPRESDIV = 0;
	            CAN_2.FDCBT.B.FRJW = 1;
	            CAN_2.FDCBT.B.FPSEG1 = 1;
	            CAN_2.FDCBT.B.FPSEG2 = 1;
	            CAN_2.FDCBT.B.FPROPSEG = 0;
	         break;

	         default:
	         break;
	    }
    }

	CAN_2.CTRL1.B.LPB = 0;		//Disable Loop-Back Mode

	/*enable interrupt for MB0~MB15*/
	CAN_2.IMASK1.R = 0xFFFF;
    if(can_pars->can2_dlc_enable==1){
        CAN_2.IMASK3.R = 0x007F;
        CAN_2.FDCTRL.B.MBDSR2 = 0x3; 	/* MB Region 2 Uses 64 Bytes per MB for data messages */
    }

	if(FALSE == rx_mask_inited)
	{
		/*Clear all RX individual Mask Registers The corresponding bit in the
				 * filter is checked*/
		for(i = 0; i < MAX_MB_NUM; i++)
		{
			CAN_2.RXIMR[i].R = 0xFFFFFFFF;
		}

		/*Set all message buffers RX inactive*/
		for(i = 0; i < MAX_MB_NUM; i++)
		{
			CAN_2.MB[i].CS.R = 0x0000;
		}
		rx_mask_inited = TRUE;
	}

//	CAN_2.RXMGMASK.R = 0x00000000;
	CAN_2.MCR.B.FRZ = 0;

	/*No freeze mode request*/
	CAN_2.MCR.B.HALT = 0;

	while (CAN_2.MCR.B.FRZACK & CAN_2.MCR.B.NOTRDY) {} /* Wait to clear */
			/* Good practice: wait for FRZACK on freeze mode entry/exit */
}

#ifdef USING_CUBTEK_CAN_0
static void can0_bus_off_recorvry(int duration)
{
	can_rec_p->bus_off_rec_timer = timer_set("can0boffrec", duration, 1, (event_proc_p)can_0_boff_rec, NULL);
}

void CAN_0_Bus_Off_Rec_InterruptHandler()
{



	int duration = 1;

	if(CAN_0.ESR1.B.BOFFINT)
	{
		CAN_0.ESR1.B.BOFFINT = 1;
		//1) Re-initialize the CAN protocol chip immediately;
		FlexCAN_0_Init();

		//2) Pause the transmission of messages before tBusOffQuick or tBusOffSlow is expired, respectively related to quick recovery and slow recovery;
		CAN_0.CTRL1.B.BOFFREC = 1; 	//Automatic recovering from Bus Off state disabled

		if(NULL == can_rec_p->bus_off_rec_timer)
		{
			if(can_rec_p->bus_off_cnt < 5)
			{
				duration = 1000/*ms*/ / can_rec_p->tBusOffQuick;
			}
			else
			{
				duration = 1000/*ms*/ / can_rec_p->tBusOffSlow;
			}

			put_event("can0_boff_rec", (event_proc_p)can0_bus_off_recorvry, (void*)duration);
		}
	}

}
#endif

#ifdef USING_CUBTEK_CAN_0
void can_0_boff_rec(uint32_t d)
{
	//3) Resume to normal CAN communication.
	CAN_0.CTRL1.B.BOFFREC = 0; 	//Automatic recovering from Bus Off state enable
//	time_reset();
	can_rec_p->bus_off_cnt++;
}


uint8_t get_can0_ide(void)
{
	return (uint8_t)can_pars->ide0;
}

uint8_t get_can0_br(void)
{
	return (uint8_t)can_pars->br0;
}

#endif

uint8_t get_can2_ide(void)
{
	return (uint8_t)can_pars->ide2;
}

uint8_t get_can2_br(void)
{
	return (uint8_t)can_pars->br2;
}

uint32_t get_uds_physical_request(void)
{
	return can_pars->uds_physical_request;
}

uint32_t get_uds_physical_response(void)
{
	return can_pars->uds_physical_response;
}
void set_uds_physical_request(uint32_t canid)
{
	can_pars->uds_physical_request = canid;
}

void set_uds_physical_response(uint32_t canid)
{
	can_pars->uds_physical_response = canid;
}

void can_info_pars_save(void)
{
	pars_set((pars_ctx_p)&can_parameters);
}

void can_info_pars_save_handler(void)
{
	put_event("can_pars_save", (event_proc_p)can_info_pars_save, NULL);
}

#ifdef USING_CUBTEK_CAN_0
void set_can0_br_dlc(uint8_t br, uint8_t dlc_enable)
{
    uint8_t br_temp,dlc_temp;
    
	if(br < CAN_BR_UNKNOWN && dlc_enable<=1 ){
	    br_temp=can_pars->br0;
	    dlc_temp=can_pars->can0_dlc_enable;
	    
		can_pars->br0 = br;
		if((br >=CAN_FD_500K_2M)&&(dlc_enable==1)){
		    can_pars->can0_dlc_enable = 1;
        }else{
            can_pars->can0_dlc_enable = 0;
        }		    
        
        if((br_temp!=can_pars->br0)||(dlc_temp!=can_pars->can0_dlc_enable)){
            pars_set((pars_ctx_p)&can_parameters);
        }
	}
}
#endif

void set_can2_br_dlc(uint8_t br, uint8_t dlc_enable)
{
	uint8_t br_temp,dlc_temp;
    
	if(br < CAN_BR_UNKNOWN && dlc_enable<=1 ){
	    br_temp=can_pars->br2;
	    dlc_temp=can_pars->can2_dlc_enable;
	    
		can_pars->br2 = br;
		if((br >=CAN_FD_500K_2M)&&(dlc_enable==1)){
		    can_pars->can2_dlc_enable = 1;
        }else{
            can_pars->can2_dlc_enable = 0;
        }		    
        
        if((br_temp!=can_pars->br2)||(dlc_temp!=can_pars->can2_dlc_enable)){
            pars_set((pars_ctx_p)&can_parameters);
        }
	}
}

#elif defined(CTI_Z7_0)||defined(CTI_Z7_1)
static can_info_t canp;
static can_info_p can_pars = &canp;

#endif

#ifdef USING_CUBTEK_CAN_0
void SettingCAN_0_MailBoxCanId(uint8_t idx, vuint32_t canid, vuint32_t mask)
{
	CAN_0.MB[idx].CS.B.CODE = 0x0;          	//MB inactive

	if(mask != 0xFFFFFFFF)
	{
		CAN_0.MCR.B.FRZ = 1;
		CAN_0.MCR.B.HALT = 1;

		while (!CAN_0.MCR.B.FRZACK) {}/* Wait for freeze acknowledge to set */

		CAN_0.RXIMR[idx].R = mask << 18;

		/*No freeze mode request*/
		CAN_0.MCR.B.HALT = 0;

		while (CAN_0.MCR.B.FRZACK & CAN_0.MCR.B.NOTRDY) {} /* Wait to exit freeze mode */
	}

	if(can_pars->ide0 == CAN_IDE_EXTENDED)
	{
		CAN_0.MB[idx].CS.B.IDE = 1;					//extended bit enable
		CAN_0.MB[idx].ID.R = canid;
	}
	else
	{
		CAN_0.MB[idx].CS.B.IDE = 0;					//extended bit disable
		CAN_0.MB[idx].ID.B.ID_STD = canid;
	}

	CAN_0.MB[idx].DATA.W[1] = 0x00000000;		//data1 set (optional)
	CAN_0.MB[idx].DATA.W[0] = 0x00000000;		//data0 set (optional)
	CAN_0.MB[idx].CS.B.DLC = 8;			  		//message length 8 bytes
	CAN_0.MB[idx].CS.B.RTR = 0;			  		//remote frame disable

	CAN_0.MB[idx].CS.B.CODE = 0x4;				//MB empty - ready for receive
}
#endif

void SettingCAN_2_MailBoxCanId(uint8_t idx, vuint32_t canid, vuint32_t mask)
{
	CAN_2.MB[idx].CS.B.CODE = 0x0;          	//MB inactive

	if(mask != 0xFFFFFFFF)
	{
		CAN_2.MCR.B.FRZ = 1;
		CAN_2.MCR.B.HALT = 1;

		while (!CAN_2.MCR.B.FRZACK) {}/* Wait for freeze acknowledge to set */

		CAN_2.RXIMR[idx].R = mask << 18;

		/*No freeze mode request*/
		CAN_2.MCR.B.HALT = 0;

		while (CAN_2.MCR.B.FRZACK & CAN_2.MCR.B.NOTRDY) {} /* Wait to exit freeze mode */
	}

	if(can_pars->ide2 == CAN_IDE_EXTENDED)
	{
		CAN_2.MB[idx].CS.B.IDE = 1;					//extended bit enable
		CAN_2.MB[idx].ID.R = canid;
	}
	else
	{
		CAN_2.MB[idx].CS.B.IDE = 0;					//extended bit disable
		CAN_2.MB[idx].ID.B.ID_STD = canid;
	}

	CAN_2.MB[idx].DATA.W[1] = 0x00000000;		//data1 set (optional)
	CAN_2.MB[idx].DATA.W[0] = 0x00000000;		//data0 set (optional)
	CAN_2.MB[idx].CS.B.DLC = 8;			  		//message length 8 bytes
	CAN_2.MB[idx].CS.B.RTR = 0;			  		//remote frame disable

	CAN_2.MB[idx].CS.B.CODE = 0x4;				//MB empty - ready for receive
}


uint8_t CAN0_GetMBSt(uint8_t mb)
{
    uint8_t st;
    if(mb<RAM_BLOCK2_START_MB){
        st = CAN_0.MB[mb].CS.B.CODE;
    }else{
        st = CAN_0_DLC.MB[mb-RAM_BLOCK2_START_MB].CS.B.CODE;
    }
    return st;
}

uint8_t CAN2_GetMBSt(uint8_t mb)
{
    uint8_t st;
    if(mb<RAM_BLOCK2_START_MB){
        st = CAN_2.MB[mb].CS.B.CODE;
    }else{
        st = CAN_2_DLC.MB[mb-RAM_BLOCK2_START_MB].CS.B.CODE;
    }
    return st;
}

#ifdef USING_CUBTEK_CAN_0
uint8_t get_can0_dlc_status(void)
{
    return can_pars->can0_dlc_enable;
}
#endif

uint8_t get_can2_dlc_status(void)
{
    return can_pars->can2_dlc_enable;
}

