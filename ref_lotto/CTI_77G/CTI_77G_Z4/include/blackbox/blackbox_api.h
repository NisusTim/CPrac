/*
 * blackbox_api.h
 *
 *  Created on: 2019/10/28
 *      Author: jacklee
 */

#ifndef BLACKBOX_API_H_
#define BLACKBOX_API_H_

#include "blackbox.h"
#include "target.h"
#include <stdint.h>

typedef enum _BBoxApiFlag {
  kFrame   = 1,
  kMonitor = 2,
  kInvalid = 15
} bbox_api_flag;

typedef struct _Object {
  int16_t  x;
  int16_t  y;
  int16_t  vel_x;
  int8_t   vel_y;
  uint8_t  state;
} obj_t;

typedef union Gear_Turn_union_tag {      /* Main Configuration Register */
  uint8_t R;
  struct {
    uint8_t turn:4;                /* Overwrite enable. */
    uint8_t gear:4;                /* Write Left/Right aligned. */
  } B;
} Gear_Turn_tag;

typedef struct _Frame {
  int16_t        speed;
  int16_t        yaw_rate;
  obj_t          objects[3];
  Gear_Turn_tag  gear_turn;
} frm_t;

typedef struct _Monitor {
  float    acc_x;
  float    acc_y;
  uint8_t  reserved[29-8];
} mon_t;

void Blackbox_Init(void);
void Blackbox_Record(tracking_group_p tkg);

#endif  // BLACKBOX_API_H_
