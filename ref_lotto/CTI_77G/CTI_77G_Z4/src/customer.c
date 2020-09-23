/*
 * vehicle.c
 *
 *  Created on: Feb 4, 2018
 *      Author: erichu
 */

#include "sys_shared.h" /* include peripheral declarations */
#include "can_cubtek.h"

static const char* customer_name[]={"Hirain-FAW", "Neusoft", "AM", "Hirain-CNHTC", "TSINTEL"};
static HW_VER_E version = HW_INVALID;

typedef struct {
    char    project_code[8];    //7
    char    customer_code[3];   //2
    char    number[8];          //7, Total 16 bytes
}customer_version_t;

//Customer Hirain
const static customer_version_t customer_hr_sw_version = {
        //93G003HRSXXX
        .project_code   = "93G003",
        .customer_code  = CUSTOMER_HIRAIN_CODE,
        .number         = "S014b01"
};

//Customer Neusoft
const static customer_version_t customer_ns_sw_version = {
        //93G003NSSXXX
        .project_code   = "93G003",
        .customer_code  = CUSTOMER_NEUSOFT_CODE,
        .number         = "S014b01"
};

//Customer TSINTEL
const static customer_version_t customer_ts_sw_version = {
        //93G003NSSXXX
        .project_code   = "93G003",
        .customer_code  = CUSTOMER_TSINTEL_CODE,
        .number         = "S014b01"
};

static customer_version_t customer_hw_version = {
        .project_code = "93G003",
        .customer_code = CUSTOMER_CODE,
        .number = "H000"
};

const static customer_version_t customer_hw_version_93G003HRH000 = {
        //93G003HRH001
        .project_code   = "93G003",
        .customer_code  = CUSTOMER_CODE,
        .number         = "H000"
};

const static customer_version_t customer_hw_version_93G003HRH001 = {
        //93G003HRH001
        .project_code   = "93G003",
        .customer_code  = CUSTOMER_CODE,
        .number         = "H001"
};

const static customer_version_t customer_hw_version_93G014HRH002 = {
        //93G014HRH002
        .project_code   = "93G014",
        .customer_code  = CUSTOMER_CODE,
        .number         = "H002"
};

const static customer_version_t customer_hw_version_93G014HRH003 = {
        //93G014HRH003
        .project_code   = "93G014",
        .customer_code  = CUSTOMER_CODE,
        .number         = "H003"
};

const static customer_version_t customer_hw_version_93G016HRH004 = {
        //93G016HRH003
        .project_code   = "93G016",
        .customer_code  = CUSTOMER_CODE,
        .number         = "H004"
};

static void customer_info(char** args, int count)
{
	if(count > 1) {
		if(!strcmp(args[1],"veh")) {
			PRINTF("Speed: %.2f\n", get_eps_speed_value());
			PRINTF("Yaw Rate: %.2f\n", get_veh_filtered_yaw_rate_value());
			PRINTF("Steering Angle: %.2f\n", get_steering_angle_value());
			PRINTF("Gear Position: %d\n", get_gear_value());
			PRINTF("Ign: %d\n", get_ign_value());
			PRINTF("Turn Sig: %d\n", get_turn_indicator_value());
		}
		else if(!strcmp(args[1],"list"))
			goto _list_cusid;
	}
	else {
_list_cusid:
		count = 0;
		PRINTF("listing cusid..\n");
		while(count < CUSTOM_ID_INVALID){
			PRINTF("%d:%s\n",count, customer_name[count]);
			count++;
		}
	}
}


const char* customer_name_get(uint8_t id)
{
	if(id < CUSTOM_ID_INVALID)
		return customer_name[id];
	return "invalid";
}

void customer_init(void)
{
	const product_info_t* prod = product_info_get();

    version = get_hw_ver();

    switch(version)
    {
        case HW_93G003_COMBO_FRONT_RADAR_BV3p3:
            memcpy(&customer_hw_version, &customer_hw_version_93G003HRH000, sizeof(customer_version_t));
            break;
        case HW_93G003_COMBO_FRONT_RADAR_BV3p4:
            memcpy(&customer_hw_version, &customer_hw_version_93G003HRH001, sizeof(customer_version_t));
            break;
        case HW_93G014_MRR_BV1p0_FOR_HIRAIN:
            memcpy(&customer_hw_version, &customer_hw_version_93G014HRH002, sizeof(customer_version_t));
            break;
        case HW_93G014_MRR_BV2p1_FOR_HIRAIN:
            memcpy(&customer_hw_version, &customer_hw_version_93G014HRH003, sizeof(customer_version_t));
            break;
        case HW_93G016_MRR_BV2p1_FOR_HIRAIN_S32R264:
            memcpy(&customer_hw_version, &customer_hw_version_93G016HRH004, sizeof(customer_version_t));
            break;
        default:
            break;
    }

	if(prod->customer < CUSTOM_ID_INVALID)
	{
		cubtek_init();

		check_radar_alignment_result();

		frame_play(-1,-1,-1,NULL,NULL);
	}
	else
		PRINTF("ctm: customer(%d) init failed\n",prod->customer);

	console_command_reg("cusinfo",customer_info);
}

void upd_hw_number_get(char *num)
{
    sprintf(num, "%s", customer_hw_version.number);
}

void upd_hw_version_get(char *ver)
{
    uint32_t UDS_CanID = 0;
    UDS_CanID = get_uds_physical_request();
    if(0x7A0 == UDS_CanID)
    {
        //Customer Hirain
        sprintf(ver, "%s%s%s", customer_hw_version.project_code, CUSTOMER_HIRAIN_CODE, customer_hw_version.number);
    }
    else if(0x7B0 == UDS_CanID)
    {
        //Customer Neusoft
        sprintf(ver, "%s%s%s", customer_hw_version.project_code, CUSTOMER_NEUSOFT_CODE, customer_hw_version.number);
    }
    else if(0x7C1 == UDS_CanID)
    {
        //Customer TSINTEL
        sprintf(ver, "%s%s%s", customer_hw_version.project_code, CUSTOMER_TSINTEL_CODE, customer_hw_version.number);
    }
}

void upd_sw_number_get(char *num)
{
    uint32_t UDS_CanID = 0;
    UDS_CanID = get_uds_physical_request();
    if(0x7A0 == UDS_CanID)
    {
        //Customer Hirain
        sprintf(num, "%s", customer_hr_sw_version.number);
    }
    else if(0x7B0 == UDS_CanID)
    {
        //Customer Neusoft
        sprintf(num, "%s", customer_ns_sw_version.number);
    }
    else if(0x7C1 == UDS_CanID)
    {
        //Customer TSINTEL
        sprintf(num, "%s", customer_ts_sw_version.number);
    }
}

void upd_sw_version_get(char *ver)
{
    uint32_t UDS_CanID = 0;
    UDS_CanID = get_uds_physical_request();
    if(0x7A0 == UDS_CanID)
    {
        //Customer Hirain
        sprintf(ver, "%s%s%s", customer_hr_sw_version.project_code, customer_hr_sw_version.customer_code, customer_hr_sw_version.number);
    }
    else if(0x7B0 == UDS_CanID)
    {
        //Customer Neusoft
        sprintf(ver, "%s%s%s", customer_ns_sw_version.project_code, customer_ns_sw_version.customer_code, customer_ns_sw_version.number);
    }
    else if(0x7C1 == UDS_CanID)
    {
        //Customer TSINTEL
        sprintf(ver, "%s%s%s", customer_ts_sw_version.project_code, customer_ts_sw_version.customer_code, customer_ts_sw_version.number);
    }
}
