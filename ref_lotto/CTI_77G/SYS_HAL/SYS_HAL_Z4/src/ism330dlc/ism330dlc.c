/**
* @file    ism330dlc.c
* @author  msn
* @version v1.0.0
* @date    2018/2/9
* @brief   --
* 
* @note    --
*/

/* Includes ------------------------------------------------------------------*/
#include "ism330dlc.h"
#include "sys_shared.h"
#include "App_ComTx.h"
#include "custom_math.h"
#include "monitor_task.h"
#include "monitor.h"

#if JSON_LIST_EN
#include "json_imu_info.h"
#include "radar_output_controller.h"
#endif

/* Private macro -------------------------------------------------------------*/
#define JSON_ENABLE_IMU			"\t\t\"Enable imu\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_SEND_CAN_MSG		"\t\t\"Send CAN msg\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_YAW_ONBOARD		"\t\t\"Yaw onboard\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_DEBUG_MODE			"\t\t\"Debug mode\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_GY_HPF_LPF1		"\t\t\"gy's HPF&LPF1\":{\"t\":\"u8\",\"o\":%d,\"v\":%u},\n"
#define JSON_GY_LPF2			"\t\t\"gy's LPF2\":{\"t\":\"u8\",\"o\":%d,\"v\":%u},\n"
#define JSON_ENABLE_AUTO_CALIB	"\t\t\"Enable auto calib\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_FILTER_MODE		"\t\t\"Filter mode\":{\"t\":\"u8\",\"o\":%d,\"v\":%u},\n"
#define JSON_FILTER_COEF		"\t\t\"Filter coef\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d, %d]},\n"
#define JSON_MOTION_THLD		"\t\t\"Motion detection thld\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_YAW_RATE_THLD		"\t\t\"Yaw rate thld\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d, %d, %d, %d]},\n"
#define JSON_CALIB_FLAG			"\t\t\"Calib flag\":{\"t\":\"u16\",\"o\":%d,\"v\":%d},\n"
#define JSON_CALIB_TEMP			"\t\t\"Calib temp\":{\"t\":\"i8\",\"o\":%d,\"v\":"\
												"[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d]},\n"
#define JSON_ZERO_G				"\t\t\"Zero-g\":{\"t\":\"i8\",\"o\":%d,\"v\":"\
												"[[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d], "\
												"[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d], "\
												"[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d]]},\n"
#define JSON_ZERO_RATE_LEVEL	"\t\t\"Zero-rate level\":{\"t\":\"i16\",\"o\":%d,\"v\":"\
														"[[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d], "\
														"[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d], "\
														"[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d]]},\n"
#define JSON_AR_GAIN			"\t\t\"AR gain\":{\"t\":\"f32\",\"o\":%d,\"v\":[%f,%f,%f]},\n"
#define JSON_AR_DIR				"\t\t\"Direction\":{\"t\":\"u8\",\"o\":%d,\"v\":%d}\n"

#define GAIN_1ST_H		8.915815088
#define GAIN_1ST_L		22.20494879
#define COEF_1ST_H		0.775679511
#define COEF_1ST_L		0.9099299882
#define GAIN_2ND_H		74.85478157
#define COEF1_2ND_H		-0.7008967812
#define COEF2_2ND_H		1.6474599811
#define GAIN_2ND_L		480.6381793
#define COEF1_2ND_L		-0.8752145483
#define COEF2_2ND_L		1.8668922797
#define GRAVITY					1000.0
#define IMU_NOT_CALIB			0x7F
#define TWO_SEC					80
#define AUTO_CALIB_SAMPLING_RNG	120
#define AUTO_CALIB_DISCARD_DATA	70
#define AUTO_CALIB_INTERVAL		10
#define THREE_PERCENT			0.03
#define TEN_PERCENT				0.1
#define G_TCOFF					5.0
#define TEMPERATURE_RANGE_IDX	16
#define V_M_S_TO_KM_H			3.6
#define SELF_TEST_INTERVAL		100
#define SLOPE_FACTOR			1000.0
#define ABS(x) 					((x) < 0 ? -(x) : (x))

/* Private enum --------------------------------------------------------------*/
typedef enum{
	AUTOMATIC_CALIB	= 0,
	MANUAL_CALIB	= 1
}CALIB_MODE_E;

typedef enum {
	CFREQ_H	= 0,
	CFREQ_L	= 1,
}FILTER_MODE_E;

typedef enum {
	MOTION_STATUS_STATIONARY	= 0,
	MOTION_STATUS_MOVING		= 1,
	MOTION_STATUS_UNKNOWN		= 2,
}MOTION_STATUS_E;

typedef enum{
	AUTOMATIC_ST	= 0,
	MANUAL_ST		= 1,
}SELF_TEST_MODE_E;

typedef enum{
	COLLECT_NOST_SPD_0	= 1,
	COLLECT_ST_SPD_0	= 2,
	COLLECT_NOST		= 3,
	COLLECT_ST			= 4,
}SELF_TEST_PHASE_E;

typedef enum {
	GYRO_ST_MIN	= 150,	//dps
	GYRO_ST_MAX	= 700,	//dps
	ACC_ST_MIN	= 90,	//mg
	ACC_ST_MAX	= 1700,	//mg
}SELF_TEST_BOUNDARY_E;

typedef enum {
	IMU_ST_SUCCESS	= 0,
	IMU_ST_FAILED	= 1,
	IMU_ST_UNDONE	= 2,
}SELF_TEST_RESULT_E;

typedef enum {
	DISABLE_IMU_DBG		= 0,
	ENABLE_IMU_DBG		= 1,//To loosen restrictions on self test
	IMU_DBG_MSG			= 2,
	MORE_IMU_DBG_MSG	= 3,
}IMU_DEBUG_MODE_E;

/* Private structures --------------------------------------------------------*/
typedef struct {
	float		raw_data;
	float		compensated_data;
	float		filtered_data;
	float		in_1st[2];
	float		out_1st[2];
	float		in_2nd[3];
	float		out_2nd[3];
}angular_rate_info_t, *angular_rate_info_p;

typedef struct {
	float		prev_raw_data;
	float		raw_data;
	float		compensated_data;
	float		filtered_data;
	float		in_1st[2];
	float		out_1st[2];
	float		in_2nd[3];
	float		out_2nd[3];
}acceleration_info_t, *acceleration_info_p;

typedef struct {
	float auto_calib_angular_rate_mdps[3];
	float auto_calib_acceleration_mg[3];
	float auto_calib_temp;
	uint8_t spd_equal_to_zero_timer;
	uint8_t auto_calib_sampling_cnt;
	uint16_t timer_cnt;
}imu_auto_calib_info_t, *imu_auto_calib_info_p;

typedef struct {
	float		zero_g;				//unit: mg
	float		zero_rate_level;	//unit: mdps
	float		xl_calib_thld;		//unit: mg^2
}imu_calib_boundary_value_t, *imu_calib_boundary_value_p;

typedef struct {
	float acc_out_nost[3];
	float acc_out_st[3];
	float gyro_out_nost[3];
	float gyro_out_st[3];
	uint8_t cnt;
	uint8_t current_phase;
	uint8_t acc_self_test_result;
	uint8_t gyro_self_test_result;
}imu_self_test_t;

typedef struct {
	uint8_t		reg;			//0: stationary, 1: motion
	int8_t		cnt;
	uint8_t		status;			//0: stationary, 1: motion
	uint8_t		reserve;
}imu_motion_t, *imu_motion_p;

typedef struct {
	float		sum_of_ar[3];
	float		sum_of_temp;
	uint8_t		temp_index;
	uint8_t		cnt;
	uint8_t		reserve[2];
}imu_ac_1st_write_t, *imu_ac_1st_write_p;

/* Private variables ---------------------------------------------------------*/
ism330dlc_pars_t ism330dlc_parameters = {
	.hdr={
		.base		= (uint32_t)&ism330dlc_parameters,
		.version	= 0x0501,
		.size		= sizeof(ism330dlc_pars_t),
		.id			= ISM330DLC_PARS_ID,
		.chksum		= 0,
		.mask		= 0
	},
	.info = {
		.enable_imu				= 1,
		.send_can_msg			= 1,
		.yaw_onboard			= 1,
		.debug_mode				= 0,
		.gy_HPF_LPF1_mode		= 5, //ISM330DLC_HP_DISABLE_LP1_LIGHT
		.gy_LPF2_mode			= 3, //ISM330DLC_GY_ODR_52Hz
		.enable_auto_calib		= 1,
		.filter_mode			= 0,
		.filter_coef			= {50, 50},
		.mthld					= 63,
		.yaw_rate_thld			= {20, 10, 5, 200},//[spd(kph), yaw(10^-1 dps), laneW(10^-1 m), laneL(m)]
		.calib_flag				= 0,
		.calib_temp				= {IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB,
								   IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB},
		.zero_g					= {{IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB,
									IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB},
								   {IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB,
									IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB},
								   {IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB,
									IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB, IMU_NOT_CALIB}},
		.zrl					= {},
		.ar_gain				= {1.0, 1.0, 1.0},
		.dir					= 0,
		.reserve				= {}
	}
};

imu_auto_calib_info_t imu_auto_calib_info = {};

imu_self_test_t imu_self_test = {
		.acc_out_nost			= {},
		.acc_out_st				= {},
		.cnt					= 0,
		.current_phase			= 0,
		.gyro_out_nost			= {},
		.gyro_out_st			= {},
		.acc_self_test_result	= IMU_ST_UNDONE,
		.gyro_self_test_result	= IMU_ST_UNDONE
};

imu_motion_t imu_motion = {};
imu_comp_info_t imu_comp_info = {};

static timer_p imu_cycle_get_timer_p = NULL;
static timer_p imu_manu_calib_timer_p = NULL;
static timer_p imu_timer_p = NULL;
//static axis1bit16_t data_raw_temperature;
static int16_t sg_data_raw_angular_rate[3];
static int16_t sg_data_raw_acceleration_mg[3];
static float temperature_degC = 0.0;
static uint8_t detected_imu_flag = 0;
static float vehicle_yaw0 = 0;			// Last time vehicle's yaw rate.
static uint8_t imu_calibration_result = ERROR; // success: 0, failure: 1
static imu_self_calib_cb imu_calib_cb = NULL;
static imu_self_test_cb imu_st_cb = NULL;
static ism330dlc_info_p ism330dlc_info = &ism330dlc_parameters.info;
static int8_t self_test_flag = FALSE;
static uint8_t imu_calibrated = FALSE;
static uint16_t customer_id = CUSTOM_ID_INVALID;
static uint16_t product_id = PROD_ID_INVALID;

angular_rate_info_t angular_rate_mdps[3] = {};
angular_rate_info_t angular_rate_mdps_for_cal[3] = {};
acceleration_info_t acceleration_mg[3] = {};
acceleration_info_t acceleration_mg_for_cal[3] = {};
imu_calib_boundary_value_t imu_calib_boundary_value = {};
void *self_test_phase_p; //8 bytes
imu_ac_1st_write_t imu_ac_1st_write = {};
uint8_t sg_whoamI = 0;
uint16_t prev_fnum = 0;

/* Private functions ---------------------------------------------------------*/
static int32_t platform_write(i2c1_input_info_t i2c1_info);
static int32_t platform_read(i2c1_input_info_t i2c1_info);
static void set_imu_status_to_vehicle_module(uint8_t part, uint8_t status);
static void restore_imu_to_default();
static void config_imu();
static void ism330dlc_read_gyro_and_xl_and_temp(void);
static float cal_radius_value(float speed_kph, float yaw);
static void ism330dlc_reg_read(char** args, int count);
static void ism330dlc_reg_write(char** args, int count);
static void ism330dlc_reg_dump(char** args, int count);
static uint8_t is_calib_value_overflow(float* zero_rate_level_mdps, float* zero_g_mg);
static void manu_calib_IMU(void);
static void ism330dlc_self_calibration(char** args, int count);
static void ism330dlc_display_or_set_gy_HPF_LPF1_mode(char** args, int count);
static char* get_gy_HPF_LPF1_mode_name(uint8_t index);
static int set_imu_calib_boundry_values(uint8_t device_id);
static int set_gy_HPF_LPF1_mode(uint8_t index);
static void ism330dlc_display_or_set_gy_LPF2_mode(char** args, int count);
static char* get_gy_LPF2_mode_name(uint8_t index);
static int set_gy_LPF2_mode(uint8_t index);
static void ism330dlc_par_info(char** args, int count);
static void ism330dlc_display_or_set_fm(char** args, int count);
static void ism330dlc_display_or_set_fc(char** args, int count);
static void ism330dlc_display_or_set_thld(char** args, int count);
static void ism330dlc_display_or_set_calib_flag(char** args, int count);
static void ism330dlc_display_or_set_yob(char** args, int count);
static void ism330dlc_display_or_set_dbg(char** args, int count);
static void ism330dlc_display_or_set_send_can_msg(char** args, int count);
//static void ism330dlc_display_or_set_auto_calib_period(char** args, int count);
static void ism330dlc_display_or_set_auto_calib(char** args, int count);
static void ism330dlc_display_or_set_calib_temp(char** args, int count);
static void ism330dlc_display_or_set_zero_g(char** args, int count);
static void ism330dlc_display_or_set_zero_rate_level(char** args, int count);
static void set_imu_enable_or_disable(char** args, int count);
static void ism330dlc_display_or_set_motion_detection_thld(char** args, int count);
static void ism330dlc_display_or_set_ag(char** args, int count);
static void ism330dlc_display_or_set_dir(char** args, int count);
static int8_t is_self_test_done();
static void ism330dlc_console_commands_reg(void);
static int ism330dlc_info_in_jsons(char* ws);
static void ism330dlc_pars_dump(void);
static float iir_filter(float current_yaw_rate);
static int8_t update_imu_comp_info(int8_t mode);
static void imu_calib_values_sort_by_temp(int8_t *sorted_temp_stamp, int8_t *sorted_temp_index);
static void compensate_function(void);
static void filter(uint8_t mode);
static void update_IMU_and_do_dsp_auto_calib(void);
static void send_imu_data_by_can(uint8_t flag_send_can_every_frame);
static void update_filtered_obd_yaw_and_radius(void);
static void update_filtered_imu_data_and_radius(uint8_t flag_update_vehicle_module);
static int8_t collect_IMU_data_and_take_average_value(int8_t calib_mode);
static int8_t allow_to_do_overwrite_zrl(uint8_t index_by_temp);
static void calib_IMU(int8_t calib_mode);
static void self_test_data_collector(void *current_phase);
static void self_test_procedure(uint8_t st_mode);
static void manual_self_test(char** args, int count);
static void motion_detection();

/*
 *   Replace the functions "platform_write" and "platform_read" with your
 *   platform specific read and write function.
 *   This example use an STM32 evaluation board and CubeMX tool.
 *   In this case the "*handle" variable is useful in order to select the
 *   correct interface but the usage of "*handle" is not mandatory.
 */

static int32_t platform_write(i2c1_input_info_t i2c1_info)
{
	i2c1_SendMsg(i2c1_info);
	return 0;
}

static int32_t platform_read(i2c1_input_info_t i2c1_info)
{
	i2c1_ReadMsg(i2c1_info);
	return 0;
}

static void set_imu_status_to_vehicle_module(uint8_t part, uint8_t status)
{
	//part, [0]: acc, [1]: gyro		status, [0]: not get value, [1]: invalid value.
	if(part == 0) //acc
	{
		if(status == 0)
		{
			set_veh_onboard_raw_acc_x_status_not_get_value();
			set_veh_onboard_raw_acc_y_status_not_get_value();
			set_veh_onboard_raw_acc_z_status_not_get_value();
			set_veh_onboard_filtered_acc_x_status_not_get_value();
			set_veh_onboard_filtered_acc_y_status_not_get_value();
			set_veh_onboard_filtered_acc_z_status_not_get_value();
		}
		else if(status == 1)
		{
			set_veh_onboard_raw_acc_x_status_invalid_value();
			set_veh_onboard_raw_acc_y_status_invalid_value();
			set_veh_onboard_raw_acc_z_status_invalid_value();
			set_veh_onboard_filtered_acc_x_status_invalid_value();
			set_veh_onboard_filtered_acc_y_status_invalid_value();
			set_veh_onboard_filtered_acc_z_status_invalid_value();
		}
	}
	else if(part == 1) //gyro
	{
		if(status == 0)
		{
			set_veh_onboard_raw_roll_rate_status_not_get_value();
			set_veh_onboard_raw_pitch_rate_status_not_get_value();
			set_veh_onboard_raw_yaw_rate_status_not_get_value();
			set_veh_onboard_filtered_roll_rate_status_not_get_value();
			set_veh_onboard_filtered_pitch_rate_status_not_get_value();
			set_veh_onboard_filtered_yaw_rate_status_not_get_value();

			set_veh_onboard_radius_status_not_get_value();
		}
		else if(status == 1)
		{
			set_veh_onboard_raw_roll_rate_status_invalid_value();
			set_veh_onboard_raw_pitch_rate_status_invalid_value();
			set_veh_onboard_raw_yaw_rate_status_invalid_value();
			set_veh_onboard_filtered_roll_rate_status_invalid_value();
			set_veh_onboard_filtered_pitch_rate_status_invalid_value();
			set_veh_onboard_filtered_yaw_rate_status_invalid_value();

			set_veh_onboard_radius_status_invalid_value();
		}
	}
}

static void restore_imu_to_default()
{
	if (imu_timer_p != NULL && !strcmp("restore_imu", imu_timer_p->name))
		timer_unset(&imu_timer_p);
	imu_timer_p = NULL;

	ism330dlc_xl_data_rate_set(ISM330DLC_XL_ODR_OFF);//Power-down mode
	ism330dlc_gy_data_rate_set(ISM330DLC_GY_ODR_OFF);//Power-down mode
	ism330dlc_reset_set(PROPERTY_ENABLE);

	if(imu_timer_p == NULL)
		imu_timer_p = timer_set("config_imu", 1, 1,(event_proc_p)config_imu, NULL);//4.17ms
}

