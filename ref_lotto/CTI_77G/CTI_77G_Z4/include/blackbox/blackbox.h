#ifndef BLACKBOX_H_
#define BLACKBOX_H_

#include <stdint.h>
#include "flash.h"

#ifdef BLACKBOX_DEBUG
#undef BLACKBOX_DEBUG
#endif
#ifndef BLACKBOX_DEBUG
#define BLACKBOX_DEBUG  FLASH_DEBUG && FLASH_READ
#endif

#define PAGE_SZ            (kSinglePage)  // default: 32 (32, 64 or 128 Byte)
#define PAGE_TIME_UNIT_MS             50  // default: 50

typedef enum _BBoxState {
  kBBoxInitError   = 0,
  kBBoxReady       = 1,
  kBBoxRecording   = 2,
  kBBoxCountdown   = 3,
  kBBoxSleeping    = 4,
  kBBoxBusyErasing = 5
} bbox_st;

typedef struct _PageFlag {
  uint8_t head:1;
  uint8_t state:3;
  uint8_t reserved:4;
} page_flag_t;

// @rel_time: 0 to (UINT16_MAX - 1), time ticks relative to rec_t's time
typedef struct _Page {
  page_flag_t flag;
  uint8_t     reserved[PAGE_SZ - 3];
  uint16_t    rel_time;
} page_t;

/*
 * Public variables and functions:
 * @curr_state: Current state of BlackBox, read-only.
 * @prev_state: Previous state of BlackBox, read-only.
 * @page_buff: Normally 32 Bytes, a buffer space about to write into flash.
 *            page_buff[0:2] for relative timestamp.
 *            page_buff[2] for the half byte of flag.
 *            page_buff[3:] for payload data.
 * @frm_num: Frame number, shared data.
 * @left_sec: Count down seconds left, read-only.
 *           Can be re-written by Countdown() if the new value is lesser.
 * Record:
 * Countdown: Transit state kCountdown from kRecording and start calculate the
 *            remaining time (left seconds).
 *            Update left seconds, but only lesser is allowed.
 * ResetCountdown: Reset state to kReady or kRecording state, while at
 *                 kSleeping or kCountdown state, respectively.
 * Dump: Print out all the blackbox data via can console.
 * Private variables and functions:
 * @rec_buff: Normally 32 Bytes, another buffer space store rec_t info to write.
 * @tm_stamp_new_obj_: Timestamp, benchmark of recorder
 * @tm_stamp_new_rec_: Timestamp, benchmark of page
 * @tm_stamp_sync_page_: Timestamp, for new page
 * @tm_stamp_prev_page_: Timestamp, for accumulated calculation for left second.
 * @rec_counter_: Indicator of recorder number, used to find latest rec.
 */
typedef struct _BlackBox {
  // public:
  uint8_t curr_state;
  uint8_t prev_state;
  uint8_t page_buff[PAGE_SZ];
  uint16_t frm_num;
  float left_sec;              // count down seconds left
  void (*Record)(struct _BlackBox *self, uint8_t to_sync_time,
                 uint8_t half_flag);
  void (*Countdown)(struct _BlackBox *self, uint16_t final_sec);
  void (*ResetCountdown)(struct _BlackBox *self);
  void (*Dump)(struct _BlackBox *self);
  // private:
  uint8_t rec_buff[PAGE_SZ];
  uint32_t tm_stamp_new_obj_;
  uint32_t tm_stamp_new_rec_;
  uint32_t tm_stamp_new_page_;
  uint32_t tm_stamp_left_sec_;
  uint16_t rec_counter_;
} BlackBox;

// API
void InitBlackBox(BlackBox *self, uint8_t tick_ms);

#endif  // BLACKBOX_H_
