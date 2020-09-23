/*
 * rmtp_hal.h
 *
 *  Created on: 2017/09/22
 *      Author: Benson
 */

#ifndef _RMTP_HAL_H_
#define _RMTP_HAL_H_
#include "sys_shared.h"

#define TIMER_OBJ_MAX		16
#define TIMER_OBJ_UNUSED	-1
#define ADDR_OF_UUID 		0x4000A8
#define RF_RX_DATA_SIZE 	4096
#define UNKNOWN				255

enum {
	ADMIN_UNLOCK			= 0,
	ADMIN_LOCK				= 1
};

enum {
	TIMER_STOP 				= 0,
	TIMER_START				= 1
};

enum {
	OPEAR_STATE_UPGARDE 	= 0,	
	OPEAR_STATE_ACTIVE		= 1,
	OPEAR_STATE_PAUSE		= 2,
	OPEAR_STATE_UNKNOWN		= 255
};

enum {
	SPT_STATE_NOT_READY 	= 0,
	SPT_STATE_READY			= 1
};

enum {
	BOOT_LOADER_VERSION		= 0,
	Z4_FW_VERSION			= 1,
	Z7_0_FW_VERSION			= 2,
	Z7_1_FW_VERSION			= 3,
	FW_REVISION				= 4
};

enum {
	CMD_ACCEPT 				= 0,
	CMD_REJECT				= 1
};

enum {
	FW_Z4A					= 0,
	FW_Z4B					= 1,
	FW_Z70A					= 2,
	FW_Z70B					= 3,
	FW_Z71					= 4,
	FW_ALL					= 5,
	FW_BLDR					= 6,
	FW_UNKNOWN				= 255
};

enum {
	FW_UPGRADE_OK			= 0,
	FW_UPGRADE_ERR_FAILED	= 1,
	FW_UPGRADE_ERR_ADDR		= 2,
	FW_UPGRADE_ERR_CHECKSUM	= 3,
	FW_UPGRADE_ERR_STATE	= 4,
	FW_UPGRADE_ERR_IMGNO	= 5,
	FW_UPGRADE_ERR_SIZE		= 6,
	FW_UPGRADE_ERR_MAGIC	= 7,
	FW_UPGRADE_ERR_CHKSUM	= 8,
	FW_UPGRADE_ERR_FLASH	= 9,
	FW_UPGRADE_ERR_VERIFY	= 10		
};

typedef void (*target_cb)(uint8_t res, float angle, float range, float velocity, float mag, float vangle);
typedef void (*doppler_cb)(uint8_t res, uint8_t *data);
typedef void (*measure_cb)(uint8_t res, uint8_t *data);
typedef void (*imu_calib_selftest_cb)(uint8_t res);
typedef void (*imu_calib_static_cb)(uint8_t res, uint8_t *data);
typedef void (*rf_signal_received_cb)(uint32_t addr, uint32_t size);

