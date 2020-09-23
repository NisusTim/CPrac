/*
 * final_proc.c
 *
 *  Created on: 2017/03/03
 *      Author: Wesley Liang
 */

#include "sys_shared.h"
#include "track_api.h"
#include "custom_math.h"
#include "alignment_main.h"

#if JSON_LIST_EN
#include "json_debug_info.h"
#endif

static tracking_api_st *trkapi = NULL;
static tracking_ctx_st *trkctx = NULL;
static const tracking_pars_t *trkpars = NULL;
static tracking_pars2_t *trkpars2 = NULL;
static const tracking_warn_t *trkwarn = NULL;
static const fcw_warn_t *fcwwarn = NULL;
static frame_data_t *fdata = NULL;

static uint16_t frame_num = 0;
uint16_t frame_lost_num = 0;
static int sg_frame_rate = 0;
//float calib_angle = 1000; //Remove by Wood, in order to fix unused declaration warning
static float yaw_rate = 0.0;
static uint8_t tracking_ready = 0;
static uint8_t yaw_rate_type = 0;
static uint8_t door_status = 0;
static uint8_t gear_status = 0;

void reset_system(void);
void tracking_warning_init(void *data);

static char* tracking_mode_get(uint8_t mode)
{
	switch (mode) {
		case TRACKING_MODE_FCW:
			return "FCW";
		case TRACKING_MODE_RCW:
			return "RCW";
		default:
			return "Unknown";
	}

	return "Unknown";
}

void get_yaw_rate_type(void* type)
{
	yaw_rate_type = (uint8_t)(uint32_t)type;
}

static void tracking_pars_get(void)
{
	trkpars = (const tracking_pars_t*)pars_ctx_get(TRACKING_PARS_ID);
	trkpars2 = (tracking_pars2_t*)pars_ctx_get(TRACKING_PARS2_ID);
	fcwwarn = (const fcw_warn_t*)pars_ctx_get(FCWWARN_PARS_ID);
	trkwarn = (const tracking_warn_t*)fcwwarn;
	PRINTF("trkp: pars(%p,%p,%p) inited\n",trkpars, trkpars2, fcwwarn);
}

void tracking_pars_init(void)
{
	pars_init_proc_reg(tracking_warning_init, NULL, "trkp");
}

void tracking_warning_init(void *data)
{
	tracking_pars_get();
	if (fdata && trkpars && trkpars2 && trkwarn) {
		trkapi = track_api_init(fdata, trkpars, trkpars2, trkwarn);
		if (trkapi->track_frame_init == NULL) {
    		PRINTF("ERR: tracking APIs are NULL: mode(%s)!\n", tracking_mode_get(trkpars->info.mode));
    		return;
    	}
		trkctx = &fdata->trkctx;
		tracking_ready = 1;
		PRINTF("Tracking is ready!\n");
	} else {
		if (!fdata) {
			PRINTF("ERR: fdata is NULL!\n");
		}
		if (!trkpars) {
			PRINTF("ERR: trkpars is NULL!\n");
		}
		if (!trkwarn) {
			PRINTF("ERR: trkwarn is NULL!\n");
		}
	}	
}

void tracking_frame_data_init(void *data)
{
	if (data == NULL) {
		PRINTF("ERR: frame data init failed!\n");
		return;
	}
	fdata = (frame_data_t *)data;
	trkctx = &fdata->trkctx;
}

void tracking_frame_rate_set(int rate)
{
    sg_frame_rate = rate;
	if (!trkapi || !trkpars || !trkwarn || !fdata) {
		PRINTF("ERR: tracking init failed!\n");
		return;
	}
    if (rate) {
    	trkapi->track_frame_rate_set(rate);
    }
}

int16_t vrs_get(float vunit)
{
	return CHIRPS_PER_FRAME;
}

void vehicle_status_fun(void *data)
{
	door_status = (uint8_t)(((uint32_t)data) & 0x01);
	gear_status = (uint8_t)(((uint32_t)data) & 0x02);
	gear_status = gear_status >> 1;
}

