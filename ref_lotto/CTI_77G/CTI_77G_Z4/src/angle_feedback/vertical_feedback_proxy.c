#include <stddef.h>  // offsetof()
#include <stdint.h>  // uintptr_t
#include <stdlib.h>
#include <string.h>  // memcpy()
#include <stdio.h>   // sprintf()
#include "vertical_feedback_proxy.h"
#include "tracking.h"

#define CAST(type, var)  (type *)(void *)var
#define VERTICAL_FEEDBACK_PARS_ID  FOURCC('v', 't', 'f', 'b')
#define STR(x)           #x
#define VTFB_ID          STR(vtfb)

typedef struct _VerticalFeedbackProperty {
  vtfb_param_t sync_eeprom;
} vtfb_t;

/************************************************
 * Forward Declarations                         *
 ************************************************/
void vtfb_init(void);
uintptr_t vtfb_static_base_get(void);

// Private Methods
static int vtfb_pars_json(char *);

/************************************************
 * Globals                                      *
 ************************************************/
/*
 * pitch_ang: (lb, ub) = (-90.0, 90.0)
 * pitch_low_bound: (lb, ub) = (-90.0, 90.0), spec. of lower limit of pitch_ang
 * pitch_up_bound: (lb, ub) = (-90.0, 90.0), spec. of upper limit of pitch_ang
 *
 * to_send_can:
 * to_loop:
 * timeout:        (lb, ub) = (0, 3600)
 * sampling_cnt:   (lb, ub) = (0, 5000)
 * bandwidth_freq: (lb, ub) = (0.0, inf)
 * high_pass_freq: (lb, ub) = (0.0, inf)
 * rng_min_meas:   (lb, ub) = (0.0, inf)
 * height_list:    (lb, ub) = (0.3, 1.1)
 * rng_min_list:   (lb, ub) = (0.0, 10.0)
 * speed_thld:     (lb, ub) = (0, inf), car speed > 40.0 km/hr
 * yaw_rate_delta: (lb, ub) = (0, inf), |yaw| <= 1.0 degree/sec
 * acc_z_delta:    (lb, ub) = (0, inf), |acc_z-980| <= 150 cm/sec2 (5% g-force)
 * hrz_aoa:        (lb, ub) = (0, 90.0), |hrz_aoa| <= 3.0 degree
 * vert_phs_thld:  (lb, ub) = (-180.0, 180.0)
 * vert_phs_shift: (lb, ub) = (-180.0, 180.0)
 */
static const vtfb_param_t kDefaultParam = {
    .hdr = {
        .base = (uint32_t)&kDefaultParam,
        .version = 0x0305,
        .size = sizeof(vtfb_param_t),
        .id = VERTICAL_FEEDBACK_PARS_ID,
        .chksum = 0,
        .mask = 0
    },
    .info = {
        .svtf_nvm = {
            .pitch_ang       =      0.0f,
            .pitch_low_bound =     -2.5f,
            .pitch_up_bound  =      2.5f,
            .state           = kVtfbInit,
            .complete_state  = kVtfbUndefined
        },
    }
};
static vtfb_t kSingletonInst;
static vtfb_t * const kSingleton = &kSingletonInst;

/************************************************
 * APIs                                         *
 ************************************************/
void vtfb_init(void)
{
    memcpy(&kSingleton->sync_eeprom, &kDefaultParam, sizeof(vtfb_param_t));
    pars_get(CAST(pars_ctx_t, &kSingleton->sync_eeprom), NULL, vtfb_pars_json);
    svtf_init();
}

uintptr_t vtfb_static_base_get(void)
{
    uintptr_t base = (uintptr_t)(void *)&kSingleton->sync_eeprom;
    uintptr_t offset = (uintptr_t)offsetof(vtfb_param_t, info)
                       + (uintptr_t)offsetof(vtfb_nvm_t, svtf_nvm);

    return base + offset;
}

void vtfb_param_set(void)
{
    pars_set(CAST(pars_ctx_t, &kSingleton->sync_eeprom));
}

/************************************************
 * Private Methods                              *
 ************************************************/
static int vtfb_pars_json(char *ws)
{
    vtfb_param_t *param = &kSingleton->sync_eeprom;
    int cnt = 0;

    if (ws) {
        cnt += sprintf(ws, "{\n");
        cnt += sprintf(ws + cnt, JSON_PARS_HDR_ID,
                   (char)(VERTICAL_FEEDBACK_PARS_ID >> 24),
                   (char)(VERTICAL_FEEDBACK_PARS_ID >> 16),
                   (char)(VERTICAL_FEEDBACK_PARS_ID >> 8),
                   (char)(VERTICAL_FEEDBACK_PARS_ID));
        cnt += sprintf(ws + cnt, JSON_PARS_HDR_VERSION, param->hdr.version);
        cnt += sprintf(ws + cnt, JSON_PARS_HDR_SIZE,
                   param->hdr.size - sizeof(pars_header_t));
        cnt += sprintf(ws + cnt, "\t\"info\":{\n");
        cnt += sprintf(ws + cnt,
                   "\t\t\"svtf_pitch_ang\":{\"t\":\"f32\",\"o\":%d,\"v\":%.2f},\n",
                   offsetof(vtfb_nvm_t, svtf_nvm)
                   + offsetof(svtf_nvm_t, pitch_ang),
                   param->info.svtf_nvm.pitch_ang);
        cnt += sprintf(ws + cnt,
                   "\t\t\"svtf_pitch_low_bound\":{\"t\":\"f32\",\"o\":%d,\"v\":%.2f},\n",
                   offsetof(vtfb_nvm_t, svtf_nvm)
                   + offsetof(svtf_nvm_t, pitch_low_bound),
                   param->info.svtf_nvm.pitch_low_bound);
        cnt += sprintf(ws + cnt,
                   "\t\t\"svtf_pitch_up_bound\":{\"t\":\"f32\",\"o\":%d,\"v\":%.2f},\n",
                   offsetof(vtfb_nvm_t, svtf_nvm)
                   + offsetof(svtf_nvm_t, pitch_up_bound),
                   param->info.svtf_nvm.pitch_up_bound);
        cnt += sprintf(ws + cnt,
                   "\t\t\"svtf_state\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n",
                   offsetof(vtfb_nvm_t, svtf_nvm)
                   + offsetof(svtf_nvm_t, state),
                   param->info.svtf_nvm.state);
        cnt += sprintf(ws + cnt,
                   "\t\t\"svtf_complete_state\":{\"t\":\"u8\",\"o\":%d,\"v\":%d}\n",
                   offsetof(vtfb_nvm_t, svtf_nvm)
                   + offsetof(svtf_nvm_t, complete_state),
                   param->info.svtf_nvm.complete_state);
        cnt += sprintf(ws + cnt, "\t}\n");
        cnt += sprintf(ws + cnt, "}\n");
    }

    return cnt;
}