void rmtp_hal_init(void);
void rmtp_set_timer(uint8_t objId, uint8_t mode);
uint8_t rmtp_get_network_id(void);
uint8_t rmtp_get_operational_state(void);
int rmtp_set_operational_state(uint8_t state);
uint8_t rmtp_get_admin_state(void);
int rmtp_set_admin_state(uint8_t state);
uint8_t rmtp_get_spt_state(void);
int rmtp_get_product_id(uint8_t *id);
int rmtp_get_customer_id(uint8_t *id);
int rmtp_get_device_id(uint8_t *id);
int rmtp_set_device_id(uint16_t id);
int rmtp_get_manufacture_date(uint8_t *data);
int rmtp_set_manufacture_date(uint8_t *data);
int rmtp_system_reset(uint8_t mode);
uint32_t rmtp_get_rand_seed(void);
int rmtp_get_serial_number(uint8_t blockId, uint8_t *data);
int rmtp_set_serial_number(uint8_t blockId, uint8_t *data);
int rmtp_get_firmware_version(uint8_t imgNum, uint8_t *ver);
uint8_t rmtp_get_fw_upgrade_prepare_state(void);
int rmtp_set_fw_upgrade_reguest(uint8_t imgNum, uint32_t size);
int rmtp_fw_upgrade_write_image(uint32_t offset, uint8_t *data, uint8_t size);
int rmtp_fw_upgrade_write_image_done(uint32_t size);
int rmtp_get_fw_upgrade_status(uint8_t imgNum);
int rmtp_set_jtag_lock_state(uint8_t lock);
uint8_t rmtp_get_jtag_lock_state(void);
int rmtp_get_rf_ic_status(uint8_t *status);
int rmtp_get_mcu_voltage(uint8_t *status);
int rmtp_get_power_voltage(uint8_t *values);
int rmtp_get_rfic_voltage(uint8_t *values);
int rmtp_get_mcu_temperature(uint8_t *temp);
int rmtp_get_temperature(uint8_t *temp);
int rmtp_calibration_control(float range, int16_t angle, target_cb cb);
int rmtp_doppler_control(uint8_t index, float range, doppler_cb cb);
int rmtp_get_doppler_data(uint8_t blockId, uint8_t *data, uint8_t *dopper);
int rmtp_measurement_control(uint8_t index, float range, measure_cb cb);
int rmtp_get_measurement_data(uint8_t blockId, uint8_t *data, uint8_t *measure);
int rmtp_imu_calib_selftest_control(imu_calib_selftest_cb cb);
int rmtp_imu_calib_static_control(imu_calib_static_cb cb);
int rmtp_get_imu_calib_data(uint8_t blockId, uint8_t *data);
int rmtp_set_imu_calib_data(uint8_t blockId, uint8_t *data);
int rmtp_rf_transmit_signal(uint8_t transmitter, rf_signal_received_cb cb);
#if RMTP_NOISE_BASE
int rmtp_get_noise_base(uint8_t sampleTimes, uint8_t *data);
#endif
int rmtp_get_rf_ic_register(uint8_t moduleAddr, uint16_t regAddr, uint8_t *data);
int rmtp_set_rf_ic_register(uint8_t moduleAddr, uint16_t regAddr, uint32_t value);
int rmtp_get_rf_ic_frequency(uint8_t pid, uint8_t *data);
int rmtp_set_rf_ic_frequency(uint8_t pid, uint16_t value);
int rmtp_get_rf_ic_operational_state(uint8_t pid, uint8_t *data);
int rmtp_get_rf_ic_tx_gain(uint8_t pid, uint8_t *data);
int rmtp_set_rf_ic_tx_gain(uint8_t pid, uint8_t *data);
int rmtp_get_rf_ic_rx_gain(uint8_t pid, uint8_t *data);
int rmtp_set_rf_ic_rx_gain(uint8_t pid, uint8_t *data);
int rmtp_get_rf_ic_cw_tx_gain(uint8_t *data);
int rmtp_set_rf_ic_cw_tx_gain(uint8_t *data);

int rmtp_get_fcw_warning_flags(uint8_t *value);
int rmtp_set_fcw_warning_flags(uint8_t *value);
int rmtp_get_fcw_warning_speed_level(uint8_t level, uint8_t *value);
int rmtp_set_fcw_warning_speed_level(uint8_t level, uint8_t *value);
int rmtp_get_fcw_warning_ttc_level(uint8_t type, uint8_t level, uint8_t *value);
int rmtp_set_fcw_warning_ttc_level(uint8_t type, uint8_t level, uint8_t *value);

