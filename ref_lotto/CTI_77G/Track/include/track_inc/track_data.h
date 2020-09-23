/*
 * track_data.h
 *
 *  Created on: 2017/08/23
 *      Author: Benson
 */

#ifndef __TRACK_DATA_H__
#define __TRACK_DATA_H__

#include "f2c.h"
#include "typedefs.h"

#define USING_FCW_MODE				1

//#define DEBUG_PERFORMANCE			1

#define MOVING_PATH_MAX				64
#define TARGET_HEAP_SIZE            200
#define VANGLE_QUEUE_SIZE      		10
#define TRACKING_SCALE              256
#define VIEW_NEAR_RANGE         	35.0
#define VIEW_HALF_RANGE          	100.0
#define VIEW_MAX_RANGE          	200.0
#define LANE_ONE_WIDTH          	1.8
#define LANE_WIDTH          		3.6
#define LANE_TWO_WIDTH          	5.4
#define LANE_THREE_WIDTH          	9.0
#define ID_DELAY					-5
#define HPF_SR_MAKEUP_SIZE          20
#define HPF_LR_MAKEUP_SIZE          20
#define ANGLE_MAKEUP_SIZE			41
#define TX_MAKEUP_SIZE				16
#define RX_MAKEUP_SIZE				8
#define LONGANGLERCSANGLE 			10
#define SHORTRANGERCSANGLE 			60
#define XSHORTRANGERCSFACTOR 		3.61E-13
#define XLONGRANGERCSFACTOR  		1.32E-14
#define RADARPOWERSENDFACTOR 		1.0
#define MINPTS						1
#define TUNNEL_FRAME				70
#define AUTO_CALIB_NUM				100
#define AUTO_CALIB_ONESIDE			60
#define AUTO_CALIB_QUEUE_SIZE		8
#define ANGLE_HISTORY_NUM			5

enum {
	BOUNDARY 			= -4,
	CORNER 				= -3,
	CHASSIS  			= -2,
	LOST				= -1,
	HIDDEN 				= 0,
	STANDING			= 1,
	STOPPED				= 2,
	MOVING				= 3,
	ONCOMING			= 4,
	FLYOVER				= 5,
	DITCHCOVER			= 6,
	NOISE				= 7,
	MAX_DYN_STATUS  	= 7,
	MEASUREMENT		  	= 10,
	UNKNOWN				= 255
};

enum {
	NO_OBJECT			= 0,
	NEW_OBJECT			= 1,
	PREDICTED			= 2,
	MEASURED			= 3,
	INAVLID				= 4
};

enum {
	PROBABILITY_25		= 0,
	PROBABILITY_50		= 1,
	PROBABILITY_75		= 2,
	PROBABILITY_99		= 3
};

enum {
	NO_WARNING 			= 0,
	CIP_WARNING 		= 1,
	PRE_WARNING 		= 3,
	WARNING				= 5,
	EMG_WARNING			= 9
};

enum {
	SEPARATE_NONE 		= 0,
	SEPARATE_LEFT 		= 1,
	SEPARATE_RIGHT 		= 2
};

enum {
	PATH_NONE 			= 0,
	PATH_STRAIGHT		= 1,
	PATH_INWARD 		= 2,
	PATH_SWERVE         = 3,
	PATH_SERPENTINE 	= 4
};

enum {
	OBJECT_UNKNOWN		= 0,
	PEDESTRIAN			= 1,
	SCOOTER				= 2,
	CAR					= 3,
	TRUCK				= 4
};

enum {
	HPF_MAKEUP			= 0,
	ANGLE_MAKEUP		= 1,
	TX_POWER			= 2,
	RX_POWER			= 3
};

typedef enum {
	TYPE_TARGET = 0,
	TYPE_POSSIBLE
}TARGET_TYPE;

typedef struct _list_st
{
  	float     		vg_x;   		// validate gating radius in x
  	float     		vg_y;   		// validate gating radius in y
  	float    		vg_v;   		// validate gating radius in velocity
 	float   		uw_x;  			// x value update weighting for new target
  	float  			uw_y;  			// y value update weighting for new target
  	float     		uw_vx;  		// velocity x value update weighting for new target
  	float     		uw_vy;  		// velocity y value update weighting for new target
  	int       		upper_bound;    // maximal score that a tracking target can have
  	int       		zero_level;
  	int       		candidate;		// candidate score
  	int       		win;            // added score number for normal case
  	int       		win2;       	// added score number for special case
  	int       		lose;           // subtracted score number for normal case
  	int       		lose2;     		// subtracted score number for special case
} list_st;

