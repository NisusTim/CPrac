/*
 * rmtp_objs.c
 *
 *  Created on: 2017/09/22
 *      Author: Benson
 */
#include <stdio.h>
#include <stdint.h>
#include "rmtp_msg.h"
#include "rmtp_ids.h"
#include "rmtp_objs.h"

rmtp_obj_t rmtp_obj_max = {
		.obj_id = MAX_OBJ_NUM
};

const rmtp_obj_t *rmtpObjList[] = {
	[0] 			= &rmtp_obj_radar_system,
	[1] 			= &rmtp_obj_system_security,
	[2] 			= &rmtp_obj_target_list,
	[3]				= &rmtp_obj_radar_field_of_view,
	[4]		        = &rmtp_obj_signal_process,
	[5]	            = &rmtp_obj_communication_setting,
	[6] 		    = &rmtp_obj_signal_process_parameter,
	[7]             = &rmtp_obj_parameter_setting,
	[8]			    = &rmtp_obj_firmware_version,
	[9] 		    = &rmtp_obj_firmware_upgrade,
	[10]		    = &rmtp_obj_hardware_status,
	[11]		    = &rmtp_obj_radar_calibration,
	[12]		    = &rmtp_obj_system_config,
	[13]		    = &rmtp_obj_system_log,
	[14]		    = &rmtp_obj_self_diagnostics,
	[15]		    = &rmtp_obj_rf_signal,
	[16]		    = &rmtp_obj_rf_ic_setting,
	[17]		    = &rmtp_obj_inner_safety_monitor,
	[18]  			= &rmtp_obj_fcw_warning_setting,
	[MAX_OBJ_NUM]	= &rmtp_obj_max
};

void rmtp_obj_init(void)
{
	int i;
	rmtp_obj_t *obj = NULL;
	
	for (i = 0; i < MAX_OBJ_NUM; i++) {
		obj = (rmtp_obj_t *)rmtpObjList[i];
		if (obj && obj->init) {
			obj->init();
		}
	}
}

void rmtp_obj_destroy(void)
{
	int i;
	rmtp_obj_t *obj = NULL;
	
	for (i = 0; i < MAX_OBJ_NUM; i++) {
		obj = (rmtp_obj_t *)rmtpObjList[i];
		if (obj && obj->destroy) {
			obj->destroy();
		}
	}	
}

rmtp_obj_t* rmtp_get_obj(uint8_t id)
{
	int i;
	rmtp_obj_t *obj = NULL;

	for (i = 0; i < MAX_OBJ_NUM; i++) {
		obj = (rmtp_obj_t *)rmtpObjList[i];
		if (obj && (obj->obj_id == id)) {
			return obj;
		}
	}

	return NULL;
}

