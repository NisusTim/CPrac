/*
 * radar_output_controller.c
 *
 *  Created on: 2019/5/2
 *      Author: WoodLiu
 */

#include <stdlib.h>
#include "radar_output_controller.h"
#include "frame.h"
#include "can_msg_format.h"
#include "can_id.h"
#include "vehicle.h"
#include "json_meas_list.h"
#include "rmtp_api.h"
#include "json_meas_list.h"
#include "json_veh_info.h"
#include "json_debug_info.h"
#include "json_target_list.h"
#include "json_warning_msg.h"
#include "json_radar_info.h"
#include "json_frame_info.h"
#include "json_imu_info.h"
#include "isotp.h"
#include "product.h"
#include "z47_ipc.h"
#include "customer.h"

#define VALID	0
#define INVALID	1

void radar_output_controller_init()
{
	static uint8_t isInited = FALSE;
	if( isInited == TRUE ){
		return;
	}

	isInited = TRUE;

#if JSON_LIST_EN
	init_json_dbg_info();
	reg_tx_function(send_json_dbg_info_by_isotp_format);
	ipc_reg_msg(MSG_JSON_DBG_INFO, "json_dbg", (msg_proc_p)send_json_dbg_info_by_isotp_format);
	ipc_reg_msg(MSG_JSON_TARGET_LIST, "json_target", (msg_proc_p)send_json_target_list_by_isotp_format);
//	ipc_reg_msg(MSG_WARN_MSG, "json_warn", (msg_proc_p)send_json_warn_msg_by_isotp_format);
	ipc_reg_msg(MSG_JSON_MEAS_LIST, "json_meas", (msg_proc_p)send_json_meas_list_by_isotp_format);
#endif
}

#if JSON_LIST_EN
void send_json_meas_list_by_isotp_format(frame_data_p fdata)
{
    bool flag = get_json_meas_list_flag();

    if(true == flag)
    {
    	product_info_p prod = (product_info_t*)product_info_get();
        uint16_t device = prod->device_id;
        JsonMeasHeader json_meas_header;
        JsonMeasData json_meas_data;
        uint16_t mcnt = 0;

        json_meas_header = compose_meas_list_to_header_of_json_frame_data(fdata);

        isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_meas_header, sizeof(JsonMeasHeader));

        json_meas_data = compose_meas_list_to_data_of_json_frame_data(&mcnt);

        isotp_just_send(ICI_TX_ID | device,
        			   (uint8_t *)&json_meas_data,
					   (sizeof(json_meas_data.header) +
					   (sizeof(json_meas_data.meas[0]) * mcnt)));

//        clear_json_meas_regs();
    }
}

void send_json_meas_list_resp_by_isotp_format(void)
{
	product_info_p prod = (product_info_t*)product_info_get();
    uint16_t device = prod->device_id;
    JsonFileHeader json_file_header;

	get_json_file_header_of_meas_list(&json_file_header);

    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.header, sizeof(json_file_header.header));
    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.data, sizeof(json_file_header.data));
}

void send_json_veh_info_by_isotp_format(void)
{
    bool flag = get_json_veh_info_flag();

    if(true == flag)
    {
    	product_info_p prod = (product_info_t*)product_info_get();
        uint16_t device = prod->device_id;
        JsonVehInfoData veh_info_data;

        veh_info_data = compose_veh_info_to_data_of_json_frame_data();

        isotp_just_send(ICI_TX_ID | device, (uint8_t *)&veh_info_data, (sizeof(veh_info_data)));
    }
}

void send_json_veh_info_resp_by_isotp_format(void)
{
	product_info_p prod = (product_info_t*)product_info_get();
    uint16_t device = prod->device_id;
    JsonFileHeader json_file_header;

    get_json_file_header_of_veh_info(&json_file_header);

    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.header, sizeof(json_file_header.header));
    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.data, sizeof(json_file_header.data));
}

void send_json_dbg_info_by_isotp_format(void)
{
    bool flag = get_json_dbg_info_flag();

    if(true == flag)
    {
    	product_info_p prod = (product_info_t*)product_info_get();
        uint16_t device = prod->device_id;
        JsonDbgInfoData dbg_info_data;

        dbg_info_data = compose_dbg_info_to_data_of_json_frame_data();

        isotp_just_send(ICI_TX_ID | device, (uint8_t *)&dbg_info_data, (sizeof(dbg_info_data)));
    }
}

void send_json_dbg_info_resp_by_isotp_format(void)
{
	product_info_p prod = (product_info_t*)product_info_get();
    uint16_t device = prod->device_id;
    JsonFileHeader json_file_header;

    get_json_file_header_of_dbg_info(&json_file_header);

    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.header, sizeof(json_file_header.header));
    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.data, sizeof(json_file_header.data));
}

