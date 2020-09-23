/*
 * alignment_main.h
 *
 *  Created on: 2020/7/23
 *      Author: HUNGNUNG YANG
 */

#ifndef ANGLE_FEEDBACK_ALIGNMENT_MAIN_H_
#define ANGLE_FEEDBACK_ALIGNMENT_MAIN_H_

#define AUTO_ALIGN_HORI_SCALE 10.0
#define AUTO_ALIGN_VERT_SCALE 10.0
#define AUTO_DETECT_HORI_SCALE 10.0
#define AUTO_DETECT_VERT_SCALE 10.0

#define ALIGN_COMPLETED        0xAA
#define ALIGN_NOT_COMPLETED    0x55
#define HORI_UPPER_ANGLE		3
#define VERT_UPPER_ANGLE		2.5

#define TARGET_MAX                  32
#define POSSIBLE_MAX                168

#define VERTICAL_SAMPLE_UPBOUND		15
#define VERTICAL_SAMPLE_LOWBOUND	2
#define VERTICAL_SAMPLE_SCALE		100

enum {
    CALIB_CORRECT       = 0,
    CALIB_RESVERD_1     = 1,
    CALIB_RESVERD_2     = 2,
    CALIB_AOA_ERR       = 3,
    CALIB_RESVERD_3     = 4,
    CALIB_YAW_RATE_ERR  = 5,
    CALIB_TIMEOUT       = 6,
    CALIB_VAOA_ERR      = 7,
    CALIB_PROCESSING    = 8,
    CALIB_INVALID
};

enum {
    ALIGN_STATUS_READY			= 0,
	ALIGN_STATUS_START     		= 1,
	ALIGN_STATUS_PROCESS   		= 2,
	ALIGN_STATUS_DONE_SAVE		= 3,
	ALIGN_STATUS_DONE_NOT_SAVE 	= 4,
	ALIGN_STATUS_ERROR     		= 5,
	ALIGN_STATUS_TIMEOUT   		= 6,
	ALIGN_STATUS_YAW_ERR		= 7,
	ALIGN_STATUS_ACCZ_ERR		= 8
};

enum{
    DETECT_STATUS_UNKNOWN = 0,
	DETECT_STATUS_READY,
	DETECT_STATUS_START,
	DETECT_STATUS_PASS,
	DETECT_STATUS_FAIL,
	DETECT_STATUS_STOP,
	DETECT_STATUS_YAW_ERR,
	DETECT_STATUS_TIMEOUT
};

typedef struct {
	uint8_t	auto_hori_align_status;
	uint8_t	auto_hori_detect_status;
	uint8_t auto_hori_finished_num;
	float	auto_hori_mount_angle;
	float	auto_hori_align_mount_angle;
	float	auto_hori_detect_mount_angle;

	uint8_t	auto_vert_align_status;
	uint8_t	auto_vert_detect_status;
	uint16_t auto_vert_finished_num;
	float	auto_vert_phase;
	float	auto_vert_angle;
	float	auto_vert_mount_angle;
	float	auto_vert_phase_std;
	float	auto_vert_align_mount_phase;
	float	auto_vert_detect_mount_phase;
} alignment_data_t, *alignment_data_p;

void alignment_init();
uint8_t hori_vert_detect_check();

uint8_t get_hori_alignment_status();
uint8_t get_hori_finished_num();

uint8_t get_vert_alignment_status();
uint16_t get_vert_finished_num();

void clear_hori_finished_num();
void clear_vert_finished_num();

void set_auto_detect_hori_status(uint8_t status);
void set_auto_detect_vert_status(uint8_t status);

uint8_t get_auto_detect_hori_status(void);
uint8_t get_auto_detect_vert_status(void);

float get_auto_hori_mount_angle(void);
float get_auto_hori_align_mount_angle(void);
float get_auto_hori_detect_mount_angle(void);

float get_auto_vert_align_mount_phase(void);
float get_auto_vert_align_mount_angle(void);
float get_auto_vert_angle(void);
float get_auto_vert_mount_angle(void);
float get_auto_vert_detect_mount_angle(void);

#endif /* ANGLE_FEEDBACK_ALIGNMENT_MAIN_H_ */
