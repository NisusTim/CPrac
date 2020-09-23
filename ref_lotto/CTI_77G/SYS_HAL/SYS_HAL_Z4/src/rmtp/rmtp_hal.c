/*
 * rmtp_hal.c
 *
 *  Created on: 2017/09/22
 *      Author: Benson
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdint.h>
#include "sys_shared.h"
#include "can_cubtek.h"
#include "tracking.h"
#include "tracking_set.h"
#include "rmtp_ids.h"
#include "rmtp_msg.h"
#include "rmtp_hal.h"
#include "rmtp_api.h"
#include "rmtp_objs.h"
#include "coefs.h"
#include "can_cubtek.h"
#include "Nvm.h"

static const product_info_t *prod = NULL;
static timer_p timer = NULL;
static uint8_t timer_obj_cnt = 0;
static int8_t timer_obj_id[TIMER_OBJ_MAX] = {TIMER_OBJ_UNUSED};
static uint8_t admin_state = ADMIN_LOCK;
//static uint8_t network_id = RMTP_ITF_CAN0;
static target_cb calib_cb = NULL;
//static target_cb measure_cb = NULL;
static doppler_cb doppler_data_cb = NULL;
static measure_cb measure_data_cb = NULL;
static imu_calib_selftest_cb imu_calib_selftest_res_cb = NULL;
static imu_calib_static_cb imu_calib_static_res_cb = NULL;
static rf_signal_received_cb rf_received_cb = NULL;
static uint32_t rf_received_addr = 0;
static uint8_t calibration_mode = 0;

void rmtp_hal_init(void)
{
	timer = NULL;
	timer_obj_cnt = 0;
	memset(timer_obj_id, TIMER_OBJ_UNUSED, TIMER_OBJ_MAX);
}

static void timeout_proc(void* x)
{
	int i;
	rmtp_obj_t *obj = NULL;

	if (admin_state == ADMIN_LOCK)
		return;	
	for (i = 0; i < TIMER_OBJ_MAX; i++) {
		if (timer_obj_id[i] > TIMER_OBJ_UNUSED) {
			obj = rmtp_get_obj((uint8_t)timer_obj_id[i]);
			if (obj && obj->timeout_handler) {
				obj->timeout_handler();
			}
		}
	}
}

void rmtp_set_timer(uint8_t objId, uint8_t mode)
{
	int i;
	int16_t ticks = 0;

	if (mode == TIMER_STOP) {
		if (timer_obj_cnt > 0) {
			timer_obj_cnt--;
		}
		for (i = 0; i < TIMER_OBJ_MAX; i++) {
			if (timer_obj_id[i] == objId) {
				timer_obj_id[i] = TIMER_OBJ_UNUSED;
				break;
			}
		}
		if ((timer_obj_cnt == 0) && timer) {
			if (NULL != timer && !strcmp("rmtp", timer->name))
				timer_unset(&timer);
			timer = NULL;
			LOG("[RMTP] stop timer\n");
		}	
	} else if (mode == TIMER_START) {
	 	if ((timer == NULL) && (timer_obj_cnt == 0)) {
			ticks = (DEFAULT_TICKS_PER_SECOND / 10);
			LOG("[RMTP] start timer: ticks=%d, cnt=-1\n", ticks);
			timer = timer_set("rmtp", ticks, -1, timeout_proc, NULL);
			if (timer == NULL) {
				LOG("[RMTP] set timer failed: objId=0x%.2x\n", objId);
				return;
			}
		} else if (timer_obj_cnt >= TIMER_OBJ_MAX) {
			LOG("[RMTP] set timer ERR: reach the limit(%d)\n", TIMER_OBJ_MAX);
			return;
		}
		timer_obj_cnt++;
		for (i = 0; i < TIMER_OBJ_MAX; i++) {
			if (timer_obj_id[i] == TIMER_OBJ_UNUSED) {
				timer_obj_id[i] = objId;
				break;
			}
		}	
	}
	LOG("[RMTP] set timer: objId=0x%.2x, mode=%d cnt=%d\n", objId, mode, timer_obj_cnt);
}

int rmtp_get_serial_number(uint8_t blockId, uint8_t *data)
{
	int index, size;
	
	prod = product_info_get();
	index = blockId * 5;
	if (blockId == 3) {
		size = 4;
	} else {
		size = 5;
	}	
	memcpy(data, &prod->serial_no[index], size);
	
	return 0;
}

int rmtp_set_serial_number(uint8_t blockId, uint8_t *data)
{
	int done = 0;
	int index, size;
	
	prod = product_info_get();
	index = blockId * 5;
	if (blockId == 3) {
		size = 4;
		done = 1;
	} else {
		size = 5;
	}
	memcpy((uint8_t *)&prod->serial_no[index], data, size);
	if (done == 1) {
		product_pars_set();
	}
	
	return 0;
}

uint8_t rmtp_get_operational_state(void)
{
	uint8_t sys_state;
	uint8_t op_state;

	sys_state = sys_state_get();
	switch (sys_state) {
		case SYST_ACTIVE:
			op_state = OPEAR_STATE_ACTIVE;
			break;
		case SYST_PAUSED:
			op_state = OPEAR_STATE_PAUSE;
			break;
		default:
			op_state = OPEAR_STATE_UNKNOWN;
			break;
	}		
	LOG("[RMTP] get op state (sys_state=%d op_state=%d)\n", sys_state, op_state);	
	
	return op_state;
}

int rmtp_set_operational_state(uint8_t state)
{
	uint8_t sys_state;
	
	switch (state) {			
		case OPEAR_STATE_ACTIVE:
			sys_state = SYST_ACTIVE;
			break;
		case OPEAR_STATE_PAUSE:
			sys_state = SYST_PAUSED;
			break;
		default:
			return RES_ERROR;
	}		
	LOG("[RMTP] set op state (sys_state=%d op_state=%d)\n", sys_state, state);	
	sys_state_set(sys_state);

	return RES_SUCCESS;
}

uint8_t rmtp_get_admin_state(void)
{
	return admin_state;
}

int rmtp_set_admin_state(uint8_t state)
{
	admin_state = state;
	return RES_SUCCESS;
}

uint8_t rmtp_get_spt_state(void)
{
	/*uint8_t state;

	state = spt_measurements_state_get();
	if ((sys_state_get() == SYST_PAUSED) && (state != MEAS_ST_READY)) {
		return SPT_STATE_NOT_READY;
	}

	return SPT_STATE_READY;*/
	return SPT_STATE_NOT_READY;
}

int rmtp_get_product_id(uint8_t *id)
{
	id[0] = (product_info_get()->product & 0xFF00) >> 8;
	id[1] = (product_info_get()->product & 0x00FF);
	return RES_SUCCESS;
}

