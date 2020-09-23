/*
 * vertical_feedback_shared.h
 *
 *  Created on: 2020-05-06
 *      Author: TimChang
 */

#ifndef VERTICAL_FEEDBACK_SHARED_H_
#define VERTICAL_FEEDBACK_SHARED_H_

#include <stdint.h>

typedef enum _VerticalFeedbackState {
    // Need to be sync with vtfb_string_of_state()
    // State or error code for process or exception handling.
    kVtfbSuccess          =  0,  // UDS: N/A
    kVtfbInit             =  1,  // UDS: N/A
    kVtfbReady            =  2,  // UDS: N/A
    kVtfbProcessing       =  3,  // UDS: 8, normally sampling
    kVtfbVehIoError       =  4,  // UDS: 4, i/o value valid but not satisfied
    // End of result.
    kVtfbVehIoInvalid     =  5,  // UDS: 5, i/o invalid
    kVtfbCorrect          =  6,  // UDS: 0
    kVtfbAngOutOfBounds   =  7,  // UDS: 3
    kVtfbTimeout          =  8   // UDS: 6
} vtfb_st;

typedef enum _VerticalFeedbackCompleteState {
    // Need to be sync with vtfb_string_of_complete_state()
    kVtfbUndefined        =  0,  // UDS: 0x00
    kVtfbNotCompleted     =  1,  // UDS: 0x55
    kVtfbCompleted        =  2   // UDS: 0xAA
} vtfb_cpl_st;

/*
 * pitch_ang: in degree, rotation of y-axis, (+) up tilt, result output
 *            where pitch_ang = -1.0 * ang_feedback
 * pitch_up_bound: in degree, (+) up tilt, pitch angle limits
 * pitch_low_bound: in degree, (+) up tilt
 * state:
 * complete_state:
 */
#define VTFB_SHARED_NVM_MEMBERS                  \
    float   pitch_ang;                           \
    float   pitch_low_bound;                     \
    float   pitch_up_bound;                      \
    uint8_t state;                               \
    uint8_t complete_state

const char *vtfb_string_of_state(vtfb_st state);
const char *vtfb_string_of_complete_state(vtfb_cpl_st complete_state);

#endif  // VERTICAL_FEEDBACK_SHARED_H_
