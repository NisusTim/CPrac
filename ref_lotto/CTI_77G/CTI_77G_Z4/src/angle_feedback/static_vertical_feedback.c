#include <stdint.h>
#include <stdlib.h>         // strtof(), strtoul()
#include <string.h>         // memcpy(), memset()
#include <stdbool.h>
#include <math.h>           // fabs(), copysignf(), powf(), sqrtf(), sinf(), atanf()
#include "static_vertical_feedback.h"
#include "vertical_feedback_shared.h"
#include "vertical_feedback_proxy.h"
#include "vehicle.h"
#include "timer.h"
#include "custom_math.h"    // RADIAN_TO_DEGREE, DEGREE_TO_RADIAN
#include "console_api.h"    // PRINTF()
#include "console_cmd.h"    // console_command_reg()
#include "console.h"        // put_string()
#include "parameters.h"
#include "frame.h"          // frame_set_hsft()

#define CAST(type, var)  (type *)(void *)var
#define STATIC_VERTICAL_FEEDBACK_PARS_ID  FOURCC('s', 'v', 't', 'f')
#define STR(x)           #x
#define SVTF_ID          STR(svtf)

#define TRANSIT_STATE(buffer, new_state)  \
    buffer.state = new_state

#define SAMPLING_RATE    50  // ms
#define SAMPLING_COUNT   (1000 / SAMPLING_RATE)  // per second
#define SAMPLING_TICKS   (TIMER_1000_MS_TICKS / SAMPLING_COUNT)  // per second
#define POLLING_TIMEOUT  30  // second
#define POLLING_TICKS    (TIMER_1000_MS_TICKS * POLLING_TIMEOUT)

typedef struct _StaticVerticalFeedbackPhysicalQuantity {
    float acc_x;          // in cm/sec2, (+) backward
    float acc_y;          // in cm/sec2, (+) right
    float acc_z;          // in cm/sec2, (+) down
    float roll_ang;       // in degree, rotation of x-axis, ISO: (+) right-down tilt
    float pitch_ang;      // in degree, rotation of y-axis, ISO: (+) forward-down tilt
    float yaw_ang;        // in degree, rotation of z-axis, ISO: (+) forward-left rotate
    float feedback_phs;   // in degree, (+) down tilt, same as pitch_ang
} svtf_qty_t;

typedef struct _StaticVerticalFeedbackProperty {
    svtf_qty_t  phys_qty_avg;
    svtf_qty_t  phys_qty_sd;
    svtf_nvm_t *eeprom;   // synchronized with eeprom from vtfb
    svtf_nvm_t  buffer;   // run time buffer
    timer_t *   timer;
    uint8_t     sampling_cnt;
} svtf_t;

/************************************************
 * Forward Declarations                         *
 ************************************************/
void svtf_init(void);
void svtf_process(bool loop);
void svtf_process_stop(void);
vtfb_st svtf_buffer_state_get(void);
vtfb_st svtf_eeprom_state_get(void);
vtfb_cpl_st svtf_eeprom_complete_state_get(void);
float svtf_buffer_pitch_angle_get(void);
float svtf_eeprom_pitch_angle_get(void);
void svtf_condition_set(float up, float low);

// Private Methods
static void state_machine(svtf_t *, vtfb_st, svtf_qty_t *);
static vtfb_st single_process(svtf_qty_t *, svtf_nvm_t *);
static vtfb_st handle_quantity(svtf_qty_t *);
static vtfb_st handle_condition(svtf_nvm_t *, svtf_qty_t *);
static void get_acc_from_vehicle(svtf_qty_t *);
static void calculate_quantity(svtf_qty_t *);
static vtfb_st check_vehicle_state(void);
static vtfb_st check_quantity_condition(svtf_qty_t *, svtf_nvm_t *);
static inline float calculate_average(float, uint32_t);
static inline float calculate_standard_deviation(float, float, uint32_t);
static void static_vertical_feedback_dump(void);
static void dump_quantity(svtf_qty_t *, svtf_qty_t *);

static void test_console(char **, int);

/************************************************
 * Globals                                      *
 ************************************************/
static svtf_t kSingletonInst;
static svtf_t * const kSingleton = &kSingletonInst;

/************************************************
 * APIs                                         *
 ************************************************/