int rmtp_get_field_of_view_width(uint8_t *value);
int rmtp_set_field_of_view_width(uint8_t *value);
int rmtp_get_field_of_view_range(uint8_t *value);
int rmtp_set_field_of_view_range(uint8_t *value);
int rmtp_get_field_of_view_angle(uint8_t *value);
int rmtp_set_field_of_view_angle(uint8_t *value);
int rmtp_get_view_zone_value(uint8_t index, uint8_t *value);
int rmtp_set_view_zone_value(uint8_t index, uint8_t *value);
int rmtp_get_aoa_shift(uint8_t *value);
int rmtp_set_aoa_shift(uint8_t *value);
int rmtp_get_spt_aoa_shift(uint8_t id, uint8_t *data);
int rmtp_set_spt_aoa_shift(uint8_t id, int16_t data);
int rmtp_get_lateral_shift(uint8_t *value);
int rmtp_set_lateral_shift(uint8_t *value);
int rmtp_get_longitudinal_shift(uint8_t *value);
int rmtp_set_longitudinal_shift(uint8_t *value);
int rmtp_get_coordinate_axis_rotation(uint8_t *value);
int rmtp_set_coordinate_axis_rotation(uint8_t value);
int rmtp_get_tracking_calibration_info(uint8_t index, uint8_t *value);
int rmtp_set_tracking_calibration_info(uint8_t index, uint8_t value);
int rmtp_get_corner_point(uint8_t index, uint8_t *value);
int rmtp_set_corner_point(uint8_t index, uint8_t *value);
int rmtp_get_anchor_point(uint8_t index, uint8_t *value);
uint8_t rmtp_get_detection_mode(void);
int rmtp_set_detection_mode(uint8_t value);

uint8_t rmtp_get_warning_device_model(void);
int rmtp_set_warning_device_model(uint8_t model);
int rmtp_get_front_radar_position(uint8_t index, uint8_t *value);
int rmtp_set_front_radar_position(uint8_t index, uint8_t *value);
int rmtp_get_side_radar_position(uint8_t index, uint8_t *value);
int rmtp_set_side_radar_position(uint8_t index, uint8_t *value);
int rmtp_get_rear_radar_position(uint8_t index, uint8_t *value);
int rmtp_set_rear_radar_position(uint8_t index, uint8_t *value);
uint8_t rmtp_get_tx_measurement_list_flag(void);
int rmtp_set_tx_measurement_list_flag(uint8_t op);
uint8_t rmtp_get_tx_target_list_flag(void);
int rmtp_set_tx_target_list_flag(uint8_t op);
int rmtp_get_pars_id_list(uint8_t *data, uint16_t *size);
int rmtp_get_pars_version_size(uint32_t id, uint16_t *ver, uint16_t *size);
uint8_t* rmtp_get_pars_info(int32_t id, uint16_t *ver, uint16_t *size);
int rmtp_set_pars_info(uint32_t id, uint8_t *data, uint16_t size);
uint8_t* rmtp_get_pars_json_data(uint32_t id, uint16_t *size);
uint8_t * rmtp_get_all_pars_json_data ( uint16_t *size);
void rmtp_lock_frequency_mode_set(uint16_t frequency, uint8_t tx, uint8_t time);
void rmtp_lock_frequency_mode_done(uint8_t netID);
uint8_t rmtp_get_calib_mode(void);
int rmtp_set_calib_mode(uint8_t mode);
int rmtp_set_calib_bandwidth(uint16_t bandwidth);
int rmtp_get_calib_bandwidth(uint16_t* bandwidth);
void rmtp_save_calib_coef(void);
int rmtp_get_calib_coef(uint8_t blockId, uint8_t *data);
int rmtp_set_calib_coef(uint8_t blockId, uint8_t *data);
int rmtp_set_configuration_reset(uint32_t * pars_id);
int rmtp_get_Tx_High_Level(uint8_t TxId, uint8_t* retTxId, uint8_t* retTxHighLevel);
int rmtp_set_Tx_High_Level(uint8_t TxId, uint8_t TxGain, uint8_t* retTxId, uint8_t* retTxHighLevel);
int rmtp_get_trkp(uint8_t Info_ID, uint8_t * res_data);
int rmtp_set_trkp(uint8_t Info_ID, uint8_t set_data);
int rmtp_get_trk2(uint8_t Info_ID, uint8_t * res_data);
int rmtp_set_trk2(uint8_t Info_ID, int16_t set_data);
int rmtp_get_Vehp(uint8_t Info_ID, uint8_t * res_data);
int rmtp_set_Vehp(uint8_t Info_ID, int16_t set_data);
int rmtp_get_can_baud_rate(uint8_t com_interface , uint8_t * br_mode_ptr);
int rmtp_set_can_baud_rate(uint8_t com_interface , uint8_t br_mode);

#endif /* _RMTP_HAL_H_ */