int rmtp_get_customer_id(uint8_t *id)
{
	id[0] = (product_info_get()->customer & 0xFF00) >> 8;
	id[1] = (product_info_get()->customer & 0x00FF);
	return RES_SUCCESS;
}

int rmtp_get_device_id(uint8_t *id)
{
	id[0] = (product_info_get()->device_id & 0xFF00) >> 8;
	id[1] = (product_info_get()->device_id & 0x00FF);
	return RES_SUCCESS;
}	

int rmtp_set_device_id(uint16_t id)
{
	product_devid_set(id);
	return RES_SUCCESS;
}

int rmtp_get_manufacture_date(uint8_t *data)
{
	data[0] = (uint8_t)((product_info_get()->manufacture_date & 0xFF000000) >> 24);
	data[1] = (uint8_t)((product_info_get()->manufacture_date & 0x00FF0000) >> 16);
	data[2] = (uint8_t)((product_info_get()->manufacture_date & 0x0000FF00) >> 8);
	data[3] = (uint8_t)((product_info_get()->manufacture_date & 0x000000FF));
	return RES_SUCCESS;
}	

int rmtp_set_manufacture_date(uint8_t *data)
{
	uint32_t date;

	date = ((uint32_t)data[0] << 24) + ((uint32_t)data[1] << 16) + ((uint32_t)data[2] << 8) + (uint32_t)data[3];
	product_manufacture_date_set(date);
	
	return RES_SUCCESS;
}

int rmtp_system_reset(uint8_t mode)
{
	if ((mode == 1) || (mode == 2)) {
		LOG("[RMTP] system reset to default (mode:%d)\n", mode);
		pars_ctx_erase(CAN_PARS_ID);
		pars_ctx_erase(CONSOLE_PARS_ID);
		pars_ctx_erase(FRAME_PARS_ID);
		pars_ctx_erase(TEF_PARS_ID);
		pars_ctx_erase(TRACKING_PARS_ID);
		pars_ctx_erase(TRACKING_PARS2_ID);
		pars_ctx_erase(FCWWARN_PARS_ID);
		if (mode == 2) {
			pars_ctx_erase(COEFS_PARS_ID);
			pars_ctx_erase(CALIB_IRON_PARS_ID);
			pars_ctx_erase(ISM330DLC_PARS_ID);
			pars_ctx_erase(FAW_DID_PARS_ID);
			pars_ctx_erase(DTC1_PARS_ID);
			pars_ctx_erase(DTC2_PARS_ID);
			pars_ctx_erase(DTC3_PARS_ID);
//			pars_ctx_erase(DTC4_PARS_ID);
//			pars_ctx_erase(DTC5_PARS_ID);
//			pars_ctx_erase(DTC6_PARS_ID);
		}
	} else {
		LOG("[RMTP] system reset!\n");
	}
#ifdef ENABLE_SWT
    Delay_ms(5);
	reset_system();
#endif
	return RES_SUCCESS;
}

uint32_t rmtp_get_rand_seed(void)
{
	return STM_0.CNT.R;
}

int rmtp_get_firmware_version(uint8_t imgNum, uint8_t *ver)
{
	switch (imgNum) {
		case BOOT_LOADER_VERSION:
			return RES_PARAMETER_ERROR;
		case Z4_FW_VERSION:
			/*if (upd_run_get() == IMGNO_Z4){
				ver[0] = CAN_INFO_IMG_Z4A;
				memcpy(&ver[1], HDR_Z4a->rv, 5);
			} else {
				ver[0] = CAN_INFO_IMG_Z4B;
				memcpy(&ver[1], HDR_Z4b->rv, 5);
			}
			return RES_SUCCESS;
		case Z7_0_FW_VERSION:
			if (upd_run_get() == IMGNO_Z4a){
				ver[0] = CAN_INFO_IMG_Z7A;
				memcpy(&ver[1], HDR_Z7a->rv, 5);
			} else {
				ver[0] = CAN_INFO_IMG_Z7B;
				memcpy(&ver[1], HDR_Z7b->rv, 5);
			}
			return RES_SUCCESS;
		case Z7_1_FW_VERSION:
			if (image_verify(IMAGE_ADDR_Z71) == RES_SUCCESS) {
				ver[0] = CAN_INFO_IMG_Z71;
				memcpy(&ver[1], HDR_Z71->rv, 5);
			} else {
				memset(ver, 0, 6);
			}*/
			return RES_SUCCESS;
		case FW_REVISION:
			upd_revision_get((char *)ver);
			return RES_SUCCESS;
		default:
			return RES_ERROR;
	}

	return RES_ERROR;
}

uint8_t rmtp_get_fw_upgrade_prepare_state(void)
{
	upd_prepare_state(1);
	return CMD_ACCEPT;
}

int rmtp_set_fw_upgrade_reguest(uint8_t imgNum, uint32_t size)
{
	if ((imgNum <= FW_BLDR) && (upd_request(imgNum, size) == RES_SUCCESS)) {
		return RES_SUCCESS;
	} else {
		return RES_ERROR;
	}	

	return RES_ERROR;
}

int rmtp_fw_upgrade_write_image(uint32_t offset, uint8_t *data, uint8_t size)
{
	upd_data_write(offset, data, size);
	return RES_SUCCESS;
}

int rmtp_fw_upgrade_write_image_done(uint32_t size)
{
	upd_data_write_done(size);
	return RES_SUCCESS;
}

int rmtp_get_fw_upgrade_status(uint8_t imgNum)
{	
	int ret = 0;
	ret = upd_data_done(imgNum);
	ret *= -1;
	return ret;
}

int rmtp_set_jtag_lock_state(uint8_t lock)
{
	if (lock == 1) {
		LOG("[RMTP] lock JTAG\n");
		write_n_enable_pass_module();
		return RES_SUCCESS;
	}

	return RES_ERROR;
}

uint8_t rmtp_get_jtag_lock_state(void)
{
	return check_DBL_lock();
}

int rmtp_get_rf_ic_status(uint8_t *status)
{
	*status = (uint8_t)get_tef810x_init_status();

	return RES_SUCCESS;
}

int rmtp_get_mcu_voltage(uint8_t *values)
{
	int v = 0;
	
	v = get_Vbg0_code();
	values[1] = (uint8_t)((v & 0xFF00) >> 8);
	values[2] = (uint8_t)(v & 0x00FF);
	v = get_Vbg1_code();
	values[3] = (uint8_t)((v & 0xFF00) >> 8);
	values[4] = (uint8_t)(v & 0x00FF);
	
	return RES_SUCCESS;
}

