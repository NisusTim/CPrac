/*
 * ism330dlc_reg_app.c
 *
 *  Created on: 2019/1/28
 *      Author: user
 */

#include "sys_shared.h"


void ism330dlc_console_read_reg_cb(uint8_t task_index)
{
	uint8_t reg_data,reg;
	i2c1_get_task_reg(&reg,task_index);
	i2c1_copy_data_from_task(&reg_data,task_index);
	PRINTF("ISM330DLC Reg[%02xh] = %02Xh\n", reg, reg_data);
}

int32_t ism330dlc_console_read_reg(uint8_t reg)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	i2c1_info.block = 0;
	i2c1_info.len = 1;
	i2c1_info.reg = reg;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = (event_proc_p)ism330dlc_console_read_reg_cb;
	i2c1_info.name = "console_read";
	mm_error = ism330dlc_read_reg(i2c1_info);
  	return mm_error;
}

void ism330dlc_console_write_reg_cb(uint8_t task_index)
{
	uint8_t reg_data,reg;
	i2c1_get_task_reg(&reg,task_index);
	i2c1_copy_data_from_task(&reg_data,task_index);
	ism330dlc_console_read_reg(reg);
}

int32_t ism330dlc_console_write_reg(uint8_t reg,uint8_t reg_data)
{
	ism330dlc_reg_t regData;
	int32_t mm_error;
	regData.byte = reg_data;
	i2c1_input_info_t i2c1_info = {};
	i2c1_info.block = 0;
	i2c1_info.len = 1;
	i2c1_info.reg = reg;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = &regData.byte;
	i2c1_info.callback = (event_proc_p)ism330dlc_console_write_reg_cb;
	i2c1_info.name = "console_write";
	mm_error = ism330dlc_write_reg(i2c1_info);
  	return mm_error;
}

void ism330dlc_console_reg_dump_cb(uint8_t task_index)
{
	uint8_t i,len,reg_data[0x76];
	i2c1_get_task_rx_len(&len,task_index);
	i2c1_copy_data_from_task(&reg_data[0],task_index);
	PRINTF("Read ISM330DLC registers...\n");
	PRINTF("===========================\n");
	for(i=0; i<len; i++)
	{
		if(i%0x10 == 0)
			PRINTF("0x%02X: ", i);
		PRINTF("%02X ", reg_data[i]);
		if((i+1)%0x10 == 0)
		{
			PRINTF("\n");
		}
	}
	PRINTF("\n===========================\n");
}

int32_t ism330dlc_console_reg_dump(uint8_t len)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	i2c1_info.block = 0;
	i2c1_info.len = len;
	i2c1_info.reg = 0;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = (event_proc_p)ism330dlc_console_reg_dump_cb;
	i2c1_info.name = "console_read_dump";
	mm_error = ism330dlc_read_reg(i2c1_info);
  	return mm_error;
}



int32_t ism330dlc_device_id_get(event_proc_p cb)
{
	i2c1_input_info_t i2c1_info = {};
	i2c1_info.block = 0;
	i2c1_info.callback = cb;
	i2c1_info.len = 1;
	i2c1_info.name = "who_am_i";
	i2c1_info.reg = ISM330DLC_WHO_AM_I;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	return ism330dlc_read_reg(i2c1_info);
}

//===================================================================//
/**
  * ism330dlc_reset_set   */


int32_t ism330dlc_reset_status_get(uint8_t* bufp)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg;

	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ISM330DLC_CTRL3_C;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = NULL;
	i2c1_info.name = "read_reset_status";
	mm_error = ism330dlc_read_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);
	*bufp = reg.byte;
	return mm_error;
}

int32_t ism330dlc_reset_set(uint8_t val)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg = {};

	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ISM330DLC_CTRL3_C;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = NULL;
	i2c1_info.name = "reset_set";


	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);
	reg.ctrl3_c.sw_reset = val;
	i2c1_info.buf_p = &reg.byte;

	mm_error |= ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

  return mm_error;
}
//===================================================================//