static void config_imu()
{
	uint8_t reg = 0;

	ism330dlc_reset_status_get(&reg);

	if (imu_timer_p != NULL && !strcmp("config_imu", imu_timer_p->name))
		timer_unset(&imu_timer_p);
	imu_timer_p = NULL;

	if((reg&1) == 0)
	{
		/*
		 *  Disable Block Data Update
		 */
		ism330dlc_block_data_update_set(PROPERTY_ENABLE);
		/*
		 * Set Output Data Rate
		 */
		ism330dlc_xl_data_rate_set(ISM330DLC_XL_ODR_52Hz);
		set_gy_LPF2_mode(ism330dlc_info->gy_LPF2_mode); //Default: ISM330DLC_GY_ODR_52Hz
		/*
		 * Set full scale
		 */
		ism330dlc_xl_full_scale_set(ISM330DLC_2g);
		ism330dlc_gy_full_scale_set(ISM330DLC_125dps);

		/*
		 * Configure filtering chain(No aux interface)
		 */
		/* Accelerometer - analog filter */
		ism330dlc_xl_filter_analog_set(ISM330DLC_XL_ANA_BW_400Hz);

		/* Accelerometer - LPF1 path ( LPF2 not used )*/
		//ism330dlc_xl_lp1_bandwidth_set(&sg_dev_ctx, ISM330DLC_XL_LP1_ODR_DIV_4);

		/* Accelerometer - LPF1 + LPF2 path */
		ism330dlc_xl_lp2_bandwidth_set(ISM330DLC_XL_LOW_NOISE_LP_ODR_DIV_100);

		/* Accelerometer - High Pass / Slope path */
		//ism330dlc_xl_reference_mode_set(&sg_dev_ctx, PROPERTY_DISABLE);
		//ism330dlc_xl_hp_bandwidth_set(&sg_dev_ctx, ISM330DLC_XL_HP_ODR_DIV_100);

		/* Gyroscope - filtering chain */
		//ism330dlc_gy_band_pass_set(&sg_dev_ctx, ISM330DLC_HP_DISABLE_LP1_LIGHT);
		set_gy_HPF_LPF1_mode(ism330dlc_info->gy_HPF_LPF1_mode); //Default: ISM330DLC_HP_DISABLE_LP1_LIGHT

		//write zero_g in ism330dlc's reg.
		//ism330dlc_xl_usr_offset_set((uint8_t *)zero_g_mg_coord_IC);

		/* ASM330LHH, Stationary/Motion detection */
		asm330lhh_set_duration_for_inactivity_detection();
		asm330lhh_set_activity_inactivity_threshold(ism330dlc_info->mthld);
		asm330lhh_select_sleep_change_notification();
		asm330lhh_enable_interrupt();
		asm330lhh_activity_inactivity_interrupt_driven_to_int1_pin();

		/* Get zero-g & zero-rate level */
		set_imu_calib_boundry_values(sg_whoamI);

		/* update acc & gyro comp info(offset, slope)*/
		imu_calibrated  = update_imu_comp_info(0);//zero-g
		imu_calibrated += update_imu_comp_info(1);//zero-rate level

		if(imu_calibrated == SUCCESS)
		{
		    set_monitoring_result_by_id(MONITOR_ID_IMU, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED);
		}
		else
		{
		    //IMU missing calibration
		    set_monitoring_result_by_id(MONITOR_ID_IMU, MONITOR_RESULT_FAILED, MONITOR_RESULT_CODE_ERROR);
		}

		PRINTF("IMU config success.\n");
	}
	else
		PRINTF("IMU config failed.\n");

	if(imu_st_cb != NULL)
	{
		imu_st_cb(imu_self_test.acc_self_test_result || imu_self_test.gyro_self_test_result);
		imu_st_cb = NULL;
	}
}

static void ism330dlc_device_id_get_cb(uint8_t task_index)
{
	i2c1_copy_data_from_task(&sg_whoamI,task_index);

	if (( sg_whoamI == ISM330DLC_ID ) ||
		( sg_whoamI == ASM330LHH_ID ))
	{
		detected_imu_flag = 1;
		PRINTF("Detected IMU.\n");

		// Get ISM330DLC's parameters from EEPROM.
		if(pars_get((pars_ctx_p)&ism330dlc_parameters, ism330dlc_pars_dump, ism330dlc_info_in_jsons) == -1)
			PRINTF("Can't read IMU's parameters from EEPROM.\n");

		if(ism330dlc_info->enable_imu && imu_timer_p == NULL)
			imu_timer_p = timer_set("restore_imu", 4, 1,(event_proc_p)restore_imu_to_default, (event_proc_p)NULL);//16.68ms

		//set vehicle module status: acc & gyro invalid.
		set_imu_status_to_vehicle_module(0, 1);
		set_imu_status_to_vehicle_module(1, 1);
	}
	else
	{
		detected_imu_flag = 0;
		PRINTF("No IMU Device\n");

		//set vehicle module: imu not get data.
		set_imu_status_to_vehicle_module(0, 0);
		set_imu_status_to_vehicle_module(1, 0);

		//motion
		set_veh_motion_status_not_get_value();

		set_veh_onboard_radius_status_not_get_value();
	}
}

void init_ism330dlc(void)
{
	customer_id = product_info_get()->customer;
	product_id = product_info_get()->product;

	/*
	 *  Initialize mems driver interface
	 */
	init_ism330dlc_read_write_reg(platform_write,platform_read);

	ism330dlc_device_id_get((event_proc_p)ism330dlc_device_id_get_cb);

	ism330dlc_console_commands_reg();
}

static void ism330dlc_temp_gyro_xl_raw_get_cb(uint8_t task_index)
{
	uint8_t imu_data[19] = {}; //{statue:3, temp:5~6, gyro:7~12, xl:13~18}
	uint8_t tda = 0, gda = 0, xlda = 0;

	i2c1_copy_data_from_task(&imu_data[0], task_index);

	tda			= (imu_data[3] >> 2) & 1;
	gda			= (imu_data[3] >> 1) & 1;
	xlda		= imu_data[3] & 1;
	imu_motion.reg = imu_data[0];

	if(tda)//temp
	{
		int16_t temp_reg = imu_data[6] << 8 | imu_data[5];
		temperature_degC = ISM330DLC_FROM_LSB_TO_degC(temp_reg);
		set_veh_onboard_temperature_value(temperature_degC);
	}

	if(gda)//gyro
	{
		switch(ism330dlc_info->dir)
		{
		case 0:
			sg_data_raw_angular_rate[Rollaxis]	= (-1)*(imu_data[12] << 8 | imu_data[11]);
			sg_data_raw_angular_rate[Pitchaxis]	= (-1)*(imu_data[8]  << 8 | imu_data[7]);
			sg_data_raw_angular_rate[Yawaxis]	= 	   (imu_data[10] << 8 | imu_data[9]);
			break;
		case 1:
			sg_data_raw_angular_rate[Rollaxis]	= (-1)*(imu_data[12] << 8 | imu_data[11]);
			sg_data_raw_angular_rate[Pitchaxis]	= (-1)*(imu_data[10] << 8 | imu_data[9]);
			sg_data_raw_angular_rate[Yawaxis]	= (-1)*(imu_data[8]  << 8 | imu_data[7]);
			break;
		case 2:
			sg_data_raw_angular_rate[Rollaxis]	= (-1)*(imu_data[12] << 8 | imu_data[11]);
			sg_data_raw_angular_rate[Pitchaxis]	=      (imu_data[8]  << 8 | imu_data[7]);
			sg_data_raw_angular_rate[Yawaxis]	= (-1)*(imu_data[10] << 8 | imu_data[9]);
			break;
		case 3:
			sg_data_raw_angular_rate[Rollaxis]	= (-1)*(imu_data[12] << 8 | imu_data[11]);
			sg_data_raw_angular_rate[Pitchaxis]	=      (imu_data[10] << 8 | imu_data[9]);
			sg_data_raw_angular_rate[Yawaxis]	=      (imu_data[8]  << 8 | imu_data[7]);
			break;
		case 4:
			sg_data_raw_angular_rate[Rollaxis]  =      (imu_data[10] << 8 | imu_data[9]);
			sg_data_raw_angular_rate[Pitchaxis] = (-1)*(imu_data[8]  << 8 | imu_data[7]);
			sg_data_raw_angular_rate[Yawaxis]	=      (imu_data[12] << 8 | imu_data[11]);
			break;
		case 5:
			sg_data_raw_angular_rate[Rollaxis]  =      (imu_data[12] << 8 | imu_data[11]);
			sg_data_raw_angular_rate[Pitchaxis] = (-1)*(imu_data[8]  << 8 | imu_data[7]);
			sg_data_raw_angular_rate[Yawaxis]	=      (imu_data[10] << 8 | imu_data[9]);
			break;
		default:
			sg_data_raw_angular_rate[Rollaxis]	= (-1)*(imu_data[12] << 8 | imu_data[11]);
			sg_data_raw_angular_rate[Pitchaxis]	= (-1)*(imu_data[8]  << 8 | imu_data[7]);
			sg_data_raw_angular_rate[Yawaxis]	=      (imu_data[10] << 8 | imu_data[9]);
		}

		angular_rate_mdps[Rollaxis].raw_data	= ISM330DLC_FROM_FS_125dps_TO_mdps(sg_data_raw_angular_rate[Rollaxis]);
		angular_rate_mdps[Pitchaxis].raw_data	= ISM330DLC_FROM_FS_125dps_TO_mdps(sg_data_raw_angular_rate[Pitchaxis]);
		angular_rate_mdps[Yawaxis].raw_data		= ISM330DLC_FROM_FS_125dps_TO_mdps(sg_data_raw_angular_rate[Yawaxis]);
	}

	if(xlda)//xl
	{
		acceleration_mg[Xaxis].prev_raw_data = acceleration_mg[Xaxis].raw_data;
		acceleration_mg[Yaxis].prev_raw_data = acceleration_mg[Yaxis].raw_data;
		acceleration_mg[Zaxis].prev_raw_data = acceleration_mg[Zaxis].raw_data;

		switch(ism330dlc_info->dir)
		{
		case 0:
			sg_data_raw_acceleration_mg[Xaxis] = (-1)*(imu_data[18] << 8 | imu_data[17]);//-z to x
			sg_data_raw_acceleration_mg[Yaxis] = (-1)*(imu_data[14] << 8 | imu_data[13]);//-x to y
			sg_data_raw_acceleration_mg[Zaxis] =      (imu_data[16] << 8 | imu_data[15]);// y to z
			break;
		case 1:
			sg_data_raw_acceleration_mg[Xaxis] = (-1)*(imu_data[18] << 8 | imu_data[17]);//-z to x
			sg_data_raw_acceleration_mg[Yaxis] = (-1)*(imu_data[16] << 8 | imu_data[15]);//-y to y
			sg_data_raw_acceleration_mg[Zaxis] = (-1)*(imu_data[14] << 8 | imu_data[13]);//-x to z
			break;
		case 2:
			sg_data_raw_acceleration_mg[Xaxis] = (-1)*(imu_data[18] << 8 | imu_data[17]);//-z to x
			sg_data_raw_acceleration_mg[Yaxis] =	  (imu_data[14] << 8 | imu_data[13]);// x to y
			sg_data_raw_acceleration_mg[Zaxis] = (-1)*(imu_data[16] << 8 | imu_data[15]);//-y to z
			break;
		case 3:
			sg_data_raw_acceleration_mg[Xaxis] = (-1)*(imu_data[18] << 8 | imu_data[17]);//-z to x
			sg_data_raw_acceleration_mg[Yaxis] =      (imu_data[16] << 8 | imu_data[15]);
			sg_data_raw_acceleration_mg[Zaxis] =      (imu_data[14] << 8 | imu_data[13]);// x to z
			break;
		case 4:
			sg_data_raw_acceleration_mg[Xaxis] =      (imu_data[16] << 8 | imu_data[15]);// y to x
			sg_data_raw_acceleration_mg[Yaxis] = (-1)*(imu_data[14] << 8 | imu_data[13]);//-x to y
			sg_data_raw_acceleration_mg[Zaxis] =      (imu_data[18] << 8 | imu_data[17]);
			break;
		case 5:
			sg_data_raw_acceleration_mg[Xaxis] = (-1)*(imu_data[14] << 8 | imu_data[13]);//-y to x
			sg_data_raw_acceleration_mg[Yaxis] = (-1)*(imu_data[16] << 8 | imu_data[15]);//-x to y
			sg_data_raw_acceleration_mg[Zaxis] = (-1)*(imu_data[18] << 8 | imu_data[17]);//-z to z
			break;
		default:
			sg_data_raw_acceleration_mg[Xaxis] = (-1)*(imu_data[18] << 8 | imu_data[17]);//-z to x
			sg_data_raw_acceleration_mg[Yaxis] = (-1)*(imu_data[14] << 8 | imu_data[13]);//-x to y
			sg_data_raw_acceleration_mg[Zaxis] =      (imu_data[16] << 8 | imu_data[15]);//-y to z
		}

		acceleration_mg[Xaxis].raw_data = ISM330DLC_FROM_FS_2g_TO_mg(sg_data_raw_acceleration_mg[Xaxis]);
		acceleration_mg[Yaxis].raw_data = ISM330DLC_FROM_FS_2g_TO_mg(sg_data_raw_acceleration_mg[Yaxis]);
		acceleration_mg[Zaxis].raw_data = ISM330DLC_FROM_FS_2g_TO_mg(sg_data_raw_acceleration_mg[Zaxis]);
	}

//	PRINTF("tda: %d, gda: %d, xlda: %d\n", tda, gda, xlda);
//	PRINTF("t: %.2f, gy[r,p,y] = {%.2f, %.2f, %.2f} mdps, xl[x,y,z] = {%.2f,%.2f,%.2f} mg.\n",
//			temperature_degC, angular_rate_mdps[Rollaxis].raw_data, angular_rate_mdps[Pitchaxis].raw_data,
//			angular_rate_mdps[Yawaxis].raw_data, acceleration_mg[Xaxis].raw_data, acceleration_mg[Yaxis].raw_data,
//			acceleration_mg[Zaxis].raw_data);
}

static void ism330dlc_read_gyro_and_xl_and_temp(void)
{
	if(detected_imu_flag == 1)
		ism330dlc_temp_gyro_xl_raw_get((event_proc_p)ism330dlc_temp_gyro_xl_raw_get_cb);
}

static float cal_radius_value(float speed_kph, float yaw)
{
	if(yaw == 0.0)
		return 32767;
	else
		return (speed_kph * KPH_TO_MS)/(yaw * DEGREE_TO_RADIAN);
}

static float check_yaw_bigger_than_thld(float temp_yaw)
{
	float vehicle_speed = get_eps_speed_value(); //get speed for radius calculate.
	float radius;

	//get thld from EEPROM.
	float lane_width_thld  = ism330dlc_info->yaw_rate_thld[2]/10.0f;  // equal 3.2m
	uint8_t lane_length_thld = ism330dlc_info->yaw_rate_thld[3];		//equal 200m

	radius = cal_radius_value(vehicle_speed, temp_yaw);

	if(temp_yaw >= 0)//Turn left:+, Turn right:-.
		lane_width_thld = (-1)*lane_width_thld;

	if(vehicle_speed > ism330dlc_info->yaw_rate_thld[0])
	{
		if(pow((double)(lane_width_thld - radius), 2) + pow((double)lane_length_thld, 2) - pow((double)radius, 2) < 0)
			return 0;
		else
			return temp_yaw;
	}
	else
	{
		if (ABS(temp_yaw) >= ism330dlc_info->yaw_rate_thld[1]/10.0f)
			return temp_yaw;
		else
			return 0;
	}
}

static void send_imu_data_by_can(uint8_t flag_send_can_every_frame)
{
	CAN_YAWRATE_FORMAT CAN_msg_angular_rate = {};
	CAN_ACCELERATION_FORMAT CAN_msg_acceleration = {};

	if(get_veh_filtered_yaw_rate_status() == VEH_STATUS_VALID)
		CAN_msg_angular_rate.B.vehicle_yawrate	= (int16_t)(get_veh_filtered_yaw_rate_value()*VEH_GY_ROLL_PITCH_YAW_FACTOR);
	if(get_veh_onboard_filtered_pitch_rate_status() == VEH_STATUS_VALID)
		CAN_msg_angular_rate.B.radar_pitchrate	= (int16_t)(get_veh_onboard_filtered_pitch_rate_value()*VEH_GY_ROLL_PITCH_YAW_FACTOR);
	if(get_veh_onboard_filtered_roll_rate_status() == VEH_STATUS_VALID)
		CAN_msg_angular_rate.B.radar_rollrate	= (int16_t)(get_veh_onboard_filtered_roll_rate_value()*VEH_GY_ROLL_PITCH_YAW_FACTOR);
	if(get_veh_onboard_filtered_yaw_rate_status() == VEH_STATUS_VALID)
		CAN_msg_angular_rate.B.radar_yawrate	= (int16_t)(get_veh_onboard_filtered_yaw_rate_value()*VEH_GY_ROLL_PITCH_YAW_FACTOR);
	if(get_veh_onboard_filtered_acc_x_status() == VEH_STATUS_VALID)
		CAN_msg_acceleration.B.Xaxis			= (int16_t)get_veh_onboard_filtered_acc_x_value();
	if(get_veh_onboard_filtered_acc_y_status() == VEH_STATUS_VALID)
		CAN_msg_acceleration.B.Yaxis			= (int16_t)get_veh_onboard_filtered_acc_y_value();
	if(get_veh_onboard_filtered_acc_z_status() == VEH_STATUS_VALID)
		CAN_msg_acceleration.B.Zaxis			= (int16_t)get_veh_onboard_filtered_acc_z_value();
	if(get_veh_onboard_raw_yaw_rate_status() == VEH_STATUS_VALID)
		CAN_msg_acceleration.B.radar_raw_yawrate = (int16_t)(get_veh_onboard_raw_yaw_rate_value()*VEH_GY_ROLL_PITCH_YAW_FACTOR);

	if(ism330dlc_info->debug_mode == IMU_DBG_MSG || ism330dlc_info->debug_mode == MORE_IMU_DBG_MSG)
	{
		PRINTF("IMUDBG: m:%d,v:%.3f,obd[r:%.2f,f:%d],gy[%d,%d,%d],xl:[%d,%d,%d]\n",
				imu_motion.status, get_eps_speed_value(), get_yaw_rate_value(), CAN_msg_angular_rate.B.vehicle_yawrate,
				CAN_msg_angular_rate.B.radar_rollrate, CAN_msg_angular_rate.B.radar_pitchrate, CAN_msg_angular_rate.B.radar_yawrate,
				CAN_msg_acceleration.B.Xaxis, CAN_msg_acceleration.B.Yaxis, CAN_msg_acceleration.B.Zaxis);
	}

#ifdef USING_CUBTEK_CAN_0
#endif
	if(ism330dlc_info->yaw_onboard == 0)
		if(VEH_STATUS_VALID == get_veh_filtered_yaw_rate_status())
			set_veh_two_src_filtered_yaw_rate_value(get_veh_filtered_yaw_rate_value());
		else
			set_veh_two_src_filtered_yaw_rate_status_not_get_value();
	else if(ism330dlc_info->yaw_onboard == 1)
		if(VEH_STATUS_VALID == get_veh_onboard_filtered_yaw_rate_status())
			set_veh_two_src_filtered_yaw_rate_value(get_veh_onboard_filtered_yaw_rate_value());
		else
			set_veh_two_src_filtered_yaw_rate_status_not_get_value();
	else
		set_veh_two_src_filtered_yaw_rate_status_not_get_value();

	// Transfer IMU information.
#ifdef ENABLE_BSW_UDS_NM
	if (tracking_yaw_sensor_message_flag_get() == 1 && flag_send_can_every_frame == TRUE)
	{
		App_ComTx_IpduData_Transmit(CAN_ID_IMU_INFO1, CAN_msg_angular_rate.R);
		App_ComTx_IpduData_Transmit(CAN_ID_IMU_INFO2, CAN_msg_acceleration.R);
	}
	else if (tracking_yaw_sensor_message_flag_get() == 2) //for Hirain, send can per 25ms.
	{
		if((CUSTOM_ID_HIRAIN_FAW == customer_id || CUSTOM_ID_HIRAIN_CNHTC == customer_id) &&
				((PROD_ID_93G014_MRR_BV1_0_FOR_Hirain == product_id) || (PROD_ID_93G014_MRR_BV2p1_FOR_HIRAIN == product_id)))
		{//Only provide the yaw rate raw data to Hirain customer
			CAN_msg_acceleration.B.Xaxis = 0;
			CAN_msg_acceleration.B.Yaxis = 0;
			CAN_msg_acceleration.B.Zaxis = 0;

			//PRINTF("Ryf:%d,Vyr:%.2f,Vyf:%d,spd:%.3f,acc:{%d,%d,%d},Rrawyr:%d\n", CAN_msg_angular_rate.B.radar_yawrate, vehicle_yaw,
			//	CAN_msg_angular_rate.B.vehicle_yawrate, vehicle_speed, CAN_msg_acceleration.B.Xaxis, CAN_msg_acceleration.B.Yaxis,
			//	CAN_msg_acceleration.B.Zaxis, CAN_msg_acceleration.B.radar_raw_yawrate);
			App_ComTx_IpduData_Transmit(CAN_ID_IMU_INFO2, CAN_msg_acceleration.R);
		}
	}
#else
	can_tracking_tx(CAN_ID_IMU_INFO1, (uint32_t*)&CAN_msg_angular_rate);
	can_tracking_tx(CAN_ID_IMU_INFO2, (uint32_t*)&CAN_msg_acceleration);
#endif
}