void svtf_init(void)
{
    kSingleton->eeprom = CAST(svtf_nvm_t, vtfb_static_base_get());
    memcpy(&kSingleton->buffer, kSingleton->eeprom, sizeof(svtf_nvm_t));
    TRANSIT_STATE(kSingleton->buffer, kVtfbReady);
    kSingleton->sampling_cnt = SAMPLING_COUNT;
#if STATIC_VERTICAL_FEEDBACK_DEBUG
    console_command_reg(SVTF_ID, test_console);
#endif
}

void svtf_process(bool loop)
{
    static uint8_t count = 0;
    static uint16_t poll_count = 0;
    static svtf_qty_t sum;
    static svtf_qty_t sq_sum;  // square sum
    static bool loop_flag = false;
    svtf_qty_t temp;
    svtf_qty_t avg;  // average
    svtf_qty_t sd;   // standard deviation

    // init: set polling timer
    if (NULL == kSingleton->timer) {
        loop_flag = loop;
        kSingleton->timer = timer_set(SVTF_ID, SAMPLING_TICKS, POLLING_TICKS,
                                (event_proc_p)svtf_process, &loop_flag);
        poll_count = 0;
        count = 0;
        memset(&sum, 0, sizeof(sum));
        memset(&sq_sum, 0, sizeof(sq_sum));
    }

    // running: sampling I/O process
    ++poll_count;
    if (0 <= count && kSingleton->sampling_cnt > count) {
        if (kVtfbVehIoError == handle_quantity(&temp)) {
            TRANSIT_STATE(kSingleton->buffer, kVtfbVehIoError);
        } else {
            TRANSIT_STATE(kSingleton->buffer, kVtfbProcessing);
            sum.acc_x += temp.acc_x;
            sum.acc_y += temp.acc_y;
            sum.acc_z += temp.acc_z;
            sum.roll_ang += temp.roll_ang;
            sum.pitch_ang += temp.pitch_ang;
            sum.yaw_ang += temp.yaw_ang;
            sum.feedback_phs += temp.feedback_phs;
            if (3 < kSingleton->sampling_cnt) {
                sq_sum.acc_x += temp.acc_x * temp.acc_x;
                sq_sum.acc_y += temp.acc_y * temp.acc_y;
                sq_sum.acc_z += temp.acc_z * temp.acc_z;
                sq_sum.roll_ang += temp.roll_ang * temp.roll_ang;
                sq_sum.pitch_ang += temp.pitch_ang * temp.pitch_ang;
                sq_sum.yaw_ang += temp.yaw_ang * temp.yaw_ang;
                sq_sum.feedback_phs += temp.feedback_phs * temp.feedback_phs;
            }
            ++count;
        }
    }

    // terminate 1: calculation process
    if (count == kSingleton->sampling_cnt) {
        if (NULL != kSingleton->timer && !strcmp(SVTF_ID, kSingleton->timer->name))
            timer_unset(&kSingleton->timer);
        kSingleton->timer = NULL;
        avg.acc_x = calculate_average(sum.acc_x, count);
        avg.acc_y = calculate_average(sum.acc_y, count);
        avg.acc_z = calculate_average(sum.acc_z, count);
        avg.roll_ang = calculate_average(sum.roll_ang, count);
        avg.pitch_ang = calculate_average(sum.pitch_ang, count);
        avg.yaw_ang = calculate_average(sum.yaw_ang, count);
        avg.feedback_phs = calculate_average(sum.feedback_phs, count);
        sd.acc_x = calculate_standard_deviation(sq_sum.acc_x, sum.acc_x, count);
        sd.acc_y = calculate_standard_deviation(sq_sum.acc_y, sum.acc_y, count);
        sd.acc_z = calculate_standard_deviation(sq_sum.acc_z, sum.acc_z, count);
        sd.roll_ang = calculate_standard_deviation(sq_sum.roll_ang,
                                                   sum.roll_ang, count);
        sd.pitch_ang = calculate_standard_deviation(sq_sum.pitch_ang,
                                                    sum.pitch_ang, count);
        sd.yaw_ang = calculate_standard_deviation(sq_sum.yaw_ang,
                                                  sum.yaw_ang, count);
        sd.feedback_phs = calculate_standard_deviation(sq_sum.feedback_phs,
                                                       sum.feedback_phs, count);
        kSingleton->phys_qty_avg = avg;
        kSingleton->phys_qty_sd = sd;
        // pitch angle condition check
        kSingleton->buffer.pitch_ang = avg.pitch_ang;
        // disable saving I/O, only print quantity
        if (kVtfbSuccess == handle_condition(&kSingleton->buffer, &avg))
            state_machine(kSingleton, kVtfbCorrect, &avg);
        else
            state_machine(kSingleton, kVtfbAngOutOfBounds, NULL);
        static_vertical_feedback_dump();
        dump_quantity(&avg, &sd);
        if (loop_flag)
            svtf_process(loop_flag);
        return;
    }

    // terminate 2: timeout or impossible
    if (POLLING_TICKS == poll_count || POLLING_TICKS < poll_count) {
        state_machine(kSingleton, kVtfbTimeout, NULL);
        if (loop_flag)
            svtf_process(loop_flag);
        return;
    }
}