void send_json_target_list_by_isotp_format(frame_data_t* fd)
{
    bool flag = get_json_target_list_flag();

    if(true == flag)
    {
    	product_info_p prod = (product_info_t*)product_info_get();
        uint16_t device = prod->device_id;
        JsonTargetHeader json_target_header;
        JsonTargetData json_target_data;

        json_target_header = compose_target_list_to_header_of_json_frame_data(fd);

        isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_target_header, sizeof(JsonTargetHeader));

        json_target_data = compose_target_list_to_data_of_json_frame_data(fd);

        isotp_just_send(ICI_TX_ID | device,
					   (uint8_t *)&json_target_data,
					   (sizeof(json_target_data.header) +
					   (sizeof(json_target_data.target[0]) * fd->trkgrp.tcnt)));
    }
}

void send_json_target_list_resp_by_isotp_format(void)
{
	product_info_p prod = (product_info_t*)product_info_get();
    uint16_t device = prod->device_id;
    JsonFileHeader json_file_header;

	get_json_file_header_of_target_list(&json_file_header);

    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.header, sizeof(json_file_header.header));
    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.data, sizeof(json_file_header.data));
}

void send_json_warn_msg_by_isotp_format(tracking_group_t *target_group)
{
    bool flag = get_json_warn_msg_flag();

    if(true == flag)
    {
    	product_info_p prod = (product_info_t*)product_info_get();
        uint16_t device = prod->device_id;
        JsonWarnData warn_msg_data;

        warn_msg_data = compose_warn_msg_to_data_of_json_frame_data(target_group);

        isotp_just_send(ICI_TX_ID | device, (uint8_t *)&warn_msg_data, (sizeof(warn_msg_data)));
    }
}

void send_json_warn_msg_resp_by_isotp_format(void)
{
	product_info_p prod = (product_info_t*)product_info_get();
    uint16_t device = prod->device_id;
    JsonFileHeader json_file_header;

    get_json_file_header_of_warn_msg(&json_file_header);

    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.header, sizeof(json_file_header.header));
    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.data, sizeof(json_file_header.data));
}

void send_json_radar_info_by_isotp_format(void)
{
	product_info_p prod = (product_info_t*)product_info_get();
    uint16_t device = prod->device_id;
	JsonRadarInfo radar_info_data;

	radar_info_data = compose_radar_info_to_data_of_json_frame_data();

	isotp_just_send(ICI_TX_ID | device, (uint8_t *)&radar_info_data, (sizeof(radar_info_data)));
}

void send_json_radar_info_resp_by_isotp_format(void)
{
	product_info_p prod = (product_info_t*)product_info_get();
    uint16_t device = prod->device_id;
    JsonFileHeader json_file_header;

    get_json_file_header_of_radar_info(&json_file_header);

    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.header, sizeof(json_file_header.header));
    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.data, sizeof(json_file_header.data));
}

void send_json_frame_info_by_isotp_format(uint16_t frame_time)
{
    bool flag = get_json_frame_info_flag();

    if(true == flag)
    {
    	product_info_p prod = (product_info_t*)product_info_get();
        uint16_t device = prod->device_id;
		JsonFrameInfo frame_info_data;

		frame_info_data = compose_frame_info_to_data_of_json_frame_data(frame_time);

		isotp_just_send(ICI_TX_ID | device, (uint8_t *)&frame_info_data, (sizeof(frame_info_data)));
    }
}

void send_json_frame_info_resp_by_isotp_format(void)
{
	product_info_p prod = (product_info_t*)product_info_get();
    uint16_t device = prod->device_id;
    JsonFileHeader json_file_header;

    get_json_file_header_of_frame_info(&json_file_header);

    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.header, sizeof(json_file_header.header));
    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.data, sizeof(json_file_header.data));
}

void send_json_imu_info_by_isotp_format(void)
{
    bool flag = get_json_imu_info_flag();

    if(true == flag)
    {
        product_info_p prod = (product_info_t*)product_info_get();
        uint16_t device = prod->device_id;
        JsonIMUHeader json_imu_header;
//        JsonIMUData json_imu_info_data;

        json_imu_header = compose_imu_info_to_header_of_json_frame_data();

        isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_imu_header.header, sizeof(JsonIMUHeader));

//        json_imu_info_data = compose_imu_info_to_data_of_json_frame_data();

//        isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_imu_info_data, (sizeof(JsonIMUData)));
    }
}

void send_json_imu_info_resp_by_isotp_format(void)
{
    product_info_p prod = (product_info_t*)product_info_get();
    uint16_t device = prod->device_id;
    JsonFileHeader json_file_header;

    get_json_file_header_of_imu_info(&json_file_header);

    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.header, sizeof(json_file_header.header));
    isotp_just_send(ICI_TX_ID | device, (uint8_t *)&json_file_header.data, sizeof(json_file_header.data));
}
#endif