int rmtp_get_power_voltage(uint8_t *values)
{
	int v = 0;

	//Type:0x00, Power[2 bytes], MCU [2 bytes], -327.68~327.37
	v = (int)(get_power_supply_voltage() * 100);	// Voltage: 8.5 ~ 36
	values[1] = (uint8_t)((v & 0xFF00) >> 8);
	values[2] = (uint8_t)(v & 0x00FF);
	v = (int)(get_fs8x_vbuck1() * 100);	// Voltage: 1.19 ~ 1.32
	values[3] = (uint8_t)((v & 0xFF00) >> 8);
	values[4] = (uint8_t)(v & 0x00FF);
	
	return RES_SUCCESS;
}

int rmtp_get_rfic_voltage(uint8_t *values)
{
	int v = 0;

	//Type:0x02, RFIC1 [2 bytes], RFIC2 [2 bytes] , -327.68~327.37
	v = (int)(get_fs8x_vpre() * 100);	// Voltage: 4.05 ~ 4.25
	values[1] = (uint8_t)((v & 0xFF00) >> 8);
	values[2] = (uint8_t)(v & 0x00FF);
	v = (int)(get_fs8x_vpre() * 100);	// Voltage: 4.05 ~ 4.25
	values[3] = (uint8_t)((v & 0xFF00) >> 8);
	values[4] = (uint8_t)(v & 0x00FF);
	
	return RES_SUCCESS;
}

int rmtp_get_mcu_temperature(uint8_t *values)
{
	int t = 0;

	t = get_tsens0();
	values[0] = (uint8_t)(int8_t)t;
	t = get_tsens1();
	values[1] = (uint8_t)(int8_t)t;

	return RES_SUCCESS;
}

int rmtp_get_temperature(uint8_t *temp)
{
	float t = 0;

//	Temperature MCU[1 byte], -128 ~ 127
//	Temperature RF IC[1 byte], -128 ~ 127
//	Temperature PM IC[1 byte], -128 ~ 127

	t = get_mcu_temperature();
	temp[0] = (uint8_t)(int8_t)t;
	t = get_tef810x_temperature();
	temp[1] = (uint8_t)(int8_t)t;
	t = get_fs8x_tempature();
	temp[2] = (uint8_t)(int8_t)t;

	return RES_SUCCESS;
}

static void rmtp_spt_calib_cb(void *data)
{
	target_p tg = (target_p)data;
	float vangle;
	
	if (tg) {
//		LOG("[RMTP] calibration target: a=%.2f, r=%d, v=%d, m=%u\n", DEGREE_OF_RADIAN(aoaidx_asin(tg->aoaidx)), tg->range, tg->velocity, tg->mag);
		vangle=(180*asin((float)(tg->vangle)/716.04))/PI;
		PRINTF("[RMTP] calibration target: a=%.2f, r=%.2f, v=%.2f, m=%.2f h=%d , va=%.2f\n", DEGREE_OF_RADIAN(aoaidx_asin(tg->aoaidx)), (float)tg->range/100, (float)tg->velocity/100, SPT_LOG2DB(tg->mag_log2), tg->vangle,vangle);
		calib_cb(RES_SUCCESS, DEGREE_OF_RADIAN(aoaidx_asin(tg->aoaidx)), (float)tg->range/100, (float)tg->velocity/100, SPT_LOG2DB(tg->mag_log2), vangle);
	} else {
		LOG("[RMTP] calibration callback failed\n");
		calib_cb(RES_ERROR, 0.0, 0.0, 0.0, 0.0,0.0);
	}
	MEAS_MOD_WR = MEAS_MOD_TRACK;

	return;
}

int rmtp_calibration_control(float range, int16_t angle, target_cb cb)
{
	uint8_t res;
    float temp;
	calib_cb = cb;
	MEAS_MOD_WR = MEAS_MOD_TRACK;
//	MEAS_FLAGS_WR = 0;

    temp=frame_get_rngs_long_start();
    if(range<=temp){
       if((range-0.5)>=1){
           frame_set_rngs_long_start(range-0.5,0);
       }else{
           frame_set_rngs_long_start(1,0);
       }
    }
	
	res = coefs_calib_ranged_measurement((float)angle,range, rmtp_spt_calib_cb);
	if (res != MEAS_ST_READY) {
		return RES_ERROR;
	}

    set_tef810x_production_mode(kPRODUCTION_MODE);
	return RES_SUCCESS;
}

static void rmtp_spt_doppler_cb(void *data)
{
	if (data) {
		target_group_p tgg = (target_group_p)data;
		LOG("[RMTP] doppler callback ok\n");
		doppler_data_cb(RES_SUCCESS, (uint8_t *)tgg->targets);
	} else {
		LOG("[RMTP] doppler callback failed\n");
		doppler_data_cb(RES_ERROR, NULL);
	}
	
	return;
}



int rmtp_doppler_control(uint8_t index, float range, doppler_cb cb)
{
	uint8_t res;
	uint8_t temp;
	uint8_t id;

	doppler_data_cb = cb;
	if(index < 2 )      //[0:short, 1:long]
	{ // short, long
		res = spt_doppler_get(index, range, rmtp_spt_doppler_cb);
	} 
	else if (index < 5) //[2:Tx1,  3:Tx2,  4:Tx3] 
	{ 
		temp=index-2;
		temp=rmtp_tef810x_txid_to_profile(temp);
		if(temp==0xff)
		{
		    return RES_PARAMETER_ERROR;
		    //temp=2;
		}    
		id=spt_profileId_to_SptContextsId(temp);
		res = spt_doppler_get_by_tx_channel(id, range, rmtp_spt_doppler_cb);
	}
	else
	{
	    return RES_PARAMETER_ERROR;
	}
	
	
	if (res != MEAS_ST_READY) {
		LOG("[RMTP] doppler control failed\n");
		return RES_CMD_PROCESS_ERR;
	}

	return RES_SUCCESS;
}