static void update_filtered_obd_yaw_and_radius(void)
{
	if(get_yaw_rate_status() != VEH_STATUS_VALID)
	{
		set_veh_filtered_yaw_rate_status_not_get_value();
		set_veh_radius_status_not_get_value();
		return;
	}

	//vehicle's yaw
	float vehicle_raw_yaw = get_yaw_rate_value();
	float vehicle_filtered_yaw = iir_filter(vehicle_raw_yaw);
	vehicle_filtered_yaw = check_yaw_bigger_than_thld(vehicle_filtered_yaw);
	set_veh_filtered_yaw_rate_value(vehicle_filtered_yaw);

	//vehicle info radius.
	if(get_eps_speed_status() == VEH_STATUS_VALID)
	{
		float vehicle_speed = get_eps_speed_value(); //get speed for radius calculate.
		float vehicle_info_radius = 0.0;

		if(vehicle_filtered_yaw == 0.0 || vehicle_speed == 0.0)
			vehicle_info_radius = 32767.0;
		else
		{
			vehicle_info_radius = (vehicle_speed * KPH_TO_MS) / (vehicle_filtered_yaw * DEGREE_TO_RADIAN);
			if(vehicle_info_radius > 32767.0 || vehicle_info_radius < -32768.0)
				vehicle_info_radius = 32767.0;
		}
		set_veh_radius_value(vehicle_info_radius);
	}
	else
		set_veh_radius_status_invalid_value();
}

static void update_filtered_imu_data_and_radius(uint8_t flag_update_vehicle_module)
{
	compensate_function();
	filter(CFREQ_H);
	float filtered_radar_yaw = check_yaw_bigger_than_thld(angular_rate_mdps[Yawaxis].filtered_data/1000.0);

	//send imu data to vihicle module
	set_veh_onboard_raw_roll_rate_value(angular_rate_mdps[Rollaxis].compensated_data/1000.0);
	set_veh_onboard_raw_pitch_rate_value(angular_rate_mdps[Pitchaxis].compensated_data/1000.0);
	set_veh_onboard_raw_yaw_rate_value(angular_rate_mdps[Yawaxis].compensated_data/1000.0);
	set_veh_onboard_raw_acc_x_value(acceleration_mg[Xaxis].compensated_data);
	set_veh_onboard_raw_acc_y_value(acceleration_mg[Yaxis].compensated_data);
	set_veh_onboard_raw_acc_z_value(acceleration_mg[Zaxis].compensated_data);

	if(flag_update_vehicle_module)//update once in a frame.
	{
		set_veh_onboard_filtered_roll_rate_value(angular_rate_mdps[Rollaxis].filtered_data/1000.0);
		set_veh_onboard_filtered_pitch_rate_value(angular_rate_mdps[Pitchaxis].filtered_data/1000.0);
		set_veh_onboard_filtered_yaw_rate_value(filtered_radar_yaw);
		set_veh_onboard_filtered_acc_x_value(acceleration_mg[Xaxis].filtered_data);
		set_veh_onboard_filtered_acc_y_value(acceleration_mg[Yaxis].filtered_data);
		set_veh_onboard_filtered_acc_z_value(acceleration_mg[Zaxis].filtered_data);

		//IMU info radius.
		if(get_eps_speed_status() == VEH_STATUS_VALID)
		{
			float vehicle_speed = get_eps_speed_value(); //get speed for radius calculate.
			float imu_radius = 0.0;

			if(get_veh_onboard_filtered_yaw_rate_value() == 0.0 || vehicle_speed == 0.0)
				imu_radius = 32767.0f;
			else
			{
				imu_radius = (vehicle_speed * KPH_TO_MS) / (get_veh_onboard_filtered_yaw_rate_value() * DEGREE_TO_RADIAN);
				if(imu_radius > 32767.0f || imu_radius < -32768.0f)
					imu_radius = 32767.0f;
			}
			set_veh_onboard_radius_value(imu_radius);
		}
	}

	// every 25ms print IMU data.
	if(ism330dlc_info->debug_mode == MORE_IMU_DBG_MSG)
	{
//		float tilt_angle[3] = {
//			atanf(acceleration_mg[Xaxis].filtered_data/sqrt(powf(acceleration_mg[Yaxis].filtered_data, 2) + powf(acceleration_mg[Zaxis].filtered_data, 2)))*180.0/PI,
//			atanf(acceleration_mg[Yaxis].filtered_data/sqrt(powf(acceleration_mg[Xaxis].filtered_data, 2) + powf(acceleration_mg[Zaxis].filtered_data, 2)))*180.0/PI,
//			atanf(sqrt(powf(acceleration_mg[Xaxis].filtered_data, 2) + powf(acceleration_mg[Yaxis].filtered_data, 2))/acceleration_mg[Zaxis].filtered_data)*180/PI
//		};

		PRINTF("IMUDBG: gy[r,p,y](mdps), fn = %d, t: %.2f r = {%.2f,%.2f,%.2f}, cmp = {%.2f,%.2f,%.2f}, f = {%.2f,%.2f,%.2f}\n",
				get_frame_counter(),
				temperature_degC,
				angular_rate_mdps[Rollaxis].raw_data,
				angular_rate_mdps[Pitchaxis].raw_data,
				angular_rate_mdps[Yawaxis].raw_data,
				angular_rate_mdps[Rollaxis].compensated_data,
				angular_rate_mdps[Pitchaxis].compensated_data,
				angular_rate_mdps[Yawaxis].compensated_data,
				angular_rate_mdps[Rollaxis].filtered_data,
				angular_rate_mdps[Pitchaxis].filtered_data,
				filtered_radar_yaw*1000.0);
		PRINTF("IMUDBG: xl[x,y,z](mg), fn = %d, t: %.2f r = {%.1f,%.1f,%.1f}, cmp = {%.1f,%.1f,%.1f}, f = {%.1f,%.1f,%.1f}\n",
				get_frame_counter(),
				temperature_degC,
				acceleration_mg[Xaxis].raw_data,
				acceleration_mg[Yaxis].raw_data,
				acceleration_mg[Zaxis].raw_data,
				acceleration_mg[Xaxis].compensated_data,
				acceleration_mg[Yaxis].compensated_data,
				acceleration_mg[Zaxis].compensated_data,
				acceleration_mg[Xaxis].filtered_data,
				acceleration_mg[Yaxis].filtered_data,
				acceleration_mg[Zaxis].filtered_data);
//		PRINTF("IMUDBG: tilt_angle = {%.1f,%.1f,%.1f}\n", tilt_angle[Xaxis], tilt_angle[Yaxis], tilt_angle[Zaxis]);
	}
}

static int8_t collect_IMU_data_and_take_average_value(int8_t calib_mode)
{
	if(imu_auto_calib_info.auto_calib_sampling_cnt < AUTO_CALIB_DISCARD_DATA)
	{
		imu_auto_calib_info.auto_calib_sampling_cnt++;
		return 1;
	}

	if(((get_eps_speed_status() == VEH_STATUS_VALID && get_eps_speed_value() == 0.0 && imu_motion.status == MOTION_STATUS_STATIONARY) || calib_mode == MANUAL_CALIB) &&
		(powf(acceleration_mg[Xaxis].raw_data*0.001, 2) + powf(acceleration_mg[Yaxis].raw_data*0.001, 2) + powf(acceleration_mg[Zaxis].raw_data*0.001, 2)) <
		imu_calib_boundary_value.xl_calib_thld)
	{
		imu_auto_calib_info.auto_calib_angular_rate_mdps[Rollaxis]	+= angular_rate_mdps_for_cal[Rollaxis].filtered_data;
		imu_auto_calib_info.auto_calib_angular_rate_mdps[Pitchaxis]	+= angular_rate_mdps_for_cal[Pitchaxis].filtered_data;
		imu_auto_calib_info.auto_calib_angular_rate_mdps[Yawaxis]	+= angular_rate_mdps_for_cal[Yawaxis].filtered_data;
		imu_auto_calib_info.auto_calib_acceleration_mg[Xaxis] += acceleration_mg_for_cal[Xaxis].filtered_data;
		imu_auto_calib_info.auto_calib_acceleration_mg[Yaxis] += acceleration_mg_for_cal[Yaxis].filtered_data;
		imu_auto_calib_info.auto_calib_acceleration_mg[Zaxis] += acceleration_mg_for_cal[Zaxis].filtered_data;
		imu_auto_calib_info.auto_calib_temp += temperature_degC;
		imu_auto_calib_info.auto_calib_sampling_cnt++;

		if((ism330dlc_info->debug_mode == MORE_IMU_DBG_MSG) || (calib_mode == MANUAL_CALIB))
			PRINTF("(%d/%d)...\t temp: %.1f deg, gy[r,p,y] = {%.1f,%.1f,%.1f} mdps, xl[x,y,z] = {%.1f,%.1f,%.1f} mg.\n",
					imu_auto_calib_info.auto_calib_sampling_cnt, AUTO_CALIB_SAMPLING_RNG, temperature_degC,
					angular_rate_mdps_for_cal[Rollaxis].filtered_data, angular_rate_mdps_for_cal[Pitchaxis].filtered_data, angular_rate_mdps_for_cal[Yawaxis].filtered_data,
					acceleration_mg_for_cal[Xaxis].filtered_data, acceleration_mg_for_cal[Yaxis].filtered_data, acceleration_mg_for_cal[Zaxis].filtered_data);

		if(imu_auto_calib_info.auto_calib_sampling_cnt >= AUTO_CALIB_SAMPLING_RNG)
		{
			if(imu_manu_calib_timer_p != NULL && !strcmp("imucal", imu_manu_calib_timer_p->name))
				timer_unset(&imu_manu_calib_timer_p);
			imu_manu_calib_timer_p = NULL;

			imu_auto_calib_info.auto_calib_temp /= (AUTO_CALIB_SAMPLING_RNG - AUTO_CALIB_DISCARD_DATA);
			imu_auto_calib_info.auto_calib_angular_rate_mdps[Rollaxis] /= (AUTO_CALIB_SAMPLING_RNG - AUTO_CALIB_DISCARD_DATA);
			imu_auto_calib_info.auto_calib_angular_rate_mdps[Pitchaxis] /= (AUTO_CALIB_SAMPLING_RNG - AUTO_CALIB_DISCARD_DATA);
			imu_auto_calib_info.auto_calib_angular_rate_mdps[Yawaxis] /= (AUTO_CALIB_SAMPLING_RNG - AUTO_CALIB_DISCARD_DATA);
			imu_auto_calib_info.auto_calib_acceleration_mg[Xaxis] /= (AUTO_CALIB_SAMPLING_RNG - AUTO_CALIB_DISCARD_DATA);
			imu_auto_calib_info.auto_calib_acceleration_mg[Yaxis] /= (AUTO_CALIB_SAMPLING_RNG - AUTO_CALIB_DISCARD_DATA);
			imu_auto_calib_info.auto_calib_acceleration_mg[Zaxis] /= (AUTO_CALIB_SAMPLING_RNG - AUTO_CALIB_DISCARD_DATA);

			if((ism330dlc_info->debug_mode == MORE_IMU_DBG_MSG) || (calib_mode == MANUAL_CALIB))
				PRINTF("IMUDBG: data collected. T:%.2f,Gy[r,p,y]={%.2f,%.2f,%.2f},Acc[x,y,z]={%.2f,%.2f,%.2f}\n",
						imu_auto_calib_info.auto_calib_temp,
						imu_auto_calib_info.auto_calib_angular_rate_mdps[Rollaxis],
						imu_auto_calib_info.auto_calib_angular_rate_mdps[Pitchaxis],
						imu_auto_calib_info.auto_calib_angular_rate_mdps[Yawaxis],
						imu_auto_calib_info.auto_calib_acceleration_mg[Xaxis],
						imu_auto_calib_info.auto_calib_acceleration_mg[Yaxis],
						imu_auto_calib_info.auto_calib_acceleration_mg[Zaxis]);

			return 0;
		}
		else
			return 1;
	}
	else
	{
		if(ism330dlc_info->debug_mode == MORE_IMU_DBG_MSG)
			PRINTF("IMUDBG: Vehicle is moving, clear calib data.\n");

		if(calib_mode == MANUAL_CALIB && imu_manu_calib_timer_p != NULL && !strcmp("imucal", imu_manu_calib_timer_p->name))
			timer_unset(&imu_manu_calib_timer_p);
		imu_manu_calib_timer_p = NULL;

		memset(&imu_auto_calib_info, 0, sizeof(imu_auto_calib_info));
		return 2;
	}
}

static int8_t allow_to_do_overwrite_zrl(uint8_t index_by_temp)
{
	float zrl_change_vs_temp = 0, per_diff = 0;
	uint8_t i = 0, result = 0;
	int8_t ref_temp = AUTO_CALIB_INTERVAL * (index_by_temp - 4);
	float diff_temp = (float)(imu_auto_calib_info.auto_calib_temp - (float)ism330dlc_info->calib_temp[index_by_temp]);

	if(ism330dlc_info->calib_temp[index_by_temp] == IMU_NOT_CALIB && (ref_temp-imu_auto_calib_info.auto_calib_temp <= AUTO_CALIB_INTERVAL-1))
	{
		uint8_t calib_flag_index = 0;
		if(ism330dlc_info->calib_flag == 0)
			return ERROR;

		for(calib_flag_index=0; calib_flag_index<TEMPERATURE_RANGE_IDX; calib_flag_index++)
			if((ism330dlc_info->calib_flag >> calib_flag_index)&1)
				break;

		for(i=0; i<3; i++)
		{
			zrl_change_vs_temp = (imu_auto_calib_info.auto_calib_angular_rate_mdps[i] - (float)ism330dlc_info->zrl[i][calib_flag_index])/
								 (imu_auto_calib_info.auto_calib_temp - (float)ism330dlc_info->calib_temp[calib_flag_index]);

			if(zrl_change_vs_temp < -3*G_TCOFF || zrl_change_vs_temp > 3*G_TCOFF)
				return ERROR;
		}

		if(imu_ac_1st_write.cnt == 0)
		{
			for(i=0; i<3; i++)
				imu_ac_1st_write.sum_of_ar[i]	+= imu_auto_calib_info.auto_calib_angular_rate_mdps[i];
			imu_ac_1st_write.temp_index			= index_by_temp;
			imu_ac_1st_write.sum_of_temp		+= imu_auto_calib_info.auto_calib_temp;
			imu_ac_1st_write.cnt++;
		}
		else if(imu_ac_1st_write.cnt != 0 && imu_ac_1st_write.temp_index == index_by_temp)
		{
			for(i=0; i<3; i++)
				imu_ac_1st_write.sum_of_ar[i]	+= imu_auto_calib_info.auto_calib_angular_rate_mdps[i];
			imu_ac_1st_write.sum_of_temp		+= imu_auto_calib_info.auto_calib_temp;
			imu_ac_1st_write.cnt++;
		}
		else
			memset(&imu_ac_1st_write, 0, sizeof(imu_ac_1st_write));

		if(imu_ac_1st_write.cnt == 5)
			result = 3;
	}
	else if(ref_temp - (int)imu_auto_calib_info.auto_calib_temp >= AUTO_CALIB_INTERVAL)
		return ERROR;
	else if(diff_temp > 0 && diff_temp <1)//very close
	{
		for(i=0; i<3; i++)
		{
			zrl_change_vs_temp = (imu_auto_calib_info.auto_calib_angular_rate_mdps[i] - (float)ism330dlc_info->zrl[i][index_by_temp])/
								 (imu_auto_calib_info.auto_calib_temp - (float)ism330dlc_info->calib_temp[index_by_temp]);
			if(zrl_change_vs_temp < -3*G_TCOFF || zrl_change_vs_temp > 3*G_TCOFF)
				return ERROR;
			else
			{
				per_diff = ABS((imu_auto_calib_info.auto_calib_angular_rate_mdps[i] - (float)ism330dlc_info->zrl[i][index_by_temp]))/
						   ABS((float)ism330dlc_info->zrl[i][index_by_temp]);
				if((per_diff > THREE_PERCENT) && (per_diff < TEN_PERCENT))
					result++;
			}
		}
	}
	else if(diff_temp >= 1)
	{
		for(i=0; i<3; i++)
		{
			zrl_change_vs_temp = (imu_auto_calib_info.auto_calib_angular_rate_mdps[i] - (float)ism330dlc_info->zrl[i][index_by_temp])/
								 (imu_auto_calib_info.auto_calib_temp - (float)ism330dlc_info->calib_temp[index_by_temp]);
			if(zrl_change_vs_temp < -3*G_TCOFF || zrl_change_vs_temp > 3*G_TCOFF)
				return ERROR;
			else
				result++;
		}
	}
	else
		return ERROR;

	if(result == 3)
		return SUCCESS;
	else
		return ERROR;
}

