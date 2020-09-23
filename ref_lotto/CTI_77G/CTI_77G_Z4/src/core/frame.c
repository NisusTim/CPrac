/*
 * frame.c
 *
 *  Created on: 2017/9/21
 *      Author: erichu
 */
#include "sys_shared.h"
#include "can_cubtek.h"
#include "monitor_task.h"
#include "radar_output_controller.h"
#include "customer.h"
#include "coefs.h"
#include "helios.h"
#include "App_Dcm.h"
#include "cubtek_monitor_handler.h"

static void frame_pars_tester(char**,int);
static void frame_tester(char**,int);
static void frame_targets_show(target_group_p);
static void frame_measurements_mode_flags_set(void);
static void frame_measurements_init(void);
static void frame_pars_dump(void);
static void frame_rf_done(target_group_p);
void coefs_pars_init(void);

#define DEFAULT_FRAME_FLAGS		(FRAME_FLAG_TRACK_ENABLED + \
		FRAME_FLAG_HIST_THLD_PEAK + FRAME_FLAG_LR_SP_VELO_EXPAND + \
		FRAME_FLAG_LR_VELO_EXPAND + FRAME_FLAG_SR_VELO_EXPAND)

#define DEFAULT_BLIND_RANGE				1.0f
#define DEFAULT_NEAR_RANGE				43		// in meters
#define DEFAULT_LONG_RANGE_START		2		// in meters
#define DEFAULT_LONG_RANGE_END			180		// in meters
#define	DEFAULT_NEAR_CTX				SPT_CONTEXT_FRAME_T1
#define DEFAULT_LONG_CTX				SPT_CONTEXT_FRAME_2TI

#define DEFAULT_GATE_SR_V				10
#define DEFAULT_GATE_SR_X				15
#define DEFAULT_GATE_SR_Y				15

#define DEFAULT_GATE_LR_V				10
#define DEFAULT_GATE_LR_X				20
#define DEFAULT_GATE_LR_Y				20

typedef struct {
	uint32_t		time;
	uint32_t		countdown;
	timer_p			timer;
	spt_context_p	ctx_long;
	spt_context_p	ctx_near;
	event_proc_p 	done_cb;
	event_proc_p	new_cb;
	uint16_t		number;
	uint8_t			state;
	uint8_t			tggs_buff_tgl;	// tggs_buff toggle for extension
} frame_handle_t, *frame_handle_p;

typedef struct {
	pars_header_t	hdr;
	frame_info_t	info;
}frame_parameters_t, *frame_parameters_p;

frame_parameters_t __attribute__((section(".frampars"))) frame_parameters;

const frame_parameters_t fpars_default = {
		.hdr = {
			.base = (uint32_t)&frame_parameters,
			.version = 0x0201,
			.size = sizeof(frame_parameters_t),
			.id=FRAME_PARS_ID,
			.chksum = 0,
			.mask = 0
		},
		.info = {
			.on = {1, 1},
			.rate = 16,
			.flags = DEFAULT_FRAME_FLAGS,
			.aoa_sft = {0.0f,0.0f},
			.aoa_coefs = {0,0},
			.aoa_start = {-45.0, -12.0},
			.aoa_end = {45.0, 12.0},
			.rng_near = {1.0, 43},
			.rng_long = {2.0, 180, 0.0},
			.tcnts = {50, 100},
			.thld_bins = {16, 8},
			.thld_long = {330, 300, 210, 180, 180, 150},
			.thld_near = {390, 300, 300, 270, 240, 210},
			.ctxs = {DEFAULT_NEAR_CTX, DEFAULT_LONG_CTX},
			.multi_chirp = {9, 6},
			.mals = 160, .mcnt = 0,
			.haoa = {0, 0, 0, 0},
			.asso_x = {DEFAULT_GATE_SR_X,DEFAULT_GATE_LR_X},
			.asso_y = {DEFAULT_GATE_SR_Y,DEFAULT_GATE_LR_Y},
			.asso_v = {DEFAULT_GATE_SR_V,DEFAULT_GATE_LR_V},
            .hsft = 0
		}
};

static frame_proc_t frame_proc = {
	frame_play,
	frame_pause
};

frame_data_t 	__attribute__((section(".frame_data"))) frame_data;
static event_proc_p rf_cbs[FRAME_CTXS_COUNT] = {NULL,NULL};
static uint16_t	max_frame_time = 100; // ms

static frame_handle_t frame_handler={0}, *frame = &frame_handler;
static frame_info_p fpars = &frame_parameters.info;
static frame_data_p fdata = &frame_data;


#define JSON_FRAME_INFO_AOA_SFT 	"\t\t\"aoa_sft\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f]},\n"
#define JSON_FRAME_INFO_AOA_COEFS 	"\t\t\"aoa_coefs\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f]},\n"
#define JSON_FRAME_INFO_AOA_START 	"\t\t\"aoa_start\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f]},\n"
#define JSON_FRAME_INFO_AOA_END 	"\t\t\"aoa_end\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f]},\n"
#define JSON_FRAME_INFO_RNG_NEAR 	"\t\t\"rng_near\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f]},\n"
#define JSON_FRAME_INFO_RNG_LONG 	"\t\t\"rng_long\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f]},\n"
#define JSON_FRAME_INFO_HSFT         "\t\t\"hsft\":{\"t\":\"f32\",\"o\":%d,\"v\":%.2f},\n"
#define JSON_FRAME_INFO_THLD_BINS	"\t\t\"thld_bins\":{\"t\":\"u8\",\"o\":%d,\"v\":[%u,%u]},\n"
#define JSON_FRAME_INFO_THLD_LONG 	"\t\t\"thld_long\":{\"t\":\"i16\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d]},\n"
#define JSON_FRAME_INFO_THLD_NEAR 	"\t\t\"thld_near\":{\"t\":\"i16\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d]},\n"
#define JSON_FRAME_INFO_TCNTS 		"\t\t\"tcnts\":{\"t\":\"u16\",\"o\":%d,\"v\":[%u,%u]},\n"
#define JSON_FRAME_INFO_MULTI_CHIRP "\t\t\"multi_chirp\":{\"t\":\"i16\",\"o\":%d,\"v\":[%d,%d]},\n"
#define JSON_FRAME_INFO_ON 			"\t\t\"on\":{\"t\":\"u8\",\"o\":%d,\"v\":[%u,%u]},\n"
#define JSON_FRAME_INFO_CTXS 		"\t\t\"ctxs\":{\"t\":\"u8\",\"o\":%d,\"v\":[%u,%u]},\n"
#define JSON_FRAME_INFO_RATE 		"\t\t\"rate\":{\"t\":\"u16\",\"o\":%d,\"v\":%u},\n"
#define JSON_FRAME_INFO_FLAGS 		"\t\t\"flags\":{\"t\":\"u16\",\"o\":%d,\"v\":%u},\n"
#define JSON_FRAME_INFO_MALS 		"\t\t\"mals\":{\"t\":\"u16\",\"o\":%d,\"v\":%u},\n"
#define JSON_FRAME_INFO_MCNT 		"\t\t\"mcnt\":{\"t\":\"u16\",\"o\":%d,\"v\":%u},\n"
#define JSON_FRAME_INFO_HAOA 		"\t\t\"haoa\":{\"t\":\"u16\",\"o\":%d,\"v\":[%d,%d,%d,%d]},\n"
#define JSON_FRAME_INFO_ASSO_X 		"\t\t\"asso_x\":{\"t\":\"i16\",\"o\":%d,\"v\":[%d,%d]},\n"
#define JSON_FRAME_INFO_ASSO_Y 		"\t\t\"asso_y\":{\"t\":\"i16\",\"o\":%d,\"v\":[%d,%d]},\n"
#define JSON_FRAME_INFO_ASSO_V 		"\t\t\"asso_v\":{\"t\":\"i16\",\"o\":%d,\"v\":[%d,%d]}\n"

