#include <stdint.h>
#include <stdlib.h>         // strtof(), strtoul()
#include <string.h>         // memcpy(), memset()
#include <float.h>          // FLT_EPSILON or __float_epsilon
#include <math.h>           // fabs(), powf(), sqrtf(), sinf(), asinf()
#include "dynamic_vertical_feedback.h"
#include "vertical_feedback_shared.h"
#include "vertical_feedback_proxy.h"
#include "z47_ipc.h"
#include "SPT.h"            // spt_vertical_feedback_mode(), spt_resume_to_normal_mode()
#include "vehicle.h"        //
#include "custom_math.h"    // RADIAN_TO_DEGREE, DEGREE_TO_RADIAN
#include "measurements.h"   // DEFAULT_GATE_STATIONARY_VEL
#include "tracking.h"       // get_auto_calibration_done()
#include "console_api.h"    // PRINTF()
#include "console_cmd.h"    // console_command_reg()
#include "console.h"        // put_string()
#include "parameters.h"     // FOURCC()
#include "tracking.h"       // tracking_radar_hight_get(), tracking_radar_hight_set()

//#define FLOAT_EPSILON           0x1.000000P-23F  // 0x1.000000 * 2^(-23) float
#define CAST(type, var)  (type *)(void *)var
#define DYNAMIC_VERTICAL_FEEDBACK_PARS_ID FOURCC('d', 'v', 't', 'f')
#define STR(x)           #x
#define DVTF_ID          STR(dvtf)

#define TRANSIT_STATE(buffer, new_state)  \
    buffer.state = new_state

/*
 * MEAS_RNG_CAPACITY: must >= 2, default 5 for 6.5, 7.0, 7.5, 8.0, 8.5
 */
#define REVERSED_SIGNF           -1.0f
#define DEGREE_OF_NO_VERTICAL   180.0f   // short range with no vertical phase
#define DEFAULT_MOUNT_HEIGHT      1.00f  //

#define LINT(a, b, f)                           \
    (a * (1.0f - f)) + (b * f)

typedef struct _DynamicVerticalFeedbackQuantity {
    float rad_rng;       // radial distance
    float ang_sim;       // in degree, (+) down tilt, simulation return angle from road surface
                         // calculated by rad_rng and mount_height
    float phs_sim;       // in degree, (+) down tilt, simulation return phase, converted from ang_sim
    float ang_meas;      // in degree, (+) down tilt, measured return angle, converted from phs_meas
    float phs_meas;      // in degree, (+) down tilt, measured return phase, sampling from measurements' vangle
    float ang_feedback;  // in degree, (+) down tilt, feedback = sim - meas
    float phs_feedback;  // in degree, (+) down tilt, feedback = sim - meas
    uint16_t count;      //
} dvtf_qty_t;

typedef struct _DynamicVerticalFeedbackAccumulation {
    float rad_rng;
    float ang_meas;
    float phs_meas;
    uint16_t count;
} dvtf_accum_t;

/*
 * mount_height: (lb, ub) = (0.3, 1.1)
 *   in meter, radar mounted height
 */
typedef struct _DynamicVerticalFeedbackProperty {
    dvtf_qty_t    qty_avg[MEAS_RNG_CAPACITY];
    dvtf_qty_t    qty_sd[MEAS_RNG_CAPACITY];
    dvtf_accum_t *accum_sum;
    dvtf_accum_t *accum_sq_sum;
    dvtf_nvm_t *  eeprom;        // synchronized with eeprom from vtfb
    dvtf_nvm_t    buffer;        // run time buffer
    float         mount_height;  // radar mounted height
    bool          to_run;        // toggle to run process after ipc triggered
    bool          is_running;    // process flow control
    uint16_t      poll_cnt;      // frame count
    uint16_t      poll_csize;    //
    vtfb_st       err_state;     // store kVtfbVehIoError or kVtfbTimeout
    void          (*end_routine)(void);
} dvtf_t;

#if DYNAMIC_VERTICAL_FEEDBACK_DEBUG
typedef enum _DynamicVerticalFeedbackError {
    kEpsSpeedStatusNotValid     = 0,
    kVehAccZStatusNotValid         ,
    kVehYawRateStatusNotValid      ,
    kHrzAutoCalibStatusNotDone     ,
    kCarSpeedNotEnough             ,
    kYawRateTooLarge               ,
    kAccZDeltaTooLarge
} dvtf_err;
#endif

/************************************************
 * Forward Declarations                         *
 ************************************************/
void dvtf_init(void (*end_routine)(void));
void dvtf_process(frame_data_t *frame_data);
void dvtf_process_start(void);
void dvtf_process_stop(void);
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
bool dvtf_rf_set(float bw, float hpf);
bool dvtf_io_condition_set(char **list, int count);
bool dvtf_force_ram_completed_set(void);
bool dvtf_fae_set(char **list, int count);
uint16_t dvtf_total_sampling_cnt_get(void);
uint16_t dvtf_sampling_size_get(void);

// Private Methods
static void state_machine(dvtf_t *, vtfb_st);
static vtfb_st initialize_accumulation_list(
    dvtf_accum_t *, const uint8_t, const dvtf_nvm_t *, const float);
static vtfb_st initialize_avg_quantity_list(
    dvtf_qty_t *, const uint8_t, const dvtf_nvm_t *, const float);
static vtfb_st initialize_sd_quantity_list(
    dvtf_qty_t *, const uint8_t, const dvtf_nvm_t *, const float);
static vtfb_st handle_accumulation(
    dvtf_accum_t *, dvtf_accum_t *, dvtf_nvm_t *,
    measurement_group_t *, const float);
static vtfb_st handle_condition(float, dvtf_nvm_t *);
static vtfb_st handle_io_condition(const dvtf_nvm_t *);
static vtfb_st check_vehicle_state(void);
static vtfb_st check_quntity_condition(float, dvtf_nvm_t *);
static bool check_accum_count_enough(
    dvtf_accum_t *, const uint8_t, const uint16_t);