//===================================================================//
/**
  * ism330dlc_block_data_update_set
  */

int32_t ism330dlc_block_data_update_set(uint8_t val)
{
	int32_t mm_error;
	ism330dlc_reg_t reg;
	uint8_t task_index;
	i2c1_input_info_t i2c1_info = {};
	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ISM330DLC_CTRL3_C;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = 0;
	i2c1_info.name = "block_data_update_set";

	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);
	reg.ctrl3_c.bdu = val;
	i2c1_info.buf_p = &reg.byte;

	mm_error |= ism330dlc_write_reg(i2c1_info);
	//if block = 1,need use "i2c1_get_block_task_index" and "i2c1_copy_data_from_task" clear data
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

  return mm_error;
}
//===================================================================//

//===================================================================//
/**
  * ism330dlc_xl_data_rate_set =>
  */

int32_t ism330dlc_xl_data_rate_set(ism330dlc_odr_xl_t val)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg;
	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ISM330DLC_CTRL1_XL;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = 0;
	i2c1_info.name = "xl_data_rate_set";

	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);
	reg.ctrl1_xl.odr_xl = val;
	i2c1_info.buf_p = &reg.byte;

	mm_error |= ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	return mm_error;
}

//===================================================================//
//===================================================================//
/**
  * ism330dlc_gy_data_rate_set =>
  */

int32_t ism330dlc_gy_data_rate_set(ism330dlc_odr_g_t val)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg;

	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ISM330DLC_CTRL2_G;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = 0;
	i2c1_info.name = "gy_data_rate_set";
	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);
	reg.ctrl2_g.odr_g = val;
	i2c1_info.buf_p = &reg.byte;

	task_index |= ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	return mm_error;
}
//===================================================================//
//===================================================================//
/**
  * ism330dlc_xl_full_scale_set  */


int32_t ism330dlc_xl_full_scale_set(ism330dlc_fs_xl_t val)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg;

	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ISM330DLC_CTRL1_XL;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = 0;
	i2c1_info.name = "xl_full_scale_set";
	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);
	reg.ctrl1_xl.fs_xl = val;
	i2c1_info.buf_p = &reg.byte;

	mm_error |= ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	return mm_error;
}

//===================================================================//
//===================================================================//
/**
  * ism330dlc_gy_full_scale_set
  */

int32_t ism330dlc_gy_full_scale_set(ism330dlc_fs_g_t val)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg;

	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ISM330DLC_CTRL2_G;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = NULL;
	i2c1_info.name = "gy_full_scale_set";

	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);
	reg.ctrl2_g.fs_g = val;
	i2c1_info.buf_p = &reg.byte;

	mm_error |= ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	return mm_error;
}

//===================================================================//

 /* ism330dlc_xl_filter_analog_set   */

int32_t ism330dlc_xl_filter_analog_set(ism330dlc_bw0_xl_t val)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg;
	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ISM330DLC_CTRL1_XL;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = NULL;
	i2c1_info.name = "xl_filter_analog_set";

	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);
	reg.ctrl1_xl.bw0_xl = val;
	i2c1_info.buf_p = &reg.byte;

	mm_error |= ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	return mm_error;
}

//===================================================================//
//===================================================================//
/**
  *
  * ism330dlc_xl_lp2_bandwidth_set  */

int32_t ism330dlc_xl_lp2_bandwidth_set(ism330dlc_input_composite_t val)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg;
	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ISM330DLC_CTRL8_XL;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = NULL;
	i2c1_info.name = "xl_lp2_bandwidth_set";


	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);
	reg.ctrl8_xl.input_composite = ( val & 0x10 ) >> 4;
	reg.ctrl8_xl.hpcf_xl = val & 0x03;
	reg.ctrl8_xl.lpf2_xl_en = 1;
	reg.ctrl8_xl.hp_slope_xl_en = 0;
	i2c1_info.buf_p = &reg.byte;

	mm_error |= ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	return mm_error;
}
//===================================================================//
//===================================================================//
//  * @addtogroup   gyroscope_filters_mode:1,2
//  * @brief   This section group all the functions concerning the filters
//  *          configuration that impact gyroscope mode 1, 2
//  *          (gyroscope on aux interface disable).
//  * @{
//  */
//
///**
//  * @brief  gy_band_pass: [set] Gyroscope low pass path bandwidth.
//  *                             Only Mode: 1, 2.
//  *
/**
  *
  * ism330dlc_gy_band_pass_set_part1  */