int rmtp_get_doppler_data(uint8_t blockId, uint8_t *data, uint8_t *doppler)
{
	uint8_t *ptr = NULL;
	uint8_t offset;
    float vangle;
    
    MEAS_MOD_WR = MEAS_MOD_TRACK;
    
	if ((data == NULL) || (doppler == NULL)) {
		return RES_CMD_PROCESS_ERR;
	}

    vangle=(180*asin((float)(((target_p)doppler)->vangle)/716.04))/PI;
    
	//Total 72 Bytes, 15 Blocks
	if (blockId == 0) {
		float angle = DEGREE_OF_RADIAN(aoaidx_asin(((target_p)doppler)->aoaidx));
		//offset = offsetof(target_t, aoaidx);
		//ptr = ((uint8_t *)doppler) + offset;
		memcpy(data, &angle, 4);
//		angle = ((target_p)doppler)->vangle;
		//offset = offsetof(target_t, vangle);
		//ptr = ((uint8_t *)doppler) + offset;
		memcpy(data + 4, &vangle, 1);
	} else if (blockId == 1) {
//		float vangle = ((target_p)doppler)->vangle;
		ptr = ((uint8_t*)&vangle) + 1;
		//ptr = ((uint8_t *)doppler) + offset;
		memcpy(data, ptr, 3);
		offset = offsetof(target_t, cmplx);
		ptr = ((uint8_t *)doppler) + offset;
		memcpy(data + 3, ptr, 2);
	} else if (blockId <= 14) {
		offset = offsetof(target_t, cmplx) + 2 + (blockId - 2) * 5;
		ptr = ((uint8_t *)doppler) + offset;
		if (blockId == 14) {
			memcpy(data, ptr, 2);
		} else {
			memcpy(data, ptr, 5);
		}
	} else {
		return RES_PARAMETER_ERROR;
	}

	return RES_SUCCESS;
}

static void rmtp_measurement_cb(void *data)
{
	if (data) {
		target_p tg = (target_p)data;
		LOG("[RMTP] measurement callback ok\n");
		measure_data_cb(RES_SUCCESS, (uint8_t *)tg);
	} else {
		LOG("[RMTP] measurement callback failed\n");
		measure_data_cb(RES_ERROR, NULL);
	}

	return;
}

int rmtp_measurement_control(uint8_t index, float range, measure_cb cb)
{
	uint8_t res;

	if (index > 2) {
		return RES_PARAMETER_ERROR;
	}
	measure_data_cb = cb;
	res = frame_measurements_get_by_rng(index, range, rmtp_measurement_cb);
	if (res != MEAS_ST_READY) {
		LOG("[RMTP] measurement control failed\n");
		return RES_CMD_PROCESS_ERR;
	}

	return RES_SUCCESS;
}

int rmtp_get_measurement_data(uint8_t blockId, uint8_t *data, uint8_t *measure)
{
	uint8_t *ptr = NULL;
	float angle = (float)DEGREE_OF_RADIAN(aoaidx_asin(((target_p)measure)->aoaidx));
	float range = (float)((target_p)measure)->range / 100;			// divide 100 for precision
	float velocity = (float)((target_p)measure)->velocity / 100;	// divide 100 for precision
	float mag = (float)SPT_LOG2DB(((target_p)measure)->mag_log2);
	float vangle=(180*asin((float)(((target_p)measure)->vangle)/716.04))/PI;
	
	if ((data == NULL) || (measure == NULL)) {
		return RES_CMD_PROCESS_ERR;
	}
	// Total 20 Bytes, 4 Blocks
	if (blockId == 0) {
		ptr = ((uint8_t *)&angle);
		memcpy(data, ptr, 4);
        ptr = ((uint8_t *)&range);
        memcpy(data + 4, ptr, 1);
	} else if (blockId == 1) {
		ptr = ((uint8_t *)&range) + 1;
		memcpy(data, ptr, 3);
		ptr = ((uint8_t *)&velocity);
        memcpy(data + 3, ptr, 2);
	} else if (blockId == 2) {
		ptr = ((uint8_t *)&velocity) + 2;
		memcpy(data, ptr, 2);
		ptr = ((uint8_t *)&mag);
        memcpy(data + 2, ptr, 3);
	} else if (blockId == 3) {
		ptr = ((uint8_t *)&mag) + 3;
		memcpy(data, ptr, 1);
		ptr = ((uint8_t *)&vangle);
        memcpy(data + 1, ptr, 4);
        PRINTF("[RMTP] measure data: a:%.2f r:%.2f v:%.2f m:%.2f va:%.2f\n", angle, range, velocity, mag, vangle);
	} else {
		return RES_PARAMETER_ERROR;
	}
	return RES_SUCCESS;
}

static void rmtp_imu_calib_selftest_cb(int res)
{
	imu_calib_selftest_res_cb((uint8_t)res);

	return;
}

int rmtp_imu_calib_selftest_control(imu_calib_selftest_cb cb)
{
	uint8_t res;

	imu_calib_selftest_res_cb = cb;
	res = imu_self_test_by_RMTP(rmtp_imu_calib_selftest_cb);
	if (res != RES_SUCCESS) {
		res = RES_CMD_UNSUPPORTED;
	}

	return res;
}

static void rmtp_imu_calib_static_cb(imu_calib_result_p res)
{
	imu_calib_static_res_cb((uint8_t)res->result, (uint8_t *)&res->calib_temp);

	return;
}

int rmtp_imu_calib_static_control(imu_calib_static_cb cb)
{
	uint8_t res;

	imu_calib_static_res_cb = cb;
	res = ism330dlc_self_calibration_by_RMTP(rmtp_imu_calib_static_cb);
	if (res != RES_SUCCESS) {
		res = RES_CMD_UNSUPPORTED;
	}

	return res;
}

//int rmtp_get_imu_calib_data(uint8_t blockId, uint8_t *data)
//{
//	uint8_t *value = NULL;
//	ism330dlc_info_p info = NULL;
//
//	info = ism330dlc_get_IMU_info();
//	if (info == NULL) {
//		return RES_CMD_PROCESS_ERR;
//	}
//	if (blockId == 0) {
//		data[0] = info->zero_g_mg[Xaxis];
//		data[1] = info->zero_g_mg[Yaxis];
//		data[2] = info->zero_g_mg[Zaxis];
//		value = (uint8_t *)&info->zero_rate_level_mdps[Pitchaxis];
//		data[3] = value[0];
//		data[4] = value[1];
//	} else if (blockId == 1) {
//		value = (uint8_t *)&info->zero_rate_level_mdps[Pitchaxis];
//		data[0] = value[2];
//		data[1] = value[3];
//		value =  (uint8_t *)&info->zero_rate_level_mdps[Yawaxis];
//		data[2] = value[0];
//		data[3] = value[1];
//		data[4] = value[2];
//	} else if (blockId == 2) {
//		value = (uint8_t *)&info->zero_rate_level_mdps[Yawaxis];
//		data[0] = value[3];
//		value = (uint8_t *)&info->zero_rate_level_mdps[Rollaxis];
//		data[1] = value[0];
//		data[2] = value[1];
//		data[3] = value[2];
//		data[4] = value[3];
//	} else if (blockId == 3) {
//		data[0] = info->calib_temp;
//		data[1] = 0;
//		data[2] = 0;
//		data[3] = 0;
//		data[4] = 0;
//	} else if (blockId != BLOCK_ID_DONE) {
//		return RES_PARAMETER_ERROR;
//	}
//
//	return RES_SUCCESS;
//}