static int frame_info_in_jsons(char* ws)
{
	int cnt = 0;
	if(ws){
		cnt = sprintf(ws,"{\n");
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_ID, (char)(FRAME_PARS_ID>>24),(char)(FRAME_PARS_ID>>16),(char)(FRAME_PARS_ID>>8),(char)(FRAME_PARS_ID));
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_VERSION, frame_parameters.hdr.version);
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_SIZE, frame_parameters.hdr.size - sizeof(pars_header_t));

		cnt += sprintf(ws+cnt,"\t\"info\":{\n");
		cnt += sprintf(ws+cnt,JSON_FRAME_INFO_AOA_SFT,offsetof(frame_info_t, aoa_sft), fpars->aoa_sft[0], fpars->aoa_sft[1]);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_AOA_COEFS,offsetof(frame_info_t, aoa_coefs), fpars->aoa_coefs[0],fpars->aoa_coefs[1]);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_AOA_START,offsetof(frame_info_t, aoa_start), fpars->aoa_start[0],fpars->aoa_start[1]);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_AOA_END,offsetof(frame_info_t, aoa_end), fpars->aoa_end[0],fpars->aoa_end[1]);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_RNG_NEAR,offsetof(frame_info_t, rng_near), fpars->rng_near[0],fpars->rng_near[1]);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_RNG_LONG,offsetof(frame_info_t, rng_long), fpars->rng_long[0],fpars->rng_long[1],fpars->rng_long[2]);
        cnt += sprintf(ws+cnt, JSON_FRAME_INFO_HSFT,offsetof(frame_info_t, hsft), fpars->hsft);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_THLD_BINS,offsetof(frame_info_t, thld_bins), fpars->thld_bins[0],fpars->thld_bins[1]);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_THLD_LONG,offsetof(frame_info_t, thld_long), fpars->thld_long[0],fpars->thld_long[1],
				fpars->thld_long[2],fpars->thld_long[3],fpars->thld_long[4],fpars->thld_long[5]);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_THLD_NEAR,offsetof(frame_info_t, thld_near), fpars->thld_near[0],fpars->thld_near[1],
				fpars->thld_near[2],fpars->thld_near[3],fpars->thld_near[4],fpars->thld_near[5]);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_TCNTS,offsetof(frame_info_t, tcnts), fpars->tcnts[0],fpars->tcnts[1]);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_CTXS,offsetof(frame_info_t, ctxs), fpars->ctxs[0],fpars->ctxs[1]);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_ON,offsetof(frame_info_t, on), fpars->on[0],fpars->on[1]);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_MULTI_CHIRP,offsetof(frame_info_t, multi_chirp), fpars->multi_chirp[0],fpars->multi_chirp[1]);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_RATE,offsetof(frame_info_t, rate), fpars->rate);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_FLAGS,offsetof(frame_info_t, flags), fpars->flags);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_MALS,offsetof(frame_info_t, mals), fpars->mals);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_MCNT,offsetof(frame_info_t, mcnt), fpars->mcnt);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_HAOA,offsetof(frame_info_t, haoa), fpars->haoa[0],fpars->haoa[1],fpars->haoa[2],fpars->haoa[3]);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_ASSO_X,offsetof(frame_info_t, asso_x), fpars->asso_x[0],fpars->asso_x[1]);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_ASSO_Y,offsetof(frame_info_t, asso_y), fpars->asso_y[0],fpars->asso_y[1]);
		cnt += sprintf(ws+cnt, JSON_FRAME_INFO_ASSO_V,offsetof(frame_info_t, asso_v), fpars->asso_v[0],fpars->asso_v[1]);
		cnt += sprintf(ws+cnt, "\t}\n}\n");
	}
	return cnt;
}

void frame_init(void)
{
	memcpy(&frame_parameters, &fpars_default, sizeof(frame_parameters_t));

	pars_get((pars_ctx_p)&frame_parameters, frame_pars_dump, frame_info_in_jsons);

	frame->done_cb = NULL;
	frame->new_cb = NULL;
	frame->state = FRAME_ST_READY;
	memset(&frame_data, 0, sizeof(frame_data_t));
	fdata->tggs = fdata->tggs_buff[frame->tggs_buff_tgl];
	frame_measurements_init();
	fdata->mgrp.state = TRK_MEAS_ST_DONE;
	spt_init(fpars, (event_proc_p)frame_rf_done, fdata->tggs);
	frame_measurements_mode_flags_set();

	coefs_pars_init();
	helios_init(&frame_proc);
	console_command_reg("frame", frame_tester);
	console_command_reg("fpars", frame_pars_tester);
	console_command_reg("spt", frame_pars_tester);
	console_command_reg("play", frame_play_cmd);
	console_command_reg("pu", frame_pause);
	IPC_SEND_MSG_Z70(MSG_FRAME_DATA, (void*)fdata, 0);
}

