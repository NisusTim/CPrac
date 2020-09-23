/*
 * vertical_feedback_proxy.h
 *
 *  Created on: 2020-05-07
 *      Author: TimChang
 */

#ifndef VERTICAL_FEEDBACK_PROXY_H_
#define VERTICAL_FEEDBACK_PROXY_H_

#include "parameters.h"
#include "static_vertical_feedback.h"

typedef struct _VerticalFeedbackNVM {
    svtf_nvm_t svtf_nvm;
} vtfb_nvm_t;

typedef struct _VerticalFeedbackParameter {
    pars_header_t hdr;
    vtfb_nvm_t    info;
} vtfb_param_t;

void vtfb_init(void);
uintptr_t vtfb_static_base_get(void);
void vtfb_param_set(void);

#endif  // VERTICAL_FEEDBACK_PROXY_H_