//int rmtp_set_imu_calib_data(uint8_t blockId, uint8_t *data)
//{
//	uint8_t *value = NULL;
//	ism330dlc_info_p info = NULL;
//
//	info = ism330dlc_get_IMU_info();
//	if (info == NULL) {
//		return RES_CMD_PROCESS_ERR;
//	}
//	if (blockId == 0) {
//		info->zero_g_mg[Xaxis] = data[0];
//		info->zero_g_mg[Yaxis] = data[1];
//		info->zero_g_mg[Zaxis] = data[2];
//		value = (uint8_t *)&info->zero_rate_level_mdps[Pitchaxis];
//		value[0] = data[3];
//		value[1] = data[4];
//	} else if (blockId == 1) {
//		value =  (uint8_t *)&info->zero_rate_level_mdps[Pitchaxis];
//		value[2] = data[0];
//		value[3] = data[1];
//		value = (uint8_t *)&info->zero_rate_level_mdps[Yawaxis];
//		value[0] = data[2];
//		value[1] = data[3];
//		value[2] = data[4];
//	} else if (blockId == 2) {
//		value = (uint8_t *)&info->zero_rate_level_mdps[Yawaxis];
//		value[3] = data[0];
//		value = (uint8_t *)&info->zero_rate_level_mdps[Rollaxis];
//		value[0] = data[1];
//		value[1] = data[2];
//		value[2] = data[3];
//		value[3] = data[4];
//	} else if (blockId == 3) {
//		info->calib_temp = data[0];
//	} else if (blockId != BLOCK_ID_DONE) {
//		return RES_PARAMETER_ERROR;
//	}
//	ism330dlc_set_IMU_calib_value(info);
//
//	return RES_SUCCESS;
//}

static void rmtp_spt_txrx_done_cb(void *data)
{
	MEAS_MOD_WR = MEAS_MOD_TRACK;
	rf_received_cb(rf_received_addr, RF_RX_DATA_SIZE);
	return;
}

int rmtp_rf_transmit_signal(uint8_t txid, rf_signal_received_cb cb)
{
	MEAS_MOD_WR = MEAS_MOD_RAW;
	rf_received_cb = cb;
	rf_received_addr = spt_txrx_test((int)txid, rmtp_spt_txrx_done_cb);
	return RF_RX_DATA_SIZE;
}


#if RMTP_NOISE_BASE
int rmtp_get_noise_base(uint8_t sampleTimes, uint8_t *data)
{
	uint8_t res;
	float noise[3][4] = {{0, 0, 0, 0}, {0, 0, 0, 0},{0, 0, 0, 0}};
	res = spt_noise_base_get(sampleTimes, noise);
	if (res != MEAS_ST_READY) {
		return RES_CMD_PROCESS_ERR;
	}
	memcpy(data, (uint8_t *)noise, sizeof(noise));
	return RES_SUCCESS;
}
#endif

int rmtp_get_rf_ic_register(uint8_t moduleAddr, uint16_t regAddr, uint8_t *data)
{
	uint32_t value;
	
	value = tef_reg_read(moduleAddr, regAddr);
	memcpy(data, &value, sizeof(uint32_t));

	return RES_SUCCESS;
}

int rmtp_set_rf_ic_register(uint8_t moduleAddr, uint16_t regAddr, uint32_t value)
{
	tef_reg_write(moduleAddr, regAddr, value);
	return RES_SUCCESS;
}

int rmtp_get_rf_ic_frequency(uint8_t pid, uint8_t *data)
{
	bool_t res;
	rmtp_rf_profile_gain_info_t profile_info;
	
	if (pid >= 4) {
		return RES_PARAMETER_ERROR;
	}
	res = rmtp_get_rf_profile_gain_info(pid, &profile_info);
	if (res == FALSE) {
		return RES_CMD_PROCESS_ERR;
	} else {
		memcpy(data, &profile_info.center_freq, sizeof(uint16_t));
		memcpy(data + 2, &profile_info.hpf, sizeof(uint16_t));
		memcpy(data + 4, &profile_info.lpf, sizeof(uint16_t));
	}
    set_tef810x_production_mode(kPRODUCTION_MODE);
	return RES_SUCCESS;
}

int rmtp_set_rf_ic_frequency(uint8_t pid, uint16_t value)
{
    bool_t res;
	rmtp_rf_profile_gain_info_t profile_info;
	
	if (pid >= 4) {
		return RES_PARAMETER_ERROR;
	}
	res = rmtp_get_rf_profile_gain_info(pid, &profile_info);
	if (res == FALSE) {
		return RES_CMD_PROCESS_ERR;
	} else {
	    profile_info.hpf=value;
		res = rmtp_set_rf_profile_gain_setting(pid, &profile_info);
		if (res == FALSE) {
			return RES_CMD_PROCESS_ERR;
		}
	}
	set_tef810x_production_mode(kPRODUCTION_MODE);
	return RES_SUCCESS;
}

int rmtp_get_rf_ic_operational_state(uint8_t txid, uint8_t *data)
{
	uint8_t profileId;
	
	if(txid>=3)
	{
	    return RES_PARAMETER_ERROR;
	}
	    
	profileId=rmtp_tef810x_txid_to_profile(txid);
	if (profileId >= 4) {
		data[0] = 0;
	}
	else
	{
	    data[0] = 1;
	}

	return RES_SUCCESS;
}

int rmtp_get_rf_ic_tx_gain(uint8_t pid, uint8_t *data)
{
	bool_t res;
	rmtp_rf_profile_gain_info_t profile_info;

	if (pid >= 4) {
		return RES_PARAMETER_ERROR;
	}
	res = rmtp_get_rf_profile_gain_info(pid, &profile_info);
	if (res == FALSE) {
		return RES_CMD_PROCESS_ERR;
	} else {
        data[1] = profile_info.txgain[data[0]];
	}

	return RES_SUCCESS;
}

int rmtp_set_rf_ic_tx_gain(uint8_t pid, uint8_t *data)
{
	bool_t res;
	rmtp_rf_profile_gain_info_t profile_info;
			
	if (pid >= 4) {
		return RES_PARAMETER_ERROR;
	}
	res = rmtp_get_rf_profile_gain_info(pid, &profile_info);
	if (res == FALSE) {
		return RES_CMD_PROCESS_ERR;
	} else {
        profile_info.txgain[data[0]]=data[1];
		res = rmtp_set_rf_profile_gain_setting(pid, &profile_info);
		if (res == FALSE) {
			return RES_CMD_PROCESS_ERR;
		}
	}

	return RES_SUCCESS;
}

