/*
 * rmtp_obj_inner_safety_monitor.c
 *
 *  Created on: 2020/07/21
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdint.h>
#include "rmtp.h"
#include "rmtp_msg.h"
#include "rmtp_ids.h"
#include "rmtp_hal.h"
#include "rmtp_api.h"

enum {
	CMD_IDEL			    = 0,
	CMD_GET_DIE_INFO		= 1,
	CMD_GET_RF_ISM_REPORT	= 2
};

static uint8_t pkt[6]= {0};
static const uint8_t attr_access[3] = {
	ATTR_N | ATTR_L,	
	ATTR_R | ATTR_L,
	ATTR_R | ATTR_L
};

static uint8_t  cmd = CMD_IDEL;
static uint8_t  net_id = RMTP_ITF_UNKNOWN;
static uint8_t  *data_ptr= NULL;
static uint16_t send_data_cnt=0;
static uint16_t total_data_size=0;
static uint8_t  send_data_sub_cnt=0;

static uint16_t timeout = 30;

static void reset(void)
{
    cmd = CMD_IDEL;
    send_data_cnt=0;
    send_data_sub_cnt=0;
    total_data_size=0;
    timeout = 30;
}

static int destroy(void) 
{
	reset();	
	return RES_SUCCESS;
}


static void Radar_to_FCT(uint8_t netId)
{
	uint8_t i;	
	uint16_t remain;

    rmtp_set_timer(OBJ_ID_INNER_SAFETY_MONITOR, TIMER_STOP);
    send_data_sub_cnt=0;
    for (i = 0; i < 32; i++) {
        send_data_cnt += 6;
        if (send_data_cnt < total_data_size) {
            rmtp_send_data_section_message(netId, OBJ_ID_INNER_SAFETY_MONITOR, i, data_ptr, 6);
            data_ptr += 6;
            send_data_sub_cnt += 6;
        } else {
            send_data_cnt -= 6;
            remain = total_data_size-send_data_cnt;
            rmtp_send_data_section_message(netId, OBJ_ID_INNER_SAFETY_MONITOR, i, data_ptr, remain);
            data_ptr += remain;
            send_data_sub_cnt += remain;
            send_data_cnt = total_data_size;
            break;
        }
    }
    timeout = 30;
	rmtp_set_timer(OBJ_ID_INNER_SAFETY_MONITOR, TIMER_START);
}

static int timeout_handler(void)
{	
	if ((cmd != CMD_IDEL) && (timeout > 0)) {
		timeout--;		
		if (timeout == 0) {
		    rmtp_set_timer(OBJ_ID_INNER_SAFETY_MONITOR, TIMER_STOP);
			rmtp_send_alarm_message(net_id, OBJ_ID_INNER_SAFETY_MONITOR, ALARM_ID_0, NULL, 0);
			reset();
			return RES_SUCCESS;
		}
	}
	return RES_SUCCESS;
}


static int get_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	uint8_t res = RES_SUCCESS;
    net_id = netId;
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_1: // DIE ID info
		    if(cmd == CMD_IDEL) {
		        cmd = CMD_GET_DIE_INFO;
		        data_ptr=(uint8_t *)spt_work_space_get();
		        if(TEF810X_FAIL== rmtp_get_tef810x_chip_info((TEF810xDieId_t *)data_ptr)){
		             LOG("[RMTP] (get_tef810x_chip_info: error)\n");
		        }
		        total_data_size=sizeof(TEF810xDieId_t);
		        memcpy(pkt, &total_data_size, 2);
			    rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_INNER_SAFETY_MONITOR, attrId, pkt, 2);
			    Radar_to_FCT(netId);
			}else{
			    rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_INNER_SAFETY_MONITOR, attrId, RES_CMD_REJECTED, NULL, 0);			
			    return RES_CMD_REJECTED;
			}
			break;
			
        case ATTR_ID_2: // RF ISM Report
		    if(cmd == CMD_IDEL) {
		        uint8_t i;
		        uint32_t *ism_report_ptr;
		        
		        ism_report_ptr=(uint32_t*)spt_work_space_get();
		        cmd = CMD_GET_RF_ISM_REPORT;
		        if(TEF810X_FAIL== rmtp_rf_selftest(ism_report_ptr, END_OF_MESSAGE*4, pkt )){
		             LOG("[RMTP] (rmtp_rf_selftest: error)\n");
		        }
		        if(pkt[0]==0){
		            total_data_size=0;
		        }else{
		            total_data_size=END_OF_MESSAGE*5;
                }	
                memcpy(&pkt[1], &total_data_size, 2);	            
			    rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_INNER_SAFETY_MONITOR, attrId, pkt, 3);
			    if(total_data_size>0){
			        data_ptr=(uint8_t *)(spt_work_space_get()+(END_OF_MESSAGE*4));
			        for(i=0;i<END_OF_MESSAGE;i++){
			           data_ptr[i*5]=i;
			            memcpy(&data_ptr[(i*5)+1],ism_report_ptr,4);
			            ism_report_ptr++;
			        }
			        Radar_to_FCT(netId);
			    }else{
			        reset();
			    }
			}else{
			    rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_INNER_SAFETY_MONITOR, attrId, RES_CMD_REJECTED, NULL, 0);			
			    return RES_CMD_REJECTED;
			}
			break;
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return res;
}


static int report_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	switch (attrId) {
		case ATTR_ID_0: // Flow control
			if (cmd != CMD_IDEL) {
				switch (data[0]) {
					case FLOW_CTRL_SEND:
						LOG("[RMTP] (Flow control: Send next)\n");
						if(send_data_cnt>=total_data_size){
						    LOG("[RMTP] (Flow control: Send next:error)\n");
						    rmtp_send_alarm_message(netId, OBJ_ID_INNER_SAFETY_MONITOR, ALARM_ID_1, NULL, 0);
						    reset();
						}else{
						    Radar_to_FCT(netId);
						}    
						break;
					case FLOW_CTRL_WAIT:
						LOG("[RMTP] (Flow control: Wait)\n");
						if(send_data_cnt>=total_data_size){
						    rmtp_send_alarm_message(netId, OBJ_ID_INNER_SAFETY_MONITOR, ALARM_ID_1, NULL, 0);
						    reset();
						}else{
						    timeout = 30;
						}
						break;
					case FLOW_CTRL_RESEND:
						LOG("[RMTP] (Flow control: Resend)\n");
						data_ptr-=send_data_sub_cnt;
						send_data_cnt-=send_data_sub_cnt;
						Radar_to_FCT(netId);
						break;
						
					case FLOW_CTRL_DONE:
						LOG("[RMTP]  (Flow control: Done)\n");
						reset();
						break;
						
					case FLOW_CTRL_ABORT:
						LOG("[RMTP]  (Flow control: Abort)\n");
						reset();
						break;
				}
			}else{
			    rmtp_send_alarm_message(netId, OBJ_ID_INNER_SAFETY_MONITOR, ALARM_ID_1, NULL, 0);
			    LOG("[RMTP]  (Flow control: error)\n");
				reset();
			}
			break;
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_SUCCESS;
}

const rmtp_obj_t rmtp_obj_inner_safety_monitor = {
	OBJ_ID_INNER_SAFETY_MONITOR,	// Object ID
	3,								// Attribute number
	(uint8_t*)&attr_access, 		// Attribute access
	2,								// Alarm number
	NULL,							// Initialize handler
	destroy, 						// Destroy handler
	timeout_handler,				// Timeout handler
	get_request_msg_handler,		// Get request message handler
	NULL, 	 	                    // Set request message handler
	NULL,							// Get response message handler
	NULL,							// Set response message handler
	report_msg_handler,				// Report message handler
	NULL,							// Alarm message handler
	NULL,							// Data section message handler
	NULL,							// Send request message handler
	NULL,							// Send report message handler
	NULL,							// Send alarm message handler
	NULL							// Send data section message handler
};
