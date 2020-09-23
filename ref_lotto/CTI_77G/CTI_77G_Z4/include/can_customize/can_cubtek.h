/*
 * can_cubtek.h
 *
 *  Created on: 2017/04/28/
 *      Author: user
 */

#ifndef CAN_CUBTEK_H_
#define CAN_CUBTEK_H_
#include "customer.h"
#include "parameters.h"

#define FAW_DID_PARS_ID							FOURCC('d','i','d','p')

typedef enum {
	CAN_STATUS_NORMAL 	 = 0,
	CAN_STATUS_ABNORMAL  = 1,
	CAN_STATUS_FCCU_ERR  = 2,
	CAN_STATUS_ISM_ERR 	 = 3,
	CAN_STATUS_STACK_ERR = 4,
	CAN_STATUS_SIGNALS_ERR = 5
} cub_func_status;

typedef union CUB_Obj_list_info_tag {
  uint64_t R;
  struct {
	uint64_t num         :6;
	uint64_t reserved1   :1;
	uint64_t tunnel_flag :1;
	uint64_t func_status :8;
	uint64_t cip_id 	 :8;
	uint64_t cip_acc_id  :8;
	uint64_t cip_aeb_id	 :8;
	uint64_t reserved2   :8;
	uint64_t cnt         :16;
  } B;
} cub_obj_list_info;

typedef union CUB_auto_calib_info_tag {
  uint64_t R;
  struct {
	uint64_t auto_calib_left_num	:8;
	uint64_t auto_calib_right_num	:8;
	uint64_t reserved				:16;
	float	 calib_angle;
  } B;
} cub_auto_calib_info;

typedef union CUB_dvtf_tag {
  uint64_t R;
  struct {
    uint64_t sampling_cnt     :16;
    uint64_t max_sampling_cnt :16;
    float    pitch_ang;
  } B;
} cub_dvtf;

typedef union CUB_Obj_list0_tag {
  uint64_t R;
  struct {
	uint64_t pos_x :12;
	uint64_t pos_y :12;
	uint64_t vel_x :12;
	uint64_t vel_y :12;
	uint64_t obj_id: 8;
	uint64_t cip_acc:1;
	uint64_t cip_aeb:1;
	uint64_t emergency_warn:1;
	uint64_t pre_warn:1;
	uint64_t cip:1;
	uint64_t warn_dist:1;
	uint64_t cnt:2;
  } B;
} cub_obj_list0;

typedef union CUB_Obj_list1_tag {
  uint64_t R;
  struct {
	uint64_t acc_x :12;
	uint64_t :4;
	uint64_t obj_id: 8;
	uint64_t status :3;
	uint64_t reserved1 :2;
	uint64_t Dynamic :3;
	uint64_t vangle :16;
	uint64_t guardrail_cnt :6;
	uint64_t probability:2;
	uint64_t rcs_type:6;
	uint64_t cnt:2;
  } B;
} cub_obj_list1;

typedef union Cubtek_Fcw_Warning_request {
  uint64_t R;
  struct {
	  uint64_t :4;
	  uint64_t warning:1;
	  uint64_t pre_warning:1;
	  uint64_t emg_warning:1;
	  uint64_t  :57;
  } B;
} CUBTEK_FCW_WARN_REQ;

#ifdef ENABLE_BSW_UDS_NM
typedef struct {
	// FAW UDS DID parameter data
	uint8_t configInfo[16];
	uint8_t	vin[17];
	uint8_t alignmentAutoDetectHAngle; // degree, offset:0, scale:0.1
	uint8_t alignmentAutoDetectVAngle; // degree, offset:0, scale:0.1
	uint8_t alignmentAutoAlignHAngle; // degree, offset:0, scale:0.1, range: -12.8 ~ 12.7
	uint8_t alignmentAutoAlignVAngle; // degree, offset:0, scale:0.1, range: -12.8 ~ 12.7
	uint8_t	gSecurityAcessAttempNumber;
	uint8_t	ecuInstallationDate[4];
	uint8_t	radarManufactureData[12];
	uint8_t is_did_300_301_written;     // DID:300 (bit7~bit4), DID:301(bit3~bit0)
	uint8_t is_rid_0201_enable_pb;      // Is enable RID 0201 progress bar
	                                    // 0: Setting by customer
	                                    // 1: Disable
	                                    // 2: Enable
	uint8_t is_autodetect_en_by_cus;	// 0: Setting by customer
										// 1: Disable
										// 2: Enable
	uint8_t	reserved1[15];
	uint8_t	reserved2[16];
} faw_did_info_t, *faw_did_info_p;