void svtf_process_stop(void)
{
    if (NULL != kSingleton->timer && !strcmp(SVTF_ID, kSingleton->timer->name))
        timer_unset(&kSingleton->timer);
    kSingleton->timer = NULL;
    TRANSIT_STATE(kSingleton->buffer, kVtfbReady);
}

vtfb_st svtf_buffer_state_get(void)
{
    return kSingleton->buffer.state;
}

vtfb_st svtf_eeprom_state_get(void)
{
    return kSingleton->eeprom->state;
}

vtfb_cpl_st svtf_eeprom_complete_state_get(void)
{
    return kSingleton->eeprom->complete_state;
}

float svtf_buffer_pitch_angle_get(void)
{
    // convert ISO to convention, (+) backward-up tilt
    return -1.0f * kSingleton->buffer.pitch_ang;
}

float svtf_eeprom_pitch_angle_get(void)
{
    // convert ISO to convention, (+) backward-up tilt
    return -1.0f * kSingleton->eeprom->pitch_ang;
}

void svtf_condition_set(float up, float low)
{
    if (90.0f < up || 90.0f < low || -90.0f > up || -90.0f > low)
        return;

    kSingleton->buffer.pitch_up_bound = up > low ? up : low;
    kSingleton->buffer.pitch_low_bound = up > low ? low : up;
}

/************************************************
 * Private Methods                              *
 ************************************************/
static void state_machine(svtf_t *kSingleton, vtfb_st state, svtf_qty_t *avg)
{
    switch (state) {
    case kVtfbCorrect:
        TRANSIT_STATE(kSingleton->buffer, kVtfbCorrect);
        kSingleton->buffer.complete_state = kVtfbCompleted;
        kSingleton->eeprom->state = kSingleton->buffer.state;
        kSingleton->eeprom->pitch_ang = kSingleton->buffer.pitch_ang;
        kSingleton->eeprom->complete_state = kSingleton->buffer.complete_state;
        vtfb_param_set();
        // convert ISO to convention, hsft: (+) backward-up tilt
        frame_set_hsft(-1.0f * avg->feedback_phs, 1);
        break;
    case kVtfbAngOutOfBounds:
        TRANSIT_STATE(kSingleton->buffer, kVtfbAngOutOfBounds);
        kSingleton->eeprom->state = kSingleton->buffer.state;
        if (kVtfbUndefined == kSingleton->eeprom->complete_state) {
            kSingleton->buffer.complete_state = kVtfbNotCompleted;
            kSingleton->eeprom->complete_state = kSingleton->buffer.complete_state;
        }
        vtfb_param_set();
        break;
    case kVtfbTimeout:
        if (NULL != kSingleton->timer && !strcmp(SVTF_ID, kSingleton->timer->name))
            timer_unset(&kSingleton->timer);
        kSingleton->timer = NULL;
        if (kVtfbVehIoError != kSingleton->buffer.state) {
            TRANSIT_STATE(kSingleton->buffer, kVtfbTimeout);
            kSingleton->eeprom->state = kSingleton->buffer.state;
        }
        if (kVtfbUndefined == kSingleton->buffer.complete_state) {
            kSingleton->buffer.complete_state = kVtfbNotCompleted;
            kSingleton->eeprom->complete_state = kSingleton->buffer.complete_state;
        }
        vtfb_param_set();
        static_vertical_feedback_dump();
        break;
    default:
        break;
    }
}

static vtfb_st single_process(svtf_qty_t *quantity, svtf_nvm_t *condition)
{
    vtfb_st state;

    // sampling I/O and calculation process
    state = handle_quantity(quantity);
    if (kVtfbVehIoError == state) {
        PRINTF("  --vtfb: %s--\n", vtfb_string_of_state(state));
        return kVtfbVehIoError;
    }

    // pitch angle condition check
    state = handle_condition(condition, quantity);

    return state;
}