static void calib_IMU(int8_t calib_mode)
{
	filter(CFREQ_L);
	int8_t result = collect_IMU_data_and_take_average_value(calib_mode);

	if(result == SUCCESS)
	{
		if(!is_calib_value_overflow(imu_auto_calib_info.auto_calib_angular_rate_mdps, imu_auto_calib_info.auto_calib_acceleration_mg))
		{
			uint8_t index_offset = 4, index_by_temp = 0;

			if(imu_auto_calib_info.auto_calib_temp > 100)
				index_by_temp = 15;
			else if(imu_auto_calib_info.auto_calib_temp > 0)
				index_by_temp = (uint8_t)(imu_auto_calib_info.auto_calib_temp/AUTO_CALIB_INTERVAL) + index_offset;
			else if(imu_auto_calib_info.auto_calib_temp <= 0 && imu_auto_calib_info.auto_calib_temp > -40)
				index_by_temp = (uint8_t)(imu_auto_calib_info.auto_calib_temp/AUTO_CALIB_INTERVAL) + index_offset - 1;
			else if(imu_auto_calib_info.auto_calib_temp <= -40)
				index_by_temp = 0;
			else
				index_by_temp = (uint8_t)(imu_auto_calib_info.auto_calib_temp/AUTO_CALIB_INTERVAL) + index_offset - 1;

			if(allow_to_do_overwrite_zrl(index_by_temp) == SUCCESS || calib_mode == MANUAL_CALIB)
			{
				if(calib_mode == MANUAL_CALIB)
				{
					imu_calibration_result = SUCCESS;
					ism330dlc_info->calib_flag						|= (1<<index_by_temp);
					ism330dlc_info->calib_temp[index_by_temp]		= imu_auto_calib_info.auto_calib_temp;
					ism330dlc_info->zero_g[Xaxis][index_by_temp]	= imu_auto_calib_info.auto_calib_acceleration_mg[Xaxis];
					ism330dlc_info->zero_g[Yaxis][index_by_temp]	= imu_auto_calib_info.auto_calib_acceleration_mg[Yaxis];
					ism330dlc_info->zero_g[Zaxis][index_by_temp]	= imu_auto_calib_info.auto_calib_acceleration_mg[Zaxis];
					ism330dlc_info->zrl[Pitchaxis][index_by_temp]	= imu_auto_calib_info.auto_calib_angular_rate_mdps[Pitchaxis];
					ism330dlc_info->zrl[Yawaxis][index_by_temp]		= imu_auto_calib_info.auto_calib_angular_rate_mdps[Yawaxis];
					ism330dlc_info->zrl[Rollaxis][index_by_temp]	= imu_auto_calib_info.auto_calib_angular_rate_mdps[Rollaxis];
				}
				else if(((ism330dlc_info->calib_flag >> index_by_temp)&1) == 0)
				{
					imu_calibration_result = SUCCESS;
					if(ism330dlc_info->calib_temp[index_by_temp] != IMU_NOT_CALIB)
					{
						ism330dlc_info->calib_temp[index_by_temp]		= imu_auto_calib_info.auto_calib_temp;
						ism330dlc_info->zrl[Pitchaxis][index_by_temp]	= imu_auto_calib_info.auto_calib_angular_rate_mdps[Pitchaxis];
						ism330dlc_info->zrl[Yawaxis][index_by_temp]		= imu_auto_calib_info.auto_calib_angular_rate_mdps[Yawaxis];
						ism330dlc_info->zrl[Rollaxis][index_by_temp]	= imu_auto_calib_info.auto_calib_angular_rate_mdps[Rollaxis];
					}
					else
					{
						ism330dlc_info->calib_temp[index_by_temp]		= imu_ac_1st_write.sum_of_temp/imu_ac_1st_write.cnt;
						ism330dlc_info->zrl[Pitchaxis][index_by_temp]	= imu_ac_1st_write.sum_of_ar[Pitchaxis]/imu_ac_1st_write.cnt;
						ism330dlc_info->zrl[Yawaxis][index_by_temp]		= imu_ac_1st_write.sum_of_ar[Yawaxis]/imu_ac_1st_write.cnt;
						ism330dlc_info->zrl[Rollaxis][index_by_temp]	= imu_ac_1st_write.sum_of_ar[Rollaxis]/imu_ac_1st_write.cnt;

						memset(&imu_ac_1st_write, 0, sizeof(imu_ac_1st_write));
					}
				}
				else
					imu_calibration_result = ERROR;

				if(imu_calibration_result == SUCCESS)
				{
					pars_set((pars_ctx_p)&ism330dlc_parameters);
					imu_calibrated  = update_imu_comp_info(0);//zero-g
					imu_calibrated += update_imu_comp_info(1);//zero-rate level
					if(calib_mode == MANUAL_CALIB || ism330dlc_info->debug_mode == IMU_DBG_MSG ||
						ism330dlc_info->debug_mode == MORE_IMU_DBG_MSG)
						PRINTF("IMUDBG: Calibrated success.\n");
				}
			}
			else
			{
				imu_calibration_result = ERROR;

				if(calib_mode == MANUAL_CALIB || ism330dlc_info->debug_mode == IMU_DBG_MSG ||
						ism330dlc_info->debug_mode == MORE_IMU_DBG_MSG)
					PRINTF("IMUDBG: Calibrated failure.\n");
			}
		}
		else
		{
			imu_calibration_result = ERROR;

			if(ism330dlc_info->debug_mode == IMU_DBG_MSG || ism330dlc_info->debug_mode == MORE_IMU_DBG_MSG)
				PRINTF("IMUDBG: auto calibration failed, overflow.\n");
		}

		if(imu_calib_cb != NULL)
		{
			imu_calib_result_t calib_result = {};

			if(imu_calibration_result == SUCCESS)
			{
				calib_result.result 			= SUCCESS;
				calib_result.calib_temp			= imu_auto_calib_info.auto_calib_temp;
				calib_result.zero_g[Xaxis]		= (int8_t)imu_auto_calib_info.auto_calib_acceleration_mg[Xaxis];
				calib_result.zero_g[Yaxis]		= (int8_t)imu_auto_calib_info.auto_calib_acceleration_mg[Yaxis];
				calib_result.zero_g[Zaxis]		= (int8_t)imu_auto_calib_info.auto_calib_acceleration_mg[Zaxis];
				calib_result.zrl[Pitchaxis]		= imu_auto_calib_info.auto_calib_angular_rate_mdps[Pitchaxis];
				calib_result.zrl[Yawaxis]		= imu_auto_calib_info.auto_calib_angular_rate_mdps[Yawaxis];
				calib_result.zrl[Rollaxis]		= imu_auto_calib_info.auto_calib_angular_rate_mdps[Rollaxis];
			}
			else
				calib_result.result = ERROR;

//			PRINTF("IMUDBG: res: %d, temp: %d, xl:{%d,%d,%d}, gy:{%.2f, %.2f, %.2f}\n",
//							calib_result.result, calib_result.calib_temp,
//							calib_result.zero_g[Xaxis], calib_result.zero_g[Yaxis], calib_result.zero_g[Zaxis],
//							calib_result.zrl[Rollaxis], calib_result.zrl[Pitchaxis], calib_result.zrl[Yawaxis]);

			imu_calib_cb(&calib_result);
			imu_calib_cb = NULL;
		}
		memset(&imu_auto_calib_info, 0, sizeof(imu_auto_calib_info));
	}
}

static void update_IMU_and_do_dsp_auto_calib(void)
{
	uint8_t is_new_frame = FALSE;

	if(prev_fnum != get_frame_counter())
	{
		prev_fnum = get_frame_counter();
		is_new_frame = TRUE;
	}

	//IMU
	if(detected_imu_flag == TRUE && ism330dlc_info->enable_imu == TRUE)
	{
		ism330dlc_read_gyro_and_xl_and_temp();				//Update IMU data.
		motion_detection();
		update_filtered_imu_data_and_radius(is_new_frame);	//Do dsp.

		//Auto calibration.
		if(get_eps_speed_status() == VEH_STATUS_VALID)
		{
			if(imu_motion.status == MOTION_STATUS_STATIONARY && get_eps_speed_value() == 0.0 && imu_auto_calib_info.spd_equal_to_zero_timer < TWO_SEC)
				imu_auto_calib_info.spd_equal_to_zero_timer++;
			else if((imu_motion.status == MOTION_STATUS_MOVING ||get_eps_speed_value() > 0.0) && imu_auto_calib_info.spd_equal_to_zero_timer)
				imu_auto_calib_info.spd_equal_to_zero_timer = 0;

			if(ism330dlc_info->debug_mode == MORE_IMU_DBG_MSG)
				PRINTF("IMUDBG: auto calib timer(80): %d, motion: %d\n", imu_auto_calib_info.spd_equal_to_zero_timer, imu_motion.status);

			if(imu_auto_calib_info.spd_equal_to_zero_timer >= TWO_SEC)
			{
				if(ism330dlc_info->debug_mode == MORE_IMU_DBG_MSG)
					PRINTF("IMUDBG: do calib\n");

				if(ism330dlc_info->enable_auto_calib == ENABLE)
					calib_IMU(AUTOMATIC_CALIB);
			}
		}
	}

	if(is_new_frame)
	{
		update_filtered_obd_yaw_and_radius();	//OBD
#if JSON_LIST_EN
		send_imu_comp_data_to_imu_info(&imu_comp_info);
#endif
	}

	if(ism330dlc_info->enable_imu == 1 && ism330dlc_info->send_can_msg == 1)
		send_imu_data_by_can(is_new_frame);

	if(imu_cycle_get_timer_p->cnt == 0)
		ism330dlc_timer_disable();
}

static void ism330dlc_reg_read(char** args, int count)
{
	if(count == 3 )
	{
		uint8_t reg_addr = strtoul(args[2], NULL, 16);
		ism330dlc_console_read_reg(reg_addr);
	}
}

static void ism330dlc_reg_write(char** args, int count)
{
	if(count == 4 )
	{
		uint8_t reg_addr =  strtoul(args[2], NULL, 16);
		uint8_t reg_data = (uint8_t) strtoul(args[3], NULL, 16);

		ism330dlc_console_write_reg(reg_addr, reg_data);
		ism330dlc_console_reg_dump(0x76);
	}
}

static void ism330dlc_reg_dump(char** args, int count)
{
	ism330dlc_console_reg_dump(0x76);//read register from Reg[0] to Reg[0x75]
}

static uint8_t is_calib_value_overflow(float* zero_rate_level_mdps, float* src_zero_g_mg)
{
	float factor[3] = {0.0, 0.0, 0.0};
	float temp_zero_mg[3] = {0.0, 0.0, 0.0};

	if(((GRAVITY - imu_calib_boundary_value.zero_g) <= ABS(src_zero_g_mg[Xaxis])) &&
			(ABS(src_zero_g_mg[Xaxis]) <= (GRAVITY + imu_calib_boundary_value.zero_g)))
	{
		if(src_zero_g_mg[Xaxis] > 0)
			factor[Xaxis] = -1;
		else
			factor[Xaxis] = 1;
	}
	else if(((GRAVITY - imu_calib_boundary_value.zero_g) <= ABS(src_zero_g_mg[Yaxis])) &&
			(ABS(src_zero_g_mg[Yaxis]) <= (GRAVITY + imu_calib_boundary_value.zero_g)))
	{
		if(src_zero_g_mg[Yaxis] > 0)
			factor[Yaxis] = -1;
		else
			factor[Yaxis] = 1;
	}
	else
	{
		if(src_zero_g_mg[Zaxis] > 0)
			factor[Zaxis] = -1;
		else
			factor[Zaxis] = 1;
	}

	temp_zero_mg[Xaxis] = src_zero_g_mg[Xaxis] + GRAVITY * factor[Xaxis];
	temp_zero_mg[Yaxis] = src_zero_g_mg[Yaxis] + GRAVITY * factor[Yaxis];
	temp_zero_mg[Zaxis] = src_zero_g_mg[Zaxis] + GRAVITY * factor[Zaxis];

	// Check overflow.
	if( (-imu_calib_boundary_value.zero_g <= temp_zero_mg[Xaxis] && temp_zero_mg[Xaxis] <= imu_calib_boundary_value.zero_g) &&
		(-imu_calib_boundary_value.zero_g <= temp_zero_mg[Yaxis] && temp_zero_mg[Yaxis] <= imu_calib_boundary_value.zero_g) &&
		(-imu_calib_boundary_value.zero_g <= temp_zero_mg[Zaxis] && temp_zero_mg[Zaxis] <= imu_calib_boundary_value.zero_g) &&
		(-imu_calib_boundary_value.zero_rate_level <= zero_rate_level_mdps[Rollaxis]  &&
				zero_rate_level_mdps[Rollaxis]  <= imu_calib_boundary_value.zero_rate_level) &&
		(-imu_calib_boundary_value.zero_rate_level <= zero_rate_level_mdps[Pitchaxis] &&
				zero_rate_level_mdps[Pitchaxis] <= imu_calib_boundary_value.zero_rate_level) &&
		(-imu_calib_boundary_value.zero_rate_level <= zero_rate_level_mdps[Yawaxis] &&
				zero_rate_level_mdps[Yawaxis]   <= imu_calib_boundary_value.zero_rate_level))
	{
		memcpy(src_zero_g_mg, temp_zero_mg, sizeof(temp_zero_mg));
		return 0;
	}
	else
		return 1;
}

static void manu_calib_IMU(void)
{
	ism330dlc_read_gyro_and_xl_and_temp();
	calib_IMU(MANUAL_CALIB);
}

uint8_t ism330dlc_self_calibration_by_RMTP(imu_self_calib_cb cb)
{
	if(detected_imu_flag == 0 || imu_st_cb != NULL)
		return 1;

	char** arguments = (char *[]){"imup", "", "cal"};
	int arguments_count = 2;

	imu_calib_cb = cb;
	ism330dlc_self_calibration(arguments, arguments_count);
	return 0;
}

uint8_t imu_self_test_by_RMTP(imu_self_test_cb cb)
{
	if(detected_imu_flag == 0)
		return 1;
	imu_st_cb = cb;
	self_test_procedure(MANUAL_ST);
	return 0;
}

ism330dlc_info_p ism330dlc_get_IMU_info(void)
{
	return ism330dlc_info;
}

void ism330dlc_set_IMU_calib_value(ism330dlc_info_p imu_calib_val_from_rmtp)
{
	int8_t index = 0, axis_index = 0;

	for(index = 0; index < 8; index++)
		ism330dlc_info->calib_temp[index] = imu_calib_val_from_rmtp->calib_temp[index];

	for(axis_index = 0; axis_index < 3; axis_index++)
		for(index = 0; index <8; index++)
		{
			ism330dlc_info->zero_g[axis_index][index] = imu_calib_val_from_rmtp->zero_g[axis_index][index];
			ism330dlc_info->zrl[axis_index][index]= imu_calib_val_from_rmtp->zrl[axis_index][index];
		}

	pars_set((pars_ctx_p)&ism330dlc_parameters);
}

static void ism330dlc_self_calibration(char** args, int count)
{
	// Input:imup cal, args[0]:imup, args[1]:cal, count:2

	if(count == 2)
	{
		char** arguments = (char *[]){""};
		frame_pause(arguments, 0);

		if(imu_cycle_get_timer_p != NULL && !strcmp("imucycleget", imu_cycle_get_timer_p->name))
			timer_unset(&imu_cycle_get_timer_p);
		imu_cycle_get_timer_p = NULL;

		memset(&imu_auto_calib_info, 0, sizeof(imu_auto_calib_info));

		//clear xl offset reg[73h~75h]
		//ism330dlc_xl_usr_offset_set((uint8_t *)zero_g_mg_coord_IC);

		//Call manu_calib_IMU() every 25ms.
		//set timer to get zero-rate level and zero-g.
		if(imu_manu_calib_timer_p == NULL)
			imu_manu_calib_timer_p = timer_set("imucal", TIMER_25_MS_TICKS, (int16_t)AUTO_CALIB_SAMPLING_RNG, (event_proc_p)manu_calib_IMU, NULL);
	}
	else
	{
		PRINTF("imup cal\n");
	}
}

static void ism330dlc_display_or_set_gy_HPF_LPF1_mode(char** args, int count)
{
	uint8_t index = 0;
	int32_t mm_error = 0;

	if(count == 2)/* Display */
	{
		for(uint8_t i = 0; i<13; i++)
		{
			PRINTF("Mode: #%d. %s\n", i, get_gy_HPF_LPF1_mode_name(i));
		}
		PRINTF("Current mode: #%d. %s\n", ism330dlc_info->gy_HPF_LPF1_mode, get_gy_HPF_LPF1_mode_name(ism330dlc_info->gy_HPF_LPF1_mode));
	}
	else if(count == 3)/* Setting mode */
	{
		index = strtoul(args[2], NULL, 10);
		mm_error = (int32_t)set_gy_HPF_LPF1_mode(index);
		PRINTF("You selected %s mode.\n", get_gy_HPF_LPF1_mode_name(index));

		if(!mm_error)
		{
			// Save to EEPROM.
			ism330dlc_info->gy_HPF_LPF1_mode = index;
			pars_set((pars_ctx_p)&ism330dlc_parameters);
		}
		ism330dlc_pars_dump();
	}
}

static char* get_gy_HPF_LPF1_mode_name(uint8_t index)
{
	switch (index)
	{
		case 0:		return "ISM330DLC_LP2_ONLY";
		case 1:		return "ISM330DLC_HP_16mHz_LP2";
		case 2:		return "ISM330DLC_HP_65mHz_LP2";
		case 3:		return "ISM330DLC_HP_260mHz_LP2";
		case 4:		return "ISM330DLC_HP_1Hz04_LP2";
		case 5:		return "ISM330DLC_HP_DISABLE_LP1_LIGHT";
		case 6:		return "ISM330DLC_HP_DISABLE_LP1_NORMAL";
		case 7:		return "ISM330DLC_HP_DISABLE_LP_STRONG";
		case 8:		return "ISM330DLC_HP_DISABLE_LP1_AGGRESSIVE";
		case 9:		return "ISM330DLC_HP_16mHz_LP1_LIGHT";
		case 10:	return "ISM330DLC_HP_65mHz_LP1_NORMAL";
		case 11:	return "ISM330DLC_HP_260mHz_LP1_STRONG";
		case 12:	return "ISM330DLC_HP_1Hz04_LP1_AGGRESSIVE";
		default:	return "ISM330DLC_HP_DISABLE_LP1_LIGHT";
	}
}

