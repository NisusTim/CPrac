/*
 * radar_output_controller.h
 *
 *  Created on: 2019/5/2
 *      Author: WoodLiu
 */

#ifndef CONTROLLER_RADAR_OUTPUT_CONTROLLER_H_
#define CONTROLLER_RADAR_OUTPUT_CONTROLLER_H_

#include "target.h"
#include "customer.h"
#include "ism330dlc.h"

#define TARGET_LIST_OFF					0
#define TARGET_LIST_ON					1
typedef enum
{
	TARGET_LIST_TX_OFF = 0,
	TARGET_LIST_TX_ON
}TARGET_LIST_TX_SWITCH_E;

typedef struct{
	uint16_t can_id_header;
	uint16_t can_id_list;
	uint16_t can_id_ex_list;
}cnr_can_id_t,*cnr_can_id_p;

void radar_output_controller_init();

#if JSON_LIST_EN
void send_json_meas_list_by_isotp_format(frame_data_p fdata);
void send_json_meas_list_resp_by_isotp_format(void);
void send_json_veh_info_by_isotp_format(void);
void send_json_veh_info_resp_by_isotp_format(void);
void send_json_dbg_info_by_isotp_format(void);
void send_json_dbg_info_resp_by_isotp_format(void);
void send_json_target_list_by_isotp_format(frame_data_t* fd);
void send_json_target_list_resp_by_isotp_format(void);
void send_json_warn_msg_by_isotp_format(tracking_group_t *target_group);
void send_json_warn_msg_resp_by_isotp_format(void);
void send_json_radar_info_by_isotp_format(void);
void send_json_radar_info_resp_by_isotp_format(void);
void send_json_frame_info_by_isotp_format(uint16_t frame_time);
void send_json_frame_info_resp_by_isotp_format(void);
void send_json_imu_info_by_isotp_format(void);
void send_json_imu_info_resp_by_isotp_format(void);
#endif

#endif /* CONTROLLER_RADAR_OUTPUT_CONTROLLER_H_ */
