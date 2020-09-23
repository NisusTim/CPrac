/*
 * rmtp_obj_system_security.c
 *
 *  Created on: 2017/09/26
 *      Author: Benson
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

#define SPECTRUM_FUNCTION     0

enum {
	DATA_SEND_IDEL			= 0,
	DATA_SEND_NOT_READY		= 1,
	DATA_SEND_READY			= 2,
	DATA_SEND_ACTIVE		= 3,
	DATA_SEND_RESEND		= 4,
	DATA_SEND_PAUSE			= 5,
	DATA_SEND_ABORT			= 6,
	DATA_SEND_DONE			= 7
};

static uint8_t pkt[6]= {0};

#if SPECTRUM_FUNCTION
static uint8_t spectrum_in_transit = 0;
static uint32_t spectrum_data_addr = 0;
static uint32_t spectrum_data_size = 0;
static uint8_t data_send_state = DATA_SEND_IDEL;
static uint8_t data_send_net_id = RMTP_ITF_UNKNOWN;
static uint32_t data_send_addr_prev = 0;
static uint32_t data_send_addr_cur = 0;
static int data_flow_ctrl_timeout = 0;
#endif

static uint8_t cmd_netId = RMTP_ITF_UNKNOWN;
static uint8_t cmd_attrId = ATTR_ID_UNKNOWN;
static uint8_t cmd_on = 0;
static uint8_t cmd_timeout = 30;
static uint8_t data_cnt=0;
static uint8_t data_sub_cnt=0;
static uint8_t *data_ptr=NULL;
static uint8_t data_size=72;
static uint8_t doppler_control_index=0;

static const uint8_t attr_access[5] = {
	ATTR_N | ATTR_L,	
	ATTR_W | ATTR_L,
	ATTR_W | ATTR_L,
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_R | ATTR_W | ATTR_L 
};


#if SPECTRUM_FUNCTION
static void signal_spectrum_received_done(uint32_t addr, uint32_t size)
{
	if (spectrum_in_transit == 1) {
		LOG("[RMTP] spectrum siganl (addr=%x, size=%d)\n", (UINT)addr, (UINT)size);
		spectrum_data_addr = addr;
		spectrum_data_size = size;
		data_send_state = DATA_SEND_READY;
		data_send_addr_prev = 0;
		data_send_addr_cur = 0;
		data_flow_ctrl_timeout = 0;
	}	
}
#endif


static void reset(void)
{
#if SPECTRUM_FUNCTION
	if (spectrum_in_transit == 1) {
		spectrum_in_transit = 0;
		data_send_state = DATA_SEND_IDEL;
		spectrum_data_addr = 0;
		spectrum_data_size = 0;
		data_send_addr_prev = 0;
		data_send_addr_cur = 0;
		data_flow_ctrl_timeout = 0;
		rmtp_set_timer(OBJ_ID_SIGNAL_PROCESS, TIMER_STOP);
	}
	else
#endif	
    {
        rmtp_set_timer(OBJ_ID_SIGNAL_PROCESS, TIMER_STOP);
        cmd_on = 0;
	    cmd_timeout = 30;
        data_cnt=0;
        data_sub_cnt=0;
        data_ptr=NULL;
        data_size=72;
	}	
}

static int destroy(void) 
{
	reset();	
	return RES_SUCCESS;
}


static void Radar_to_FCT(uint8_t netId)
{
	uint8_t remain;
    uint8_t i;
    rmtp_set_timer(OBJ_ID_SIGNAL_PROCESS, TIMER_STOP);
    data_sub_cnt=0;
    for(i=0;i<32;i++){
        data_cnt+=6;
        if(data_cnt<data_size){
            rmtp_send_data_section_message(netId, OBJ_ID_SIGNAL_PROCESS, i, data_ptr, 6);
            data_ptr+=6;
            data_sub_cnt+=6;
        }else{
            data_cnt-=6;
            remain=data_size-data_cnt;
            rmtp_send_data_section_message(netId, OBJ_ID_SIGNAL_PROCESS, i, data_ptr, remain);
            data_ptr+=remain;
            data_sub_cnt+=remain;
            data_cnt=data_size;
            break;
        }
    }
    cmd_timeout=30;
	rmtp_set_timer(OBJ_ID_SIGNAL_PROCESS, TIMER_START);
}

static uint8_t * convert_doppler_data_to_RMTP(uint8_t *doppler)
{
    float angle=0; 
    float vangle=0;
    uint8_t * cmplx_ptr;
    uint8_t * data_ptr=(uint8_t*)spt_work_space_get();
    
    angle=DEGREE_OF_RADIAN(aoaidx_asin(((target_p)doppler)->aoaidx));
    vangle=(180*asin((float)(((target_p)doppler)->vangle)/716.04))/PI;
    cmplx_ptr=(uint8_t*)((target_p)doppler)->cmplx;
    
	memcpy(data_ptr,    &angle,     4);
	memcpy(data_ptr+4,  &vangle,    4);
    memcpy(data_ptr+8,  cmplx_ptr,  data_size-8);

	return data_ptr;
}

static void doppler_done(uint8_t res, uint8_t *data)
{
	uint16_t size;
	memset(pkt, 0, 6);
	if ((res == RES_SUCCESS) && (cmd_on == 1)) {
		cmd_timeout = 30;
		if(doppler_control_index==1){
		    data_size=72;
		}else{
		    data_size=40;
		}
		data_ptr=convert_doppler_data_to_RMTP(data);
		size=data_size;
		memcpy(pkt, (uint8_t *)&size, 2);	
		rmtp_send_ok_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS, ATTR_ID_4, pkt, 2);
		cmd_on=2;
		Radar_to_FCT(cmd_netId);
	} else {
		reset();
		rmtp_send_err_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS, ATTR_ID_4, RES_CMD_PROCESS_ERR, NULL, 0);
	}	
}	


static int timeout_handler(void)
{
#if SPECTRUM_FUNCTION
	int i = 0;
	int new_addr = 0;
	int size = 0;
	uint8_t *data = NULL;

	if (spectrum_in_transit == 1) {
		switch (data_send_state) {
			case DATA_SEND_IDEL:
			case DATA_SEND_ABORT:
			case DATA_SEND_DONE:
				LOG("[RMTP] spectrum (IDEL/ABORT/DONE prev=%d, cur=%d)\n", (UINT)data_send_addr_prev, (UINT)data_send_addr_cur);
				reset();
				break;
			case DATA_SEND_READY:
				LOG("[RMTP] spectrum (READY)\n");
				data_send_state = DATA_SEND_ACTIVE;
				break;
			case DATA_SEND_ACTIVE:
				LOG("[RMTP] spectrum (ACTIVE)\n");
				data_send_addr_prev = data_send_addr_cur;
				break;
			case DATA_SEND_RESEND:
				LOG("[RMTP] spectrum (RESEND)\n");
				data_send_addr_cur = data_send_addr_prev;
				data_send_state = DATA_SEND_ACTIVE;				
				break;
			case DATA_SEND_PAUSE:
				LOG("[RMTP] spectrum (PAUSE:%d)\n", data_flow_ctrl_timeout);
				data_flow_ctrl_timeout++;	
				if (data_flow_ctrl_timeout >= 35) {
					LOG("[RMTP] spectrum (timeout=%d)\n",  data_flow_ctrl_timeout);
					rmtp_send_alarm_message(data_send_net_id, OBJ_ID_SIGNAL_PROCESS, ALARM_ID_0, NULL, 0);
					reset();
				}
				break;
			default:
				break;
		}
		if (data_send_state == DATA_SEND_ACTIVE) {
			LOG("[RMTP] spectrum (SEND addr=%d)\n", (UINT)data_send_addr_prev);
			for (i = 0; i < 8; i++) {
				if (data_send_addr_cur < spectrum_data_size) {
					data = (uint8_t *)(spectrum_data_addr + data_send_addr_cur);
					new_addr = data_send_addr_cur + 6;
					if (new_addr <= spectrum_data_size) {
						rmtp_send_data_section_message(data_send_net_id, OBJ_ID_SIGNAL_PROCESS, i, data, 6);
						data_send_addr_cur = new_addr;;
					} else {
						size = spectrum_data_size - data_send_addr_cur;
						rmtp_send_data_section_message(data_send_net_id, OBJ_ID_SIGNAL_PROCESS, i, data, size);
						data_send_addr_cur += size;
					}
					LOG("[RMTP] spectrum (SEND seqNum=%d prev=%d, cur=%d)\n", i, (UINT)data_send_addr_prev, (UINT)data_send_addr_cur);
				}
			}
			data_flow_ctrl_timeout = 0;
			data_send_state = DATA_SEND_PAUSE;
		}
	}
	else
#endif	

    if (cmd_timeout > 0) {
		cmd_timeout--;		
		if (cmd_timeout == 0) {
		    rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_STOP);
		    if(cmd_on == 1){
                rmtp_send_err_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS, ATTR_ID_4, RES_CMD_PROCESS_TIMEOUT, NULL, 0);
            }else if(cmd_on == 2){
                rmtp_send_alarm_message(cmd_netId, OBJ_ID_SIGNAL_PROCESS, ALARM_ID_0, NULL, 0);
            }
            reset();
            return RES_CMD_PROCESS_TIMEOUT;
        }
    }
	return RES_SUCCESS;
}

static int set_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	//int size = 0;
	uint8_t res = RES_ERROR;
	uint16_t frequency;
	uint8_t tx;
	uint8_t times;
    float range;
    
	memset(pkt, 0, 6);
	switch (attrId) {
#if SPECTRUM_FUNCTION
	    case ATTR_ID_1:                             //set Tx, Rx, v_bin_start, v_bin_end, r_bin_start, r_bin_end             
	        if(     (data[0]<5)                     //Tx:           0:short, 1:long, 2:Tx1, 3:Tx2, 4:Tx3, 
	            &&  (data[1]!=0)                    //Rx:           b0~b7 -> R1~R8
	            &&  (data[2]<128)                   //v_bin_start:  0~127
	            &&  (data[3]<128)                   //v_bin_end:    0~127
	            &&  (data[3]>=data[2])              //v_bin_end >= v_bin_start
	            &&  (data[5]>=data[4])              //r_bin_end >= r_bin_start  
	         ) 
			{
		        if(spectrum_in_transit==0)
		        {
		            spectrum_in_transit=1;
		            data_send_state = DATA_SEND_NOT_READY;
					data_send_net_id = netId;
		            size=rmtp_signal_process_spectrum(data[0],data[1],data[2],data[3],data[4],data[5],&signal_spectrum_received_done);
		            if(size>0)
		            {
		                pkt[0] = (uint8_t)((size & 0xFF00) >> 8);
					    pkt[1] = (uint8_t)(size & 0x00FF);
					    rmtp_set_timer(OBJ_ID_SIGNAL_PROCESS, TIMER_START);
					    return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS, attrId, pkt, 2);
		            }
		            else
		            if(size==-1)        //frame play busy
		            {
		                reset();
		                return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS, attrId, RES_SYSTEM_BUSY, NULL, 0);
		            }        
		            else
		            {
		                reset();
		                return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS, attrId, RES_CMD_UNSUPPORTED, NULL, 0);
		            }
		        }
		        else
		        {
		            
		            return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS, attrId, RES_CMD_REJECTED, NULL, 0);
		            
		        }
		    }
		    else 
		    {
				return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS, attrId, RES_PARAMETER_ERROR, NULL, 0);
			}        
			break;
#endif
        case ATTR_ID_2:

            memcpy(&frequency, &data[0], sizeof(uint16_t));
            tx=data[2];
            times=data[3];
            if(tx < 3)
            {    
                int return_value;
                return_value = rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS, ATTR_ID_2, NULL, 0);
                rmtp_lock_frequency_mode_set(frequency,tx|(netId<<2),times);
                return (return_value);
            }        
            else
            {
                return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS, attrId, RES_PARAMETER_ERROR, NULL, 0);
            }
            break;
        
        case ATTR_ID_4:
            if (cmd_on == 0) {
				memcpy(&range, &data[1], sizeof(float));
				res = rmtp_doppler_control(data[0], range, doppler_done);
				if (res == RES_SUCCESS) {
					cmd_on = 1;
					cmd_netId = netId;
					cmd_attrId = attrId;
					cmd_timeout = 50;
					doppler_control_index=data[0];
					rmtp_set_timer(OBJ_ID_SIGNAL_PROCESS, TIMER_START);
				} else {
					rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS, attrId, RES_CMD_PROCESS_ERR, NULL, 0);
				}	
			} else {
				rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS, attrId, RES_CMD_REJECTED, NULL, 0);
				return RES_CMD_REJECTED;
			}
			break;
			
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;
}

static int report_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	switch (attrId) {
		case ATTR_ID_0: // Flow control
		    
#if SPECTRUM_FUNCTION		    
			if (spectrum_in_transit == 1) {
				switch (data[0]) {
					case FLOW_CTRL_SEND:
						LOG("[RMTP] spectrum (Flow control: Send next)\n");
						if (data_send_addr_cur >= spectrum_data_size) {
							data_send_state = DATA_SEND_DONE;
							rmtp_send_alarm_message(netId, OBJ_ID_SIGNAL_PROCESS, ALARM_ID_1, NULL, 0);
						} else {							
							data_send_state = DATA_SEND_ACTIVE;
						}
						break;
					case FLOW_CTRL_WAIT:
						LOG("[RMTP] spectrum (Flow control: Wait)\n");
						if (data_send_addr_cur >= spectrum_data_size) {
							data_send_state = DATA_SEND_DONE;
							rmtp_send_alarm_message(netId, OBJ_ID_SIGNAL_PROCESS, ALARM_ID_1, NULL, 0);
						} else {
							data_send_state = DATA_SEND_PAUSE;
						}
						break;
					case FLOW_CTRL_RESEND:
						LOG("[RMTP] spectrum (Flow control: Resend)\n");
						data_send_state = DATA_SEND_RESEND;
						break;
					case FLOW_CTRL_DONE:
						LOG("[RMTP] spectrum (Flow control: Done)\n");
						data_send_state = DATA_SEND_DONE;
						reset();
						break;
					case FLOW_CTRL_ABORT:
						LOG("[RMTP] spectrum (Flow control: Abort)\n");
						data_send_state = DATA_SEND_ABORT;
						reset();
						break;
				}
			}
			else
#endif
            if ((cmd_on == 2) && (data_ptr != NULL)) {    
				switch (data[0]) {
					case FLOW_CTRL_SEND:
						LOG("[RMTP] (Flow control: Send next)\n");
						if(data_cnt>=data_size){
						    LOG("[RMTP] (Flow control: Send next:error)\n");
						    rmtp_send_alarm_message(netId, OBJ_ID_SIGNAL_PROCESS, ALARM_ID_1, NULL, 0);
						    reset();
						}else{
						    Radar_to_FCT(netId);
						}    
						break;
					case FLOW_CTRL_WAIT:
						LOG("[RMTP] (Flow control: Wait)\n");
						if(data_cnt>=data_size){
						    rmtp_send_alarm_message(netId, OBJ_ID_SIGNAL_PROCESS, ALARM_ID_1, NULL, 0);
						    reset();
						}else{
							cmd_timeout = 30;
						}
						break;
					case FLOW_CTRL_RESEND:
						LOG("[RMTP] (Flow control: Resend)\n");
						data_ptr-=data_sub_cnt;
						data_cnt-=data_sub_cnt;
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
			}
			break;
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;	
}

const rmtp_obj_t rmtp_obj_signal_process = {
	OBJ_ID_SIGNAL_PROCESS,			// Object ID
	5,								// Attribute number
	(uint8_t*)&attr_access, 		// Attribute access
	2,								// Alarm number
	NULL,							// Initialize handler
	destroy, 						// Destroy handler
	timeout_handler,				// Timeout handler
	NULL,							// Get request message handler
	set_request_msg_handler, 	 	// Set request message handler
	NULL,							// Get response message handler
	NULL,							// Set response message handler
	report_msg_handler,				// Report message handler
	NULL,							// Alarm message handler
	NULL,							// Data section message handler
	NULL,							// Send request message handler
	NULL,		                    // Send report message handler
	NULL,							// Send alarm message handler
	NULL							// Send data section message handler
};