static int set_imu_calib_boundry_values(uint8_t device_id)
{
	if ( device_id == ISM330DLC_ID )
	{
		imu_calib_boundary_value.zero_g = 85.0;
		imu_calib_boundary_value.zero_rate_level = 16000.0;
		imu_calib_boundary_value.xl_calib_thld = 1.191675;
		return 0;
	}
	else if(device_id == ASM330LHH_ID)
	{
		imu_calib_boundary_value.zero_g = 80.0;
		imu_calib_boundary_value.zero_rate_level = 10000.0;
		imu_calib_boundary_value.xl_calib_thld = 1.1792;
		return 0;
	}
	else
	{
		imu_calib_boundary_value.zero_g = 0.0;
		imu_calib_boundary_value.zero_rate_level = 0.0;
		return 1;
	}
}

static int set_gy_HPF_LPF1_mode(uint8_t index)
{
	uint32_t mm_error = 0;

	switch(index)
	{
		case 0:
			mm_error = ism330dlc_gy_band_pass_set_part1(ISM330DLC_LP2_ONLY);
			mm_error = ism330dlc_gy_band_pass_set_part2(ISM330DLC_LP2_ONLY);
			mm_error = ism330dlc_gy_band_pass_set_part3(ISM330DLC_LP2_ONLY);
			break;
		case 1:
			mm_error = ism330dlc_gy_band_pass_set_part1(ISM330DLC_HP_16mHz_LP2);
			mm_error = ism330dlc_gy_band_pass_set_part2(ISM330DLC_HP_16mHz_LP2);
			mm_error = ism330dlc_gy_band_pass_set_part3(ISM330DLC_HP_16mHz_LP2);
			break;
		case 2:
			mm_error = ism330dlc_gy_band_pass_set_part1(ISM330DLC_HP_65mHz_LP2);
			mm_error = ism330dlc_gy_band_pass_set_part2(ISM330DLC_HP_65mHz_LP2);
			mm_error = ism330dlc_gy_band_pass_set_part3(ISM330DLC_HP_65mHz_LP2);
			break;
		case 3:
			mm_error = ism330dlc_gy_band_pass_set_part1(ISM330DLC_HP_260mHz_LP2);
			mm_error = ism330dlc_gy_band_pass_set_part2(ISM330DLC_HP_260mHz_LP2);
			mm_error = ism330dlc_gy_band_pass_set_part3(ISM330DLC_HP_260mHz_LP2);
			break;
		case 4:
			mm_error = ism330dlc_gy_band_pass_set_part1(ISM330DLC_HP_1Hz04_LP2);
			mm_error = ism330dlc_gy_band_pass_set_part2(ISM330DLC_HP_1Hz04_LP2);
			mm_error = ism330dlc_gy_band_pass_set_part3(ISM330DLC_HP_1Hz04_LP2);
			break;
		case 5:
			mm_error = ism330dlc_gy_band_pass_set_part1(ISM330DLC_HP_DISABLE_LP1_LIGHT);
			mm_error = ism330dlc_gy_band_pass_set_part2(ISM330DLC_HP_DISABLE_LP1_LIGHT);
			mm_error = ism330dlc_gy_band_pass_set_part3(ISM330DLC_HP_DISABLE_LP1_LIGHT);
			break;
		case 6:
			mm_error = ism330dlc_gy_band_pass_set_part1(ISM330DLC_HP_DISABLE_LP1_NORMAL);
			mm_error = ism330dlc_gy_band_pass_set_part2(ISM330DLC_HP_DISABLE_LP1_NORMAL);
			mm_error = ism330dlc_gy_band_pass_set_part3(ISM330DLC_HP_DISABLE_LP1_NORMAL);
			break;
		case 7:
			mm_error = ism330dlc_gy_band_pass_set_part1(ISM330DLC_HP_DISABLE_LP_STRONG);
			mm_error = ism330dlc_gy_band_pass_set_part2(ISM330DLC_HP_DISABLE_LP_STRONG);
			mm_error = ism330dlc_gy_band_pass_set_part3(ISM330DLC_HP_DISABLE_LP_STRONG);
			break;
		case 8:
			mm_error = ism330dlc_gy_band_pass_set_part1(ISM330DLC_HP_DISABLE_LP1_AGGRESSIVE);
			mm_error = ism330dlc_gy_band_pass_set_part2(ISM330DLC_HP_DISABLE_LP1_AGGRESSIVE);
			mm_error = ism330dlc_gy_band_pass_set_part3(ISM330DLC_HP_DISABLE_LP1_AGGRESSIVE);
			break;
		case 9:
			mm_error = ism330dlc_gy_band_pass_set_part1(ISM330DLC_HP_16mHz_LP1_LIGHT);
			mm_error = ism330dlc_gy_band_pass_set_part2(ISM330DLC_HP_16mHz_LP1_LIGHT);
			mm_error = ism330dlc_gy_band_pass_set_part3(ISM330DLC_HP_16mHz_LP1_LIGHT);
			break;
		case 10:
			mm_error = ism330dlc_gy_band_pass_set_part1(ISM330DLC_HP_65mHz_LP1_NORMAL);
			mm_error = ism330dlc_gy_band_pass_set_part2(ISM330DLC_HP_65mHz_LP1_NORMAL);
			mm_error = ism330dlc_gy_band_pass_set_part3(ISM330DLC_HP_65mHz_LP1_NORMAL);
			break;
		case 11:
			mm_error = ism330dlc_gy_band_pass_set_part1(ISM330DLC_HP_260mHz_LP1_STRONG);
			mm_error = ism330dlc_gy_band_pass_set_part2(ISM330DLC_HP_260mHz_LP1_STRONG);
			mm_error = ism330dlc_gy_band_pass_set_part3(ISM330DLC_HP_260mHz_LP1_STRONG);
			break;
		case 12:
			mm_error = ism330dlc_gy_band_pass_set_part1(ISM330DLC_HP_1Hz04_LP1_AGGRESSIVE);
			mm_error = ism330dlc_gy_band_pass_set_part2(ISM330DLC_HP_1Hz04_LP1_AGGRESSIVE);
			mm_error = ism330dlc_gy_band_pass_set_part3(ISM330DLC_HP_1Hz04_LP1_AGGRESSIVE);
			break;
		default:
			mm_error = ism330dlc_gy_band_pass_set_part1(ISM330DLC_HP_DISABLE_LP1_LIGHT);
			mm_error = ism330dlc_gy_band_pass_set_part2(ISM330DLC_HP_DISABLE_LP1_LIGHT);
			mm_error = ism330dlc_gy_band_pass_set_part3(ISM330DLC_HP_DISABLE_LP1_LIGHT);
	}

	return (int)mm_error;
}

static void ism330dlc_display_or_set_gy_LPF2_mode(char** args, int count)
{
	uint8_t index = 0;
	int32_t mm_error = 0;

	if(count == 2)/* Display. */
	{
		for(uint8_t i = 0; i<11; i++)
		{
			PRINTF("Mode: #%d. %s\n", i, get_gy_LPF2_mode_name(i));
		}
		PRINTF("Current mode: #%d. %s\n", ism330dlc_info->gy_LPF2_mode, get_gy_LPF2_mode_name(ism330dlc_info->gy_LPF2_mode));
	}
	else if(count == 3)/* Setting mode. */
	{
		index = strtoul(args[2], NULL, 10);
		mm_error = (int32_t)set_gy_LPF2_mode(index);
		PRINTF("You selected %s mode.\n", get_gy_LPF2_mode_name(index));

		if(!mm_error)
		{
			// Save to EEPROM.
			ism330dlc_info->gy_LPF2_mode = index;
			pars_set((pars_ctx_p)&ism330dlc_parameters);
		}
		ism330dlc_pars_dump();
	}
}

static char* get_gy_LPF2_mode_name(uint8_t index)
{
	switch (index)
	{
		case 0:		return "ISM330DLC_GY_ODR_OFF";
		case 1:		return "ISM330DLC_GY_ODR_12Hz5";
		case 2:		return "ISM330DLC_GY_ODR_26Hz";
		case 3:		return "ISM330DLC_GY_ODR_52Hz";
		case 4:		return "ISM330DLC_GY_ODR_104Hz";
		case 5:		return "ISM330DLC_GY_ODR_208Hz";
		case 6:		return "ISM330DLC_GY_ODR_416Hz";
		case 7:		return "ISM330DLC_GY_ODR_833Hz";
		case 8:		return "ISM330DLC_GY_ODR_1k66Hz";
		case 9:		return "ISM330DLC_GY_ODR_3k33Hz";
		case 10:	return "ISM330DLC_GY_ODR_6k66Hz";
		default:	return "ISM330DLC_GY_ODR_52Hz";
	}
}

static int set_gy_LPF2_mode(uint8_t index)
{
	uint32_t mm_error = 0;

	switch(index)
	{
		case 0:
			mm_error = ism330dlc_gy_data_rate_set(ISM330DLC_GY_ODR_OFF);
			break;
		case 1:
			mm_error = ism330dlc_gy_data_rate_set(ISM330DLC_GY_ODR_12Hz5);
			break;
		case 2:
			mm_error = ism330dlc_gy_data_rate_set(ISM330DLC_GY_ODR_26Hz);
			break;
		case 3:
			mm_error = ism330dlc_gy_data_rate_set(ISM330DLC_GY_ODR_52Hz);
			break;
		case 4:
			mm_error = ism330dlc_gy_data_rate_set(ISM330DLC_GY_ODR_104Hz);
			break;
		case 5:
			mm_error = ism330dlc_gy_data_rate_set(ISM330DLC_GY_ODR_208Hz);
			break;
		case 6:
			mm_error = ism330dlc_gy_data_rate_set(ISM330DLC_GY_ODR_416Hz);
			break;
		case 7:
			mm_error = ism330dlc_gy_data_rate_set(ISM330DLC_GY_ODR_833Hz);
			break;
		case 8:
			mm_error = ism330dlc_gy_data_rate_set(ISM330DLC_GY_ODR_1k66Hz);
			break;
		case 9:
			mm_error = ism330dlc_gy_data_rate_set(ISM330DLC_GY_ODR_3k33Hz);
			break;
		case 10:
			mm_error = ism330dlc_gy_data_rate_set(ISM330DLC_GY_ODR_6k66Hz);
			break;
		default:
			mm_error = ism330dlc_gy_data_rate_set(ISM330DLC_GY_ODR_52Hz);
	}

	return (int)mm_error;
}

static void ism330dlc_par_info(char** args, int count)
{
	ism330dlc_read_gyro_and_xl_and_temp();

	PRINTF("IMU info:\n");
	PRINTF("===========================\n");
	if(pars_get((pars_ctx_p)&ism330dlc_parameters, ism330dlc_pars_dump, ism330dlc_info_in_jsons) != -1)
	{
		PRINTF("Gy's filter mode(HPF + LPF1): #%d. %s.\n", ism330dlc_info->gy_HPF_LPF1_mode,
				get_gy_HPF_LPF1_mode_name(ism330dlc_info->gy_HPF_LPF1_mode));
		PRINTF("ODR(LPF2): #%d. %s.\n", ism330dlc_info->gy_LPF2_mode, get_gy_LPF2_mode_name(ism330dlc_info->gy_LPF2_mode));
		PRINTF("angular rate(raw) [roll, pitch, yaw] = {%.2f,%.2f,%.2f} mdps.\n",
				angular_rate_mdps[Rollaxis].raw_data,angular_rate_mdps[Pitchaxis].raw_data,angular_rate_mdps[Yawaxis].raw_data);
		PRINTF("compensated angular rate [roll, pitch, yaw] = {%.2f,%.2f,%.2f} mdps.\n",
				angular_rate_mdps[Rollaxis].compensated_data, angular_rate_mdps[Pitchaxis].compensated_data,
				angular_rate_mdps[Yawaxis].compensated_data);
		PRINTF("acceleration(raw) [x, y, z] = {%.2f,%.2f,%.2f} mg.\n",
				acceleration_mg[Xaxis].raw_data, acceleration_mg[Yaxis].raw_data, acceleration_mg[Zaxis].raw_data);
		PRINTF("compensated acceleration [x, y, z] = {%.2f,%.2f,%.2f} mg.\n",
				acceleration_mg[Xaxis].compensated_data, acceleration_mg[Yaxis].compensated_data,
				acceleration_mg[Zaxis].compensated_data);
		PRINTF("Temperature = %.1f degC.\n", temperature_degC);
	}
	else
	{
		PRINTF("Can't read IMU's parameters from EEPROM.\n");
	}
}

static void ism330dlc_display_or_set_fm(char** args, int count)
{
	if(count == 3) // write
	{
		ism330dlc_info->filter_mode = (uint8)atoi(args[2]);
		pars_set((pars_ctx_p)&ism330dlc_parameters);
	}
	ism330dlc_pars_dump();
}

static void ism330dlc_display_or_set_fc(char** args, int count)
{
	float obd_yaw_fl_coef = 0.0, imu_yaw_fl_coef = 0.0;

	if(count == 4) // write
	{
		if(atof(args[2]) <= 1.0 && atof(args[3]) <= 0.255)
		{
			obd_yaw_fl_coef = (uint8_t)(atof(args[2])*100);
			imu_yaw_fl_coef = (uint8_t)(atof(args[3])*1000);

			ism330dlc_info->filter_coef[0] = obd_yaw_fl_coef;
			ism330dlc_info->filter_coef[1] = imu_yaw_fl_coef;
			pars_set((pars_ctx_p)&ism330dlc_parameters);
		}
	}
	ism330dlc_pars_dump();
}

static void ism330dlc_display_or_set_thld(char** args, int count)
{
	if(count == 6) // write
	{
		ism330dlc_info->yaw_rate_thld[0] = atoi(args[2]);
		ism330dlc_info->yaw_rate_thld[1] = (uint8_t)(atof(args[3])*10.0);
		ism330dlc_info->yaw_rate_thld[2] = (uint8_t)(atof(args[4])*10.0);
		ism330dlc_info->yaw_rate_thld[3] = atoi(args[5]);
		pars_set((pars_ctx_p)&ism330dlc_parameters);
	}
	ism330dlc_pars_dump();
}

static void ism330dlc_display_or_set_calib_flag(char** args, int count)
{
	if(count == 3) // write
	{
		ism330dlc_info->calib_flag = strtoul(args[2], NULL, 16);
		pars_set((pars_ctx_p)&ism330dlc_parameters);
	}
	ism330dlc_pars_dump();
}

static void ism330dlc_display_or_set_yob(char** args, int count)
{
	if(count == 3) // write
	{
		ism330dlc_info->yaw_onboard = atoi(args[2]);
		pars_set((pars_ctx_p)&ism330dlc_parameters);
	}
	ism330dlc_pars_dump();
}

static void ism330dlc_display_or_set_dbg(char** args, int count)
{
	uint8_t dbg = 0;

	if(count == 3) // write
	{
		dbg = atoi(args[2]);
		if(dbg <= 3)
		{
			ism330dlc_info->debug_mode = dbg;
			pars_set((pars_ctx_p)&ism330dlc_parameters);
		}
	}
	ism330dlc_pars_dump();
}

static void ism330dlc_display_or_set_send_can_msg(char** args, int count)
{
	uint8_t input = 0;

	if(count == 3) // write
	{
		input = atoi(args[2]);
		ism330dlc_info->send_can_msg = input;
		pars_set((pars_ctx_p)&ism330dlc_parameters);
	}
	ism330dlc_pars_dump();
}

static void ism330dlc_display_or_set_auto_calib(char** args, int count)
{
	int8_t input = 0;

	if(count == 3) // write
	{
		input = (int8_t)atoi(args[2]);
		ism330dlc_info->enable_auto_calib = input;
		pars_set((pars_ctx_p)&ism330dlc_parameters);
	}
	ism330dlc_pars_dump();
}

static void ism330dlc_display_or_set_calib_temp(char** args, int count)
{
	if(count == 18) // write
	{
		int8_t index = 0;
		for(index = 0; index < 16; index++)
			ism330dlc_info->calib_temp[index] = (int8_t)atoi(args[2 + index]);
		pars_set((pars_ctx_p)&ism330dlc_parameters);
	}
	ism330dlc_pars_dump();
}

static void ism330dlc_display_or_set_zero_g(char** args, int count)
{
	if(count == 19) // write
	{
		int8_t index = 0;
		int8_t xl_axis = 0;
		int8_t input_value = 0;

		if(!strcmp(args[2], "x"))
			xl_axis = Xaxis;
		else if(!strcmp(args[2], "y"))
			xl_axis = Yaxis;
		else if(!strcmp(args[2], "z"))
			xl_axis = Zaxis;
		else
			return;

		for(index = 0; index < 16; index++)
		{
			input_value = (int8_t)atoi(args[3 + index]);
			if(-imu_calib_boundary_value.zero_g <= input_value && input_value <= imu_calib_boundary_value.zero_g)
				ism330dlc_info->zero_g[xl_axis][index] = input_value;
		}

		pars_set((pars_ctx_p)&ism330dlc_parameters);
	}
	ism330dlc_pars_dump();
}

static void ism330dlc_display_or_set_zero_rate_level(char** args, int count)
{
	if(count == 19) // write
	{
		int8_t index = 0;
		int8_t gyro_axis = 0;
		int16_t input_value = 0.0;

		if(!strcmp(args[2], "pitch"))
			gyro_axis = Pitchaxis;
		else if(!strcmp(args[2], "roll"))
			gyro_axis = Rollaxis;
		else if(!strcmp(args[2], "yaw"))
			gyro_axis = Yawaxis;
		else
			return;

		for(index = 0; index < 16; index++)
		{
			input_value = (int16_t)atoi(args[3 + index]);
			if(-imu_calib_boundary_value.zero_rate_level <= input_value  && input_value  <= imu_calib_boundary_value.zero_rate_level)
				ism330dlc_info->zrl[gyro_axis][index] = input_value;
		}

		pars_set((pars_ctx_p)&ism330dlc_parameters);
	}
	ism330dlc_pars_dump();
}

static void set_imu_enable_or_disable(char** args, int count)
{
	if(count == 3) // write
	{
		uint8_t input = atoi(args[2]);

		if(0 == input || 1 == input)
		{
			ism330dlc_info->enable_imu = input;
			pars_set((pars_ctx_p)&ism330dlc_parameters);
		}
	}
	ism330dlc_pars_dump();
}

