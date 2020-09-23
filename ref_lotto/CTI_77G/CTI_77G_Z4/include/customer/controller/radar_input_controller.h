/*
 * controller.h
 *
 *  Created on: 2019/5/2
 *      Author: WoodLiu
 */

#ifndef CONTROLLER_RADAR_INPUT_CONTROLLER_H_
#define CONTROLLER_RADAR_INPUT_CONTROLLER_H_

#include "can_msg_format.h"
#include "isotp.h"

void radar_input_controller_init();
void json_req_handle(IsoTpLink *isotp_link);

#endif /* CONTROLLER_RADAR_INPUT_CONTROLLER_H_ */
