#ifndef STATIC_VERTICAL_FEEDBACK_H_
#define STATIC_VERTICAL_FEEDBACK_H_

#include <stdbool.h>
#include "vertical_feedback_shared.h"

#define STATIC_VERTICAL_FEEDBACK_DEBUG       1

#define STATIC_NVM_MEMBERS                      \
    VTFB_SHARED_NVM_MEMBERS;

typedef struct _StaticVerticalFeedbackParameterInfo {
    STATIC_NVM_MEMBERS;
} svtf_nvm_t;

void svtf_init(void);
void svtf_process(bool loop);
void svtf_process_stop(void);
vtfb_st svtf_buffer_state_get(void);
vtfb_st svtf_eeprom_state_get(void);
vtfb_cpl_st svtf_eeprom_complete_state_get(void);
float svtf_buffer_pitch_angle_get(void);
float svtf_eeprom_pitch_angle_get(void);
void svtf_condition_set(float up, float low);

#endif  // STATIC_VERTICAL_FEEDBACK_H_