static bool apply_range_by_height(dvtf_nvm_t *);
static inline float calculate_simulation_angle(float, float);
static inline float convert_phase_to_return_angle(float);
static inline float convert_return_angle_to_phase(float);
static inline float calculate_average(float, uint32_t);
static inline float calculate_standard_deviation(float, float, uint32_t);
static void calculate_avg_sd_result(dvtf_qty_t *, dvtf_qty_t *,
                                    dvtf_accum_t *, dvtf_accum_t *);
#if DYNAMIC_VERTICAL_FEEDBACK_DEBUG
static inline const char *string_of_error(dvtf_err);
#endif
static void dynamic_vertical_feedback_help(void);
static void dynamic_vertical_feedback_dump(void);
static void dump_quantity(dvtf_qty_t *, dvtf_qty_t *);
static void test_console(char **, int);

/************************************************
 * Globals                                      *
 ************************************************/
static dvtf_t kSingletonInst;
static dvtf_t * const kSingleton = &kSingletonInst;

/************************************************
 * APIs                                         *
 ************************************************/
void dvtf_init(void (*end_routine)(void))
{
    kSingleton->eeprom = CAST(dvtf_nvm_t, vtfb_dynamic_base_get());
    memcpy(&kSingleton->buffer, kSingleton->eeprom, sizeof(dvtf_nvm_t));
    if (0.0f == (kSingleton->mount_height = tracking_radar_hight_get()))
        kSingleton->mount_height = DEFAULT_MOUNT_HEIGHT;
    apply_range_by_height(&kSingleton->buffer);
    kSingleton->to_run = false;
    kSingleton->is_running = false;
    kSingleton->end_routine = end_routine;
    memset(kSingleton->qty_avg, 0, sizeof(kSingleton->qty_avg));
    memset(kSingleton->qty_sd, 0, sizeof(kSingleton->qty_sd));
    TRANSIT_STATE(kSingleton->buffer, kVtfbReady);
    ipc_reg_msg(MSG_DVTF_CALIB, "dvtf", (msg_proc_p)dvtf_process);
    if (kSingleton->buffer.to_loop)
        dvtf_process_start();

#if DYNAMIC_VERTICAL_FEEDBACK_DEBUG
    console_command_reg(DVTF_ID, test_console);
#endif
}

void dvtf_process(frame_data_t *frame_data)
{
    if (false == kSingleton->to_run)
        return;

    static dvtf_accum_t sum[MEAS_RNG_CAPACITY];
    static dvtf_accum_t sq_sum[MEAS_RNG_CAPACITY];
    dvtf_qty_t avg[MEAS_RNG_CAPACITY] = {{0}};
    dvtf_qty_t sd[MEAS_RNG_CAPACITY] = {{0}};
    measurement_group_t *meas_list = &frame_data->mgrp;
    static float range_delta;
    const float bandwidth = kSingleton->buffer.bandwidth_freq;
    const float high_pass = kSingleton->buffer.high_pass_freq;
    vtfb_st state = kVtfbReady;

    // init: set polling timer
    if (false == kSingleton->is_running) {
        spt_vertical_feedback_mode(bandwidth, high_pass);
        kSingleton->is_running = true;
        kSingleton->err_state = kVtfbReady;
        kSingleton->poll_cnt = 0;
        kSingleton->poll_csize = frame_rate(-1) * kSingleton->buffer.timeout;
        return;
    }

    // ignore first two frames to get proper runit
    ++kSingleton->poll_cnt;
    if (1 >= kSingleton->poll_cnt)
        return;

    if (2 == kSingleton->poll_cnt) {
        range_delta = frame_data->tggs[1].runit;
        float height = tracking_radar_hight_get();
        if (0.0f != height)
            kSingleton->mount_height = height;
        apply_range_by_height(&kSingleton->buffer);
        initialize_accumulation_list(sum, MEAS_RNG_CAPACITY, &kSingleton->buffer, range_delta);
        initialize_accumulation_list(sq_sum, MEAS_RNG_CAPACITY, &kSingleton->buffer, range_delta);
        initialize_avg_quantity_list(kSingleton->qty_avg, MEAS_RNG_CAPACITY, &kSingleton->buffer, range_delta);
        kSingleton->accum_sum = sum;
        kSingleton->accum_sq_sum = sq_sum;
    }

#if DYNAMIC_VERTICAL_FEEDBACK_DEBUG
    if (0 == kSingleton->poll_cnt % 20) {
        uint16_t capacity = kSingleton->buffer.sampling_cnt;
        PRINTF("  Dvtf: poll_cnt: %5u/%5u\n", kSingleton->poll_cnt, kSingleton->poll_csize);
        PRINTF("  Dvtf: accum cnt: %3u/%3u, %3u/%3u, %3u/%3u, %3u/%3u, %3u/%3u\n",
            sum[0].count, capacity, sum[1].count, capacity,
            sum[2].count, capacity, sum[3].count, capacity,
            sum[4].count, capacity);
    }
#endif

  // running: sampling I/O process
    if (!check_accum_count_enough(sum, MEAS_RNG_CAPACITY, kSingleton->buffer.sampling_cnt)) {
        state = handle_accumulation(sum, sq_sum, &kSingleton->buffer, meas_list, range_delta);
        if (kVtfbVehIoError == state) {
            kSingleton->err_state = kVtfbVehIoError;
        } else if (kVtfbVehIoInvalid == state) {
            TRANSIT_STATE(kSingleton->buffer, kVtfbVehIoInvalid);
        } else {
            TRANSIT_STATE(kSingleton->buffer, kVtfbProcessing);
        }
    }

    // terminate 1: io invalid
    if (kVtfbVehIoInvalid == state) {
        kSingleton->to_run = kSingleton->buffer.to_loop ? true : false;
        kSingleton->is_running = false;
        state_machine(kSingleton, kVtfbVehIoInvalid);
        if (NULL != kSingleton->end_routine)
            kSingleton->end_routine();
        return;
    }

    // terminate 2: calculation process
    if (check_accum_count_enough(sum, MEAS_RNG_CAPACITY, kSingleton->buffer.sampling_cnt)) {
        kSingleton->is_running = false;
        kSingleton->to_run = kSingleton->buffer.to_loop ? true : false;

        initialize_avg_quantity_list(avg, MEAS_RNG_CAPACITY, &kSingleton->buffer, range_delta);
        initialize_sd_quantity_list(sd, MEAS_RNG_CAPACITY, &kSingleton->buffer, range_delta);
        calculate_avg_sd_result(avg, sd, sum, sq_sum);
        memcpy(kSingleton->qty_avg, avg, sizeof(kSingleton->qty_avg));
        memcpy(kSingleton->qty_sd, sd, sizeof(kSingleton->qty_sd));

        // pitch angle condition check
        float pitch_ang = 0.0f;
        float pitch_phs = 0.0f;
        float count = 0.0f;
        for (uint8_t i = 0; i < MEAS_RNG_CAPACITY; ++i) {
            // direction: pitch = feedback
            pitch_ang += avg[i].ang_feedback * avg[i].count;
            pitch_phs += avg[i].phs_feedback * avg[i].count;
            count += avg[i].count;
        }
        pitch_ang = pitch_ang / count;
        pitch_phs = pitch_phs / count;
        kSingleton->buffer.pitch_ang = pitch_ang;
        if (kVtfbSuccess == handle_condition(pitch_ang, &kSingleton->buffer))
            state_machine(kSingleton, kVtfbCorrect);
        else
            state_machine(kSingleton, kVtfbAngOutOfBounds);
        PRINTF("  Dvtf: pitch_ang: %.2f  poll_cnt: %5u/%5u\n",
            kSingleton->buffer.pitch_ang, kSingleton->poll_cnt, kSingleton->poll_csize);
        dump_quantity(avg, sd);

        if (NULL != kSingleton->end_routine)
            kSingleton->end_routine();
        return;
    }

    // terminate 3: timeout or impossible
    if (kSingleton->poll_csize == kSingleton->poll_cnt || kSingleton->poll_csize < kSingleton->poll_cnt) {
        kSingleton->is_running = false;
        kSingleton->to_run = kSingleton->buffer.to_loop ? true : false;
        state_machine(kSingleton, kVtfbTimeout);
        if (NULL != kSingleton->end_routine)
            kSingleton->end_routine();
        return;
    }
}