static void ism330dlc_display_or_set_motion_detection_thld(char** args, int count)
{
	if(count == 3) // write
	{
		uint8_t input = (uint8_t)atoi(args[2]);

		if(input < 64)
		{
			ism330dlc_info->mthld = input;
			pars_set((pars_ctx_p)&ism330dlc_parameters);
		}
	}
	ism330dlc_pars_dump();
}

static void ism330dlc_display_or_set_ag(char** args, int count)
{
	if(count == 5) // write
	{
		float ag0 = atof(args[2]);
		float ag1 = atof(args[3]);
		float ag2 = atof(args[4]);

		if((0.9 < ag0 && ag0 < 1.1) && (0.9 < ag1 && ag1 < 1.1) && (0.9 < ag2 && ag2 < 1.1))
		{
			ism330dlc_info->ar_gain[0] = ag0;
			ism330dlc_info->ar_gain[1] = ag1;
			ism330dlc_info->ar_gain[2] = ag2;
			pars_set((pars_ctx_p)&ism330dlc_parameters);
		}
	}
	ism330dlc_pars_dump();
}

static void ism330dlc_display_or_set_dir(char** args, int count)
{
	if(count == 3) // write
	{
		uint8_t input = (uint8_t)atoi(args[2]);

		if(input < 6)
		{
			ism330dlc_info->dir = input;
			pars_set((pars_ctx_p)&ism330dlc_parameters);
		}
	}
	ism330dlc_pars_dump();
}

static int8_t is_self_test_done()
{
	if(detected_imu_flag == FALSE)
		return FALSE;
	else if(imu_self_test.acc_self_test_result == SUCCESS && imu_self_test.gyro_self_test_result == SUCCESS)
		return TRUE;
	else
	{
		if(get_frame_counter()%SELF_TEST_INTERVAL == 5)
			self_test_flag = TRUE;

		//if self-test undone/failure, do self-test every 100 frames.
		if(self_test_flag == TRUE)
		{
			if(get_eps_speed_value() == 0 && imu_self_test.current_phase == 0)
			{
				//Self test procedure.
				if(imu_cycle_get_timer_p != NULL && !strcmp("imucycleget", imu_cycle_get_timer_p->name))
					timer_unset(&imu_cycle_get_timer_p);
				imu_cycle_get_timer_p = NULL;
				self_test_procedure(AUTOMATIC_ST);
				self_test_flag = FALSE;
			}
		}
		return FALSE;
	}
}

void ism330dlc_timer_enable(void)
{
	if(imu_cycle_get_timer_p != NULL)
		return;

	if(get_eps_speed_status() != VEH_STATUS_VALID || imu_calibrated != SUCCESS)
	{
		//set vehicle module status: acc & gyro invalid.
		set_imu_status_to_vehicle_module(0, 1);
		set_imu_status_to_vehicle_module(1, 1);
		return;
	}

	if(ism330dlc_info->enable_imu == 1 && detected_imu_flag == 1 && is_self_test_done() == TRUE)//enable imu.
		imu_cycle_get_timer_p = timer_set("imucycleget", TIMER_25_MS_TICKS, -1,(event_proc_p)update_IMU_and_do_dsp_auto_calib, NULL);
	else if(ism330dlc_info->enable_imu == 1 && detected_imu_flag == 1 && ism330dlc_info->debug_mode == ENABLE_IMU_DBG)//run imu even if spd != 0.
		imu_cycle_get_timer_p = timer_set("imucycleget", TIMER_25_MS_TICKS, 200,(event_proc_p)update_IMU_and_do_dsp_auto_calib, NULL);
//	else if(ism330dlc_info->enable_imu == 0 && ism330dlc_info->yaw_onboard == 0)//disable imu, using obd yaw.
//		imu_cycle_get_timer_p = timer_set("imucycleget", TIMER_25_MS_TICKS, -1,(event_proc_p)update_IMU_and_do_dsp_auto_calib, NULL);
}

void ism330dlc_timer_disable(void)
{
	if (imu_cycle_get_timer_p != NULL && !strcmp("imucycleget", imu_cycle_get_timer_p->name))
		timer_unset(&imu_cycle_get_timer_p);
	imu_cycle_get_timer_p = NULL;
}

static void ism330dlc_parameter_setting(char** args, int count)
{
	// Input:imup ghl1, args[0]:imup, args[1]:ghl1, count:2
	if (count >= 2) {
		if (!strcmp(args[1], "ghl1")) {
			ism330dlc_display_or_set_gy_HPF_LPF1_mode(args, count);
		} else if (!strcmp(args[1], "glp2")) {
			ism330dlc_display_or_set_gy_LPF2_mode(args, count);
		} else if (!strcmp(args[1], "fm")) {
			ism330dlc_display_or_set_fm(args, count);
		} else if (!strcmp(args[1], "fc")) {
			ism330dlc_display_or_set_fc(args, count);
		} else if (!strcmp(args[1], "thld")) {
			ism330dlc_display_or_set_thld(args, count);
		} else if (!strcmp(args[1], "cf")) {
			ism330dlc_display_or_set_calib_flag(args, count);
		} else if (!strcmp(args[1], "yob")) {
			ism330dlc_display_or_set_yob(args, count);
		} else if (!strcmp(args[1], "dbg")) {
			ism330dlc_display_or_set_dbg(args, count);
		} else if (!strcmp(args[1], "imu")) {
			set_imu_enable_or_disable(args, count);
		} else if (!strcmp(args[1], "can")) {
			ism330dlc_display_or_set_send_can_msg(args, count);
		} else if (!strcmp(args[1], "ac")) {
			ism330dlc_display_or_set_auto_calib(args, count);
		} else if (!strcmp(args[1], "ct")) {
			ism330dlc_display_or_set_calib_temp(args, count);
		} else if (!strcmp(args[1], "zg")) {
			ism330dlc_display_or_set_zero_g(args, count);
		} else if (!strcmp(args[1], "zrl")) {
			ism330dlc_display_or_set_zero_rate_level(args, count);
		} else if (!strcmp(args[1], "cal")) {
			ism330dlc_self_calibration(args, count);
		} else if (!strcmp(args[1], "info")) {
			ism330dlc_par_info(args, count);
		} else if (!strcmp(args[1], "regr")) {
			ism330dlc_reg_read(args, count);
		} else if (!strcmp(args[1], "regw")) {
			ism330dlc_reg_write(args, count);
		} else if (!strcmp(args[1], "regd")) {
			ism330dlc_reg_dump(args, count);
		} else if (!strcmp(args[1], "st")) {
			manual_self_test(args, count);
		} else if (!strcmp(args[1], "mthld")) {
			ism330dlc_display_or_set_motion_detection_thld(args, count);
		} else if (!strcmp(args[1], "ag")) {
			ism330dlc_display_or_set_ag(args, count);
		} else if (!strcmp(args[1], "dir")) {
			ism330dlc_display_or_set_dir(args, count);
		} else
			PRINTF("Unsupported command: %s.\n", args[1]);
	} else {
		ism330dlc_pars_dump();
	}
}

static void ism330dlc_console_commands_reg(void)
{
	console_command_reg("imup",		ism330dlc_parameter_setting);
}

static int ism330dlc_info_in_jsons(char* ws)
{
	int cnt = 0;
	if(ws){
		cnt = sprintf(ws,"{\n");
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_ID, (char)(ISM330DLC_PARS_ID>>24), (char)(ISM330DLC_PARS_ID>>16),
				(char)(ISM330DLC_PARS_ID>>8),(char)(ISM330DLC_PARS_ID));
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_VERSION, ism330dlc_parameters.hdr.version);
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_SIZE, ism330dlc_parameters.hdr.size  - sizeof(pars_header_t));
		cnt += sprintf(ws+cnt,"\t\"info\":{\n");
		cnt += sprintf(ws+cnt, JSON_ENABLE_IMU, offsetof(ism330dlc_info_t, enable_imu), ism330dlc_info->enable_imu);
		cnt += sprintf(ws+cnt, JSON_SEND_CAN_MSG, offsetof(ism330dlc_info_t, send_can_msg), ism330dlc_info->send_can_msg);
		cnt += sprintf(ws+cnt, JSON_YAW_ONBOARD, offsetof(ism330dlc_info_t, yaw_onboard), ism330dlc_info->yaw_onboard);
		cnt += sprintf(ws+cnt, JSON_DEBUG_MODE, offsetof(ism330dlc_info_t, debug_mode), ism330dlc_info->debug_mode);
		cnt += sprintf(ws+cnt, JSON_GY_HPF_LPF1, offsetof(ism330dlc_info_t, gy_HPF_LPF1_mode), ism330dlc_info->gy_HPF_LPF1_mode);
		cnt += sprintf(ws+cnt, JSON_GY_LPF2, offsetof(ism330dlc_info_t, gy_LPF2_mode), ism330dlc_info->gy_LPF2_mode);
		cnt += sprintf(ws+cnt, JSON_ENABLE_AUTO_CALIB, offsetof(ism330dlc_info_t, enable_auto_calib), ism330dlc_info->enable_auto_calib);
		cnt += sprintf(ws+cnt, JSON_FILTER_MODE, offsetof(ism330dlc_info_t, filter_mode), ism330dlc_info->filter_mode);
		cnt += sprintf(ws+cnt, JSON_FILTER_COEF, offsetof(ism330dlc_info_t, filter_coef),
				ism330dlc_info->filter_coef[0], ism330dlc_info->filter_coef[1]);
		cnt += sprintf(ws+cnt, JSON_MOTION_THLD, offsetof(ism330dlc_info_t, mthld), ism330dlc_info->mthld);
		cnt += sprintf(ws+cnt, JSON_YAW_RATE_THLD, offsetof(ism330dlc_info_t, yaw_rate_thld), ism330dlc_info->yaw_rate_thld[0],
				ism330dlc_info->yaw_rate_thld[1], ism330dlc_info->yaw_rate_thld[2], ism330dlc_info->yaw_rate_thld[3]);
		cnt += sprintf(ws+cnt, JSON_CALIB_FLAG, offsetof(ism330dlc_info_t, calib_flag), ism330dlc_info->calib_flag);
		cnt += sprintf(ws+cnt, JSON_CALIB_TEMP, offsetof(ism330dlc_info_t, calib_temp),
				ism330dlc_info->calib_temp[0],  ism330dlc_info->calib_temp[1],  ism330dlc_info->calib_temp[2],  ism330dlc_info->calib_temp[3],
				ism330dlc_info->calib_temp[4],  ism330dlc_info->calib_temp[5],  ism330dlc_info->calib_temp[6],  ism330dlc_info->calib_temp[7],
				ism330dlc_info->calib_temp[8],  ism330dlc_info->calib_temp[9],  ism330dlc_info->calib_temp[10], ism330dlc_info->calib_temp[11],
				ism330dlc_info->calib_temp[12], ism330dlc_info->calib_temp[13], ism330dlc_info->calib_temp[14], ism330dlc_info->calib_temp[15]);
		cnt += sprintf(ws+cnt, JSON_ZERO_G, offsetof(ism330dlc_info_t, zero_g),
				ism330dlc_info->zero_g[Xaxis][0],  ism330dlc_info->zero_g[Xaxis][1],  ism330dlc_info->zero_g[Xaxis][2],  ism330dlc_info->zero_g[Xaxis][3],
				ism330dlc_info->zero_g[Xaxis][4],  ism330dlc_info->zero_g[Xaxis][5],  ism330dlc_info->zero_g[Xaxis][6],  ism330dlc_info->zero_g[Xaxis][7],
				ism330dlc_info->zero_g[Xaxis][8],  ism330dlc_info->zero_g[Xaxis][9],  ism330dlc_info->zero_g[Xaxis][10], ism330dlc_info->zero_g[Xaxis][11],
				ism330dlc_info->zero_g[Xaxis][12], ism330dlc_info->zero_g[Xaxis][13], ism330dlc_info->zero_g[Xaxis][14], ism330dlc_info->zero_g[Xaxis][15],
				ism330dlc_info->zero_g[Yaxis][0],  ism330dlc_info->zero_g[Yaxis][1],  ism330dlc_info->zero_g[Yaxis][2],  ism330dlc_info->zero_g[Yaxis][3],
				ism330dlc_info->zero_g[Yaxis][4],  ism330dlc_info->zero_g[Yaxis][5],  ism330dlc_info->zero_g[Yaxis][6],  ism330dlc_info->zero_g[Yaxis][7],
				ism330dlc_info->zero_g[Yaxis][8],  ism330dlc_info->zero_g[Yaxis][9],  ism330dlc_info->zero_g[Yaxis][10], ism330dlc_info->zero_g[Yaxis][11],
				ism330dlc_info->zero_g[Yaxis][12], ism330dlc_info->zero_g[Yaxis][13], ism330dlc_info->zero_g[Yaxis][14], ism330dlc_info->zero_g[Yaxis][15],
				ism330dlc_info->zero_g[Yaxis][0],  ism330dlc_info->zero_g[Yaxis][1],  ism330dlc_info->zero_g[Yaxis][2],  ism330dlc_info->zero_g[Yaxis][3],
				ism330dlc_info->zero_g[Zaxis][4],  ism330dlc_info->zero_g[Zaxis][5],  ism330dlc_info->zero_g[Zaxis][6],  ism330dlc_info->zero_g[Zaxis][7],
				ism330dlc_info->zero_g[Zaxis][8],  ism330dlc_info->zero_g[Zaxis][9],  ism330dlc_info->zero_g[Zaxis][10], ism330dlc_info->zero_g[Zaxis][11],
				ism330dlc_info->zero_g[Zaxis][12], ism330dlc_info->zero_g[Zaxis][13], ism330dlc_info->zero_g[Zaxis][14], ism330dlc_info->zero_g[Zaxis][15]);
		cnt += sprintf(ws+cnt, JSON_ZERO_RATE_LEVEL, offsetof(ism330dlc_info_t, zrl),
				ism330dlc_info->zrl[Pitchaxis][0],  ism330dlc_info->zrl[Pitchaxis][1],  ism330dlc_info->zrl[Pitchaxis][2],  ism330dlc_info->zrl[Pitchaxis][3],
				ism330dlc_info->zrl[Pitchaxis][4],  ism330dlc_info->zrl[Pitchaxis][5],  ism330dlc_info->zrl[Pitchaxis][6],  ism330dlc_info->zrl[Pitchaxis][7],
				ism330dlc_info->zrl[Pitchaxis][8],  ism330dlc_info->zrl[Pitchaxis][9],  ism330dlc_info->zrl[Pitchaxis][10], ism330dlc_info->zrl[Pitchaxis][11],
				ism330dlc_info->zrl[Pitchaxis][12], ism330dlc_info->zrl[Pitchaxis][13], ism330dlc_info->zrl[Pitchaxis][14], ism330dlc_info->zrl[Pitchaxis][15],
				ism330dlc_info->zrl[Yawaxis][0],  ism330dlc_info->zrl[Yawaxis][1],  ism330dlc_info->zrl[Yawaxis][2],  ism330dlc_info->zrl[Yawaxis][3],
				ism330dlc_info->zrl[Yawaxis][4],  ism330dlc_info->zrl[Yawaxis][5],  ism330dlc_info->zrl[Yawaxis][6],  ism330dlc_info->zrl[Yawaxis][7],
				ism330dlc_info->zrl[Yawaxis][8],  ism330dlc_info->zrl[Yawaxis][9],  ism330dlc_info->zrl[Yawaxis][10], ism330dlc_info->zrl[Yawaxis][11],
				ism330dlc_info->zrl[Yawaxis][12], ism330dlc_info->zrl[Yawaxis][13], ism330dlc_info->zrl[Yawaxis][14], ism330dlc_info->zrl[Yawaxis][15],
				ism330dlc_info->zrl[Rollaxis][0],  ism330dlc_info->zrl[Rollaxis][1],  ism330dlc_info->zrl[Rollaxis][2],  ism330dlc_info->zrl[Rollaxis][3],
				ism330dlc_info->zrl[Rollaxis][4],  ism330dlc_info->zrl[Rollaxis][5],  ism330dlc_info->zrl[Rollaxis][6],  ism330dlc_info->zrl[Rollaxis][7],
				ism330dlc_info->zrl[Rollaxis][8],  ism330dlc_info->zrl[Rollaxis][9],  ism330dlc_info->zrl[Rollaxis][10], ism330dlc_info->zrl[Rollaxis][11],
				ism330dlc_info->zrl[Rollaxis][12], ism330dlc_info->zrl[Rollaxis][13], ism330dlc_info->zrl[Rollaxis][14], ism330dlc_info->zrl[Rollaxis][15]);
		cnt += sprintf(ws+cnt, JSON_AR_GAIN, offsetof(ism330dlc_info_t, ar_gain), ism330dlc_info->ar_gain[0], ism330dlc_info->ar_gain[1], ism330dlc_info->ar_gain[2]);
		cnt += sprintf(ws+cnt, JSON_AR_DIR, offsetof(ism330dlc_info_t, dir), ism330dlc_info->dir);
		cnt += sprintf(ws+cnt, "\t}\n}\n");
	}
	return cnt;
}