static uint16_t tracking_targets_get(void)
{
	uint16_t			tcnt;
	int           		index, count, status;
	float 			 	probability;
	int			     	ittc;
	int 				idx;
	float 				sin_value, cos_value;
	target_st        	output;
    tracking_group_t 	*tg;
    tracking_t       	*trk;
	measure_st 			*m = NULL;
	
	tg = &fdata->trkgrp;
	trk = tg->targets;
	count = trkapi->track_target_filtering();
	tcnt = 0;
	for (index = 0; ((index < count) && (index < trkpars->info.max_cnt)); index++) {
		status = trkapi->track_target_get(&output);
		if (status == 0) {
			break;
		}
		trk->rx = output.y;
		trk->ry = output.x * -1;
		trk->range = output.range;
		trk->angle= output.angle;
		trk->vx = output.vy;
		trk->vy = output.vx * -1;
		trk->ax = output.accy;
		trk->tracking_id = output.idx + 1;
		trk->dynamic_property = output.dyn_status;
		trk->status = output.updated;
		probability = ((float)output.measured / (float)(output.measured + output.missed));
		if (probability >= 0.99) {
			trk->probability = PROBABILITY_99;
		} else if (probability >= 0.75) {
			trk->probability = PROBABILITY_75;
		} else if (probability >= 0.50) {
			trk->probability = PROBABILITY_50;
		} else {
			trk->probability = PROBABILITY_25;
		}
		trk->vangle = (int16_t)output.vector_angle;		//output.rcs;	//output.vangle;
		trk->guardrail_cnt = output.guardrail_cnt;
		trk->cip = output.cip_warning;
		trk->cip_acc = output.cip_acc_flag;
		trk->cip_aeb = output.cip_aeb_flag;
		trk->rcs_type = output.object_type;
		trk->ittc = 0;
        if (output.vy == 0) {
        	trk->ittc = 0x00FF;
        } else {
        	ittc = -1 * (output.y / output.vy) * 10;
        	trk->ittc = ABS(ittc) > 250 ?  0xFA : ABS(ittc);
        	if (ittc >= 0) {
        		trk->ittc = 0x00FF & trk->ittc;
        	} else {
        		trk->ittc = 0x0100 | trk->ittc;
        	}
        }
		if ((trkpars->info.tracking_dbg == 1) && (trkpars->info.mode == TRACKING_MODE_FCW) && (status == 2)) {
			PRINTF("---> CIP(%d) x:%.2f y:%.2f vx:%.2f vy:%.2f w:%d\n", trk->tracking_id, output.x, output.y, output.vx, output.vy, trk->cip);
		}	
		trk++,
		tcnt++;
	}
	tg->tcnt = tcnt;
	tg->frame_num = frame_num;
	tg->ctrl = trkctx->tracking_ctrl;
	tg->status = trkctx->tracking_ctrl_status;
	tg->tunnel_flag = trkctx->tunnel_flag;
	tg->auto_calib_flag = (trkpars2->info.auto_calib[8] == 0) ? 0 : 1;
	tg->auto_calib_left_num = trkctx->auto_calib_left_num;
	tg->auto_calib_right_num = trkctx->auto_calib_right_num;
	tg->calib_angle = trkctx->calib_angle;
	if (trkpars->info.measurement_display == 1) {
		for (idx = 0; idx < trkctx->measurements_count; idx++) {
			m = &trkctx->measurements[idx];
			m->angle = m->angle - trkpars->info.aoa_shift;
	    	m->rad = m->angle * DEGREE_TO_RADIAN;
	    	sin_value = SIN(m->rad);
	    	cos_value = COS(m->rad) + 0.000001;
			m->x = sin_value * m->range;
	    	m->y = cos_value * m->range;
			m->vy = m->velocity / cos_value;

			trk->rx = m->y;
			trk->ry = m->x * -1;
			trk->range = m->range;
			trk->angle= m->angle;
			trk->vx = m->vy;
			trk->vy = 0;
			trk->ax = 0;
			trk->tracking_id = 0;
			trk->dynamic_property = MEASUREMENT;
			trk->status = 0;
			trk++;
	  	}
		tg->tcnt = trkctx->measurements_count + tcnt;
	}

	IPC_SEND_MSG_Z40(MSG_TARGETS_LIST, tg, 0);
	IPC_SEND_MSG_Z40(MSG_TARGETS_INFO, tg, 0);
#if JSON_LIST_EN
	IPC_SEND_MSG_Z40(MSG_WARN_MSG, tg, 0);
	IPC_SEND_MSG_Z40(MSG_JSON_TARGET_LIST, fdata, 0);
#endif
	return tcnt;
}