#define MINI_FRAME_INTERVAL_TIME 		(20)	//~22ms
void frame_new(uint32_t fn)
{
	static uint16_t llt = 0, skipped=0, prev_state = FRAME_ST_READY;
	uint16_t elapsed = (STM_0.CNT.R>>16)-llt;

	llt = STM_0.CNT.R>>16;
	if(elapsed < MINI_FRAME_INTERVAL_TIME){
		//IPC_SEND_MSG_Z70(MSG_TARGETS_LIST, NULL);
		PRINTF("frm: interval %.2fms, skipped\n", elapsed*1.1f);
		return;
	}

	if(fn != 0xFFFFFFFF)
		frame->number = fn-1;

	frame->number++;

	if(frame->state != FRAME_ST_READY){
		fdata->counter = frame->number-1;
		PRINTF("frm:%d, state %d, skipped\n", fdata->counter, frame->state);
		IPC_SEND_MSG_Z70(MSG_FRAME_NEXT, (void*)(uint32_t)fdata->counter, 0);
		if(prev_state == frame->state){
			skipped++;
			if(skipped >= 3)
				frame->state = FRAME_ST_READY;
		}
		else
			skipped = 0;

		prev_state = frame->state;
		return;
	}
	skipped = 0;

	PRINTF("f%u@%.2fs\n",frame->number, ((float)time_get())/DEFAULT_TICKS_PER_SECOND);
	if(frame->new_cb)
		frame->new_cb((void*)(uint32_t)frame->number);
	frame->time = STM_0.CNT.R;

  // tggs buff switch
	frame->tggs_buff_tgl = (frame->tggs_buff_tgl + 1) % TGGS_BUFF_COUNT;
	spt_switch_tggs(fdata->tggs_buff[frame->tggs_buff_tgl]);

	if(fpars->on[FRAME_CTX_IDX_NEAR]) {
		frame->ctx_near = spt_meas_start(fpars->ctxs[FRAME_CTX_IDX_NEAR], (event_proc_p)near_meas_done);
		if(NULL==frame->ctx_near){
			frame_pause(NULL,0);
			return;
		}
		frame->state = FRAME_ST_NEAR;
	}

	else if(fpars->on[FRAME_CTX_IDX_LONG]){
		frame->ctx_long = spt_meas_start(fpars->ctxs[FRAME_CTX_IDX_LONG], (event_proc_p)long_meas_done);
		if(NULL==frame->ctx_long){
			frame_pause(NULL,0);
			return;
		}
		frame->state = FRAME_ST_LONG;
	}

	else {
		PRINTF("frm: neither near or long range frame context enabled\n");
		return;
	}

	prev_state = frame->state;
	if(frame->countdown) {
		frame->countdown--;
		if(frame->countdown == 0) {
			if(frame->timer) {
				if (!strcmp("frm", frame->timer->name))
					timer_unset(&frame->timer);
				frame->timer = NULL;
				fpars->rate = 0;
				IPC_SEND_MSG_Z70(MSG_FRAMERATE, (void*)(uint32_t)fpars->rate, 0);
			}
		}
	}
	ism330dlc_timer_enable();
	monitor_show();
}

void frame_pause(char** args,int count)
{
	if(frame->timer) {
		IPC_SEND_MSG_Z70(MSG_FRAMERATE, (void*)(uint32_t)0, 0);
		if (!strcmp("frm", frame->timer->name))
			timer_unset(&frame->timer);
		frame->timer = NULL;
	}
	ism330dlc_timer_disable();
}

void frame_resume(void)
{
	if(fpars->rate) {
		IPC_SEND_MSG_Z70(MSG_FRAMERATE, (void*)(uint32_t)fpars->rate, 0);

	    if(frame->timer)
	        if (!strcmp("frm", frame->timer->name))
	            timer_unset(&frame->timer);

		frame->timer = timer_set("frm",DEFAULT_TICKS_PER_SECOND/fpars->rate, -1, (event_proc_p)frame_new, (void*)0xFFFFFFFF);
	}
}

int frame_ctx_seq_get(void)
{
	if(frame->state == FRAME_ST_LONG && fpars->on[FRAME_CTX_IDX_NEAR] != 0)
		return 1;
	return 0;
}

/* nmeas: near measurements
 * lmeas: long measurements
 * rate: 0 no play, 1~32 rate to play, 0xFF=>apply original fpars rate value, others=>one frame test
 * done_cb: frame done event callback
 * new_cb: new frame event callback
 */
uint16_t frame_play(uint8_t nmeas, uint8_t lmeas, uint8_t rate, event_proc_p done_cb, event_proc_p new_cb)
{
	if(frame->timer)
		if (NULL != frame->timer && !strcmp("frm", frame->timer->name))
			timer_unset(&frame->timer);
		frame->timer = NULL;

	frame_measurements_init();

	if(nmeas != 0xFF)
		fpars->on[FRAME_CTX_IDX_NEAR] = nmeas;

	if(lmeas != 0xFF)
		fpars->on[FRAME_CTX_IDX_LONG] = lmeas;

	if(done_cb)
		frame->done_cb = done_cb;

	frame->new_cb = new_cb;

	if(rate == 0xFF)
		rate = fpars->rate;

	frame->state = FRAME_ST_READY;
	if(rate) {
		if(rate <= MAX_FRAME_RATE) {
			IPC_SEND_MSG_Z70(MSG_FRAMERATE, (void*)(uint32_t)rate, 0);
			frame->timer = timer_set("frm",DEFAULT_TICKS_PER_SECOND/rate, -1, (event_proc_p)frame_new, (void*)0xFFFFFFFF);
		}
		else
			frame->timer = timer_set("frm",DEFAULT_TICKS_PER_SECOND/rate, 1, (event_proc_p)frame_new, (void*)0xFFFFFFFF);
		max_frame_time = (1000/fpars->rate) + 10;
	}
	else
		max_frame_time = 100;

	PRINTF("max frame time : %ums\n", max_frame_time);

	return frame->number;
}

void frame_play_cmd(char** args,int count)
{
	uint8_t nm=0xFF, lm=0xFF, rate=0xFF;
	if(args != NULL){
		if(count > 1) {
			if(count > 2) {
				rate = (uint8_t)strtoul(args[2],NULL,10);
				if(!rate)
					rate = FRAME_RATE_ONCE;
			}

			if(!strcmp(args[1],"near")){
				nm=1;
				lm=0;
			}

			else if(!strcmp(args[1],"long")){
				nm=0;
				lm=1;
			}

			else {
				nm=1;
				lm=1;
			}
		}
		else if(!fpars->rate)
			rate = FRAME_RATE_ONCE;
	}

	frame_play(nm,lm,rate, NULL, NULL);
	//API_flash_init();
}

void frame_measurements_mode_flags_set(void)
{
	uint32_t mod, flags;
	spt_mode_flags_get(&mod,&flags);

	//PRINTF("frm: mod=%04lX,flags=%04lX\n", mod, flags);
	if(fpars->flags & FRAME_FLAG_TRACK_ENABLED)
		mod = MEAS_MOD_TRACK;

	if(fpars->flags & FRAME_FLAG_LR_VELO_EXPAND)
		flags |= MEAS_FLAG_LR_VELO_EXPAND;
	else
		flags &= ~MEAS_FLAG_LR_VELO_EXPAND;

	if(fpars->flags & FRAME_FLAG_LR_SP_VELO_EXPAND)
		flags |= MEAS_FLAG_LR_SP_VELO_EXPAND;
	else
		flags &= ~MEAS_FLAG_LR_SP_VELO_EXPAND;

	if(fpars->flags & FRAME_FLAG_SR_VELO_EXPAND)
		flags |= MEAS_FLAG_SR_VELO_EXPAND;
	else
		flags &= ~MEAS_FLAG_SR_VELO_EXPAND;

	if(fpars->flags & FRAME_FLAG_LOG_MEASUREMENTS)
		flags |= MEAS_FLAG_LOG_MEASUREMENTS;
	else
		flags &= ~MEAS_FLAG_LOG_MEASUREMENTS;

	//PRINTF("frm: mod=%04lX,flags=%04lX\n", mod, flags);
	spt_mode_flags_set(mod,flags);
}