void dvtf_process_start(void)
{
    kSingleton->to_run = true;
    kSingleton->is_running = false;

    // to inform vertical auto-detect stop doing
    set_auto_align_vert_to_run(kSingleton->to_run);
}

void dvtf_process_stop(void)
{
    kSingleton->to_run = false;
    kSingleton->is_running = false;
    TRANSIT_STATE(kSingleton->buffer, kVtfbReady);
    spt_resume_to_normal_mode();
}

void dvtf_sampling_cnt_clear(void){
	if(kSingleton->accum_sum != NULL){
		for(int i = 0; i < MEAS_RNG_CAPACITY; i++){
			kSingleton->accum_sum[i].count = 0;
		}
	}

}

vtfb_st dvtf_buffer_state_get(void)
{
    return kSingleton->buffer.state;
}

vtfb_st dvtf_eeprom_state_get(void)
{
    return kSingleton->eeprom->state;
}

vtfb_cpl_st dvtf_eeprom_complete_state_get(void)
{
    return kSingleton->eeprom->complete_state;
}

float dvtf_buffer_pitch_angle_get(void)
{
    return kSingleton->buffer.pitch_ang;
}

float dvtf_eeprom_pitch_angle_get(void)
{
    return kSingleton->eeprom->pitch_ang;
}

bool dvtf_condition_set(float low, float up)
{
    if (90.0f < up || 90.0f < low || -90.0f > up || -90.0f > low)
        return false;

    kSingleton->buffer.pitch_up_bound = up > low ? up : low;
    kSingleton->buffer.pitch_low_bound = up > low ? low : up;

    return true;
}

bool dvtf_to_send_can_get(void)
{
    return kSingleton->buffer.to_send_can;
}

bool dvtf_to_send_can_set(bool toggle)
{
    if (kSingleton->buffer.to_send_can ^ toggle) {
        kSingleton->buffer.to_send_can = toggle;
        return true;
    }

    return false;
}

bool dvtf_to_loop_set(bool toggle)
{
    if (kSingleton->buffer.to_loop ^ toggle) {
        kSingleton->buffer.to_loop = toggle;
        dvtf_process_start();
        return true;
    } else {
        dvtf_process_stop();
        return false;
    }
}

bool dvtf_timeout_set(uint16_t second)
{
    if (3600 < second)  // ub: 60 minutes
        second = 3600;

    kSingleton->buffer.timeout = second;

    return true;
}

bool dvtf_sampling_cnt_set(uint16_t sampling_cnt)
{
    if (5000 < sampling_cnt)  // ub: 5000
        sampling_cnt = 5000;

    kSingleton->buffer.sampling_cnt = sampling_cnt;

    return true;
}

bool dvtf_mount_height_set(float height)
{
    if (kSingleton->buffer.height_list[0] > height
        || kSingleton->buffer.height_list[HGT_RNG_LIST_CAP-1] < height)
    return false;

    kSingleton->mount_height = height;

    return true;
}

bool dvtf_height_list_set(char **list, int count)
{
    float prev = 0.0f;
    float curr = 0.0f;

    for (int i = 0; i < count; ++i) {
        curr = strtof(list[i], NULL);
        if (prev > curr) {
            memcpy(kSingleton->buffer.height_list, kSingleton->eeprom->height_list,
                   sizeof(kSingleton->buffer.height_list));
            return false;
        }
        kSingleton->buffer.height_list[i] = curr;
        prev = curr;
    }

    return true;
}

bool dvtf_rng_min_list_set(char **list, int count)
{
    float prev = 0.0f;
    float curr = 0.0f;

    for (int i = 0; i < count; ++i) {
        curr = strtof(list[i], NULL);
        if (prev > curr) {
            memcpy(kSingleton->buffer.rng_min_list, kSingleton->eeprom->rng_min_list,
                   sizeof(kSingleton->buffer.rng_min_list));
            return false;
        }
        kSingleton->buffer.rng_min_list[i] = curr;
        prev = curr;
    }

    return true;
}

bool dvtf_rf_set(float bw, float hpf)
{
    if (0.0f > bw || 0.0f > hpf)
        return false;

    kSingleton->buffer.bandwidth_freq = bw;
    kSingleton->buffer.high_pass_freq = hpf;

    return true;
}