int rmtp_get_rf_ic_rx_gain(uint8_t pid, uint8_t *data)
{
	bool_t res;
	rmtp_rf_profile_gain_info_t profile_info;
			
	if (pid >= 4) {
		return RES_PARAMETER_ERROR;
	}	
	res = rmtp_get_rf_profile_gain_info(pid, &profile_info);
	if (res == FALSE) {
		return RES_CMD_PROCESS_ERR;
	} else {
		data[0] = profile_info.rxgain[0];
		data[1] = profile_info.rxgain[1];
		data[2] = profile_info.rxgain[2];
		data[3] = profile_info.rxgain[3];
	}
	
	return RES_SUCCESS;
}

int rmtp_set_rf_ic_rx_gain(uint8_t pid, uint8_t *data)
{
	bool_t res;
	rmtp_rf_profile_gain_info_t profile_info;
			
	if (pid >= 4) {
		return RES_PARAMETER_ERROR;
	}	
	res = rmtp_get_rf_profile_gain_info(pid, &profile_info);
	if (res == FALSE) {
		return RES_CMD_PROCESS_ERR;
	} else {
		profile_info.rxgain[0] = data[0];
		profile_info.rxgain[1] = data[1];
		profile_info.rxgain[2] = data[2];
		profile_info.rxgain[3] = data[3];
		res = rmtp_set_rf_profile_gain_setting(pid, &profile_info);
		if (res == FALSE) {
			return RES_CMD_PROCESS_ERR;
		}
	}

	return RES_SUCCESS;
}

int rmtp_get_rf_ic_cw_tx_gain(uint8_t *data)
{
	bool_t res;
	rmtp_rf_profile_gain_info_t profile_info;

	res = rmtp_get_rf_profile_gain_info(0, &profile_info);
	if (res == FALSE) {
		return RES_CMD_PROCESS_ERR;
	} else {
		data[0] = profile_info.txgain[0];
		data[1] = profile_info.txgain[1];
		data[2] = profile_info.txgain[2];
	}

	return RES_SUCCESS;
}

int rmtp_set_rf_ic_cw_tx_gain(uint8_t *data)
{
	bool_t res;
	rmtp_rf_profile_gain_info_t profile_info;
			
	res = rmtp_get_rf_profile_gain_info(0, &profile_info);
	if (res == FALSE) {
		return RES_CMD_PROCESS_ERR;
	} else {
		profile_info.txgain[0] = data[0];
		profile_info.txgain[1] = data[1];
		profile_info.txgain[2] = data[2];
		res = rmtp_set_rf_profile_gain_setting(0, &profile_info);
		if (res == FALSE) {
			return RES_CMD_PROCESS_ERR;
		}
	}

	return RES_SUCCESS;
}


int rmtp_get_spt_aoa_shift(uint8_t id, uint8_t *data)
{
	float aoa_shift;
    int16_t aoa_shift_temp;
    
	if (id > 1) {
		return RES_PARAMETER_ERROR;
	}
	aoa_shift=frame_get_aoa_shift(id);
	aoa_shift=aoa_shift*100;
	aoa_shift_temp=(int16_t)aoa_shift;
	data[0]=id;
	memcpy(&data[1],&aoa_shift_temp,sizeof(int16_t));
	return RES_SUCCESS;
}

int rmtp_set_spt_aoa_shift(uint8_t id, int16_t data)
{
	float aoa_shift;
	aoa_shift=(float)data;
	aoa_shift=aoa_shift/100;
	if(id>1){//||aoa_shift>90||aoa_shift<-90){
		return RES_PARAMETER_ERROR;
	}
	else
	{    
	    frame_set_aoa_shift(id,aoa_shift);
	    return RES_SUCCESS;
	}
}

int rmtp_get_fcw_warning_flags(uint8_t *value)
{
	return tracking_fcw_warning_flags_get(value);

}

int rmtp_set_fcw_warning_flags(uint8_t *value)
{
	return tracking_fcw_warning_flags_set(value);

}

int rmtp_get_fcw_warning_speed_level(uint8_t level, uint8_t *value)
{
	return tracking_fcw_warning_speed_level_get(level, (float *)value);

}

int rmtp_set_fcw_warning_speed_level(uint8_t level, uint8_t *value)
{
	float speed;
	memcpy(&speed, value, sizeof(float));
	return tracking_fcw_warning_speed_level_set(level, speed);

}

int rmtp_get_fcw_warning_ttc_level(uint8_t type, uint8_t level, uint8_t *value)
{
	return tracking_fcw_warning_speed_ttc_get(type, level, (float *)value);

}

int rmtp_set_fcw_warning_ttc_level(uint8_t type, uint8_t level, uint8_t *value)
{
	float ttc;
	memcpy(&ttc, value, sizeof(float));
	return tracking_fcw_warning_speed_ttc_set(type, level, ttc);
}


int rmtp_get_field_of_view_width(uint8_t *value)
{
	float width;

	width = tracking_field_of_view_width_get();
	memcpy(value, &width, sizeof(float));

	return RES_SUCCESS;
}

int rmtp_set_field_of_view_width(uint8_t *value)
{
	float width;

	memcpy(&width, value, sizeof(float));
	tracking_field_of_view_width_set(width);

	return RES_SUCCESS;
}

int rmtp_get_field_of_view_range(uint8_t *value)
{
	float range;

	range = tracking_field_of_view_range_get();
	memcpy(value, &range, sizeof(float));

	return RES_SUCCESS;
}

int rmtp_set_field_of_view_range(uint8_t *value)
{
	float range;

	memcpy(&range, value, sizeof(float));
	tracking_field_of_view_range_set(range);

	return RES_SUCCESS;
}

int rmtp_get_field_of_view_angle(uint8_t *value)
{
	float angle;

	angle = tracking_field_of_view_angle_get();
	memcpy(value, &angle, sizeof(float));

	return RES_SUCCESS;
}

int rmtp_set_field_of_view_angle(uint8_t *value)
{
	float angle;

	memcpy(&angle, value, sizeof(float));
	tracking_field_of_view_angle_set(angle);

	return RES_SUCCESS;
}

int rmtp_get_view_zone_value(uint8_t index, uint8_t *value)
{
	float zone;

	if (index >= 4) {
		return RES_ERROR;
	}
	zone = tracking_view_zone_value_get(index);
	memcpy(value, &zone, sizeof(float));

	return RES_SUCCESS;
}

int rmtp_set_view_zone_value(uint8_t index, uint8_t *value)
{
	float zone;

	if (index >= 4) {
		return RES_ERROR;
	}
	memcpy(&zone, value, sizeof(float));
	tracking_view_zone_value_set(index, zone);

	return RES_SUCCESS;
}

int rmtp_get_aoa_shift(uint8_t *value)
{
	float aoa;

	aoa = tracking_aoa_shift_get();
	memcpy(value, &aoa, sizeof(float));

	return RES_SUCCESS;
}