static void frame_mals_count(void)
{
	static uint16_t mals = 0;

	if(fpars->mals == 0)
		return;

	int tcnt = fdata->tggs[FRAME_CTX_IDX_NEAR].tcnt+fdata->tggs[FRAME_CTX_IDX_LONG].tcnt;
	if(tcnt > fpars->mcnt){
		mals = 0;
		set_monitoring_result_by_id(MONITOR_ID_RADAR_BLOCKAGE, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED);
		return;
	}

	mals += 1;
	if(mals >= fpars->mals){
		mals = 0;
		set_monitoring_result_by_id(MONITOR_ID_RADAR_BLOCKAGE, MONITOR_RESULT_FAILED, MONITOR_RESULT_CODE_ERROR);
		PRINTF("frm: malfunction set!\n");
	}
}


void long_meas_done(target_group_p tgg)
{
	fdata->tggs = fdata->tggs_buff[frame->tggs_buff_tgl];
	fdata->time = (uint16_t)((STM_0.CNT.R-frame->time)*CLOCK_PERIOD_MS);
	PRINTF("f%u-1 %ums,[%d,%d]\n",frame->number, fdata->time, fdata->tggs[0].tcnt, fdata->tggs[1].tcnt);

#if defined(DEBUG_PROC_IN_TIME)
	if(fdata->time > max_frame_time){
		frame_pause(NULL, 0);
		event_dump(NULL,0);
		clear_SWT0_counter();
		ipc_dump_msg_que(NULL,1);
		clear_SWT0_counter();
		ipc_dump_msg_que(NULL,0);
		frame_resume();
	}
#endif

	if(fpars->on[FRAME_CTX_IDX_NEAR] == 0)
		fdata->tggs[FRAME_CTX_IDX_NEAR].tcnt = 0;

	fdata->counter = frame->number;
	frame_mals_count();

	if(frame->done_cb){
		frame->done_cb(tgg);
		tgg->state = TGG_ST_READY;
	}
	else if(MEAS_MOD_WR >= MEAS_MOD_MEASUREMENTS){
		IPC_SEND_MSG_Z71(MSG_TARGETS_LIST, (void*)fdata, 0);
	}

	frame->state = FRAME_ST_READY;

#if JSON_LIST_EN
    send_json_frame_info_by_isotp_format(fdata->time);
    send_json_veh_info_by_isotp_format();
    send_json_imu_info_by_isotp_format();
#endif
}

void near_meas_done(target_group_p tgg)
{
	if(fpars->on[FRAME_CTX_IDX_LONG] == 0){
		fdata->tggs[FRAME_CTX_IDX_LONG].tcnt = 0;
		fdata->time = (uint16_t)((STM_0.CNT.R-frame->time)*CLOCK_PERIOD_MS);
		PRINTF("f%u-0 %ums,[%d]\n",frame->number, fdata->time,tgg->tcnt);

		fdata->counter = frame->number;
		if(frame->done_cb){
			frame->done_cb(tgg);
			tgg->state = TGG_ST_READY;
		}
		else if(MEAS_MOD_WR >= MEAS_MOD_MEASUREMENTS){
			fdata->tggs = fdata->tggs_buff[frame->tggs_buff_tgl];
			IPC_SEND_MSG_Z71(MSG_TARGETS_LIST, (void*)fdata, 0);
		}

		frame->state = FRAME_ST_READY;
	}
	else if(frame->state == FRAME_ST_NEAR){ // in case frame skipped twice
		frame->ctx_long = spt_meas_start(fpars->ctxs[FRAME_CTX_IDX_LONG], (event_proc_p)long_meas_done);
		frame->state = FRAME_ST_LONG;
	}
}

uint32_t frame_rate(int32_t fr)
{
	static uint8_t is_inited = FALSE;
	if(fr != -1)
	{
		if(FALSE == is_inited || fr != fpars->rate)
		{
			fpars->rate = fr;
			IPC_SEND_MSG_Z70(MSG_FRAMERATE, (void*)(uint32_t)fpars->rate, 0);
			is_inited = TRUE;
		}
	}
	return fpars->rate;
}

uint32_t frame_number(int32_t fn)
{
	if(fn != -1)
		frame->number = fn;
	return frame->number;
}

uint16_t get_frame_counter(void)
{
	return fdata->counter;
}

static void frame_measurements_init(void)
{
	target_group_p tgg = fdata->tggs;
	target_p 	tg;
	int i = 0;
	while(i<FRAME_CTXS_COUNT){
		tgg->state = TGG_ST_READY;
		tgg->idx = i;
		tgg->runit = 1.0;
		tgg->vunit = 1.0;
		if(i == FRAME_CTX_IDX_NEAR){
			tgg->rcnt = RX_ACTIVES;
			tgg->vbins = CHIRPS_PER_FRAME*2; // 256 chirps
			tgg->rbins = SAMPLES_PER_CHIRP/4;// 128 bins
			tgg->done = (event_proc_p)near_meas_done;
			tg = tgg->targets;

			while(tg < tgg->targets+MAX_COUNT_OF_TARGET){
				tg->vangle = 180;
				tg++;
			}
		}
		else {
			tgg->rcnt = TOTAL_RX_ACTIVES;
			tgg->vbins = CHIRPS_PER_FRAME*2; // 256 chirps
			tgg->rbins = SAMPLES_PER_CHIRP/2;// 256 bins
			tgg->done = (event_proc_p)long_meas_done;
		}

		tgg++;
		i++;
	}

	memcpy(fdata->tggs_buff[1], fdata->tggs_buff[0], sizeof(fdata->tggs_buff[1]));

	fdata->tggs_buff[0][FRAME_CTX_IDX_NEAR].x = &fdata->tggs_buff[1][FRAME_CTX_IDX_NEAR];
	fdata->tggs_buff[1][FRAME_CTX_IDX_NEAR].x = &fdata->tggs_buff[0][FRAME_CTX_IDX_NEAR];
	fdata->tggs_buff[0][FRAME_CTX_IDX_LONG].x = &fdata->tggs_buff[1][FRAME_CTX_IDX_LONG];
	fdata->tggs_buff[1][FRAME_CTX_IDX_LONG].x = &fdata->tggs_buff[0][FRAME_CTX_IDX_LONG];
}

void frame_measurements_rf_cbs_reg(event_proc_p near_cb, event_proc_p long_cb)
{
	rf_cbs[FRAME_CTX_IDX_NEAR] = near_cb;
	rf_cbs[FRAME_CTX_IDX_LONG] = long_cb;
}

static void frame_rf_done(target_group_p tgg)
{
	if(tgg) {
		if(rf_cbs[tgg->idx])
			rf_cbs[tgg->idx](tgg);

	}
	else {
		PRINTF("frame meas rf done, but ctx idx error: %d\n", tgg->idx);
	}
}

static void frame_tester(char** args, int count)
{
	if(count > 1) {
		if(!strcmp(args[1], "countdown")){
			if(count > 2)
				frame->countdown = strtoul(args[2], NULL, 16);
			else
				frame->countdown = 0;
		}

		else if(!strcmp(args[1], "new")){
			uint32_t counter = -1;
			if(count > 2)
				counter = strtoul(args[2], NULL, 10);
			frame_new(counter);
		}

		else if(!strcmp(args[1], "tgg")){
			int i;
			if(count > 2) {
				if(!strcmp(args[2], "clr")){
					fdata->tggs[0].tcnt = 0;
					fdata->tggs[1].tcnt = 0;
				}
				else {
					count = strtoul(args[2], NULL, 10);
					if(count < FRAME_CTXS_COUNT)
						frame_targets_show(&fdata->tggs[count]);
				}
			}
			else {
				for(i=0; i < FRAME_CTXS_COUNT; i++)
					frame_targets_show(&fdata->tggs[i]);
			}
			PRINTF("#");
		}
	}
	else
		PRINTF("frm : st=%02X,countd=%ld\n", frame->state, frame->countdown);
}