int32_t ism330dlc_gy_band_pass_set_part1(ism330dlc_lpf1_sel_g_t val)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg;
	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ISM330DLC_CTRL7_G;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = NULL;
	i2c1_info.name = "gy_band_pass_set_part1";

	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);
	reg.ctrl7_g.hpm_g  = ( val & 0x30 ) >> 4;
	reg.ctrl7_g.hp_en_g = ( val & 0x80 ) >> 7;
	i2c1_info.buf_p = &reg.byte;

	mm_error |= ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	return mm_error;
}
//===================================================================//
//===================================================================//
/**
  *
  * ism330dlc_gy_band_pass_set_part2  */


int32_t ism330dlc_gy_band_pass_set_part2(ism330dlc_lpf1_sel_g_t val)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg;

	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ISM330DLC_CTRL6_C;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = NULL;
	i2c1_info.name = "gy_band_pass_set_part2";

	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);
	reg.ctrl6_c.ftype  = val & 0x03;
	i2c1_info.buf_p = &reg.byte;

	mm_error |= ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);


	return mm_error;
}
//===================================================================//
//===================================================================//
/**
  *
  * ism330dlc_gy_band_pass_set_part3  */


int32_t ism330dlc_gy_band_pass_set_part3(ism330dlc_lpf1_sel_g_t val)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg;
	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ISM330DLC_CTRL4_C;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = NULL;
	i2c1_info.name = "gy_band_pass_set_part3";

	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);
	reg.ctrl4_c.lpf1_sel_g = ( val & 0x08 ) >> 3;
	i2c1_info.buf_p = &reg.byte;

	mm_error |= ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	return mm_error;
}
//===================================================================//
//===================================================================//
/**
  * ism330dlc_xl_usr_offset_set
  */

int32_t ism330dlc_xl_usr_offset_set(uint8_t *buff)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	i2c1_info.block = 1;
	i2c1_info.len = 3;
	i2c1_info.reg = ISM330DLC_X_OFS_USR;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = buff;
	i2c1_info.callback = NULL;
	i2c1_info.name = "xl_usr_offset_set";
	mm_error = ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(buff,task_index);
	return mm_error;
}

//===================================================================//
//===================================================================//
/**
  * ism330dlc_status_reg_get
  */
/*int32_t ism330dlc_status_reg_get(event_proc_p cb)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	i2c1_info.block = 0;
	i2c1_info.len = 1;
	i2c1_info.reg = ISM330DLC_STATUS_REG;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = cb;
	i2c1_info.name = "status_reg_get";

	mm_error = ism330dlc_read_reg(i2c1_info);
	return mm_error;
}*/

int32_t ism330dlc_status_reg_get_value(uint8_t *value)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;

	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ISM330DLC_STATUS_REG;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = 0;
	i2c1_info.name = "status_reg_get";

	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(value,task_index);

	return mm_error;
}

//===================================================================//
//===================================================================//
//  * @brief  acceleration_raw: [get] Linear acceleration output register.
//  *                                 The value is expressed as a 16-bit word
//  *                                 in two complement.

/**
  * ism330dlc_acceleration_raw_get
  */

/*int32_t ism330dlc_acceleration_raw_get(event_proc_p cb)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	i2c1_info.block = 0;
	i2c1_info.len = 6;
	i2c1_info.reg = ISM330DLC_OUTX_L_XL;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = cb;
	i2c1_info.name = "acc_raw_get";

	mm_error = ism330dlc_read_reg(i2c1_info);
	return mm_error;
}*/