int rmtp_set_aoa_shift(uint8_t *value)
{
	int res;
	float aoa;

	memcpy(&aoa, value, sizeof(float));
	res = tracking_aoa_shift_set(aoa);
	if (res == 1) {
		return RES_PARAMETER_ERROR;
	}
	
	return RES_SUCCESS;
}

int rmtp_get_lateral_shift(uint8_t *value)
{
	float shift;

	shift = tracking_lateral_shift_get();
	memcpy(value, &shift, sizeof(float));

	return RES_SUCCESS;
}

int rmtp_set_lateral_shift(uint8_t *value)
{
	float shift;

	memcpy(&shift, value, sizeof(float));
	tracking_lateral_shift_set(shift);

	return RES_SUCCESS;
}

int rmtp_get_longitudinal_shift(uint8_t *value)
{
	float shift;

	shift = tracking_longitudinal_shift_get();
	memcpy(value, &shift, sizeof(float));

	return RES_SUCCESS;
}

int rmtp_set_longitudinal_shift(uint8_t *value)
{
	float shift;

	memcpy(&shift, value, sizeof(float));
	tracking_longitudinal_shift_set(shift);

	return RES_SUCCESS;
}

int rmtp_get_pars_id_list(uint8_t *data, uint16_t *size)
{
	int num = 0;

	num = pars_id_list((uint32_t *)data);
	*size = num * 4;

	return RES_SUCCESS;
}

uint8_t* rmtp_get_pars_info(int32_t id, uint16_t *ver, uint16_t *size)
{	
	uint8_t *data = NULL;

	*ver = 0;
	*size = 0;
	data = pars_info_get(id, ver, size);
	
	return data;
}

int rmtp_set_pars_info(uint32_t id, uint8_t *data, uint16_t size)
{	
	int res;

	res = pars_info_set(id, data, size);
	if (res != 0) {
		return RES_PARAMETER_ERROR;
	}

	return RES_SUCCESS;
}

uint8_t* rmtp_get_pars_json_data(uint32_t id, uint16_t *size)
{
	int len = 0;
	uint8_t *data = NULL;
	
	*size = 0;
	data = (uint8_t *)pars_json_get(id, (int *)&len);
	if (data != NULL) {
		*size = len;
	}
	
	return data;
}

uint8_t * rmtp_get_all_pars_json_data (uint16_t *size)
{
    uint8_t * data_ptr=(uint8_t*)spt_work_space_get();
    *size = pars_all_json_data_get((char*)data_ptr);
    return data_ptr;
}

void rmtp_lock_frequency_mode_set(uint16_t frequency, uint8_t tx, uint8_t time)
{
    chg_tef810x_lock_freq_cb(time, tx+1, frequency/10);	//RMTP Tx=>0~2 ; chg_tef810x_lock_freq_cb() Tx=>1~3
}

void rmtp_lock_frequency_mode_done(uint8_t netID)
{
    LOG("[RMTP] RF_CM_mode_done\n");
    rmtp_send_report_message(netID, OBJ_ID_SIGNAL_PROCESS, ATTR_ID_2, NULL, 0);
}

uint8_t rmtp_get_calib_mode(void)
{
    return calibration_mode;
}

int rmtp_set_calib_mode(uint8_t mode)
{
    switch(mode)
    {
        case 0:
            set_tef810x_production_mode(kNORMAL_MODE);
            re_init_TEF810x_cb(0);      //normal mode
            break;
        
        case 1:    
            set_tef810x_production_mode(kPRODUCTION_MODE);
            tef_zero_calibration(0, 0);     //calibration mode
            break;
            
        case 2:
            set_tef810x_production_mode(kPRODUCTION_MODE);
            re_init_TEF810x_cb(0);      //measurement mode
            chg_tef810x_filter_cb(0,100,15);    //profile-0,HPF=100Khz,LPF=15Mhz
            chg_tef810x_filter_cb(1,100,15);    //profile-1,HPF=100Khz,LPF=15Mhz
            chg_tef810x_filter_cb(2,100,15);    //profile-0,HPF=100Khz,LPF=15Mhz
            chg_tef810x_filter_cb(3,100,15);    //profile-1,HPF=100Khz,LPF=15Mhz
            re_init_TEF810x_cb(1); 
            frame_aoa_measument_mode();
            break;
         
        default:
            return RES_CMD_UNSUPPORTED;
    }        
    
    calibration_mode=mode;
    return RES_SUCCESS;

}

int rmtp_set_calib_bandwidth(uint16_t bandwidth)
{
	if(set_calibration_bandwidth(bandwidth) != 0)
		return RES_PARAMETER_ERROR;
	return RES_SUCCESS;
}

int rmtp_get_calib_bandwidth(uint16_t* bandwidth)
{
	if(bandwidth == NULL)
		return RES_PARAMETER_ERROR;

	*bandwidth = get_calibration_bandwidth();
	return RES_SUCCESS;
}


void rmtp_save_calib_coef(void)
{
    coefs_data_p rmtp_coefs;
    void(*rmtp_coefs_pars_set)(void);
    
    coefs_rmtp_pars_init(&rmtp_coefs,&rmtp_coefs_pars_set);
    rmtp_coefs_pars_set();
}

int rmtp_get_calib_coef(uint8_t blockId, uint8_t *data)
{
	uint8_t *ptr = NULL;
	uint8_t offset;
	coefs_data_p rmtp_coefs;
    void(*rmtp_coefs_pars_set)(void);

	coefs_rmtp_pars_init(&rmtp_coefs,&rmtp_coefs_pars_set);
	if ((data == NULL) || (rmtp_coefs == NULL)) {
		return RES_CMD_PROCESS_ERR;
	}

	//Total 128 Bytes, 26 Blocks
	if (blockId <= 25) {
		offset = offsetof(coefs_data_t, coefs);
		ptr = ((uint8_t *)rmtp_coefs) + offset + (blockId*5);
		if(blockId == 25) {
		    memcpy(data, ptr, 3);
		}else{
		    memcpy(data, ptr, 5);
		}
	} else {
		return RES_PARAMETER_ERROR;
	}

	return RES_SUCCESS;
}

int rmtp_set_calib_coef(uint8_t blockId, uint8_t *data)
{
    uint8_t *ptr = NULL;
	uint8_t offset;
    coefs_data_p rmtp_coefs;
    void(*rmtp_coefs_pars_set)(void);
    
    coefs_rmtp_pars_init(&rmtp_coefs,&rmtp_coefs_pars_set);
	if ((data == NULL) || (rmtp_coefs == NULL)) {
		return RES_CMD_PROCESS_ERR;
	}
	//Total 128 Bytes, 26 Blocks
	if (blockId <= 25) {
		offset = offsetof(coefs_data_t, coefs);
		ptr = ((uint8_t *)rmtp_coefs) + offset + (blockId*5);
		if(blockId == 25) {
		    memcpy(ptr, data, 3);
		}else{
		    memcpy(ptr, data, 5);
		}
	} else {
		return RES_PARAMETER_ERROR;
	}

	return RES_SUCCESS;
	
}


