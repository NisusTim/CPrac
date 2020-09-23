/*
 * radar_input_controller.c
 *
 *  Created on: 2019/5/2
 *      Author: WoodLiu
 */

#include "radar_input_controller.h"
#include "vehicle.h"
#include "customer.h"
#include "isotp_defines.h"
#include "json_meas_list.h"
#include "radar_output_controller.h"
#include "json_veh_info.h"
#include "json_debug_info.h"
#include "json_target_list.h"
#include "json_warning_msg.h"
#include "json_frame_info.h"
#include "json_imu_info.h"
#include "isotp.h"
#include "product.h"
#include "can_id.h"
#include "canfd_registration_flag.h"



void radar_input_controller_init()
{
	product_info_p prod = (product_info_t*)product_info_get();
	uint16_t device = prod->device_id;
	canfd_registration_init(device);
}


void json_req_handle(IsoTpLink *isotp_link)
{
#if JSON_LIST_EN
	if(ISOTP_RECEIVE_STATUS_FULL == isotp_link->receive_status)
	{
		switch(isotp_link->receive_buffer[0])
		{
		case CAN_PCODE_MEAS:

			if(1 == isotp_link->receive_buffer[4])
			{
				set_json_meas_list_flag(true);
				send_json_meas_list_resp_by_isotp_format();
			}
			else if(0 == isotp_link->receive_buffer[4])
			{
				set_json_meas_list_flag(false);
			}

			break;

		case CAN_PCODE_VEH_INFO:

			if(1 == isotp_link->receive_buffer[4])
			{
				set_json_veh_info_flag(true);
				send_json_veh_info_resp_by_isotp_format();
			}
			else if(0 == isotp_link->receive_buffer[4])
			{
				set_json_veh_info_flag(false);
			}

			break;

		case CAN_PCODE_DBG_INFO:

			if(1 == isotp_link->receive_buffer[4])
			{
				set_json_dbg_info_flag(true);
				send_json_dbg_info_resp_by_isotp_format();
			}
			else if(0 == isotp_link->receive_buffer[4])
			{
				set_json_dbg_info_flag(false);
			}

			break;

		case CAN_PCODE_TARGET:

			if(1 == isotp_link->receive_buffer[4])
			{
				set_json_target_list_flag(true);
				send_json_target_list_resp_by_isotp_format();
			}
			else if(0 == isotp_link->receive_buffer[4])
			{
				set_json_target_list_flag(false);
			}

			break;

		case CAN_PCODE_WARN:

			if(1 == isotp_link->receive_buffer[4])
			{
				set_json_warn_msg_flag(true);
				send_json_warn_msg_resp_by_isotp_format();
			}
			else if(0 == isotp_link->receive_buffer[4])
			{
				set_json_warn_msg_flag(false);
			}

			break;

		case CAN_PCODE_RADAR_INFO:

			if(1 == isotp_link->receive_buffer[4])
			{
				send_json_radar_info_resp_by_isotp_format();
				send_json_radar_info_by_isotp_format();
			}
			else if(0 == isotp_link->receive_buffer[4])
			{
				// NON
			}

			break;

		case CAN_PCODE_FRAME_INFO:

			if(1 == isotp_link->receive_buffer[4])
			{
				set_json_frame_info_flag(true);
				send_json_frame_info_resp_by_isotp_format();
			}
			else if(0 == isotp_link->receive_buffer[4])
			{
				set_json_frame_info_flag(false);
			}

			break;

//		case CAN_PCODE_NOISE_BASE_INFO:
//			break;

		case CAN_PCODE_IMU_INFO:

			if(1 == isotp_link->receive_buffer[4])
			{
				set_json_imu_info_flag(true);
				send_json_imu_info_resp_by_isotp_format();
			}
			else if(0 == isotp_link->receive_buffer[4])
			{
				set_json_imu_info_flag(false);
			}

			break;
		default:
			break;
		}
	}
#endif
}

