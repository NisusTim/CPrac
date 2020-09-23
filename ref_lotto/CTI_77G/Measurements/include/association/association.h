#ifndef MEASUREMENT_ASSOCIATION_H_
#define MEASUREMENT_ASSOCIATION_H_

#include <stdint.h>
#include "target.h"

#define MEAS_ASSO_DEBUG			0
#if MEAS_ASSO_DEBUG
#define ASSO_DEBUG(...)		do { if(MEAS_FLAG_ASSO_DEBUG & MEAS_FLAGS_WR) PRINTF(__VA_ARGS__);} while(0)
#else
#define ASSO_DEBUG(...)		do { } while(0)
#endif

// META_MEAS_GROUP_CAP must be ge 2
#define META_MEAS_CAP       				MAX_COUNT_OF_TARGET
#define META_MEAS_GROUP_CAP   				2

#define MAX_VELOCITY_SUPPORTED	  			60	// in m/s~=216km/h
#define EXP_VEL(_v, _max, _f)				((_v) + (_f) * (_max))

typedef enum _ExpandVelState {
  kNegThree =   -3,
  kNegTwo =     -2,
  kNegOne =     -1,
  kZero =        0,
  kPosOne =      1,
  kPosTwo =      2,
  kPosThree =    3,
  kNotPaired =  10
} exp_vel_st;

typedef struct _MetaMeasurement {  // scale of measurement
  float range;
  float rng_x;    // meter
  float rng_y;    // meter
  float vel;      // meter per second
  target_p tg;
  int16_t aoaidx;
  int8_t flip;
  int8_t reserved;
} meta_meas_t;

typedef struct _MetaMeasurementGroup {  // scale of frame
  meta_meas_t mm[META_MEAS_CAP];
  float vel_max;     // meter per second, 256 bin
  target_group_t *tgg;
  uint16_t mm_cnt;
} meta_meas_group_t;

typedef struct _MeasAsn {
  meta_meas_group_t mmgs[META_MEAS_GROUP_CAP];
  meta_meas_t gate;
  meta_meas_group_t *curr;
  meta_meas_group_t *prev;
  float time_delta;  // in second
  int8_t mult_vel;
  uint8_t curr_idx;
  meta_meas_group_t *(*API_Association)(struct _MeasAsn *self, target_group_t *, float);
} MeasAsn;

void API_NewMeasAsn(MeasAsn *self);

#endif  // MEASUREMENT_ASSOCIATION_H_