int rmtp_set_configuration_reset(uint32_t *pars_id)
{
    pars_ctx_erase( *pars_id);
    
    return RES_SUCCESS;
}

int rmtp_get_Tx_High_Level(uint8_t TxId, uint8_t* retTxId, uint8_t* retTxHighLevel)
{
    if((TxId>=3)||(retTxId==NULL)||(retTxHighLevel==NULL)){
        return RES_PARAMETER_ERROR;
    }
    (* retTxHighLevel)=rmtp_get_tx_high_level(TxId);    
    (* retTxId)=TxId;
    
    return RES_SUCCESS;
}

int rmtp_set_Tx_High_Level(uint8_t TxId, uint8_t TxGain, uint8_t* retTxId, uint8_t* retTxHighLevel)
{
    if((TxId>=3)||(retTxId==NULL)||(retTxHighLevel==NULL)){
        return RES_PARAMETER_ERROR;
    }
    if(rmtp_find_tx_high_level(TxId,TxGain)){
        return RES_CMD_PROCESS_ERR;
    }
    (* retTxHighLevel)=rmtp_get_tx_high_level(TxId);
    (* retTxId)=TxId;
    
    return RES_SUCCESS;
}

int rmtp_get_trkp(uint8_t Info_ID, uint8_t * res_data)
{
    res_data[0]=Info_ID;
    switch(Info_ID)
    {
        case 0x00:
            res_data[1]=(uint8_t)get_ditch_cover_v_phase_threshold();
            break;
        case 0x01:
            res_data[1]=(uint8_t)get_flyover_v_phase_threshold();
            break;   
        default:    
            return RES_PARAMETER_ERROR;
    }
    return RES_SUCCESS;
}

int rmtp_set_trkp(uint8_t Info_ID, uint8_t set_data)
{
    switch(Info_ID)
    {
        case 0x00:
            set_ditch_cover_v_phase_threshold((int8_t)set_data);
            break;
        case 0x01:
            set_flyover_v_phase_threshold((int8_t)set_data);
            break;   
        default:    
            return RES_PARAMETER_ERROR;
    }
    return RES_SUCCESS;
    
}

int rmtp_get_trk2(uint8_t Info_ID, uint8_t * res_data)
{
    float stationary;
    int16_t temp_int16;
    
    res_data[0]=Info_ID;
    switch(Info_ID)
    {
        case 0x00:
            get_trk2_uds_speed_makeup(0, 0, &stationary);
            temp_int16=(int16_t)(stationary*100);
            memcpy(&res_data[1],&temp_int16,2);
            break;
        default:    
            return RES_PARAMETER_ERROR;
    }
    return RES_SUCCESS;
    
}

int rmtp_set_trk2(uint8_t Info_ID, int16_t set_data)
{
    switch(Info_ID)
    {
        case 0x00:
            if((set_data>=0)&&(set_data<=500)){
                set_trk2_uds_speed_makeup(-1.0f, -1.0f, ((float)set_data)/100);
            }else{
                return RES_PARAMETER_ERROR;
            }
            break;
        default:    
            return RES_PARAMETER_ERROR;
    }
    return RES_SUCCESS;    
}

int rmtp_get_Vehp(uint8_t Info_ID, uint8_t * res_data)
{
    float speed_filter;
    int16_t temp_int16;
    
    res_data[0]=Info_ID;
    switch(Info_ID)
    {
        case 0x00:
            get_trk2_uds_speed_makeup(&speed_filter, 0, 0);
            temp_int16=(int16_t)(speed_filter*100);
            memcpy(&res_data[1],&temp_int16,2);
            break;
            
         case 0x01:
            get_trk2_uds_speed_makeup(0, &speed_filter, 0);   
            temp_int16=(int16_t)(speed_filter*100);
            memcpy(&res_data[1],&temp_int16,2);
            break;
        default:    
            return RES_PARAMETER_ERROR;
    }
    return RES_SUCCESS;
    
}

int rmtp_set_Vehp(uint8_t Info_ID, int16_t set_data)
{
    switch(Info_ID)
    {
        case 0x00:
            if((set_data>0)&&(set_data<=200)){
                set_trk2_uds_speed_makeup(((float)set_data)/100,-1.0f, -1.0f);
            }else{
                return RES_PARAMETER_ERROR;
            }
            break;
            
         case 0x01:
            if((set_data>=0)&&(set_data<=200)){
                set_trk2_uds_speed_makeup(-1.0f,((float)set_data)/100, -1.0f);
            }else{
                return RES_PARAMETER_ERROR;
            }
            break;    
        default:    
            return RES_PARAMETER_ERROR;
    }
    return RES_SUCCESS;    
}

int rmtp_get_can_baud_rate(uint8_t com_interface , uint8_t * br_mode_ptr)
{
    int16_t br;
    uint8_t dlc_enable;
    
#ifdef USING_CUBTEK_CAN_0   
    if(com_interface==0){ //CAN0
        br=get_can0_br();
        dlc_enable=get_can0_dlc_status();
    }else
#endif
        
    if(com_interface==1){ //CAN2
        br=get_can2_br();
        dlc_enable=get_can2_dlc_status();    
    }else{
        return RES_PARAMETER_ERROR;
    }
    
    if((br >= CAN_FD_500K_2M)&&(dlc_enable==1)){
        (*br_mode_ptr)=(uint8_t)(br+5);
    }else{
        (*br_mode_ptr)=(uint8_t)br;
    }
    return RES_SUCCESS;
}

int rmtp_set_can_baud_rate(uint8_t com_interface , uint8_t br_mode)
{
    int16_t br;
    uint8_t dlc_enable;
    
    if(br_mode<=8){
        dlc_enable=0;
        br=br_mode;
    }else
    if(br_mode<=13){
        dlc_enable=1;
        br=br_mode-5;
    }else{
        return RES_PARAMETER_ERROR;
    }

#ifdef USING_CUBTEK_CAN_0      
    if(com_interface==0){ //CAN0
        set_can0_br_dlc((uint8_t)br,dlc_enable);
    }else
#endif        
    if(com_interface==1){ //CAN2
        set_can2_br_dlc((uint8_t)br,dlc_enable);
    }else{
        return RES_PARAMETER_ERROR;
    }
    
    return RES_SUCCESS;
}

