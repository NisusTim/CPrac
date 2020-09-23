/*
 * coefs.h
 *
 *  Created on: Feb 16, 2019
 *      Author: erichu
 */

#ifndef CORE_DETECTIONS_COEFS_H_
#define CORE_DETECTIONS_COEFS_H_

#include "detections.h"

//#define AOAIDXS_SET
#define AOAIDX_INVALID	BINS_OF_AOA_FFT
typedef struct _aoaidxs_table {
	float			asin[BINS_OF_AOA_FFT+1];		// radians
	float			sin[BINS_OF_AOA_FFT];		// value of sin
	float			cos[BINS_OF_AOA_FFT];		// value od cos
}aoaidxs_table_t,*aoaidxs_table_p;

#define COEFS_PARS_ID					FOURCC('c','l','b','r')
#define DEFAULT_SCALE_VALUE				32767
typedef struct {
	tram_value_t	fft3d_long[CHIRPS_PER_FRAME][2][FFT3D_BINS];
	tram_value_t	fft3d_near[FFT3D_BINS];
	tram_value_t	fft3d_amap4[TOTAL_RX_ACTIVES];
	tram_value_t	fft3d_amap8[TOTAL_RX_ACTIVES];
	float_cmplx_t	aoa_long[CHIRPS_PER_FRAME*2][TOTAL_RX_ACTIVES];// positive aoa coefs for virtual array
	float_cmplx_t	aoa_near[RX_ACTIVES];
	float_cmplx_t	music_table[200][8];
	int16_t			win512[512];
	int16_t			win256[256];
	int16_t			win128[128];

#ifdef AOAIDXS_SET
	aoaidxs_table_t aoaidxs;
#endif

	uint32_t		coefs_id;
	uint16_t		updcnt;
	uint16_t		version;
} rv_cmps_data_t, *rv_cmps_data_p;


// size of target_aoa_data_t : (512+16+32) = 560B
typedef struct {
	complex24_t 	t1t2[TOTAL_RX_ACTIVES*3];
	complex24_t		t1[TOTAL_RX_ACTIVES*2];
	complex24_t		t2[TOTAL_RX_ACTIVES*3];
	float_cmplx_t 	tv[2];
	uint32_t		pv[2][16];
}target_aoa_data_t,*target_aoa_data_p;

typedef enum {
	WIN_IDX_RANGE = 0,
	WIN_IDX_DOPPLER,
	WIN_IDX_COUNT
}WIN_IDX_E;

typedef struct {
	double_cmplx_t	coefs[TOTAL_RX_ACTIVES];
	uint32_t		opts_aoa;
	uint32_t		opts_fft3d;
	int8_t			win_types[WIN_IDX_COUNT];
	int8_t			win_factors[WIN_IDX_COUNT];
	int8_t			maps_ant[RX_ACTIVES*3];
} coefs_data_t,*coefs_data_p;

typedef enum {
	CAL_OPT_CIRCUIT,
	CAL_OPT_BUMPER,
	CAL_OPT_INVALID
}CAL_OPT;

void coefs_init(coefs_data_p, void(*)(void));
void coefs_calib_start(float clb, float angle, CAL_OPT opt,void(*)(float,float));
int coefs_calib_ranged_measurement(float clb_angle, float clb_range, void(*)(void*));
void coefs_target_cmplx_cmps(target_p, target_aoa_data_p, int);
uint8_t coefs_overlapped_rx_get(void);
float coefs_phase_differ(complex24_p, complex24_p);
void coefs_print_cmpsed_cmplx(target_aoa_data_p, int);
float aoaidx_asin(int16_t idx);
float aoaidx_sin(int16_t idx);
float aoaidx_cos(int16_t idx);

typedef enum {
    COEFS_CMPS_INIT = 0,
    COEFS_CMPS_CALIB_ONLY,
    COEFS_CMPS_WIN_ONLY,
	COEFS_CMPS_AOAIDXS_ONLY,
    COEFS_CMPS_ALL
}COEFS_CMPS_SET_MODE_E;
void coefs_cmps_set(COEFS_CMPS_SET_MODE_E);

void print_cmpsed_cmplx(target_aoa_data_p tad, int order);

#define ZERO_CALIBRATION_BW 300                          //zero calibration use bandwidth(each unit = 1MHz).
int8_t set_calibration_bandwidth(uint16_t bandwidth);    //set zero angle calibration used bandwidth.
uint16_t get_calibration_bandwidth(void);                //get zero angle calibration used bandwidth.