bool dvtf_io_condition_set(char **list, int count)
{
    for (int i = 0; i < count; ++i) {
        float temp = strtof(list[i], NULL);
        switch (i) {
        case 0:  // speed_thld
            if (0.0f > temp) return false;
            kSingleton->buffer.speed_thld = temp;
            break;
        case 1:  // yaw_rate_delta
            if (0.0f > temp) return false;
            kSingleton->buffer.yaw_rate_delta = temp;
            break;
        case 2:  // acc_z_delta
            if (0.0f > temp) return false;
            kSingleton->buffer.acc_z_delta = temp;
            break;
        case 3:  // hrz_aoa
            if (0.0f > temp || 90.0f < temp) return false;
            kSingleton->buffer.hrz_aoa = temp;
            break;
        case 4:  // vert_phs_thld
            if (-180.0f > temp || 180.0f < temp) return false;
            kSingleton->buffer.vert_phs_thld = temp;
            break;
        case 5:  // vert_phs_shift
            if (-180.0f > temp || 180.0f < temp) return false;
            kSingleton->buffer.vert_phs_shift = temp;
            break;
        }
    }
    return true;
}

bool dvtf_force_ram_completed_set(void)
{
    TRANSIT_STATE(kSingleton->buffer, kVtfbCorrect);
    kSingleton->buffer.complete_state = kVtfbCompleted;

    return true;
}

bool dvtf_fae_set(char **list, int count)
{
    for (int i = 0; i < count; ++i) {
        float temp = strtof(list[i], NULL);
        switch (i) {
        case 0:  // speed_thld
            if (0.0f > temp) return false;
            kSingleton->buffer.speed_thld = temp;
            break;
        case 1:  // yaw_rate_delta
            if (0.0f > temp) return false;
            kSingleton->buffer.yaw_rate_delta = temp;
            break;
        case 2:  // acc_z_delta
            if (0.0f > temp) return false;
            kSingleton->buffer.acc_z_delta = temp;
            break;
        case 3:  // hrz_aoa
            if (0.0f > temp || 90.0f < temp) return false;
            kSingleton->buffer.hrz_aoa = temp;
            break;
        case 4:  // vert_phs_thld
            if (-180.0f > temp || 180.0f < temp) return false;
            kSingleton->buffer.vert_phs_thld = temp;
            break;
        case 5:  // vert_phs_shift
            if (-180.0f > temp || 180.0f < temp) return false;
            kSingleton->buffer.vert_phs_shift = temp;
            break;
        case 6:  // sampling_cnt
            if (5000 < (uint16_t)temp) return false;
            kSingleton->buffer.sampling_cnt = (uint16_t)temp;
            break;
        case 7:  // mount_height
            if (kSingleton->buffer.height_list[0] > temp
                || kSingleton->buffer.height_list[HGT_RNG_LIST_CAP-1] < temp)
                return false;
            kSingleton->mount_height = temp;
            apply_range_by_height(&kSingleton->buffer);
            tracking_radar_hight_set(temp);
            break;
        default:
            return false;  // impossible
            break;
        }
    }
    return true;
}

uint16_t dvtf_total_sampling_cnt_get(void)
{
    uint16_t total = 0;

    if (NULL == kSingleton->accum_sum)
        return 0;

    for (uint8_t i = 0; i < MEAS_RNG_CAPACITY; ++i)
    total += kSingleton->accum_sum[i].count;

    return total;
}

uint16_t dvtf_sampling_size_get(void)
{
    return SAMPLING_SIZE_CNT_RATIO * kSingleton->buffer.sampling_cnt;
}

/************************************************
 * Private Methods                              *
 ************************************************/
static void state_machine(dvtf_t *kSingleton, vtfb_st state)
{
    switch (state) {
    case kVtfbVehIoInvalid:
        if (kSingleton->eeprom->state != kSingleton->buffer.state) {
            kSingleton->eeprom->state = kSingleton->buffer.state;
            vtfb_param_set();
        }
        spt_resume_to_normal_mode();
        break;
    case kVtfbCorrect:
        TRANSIT_STATE(kSingleton->buffer, kVtfbCorrect);
        kSingleton->buffer.complete_state = kVtfbCompleted;
        kSingleton->eeprom->state = kSingleton->buffer.state;
        kSingleton->eeprom->pitch_ang = kSingleton->buffer.pitch_ang;
        kSingleton->eeprom->complete_state = kSingleton->buffer.complete_state;
        vtfb_param_set();
        spt_resume_to_normal_mode();  // restore config of spt's ram
        float phs_fb = convert_return_angle_to_phase(kSingleton->buffer.pitch_ang);
        // convert ISO to convention, hsft: (+) backward-up tilt
        frame_set_hsft(phs_fb, 1);
        break;
    case kVtfbAngOutOfBounds:
        TRANSIT_STATE(kSingleton->buffer, kVtfbAngOutOfBounds);
        kSingleton->eeprom->state = kSingleton->buffer.state;
        if (kVtfbUndefined == kSingleton->eeprom->complete_state) {
            kSingleton->buffer.complete_state = kVtfbNotCompleted;
            kSingleton->eeprom->complete_state = kSingleton->buffer.complete_state;
        }
        vtfb_param_set();
        spt_resume_to_normal_mode();
        break;
    case kVtfbTimeout:
        if (kVtfbVehIoError == kSingleton->err_state) {
            TRANSIT_STATE(kSingleton->buffer, kVtfbVehIoError);
            kSingleton->eeprom->state = kSingleton->buffer.state;
        } else {
            TRANSIT_STATE(kSingleton->buffer, kVtfbTimeout);
            kSingleton->eeprom->state = kSingleton->buffer.state;
        }
        if (kVtfbUndefined == kSingleton->buffer.complete_state) {
            kSingleton->buffer.complete_state = kVtfbNotCompleted;
            kSingleton->eeprom->complete_state = kSingleton->buffer.complete_state;
        }
        vtfb_param_set();
        spt_resume_to_normal_mode();
        break;
    default:
        break;
    }
}