static void frame_pars_dump(void)
{
	PRINTF("frame pars:\n");
	PRINTF("spt asft   :[%.2f,%.2f],Installation angular\n", fpars->aoa_sft[0],fpars->aoa_sft[1]);
	PRINTF("spt acoefs :[%.2f,%.2f],Linear factor of aoa adjustment\n", fpars->aoa_coefs[0],fpars->aoa_coefs[1]);
	PRINTF("spt astart :[%.2f,%.2f],Start of angular\n", fpars->aoa_start[0],fpars->aoa_start[1]);
	PRINTF("spt aend   :[%.2f,%.2f],End of angular\n", fpars->aoa_end[0],fpars->aoa_end[1]);
	PRINTF("spt rngs   :[blind=%.2f,near_end=%.2f,long_start=%.2f,end=%.2f,lsr=%.2f],Range boundary\n", fpars->rng_near[0],
			fpars->rng_near[1], fpars->rng_long[0], fpars->rng_long[1],fpars->rng_long[2]);
    PRINTF("spt hsft   :[%.2f], shift of vertical phase\n", fpars->hsft);
    PRINTF("           :[%.2f], shift of vertical angle\n", frame_get_hsft_in_angle());
	PRINTF("spt ctx    :[%d,%d],Measuresments CTX number\n",fpars->ctxs[FRAME_CTX_IDX_NEAR], fpars->ctxs[FRAME_CTX_IDX_LONG]);
	PRINTF("spt thld_bins :[%d,%d],range bins per threshold\n",fpars->thld_bins[FRAME_CTX_IDX_NEAR], fpars->thld_bins[FRAME_CTX_IDX_LONG]);
	PRINTF("spt thld_long :[%.1f,%.1f,%.1f,%.1f,%.1f,%.1f],thld(db) for LR, stepped in thld_bins\n", fpars->thld_long[0]*0.1f,
			fpars->thld_long[1]*0.1f,fpars->thld_long[2]*0.1f, fpars->thld_long[3]*0.1f,fpars->thld_long[4]*0.1f, fpars->thld_long[5]*0.1f);
	PRINTF("spt thld_near :[%.1f,%.1f,%.1f,%.1f,%.1f,%.1f],thld(db) for SR, stepped in thld_bins\n", fpars->thld_near[0]*0.1f,
			fpars->thld_near[1]*0.1f,fpars->thld_near[2]*0.1f, fpars->thld_near[3]*0.1f,fpars->thld_near[4]*0.1f, fpars->thld_near[5]*0.1f);
	PRINTF("spt tcnt   :[%d,%d],Max count of target to accept\n", fpars->tcnts[FRAME_CTX_IDX_NEAR], fpars->tcnts[FRAME_CTX_IDX_LONG]);
	PRINTF("spt mchpt  :[%dus,%dus],Additional chirp time on odd frame\n", fpars->multi_chirp[FRAME_CTX_IDX_NEAR], fpars->multi_chirp[FRAME_CTX_IDX_LONG]);
	PRINTF("spt haoa   :[%d times,spd<=%dm/s,%dm<range<%dm]\n", fpars->haoa[0], fpars->haoa[1], fpars->haoa[2], fpars->haoa[3]);
	PRINTF("spt asso_x :[%.1f,%.1f],Asso gate X\n", 0.1f*fpars->asso_x[0],0.1f*fpars->asso_x[1]);
	PRINTF("spt asso_y :[%.1f,%.1f],Asso gate Y\n", 0.1f*fpars->asso_y[0],0.1f*fpars->asso_y[1]);
	PRINTF("spt asso_v :[%.1f,%.1f],Asso gate V\n", 0.1f*fpars->asso_v[0],0.1f*fpars->asso_v[1]);

	PRINTF("fpars mals :[frames=%d,targets=%d],Alert malfunction if target count < [targets] in [frames]\n", fpars->mals, fpars->mcnt);

	PRINTF("fpars on   :[%d,%d]\n", fpars->on[0], fpars->on[1]);
	PRINTF("fpars rate :%d\n", fpars->rate);
	PRINTF("fpars flags:%04X,b7:track,b6:log,b5:thld in peak(1)/zero(0),b3:standing lsr,b1:LR velox3,b0:SR velox2\n",fpars->flags);
}

