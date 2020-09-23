/*
 * rmtp_obj_system_config.c
 *
 *  Created on: 2017/10/23
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

enum {
	FLAG_ID_LIST	        = 0,
	FLAG_CFG_DATA	        = 1,
	FLAG_READ_ALL_CFG_DATA  = 2,
	FLAG_UNKNOWN            = 255
};

enum {
    CFG_MODE_IDLE           =0,
    CFG_MODE_FCT_TO_RADAR   =1,
    CFG_MODE_RADAR_TO_FCT   =2,
    CFG_MODE_UNKNOWN        = 255
};

static uint8_t cfg_mode = CFG_MODE_IDLE;
static uint8_t cfg_net_id = RMTP_ITF_UNKNOWN;
static uint8_t cfg_cmd = SUB_TYPE_UNKNOWN;
static uint32_t cfg_id = 0;
static uint16_t cfg_ver = 0;
static uint16_t cfg_size = 0;
static uint16_t cfg_sec_num = 0;
static uint16_t cfg_timeout = 50;
static uint8_t *cfg_data = NULL;

static uint16_t send_data_cnt=0;
static uint8_t  send_data_sub_cnt=0;
static uint8_t  seqNum_cnt=0;
static uint8_t  *data_cur_ptr= NULL;
static uint16_t recv_data_cnt=0;
static uint8_t  err_seq_flag=0;
static uint8_t  cfg_attr_id=0;
static uint8_t  pkt[6]= {0};

static const uint8_t attr_access[6] = {
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_N | ATTR_L,
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_W | ATTR_L
};

static int reset(void)
{
	rmtp_set_timer(OBJ_ID_SYSTEM_CONFIG, TIMER_STOP);
	cfg_mode = CFG_MODE_IDLE;
	cfg_net_id = RMTP_ITF_UNKNOWN;
	cfg_cmd = SUB_TYPE_UNKNOWN;
	cfg_id = 0;
	cfg_ver = 0;
	cfg_size = 0;
	cfg_sec_num = 0;
	cfg_timeout = 50;
	cfg_data = NULL;

    send_data_cnt=0;
    send_data_sub_cnt=0;
    seqNum_cnt=0;
    data_cur_ptr= NULL;
    recv_data_cnt=0;
    err_seq_flag=0;
    cfg_attr_id=0;
	return RES_SUCCESS;
}

static void Radar_to_FCT(uint8_t netId)
{
	uint8_t i;	
	uint16_t remain;

    rmtp_set_timer(OBJ_ID_SYSTEM_CONFIG, TIMER_STOP);
    send_data_sub_cnt=0;
    for (i = 0; i < 32; i++) {
        send_data_cnt += 6;
        if (send_data_cnt < cfg_size) {
            rmtp_send_data_section_message(netId, OBJ_ID_SYSTEM_CONFIG, i, cfg_data, 6);
            cfg_data += 6;
            send_data_sub_cnt += 6;
        } else {
            send_data_cnt -= 6;
            remain = cfg_size-send_data_cnt;
            rmtp_send_data_section_message(netId, OBJ_ID_SYSTEM_CONFIG, i, cfg_data, remain);
            cfg_data += remain;
            send_data_sub_cnt += remain;
            send_data_cnt = cfg_size;
            break;
        }
    }
    cfg_attr_id = ATTR_ID_2;
    cfg_timeout = 30;
	rmtp_set_timer(OBJ_ID_SYSTEM_CONFIG, TIMER_START);
}

static int destroy(void) 
{
	if (cfg_mode != CFG_MODE_IDLE) {		
		reset();
	}
	
	return RES_SUCCESS;
}

static int timeout_handler(void)
{	
	if ((cfg_mode != CFG_MODE_IDLE) && (cfg_timeout > 0)) {
		cfg_timeout--;		
		if (cfg_timeout == 0) {
		    rmtp_set_timer(OBJ_ID_SYSTEM_CONFIG, TIMER_STOP);
			LOG("[RMTP] system config: timeout!\n");
			if(cfg_attr_id==ATTR_ID_2){
			    if(cfg_mode==CFG_MODE_FCT_TO_RADAR){
			        pkt[0] = FLOW_CTRL_TIMEOUT;
		            rmtp_send_report_message(cfg_net_id, OBJ_ID_SYSTEM_CONFIG, ATTR_ID_2, pkt, 1);
		            if(cfg_id){
		                pars_get(pars_ctx_get(cfg_id),NULL,NULL);           //Restore the original parameters 
		            }
		        }else if(cfg_mode==CFG_MODE_RADAR_TO_FCT){
		            rmtp_send_alarm_message(cfg_net_id, OBJ_ID_SYSTEM_CONFIG, ALARM_ID_0, NULL, 0);
		        }
			}else{
			    rmtp_send_err_response_message(cfg_net_id, cfg_cmd, OBJ_ID_SYSTEM_CONFIG, cfg_attr_id, RES_CMD_PROCESS_TIMEOUT, NULL, 0);
			}
			
			reset();
			return RES_SUCCESS;
		}
	}

	return RES_SUCCESS;
}

static int get_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	int res=RES_SUCCESS;
	uint8_t flags;
	uint32_t id;
	uint16_t ver, size, json_size;
	uint8_t *info = NULL;
		
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_0: // Configuration control
			if (cfg_mode == CFG_MODE_IDLE) {
			    cfg_attr_id=attrId;
				flags = data[0];
				if (flags == FLAG_ID_LIST) {
					cfg_data = rmtp_get_data();
					rmtp_get_pars_id_list(cfg_data, (uint16_t *)&cfg_size);
					if (cfg_size == 0) {
						cfg_data = NULL;
						return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_SYSTEM_CONFIG, attrId, RES_CMD_PROCESS_ERR, NULL, 0);
					} else if ((cfg_size > 0) && (cfg_data != NULL)) {
						cfg_mode = CFG_MODE_RADAR_TO_FCT;
						cfg_net_id = netId;
						cfg_cmd = SUB_TYPE_GET;
						cfg_id = 0;
						cfg_ver = 0;
						cfg_sec_num = 0;
						pkt[0] = 0xFF;
						pkt[1] = 0xFF;
						memcpy(&pkt[2], &cfg_size, sizeof(uint16_t));
						res=rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_SYSTEM_CONFIG, attrId, pkt, 6);
						Radar_to_FCT(netId);
					}					
				} else if (flags == FLAG_CFG_DATA) {
					memcpy(&id, &data[1], sizeof(uint32_t)); 
					info = rmtp_get_pars_info(id, (uint16_t *)&ver, (uint16_t *)&size);
					if ((info != NULL) && (ver != 0) && (size != 0)) {
						info = rmtp_get_pars_json_data(id, (uint16_t *)&json_size);
						if ((info != NULL) && (json_size != 0)) {
							memcpy(&pkt[0], &ver, sizeof(uint16_t));
							memcpy(&pkt[2], &size, sizeof(uint16_t));
							memcpy(&pkt[4], &json_size, sizeof(uint16_t));
							cfg_mode = CFG_MODE_RADAR_TO_FCT;
							cfg_net_id = netId;
							cfg_cmd = SUB_TYPE_GET;
							cfg_id = id;
							cfg_ver = ver;
							cfg_size = json_size;
							cfg_sec_num = 0;
							cfg_data = info;
							res=rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_SYSTEM_CONFIG, attrId, pkt, 6);
							Radar_to_FCT(netId);
						}
					}						
				} else if (flags == FLAG_READ_ALL_CFG_DATA) {
				    info = rmtp_get_all_pars_json_data((uint16_t *)&json_size);
				    if ((info != NULL) && (json_size != 0)) {
				        memset(pkt, 0xff, 4);
				        memcpy(&pkt[4], &json_size, sizeof(uint16_t));
				        cfg_mode = CFG_MODE_RADAR_TO_FCT;
						cfg_net_id = netId;
						cfg_cmd = SUB_TYPE_GET;
						cfg_size = json_size;
						cfg_sec_num = 0;
						cfg_data = info;
						res= rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_SYSTEM_CONFIG, attrId, pkt, 6);
						Radar_to_FCT(netId);
				    }
				}else{
				    return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_SYSTEM_CONFIG, attrId, RES_PARAMETER_ERROR, NULL, 0);
				}
			}else{
			    rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_SYSTEM_CONFIG, attrId, RES_CMD_REJECTED, NULL, 0);			
			    return RES_CMD_REJECTED;
			}
		break;	
			
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return res;
}

static int set_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	int res = RES_SUCCESS;
	uint32_t id;
	uint16_t ver, size;
	uint8_t *info = NULL;
		
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_0: // Configuration control
			if (cfg_mode == CFG_MODE_IDLE) {
				memcpy(&id, &data[0], sizeof(uint32_t));
				info = rmtp_get_pars_info(id, (uint16_t *)&ver, (uint16_t *)&size);
				if ((info != NULL) && (size > 0)) {
					memcpy(&pkt[0], &ver, sizeof(uint16_t));
					memcpy(&pkt[2], &size, sizeof(uint16_t));
					cfg_mode = CFG_MODE_FCT_TO_RADAR;
					cfg_net_id = netId;
					cfg_cmd = SUB_TYPE_SET;
					cfg_id = id;
					cfg_ver = ver;
					cfg_size = size;
					cfg_sec_num = 0;
					cfg_timeout = 30;
					cfg_data = info;
					data_cur_ptr= info;
					recv_data_cnt=0;
					cfg_attr_id=ATTR_ID_2;
					rmtp_set_timer(OBJ_ID_SYSTEM_CONFIG, TIMER_START);						
					return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_SYSTEM_CONFIG, attrId, pkt, 6);					
				}
				return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SYSTEM_CONFIG, attrId, RES_PARAMETER_ERROR, NULL, 0);
			}
			rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SYSTEM_CONFIG, attrId, RES_CMD_REJECTED, NULL, 0);			
			return RES_CMD_REJECTED;
		
		case ATTR_ID_5: //Configuration reset
		    res = rmtp_set_configuration_reset((uint32_t *)data);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_SYSTEM_CONFIG, attrId, NULL, 0);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SYSTEM_CONFIG, attrId, res, NULL, 0);
			}
		    
		    break;	
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;
}

static int data_section_msg_handler(uint8_t netId, uint8_t seqNum, uint8_t *data)
{
    memset(pkt, 0, 6);
	if (cfg_mode == CFG_MODE_FCT_TO_RADAR) {
	    rmtp_set_timer(OBJ_ID_SYSTEM_CONFIG, TIMER_STOP);
	    if(seqNum_cnt!=seqNum){
	        err_seq_flag=1;
	    }
        recv_data_cnt+=6;
        seqNum_cnt++;
        if(	recv_data_cnt >= cfg_size)
        {
            memcpy(data_cur_ptr,data,(cfg_size+6)-recv_data_cnt);
            data_cur_ptr+=6;
            if(err_seq_flag==0){
                rmtp_set_pars_info(cfg_id, cfg_data, cfg_size);
                pkt[0] = FLOW_CTRL_DONE;
                rmtp_send_report_message(netId, OBJ_ID_SYSTEM_CONFIG, ATTR_ID_2, pkt, 1);
                reset();
                return RES_SUCCESS;
            }else{
                data_cur_ptr-=(seqNum_cnt*6);
		        recv_data_cnt-=(seqNum_cnt*6);
		        err_seq_flag=0;
		        pkt[0] = FLOW_CTRL_RESEND;
		        rmtp_send_report_message(netId, OBJ_ID_SYSTEM_CONFIG, ATTR_ID_2, pkt, 1);
            }
        }else{ 
            memcpy(data_cur_ptr,data,6);
            data_cur_ptr+=6;
	        if(seqNum_cnt==32){
	            if(err_seq_flag==0){
		            pkt[0] = FLOW_CTRL_SEND;
		            rmtp_send_report_message(netId, OBJ_ID_SYSTEM_CONFIG, ATTR_ID_2, pkt, 1);
		        }else{
		            data_cur_ptr-=(seqNum_cnt*6);
		            recv_data_cnt-=(seqNum_cnt*6);
		            err_seq_flag=0;
		            pkt[0] = FLOW_CTRL_RESEND;
		            rmtp_send_report_message(netId, OBJ_ID_SYSTEM_CONFIG, ATTR_ID_2, pkt, 1);
		        }
		        seqNum_cnt=0;
		    }
		}
		cfg_attr_id=ATTR_ID_2;
		cfg_timeout = 30;
		rmtp_set_timer(OBJ_ID_SYSTEM_CONFIG, TIMER_START);		
	}else{
		pkt[0] = FLOW_CTRL_ABORT;
		LOG("[RMTP] FlowCtrl: ABORT\n");
		rmtp_send_report_message(netId, OBJ_ID_SYSTEM_CONFIG, ATTR_ID_2, pkt, 1);
	}	

	return RES_SUCCESS;
}



static int report_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	switch (attrId) {
		case ATTR_ID_2: // Flow control
			if (cfg_mode == CFG_MODE_RADAR_TO_FCT) {
				switch (data[0]) {
					case FLOW_CTRL_SEND:
						LOG("[RMTP] (Flow control: Send next)\n");
						if(send_data_cnt>=cfg_size){
						    LOG("[RMTP] (Flow control: Send next:error)\n");
						    rmtp_send_alarm_message(netId, OBJ_ID_SYSTEM_CONFIG, ALARM_ID_1, NULL, 0);
						    reset();
						}else{
						    Radar_to_FCT(netId);
						}    
						break;
					case FLOW_CTRL_WAIT:
						LOG("[RMTP] (Flow control: Wait)\n");
						if(send_data_cnt>=cfg_size){
						    rmtp_send_alarm_message(netId, OBJ_ID_SYSTEM_CONFIG, ALARM_ID_1, NULL, 0);
						    reset();
						}else{
						    cfg_timeout = 30;
						}
						break;
					case FLOW_CTRL_RESEND:
						LOG("[RMTP] (Flow control: Resend)\n");
						cfg_data-=send_data_sub_cnt;
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
			}
			break;
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_SUCCESS;
}


const rmtp_obj_t rmtp_obj_system_config = {
	OBJ_ID_SYSTEM_CONFIG,			// Object ID
	6,								// Attribute number
	(uint8_t*)&attr_access, 		// Attribute access
	0,								// Alarm number
	NULL,							// Initialize handler
	destroy, 						// Destroy handler
	timeout_handler,				// Timeout handler
	get_request_msg_handler,		// Get request message handler
	set_request_msg_handler, 	 	// Set request message handler
	NULL,							// Get response message handler
	NULL,							// Set response message handler
	report_msg_handler,				// Report message handler
	NULL,							// Alarm message handler
	data_section_msg_handler,		// Data section message handler
	NULL,							// Send request message handler
	NULL,							// Send report message handler
	NULL,							// Send alarm message handler
	NULL							// Send data section message handler
};