static vtfb_st initialize_accumulation_list(
    dvtf_accum_t *list, const uint8_t capacity, const dvtf_nvm_t *param, const float rng_delta)
{
    if (0 == capacity)
        return kVtfbVehIoError;  // abnormal

    const float rng_min = rng_delta * floorf((param->rng_min_meas + rng_delta / 2) / rng_delta);

    for (uint8_t i = 0; i < capacity; ++i) {
        list[i].rad_rng = rng_min + i * rng_delta;
        list[i].ang_meas = 0.0f;
        list[i].phs_meas = 0.0f;
        list[i].count = 0;
    }

    return kVtfbSuccess;
}

static vtfb_st initialize_avg_quantity_list(
    dvtf_qty_t *avg_list, const uint8_t capacity, const dvtf_nvm_t *param, const float rng_delta)
{
    if (0 == capacity)
        return kVtfbVehIoError;

    const float rng_min = rng_delta * floorf((param->rng_min_meas + rng_delta / 2) / rng_delta);
    float height = kSingleton->mount_height;
    float temp;

    memset(avg_list, 0, sizeof(dvtf_qty_t) * capacity);
    for (uint8_t i = 0; i < capacity; ++i) {
        avg_list[i].rad_rng = temp = rng_min + i * rng_delta;
        avg_list[i].ang_sim = temp = REVERSED_SIGNF * calculate_simulation_angle(temp, height);
        avg_list[i].phs_sim = convert_return_angle_to_phase(temp);
    }

    return kVtfbSuccess;
}

static vtfb_st initialize_sd_quantity_list(
    dvtf_qty_t *sd_list, const uint8_t capacity, const dvtf_nvm_t *param, const float rng_delta)
{
    if (0 == capacity)
        return kVtfbVehIoError;

    const float rng_min = rng_delta * floorf((param->rng_min_meas + rng_delta / 2) / rng_delta);

    memset(sd_list, 0, sizeof(dvtf_qty_t) * capacity);
    for (uint8_t i = 0; i < capacity; ++i)
        sd_list[i].rad_rng = rng_min + i * rng_delta;

    return kVtfbSuccess;
}

static vtfb_st handle_accumulation(
    dvtf_accum_t *sum, dvtf_accum_t *sq_sum, dvtf_nvm_t *param,
    measurement_group_t *mg_list, const float rng_delta)
{
    const vtfb_st state = handle_io_condition(param);

    if (kVtfbVehIoError == state)
        return kVtfbVehIoError;
    if (kVtfbVehIoInvalid == state)
        return kVtfbVehIoInvalid;

    measurement_t *meas = mg_list->measurements;
    float *epsilon_p = (float *)__float_epsilon;
    float flt_epsilon = *epsilon_p;
    float rng_min = param->rng_min_meas;
    float rng_max = rng_min + (MEAS_RNG_CAPACITY - 1) * rng_delta;
    float temp;

    for (uint16_t i = 0; i < mg_list->mcnt; ++i) {
        // if (vangle == 180.0f)
        if (flt_epsilon > fabs(DEGREE_OF_NO_VERTICAL - fabs(meas[i].vangle)))
            continue;
        // if (vangle >= 0.0f)
        if (param->vert_phs_thld <= meas[i].vangle)
            continue;
        // if not (|angle| > 1.0 degree)
        if (param->hrz_aoa < fabs(meas[i].angle))
            continue;
        // if not stationary
        if (DEFAULT_GATE_STATIONARY_VEL < fabs(meas[i].velocity + get_eps_speed_value() / 3.6f))
            continue;
        // if not in desired range, too small then continue, too large then break
        if (rng_min - 0.5f * rng_delta > meas[i].range)
            continue;
        if (rng_max + 0.5f * rng_delta < meas[i].range)
            break;
        for (uint8_t j = 0; j < MEAS_RNG_CAPACITY; ++j) {
            if (sum[j].rad_rng - 0.5f * rng_delta <= meas[i].range
                && sum[j].rad_rng + 0.5f * rng_delta > meas[i].range) {
                sum[j].phs_meas += temp = meas[i].vangle + param->vert_phs_shift;
                sq_sum[j].phs_meas += temp * temp;
                sum[j].ang_meas += temp = convert_phase_to_return_angle(temp);
                sq_sum[j].ang_meas += temp * temp;
                ++sum[j].count;
                ++sq_sum[j].count;
                break;
            }
        }
    }
    return kVtfbSuccess;
}

static vtfb_st handle_condition(float pitch_ang, dvtf_nvm_t *param)
{
    // check condition, write shared data and write spt param back.
    vtfb_st state = check_quntity_condition(pitch_ang, param);

    return state;
}

static vtfb_st handle_io_condition(const dvtf_nvm_t *param)
{
    if (kVtfbVehIoInvalid == check_vehicle_state())
        return kVtfbVehIoInvalid;

    float speed_thld = param->speed_thld;
    float yaw_rate_delta = param->yaw_rate_delta;
    float acc_z_delta = param->acc_z_delta;
    //float yaw_ang = io_condition->yaw_ang;

    // car speed >= 40.0 km/hr
    if (speed_thld > get_eps_speed_value()) {
#if DYNAMIC_VERTICAL_FEEDBACK_DEBUG
        PRINTF("  Dvtf: %s err: %f\n",
               string_of_error(kCarSpeedNotEnough), get_eps_speed_value());
#endif
        return kVtfbVehIoError;
    }
    // |yaw| <= 0.5 degree/sec
    if (yaw_rate_delta < fabs(get_veh_onboard_filtered_yaw_rate_value())) {
#if DYNAMIC_VERTICAL_FEEDBACK_DEBUG
        PRINTF("  Dvtf: %s err: %f\n",
               string_of_error(kYawRateTooLarge),
               get_veh_onboard_filtered_yaw_rate_value());
#endif
        return kVtfbVehIoError;
    }
    // |acc_z-980| <= 49 cm/sec2 (5% g-force)
    if (acc_z_delta < fabs(get_veh_onboard_filtered_acc_z_value() - 980.0f)) {
#if DYNAMIC_VERTICAL_FEEDBACK_DEBUG
        PRINTF("  Dvtf: %s err: %f\n",
               string_of_error(kAccZDeltaTooLarge),
               get_veh_onboard_filtered_acc_z_value() - 980.0f);
#endif
        return kVtfbVehIoError;
    }

    return kVtfbSuccess;
}