int32_t ism330dlc_acceleration_raw_get_value(uint8_t *value)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	i2c1_info.block = 1;
	i2c1_info.len = 6;
	i2c1_info.reg = ISM330DLC_OUTX_L_XL;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = 0;
	i2c1_info.name = "acc_raw_get";

	mm_error = ism330dlc_read_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(value,task_index);

	return mm_error;
}

//===================================================================//
//  * @brief  angular_rate_raw: [get] Angular rate sensor. The value is
//  *                                 expressed as a 16-bit word in
//  *                                 two complement.

/**
  * ism330dlc_acceleration_raw_get
  */

/*int32_t ism330dlc_angular_rate_raw_get(event_proc_p cb)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	i2c1_info.block = 0;
	i2c1_info.len = 6;
	i2c1_info.reg = ISM330DLC_OUTX_L_G;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = cb;
	i2c1_info.name = "angular_rate_raw_get";

	mm_error = ism330dlc_read_reg(i2c1_info);
	return mm_error;
}*/

int32_t ism330dlc_angular_rate_raw_get_value(uint8_t *value)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;

	i2c1_info.block = 1;
	i2c1_info.len = 6;
	i2c1_info.reg = ISM330DLC_OUTX_L_G;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = 0;
	i2c1_info.name = "angular_rate_raw_get";

	mm_error = ism330dlc_read_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(value,task_index);

	return mm_error;
}

//===================================================================//
/**
  * ism330dlc_acceleration_raw_get
  */

/*int32_t ism330dlc_temperature_raw_get(event_proc_p cb)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	i2c1_info.block = 0;
	i2c1_info.len = 2;
	i2c1_info.reg = ISM330DLC_OUT_TEMP_L;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = cb;
	i2c1_info.name = "temperature_raw_get";

	mm_error = ism330dlc_read_reg(i2c1_info);
	return mm_error;
}*/

int32_t ism330dlc_temperature_raw_get_value(uint8_t *value)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;

	i2c1_info.block = 1;
	i2c1_info.len = 2;
	i2c1_info.reg = ISM330DLC_OUT_TEMP_L;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = 0;
	i2c1_info.name = "temperature_raw_get";

	mm_error = ism330dlc_read_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(value,task_index);
	return mm_error;
}

//===================================================================//
/**
  * ism330dlc_temp_gyro_xl_raw_get
  */

int32_t ism330dlc_temp_gyro_xl_raw_get(event_proc_p cb)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	i2c1_info.block = 0;
	i2c1_info.len = 19;
	i2c1_info.reg = ISM330DLC_WAKE_UP_SRC;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = cb;
	i2c1_info.name = "temp_gyro_xl_raw_get";

	mm_error = ism330dlc_read_reg(i2c1_info);
	return mm_error;
}

//===================================================================//
/**
  * ism330dlc_config_self_test
  */

int32_t ism330dlc_config_self_test(uint8_t *buff)
{
    int32_t mm_error;
    i2c1_input_info_t i2c1_info = {};
    uint8_t task_index;
    i2c1_info.block = 1;
    i2c1_info.len = 10;
    i2c1_info.reg = ISM330DLC_CTRL1_XL;
    i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
    i2c1_info.buf_p = buff;
    i2c1_info.callback = NULL;
    i2c1_info.name = "enable_imu_self_test";
    mm_error = ism330dlc_write_reg(i2c1_info);
    task_index = i2c1_get_block_task_index();
    i2c1_copy_data_from_task(buff,task_index);
    return mm_error;
}

//===================================================================//
/**
  * asm330lhh_set_duration_for_inactivity_detection
  */

int32_t asm330lhh_set_duration_for_inactivity_detection()
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg = {};

	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ASM330LHH_WAKE_UP_DUR;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = 0;
	i2c1_info.name = "set_duration_for_inactivity_detection";
	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	reg.wake_up_dur.ff_dur = 0;
	reg.wake_up_dur.wake_dur = 0;
	reg.wake_up_dur.wake_ths_w = 1;
	//if sleep_dur != 0, and ODR_XL = 208Hz, 1 * 512 / ODR_XL = 2.46 sec
	//if sleep_dur == 0, and ODR_XL = 26Hz,  16/26 = 0.61 sec
	reg.wake_up_dur.sleep_dur = 0;

	i2c1_info.buf_p = &reg.byte;

	mm_error |= ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	return mm_error;
}