typedef struct {
	pars_header_t hdr;
	faw_did_info_t info;
} faw_did_pars_t, *faw_did_pars_p;

typedef enum {
	CAN_EnRx_EnTx 	 = 0,
	CAN_DisRx_EnTx  = 1,
	CAN_EnRx_DisTx  = 2,
	CAN_DisRx_DisTx  = 3
} cub_can_status;

typedef enum {
	DIDPARS_SAVE_INDIRECT  = 0,        // Save faw did pars indirectly 
 	DIDPARS_SAVE_DIRECT  = 1           // Save faw did pars directly
} cub_faw_did_pars_save_status;

#endif

void cubtek_init(void);
void cubtek_did_init(void);
#ifdef ENABLE_BSW_UDS_NM
void cubtek_can_vehcle_info2_proc(uint64_t data);
void cubtek_can_info_proc(uint64_t data);
#else
void cubtek_can_vehcle_info2_proc(can_message_p msg);
void cubtek_can_info_proc(can_message_p msg);
#endif
//void cubtek_can_send_warning_message(void* x);
void cubtek_can_set_func_status(uint8_t status);
uint8_t cubtek_can_get_func_status(void);

#ifdef ENABLE_BSW_UDS_NM
uint8_t* cubtek_faw_did_config_info_get();
uint8_t* cubtek_faw_did_vin_get();
uint8_t* cubtek_faw_did_aligment_auto_detect_h_angle_get();
uint8_t* cubtek_faw_did_aligment_auto_detect_v_angle_get();
uint8_t* cubtek_faw_did_aligment_auto_align_h_angle_get();
uint8_t* cubtek_faw_did_aligment_auto_align_v_angle_get();
void cubtek_faw_did_aligment_auto_detect_h_angle_set_and_save(uint8_t value);
void cubtek_faw_did_aligment_auto_detect_v_angle_set_and_save(uint8_t value);
void cubtek_faw_did_aligment_auto_align_h_angle_set_and_save(uint8_t value);
void cubtek_faw_did_aligment_auto_align_v_angle_set_and_save(uint8_t value);
uint8_t* cubtek_faw_did_tester_series_number_get();
uint8_t* cubtek_faw_did_programming_date_get();
uint8_t* cubtek_faw_did_ecu_installation_date_get();
uint8_t* cubtek_faw_did_radar_manufacture_data_get();
uint8_t* cubtek_faw_did_reserved_1_get();
uint8_t* cubtek_faw_did_reserved_2_get();
uint8_t* cubtek_faw_did_g_security_acess_attemp_number_get();
uint8_t* cubtek_faw_did_is_300_301_written_get();
void cubtek_faw_did_pars_save_fun();
void cubtek_faw_did_pars_save(uint8_t status);

uint8_t cubtek_faw_did_ds_1s_delay_status_get();
void cubtek_faw_did_ds_1s_delay_status_set(uint8_t status);

uint8_t cubtek_faw_did_ds_communication_bus_off_status_get();
void cubtek_faw_did_ds_communication_bus_off_status_set(uint8_t status);
uint8_t cubtek_faw_did_ds_can_comm_lost_after_wakeup_status_get();
void cubtek_faw_did_ds_can_comm_lost_after_wakeup_status_set(uint8_t status);
uint8_t cubtek_faw_did_ds_ready_to_sleep_status_get();
void cubtek_faw_did_ds_ready_to_sleep_status_set(uint8_t status);

uint8_t cubtek_faw_did_ds_can_status_get();
void cubtek_faw_did_ds_can_status_set(uint8_t status);

void cubtek_did_can_config_handler(void);
void check_radar_alignment_result();
progress_bar_t is_enable_RID_0201_progress_bar(void);

ad_en_status is_enable_auto_detect_by_cus(void);
void auto_detect_en_by_cus_setting_update();

void target_list_trasmit_enable(void);
void target_list_trasmit_disable(void);
void set_target_list_tx_header_only(uint8_t op);
#endif

#endif /* CAN_CUBTEK_H_ */
