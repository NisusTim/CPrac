#ifndef DYNAMIC_VERTICAL_FEEDBACK_H_
#define DYNAMIC_VERTICAL_FEEDBACK_H_

#include <stdbool.h>
#include <stdint.h>
#include "vertical_feedback_shared.h"
#include "frame.h"    // frame_data_t

#define DYNAMIC_VERTICAL_FEEDBACK_DEBUG       1
#define HGT_RNG_LIST_CAP                      4
#define MEAS_RNG_CAPACITY                     5
#define MEAS_RNG_MULTIPLIER                   2
#define SAMPLING_SIZE_CNT_RATIO               (MEAS_RNG_MULTIPLIER*MEAS_RNG_CAPACITY)

/*
 * to_send_can:    toggle to send can msg
 * to_loop:        toggle to auto run
 * timeout:        in second, related to frame rate
 * sampling_cnt:   number of sample for each measurement range point
 * bandwidth_freq: in hertz
 * high_pass_freq: in hertz
 * rng_min_meas:   in meter, min sampling range
 * height_list:    in meter, ascending sorting
 * rng_min_list:   in meter, ascending sorting
 * speed_thld:     in km/hr, (+) forward car speed threshold
 * yaw_rate_delta: in degree/sec, rotation of z-axis, ISO: (+) forward-left rotate
 * acc_z_delta:    in cm/sec2, (+) down, acc_z difference between 980 cm/sec2
 * hrz_aoa:        in degree
 * vert_phs_thld:  in degree
 * vert_phs_shift: in degree
 */
#define DYNAMIC_NVM_MEMBERS                     \
    uint8_t  to_send_can;                       \
    uint8_t  to_loop;                           \
    uint16_t timeout;                           \
    uint16_t sampling_cnt;                      \
    float    bandwidth_freq;                    \
    float    high_pass_freq;                    \
    float    rng_min_meas;                      \
    float    height_list[HGT_RNG_LIST_CAP];     \
    float    rng_min_list[HGT_RNG_LIST_CAP];    \
    float    speed_thld;                        \
    float    yaw_rate_delta;                    \
    float    acc_z_delta;                       \
    float    hrz_aoa;                           \
    float    vert_phs_thld;                     \
    float    vert_phs_shift;                    \
    VTFB_SHARED_NVM_MEMBERS;

typedef struct _DynamicVerticalFeedbackNVM {
    DYNAMIC_NVM_MEMBERS;
} dvtf_nvm_t;

void dvtf_init(void (*done_routine)(void));
void dvtf_process(frame_data_t *frame_data);
void dvtf_process_start(void);
void dvtf_process_stop(void);
void dvtf_sampling_cnt_clear(void);
vtfb_st dvtf_buffer_state_get(void);
vtfb_st dvtf_eeprom_state_get(void);
vtfb_cpl_st dvtf_eeprom_complete_state_get(void);
float dvtf_buffer_pitch_angle_get(void);
float dvtf_eeprom_pitch_angle_get(void);
bool dvtf_condition_set(float low, float up);
bool dvtf_to_send_can_get(void);
bool dvtf_to_send_can_set(bool toggle);
bool dvtf_to_loop_set(bool toggle);
bool dvtf_timeout_set(uint16_t second);
bool dvtf_sampling_cnt_set(uint16_t sampling_cnt);
bool dvtf_mount_height_set(float height);
bool dvtf_height_list_set(char **list, int count);
bool dvtf_rng_min_list_set(char **list, int count);
bool dvtf_rng_max_list_set(char **list, int count);
bool dvtf_rf_set(float bw, float hpf);
bool dvtf_io_condition_set(char **list, int count);
bool dvtf_force_ram_completed_set(void);
bool dvtf_fae_set(char **list, int count);
uint16_t dvtf_total_sampling_cnt_get(void);
uint16_t dvtf_sampling_size_get(void);

#endif  // DYNAMIC_VERTICAL_FEEDBACK_H_
