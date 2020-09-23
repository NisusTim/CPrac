/*
 * ism330dlc_reg_app.h
 *
 *  Created on: 2019�~1��28��
 *      Author: user
 */

#ifndef ISM330DLC_ISM330DLC_REG_APP_H_
#define ISM330DLC_ISM330DLC_REG_APP_H_

extern void register_reset_ok_init_function(event_proc_p cb);
extern int32_t ism330dlc_console_read_reg(uint8_t reg);
extern int32_t ism330dlc_console_write_reg(uint8_t reg,uint8_t reg_data);
extern int32_t ism330dlc_console_reg_dump(uint8_t len);
extern int32_t ism330dlc_device_id_get(event_proc_p cb);
extern int32_t ism330dlc_reset_status_get(uint8_t* bufp);
extern int32_t ism330dlc_reset_set(uint8_t val);
extern int32_t ism330dlc_block_data_update_set(uint8_t val);
extern int32_t ism330dlc_xl_data_rate_set(ism330dlc_odr_xl_t val);
extern int32_t ism330dlc_gy_data_rate_set(ism330dlc_odr_g_t val);
extern int32_t ism330dlc_xl_full_scale_set(ism330dlc_fs_xl_t val);
extern int32_t ism330dlc_gy_full_scale_set(ism330dlc_fs_g_t val);
extern int32_t ism330dlc_xl_filter_analog_set(ism330dlc_bw0_xl_t val);
extern int32_t ism330dlc_xl_lp2_bandwidth_set(ism330dlc_input_composite_t val);
extern int32_t ism330dlc_gy_band_pass_set_part1(ism330dlc_lpf1_sel_g_t val);
extern int32_t ism330dlc_gy_band_pass_set_part2(ism330dlc_lpf1_sel_g_t val);
extern int32_t ism330dlc_gy_band_pass_set_part3(ism330dlc_lpf1_sel_g_t val);
extern int32_t ism330dlc_xl_usr_offset_set(uint8_t *buff);
//extern int32_t ism330dlc_status_reg_get(event_proc_p cb);
extern int32_t ism330dlc_status_reg_get_value(uint8_t *value);
//extern int32_t ism330dlc_acceleration_raw_get(event_proc_p cb);
extern int32_t ism330dlc_acceleration_raw_get_value(uint8_t *value);
//extern int32_t ism330dlc_angular_rate_raw_get(event_proc_p cb);
extern int32_t ism330dlc_angular_rate_raw_get_value(uint8_t *value);
//extern int32_t ism330dlc_temperature_raw_get(event_proc_p cb);
extern int32_t ism330dlc_temperature_raw_get_value(uint8_t *value);
extern int32_t ism330dlc_temp_gyro_xl_raw_get(event_proc_p cb);
extern int32_t ism330dlc_config_self_test(uint8_t *buff);
extern int32_t asm330lhh_set_duration_for_inactivity_detection();
extern int32_t asm330lhh_set_activity_inactivity_threshold(uint8_t val);
extern int32_t asm330lhh_select_sleep_change_notification();
extern int32_t asm330lhh_enable_interrupt();
extern int32_t asm330lhh_activity_inactivity_interrupt_driven_to_int1_pin();
extern int32_t asm330lhh_int1_ctrl_get_value(uint8_t *value);
extern int32_t asm330lhh_wake_up_src_get_value(uint8_t *value);
#endif /* ISM330DLC_ISM330DLC_REG_APP_H_ */