static vtfb_st handle_quantity(svtf_qty_t *quantity)
{
    // check vehicle, get acc and calculate quantity.
    if (kVtfbVehIoError == check_vehicle_state())
        return kVtfbVehIoError;

    get_acc_from_vehicle(quantity);
    calculate_quantity(quantity);
    return kVtfbSuccess;
}

static vtfb_st handle_condition(svtf_nvm_t *param, svtf_qty_t *quantity)
{
    // check condition, write shared data and write spt param back.
    vtfb_st state = check_quantity_condition(quantity, param);

    return state;
}

static void get_acc_from_vehicle(svtf_qty_t *qty)
{
    qty->acc_x = get_veh_onboard_filtered_acc_x_value();
    qty->acc_y = get_veh_onboard_filtered_acc_y_value();
    qty->acc_z = get_veh_onboard_filtered_acc_z_value();
}

static void calculate_quantity(svtf_qty_t *qty)
{
    float acc_x = qty->acc_x;
    float acc_y = qty->acc_y;
    float acc_z = qty->acc_z;

    //             original       optimized
    // roll_ang :  arctan(y/z)    arctan(y / (x^2 + z^2)^0.5)
    // pitch_ang:  arctan(x/z)    arctan((x^2 + y^2)^0.5 / z)
    // yaw_ang  :  arctan(x/y)    arctan(x / (y^2 + z^2)^0.5)
    qty->roll_ang =
        copysignf(1.0f, 1.0f*acc_y*acc_z) * RADIAN_TO_DEGREE
        * atanf(fabs(acc_y) / sqrtf(powf(acc_z, 2)+powf(acc_x, 2)));
    qty->pitch_ang =
        copysignf(1.0f, -1.0f*acc_x*acc_z) * RADIAN_TO_DEGREE
        * atanf(sqrtf(powf(acc_x, 2)+powf(acc_y, 2)) / fabs(acc_z));
    qty->yaw_ang =
        copysignf(1.0f, 1.0f*acc_x*acc_y) * RADIAN_TO_DEGREE
        * atanf(fabs(acc_x) / sqrtf(powf(acc_y, 2)+powf(acc_z, 2)));
    qty->feedback_phs =
        2 * 1.989f * 180.0f * sinf(qty->pitch_ang * DEGREE_TO_RADIAN);
}

static vtfb_st check_vehicle_state(void)
{
    if (VEH_STATUS_VALID == get_veh_motion_status()
        && VEH_MOTION_STATUS_STATIONARY == get_veh_motion_value()
        && VEH_STATUS_VALID == get_veh_onboard_filtered_acc_x_status()
        && VEH_STATUS_VALID == get_veh_onboard_filtered_acc_y_status()
        && VEH_STATUS_VALID == get_veh_onboard_filtered_acc_z_status())
        return kVtfbSuccess;
    else
        return kVtfbVehIoError;
}