//---calib iron-get-----
#define CALIB_IRON_PARS_ID							FOURCC('c','l','b','i')
#define CALIB_IRON_PARS_VERSION_MAJOR				0x06
#define CALIB_IRON_PARS_VERSION_MINOR				0x00
#define VERSION_OF_CALIB_IRON_PARS    				(((uint16_t)CALIB_IRON_PARS_VERSION_MAJOR<<8) | CALIB_IRON_PARS_VERSION_MINOR)
#define CALIB_IRON_NOT_COMPLETED                    0x55
#define CALIB_IRON_COMPLETED                        0xAA

typedef enum {
    CALIB_EQUIPMENT_CORRECT =0,
    CALIB_EQUIPMENT_NOT_FOUND,
    CALIB_EQUIPMENT_RANGE_ERR,
    CALIB_EQUIPMENT_AOA_ERR,
    CALIB_EQUIPMENT_SIGNAL_MAG_ERR,
    CALIB_EQUIPMENT_RADAR_HW_ERR,
    CALIB_EQUIPMENT_TIME_OUT,
    CALIB_EQUIPMENT_VAOA_ERR,
    CALIB_EQUIPMENT_PROCESSING,
    CALIB_EQUIPMENT_INVALID
}calib_equipment_e;

typedef enum
{
	CALIB_STATUS_IDLE,
	CALIB_STATUS_READY,
	CALIB_STATUS_BUSY,
	CALIB_STATUS_DONE,
	CALIB_STATUS_START,
	CALIB_STATUS_INVALID
}calib_status_e;

typedef enum
{
    CALIB_IRON_PARS_CORRECT=0,
    CALIB_IRON_PARS_DISTANCE_ERR,
    CALIB_IRON_PARS_ANGLE_ERR
}calib_iron_pars_status;
    
typedef struct
{
	calib_equipment_e    	calibration_result;
	calib_status_e     		calibration_sta;
}calib_iron_info_t;

typedef struct {

	uint8_t		equipment_magdB_threshold;
	uint8_t		equipment_angle_tolerance;
	uint8_t		equipment_vangle_tolerance;
	uint8_t		equipment_magdB_dif_tolerance;
	uint8_t     number_of_inspections;
	uint8_t 	correct_cnt_threshold;
	uint8_t     not_found_cnt_threshold;
	uint8_t     range_err_cnt_threshold;
	uint8_t     aoa_err_cnt_threshold;
	uint8_t     vaoa_err_cnt_threshold;
	uint8_t     number_of_measurement;
	
	uint16_t    calib_iron_bandwidth;
	float       vangle_compensation_table[11];      //0.9m 1.05m 1.2m 1.35m 1.5m 1.65m 1.8m 1.95m 2.1m 2.25 2.4m
	
	//for UDS
	float               target_offset_angle;
	float               target_distance;
	uint8_t             alignment_completion_flag;
	calib_equipment_e   radar_alignment_result;
	float               h_alignment_angle;
	float               v_alignment_angle;
	float               alignment_received_power;
} calib_iron_data_t,*calib_iron_data_p;
void calib_iron_init(calib_iron_data_p);

typedef struct {
	pars_header_t	hdr;
	calib_iron_data_t	pars;
}calib_iron_pars_t, *calib_iron_pars_p;

typedef struct{
    float   iron_angle;
    float   iron_vangle;
    float   iron_mag;
}iron_calib_result_t, *iron_calib_result_p;
void save_calib_iron_result_to_EE(calib_equipment_e iron_calib_status, iron_calib_result_p iron_calib_result);
typedef void (*iron_calib_done_p)(calib_equipment_e iron_calib_status, iron_calib_result_p iron_calib_result);
extern calib_status_e get_calib_iron_sta(void);
extern calib_status_e start_iron_calibration(iron_calib_done_p iron_calib_done);
extern void stop_iron_calibration();
extern float get_calib_iron_target_offset_angle(void);
extern void set_calib_iron_target_offset_angle(float angle);
extern void set_calib_iron_range(float range);
extern float get_calib_iron_target_distance(void);
extern void set_calib_iron_target_distance(float angle);
extern uint8_t get_calib_iron_alignment_completion_flag(void);
extern void set_calib_iron_alignment_completion_flag(uint8_t flag);
extern calib_equipment_e get_calib_iron_radar_alignment_result(void);
extern void set_calib_iron_radar_alignment_result(calib_equipment_e result);
extern float get_calib_iron_h_alignment_angle(void);
extern void set_calib_iron_h_alignment_angle(float angle);
extern float get_calib_iron_v_alignment_angle(void);
extern void set_calib_iron_v_alignment_angle(float angle);
extern float get_calib_iron_alignment_received_power(void);
extern void set_calib_iron_alignment_received_power(float power);
extern calib_iron_pars_status get_calib_iron_pars_status(void);

extern void coefs_rmtp_pars_init(coefs_data_p* cfs, void(**pset)(void));
#endif /* CORE_DETECTIONS_COEFS_H_ */