static void ism330dlc_pars_dump(void)
{
	int i, j;
	pars_get((pars_ctx_p)&ism330dlc_parameters, ism330dlc_pars_dump, ism330dlc_info_in_jsons);

	PRINTF("<IMU>\n- version: %d\n- size: %d\n", ism330dlc_parameters.hdr.version, sizeof(ism330dlc_pars_t));
	PRINTF("- imu(Enable imu): %d, [0:OFF, 1:ON]\n", ism330dlc_info->enable_imu);
	PRINTF("- can(Send CAN msg): %d, [0:OFF, 1:ON]\n", ism330dlc_info->send_can_msg);
	PRINTF("- yob(Yaw rate onboard): %d, [0:trk using OBD, 1:trk using IMU]\n", ism330dlc_info->yaw_onboard);
	PRINTF("- dbg(Debug mode): %d, [0:OFF, 1:ON]\n", ism330dlc_info->debug_mode);
	PRINTF("- ghl1(Gyrosope's HPF&LPF1 mode): #%d. %s\n", ism330dlc_info->gy_HPF_LPF1_mode,
			get_gy_HPF_LPF1_mode_name(ism330dlc_info->gy_HPF_LPF1_mode));
	PRINTF("- glp2(Gyrosope's LPF2 mode): #%d. %s\n", ism330dlc_info->gy_LPF2_mode, get_gy_LPF2_mode_name(ism330dlc_info->gy_LPF2_mode));
	PRINTF("- ac(Enable auto calib): %d\n", ism330dlc_info->enable_auto_calib);
	PRINTF("- fm(Filter mode): %d, [0:1st, 1:2nd]\n", ism330dlc_info->filter_mode);
	PRINTF("- fc(Filter's coef): {%.2f, %.3f}\n", ism330dlc_info->filter_coef[0]*0.01, ism330dlc_info->filter_coef[1]*0.001);
	PRINTF("- mthld(Motion detection thld): %d\n", ism330dlc_info->mthld);
	PRINTF("- thld(Yaw's thld): [spd(kph), yaw, laneW(m), laneL(m)]={%d, %.1f, %.1f, %d}\n",
		ism330dlc_info->yaw_rate_thld[0], ism330dlc_info->yaw_rate_thld[1]*0.1, ism330dlc_info->yaw_rate_thld[2]*0.1, ism330dlc_info->yaw_rate_thld[3]);
	PRINTF("- cf(Calib flag): %04Xh\n", ism330dlc_info->calib_flag);

	PRINTF("- ct(Calib temp):\n");
	for(i = 0; i<16; i++)
	{
		if(i == 0)
			PRINTF("\t{%d, ", ism330dlc_info->calib_temp[i]);
		else if(i == 7)
			PRINTF("%d,\n", ism330dlc_info->calib_temp[i]);
		else if(i == 8)
			PRINTF("\t %d, ", ism330dlc_info->calib_temp[i]);
		else if(i == 15)
			PRINTF("%d}\n", ism330dlc_info->calib_temp[i]);
		else
			PRINTF("%d, ", ism330dlc_info->calib_temp[i]);
	}

	PRINTF("- zg(Zero-g):\n");
	for(i = Xaxis; i<= Zaxis; i++)
	{
		for(j = 0; j< 16; j++)
		{
			if(i == Xaxis && j == 0)
				PRINTF("\tx: {%d, ", ism330dlc_info->zero_g[i][j]);
			else if(i == Yaxis && j == 0)
				PRINTF("\ty: {%d, ", ism330dlc_info->zero_g[i][j]);
			else if(i == Zaxis && j == 0)
				PRINTF("\tz: {%d, ", ism330dlc_info->zero_g[i][j]);
			else if(j == 7)
				PRINTF("%d,\n", ism330dlc_info->zero_g[i][j]);
			else if(j == 8)
				PRINTF("\t    %d, ", ism330dlc_info->zero_g[i][j]);
			else if(j == 15)
				PRINTF("%d}\n", ism330dlc_info->zero_g[i][j]);
			else
				PRINTF("%d, ", ism330dlc_info->zero_g[i][j]);
		}
	}

	PRINTF("- zrl(Zero-rate level):\n");
	for(i = Pitchaxis; i<= Rollaxis; i++)
	{
		for(j = 0; j< 16; j++)
		{
			if(i == Pitchaxis && j == 0)
				PRINTF("\tpitch: {%d, ", ism330dlc_info->zrl[i][j]);
			else if(i == Yawaxis && j == 0)
				PRINTF("\t  yaw: {%d, ", ism330dlc_info->zrl[i][j]);
			else if(i == Rollaxis && j == 0)
				PRINTF("\t roll: {%d, ", ism330dlc_info->zrl[i][j]);
			else if(j == 7)
				PRINTF("%d,\n", ism330dlc_info->zrl[i][j]);
			else if(j == 8)
				PRINTF("\t        %d, ", ism330dlc_info->zrl[i][j]);
			else if(j == 15)
				PRINTF("%d}\n", ism330dlc_info->zrl[i][j]);
			else
				PRINTF("%d, ", ism330dlc_info->zrl[i][j]);
		}
	}

	PRINTF("- ag(Angular rate gain): {%.5f, %.5f, %.5f}\n",
			ism330dlc_info->ar_gain[0], ism330dlc_info->ar_gain[1], ism330dlc_info->ar_gain[2]);
	PRINTF("- dir(Direction): %d\n", ism330dlc_info->dir);
}

static float iir_filter(float current_yaw_rate)
{
	float filtered_yaw_rate;

	filtered_yaw_rate = (ism330dlc_info->filter_coef[0]*0.01 * vehicle_yaw0) + (1 - ism330dlc_info->filter_coef[0]*0.01) * current_yaw_rate;
	vehicle_yaw0 = filtered_yaw_rate;

	if (ABS(filtered_yaw_rate) <= ism330dlc_info->yaw_rate_thld[1]/10.0f) {
		filtered_yaw_rate = 0.0;
	}

	return filtered_yaw_rate;
}

static int8_t update_imu_comp_info(int8_t mode)
{
	int8_t i = 0, j = 0, k = 0;
	int8_t sorted_temp_stamp[TEMPERATURE_RANGE_IDX];
	int8_t sorted_temp_index[TEMPERATURE_RANGE_IDX] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	int8_t calib_value_cnt = 0;

	memcpy(sorted_temp_stamp, ism330dlc_info->calib_temp, sizeof(sorted_temp_stamp));

	for (i = 0; i < TEMPERATURE_RANGE_IDX; i++)
		if (mode == 0)//zero-g
			if (ism330dlc_info->zero_g[Xaxis][i] != IMU_NOT_CALIB)
			{
				calib_value_cnt++;
				k = i;
			}
			else
				sorted_temp_stamp[i] = IMU_NOT_CALIB;
		else if (mode == 1)//zero-rate level
			if (ism330dlc_info->calib_temp[i] != IMU_NOT_CALIB)
			{
				calib_value_cnt++;
				k = i;
			}

	if (calib_value_cnt == 0)
	{
		if (mode == 0)//zero-g
		{
			memset(imu_comp_info.acc_slope_table,  0, sizeof(imu_comp_info.acc_slope_table));
			memset(imu_comp_info.acc_offset_table, 0, sizeof(imu_comp_info.acc_offset_table));
		}
		else if (mode == 1)//zero-rate level
		{
			memset(imu_comp_info.gyro_slope_table,  0, sizeof(imu_comp_info.gyro_slope_table));
			memset(imu_comp_info.gyro_offset_table, 0, sizeof(imu_comp_info.gyro_offset_table));
		}
		return ERROR;
	}
	else if (calib_value_cnt == 1)
	{
		if (mode == 0)//zero-g
		{
			memset(imu_comp_info.acc_slope_table,  0, sizeof(imu_comp_info.acc_slope_table));

			for (i = 0; i < 3; i++)
				for (j = 0; j < TEMPERATURE_RANGE_IDX - 1; j++)
					imu_comp_info.acc_offset_table[i][j] = ism330dlc_info->zero_g[i][k];
			return SUCCESS;
		}
		else if (mode == 1)//zero-rate level
		{
			memset(imu_comp_info.gyro_slope_table, 0, sizeof(imu_comp_info.gyro_slope_table));

			for (i = 0; i < 3; i++)
				for (j = 0; j < TEMPERATURE_RANGE_IDX - 1; j++)
					imu_comp_info.gyro_offset_table[i][j] = ism330dlc_info->zrl[i][k];
			return SUCCESS;
		}
	}
	else
	{
		int slope_cnt = calib_value_cnt - 1;
		int highest_t_idx = calib_value_cnt - 1;

		if (mode == 0)//zero-g
		{
			imu_calib_values_sort_by_temp(sorted_temp_stamp, sorted_temp_index);

			for (i = 0; i < slope_cnt; i++)
				for (j = sorted_temp_index[i]; j < sorted_temp_index[i + 1]; j++)
					for (k = 0; k < 3; k++)//axis
					{
						if ((ism330dlc_info->calib_temp[sorted_temp_index[i + 1]] - ism330dlc_info->calib_temp[sorted_temp_index[i]]) == 0)
							imu_comp_info.acc_slope_table[k][j] = 0;
						else
							imu_comp_info.acc_slope_table[k][j] =
									(int16_t)((float)(ism330dlc_info->zero_g[k][sorted_temp_index[i + 1]] - ism330dlc_info->zero_g[k][sorted_temp_index[i]])/
									(ism330dlc_info->calib_temp[sorted_temp_index[i + 1]] - ism330dlc_info->calib_temp[sorted_temp_index[i]])*SLOPE_FACTOR);

						imu_comp_info.acc_offset_table[k][j] = ism330dlc_info->zero_g[k][sorted_temp_index[i]] -
														imu_comp_info.acc_slope_table[k][j]/SLOPE_FACTOR*ism330dlc_info->calib_temp[sorted_temp_index[i]];
					}

			for (i = sorted_temp_index[highest_t_idx]; i < TEMPERATURE_RANGE_IDX - 1; i++)
				for (k = 0; k < 3; k++)//axis
				{
					imu_comp_info.acc_slope_table[k][i] = imu_comp_info.acc_slope_table[k][sorted_temp_index[highest_t_idx] - 1];
					imu_comp_info.acc_offset_table[k][i] = imu_comp_info.acc_offset_table[k][sorted_temp_index[highest_t_idx] - 1];
				}

			for (i = 0; i < sorted_temp_index[0]; i++)
				for (k = 0; k < 3; k++)//axis
				{
					imu_comp_info.acc_slope_table[k][i]  = imu_comp_info.acc_slope_table[k][sorted_temp_index[0]];
					imu_comp_info.acc_offset_table[k][i] = imu_comp_info.acc_offset_table[k][sorted_temp_index[0]];
				}

			return SUCCESS;
		}
		else if (mode == 1)//zero-rate level
		{
			imu_calib_values_sort_by_temp(sorted_temp_stamp, sorted_temp_index);

			for (i = 0; i < slope_cnt; i++)
				for (j = sorted_temp_index[i]; j < sorted_temp_index[i + 1]; j++)
					for (k = 0; k < 3; k++)//axis
					{
						if ((ism330dlc_info->calib_temp[sorted_temp_index[i + 1]] - ism330dlc_info->calib_temp[sorted_temp_index[i]]) == 0)
							imu_comp_info.gyro_slope_table[k][j] = 0;
						else
							imu_comp_info.gyro_slope_table[k][j] =
									(int16_t)((float)(ism330dlc_info->zrl[k][sorted_temp_index[i+1]] - ism330dlc_info->zrl[k][sorted_temp_index[i]]) /
									(ism330dlc_info->calib_temp[sorted_temp_index[i+1]] - ism330dlc_info->calib_temp[sorted_temp_index[i]])*SLOPE_FACTOR);

						imu_comp_info.gyro_offset_table[k][j] = ism330dlc_info->zrl[k][sorted_temp_index[i]] -
															imu_comp_info.gyro_slope_table[k][j]/SLOPE_FACTOR*ism330dlc_info->calib_temp[sorted_temp_index[i]];
					}

			for (i = sorted_temp_index[highest_t_idx]; i < TEMPERATURE_RANGE_IDX - 1; i++)
				for (k = 0; k < 3; k++)//axis
				{
					imu_comp_info.gyro_slope_table[k][i]  = imu_comp_info.gyro_slope_table[k][sorted_temp_index[highest_t_idx] - 1];
					imu_comp_info.gyro_offset_table[k][i] = imu_comp_info.gyro_offset_table[k][sorted_temp_index[highest_t_idx] - 1];
				}

			for (i = 0; i < sorted_temp_index[0]; i++)
				for (k = 0; k < 3; k++)//axis
				{
					imu_comp_info.gyro_slope_table[k][i]  = imu_comp_info.gyro_slope_table[k][sorted_temp_index[0]];
					imu_comp_info.gyro_offset_table[k][i] = imu_comp_info.gyro_offset_table[k][sorted_temp_index[0]];
				}

			return SUCCESS;
		}
	}

	return SUCCESS;
}

static void imu_calib_values_sort_by_temp(int8_t *sorted_temp_stamp, int8_t *sorted_temp_index)
{
	int8_t i = 0, j = 0, tmp = 0;

	for (i = 0; i < 15; i++)
		for (j = 0; j < 15 - i; j++)
			if (sorted_temp_stamp[j] > sorted_temp_stamp[j + 1])
			{
				tmp = sorted_temp_stamp[j];
				sorted_temp_stamp[j] = sorted_temp_stamp[j + 1];
				sorted_temp_stamp[j + 1] = tmp;

				tmp = sorted_temp_index[j];
				sorted_temp_index[j] = sorted_temp_index[j + 1];
				sorted_temp_index[j + 1] = tmp;
			}
}

static void compensate_function(void)
{
	int index = 0, i = 0;

	if (temperature_degC <= -40)
		index = 0;
	else if (temperature_degC >= 110)
		index = 14;
	else if(temperature_degC >=0)
		index = temperature_degC / 10 + 4;
	else
		index = temperature_degC / 10 + 3;

	for(i=0; i<3; i++)//axis
	{
		imu_comp_info.acc_slope[i] = imu_comp_info.acc_slope_table[i][index];
		imu_comp_info.acc_offset[i] = imu_comp_info.acc_offset_table[i][index];
		imu_comp_info.gyro_slope[i] = imu_comp_info.gyro_slope_table[i][index];
		imu_comp_info.gyro_offset[i] = imu_comp_info.gyro_offset_table[i][index];

		acceleration_mg[i].compensated_data   = acceleration_mg[i].raw_data -
				imu_comp_info.acc_slope[i]/SLOPE_FACTOR*temperature_degC - imu_comp_info.acc_offset[i];
		angular_rate_mdps[i].compensated_data = angular_rate_mdps[i].raw_data -
				imu_comp_info.gyro_slope[i]/SLOPE_FACTOR*temperature_degC - imu_comp_info.gyro_offset[i];
	}
}

static void filter(uint8_t mode)
{
	for(uint8_t axis_index = 0; axis_index < 3; axis_index++)
	{
		if(ism330dlc_info->filter_mode == 0)
		{
			if(mode == CFREQ_H)
			{
				//angular_rate
				angular_rate_mdps[axis_index].in_1st[0]	= angular_rate_mdps[axis_index].in_1st[1];
				angular_rate_mdps[axis_index].out_1st[0]	= angular_rate_mdps[axis_index].out_1st[1];
				angular_rate_mdps[axis_index].in_1st[1] = angular_rate_mdps[axis_index].compensated_data / GAIN_1ST_H;
				angular_rate_mdps[axis_index].out_1st[1] = (angular_rate_mdps[axis_index].in_1st[0] + angular_rate_mdps[axis_index].in_1st[1]) +
																( COEF_1ST_H * angular_rate_mdps[axis_index].out_1st[0]);

				if (ABS(angular_rate_mdps[axis_index].out_1st[1]) < ism330dlc_info->filter_coef[1])
					angular_rate_mdps[axis_index].out_1st[1] = 0.0;

				angular_rate_mdps[axis_index].filtered_data = angular_rate_mdps[axis_index].out_1st[1];

				//acceleration
				acceleration_mg[axis_index].in_1st[0]	= acceleration_mg[axis_index].in_1st[1];
				acceleration_mg[axis_index].out_1st[0]	= acceleration_mg[axis_index].out_1st[1];
				acceleration_mg[axis_index].in_1st[1] = acceleration_mg[axis_index].compensated_data / GAIN_1ST_H;
				acceleration_mg[axis_index].out_1st[1] = (acceleration_mg[axis_index].in_1st[0] + acceleration_mg[axis_index].in_1st[1]) +
																( COEF_1ST_H * acceleration_mg[axis_index].out_1st[0]);
				acceleration_mg[axis_index].filtered_data = acceleration_mg[axis_index].out_1st[1];
			}
			else if(mode == CFREQ_L)
			{
				angular_rate_mdps_for_cal[axis_index].in_1st[0]	= angular_rate_mdps_for_cal[axis_index].in_1st[1];
				angular_rate_mdps_for_cal[axis_index].out_1st[0]	= angular_rate_mdps_for_cal[axis_index].out_1st[1];
				acceleration_mg_for_cal[axis_index].in_1st[0]	= acceleration_mg_for_cal[axis_index].in_1st[1];
				acceleration_mg_for_cal[axis_index].out_1st[0]	= acceleration_mg_for_cal[axis_index].out_1st[1];

				//angular_rate
				angular_rate_mdps_for_cal[axis_index].in_1st[1] = angular_rate_mdps[axis_index].raw_data / GAIN_1ST_L;
				angular_rate_mdps_for_cal[axis_index].out_1st[1] = (angular_rate_mdps_for_cal[axis_index].in_1st[0] + angular_rate_mdps_for_cal[axis_index].in_1st[1]) +
															( COEF_1ST_L * angular_rate_mdps_for_cal[axis_index].out_1st[0]);
				angular_rate_mdps_for_cal[axis_index].filtered_data = angular_rate_mdps_for_cal[axis_index].out_1st[1];

				//acceleration
				acceleration_mg_for_cal[axis_index].in_1st[1] = acceleration_mg[axis_index].raw_data / GAIN_1ST_L;
				acceleration_mg_for_cal[axis_index].out_1st[1] = (acceleration_mg_for_cal[axis_index].in_1st[0] + acceleration_mg_for_cal[axis_index].in_1st[1]) +
															( COEF_1ST_L * acceleration_mg_for_cal[axis_index].out_1st[0]);
				acceleration_mg_for_cal[axis_index].filtered_data = acceleration_mg_for_cal[axis_index].out_1st[1];
			}
		}
		else if(ism330dlc_info->filter_mode == 1)
		{
			if(mode == CFREQ_H)
			{
				//angular rate
				angular_rate_mdps[axis_index].in_2nd[0]	= angular_rate_mdps[axis_index].in_2nd[1];
				angular_rate_mdps[axis_index].in_2nd[1]	= angular_rate_mdps[axis_index].in_2nd[2];
				angular_rate_mdps[axis_index].in_2nd[2]	= angular_rate_mdps[axis_index].compensated_data / GAIN_2ND_H;
				angular_rate_mdps[axis_index].out_2nd[0]	= angular_rate_mdps[axis_index].out_2nd[1];
				angular_rate_mdps[axis_index].out_2nd[1]	= angular_rate_mdps[axis_index].out_2nd[2];

				angular_rate_mdps[axis_index].out_2nd[2] =
						(angular_rate_mdps[axis_index].in_2nd[0] + angular_rate_mdps[axis_index].in_2nd[2]) +
						2*angular_rate_mdps[axis_index].in_2nd[1] + ( COEF1_2ND_H * angular_rate_mdps[axis_index].out_2nd[0]) +
						(  COEF2_2ND_H * angular_rate_mdps[axis_index].out_2nd[1]);

				if (ABS(angular_rate_mdps[axis_index].out_2nd[2]) < ism330dlc_info->filter_coef[1])
					angular_rate_mdps[axis_index].out_2nd[2] = 0.0;

				angular_rate_mdps[axis_index].filtered_data = angular_rate_mdps[axis_index].out_2nd[2];

				//acceleration
				acceleration_mg[axis_index].in_2nd[0]	= acceleration_mg[axis_index].in_2nd[1];
				acceleration_mg[axis_index].in_2nd[1]	= acceleration_mg[axis_index].in_2nd[2];
				acceleration_mg[axis_index].in_2nd[2]	= acceleration_mg[axis_index].compensated_data / GAIN_2ND_H;
				acceleration_mg[axis_index].out_2nd[0]	= acceleration_mg[axis_index].out_2nd[1];
				acceleration_mg[axis_index].out_2nd[1]	= acceleration_mg[axis_index].out_2nd[2];

				acceleration_mg[axis_index].out_2nd[2] =
						(acceleration_mg[axis_index].in_2nd[0] + acceleration_mg[axis_index].in_2nd[2]) +
						2*acceleration_mg[axis_index].in_2nd[1] + ( COEF1_2ND_H * acceleration_mg[axis_index].out_2nd[0]) +
						(  COEF2_2ND_H * acceleration_mg[axis_index].out_2nd[1]);

				acceleration_mg[axis_index].filtered_data = acceleration_mg[axis_index].out_2nd[2];
			}
			else if(mode == CFREQ_L)
			{
				//angular rate
				angular_rate_mdps_for_cal[axis_index].in_2nd[0]	= angular_rate_mdps_for_cal[axis_index].in_2nd[1];
				angular_rate_mdps_for_cal[axis_index].in_2nd[1]	= angular_rate_mdps_for_cal[axis_index].in_2nd[2];
				angular_rate_mdps_for_cal[axis_index].in_2nd[2]	= angular_rate_mdps[axis_index].raw_data / GAIN_2ND_L;
				angular_rate_mdps_for_cal[axis_index].out_2nd[0]	= angular_rate_mdps_for_cal[axis_index].out_2nd[1];
				angular_rate_mdps_for_cal[axis_index].out_2nd[1]	= angular_rate_mdps_for_cal[axis_index].out_2nd[2];

				angular_rate_mdps_for_cal[axis_index].out_2nd[2] =
						(angular_rate_mdps_for_cal[axis_index].in_2nd[0] + angular_rate_mdps_for_cal[axis_index].in_2nd[2]) +
						2*angular_rate_mdps_for_cal[axis_index].in_2nd[1] + ( COEF1_2ND_L * angular_rate_mdps_for_cal[axis_index].out_2nd[0]) +
						(  COEF2_2ND_L * angular_rate_mdps_for_cal[axis_index].out_2nd[1]);

				angular_rate_mdps_for_cal[axis_index].filtered_data = angular_rate_mdps_for_cal[axis_index].out_2nd[2];

				//acceleration
				acceleration_mg_for_cal[axis_index].in_2nd[0]	= acceleration_mg_for_cal[axis_index].in_2nd[1];
				acceleration_mg_for_cal[axis_index].in_2nd[1]	= acceleration_mg_for_cal[axis_index].in_2nd[2];
				acceleration_mg_for_cal[axis_index].in_2nd[2]	= acceleration_mg[axis_index].raw_data / GAIN_2ND_L;
				acceleration_mg_for_cal[axis_index].out_2nd[0]	= acceleration_mg_for_cal[axis_index].out_2nd[1];
				acceleration_mg_for_cal[axis_index].out_2nd[1]	= acceleration_mg_for_cal[axis_index].out_2nd[2];

				acceleration_mg_for_cal[axis_index].out_2nd[2] =
						(acceleration_mg_for_cal[axis_index].in_2nd[0] + acceleration_mg_for_cal[axis_index].in_2nd[2]) +
						2*acceleration_mg_for_cal[axis_index].in_2nd[1] + ( COEF1_2ND_L * acceleration_mg_for_cal[axis_index].out_2nd[0]) +
						(  COEF2_2ND_L * acceleration_mg_for_cal[axis_index].out_2nd[1]);

				acceleration_mg_for_cal[axis_index].filtered_data = acceleration_mg_for_cal[axis_index].out_2nd[2];
			}
		}
	}
}