static void frame_pars_tester(char** args, int count)
{
	if (count > 2) {
		if(!strcmp(args[1], "on")){
			fpars->on[0] = strtoul(args[2], NULL, 10);
			if(count > 3)
				fpars->on[1] = strtoul(args[3], NULL, 10);
			pars_set((pars_ctx_p)&frame_parameters);
		}

		else if(!strcmp(args[1], "rate")) {
			uint8_t rate = strtoul(args[2], NULL, 10);
			if(rate <= MAX_FRAME_RATE) {
				fpars->rate = rate;
				pars_set((pars_ctx_p)&frame_parameters);
				IPC_SEND_MSG_Z70(MSG_FRAMERATE, (void*)(uint32_t)fpars->rate, 0);
				if(fpars->rate)
					frame_play(-1,-1,rate, NULL, NULL);
			}
		}

		else if(!strcmp(args[1], "flags")){
			fpars->flags = strtoul(args[2], NULL, 16);
			pars_set((pars_ctx_p)&frame_parameters);
			frame_measurements_mode_flags_set();
		}

		else if(!strcmp(args[1], "asft")){
			float aoa = strtof(args[2], NULL);
			if(aoa <= 90.0 && aoa >= -90.0)
				fpars->aoa_sft[0] = aoa;

			if(count > 3){
				aoa = strtof(args[3], NULL);
				if(aoa <= 90.0 && aoa >= -90.0)
					fpars->aoa_sft[1] = aoa;
			}

			spt_aoas_misc_set();
			pars_set((pars_ctx_p)&frame_parameters);
		}

		else if(!strcmp(args[1], "acoefs")) {
			fpars->aoa_coefs[0] = strtof(args[2], NULL);
			if(count > 3)
				fpars->aoa_coefs[1] = strtof(args[3], NULL);
			pars_set((pars_ctx_p)&frame_parameters);
		}

		else if(!strcmp(args[1], "astart")){
			float aoa = strtof(args[2], NULL);
			if(aoa <= 180.0 && aoa >= -180.0)
				fpars->aoa_start[0] = aoa;

			if(count > 3){
				aoa = strtof(args[3], NULL);
				if(aoa <= 180.0 && aoa >= -180.0)
					fpars->aoa_start[1] = aoa;
			}

			spt_aoas_misc_set();
			pars_set((pars_ctx_p)&frame_parameters);
		}

		else if(!strcmp(args[1], "aend")){
			float aoa = strtof(args[2], NULL);
			if(aoa <= 180.0 && aoa >= -180.0)
				fpars->aoa_end[0] = aoa;

			if(count > 3){
				aoa = strtof(args[3], NULL);
				if(aoa <= 180.0 && aoa >= -180.0)
					fpars->aoa_end[1] = aoa;
			}

			spt_aoas_misc_set();
			pars_set((pars_ctx_p)&frame_parameters);
		}

        else if(!strcmp(args[1], "hsft")){
            float hsft = strtof(args[2], NULL);
            if(hsft <= 180.0 && hsft >= -180.0)
                fpars->hsft = hsft;

            pars_set((pars_ctx_p)&frame_parameters);
        }

		else if(!strcmp(args[1], "rngs")){
			float rng = strtof(args[2], NULL);
			if (rng <= 64)
				fpars->rng_near[0] = rng;
			if(count > 3) {
				rng = strtof(args[3], NULL);
				if(rng <= 256)
					fpars->rng_near[1] = rng;

				if(count > 4) {
					rng = strtof(args[4], NULL);
					if(rng <= 256)
						fpars->rng_long[0] = rng;
					if(count > 5) {
						rng = strtof(args[5], NULL);
						if(rng <= 400)
							fpars->rng_long[1] = rng;
						/*if(count > 6) {
							rng = strtof(args[6], NULL);
							if(rng <= 64)
								fpars->rng_long[2] = rng;
						}*/
					}
				}
			}
			pars_set((pars_ctx_p)&frame_parameters);
		}

		else if(!strcmp(args[1], "ctx")) {
			uint8_t ctx = strtoul(args[2], NULL, 10);
			if(ctx < SPT_CONTEXT_FRAME_2TI)
				fpars->ctxs[FRAME_CTX_IDX_NEAR] = ctx;

			if(count > 3) {
				ctx = strtoul(args[3], NULL, 10);
				if(ctx < SPT_CONTEXT_CLIPPING)
					fpars->ctxs[FRAME_CTX_IDX_LONG] = ctx;
			}
			pars_set((pars_ctx_p)&frame_parameters);
		}

		else if(!strcmp(args[1], "thld_bins")) {
			uint16_t bins = strtoul(args[2], NULL, 10);
			if ((bins & 0x07) || bins > 64){
				PRINTF("spt: thld_bins(%d) invalid, must be multiple of 8 and less than 64\n", bins);
				return;
			}

			fpars->thld_bins[FRAME_CTX_IDX_NEAR] = bins;
			spt_thlds_set(FRAME_CTX_IDX_NEAR);

			if(count > 3) {
				bins = strtoul(args[3], NULL, 10);
				if ((bins & 0x07) || bins > 64){
					PRINTF("spt: thld_bins(%d) invalid, must be multiple of 8 and less than 64\n", bins);
					return;
				}

				fpars->thld_bins[FRAME_CTX_IDX_LONG] = bins;
				spt_thlds_set(FRAME_CTX_IDX_LONG);
			}

			pars_set((pars_ctx_p)&frame_parameters);
		}

		else if(!strcmp(args[1], "thld_long")) {
			fpars->thld_long[0] = (int16_t)(strtof(args[2], NULL)*10);
			if(count > 3) {
				fpars->thld_long[1] = (int16_t)(strtof(args[3], NULL)*10);
				if(count > 4) {
					fpars->thld_long[2] = (int16_t)(strtof(args[4], NULL)*10);
					if(count > 5) {
						fpars->thld_long[3] = (int16_t)(strtof(args[5], NULL)*10);
						if(count > 6) {
							fpars->thld_long[4] = (int16_t)(strtof(args[6], NULL)*10);
							if(count > 7) {
								fpars->thld_long[5] = (int16_t)(strtof(args[7], NULL)*10);
							}
						}
					}
				}
			}
			spt_thlds_set(FRAME_CTX_IDX_LONG);
			pars_set((pars_ctx_p)&frame_parameters);
		}

		else if(!strcmp(args[1], "thld_near")) {
			fpars->thld_near[0] = (int16_t)(strtof(args[2], NULL)*10);
			if(count > 3) {
				fpars->thld_near[1] = (int16_t)(strtof(args[3], NULL)*10);
				if(count > 4) {
					fpars->thld_near[2] = (int16_t)(strtof(args[4], NULL)*10);
					if(count > 5) {
						fpars->thld_near[3] = (int16_t)(strtof(args[5], NULL)*10);
						if(count > 6) {
							fpars->thld_near[4] = (int16_t)(strtof(args[6], NULL)*10);
							if(count > 7) {
								fpars->thld_near[5] = (int16_t)(strtof(args[7], NULL)*10);
							}
						}
					}
				}
			}
			spt_thlds_set(FRAME_CTX_IDX_NEAR);
			pars_set((pars_ctx_p)&frame_parameters);
		}

		else if(!strcmp(args[1], "tcnt")) {
			uint16_t tcnt = strtoul(args[2], NULL, 10);
			if(tcnt <= MAX_COUNT_OF_TARGET)
				fpars->tcnts[FRAME_CTX_IDX_NEAR] = tcnt;

			if(count > 3){
				tcnt = strtoul(args[3], NULL, 10);
				if(tcnt <= MAX_COUNT_OF_TARGET)
					fpars->tcnts[FRAME_CTX_IDX_LONG] = tcnt;
			}

			pars_set((pars_ctx_p)&frame_parameters);
		}

		else if(!strcmp(args[1],"mchpt")){
			int16_t ct = strtol(args[2], NULL, 10);
			if(ct < 40)
				fpars->multi_chirp[FRAME_CTX_IDX_NEAR] = ct;
			if(count > 3){
				ct = strtol(args[3], NULL, 10);
				if(ct < 40)
					fpars->multi_chirp[FRAME_CTX_IDX_LONG] = ct;
			}

			spt_mchp_velo_thld_set();
			pars_set((pars_ctx_p)&frame_parameters);
		}

		else if(!strcmp(args[1],"haoa")){
			fpars->haoa[0] = (uint16_t)strtoul(args[2], NULL, 10);
			if(count > 3) {
				fpars->haoa[1] = (uint16_t)strtof(args[3],NULL);
				if(count > 4) {
					fpars->haoa[2] = (uint16_t)strtoul(args[4], NULL, 10);
					if(count > 5) {
						fpars->haoa[3] = (uint16_t)strtoul(args[5], NULL, 10);
					}
				}
			}
			pars_set((pars_ctx_p)&frame_parameters);
		}

		else if(!strcmp(args[1], "asso_x")) {
			fpars->asso_x[FRAME_CTX_IDX_NEAR] = (int16_t)(strtof(args[2], NULL)*10);
			if(count > 3)
				fpars->asso_x[FRAME_CTX_IDX_LONG] = (int16_t)(strtof(args[3], NULL)*10);
			pars_set((pars_ctx_p)&frame_parameters);
		}

		else if(!strcmp(args[1], "asso_y")) {
			fpars->asso_y[FRAME_CTX_IDX_NEAR] = (int16_t)(strtof(args[2], NULL)*10);
			if(count > 3)
				fpars->asso_y[FRAME_CTX_IDX_LONG] = (int16_t)(strtof(args[3], NULL)*10);
			pars_set((pars_ctx_p)&frame_parameters);
		}

		else if(!strcmp(args[1], "asso_v")) {
			fpars->asso_v[FRAME_CTX_IDX_NEAR] = (int16_t)(strtof(args[2], NULL)*10);
			if(count > 3)
				fpars->asso_v[FRAME_CTX_IDX_LONG] = (int16_t)(strtof(args[3], NULL)*10);
			pars_set((pars_ctx_p)&frame_parameters);
		}

		else if(!strcmp(args[1], "mals")) {
			uint16_t mals = strtoul(args[2], NULL, 10);
			if(mals >= 0)
				fpars->mals = mals;

			if(count > 3) {
				mals = strtoul(args[3], NULL, 10);
				if(mals <= 20)
					fpars->mcnt = mals;
			}

			pars_set((pars_ctx_p)&frame_parameters);
		}
	}
	frame_pars_dump();
}