static vtfb_st check_quantity_condition(svtf_qty_t *qty, svtf_nvm_t *param)
{
    const float kUpBound = param->pitch_up_bound;
    const float kLowBound = param->pitch_low_bound;

    if (kUpBound >= qty->pitch_ang && kLowBound <= qty->pitch_ang)
        return kVtfbSuccess;
    else
        return kVtfbAngOutOfBounds;
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

static void static_vertical_feedback_dump(void)
{
    svtf_nvm_t *e2p = kSingleton->eeprom;
    svtf_nvm_t *ram = &kSingleton->buffer;

    PRINTF("----Vertical Feedback: command----\n");
    PRINTF("  vtfb meas\n");
    PRINTF("  vtfb calib\n");
    PRINTF("  vtfb stop\n");
    PRINTF("  vtfb cond <up_degree> <low_degree>\n");
    PRINTF("----Vertical Feedback: status----\n");
    PRINTF("  eeprom param:\n");
    PRINTF("  complete state: %s\n", vtfb_string_of_complete_state(e2p->complete_state));
    PRINTF("  state:          %s\n", vtfb_string_of_state(e2p->state));
    PRINTF("  pitch_ang:      %8.2f deg\n", e2p->pitch_ang);
    PRINTF("  upper bound:    %8.1f deg\n", e2p->pitch_up_bound);
    PRINTF("  lower bound:    %8.1f deg\n", e2p->pitch_low_bound);
    PRINTF("  ram buffer param:\n");
    PRINTF("  complete state: %s\n", vtfb_string_of_complete_state(ram->complete_state));
    PRINTF("  state:          %s\n", vtfb_string_of_state(ram->state));
    PRINTF("  pitch_ang:      %8.2f deg\n", ram->pitch_ang);
    PRINTF("  upper bound:    %8.1f deg\n", ram->pitch_up_bound);
    PRINTF("  lower bound:    %8.1f deg\n", ram->pitch_low_bound);
    dump_quantity(&kSingleton->phys_qty_avg, &kSingleton->phys_qty_sd);
    PRINTF("\n");
}

static void dump_quantity(svtf_qty_t *avg, svtf_qty_t *sd)
{
  if (NULL != avg && NULL == sd) {
    PRINTF("  quantity          avg |  unit\n");
    PRINTF("  acc_x:        %7.1f   cm/s2\n", avg->acc_x);
    PRINTF("  acc_y:        %7.1f   cm/s2\n", avg->acc_y);
    PRINTF("  acc_z:        %7.1f   cm/s2\n", avg->acc_z);
    PRINTF("  roll_ang:     %7.2f     deg\n", avg->roll_ang);
    PRINTF("  pitch_ang:    %7.2f     deg\n", avg->pitch_ang);
    PRINTF("  yaw_ang:      %7.2f     deg\n", avg->yaw_ang);
    PRINTF("  feedback_phs: %7.2f     deg\n", avg->feedback_phs);
  } else if (NULL != avg && NULL != sd) {
    PRINTF("  quantity          avg |   sd |  unit\n");
    PRINTF("  acc_x:        %7.1f   %4.1f   cm/s2\n", avg->acc_x, sd->acc_x);
    PRINTF("  acc_y:        %7.1f   %4.1f   cm/s2\n", avg->acc_y, sd->acc_y);
    PRINTF("  acc_z:        %7.1f   %4.1f   cm/s2\n", avg->acc_z, sd->acc_z);
    PRINTF("  roll_ang:     %7.2f   %4.2f     deg\n", avg->roll_ang, sd->roll_ang);
    PRINTF("  pitch_ang:    %7.2f   %4.2f     deg\n", avg->pitch_ang, sd->pitch_ang);
    PRINTF("  yaw_ang:      %7.2f   %4.2f     deg\n", avg->yaw_ang, sd->yaw_ang);
    PRINTF("  feedback_phs: %7.2f   %4.2f     deg\n", avg->feedback_phs, sd->feedback_phs);
  }
}

/**************************************************
 * Test                                           *
 **************************************************/
static void test_console(char **argv, int argc)
{
    svtf_qty_t avg;
    float up;
    float low;
    uint8_t cnt;

    if (argc == 1) {
        static_vertical_feedback_dump();
    } else if (argc == 2 && (!strcmp(argv[1], "meas"))) {
        handle_quantity(&avg);
        dump_quantity(&avg, NULL);
    } else if ((argc == 2 || argc == 3) && (!strcmp(argv[1], "calib"))) {
        cnt = strtoul(argv[2], NULL, 10);
        if (argc == 2) {
            kSingleton->sampling_cnt = SAMPLING_COUNT;
            svtf_process(false);
        } else if (argc == 3 && cnt == 1) {
            kSingleton->buffer.state = single_process(&kSingleton->phys_qty_avg, &kSingleton->buffer);
            dump_quantity(&kSingleton->phys_qty_avg, NULL);
        } else if (argc == 3 && (!strcmp(argv[2], "loop"))) {
            svtf_process(true);
        } else {
            kSingleton->sampling_cnt = cnt;
            svtf_process(false);
        }
    } else if (argc == 2 && (!strcmp(argv[1], "stop"))) {
        svtf_process_stop();
        static_vertical_feedback_dump();
    } else if (argc == 4 && (!strcmp(argv[1], "cond"))) {
        up = strtof(argv[2], NULL);
        low = strtof(argv[3], NULL);
        svtf_condition_set(up, low);
        kSingleton->eeprom->pitch_low_bound = kSingleton->buffer.pitch_low_bound;
        kSingleton->eeprom->pitch_up_bound = kSingleton->buffer.pitch_up_bound;
        vtfb_param_set();
    }
}