static void motion_detection()
{
	uint8_t wu_ia	= (imu_motion.reg >> 3) & 1;
	uint8_t x_wu	= (imu_motion.reg >> 2) & 1;
	uint8_t y_wu	= (imu_motion.reg >> 1) & 1;
	uint8_t z_wu	= imu_motion.reg & 1;

	if(get_eps_speed_status() == VEH_STATUS_VALID)
	{
		if(x_wu || z_wu || (get_eps_speed_value() != 0))
		{
			if(imu_motion.cnt >= -2)//moving
				imu_motion.cnt--;
		}
		else
		{
			if(imu_motion.cnt <= 2)//stationary
				imu_motion.cnt++;
		}
	}
	else
	{
		imu_motion.cnt = 0;
		imu_motion.status = MOTION_STATUS_UNKNOWN;
		set_veh_motion_status_not_get_value();
		return;
	}

	if(imu_motion.cnt == 3)
	{
		imu_motion.status = MOTION_STATUS_STATIONARY;
		set_veh_motion_status_stationary_value();
	}
	else
	{
		imu_motion.status = MOTION_STATUS_MOVING;
		set_veh_motion_status_moving_value();
	}

	if(ism330dlc_info->debug_mode == MORE_IMU_DBG_MSG)
		PRINTF("IMUDBG: status:%d,reg:[%d%d%d%d],cnt:%d\n", imu_motion.status, wu_ia, x_wu, y_wu, z_wu, imu_motion.cnt);
}

static void self_test_discard_1st_data(void *current_phase)
{
	imu_self_test.current_phase = *((uint8_t *)current_phase);
	self_test_phase_p = &imu_self_test.current_phase;

	if (imu_timer_p != NULL && !strcmp("imu_discard_1st_data", imu_timer_p->name))
		timer_unset(&imu_timer_p);
	imu_timer_p = NULL;

//	PRINTF("IMUDBG: Enter func-self_test_discard_1st_data, phase: %d\n", imu_self_test.current_phase);

	if((imu_self_test.current_phase == COLLECT_NOST_SPD_0 || imu_self_test.current_phase == COLLECT_ST_SPD_0) &&
	   (get_eps_speed_status() != VEH_STATUS_VALID || get_eps_speed_value() != 0.0))
	{
		memset(&imu_self_test, 0, sizeof(imu_self_test));
		imu_self_test.acc_self_test_result = IMU_ST_UNDONE;
		imu_self_test.gyro_self_test_result = IMU_ST_UNDONE;
		self_test_phase_p = NULL;
		restore_imu_to_default();
		return;
	}

	ism330dlc_read_gyro_and_xl_and_temp();
//	PRINTF("IMUDBG: Gyro = {%04hx,%04hx,%04hx}, Acc = {%04hx,%04hx,%04hx} --- discard\n",
//			angular_rate_mdps[Rollaxis].raw_data_bits, angular_rate_mdps[Pitchaxis].raw_data_bits, angular_rate_mdps[Yawaxis].raw_data_bits,
//			acceleration_mg[Xaxis].raw_data_bits, acceleration_mg[Yaxis].raw_data_bits, acceleration_mg[Zaxis].raw_data_bits);

	if((imu_self_test.current_phase == COLLECT_NOST_SPD_0 || imu_self_test.current_phase == COLLECT_NOST) && imu_timer_p == NULL)
		imu_timer_p = timer_set("imu_nost_collect", TIMER_25_MS_TICKS, 5, (event_proc_p)self_test_data_collector, self_test_phase_p);
	else if((imu_self_test.current_phase == COLLECT_ST_SPD_0 || imu_self_test.current_phase == COLLECT_ST) && imu_timer_p == NULL)
		imu_timer_p = timer_set("imu_st_collect", TIMER_25_MS_TICKS, 5, (event_proc_p)self_test_data_collector, self_test_phase_p);
	else
		return;
}

static void self_test_data_collector(void *current_phase)
{
	imu_self_test.current_phase = *((uint8_t *)current_phase);
//	PRINTF("IMUDBG: Enter func-self_test_data_collector, phase: %d\n", imu_self_test.current_phase);

	if((imu_self_test.current_phase == COLLECT_NOST_SPD_0 || imu_self_test.current_phase == COLLECT_ST_SPD_0) &&
	   (get_eps_speed_status() != VEH_STATUS_VALID || get_eps_speed_value() != 0.0))
	{
		if (imu_timer_p != NULL && (!strcmp("imu_nost_collect", imu_timer_p->name) || !strcmp("imu_st_collect", imu_timer_p->name)))
			timer_unset(&imu_timer_p);
		imu_timer_p = NULL;

		if(imu_self_test.current_phase == COLLECT_ST_SPD_0)
		{
			//Gyro & Acc:	Disable self-test and disable Gyro & Acc sensor.
			uint8_t regs[10] = {0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
			ism330dlc_config_self_test((uint8_t *)regs);
		}

		restore_imu_to_default();
		memset(&imu_self_test, 0, sizeof(imu_self_test));
		imu_self_test.acc_self_test_result = IMU_ST_UNDONE;
		imu_self_test.gyro_self_test_result = IMU_ST_UNDONE;
		self_test_phase_p = NULL;
		return;
	}

	ism330dlc_read_gyro_and_xl_and_temp();
//	PRINTF("IMUDBG: cnt:%d, Gyro = {%04hx,%04hx,%04hx}, Acc = {%04hx,%04hx,%04hx}\n", imu_self_test.cnt,
//			sg_data_raw_angular_rate[Rollaxis], sg_data_raw_angular_rate[Pitchaxis], sg_data_raw_angular_rate[Yawaxis],
//			sg_data_raw_acceleration_mg[Xaxis], sg_data_raw_acceleration_mg[Yaxis], sg_data_raw_acceleration_mg[Zaxis]);

	if(imu_self_test.current_phase == COLLECT_NOST_SPD_0 || imu_self_test.current_phase == COLLECT_NOST)
	{
		// Gyro
		imu_self_test.gyro_out_nost[Rollaxis]	+= ISM330DLC_FROM_FS_2000dps_TO_mdps(sg_data_raw_angular_rate[Rollaxis])*0.0002;
		imu_self_test.gyro_out_nost[Pitchaxis]	+= ISM330DLC_FROM_FS_2000dps_TO_mdps(sg_data_raw_angular_rate[Pitchaxis])*0.0002;
		imu_self_test.gyro_out_nost[Yawaxis]	+= ISM330DLC_FROM_FS_2000dps_TO_mdps(sg_data_raw_angular_rate[Yawaxis])*0.0002;
		// Acc
		imu_self_test.acc_out_nost[Xaxis]	+= ISM330DLC_FROM_FS_4g_TO_mg(sg_data_raw_acceleration_mg[Xaxis])*0.2;
		imu_self_test.acc_out_nost[Yaxis]	+= ISM330DLC_FROM_FS_4g_TO_mg(sg_data_raw_acceleration_mg[Yaxis])*0.2;
		imu_self_test.acc_out_nost[Zaxis]	+= ISM330DLC_FROM_FS_4g_TO_mg(sg_data_raw_acceleration_mg[Zaxis])*0.2;

		imu_self_test.cnt++;

		if(imu_self_test.cnt == 5)
		{
			if (imu_timer_p != NULL && !strcmp("imu_nost_collect", imu_timer_p->name))
				timer_unset(&imu_timer_p);
			imu_timer_p = NULL;

			if(imu_self_test.current_phase == COLLECT_NOST_SPD_0)
				imu_self_test.current_phase = COLLECT_ST_SPD_0;
			else if(imu_self_test.current_phase == COLLECT_NOST)
				imu_self_test.current_phase = COLLECT_ST;

			self_test_phase_p = &imu_self_test.current_phase;
			imu_self_test.cnt = 0;//Clear reg.
			ism330dlc_console_write_reg(ISM330DLC_CTRL5_C, 0x05);//Enable acc & gyro self test.
			if(imu_timer_p == NULL)
				imu_timer_p = timer_set("imu_discard_1st_data", TIMER_100_MS_TICKS, 1, (event_proc_p)self_test_discard_1st_data, self_test_phase_p);
		}
	}
	else if(imu_self_test.current_phase == COLLECT_ST_SPD_0 || imu_self_test.current_phase == COLLECT_ST)
	{
		uint8_t i = 0; //for loop
		uint8_t acc_result = 0, gyro_result = 0;

		//Gyro
		imu_self_test.gyro_out_st[Rollaxis]	+= ISM330DLC_FROM_FS_2000dps_TO_mdps(sg_data_raw_angular_rate[Rollaxis]) *0.0002;
		imu_self_test.gyro_out_st[Pitchaxis]+= ISM330DLC_FROM_FS_2000dps_TO_mdps(sg_data_raw_angular_rate[Pitchaxis])*0.0002;
		imu_self_test.gyro_out_st[Yawaxis]	+= ISM330DLC_FROM_FS_2000dps_TO_mdps(sg_data_raw_angular_rate[Yawaxis])	 *0.0002;

		//Acc
		imu_self_test.acc_out_st[Xaxis]	+= ISM330DLC_FROM_FS_4g_TO_mg(sg_data_raw_acceleration_mg[Xaxis])*0.2;
		imu_self_test.acc_out_st[Yaxis]	+= ISM330DLC_FROM_FS_4g_TO_mg(sg_data_raw_acceleration_mg[Yaxis])*0.2;
		imu_self_test.acc_out_st[Zaxis]	+= ISM330DLC_FROM_FS_4g_TO_mg(sg_data_raw_acceleration_mg[Zaxis])*0.2;

		imu_self_test.cnt++;

		if(imu_self_test.cnt == 5)
		{
			//Pass or fail.
//			PRINTF("IMUDBG: acc,    out_st(avg): {%.1f, %.1f, %.1f}\n",
//					imu_self_test.acc_out_st[Rollaxis], imu_self_test.acc_out_st[Pitchaxis], imu_self_test.acc_out_st[Yawaxis]);
//			PRINTF("IMUDBG: acc,  out_nost(avg): {%.1f, %.1f, %.1f}\n",
//					imu_self_test.acc_out_nost[Rollaxis], imu_self_test.acc_out_nost[Pitchaxis], imu_self_test.acc_out_nost[Yawaxis]);
//			PRINTF("IMUDBG: gyro,   out_st(avg): {%.1f, %.1f, %.1f}\n",
//					imu_self_test.gyro_out_st[Rollaxis], imu_self_test.gyro_out_st[Pitchaxis], imu_self_test.gyro_out_st[Yawaxis]);
//			PRINTF("IMUDBG: gyro, out_nost(avg): {%.1f, %.1f, %.1f}\n",
//					imu_self_test.gyro_out_nost[Rollaxis], imu_self_test.gyro_out_nost[Pitchaxis], imu_self_test.gyro_out_nost[Yawaxis]);

			for(i=0; i<3; i++)
			{
				//Acc
				if((ACC_ST_MIN <= ABS(imu_self_test.acc_out_st[i] - imu_self_test.acc_out_nost[i])) &&
						(ABS(imu_self_test.acc_out_st[i] - imu_self_test.acc_out_nost[i]) <= ACC_ST_MAX))
					acc_result += 1;
				//Gyro
				if((GYRO_ST_MIN <= ABS(imu_self_test.gyro_out_st[i] - imu_self_test.gyro_out_nost[i])) &&
						(ABS(imu_self_test.gyro_out_st[i] - imu_self_test.gyro_out_nost[i]) <= GYRO_ST_MAX))
					gyro_result += 1;
			}

			memset(&imu_self_test, 0, sizeof(imu_self_test));
			self_test_phase_p = NULL;

			if (imu_timer_p != NULL && !strcmp("imu_st_collect", imu_timer_p->name))
				timer_unset(&imu_timer_p);
			imu_timer_p = NULL;

			if(acc_result == 3)
				imu_self_test.acc_self_test_result = IMU_ST_SUCCESS;
			else
				imu_self_test.gyro_self_test_result = IMU_ST_FAILED;

			if(gyro_result == 3)
				imu_self_test.gyro_self_test_result = IMU_ST_SUCCESS;
			else
				imu_self_test.gyro_self_test_result = IMU_ST_FAILED;

			if(imu_self_test.acc_self_test_result == IMU_ST_SUCCESS && imu_self_test.gyro_self_test_result == IMU_ST_SUCCESS)
			{
				set_monitoring_result_by_id(MONITOR_ID_IMU, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED);
				if(ism330dlc_info->debug_mode == IMU_DBG_MSG || ism330dlc_info->debug_mode == MORE_IMU_DBG_MSG)
					PRINTF("IMUDBG: self-test success\n");
			}
			else
			{
				set_monitoring_result_by_id(MONITOR_ID_IMU, MONITOR_RESULT_FAILED, MONITOR_RESULT_CODE_ERROR);
				set_imu_status_to_vehicle_module(0, 1);
				set_imu_status_to_vehicle_module(1, 1);
				if(ism330dlc_info->debug_mode == IMU_DBG_MSG || ism330dlc_info->debug_mode == MORE_IMU_DBG_MSG)
					PRINTF("IMUDBG: self-test result: failed. {%d, %d}.\n",
							imu_self_test.acc_self_test_result, imu_self_test.gyro_self_test_result);
			}

			//Gyro & Acc:	Disable self-test and disable Gyro & Acc sensor.
			uint8_t regs[10] = {0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
			ism330dlc_config_self_test((uint8_t *)regs);

			restore_imu_to_default();
		}
	}
	else
		return;
}

static void self_test_procedure(uint8_t st_mode)
{
	if(st_mode == AUTOMATIC_ST)
	{
		imu_self_test.current_phase = COLLECT_NOST_SPD_0;
		self_test_phase_p = &imu_self_test.current_phase;
	}
	else if(st_mode == MANUAL_ST)
	{
		imu_self_test.current_phase = COLLECT_NOST;
		self_test_phase_p = &imu_self_test.current_phase;
	}
	else
		return;

	//Gyro:	Initial and turn on sensor, set BDU = 1, ODR = 208 Hz, FS = +-2000 dps.
	//Acc:	Initial and turn on sensor, set BDU = 1, ODR =  52 Hz, FS =    +-4 g.
	uint8_t regs[10] = {0x38, 0x5C, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	ism330dlc_config_self_test((uint8_t *)regs);

	if(sg_whoamI == ASM330LHH_ID && imu_timer_p == NULL)
		imu_timer_p = timer_set("imu_discard_1st_data", TIMER_100_MS_TICKS, 1, (event_proc_p)self_test_discard_1st_data, self_test_phase_p);
	else if(sg_whoamI == ISM330DLC_ID && imu_timer_p == NULL)
		imu_timer_p = timer_set("imu_discard_1st_data", TIMER_200_MS_TICKS, 1, (event_proc_p)self_test_discard_1st_data, self_test_phase_p);
	else
		return;
}

static void manual_self_test(char** args, int count)
{
	if(count == 2)
		self_test_procedure(MANUAL_ST);
	else
		return;
}