void frame_rng_aoa_set(float aoa, float blind, float near_rng, float long_rng, int save)
{
	int set = 0;

	if((aoa < 90.0 && aoa > -90.0) && ((fpars->aoa_sft[0] != aoa) || (fpars->aoa_sft[1] != aoa))) {
		fpars->aoa_sft[0] = aoa;
		fpars->aoa_sft[1] = aoa;
		spt_aoas_misc_set();
		set = 1;
	}

	if((blind > 0) && (fpars->rng_near[0] != blind)) {
		fpars->rng_near[0] = blind;
		set = 1;
	}

	if((near_rng > 0) && ((fpars->rng_near[1] != near_rng) || (fpars->rng_long[0] != near_rng))) {
		fpars->rng_near[1] = near_rng;
		fpars->rng_long[0] = near_rng;
		set = 1;
	}

	if((long_rng > 0) && (fpars->rng_long[1] != long_rng)) {
		fpars->rng_long[1] = long_rng;
		set = 1;
	}

	if(save && set)
		pars_set((pars_ctx_p)&frame_parameters);
}

void frame_rng_set(float blind, float near_end, float long_start, float long_end, int save)
{
	int set = 0;


	if((blind > 0) && (fpars->rng_near[0] != blind)) {
		fpars->rng_near[0] = blind;
		set = 1;
	}

	if((near_end > 0) && (fpars->rng_near[1] != near_end)) {
		fpars->rng_near[1] = near_end;
		set = 1;
	}

	if((long_start > 0) && (fpars->rng_long[0] != long_start)) {
		fpars->rng_long[0] = long_start;
		set = 1;
	}

	if((long_end > 0) && (fpars->rng_long[1] != long_end)) {
		fpars->rng_long[1] = long_end;
		set = 1;
	}

	if(save && set)
		pars_set((pars_ctx_p)&frame_parameters);
}

int frame_tgg_in_jsons(target_group_p tgg, char* ws)
{
	int cnt = 0;

	if(tgg == NULL || tgg->tcnt <= 0)
		return 0;

	target_p tg = tgg->targets;

	cnt += sprintf(ws+cnt, "{\"i\":%d,\"n\":%d,\"t\":[", tgg->idx, tgg->tcnt);
	while(tg < (tgg->targets+tgg->tcnt)){
		cnt += sprintf(ws+cnt, "\n{\"r\":%d,\"v\":%d,\"a\":%.5f,\"m\":%.1f,\"h\":%d,",
				tg->range, tg->velocity, DEGREE_OF_RADIAN(aoaidx_asin(tg->aoaidx)), SPT_LOG2DB(tg->mag_log2), tg->vangle);
		cnt += sprintf(ws+cnt, "\"c\":[[%ld,%ld],[%ld,%ld],[%ld,%ld],[%ld,%ld]",
				tg->cmplx[0].re,tg->cmplx[0].im,tg->cmplx[1].re,tg->cmplx[1].im,
				tg->cmplx[2].re,tg->cmplx[2].im,tg->cmplx[3].re,tg->cmplx[3].im);
		if(tgg->rcnt == TOTAL_RX_ACTIVES){
			cnt += sprintf(ws+cnt, ",[%ld,%ld],[%ld,%ld],[%ld,%ld],[%ld,%ld]",
					tg->cmplx[4].re,tg->cmplx[4].im,tg->cmplx[5].re,tg->cmplx[5].im,
					tg->cmplx[6].re,tg->cmplx[6].im,tg->cmplx[7].re,tg->cmplx[7].im);
		}
		cnt += sprintf(ws+cnt,"]},");
		tg++;
	}
	cnt--;
	cnt += sprintf(ws+cnt,"\n]}");
	return cnt;
}


int frame_tggs_in_jsons(char* ws)
{
	target_group_p tgg = fdata->tggs, end=fdata->tggs+FRAME_CTXS_COUNT;
	int cnt = 0;

	cnt = sprintf(ws,"[\n");
	while(tgg < end) {
		if(tgg->tcnt > 0){
			cnt += frame_tgg_in_jsons(tgg,ws+cnt);
			cnt += sprintf(ws+cnt, ",\n");
		}
		tgg++;
	}
	if(cnt > 10){
		cnt -= 2;
	}
	ws[cnt++] = ']';
	ws[cnt++] = '\n';
	return cnt;
}

void frame_targets_show(target_group_p tgg)
{
	if (tgg == NULL)
		return;

	int id = 0;
	target_p tg = tgg->targets;
	PRINTF("tggs[%d]:tcnt=%d,st=%d,rcnt=%d\n", tgg->idx, tgg->tcnt, tgg->state, tgg->rcnt);

	while(id < tgg->tcnt) {
		PRINTF("tg(%d):r(%d),v(%d),a(%.4f),h(%d),m(%.1f),p(%04X)", id,tg->range,tg->velocity,DEGREE_OF_RADIAN(aoaidx_asin(tg->aoaidx)),tg->vangle,SPT_LOG2DB(tg->mag_log2),tg->pos);
		PRINTF(",(%ld+%ldj),(%ld+%ldj),(%ld+%ldj),(%ld+%ldj),",
			tg->cmplx[0].re,tg->cmplx[0].im,
			tg->cmplx[1].re, tg->cmplx[1].im,
			tg->cmplx[2].re,tg->cmplx[2].im,
			tg->cmplx[3].re, tg->cmplx[3].im);

		if(tgg->rcnt == 8) {
			PRINTF(",(%ld+%ldj),(%ld+%ldj),(%ld+%ldj),(%ld+%ldj)\n",
				tg->cmplx[4].re,tg->cmplx[4].im,
				tg->cmplx[5].re, tg->cmplx[5].im,
				tg->cmplx[6].re,tg->cmplx[6].im,
				tg->cmplx[7].re, tg->cmplx[7].im);
		}
		else
			PRINTF("\n");

		id++;
		tg++;
	}
	PRINTF("\n");
}