static vtfb_st check_vehicle_state(void)
{
    if (VEH_STATUS_VALID != get_eps_speed_status()) {
#if DYNAMIC_VERTICAL_FEEDBACK_DEBUG
        PRINTF("  Dvtf: %s err: %d\n",
               string_of_error(kEpsSpeedStatusNotValid), get_eps_speed_status());
#endif
        return kVtfbVehIoInvalid;
    }
    if (VEH_STATUS_VALID != get_veh_onboard_filtered_acc_z_status()) {
#if DYNAMIC_VERTICAL_FEEDBACK_DEBUG
        PRINTF("  Dvtf: %s err: %d\n",
               string_of_error(kVehAccZStatusNotValid),
               get_veh_onboard_filtered_acc_z_status());
#endif
        return kVtfbVehIoInvalid;
    }
    if (VEH_STATUS_VALID != get_veh_onboard_filtered_yaw_rate_status()) {
#if DYNAMIC_VERTICAL_FEEDBACK_DEBUG
        PRINTF("  Dvtf: %s err: %d\n",
               string_of_error(kVehYawRateStatusNotValid),
               get_veh_onboard_filtered_yaw_rate_status());
#endif
        return kVtfbVehIoInvalid;
    }

    return kVtfbSuccess;
}

static vtfb_st check_quntity_condition(float pitch_ang, dvtf_nvm_t *param)
{
    const float kUpBound = param->pitch_up_bound;
    const float kLowBound = param->pitch_low_bound;

    if (kUpBound >= pitch_ang && kLowBound <= pitch_ang)
        return kVtfbSuccess;
    else
        return kVtfbAngOutOfBounds;
}

static bool check_accum_count_enough(
    dvtf_accum_t *list, const uint8_t capacity, const uint16_t sampling_cnt)
{
    bool is_each_enough = true;
    uint16_t total = 0;

    // if (each >= sampling_cnt or total >= 10 * sampling_cnt)
    for (uint8_t i = 0; i < capacity; ++i) {
        total += list[i].count;
        if (list[i].count < sampling_cnt)
            is_each_enough = false;
    }

    if (is_each_enough || total >= SAMPLING_SIZE_CNT_RATIO * sampling_cnt)
        return true;
    else
        return false;
}

static bool apply_range_by_height(dvtf_nvm_t *param)
{
    const float height = kSingleton->mount_height;
    const float const *height_list = param->height_list;

    if (height_list[0] > height || height_list[HGT_RNG_LIST_CAP-1] < height)
        return false;

    for (uint8_t i = 0; i < HGT_RNG_LIST_CAP; ++i) {
        if (height_list[i] <= height) {
            param->rng_min_meas = param->rng_min_list[i];
        } else {
            param->rng_min_meas = LINT(param->rng_min_meas, param->rng_min_list[i],
                    (height - height_list[i-1]) / (height_list[i] - height_list[i-1]));
            break;
        }
    }

    return true;
}

static inline float calculate_simulation_angle(float rad_range, float height)
{
    return asinf(height / rad_range) * RADIAN_TO_DEGREE;
}

static inline float convert_phase_to_return_angle(float phase)
{
    // ang_delta = asin(phase/(k d))
    return asinf(phase / (2 * 1.989f * 180.0f)) * RADIAN_TO_DEGREE;
}

static inline float convert_return_angle_to_phase(float angle)
{
    // phs_delta = k d sin(angle) = 2 pi (d/wavelength) sin(angle) (180/pi)
    return 2 * 1.989f * 180.0f * sinf(angle * DEGREE_TO_RADIAN);
}

static inline float calculate_average(float sum, uint32_t count)
{
    return sum / count;
}

static inline float calculate_standard_deviation(float sq_sum, float sum,
                                                 uint32_t count)
{
    return sqrtf(fabs((sq_sum - sum * sum / count) / (count - 1)));
}

static void calculate_avg_sd_result(dvtf_qty_t *avg, dvtf_qty_t *sd,
                                    dvtf_accum_t *sum, dvtf_accum_t *sq_sum)
{
    for (uint8_t i = 0; i < MEAS_RNG_CAPACITY; ++i) {
        if (0 >= sum[i].count)
            continue;
        avg[i].ang_meas = calculate_average(sum[i].ang_meas, sum[i].count);
        avg[i].phs_meas = calculate_average(sum[i].phs_meas, sum[i].count);
        avg[i].ang_feedback = avg[i].ang_sim - avg[i].ang_meas;
        avg[i].phs_feedback = avg[i].phs_sim - avg[i].phs_meas;
        avg[i].count = sum[i].count;
        if (3 > sum[i].count)
            continue;
        sd[i].ang_meas = calculate_standard_deviation(sq_sum[i].ang_meas,
                             sum[i].ang_meas, sq_sum[i].count);
        sd[i].phs_meas = calculate_standard_deviation(sq_sum[i].phs_meas,
                             sum[i].phs_meas, sq_sum[i].count);
        sd[i].ang_feedback = sd[i].ang_meas;
        sd[i].phs_feedback = sd[i].phs_meas;
        sd[i].count = sum[i].count;
    }
}

#if DYNAMIC_VERTICAL_FEEDBACK_DEBUG
static inline const char *string_of_error(dvtf_err errno)
{
    static const char *error_code_list[] = {
        "eps speed not valid",
        "veh acc z not valid",
        "veh yaw rate not valid",
        "hrz auto calib not end",
        "car speed not enough",
        "yaw rate too large",
        "acc z delta too large"
    };

    return error_code_list[errno];
}
#endif