void tracking_frame_next(void *data)
{
	// frame initialization, null measurements
	tracking_group_t 	*tg;

	frame_num = fdata->counter;
	frame_lost_num++;
	if (trkpars->info.tracking_dbg) {
	    PRINTF("Tracking:Next(f:%d,l:%d,r:%d,y:%.2f,v:%.2f,g:%d,d:%d)\n", frame_num, frame_lost_num, sg_frame_rate, yaw_rate, get_eps_speed_value(), gear_status, door_status);
	}
	tg = &fdata->trkgrp;
	tg->frame_num = frame_num;
	//tg->tcnt = 0;
	IPC_SEND_MSG_Z40(MSG_TARGETS_LIST, tg, 0);

//	tracking_group_t tg = {};
//	IPC_SEND_MSG_Z40(MSG_TARGETS_LIST, &tg, 0);
	return;
}

void tracking_process(void *data)
{
	uint16_t	tcnt = 0, mcnt = 0;
    float   	start, end, yaw_x, acc_x, acc_y, acc_z;

	if (tracking_ready == 0) {
		PRINTF("ERR: tracking isn't ready!\n");
	}

	yaw_rate = fdata->yaw_msg;
	yaw_x = -1.0 * ((fdata->comp_veh_spd + 0.0278) / ((yaw_rate * DEGREE_TO_RADIAN) + 0.0000000001));
	acc_x = (VEH_STATUS_VALID == get_veh_onboard_filtered_acc_x_status())?(get_veh_onboard_filtered_acc_x_value()/1000.0):0;
	acc_y = (VEH_STATUS_VALID == get_veh_onboard_filtered_acc_y_status())?(get_veh_onboard_filtered_acc_y_value()/1000.0):0;
	acc_z = fdata->acc_z;

    // read measurements
    frame_num = fdata->counter;
    mcnt = fdata->mgrp.mcnt;
    if (trkapi->track_frame_init == NULL) {
    	PRINTF("ERR: tracking APIs are NULL: mode(%s)!\n", tracking_mode_get(trkpars->info.mode));
    	return;
    }    
    trkapi->track_frame_init(frame_num, fdata->comp_veh_spd, yaw_rate, yaw_x, gear_status, door_status, acc_z);

    // per-frame tracking
	if (trkpars->info.tracking_dbg) {
		PRINTF("Tracking(f:%d,l:%d,r:%d,y:%.2f,ax:%.3f,ay:%.3f,az:%.3f,v:%.2f,g:%d,d:%d,t:%d,ca:%.3f)\n",
				frame_num, frame_lost_num, sg_frame_rate, yaw_rate, acc_x, acc_y, acc_z, get_eps_speed_value(), gear_status, door_status, trkctx->tunnel_flag, trkctx->calib_angle);
	}
    start = STM_0.CNT.R;
	trkapi->track_frame();
	tcnt = tracking_targets_get();
	end = STM_0.CNT.R;
	if (trkpars->info.tracking_dbg) {
		PRINTF("...Done(m:%d,t:%d,T:%dus)\n", mcnt, tcnt, (int)((end - start)*16.7/1000));
	}

#if JSON_LIST_EN
	uint32_t json_frame_lost_num = (uint32_t)frame_lost_num;
	uint32_t json_tunnel_flag = (uint32_t)trkctx->tunnel_flag;

	reg_dbg_info("fLoseNum", DBG_INFO_TYPE_U32);
	send_dbg_info("fLoseNum", &json_frame_lost_num);
	reg_dbg_info("tunnelFLG", DBG_INFO_TYPE_U32);
	send_dbg_info("tunnelFLG", &json_tunnel_flag);
	reg_dbg_info("caibAngle", DBG_INFO_TYPE_F32);
	send_dbg_info("caibAngle", (uint32_t *)&trkctx->calib_angle);
#endif
	
	return;
}