#define MEASURE_MEMBERS	\
	float    		range;		/* unit: m */				\
	float      		velocity;	/* unit: m/s */				\
	float      		angle;   	/* unit: deg */				\
	float			vangle;		/* unit: deg */				\
	float      		rad;		/* rad value for angle */   \
	float      		x;			/* range * sin(angle) */  	\
	float      		y;			/* range * cos(angle) */    \
	float      		vy;			/* abs x*/					\
	float      		tv;										\
	float			absx;		/* abs x*/					\
	float			absa;		/* abs angle*/				\
	float			mag;		/* magnitude*/				\
	float			rcs;		\
	int8_t       	score;		\
	int8_t			beam;

typedef struct _measure_st
{
	MEASURE_MEMBERS;
} measure_st, measurement_t, *measurement_p;

#define TARGET_ST \
	uint8_t      	idx;																				\
	uint8_t			m_idx;			/* data association measurement's index */							\
	int16_t       	score;      	/* possible target use bit 0..7, tracking target use bit 8..15 */	\
	int16_t			vangle;			/* vertical angle */												\
	uint16_t		mag;			/* magnitude */														\
	float			m_min;			/* data association measurement's minimum value */					\
	float      		range;     		/* unit: m */														\
	float      		velocity;   	/* unit: m/s */														\
	float      		angle;      	/* unit: deg */														\
	float      		rad;        	/* rad value for angle */											\
	float			rcs;			/* radar cross section */											\
	float      		x;        		/* range * sin(angle) */											\
	float      		y;          	/* range * cos(angle) */											\
	float			init_y;																				\
	float      		sx;																					\
	float			px;				/* previous y position */											\
	float			xq[5];			/* x queue */														\
	float			py;				/* previous y position */											\
	float      		yq[5];         	/* y queue */														\
	float       	vx;																					\
	float			vxq[5];			/* vx queue */														\
	float			pvx;			/* vx at previous second */											\
	float      		vy;																					\
	float      		vyq[5];			/* vy queue */														\
	float			pvy;			/* vy at previous second */											\
	float     		accx;																				\
	float     		accy;																				\
	float			accy_est;																			\
	float      		svyq[5];		/* smooth vy queue */												\
	float           accyq[5];		/* accy queue */													\
	float 			km_a;																				\
	float 			va_iir;																				\
	float			vaq[VANGLE_QUEUE_SIZE];		/* vertical angle queue */								\
	uint32_t		vaq_idx;					/* vertical angle queue index */						\
	int8_t       	dyn_status;																			\
	uint8_t         height_cnt;																			\
	uint8_t			cip_score;																			\
	uint8_t			cip_acc_score;																		\
	uint8_t			cip_aeb_score;																		\
	uint8_t			cip_warning;																		\
	uint8_t			cip_acc_flag;																		\
	uint8_t			cip_aeb_flag;																		\
	uint8_t			updated;		/* new measurement for updating */									\
	uint32_t 		measured;		/* measurement received count */									\
	uint32_t		missed;			/* measurement missed count */										\
	uint16_t		warning_score;																		\
	uint8_t			lateral_cnt;																		\
	uint8_t			standing_cnt;																		\
	uint8_t			guardrail_visit;																	\
	uint8_t			guardrail_cluster;																	\
	uint8_t			guardrail_cnt;																		\
	uint8_t			cip_go_straight_score;																\
	uint8_t			cip_turnright_score;																\
	uint8_t			cip_turnleft_score;																	\
	uint8_t			potential_cip_flag;																	\
	int8_t			potentialCIPVDirection;																\
	float			cipvTurningLocation;																\
	float           auto_calib_xq[AUTO_CALIB_QUEUE_SIZE];												\
	float			auto_calib_yq[AUTO_CALIB_QUEUE_SIZE];												\
	float			vector_x;																			\
	float			vector_y;																			\
	float			vector_angle;																		\
	uint8_t			auto_calib_counter;																	\
	uint8_t			object_type;																		\
	uint8_t			object_type_temp;																	\
	uint8_t			object_type_counter;																\
	uint8_t			grouped;																			\
	uint8_t			live_score;																			\
	uint8_t			group_score;