static void dynamic_vertical_feedback_help(void)
{
    PRINTF("----Dynamic Vertical Feedback: command----\n");
    PRINTF("  dvtf calib\n");
    PRINTF("  dvtf stop\n");
    PRINTF("  dvtf cond <up_degree> <low_degree>\n");
    PRINTF("  dvtf can <on: 1/off: 0>\n");
    PRINTF("  dvtf loop <on: 1/off: 0>\n");
    PRINTF("  dvtf timeout <second>\n");
    PRINTF("  dvtf sample_cnt <count>\n");
    PRINTF("  dvtf height <meter>\n");
    PRINTF("  dvtf h_list <h1> <h2> <h3> <h4> ascending sorted\n");
    PRINTF("  dvtf rng_min_list <r1> <r2> <r3> <r4> ascending sorted\n");
    PRINTF("  dvtf rf <bw> <hpf>\n");
    PRINTF("  dvtf io_cond <speed_thld> <yaw_rate> <acc_z> <hrz_aoa> <va_thld> <va_shift>\n");
    PRINTF("  dvtf force_complete\n");
    PRINTF("  dvtf fae <speed_thld> <yaw_rate> <acc_z> <hrz_aoa> <va_thld> <va_shift>\n");
    PRINTF("           <sample_cnt> <height>\n");
}

static void dynamic_vertical_feedback_dump(void)
{
    dvtf_nvm_t *e2p = kSingleton->eeprom;
    dvtf_nvm_t *ram = &kSingleton->buffer;

    PRINTF("----Dynamic Vertical Feedback: status----\n");
    PRINTF("  <hint>: 'dvtf help' to see more commands\n");
    PRINTF("  property:\n");
    PRINTF("  mount_height:   %12.2f m\n", kSingleton->mount_height);
    PRINTF("  rng_min_meas:   %12.1f m\n", ram->rng_min_meas);
    PRINTF("  to_run:         %12s\n", kSingleton->to_run ? "enabled" : "disabled");
    PRINTF("  is_running:     %12s\n", kSingleton->is_running ? "enabled" : "disabled");
    PRINTF("  poll_cnt:       %12u/%5u\n", kSingleton->poll_cnt, kSingleton->poll_csize);
    PRINTF("                  eeprom param |  buffer param\n");
    PRINTF("  complete state: %12s |  %12s\n",
        vtfb_string_of_complete_state(e2p->complete_state),
        vtfb_string_of_complete_state(ram->complete_state));
    PRINTF("  state:          %12s |  %12s\n",
        vtfb_string_of_state(e2p->state), vtfb_string_of_state(ram->state));
    PRINTF("  pitch_ang:      %12.2f |  %12.2f deg\n",
        e2p->pitch_ang, ram->pitch_ang);
    PRINTF("  upper bound:    %12.1f |  %12.1f deg\n",
        e2p->pitch_up_bound, ram->pitch_up_bound);
    PRINTF("  lower bound:    %12.1f |  %12.1f deg\n",
        e2p->pitch_low_bound, ram->pitch_low_bound);
    PRINTF("  bandwidth_freq: %12.2g |  %12.2g hertz\n",
        e2p->bandwidth_freq, ram->bandwidth_freq);
    PRINTF("  high_pass_freq: %12.2g |  %12.2g hertz\n",
        e2p->high_pass_freq, ram->high_pass_freq);
    PRINTF("  height_list:    %4.2f, %4.2f, %4.2f, %4.2f m\n",
        e2p->height_list[0], e2p->height_list[1], e2p->height_list[2],
        e2p->height_list[3]);
    PRINTF("  rng_min_list:   %4.2f, %4.2f, %4.2f, %4.2f m\n",
        e2p->rng_min_list[0], e2p->rng_min_list[1], e2p->rng_min_list[2],
        e2p->rng_min_list[3]);
    PRINTF("  to_send_can:    %12s |  %12s\n",
        e2p->to_send_can ? "enabled" : "disabled",
        ram->to_send_can ? "enabled" : "disabled");
    PRINTF("  to_loop:        %12s |  %12s\n",
        e2p->to_loop ? "enabled" : "disabled",
        ram->to_loop ? "enabled" : "disabled");
    PRINTF("  timeout:        %12u |  %12u sec\n", e2p->timeout, ram->timeout);
    PRINTF("  sampling_cnt:   %12u |  %12u\n",
        e2p->sampling_cnt, ram->sampling_cnt);
    PRINTF("  speed_thld:     %12.1f |  %12.1f km/hr\n",
        e2p->speed_thld, ram->speed_thld);
    PRINTF("  yaw_rate_delta: %12.1f |  %12.1f deg/sec\n",
        e2p->yaw_rate_delta, ram->yaw_rate_delta);
    PRINTF("  acc_z_delta:    %12.1f |  %12.1f cm/sec2\n",
        e2p->acc_z_delta, ram->acc_z_delta);
    PRINTF("  hrz_aoa:        %12.1f |  %12.1f deg\n",
        e2p->hrz_aoa, ram->hrz_aoa);
    PRINTF("  vert_phs_thld:  %12.1f |  %12.1f deg\n",
        e2p->vert_phs_thld, ram->vert_phs_thld);
    PRINTF("  vert_phs_shift: %12.1f |  %12.1f deg\n",
        e2p->vert_phs_shift, ram->vert_phs_shift);

    if (kSingleton->is_running)
        calculate_avg_sd_result(kSingleton->qty_avg, kSingleton->qty_sd,
                                kSingleton->accum_sum, kSingleton->accum_sq_sum);
    dump_quantity(kSingleton->qty_avg, kSingleton->qty_sd);
}

static void dump_quantity(dvtf_qty_t *avg, dvtf_qty_t *sd)
{
    if (NULL != avg) {
        PRINTF("  avg: rad_rng, ang_sim, phs_sim, ang_meas, phs_meas, "
               "ang_fb, phs_fb, count\n");
        for (uint8_t i = 0; i < MEAS_RNG_CAPACITY; ++i) {
        PRINTF("       %7.1f, %7.1f, %7.1f, %8.1f, %8.1f, %6.1f, %6.1f, %5u\n",
               avg[i].rad_rng, avg[i].ang_sim, avg[i].phs_sim,
               avg[i].ang_meas, avg[i].phs_meas, avg[i].ang_feedback,
               avg[i].phs_feedback, avg[i].count);
        }
    }
    if (NULL != sd) {
        PRINTF("   sd: rad_rng, ang_sim, phs_sim, ang_meas, phs_meas, "
               "ang_fb, phs_fb, count\n");
        for (uint8_t i = 0; i < MEAS_RNG_CAPACITY; ++i) {
            PRINTF("       %7.1f, %7.1f, %7.1f, %8.1f, %8.1f, %6.1f, %6.1f, %5u\n",
                   sd[i].rad_rng, sd[i].ang_sim, sd[i].phs_sim,
                   sd[i].ang_meas, sd[i].phs_meas, sd[i].ang_feedback,
                   sd[i].phs_feedback, sd[i].count);
        }
    }
}