//===================================================================//
/**
  * asm330lhh_set_activity_inactivity_threshold
  */

int32_t asm330lhh_set_activity_inactivity_threshold(uint8_t val)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg = {};

	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ASM330LHH_WAKE_UP_THS;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = 0;
	i2c1_info.name = "set_activity_inactivity_threshold";
	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	reg.wake_up_ths.usr_off_on_wu = 0;

	if(val < 64)
		reg.wake_up_ths.wk_ths = val;
	else
		reg.wake_up_ths.wk_ths = 63;

	i2c1_info.buf_p = &reg.byte;

	mm_error |= ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	return mm_error;
}

//===================================================================//
/**
  * asm330lhh_select_sleep_change_notification
  */

int32_t asm330lhh_select_sleep_change_notification()
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg = {};

	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ASM330LHH_INT_CFG0;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = 0;
	i2c1_info.name = "set_activity_inactivity_threshold";
	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	reg.int_cfg0.int_clr_on_read = 0;
	reg.int_cfg0.lir = 0;
	reg.int_cfg0.sleep_status_on_int = 1;
	reg.int_cfg0.slope_fds = 0;

	i2c1_info.buf_p = &reg.byte;

	mm_error |= ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	return mm_error;
}

//===================================================================//
/**
  * asm330lhh_enable_interrupt
  */

int32_t asm330lhh_enable_interrupt()
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg = {};

	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ASM330LHH_INT_CFG1;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = 0;
	i2c1_info.name = "enable_interrupt";
	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	reg.int_cfg1.interrupts_enable = 1;
	reg.int_cfg1.inact_en = 0;

	i2c1_info.buf_p = &reg.byte;

	mm_error |= ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	return mm_error;
}

//===================================================================//
/**
  * asm330lhh_activity_inactivity_interrupt_driven_to_int1_pin
  */

int32_t asm330lhh_activity_inactivity_interrupt_driven_to_int1_pin()
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;
	ism330dlc_reg_t reg = {};

	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ASM330LHH_MD1_CFG;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = 0;
	i2c1_info.name = "activity_inactivity_interrupt_driven_to_int1_pin";
	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	reg.md1_cfg.int1_sleep_change = 1;
	reg.md1_cfg.int1_wu = 0;
	reg.md1_cfg.int1_ff = 0;
	reg.md1_cfg.int1_6d = 0;

	i2c1_info.buf_p = &reg.byte;

	mm_error |= ism330dlc_write_reg(i2c1_info);
	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(&reg.byte,task_index);

	return mm_error;
}

//===================================================================//
/**
  * asm330lhh_int1_ctrl_get_value
  */

int32_t asm330lhh_int1_ctrl_get_value(uint8_t *value)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;

	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ASM330LHH_INT1_CTRL;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = 0;
	i2c1_info.name = "int1_ctrl_get_value";

	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(value, task_index);

	return mm_error;
}

//===================================================================//
/**
  * asm330lhh_wake_up_src_get_value
  */

int32_t asm330lhh_wake_up_src_get_value(uint8_t *value)
{
	int32_t mm_error;
	i2c1_input_info_t i2c1_info = {};
	uint8_t task_index;

	i2c1_info.block = 1;
	i2c1_info.len = 1;
	i2c1_info.reg = ISM330DLC_WAKE_UP_SRC;
	i2c1_info.slaveAddress = ISM330DLC_I2C_ADD_H;
	i2c1_info.buf_p = 0;
	i2c1_info.callback = 0;
	i2c1_info.name = "wake_up_src_get_value";

	mm_error = ism330dlc_read_reg(i2c1_info);

	task_index = i2c1_get_block_task_index();
	i2c1_copy_data_from_task(value, task_index);

	return mm_error;
}

