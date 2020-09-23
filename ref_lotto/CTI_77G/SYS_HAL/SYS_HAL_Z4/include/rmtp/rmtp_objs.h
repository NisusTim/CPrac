/*
 * rmtp_objs.h
 *
 *  Created on: 2017/09/22
 *      Author: Benson
 */

#ifndef _RMTP_OBJS_H_
#define _RMTP_OBJS_H_

extern rmtp_obj_t rmtp_obj_radar_system;
extern rmtp_obj_t rmtp_obj_system_security;
extern rmtp_obj_t rmtp_obj_firmware_version;
extern rmtp_obj_t rmtp_obj_target_list;
extern rmtp_obj_t rmtp_obj_radar_field_of_view;
extern rmtp_obj_t rmtp_obj_signal_process;
extern rmtp_obj_t rmtp_obj_communication_setting;
extern rmtp_obj_t rmtp_obj_signal_process_parameter;
extern rmtp_obj_t rmtp_obj_parameter_setting;
extern rmtp_obj_t rmtp_obj_firmware_upgrade;
extern rmtp_obj_t rmtp_obj_hardware_status;
extern rmtp_obj_t rmtp_obj_radar_calibration;
extern rmtp_obj_t rmtp_obj_system_config;
extern rmtp_obj_t rmtp_obj_system_log;
extern rmtp_obj_t rmtp_obj_self_diagnostics;
extern rmtp_obj_t rmtp_obj_rf_signal;
extern rmtp_obj_t rmtp_obj_rf_ic_setting;
extern rmtp_obj_t rmtp_obj_inner_safety_monitor;
extern rmtp_obj_t rmtp_obj_fcw_warning_setting;

void rmtp_obj_init(void);
void rmtp_obj_destroy(void);
rmtp_obj_t* rmtp_get_obj(uint8_t id);

#endif /* _RMTP_OBJS_H_ */
