#include "vertical_feedback_shared.h"

/************************************************
 * Forward Declarations                         *
 ************************************************/
const char *vtfb_string_of_state(vtfb_st state);
const char *vtfb_string_of_complete_state(vtfb_cpl_st complete_state);

/************************************************
 * Globals                                      *
 ************************************************/

/************************************************
 * APIs                                         *
 ************************************************/
const char *vtfb_string_of_state(vtfb_st state)
{
    static const char *state_list[] = {
        "success",
        "initializing",
        "ready",
        "processing",
        "vehicle i/o error",
        "vehicle i/o invalid",
        "correct",
        "angle out of bounds",
        "timeout"
    };

    return state_list[state];
}

const char *vtfb_string_of_complete_state(vtfb_cpl_st complete_state)
{
    static const char *complete_state_list[] = {
        "undefined",
        "not completed",
        "completed"
    };

    return complete_state_list[complete_state];
}