typedef struct _target_st
{
	TARGET_ST;
} target_st;

typedef struct _sorting_st
{
	int16_t 		idx;
	uint8_t 		used;
	float 			ry;
	struct _sorting_st 	*prev;
  	struct _sorting_st 	*next;
} sorting_st;

typedef struct _guardrail_st
{
	float 			x;
	float 			y;
	float			linear_regression_a;
	float			linear_regression_b;
	float 			y_near;//lxh+
	float 			y_far;
} guardrail_st;

#if (defined USING_RCW_MODE) && (defined USING_RCW_MODE_FENIEX)
typedef struct _moving_path_st
{
	int16_t 		idx;
	float			path_y;
	float			straight_x;
	float			straight_y;
	float			straight_dy;
	float			straight_pml;
	float			straight_pmr;
	float			inward_x;
	float			inward_y;
	float			inward_dy;
	float			inward_a;
	float			inward_rad;
	float			inward_plx;
	float			inward_prx;
	float			inward_pml;
	float			inward_pmr;
	float			inward_dl;
	float			inward_dr;
	uint8_t			straight_cnt;
	uint8_t			straight_wcnt;
	uint8_t			inward_new;
	uint8_t			inward_cnt;
	uint8_t			swerve_wcnt;
	uint8_t			serpentine_on;
	uint8_t			serpentine_lcnt;
	uint8_t			serpentine_rcnt;
	uint8_t			serpentine_cnt;	
	uint8_t			path_zero_level;
	uint8_t			path_upper_bound;
	uint8_t			pre_path_mode;
	uint8_t			path_mode;
} moving_path_st;
#endif

typedef struct _tracking_ctx_st
{
	float 			frame_slot_sec;
	uint32_t 		frame_cnt;
	uint16_t 		frame_num;	
	uint8_t 		frame_rate;
	uint16_t		tracking_ctrl;
	uint16_t		tracking_ctrl_status;
	list_st 		tracking_pars;
	list_st 		possible_pars;
	sorting_st 		sorting[TARGET_HEAP_SIZE];
	target_st		heap[TARGET_HEAP_SIZE];
	measure_st* 	measurements;
#if (defined USING_RCW_MODE) && (defined USING_RCW_MODE_FENIEX)
	moving_path_st 	moving_path[MOVING_PATH_MAX];
#endif
	uint8_t 		measurements_count;
	uint8_t 		target_max_idx;
	sorting_st 		*target_list;
	uint8_t 		target_cnt;
	uint8_t 		target_get_step;
	uint8_t 		target_get_max_step;
	uint8_t 		target_get_status;
	float 			target_get_xy[8][2];
	float 			measure_angle;
	float			measure_width;
	float 			my_speed;
	float 			my_neg_speed;
	float 			my_pre_speed;
	float 			my_accel;
	float 			yaw_rate;
	float 			turn_radius;
	uint8_t			gear_status;
	uint8_t			door_status;
	uint8_t			door_status_time;
	uint8_t 		standing_flag;
	uint8_t 		separate_flag;
	float 			standing_speed;
	float 			standing_speed_v0;
	float 			standing_speed_a0;
	float 			standing_speed_v1;
	float 			standing_speed_a1;
	float 			standing_speed_v2;
	float 			weight_y_range;
	float 			weight_x_near;
	float 			weight_x_far;
	float 			km_q;
	float 			km_r;
	float			acc_z;
	uint8_t 		cipv_index;
	uint8_t			cipv_acc_index;
	uint8_t 		cipv_aeb_index;
	uint8_t			cipv_losing_time;
	uint8_t			cipv_acc_losing_time;
	uint8_t			cipv_aeb_losing_time;
	uint8_t			tunnel_flag;
	uint8_t			potential_cipv_index;
	uint8_t			dfilter_frame_cnt;
	uint8_t         auto_calib_left_num;
	uint8_t         auto_calib_right_num;
	float 			calib_angle;
	float           calib_mount_angle;
	float			auto_calib_angle[AUTO_CALIB_NUM];
	uint8_t			guardrail_cluster_cnt;
	guardrail_st	guardrail_lr[10];
    float           calib_angle_history[ANGLE_HISTORY_NUM];
    uint8_t         calib_angle_index;
} tracking_ctx_st;

#endif /* __TRACK_DATA_H__ */