/**************************************************
 * Test                                           *
 **************************************************/
static void test_console(char **argv, int argc)
{
    float float_1;
    float float_2;
    uint16_t cnt;

    if (argc == 2 && !strcmp(argv[1], "help")) {
        dynamic_vertical_feedback_help();
    } else if ((argc == 2 || argc == 3) && (!strcmp(argv[1], "calib"))) {
        dvtf_process_start();
    } else if (argc == 2 && !strcmp(argv[1], "stop")) {
        dvtf_process_stop();
        dynamic_vertical_feedback_dump();
    } else if (argc == 4 && !strcmp(argv[1], "cond")) {
        float_1 = strtof(argv[2], NULL);
        float_2 = strtof(argv[3], NULL);
        if (dvtf_condition_set(float_1, float_2)) {
            kSingleton->eeprom->pitch_low_bound = kSingleton->buffer.pitch_low_bound;
            kSingleton->eeprom->pitch_up_bound = kSingleton->buffer.pitch_up_bound;
            vtfb_param_set();
        }
    } else if (argc == 3 && !strcmp(argv[1], "can")) {
        cnt = strtoul(argv[2], NULL, 10);
        if (dvtf_to_send_can_set(cnt)) {
            kSingleton->eeprom->to_send_can = kSingleton->buffer.to_send_can;
            vtfb_param_set();
        }
    } else if (argc == 3 && !strcmp(argv[1], "loop")) {
        cnt = strtoul(argv[2], NULL, 10);
        if (dvtf_to_loop_set(cnt)) {
            kSingleton->eeprom->to_loop = kSingleton->buffer.to_loop;
            vtfb_param_set();
        }
    } else if (argc == 3 && !strcmp(argv[1], "timeout")) {
        cnt = strtoul(argv[2], NULL, 10);
        if (dvtf_timeout_set(cnt)) {
            kSingleton->eeprom->timeout = kSingleton->buffer.timeout;
            vtfb_param_set();
        }
    } else if (argc == 3 && !strcmp(argv[1], "sample_cnt")) {
        cnt = strtoul(argv[2], NULL, 10);
        if (dvtf_sampling_cnt_set(cnt)) {
            kSingleton->eeprom->sampling_cnt = kSingleton->buffer.sampling_cnt;
            vtfb_param_set();
        }
    } else if (argc == 3 && !strcmp(argv[1], "height")) {
        float_1 = strtof(argv[2], NULL);
        if (dvtf_mount_height_set(float_1)) {
            apply_range_by_height(&kSingleton->buffer);
            tracking_radar_hight_set(float_1);
        }
    } else if (argc >= 3 && argc <= 3+HGT_RNG_LIST_CAP-1 && !strcmp(argv[1], "h_list")) {
        if (dvtf_height_list_set(argv+2, argc-2)) {
            memcpy(kSingleton->eeprom->height_list, kSingleton->buffer.height_list, sizeof(kSingleton->buffer.height_list));
            vtfb_param_set();
        }
    } else if (argc >= 3 && argc <= 3+HGT_RNG_LIST_CAP-1 && !strcmp(argv[1], "rng_min_list")) {
        if (dvtf_rng_min_list_set(argv+2, argc-2)) {
            memcpy(kSingleton->eeprom->rng_min_list, kSingleton->buffer.rng_min_list, sizeof(kSingleton->buffer.rng_min_list));
            vtfb_param_set();
        }
    } else if (argc == 4 && !strcmp(argv[1], "rf")) {
        float_1 = strtof(argv[2], NULL);
        float_2 = strtof(argv[3], NULL);
        if (dvtf_rf_set(float_1, float_2)) {
            kSingleton->eeprom->bandwidth_freq = kSingleton->buffer.bandwidth_freq;
            kSingleton->eeprom->high_pass_freq = kSingleton->buffer.high_pass_freq;
            vtfb_param_set();
        }
    } else if (argc >= 3 && argc <= 8 && !strcmp(argv[1], "io_cond")) {
        if (dvtf_io_condition_set(argv+2, argc-2)) {
            kSingleton->eeprom->speed_thld = kSingleton->buffer.speed_thld;
            kSingleton->eeprom->yaw_rate_delta = kSingleton->buffer.yaw_rate_delta;
            kSingleton->eeprom->acc_z_delta = kSingleton->buffer.acc_z_delta;
            kSingleton->eeprom->hrz_aoa = kSingleton->buffer.hrz_aoa;
            kSingleton->eeprom->vert_phs_thld = kSingleton->buffer.vert_phs_thld;
            kSingleton->eeprom->vert_phs_shift = kSingleton->buffer.vert_phs_shift;
            vtfb_param_set();
        }
    } else if (argc == 3 && !strcmp(argv[1], "force_complete")) {
        dvtf_force_ram_completed_set();
    } else if (argc >= 3 && argc <= 10 && !strcmp(argv[1], "fae")) {
        if (dvtf_fae_set(argv+2, argc-2)) {
            kSingleton->eeprom->speed_thld = kSingleton->buffer.speed_thld;
            kSingleton->eeprom->yaw_rate_delta = kSingleton->buffer.yaw_rate_delta;
            kSingleton->eeprom->acc_z_delta = kSingleton->buffer.acc_z_delta;
            kSingleton->eeprom->hrz_aoa = kSingleton->buffer.hrz_aoa;
            kSingleton->eeprom->vert_phs_thld = kSingleton->buffer.vert_phs_thld;
            kSingleton->eeprom->vert_phs_shift = kSingleton->buffer.vert_phs_shift;
            kSingleton->eeprom->sampling_cnt = kSingleton->buffer.sampling_cnt;
            // height not in eeprom/buffer of dvtf but tracking
            vtfb_param_set();
        }
    } else {
        dynamic_vertical_feedback_dump();
    }
}