RADAR_MODE_E get_frame_radar_mode(void)
{
	return fdata->rmode;
}

void set_frame_radar_mode(RADAR_MODE_E mode)
{
	if(RADAR_MODE_INVALID > mode)
		fdata->rmode = mode;
}

void frame_set_tracking_control(TRK_CTRL_E ctrl)
{
	fdata->trkctrl = ctrl;
}


/***********************************************************************************************
 * frame measurement data get for RMTP
 ***********************************************************************************************/
typedef enum {
    MEAS_GET_FOR_NORMAL =0,
	MEAS_GET_FOR_CALIB = 1,
	MEAS_GET_FOR_CALIB_IRON = 2
} MEAS_GET_TYPE_E;

typedef struct rng_velo {
	float 			range;
	event_proc_p 	cb;
	uint8_t 		ctx_idx;
	MEAS_GET_TYPE_E meas_get_type;
}measurement_info_t;
static measurement_info_t measurement_info = {0};

static void _get_measurement_filtered_by_rng(void *d)
{
    target_group_p tgg=d;
    target_p tg = NULL, temp = NULL;
	uint8_t id = 0;
    
    float f_bin_index;
    uint16_t bin_index;
    
    f_bin_index=measurement_info.range/tgg->runit;
    bin_index=(int16_t)f_bin_index;
    if((f_bin_index-bin_index)>=(tgg->runit/2)){
        bin_index++;
    }

	//PRINTF("tgg@%p[%d]:tcnt=%d,st=%d,rcnt=%d\n", tgg, tgg->idx, tgg->tcnt, tgg->state,tgg->rcnt);
    temp = tgg->targets;
    while(id < tgg->tcnt)
    {
        PRINTF("e%d,a:%.5f,v:%.2f,r:%.2f,h:%d,m:%.2f\n", id, DEGREE_OF_RADIAN(aoaidx_asin(temp->aoaidx)), temp->velocity*tgg->vunit, temp->range*tgg->runit, temp->vangle, SPT_LOG2DB(temp->mag_log2));
        if((temp->range<= bin_index+1)&&(temp->range>= bin_index-1))
		{
			if((measurement_info.meas_get_type==MEAS_GET_FOR_NORMAL)||((measurement_info.meas_get_type!=MEAS_GET_FOR_NORMAL)&&(temp->velocity==0)))
			{    
			    if(tg == NULL || temp->mag_log2 > tg->mag_log2)
                {
                    tg = temp;
                }
            }
        }
        id++;
        temp++;
    }

    if(tg != NULL)
	{	//Measurement found
		if(measurement_info.meas_get_type!=MEAS_GET_FOR_CALIB_IRON){
		    tg->range = (int16_t)(tg->range * (tgg->runit * 100.0));			//Multiple 100 for precision, unit: meter
		    tg->velocity = (int16_t)(tg->velocity * (tgg->vunit * 100.0));		//Multiple 100 for precision, unit: meter/sec
		}
	}
	else
	{
	    //Measurement not found;
		tg = tgg->targets;
		tg->range = 0;
		tg->aoaidx = AOAIDX_INVALID;
		tg->mag_log2 = 0;
		tg->vangle = 0;
		tg->velocity = 0;
		tg->pos = 0;
	}    

	measurement_info.cb(tg);

	frame->done_cb = NULL;
	
}

uint8_t frame_measurements_get_by_rng_sub(FRAME_CTX_IDX_E idx, float rng, event_proc_p cb)
{
	measurement_info.range = rng;
	measurement_info.ctx_idx = idx;
	measurement_info.cb = cb;

	tef_all_HPF100();
	frame->done_cb = _get_measurement_filtered_by_rng;

	if(idx == FRAME_CTX_IDX_NEAR)
	{
        frame->ctx_near = spt_meas_start(fpars->ctxs[FRAME_CTX_IDX_NEAR], (event_proc_p)near_meas_done);
		frame->state = FRAME_ST_NEAR;
	}
	else if(idx == FRAME_CTX_IDX_LONG)
	{
        frame->ctx_long = spt_meas_start(fpars->ctxs[FRAME_CTX_IDX_LONG], (event_proc_p)long_meas_done);
		frame->state = FRAME_ST_LONG;
	}
	else
		PRINTF("meas: unknown idx(%d) to get doppler\n",idx);

	return MEAS_ST_READY;
}

uint8_t frame_measurements_get_by_rng(FRAME_CTX_IDX_E idx, float rng, event_proc_p cb)
{
    measurement_info.meas_get_type=MEAS_GET_FOR_NORMAL;
    return(frame_measurements_get_by_rng_sub(idx,rng,cb));
}


uint8_t frame_measurements_get_by_rng_for_calib(FRAME_CTX_IDX_E idx, float rng, event_proc_p cb)
{
    measurement_info.meas_get_type=MEAS_GET_FOR_CALIB;
    return(frame_measurements_get_by_rng_sub(idx,rng,cb));
}

uint8_t frame_measurements_get_by_rng_for_calib_iron(FRAME_CTX_IDX_E idx, float rng, event_proc_p cb)
{
    measurement_info.meas_get_type=MEAS_GET_FOR_CALIB_IRON;
    return(frame_measurements_get_by_rng_sub(idx,rng,cb));
}



float frame_get_acoefs(void)
{
	return fpars->aoa_coefs[0];
}

float frame_get_aoa_shift(uint8_t id)
{
    return (fpars->aoa_sft[id]);
}

void frame_set_aoa_shift(uint8_t id, float aoa_shift)
{
	fpars->aoa_sft[id] = aoa_shift;
	pars_set((pars_ctx_p)&frame_parameters);
    spt_aoas_misc_set();
}

float frame_get_asft_0(void)
{
    return fpars->aoa_sft[0];
}

float frame_get_hsft(void)
{
    return fpars->hsft;
}

float frame_get_hsft_in_angle(void)
{
  return DEGREE_OF_RADIAN(asinf(fpars->hsft / (2 * 1.989f * 180.0f)));
}

void frame_set_hsft(float hsft, int save){
    fpars->hsft = hsft;
    if(save ==1){
        pars_set((pars_ctx_p)&frame_parameters);
    }
}

float frame_get_rngs_long_start(void)
{
    return fpars->rng_long[0];
} 

void frame_set_rngs_long_start(float rngs_long_start, int save)
{
    fpars->rng_long[0]=rngs_long_start;
    if(save ==1){
        pars_set((pars_ctx_p)&frame_parameters);
    }
}

FRAME_STATE_E get_frame_state()
{
	return frame->state;
}

void frame_aoa_measument_mode(void)
{
    fpars->aoa_start[0]=-90.0f;
    fpars->aoa_start[1]=-90.0f;
    fpars->aoa_end[0]=90.0f;
    fpars->aoa_end[1]=90.0f;
    spt_aoas_misc_set();
}

void frame_set_asft(float asft)
{
	if (asft < 30000 ) {
	    fpars->aoa_sft[0] = asft;
	    fpars->aoa_sft[1] = asft;
		spt_aoas_misc_set();
		pars_set((pars_ctx_p)&frame_parameters);
	}
}