static char* get_activity_state(uint8_t activity)
{
	switch (activity) {
		case 0:
			return "OFF";
		case 1:
			return "ON";
		default:
			return "Unknown";
	}

	return "Unknown";
}

static char* get_tracking_mode(uint8_t mode)
{
	switch (mode) {
		case TRACKING_MODE_FCW:
			return "FCW";
		case TRACKING_MODE_RCW:
			return "RCW";
		default:
			return "Unknown";
	}

	return "Unknown";
}

static char* get_dynamic_status(uint8_t mode)
{
	switch (mode) {
		case DYNAMIC_STATUS_ALL:
			return "All";
		case DYNAMIC_STATUS_ONCOMING_ONLY:
			return "Oncoming only";
		default:
			return "Unknown";
	}

	return "Unknown";
}

static char* get_warning_dyn_status(uint8_t mode)
{
	switch (mode) {
		case X_DYNAMIC_STATUS_ALL:
			return "All";
		case X_DYNAMIC_STATUS_ONCOMING_WO:
			return "W/O oncoming";
		default:
			return "Unknown";
	}

	return "Unknown";
}

void final_proc_command(char** args, int count)
{
	float v0, v1;
    
	if (!strncmp(args[0], "z7-sh", 5)) {
	    #if 0
	    uint32_t id=TRACKING_PARS_ID;
	    uint8_t test=20;
	    memcpy((uint8_t*)&trkpars->info.max_cnt,&test,1);
	    IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)id, 0);
	    #endif
	    
		PRINTF("Tracking setting (trkp):\n");
		PRINTF("- tracking mode(tmode): %s (0:FCW, 1:BSD, 2:RCW, 3:PDS, 4:ODS)\n", get_tracking_mode(trkpars->info.mode));
		PRINTF("- target maximum count(tcnt): %d\n", trkpars->info.max_cnt);
		PRINTF("- dynamic status(dynst): %s\n", get_dynamic_status(trkpars->info.dynamic_status));	
		PRINTF("- tracking debug(debug): %d\n", trkpars->info.tracking_dbg);
		v0 = trkpars->info.oper_speed[0] * MS_TO_KPH;
		v1 = trkpars->info.oper_speed[1] * MS_TO_KPH;
		PRINTF("- operating speed(opspd): %.2f ~ %.2f km/h\n", v0, v1);
		v0 = trkpars->info.standing_on_off * MS_TO_KPH;
		PRINTF("- standing ON/OFF(stdspd): %.2f km/h\n", v0);
		PRINTF("- view width(vwdh): %.2f m\n", trkpars->info.view_width);
		PRINTF("- view range(vrng): %.2f m\n", trkpars->info.view_range);
		PRINTF("- view angle(vang): %.2f degree\n", trkpars->info.view_angle);
		PRINTF("- view zone(vzone): X(%.2f ~ %.2f) Y(%.2f ~ %.2f) m\n", trkpars->info.view_zone[0], trkpars->info.view_zone[1],
			trkpars->info.view_zone[2], trkpars->info.view_zone[3]);
		PRINTF("- lane width(lane): [%.2f %.2f] m\n", trkpars->info.lane_width[0], trkpars->info.lane_width[1]);
		PRINTF("- body width(bwdh): %.2f m\n", trkpars->info.body_width);
		PRINTF("- aoa shift(aoa): %.2f degree\n", trkpars->info.aoa_shift);
		PRINTF("- position shift(pshift): [%.2f %.2f] m [lateral, longitudinal]\n", trkpars->info.position_shift[0], trkpars->info.position_shift[1]);
		PRINTF("- steering ratio(strgr): %.2f\n", trkpars->info.steering_ratio);
		PRINTF("- grouping flag(tgrp): %s\n", get_activity_state(trkpars->info.grouping_flag));
		PRINTF("- measurement limit(mlimit): %d\n", trkpars->info.measurement_limit);	
		PRINTF("- warning message flag(wmsg): %d\n", trkpars->info.warning_message_flag);
		PRINTF("- yaw sensor message(ymsg): %d\n", trkpars->info.yaw_sensor_message_flag);
		PRINTF("- grouping gate(ggate): [%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f] m\n", trkpars->info.grouping_gate[0], trkpars->info.grouping_gate[1],
			trkpars->info.grouping_gate[2], trkpars->info.grouping_gate[3], trkpars->info.grouping_gate[4], trkpars->info.grouping_gate[5],
			trkpars->info.grouping_gate[6], trkpars->info.grouping_gate[7]);
		PRINTF("- chassis gate(cgate): %.2f m\n", trkpars->info.chassis_gate);
		PRINTF("- angle IIR (aiir): [%.2f %.2f %.2f %.2f]\n", trkpars->info.angle_IIR[0], trkpars->info.angle_IIR[1],
			trkpars->info.angle_IIR[2], trkpars->info.angle_IIR[3]);
		PRINTF("- guardrail (gdl): [%.2f %.2f %.2f %.2f] [speed, gx, gy, yaw]\n", trkpars->info.guardrail[0], trkpars->info.guardrail[1],
			trkpars->info.guardrail[2], trkpars->info.guardrail[3]);
		PRINTF("- tunnel detection(tunnel): [%.2f %.2f %.2f %.2f] [speed, x, angle, average]\n", trkpars->info.tunnel[0], trkpars->info.tunnel[1],
			trkpars->info.tunnel[2], trkpars->info.tunnel[3]);
		PRINTF("- ditchcover filter(dfilter): [%.2f %.2f %.2f %.2f %.2f %.2f] [speed, ttc, x, y, yaw, frame]\n", trkpars->info.ditchcover_filter[0], trkpars->info.ditchcover_filter[1],
			trkpars->info.ditchcover_filter[2], trkpars->info.ditchcover_filter[3], trkpars->info.ditchcover_filter[4], trkpars->info.ditchcover_filter[5]);
		PRINTF("- vertical angle filter(vangle): [%d %d %d %d %d %d %d %d %d %d %d %d] [enable, display, IIR, width, yaw, degree, dist, times, degree, dist, times, mag]\n",
			trkpars->info.vangle[0], trkpars->info.vangle[1], trkpars->info.vangle[2], trkpars->info.vangle[3], trkpars->info.vangle[4], trkpars->info.vangle[5],
			trkpars->info.vangle[6], trkpars->info.vangle[7], trkpars->info.vangle[8], trkpars->info.vangle[9], trkpars->info.vangle[10], trkpars->info.vangle[11]);
		PRINTF("- cipv setting(cipv): [%d %d %d %d] [standing generate frame, standing disappear frame, dynamic generate frame, dynamic disappear frame]\n",
			trkpars->info.cipv[0], trkpars->info.cipv[1], trkpars->info.cipv[2], trkpars->info.cipv[3]);
		PRINTF("- target score(tscore): [%d %d %d %d] [standing min score, standing max score, dynamic min score, dynamic max score]\n",
			trkpars->info.target_score[0], trkpars->info.target_score[1], trkpars->info.target_score[2], trkpars->info.target_score[3]);
		PRINTF("- rcs level(rcs): [%d %d %d %d %d %d %d %d] [rcs enable, truck min rcs, car min rcs, scooter min rcs, rcs filter, x, y, frame]\n",
			trkpars->info.rcs_level[0], trkpars->info.rcs_level[1], trkpars->info.rcs_level[2], trkpars->info.rcs_level[3],
			trkpars->info.rcs_level[4], trkpars->info.rcs_level[5], trkpars->info.rcs_level[6], trkpars->info.rcs_level[7]);
		PRINTF("- possible upper bound(pub): %d\n", trkpars->info.possible_upper);
		PRINTF("- frame make up(fmakeup): %s %d\n", get_activity_state(trkpars->info.frame_makeup[0]), trkpars->info.frame_makeup[1]);
		PRINTF("- door close time(door): %d frames\n", trkpars->info.door_close_time);
		PRINTF("- measurement display(mplay): %s\n", get_activity_state(trkpars->info.measurement_display));
		PRINTF("- extend lane width coef(exlwc): %d %d %d %d\n", trkpars->info.extend_lane_width_coef[0], trkpars->info.extend_lane_width_coef[1],
					trkpars->info.extend_lane_width_coef[2], trkpars->info.extend_lane_width_coef[3]);
		PRINTF("- init flag(init): %d\n", trkpars->info.init_flag);
		PRINTF("Tracking setting 2(trk2):\n");
		PRINTF("- potential cipv enable(pcipv): %d\n", trkpars2->info.pcipv_enable);
		PRINTF("- acc aeb setting (accaeb): [%.2f %.2f] [speed, range]\n", trkpars2->info.acc_aeb[0], trkpars2->info.acc_aeb[1]);
		PRINTF("- rcs gate setting (rcsgate): [%.2f %.2f %.2f %.2f %.2f] [truck, car, scooter, standing, x gate in standing]\n", trkpars2->info.rcs_gate[0], trkpars2->info.rcs_gate[1], trkpars2->info.rcs_gate[2], trkpars2->info.rcs_gate[3], trkpars2->info.rcs_gate[4]);
		PRINTF("- mirror setting (mirror): [%.2f %.2f %.2f %.2f %.2f %.2f] [my speed, front car speed, y, x, dist multiple, short dist]\n", trkpars2->info.mirror[0], trkpars2->info.mirror[1], trkpars2->info.mirror[2], trkpars2->info.mirror[3], trkpars2->info.mirror[4], trkpars2->info.mirror[5]);
	    PRINTF("- auto calib (calib): [%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f] [enable, x min, x max, y min, y max, yaw, speed, |ang|, output]\n", trkpars2->info.auto_calib[0], trkpars2->info.auto_calib[1], trkpars2->info.auto_calib[2], trkpars2->info.auto_calib[3], trkpars2->info.auto_calib[4], trkpars2->info.auto_calib[5],
	    		trkpars2->info.auto_calib[6], trkpars2->info.auto_calib[7], trkpars2->info.auto_calib[8]);
	    PRINTF("- align completed (agncom): [%X %X]\n", trkpars2->info.align_completed[0], trkpars2->info.align_completed[1]);
	    PRINTF("- align result: [%X %X]\n", trkpars2->info.align_result[0], trkpars2->info.align_result[1]);
	    PRINTF("- standing speed (sspeed): [%.2f %.2f %.2f %.2f %.2f %.2f] [low speed, 5 degree speed, 60 degree speed, high speed, 5 degree speed, 60 degree speed]\n", trkpars2->info.standing_speed[0], trkpars2->info.standing_speed[1], trkpars2->info.standing_speed[2], trkpars2->info.standing_speed[3], trkpars2->info.standing_speed[4], trkpars2->info.standing_speed[5]);
	    PRINTF("- uds speed makeup (uspeed): [%.2f %.2f %.2f] [slope a, intercept b, speed makeup]\n", trkpars2->info.uds_speed_makeup[0], trkpars2->info.uds_speed_makeup[1], trkpars2->info.uds_speed_makeup[2]);
	    PRINTF("- calib rule (crule): [%d %d %d %d %d %d] [mod, counter, score, times, totalsample(min:10,max:100), oneside_sample]\n", trkpars2->info.calib_rule[0], trkpars2->info.calib_rule[1], trkpars2->info.calib_rule[2], trkpars2->info.calib_rule[3], trkpars2->info.calib_rule[4], trkpars2->info.calib_rule[5]);
	    PRINTF("- vertical align(valign): [%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f] [enable, x min, x max, y min, y max, yaw, speed, vang, accz, ang]\n", trkpars2->info.vertical_align[0], trkpars2->info.vertical_align[1], trkpars2->info.vertical_align[2], trkpars2->info.vertical_align[3], trkpars2->info.vertical_align[4], trkpars2->info.vertical_align[5], trkpars2->info.vertical_align[6],
	    		trkpars2->info.vertical_align[7], trkpars2->info.vertical_align[8], trkpars2->info.vertical_align[9]);
	    PRINTF("- vertical rule(vrule): [%d %d %d] [vasft, times, samplenum]\n", trkpars2->info.vert_rule[0], trkpars2->info.vert_rule[1], trkpars2->info.vert_rule[2] * VERTICAL_SAMPLE_SCALE);
	    PRINTF("- auto-detect enable(aten): [%d %d] [horizontal, vertical]\n", trkpars2->info.auto_detect_en[0], trkpars2->info.auto_detect_en[1]);
		if ((trkpars->info.mode == TRACKING_MODE_FCW) || (trkpars->info.mode == TRACKING_MODE_RCW)) {
			PRINTF("FCW/RCW warning setting (warn):\n");
			PRINTF("- warning dynamic status(xdynst): %s (0:All, 1:W/O oncoming)\n", get_warning_dyn_status(fcwwarn->info.dynamic_status));
			PRINTF("- pre_warning flag(pwarn): %s\n", get_activity_state(fcwwarn->info.pre_warning_flag));
			PRINTF("- warning flag(warn): %s\n", get_activity_state(fcwwarn->info.warning_flag));
			PRINTF("- emergency warning flag(ewarn): %s\n", get_activity_state(fcwwarn->info.emg_warning_flag));
			v0 = fcwwarn->info.warning_ttc_v[0] * MS_TO_KPH;
			v1 = fcwwarn->info.warning_ttc_v[1] * MS_TO_KPH;
			PRINTF("- warning TTC_V(xttcv): [%.2f %.2f] km/h\n", v0, v1);
			PRINTF("- pre-warning TTC(xpttc): [%.2f %.2f] s\n", fcwwarn->info.pre_warning_ttc[0], fcwwarn->info.pre_warning_ttc[1]);
			PRINTF("- warning TTC(xttc): [%.2f %.2f] s\n", fcwwarn->info.warning_ttc[0] , fcwwarn->info.warning_ttc[1]);
			PRINTF("- emergency warning TTC(xettc): [%.2f %.2f] s\n", fcwwarn->info.emg_warning_ttc[0] , fcwwarn->info.emg_warning_ttc[1]);
			PRINTF("- warning distance Atv(xatv): %.2f m/s/s\n", fcwwarn->info.warning_atv);
			PRINTF("- warning distance scaling factor(xsfc): %.2f\n", fcwwarn->info.warning_factor);
			PRINTF("- warning distance minimum(xmin): %.2f m\n", fcwwarn->info.warning_min);
			PRINTF("- warning delay time(xdelay): [%.2fms %.2fs %.2fs]\n", fcwwarn->info.warning_delay[0], fcwwarn->info.warning_delay[1], fcwwarn->info.warning_delay[2]);
			PRINTF("- straight path(spath): [%.2f %.2f %.2f] m\n", fcwwarn->info.straight_path[0], fcwwarn->info.straight_path[1], fcwwarn->info.straight_path[2]);
			PRINTF("- inward path(ipath): [%.2f %.2f] m\n", fcwwarn->info.inward_path[0], fcwwarn->info.inward_path[1]);
			PRINTF("- warning path(wpath): [%.2f %.2f %.2f] m\n", fcwwarn->info.warning_path[0], fcwwarn->info.warning_path[1], fcwwarn->info.warning_path[2]);
			PRINTF("- speed factor(spdfc): [%.2f %.2f]\n", fcwwarn->info.speed_factor[0], fcwwarn->info.speed_factor[1]);
			PRINTF("- path score(pscore): [%d %d]\n", fcwwarn->info.path_score[0], fcwwarn->info.path_score[1]);
			PRINTF("- warning score(wscore): [%d %d]\n", fcwwarn->info.warning_score[0], fcwwarn->info.warning_score[1]);
		}
		PRINTF("Target dump(z7-dump): target dumping\n");
	} else if (!strncmp(args[0], "z7-dump", 7)) {
		if (trkapi->track_target_dump != NULL) {
			trkapi->track_target_dump();
		}
#ifndef DISABLE_SWT
    } else if (!strncmp(args[0], "z7-reset", 5)) {
    	reset_system();
#endif
    } else {
    	PRINTF("z7-vrs {int}      ,velocity range shift\n");
    	PRINTF("z7-log-cfar {1/0} ,enable/disable CFAR log\n");
    }
}

