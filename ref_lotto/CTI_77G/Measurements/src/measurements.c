/*
 * measurements.c
 *
 *  Created on: Jan 24, 2018
 *      Author: erichu
 */

#include "sys_shared.h"
#include "measurements.h"
#include "f2c.h"
#include "association.h"
#include "vehicle.h"
#include "coefs.h"
#include "TEF810x.h"
#include "custom_math.h"
#include "LibVer.h"

#if JSON_LIST_EN
#include "json_debug_info.h"
#include "z47_ipc.h"
#endif

#define MEAS_DEBUG_FULL					0

#define DEFAULT_MULT_VEL				1
#define MAX_VELOS_PER_RANGE				5

const LIBS_VER_T __attribute__((section(".library_version"))) Detection_version =  {
		.id =         VER_ID          (MEAS_LIB_VER),
		.major=       VER_MAJOR       (3),
		.minor=       VER_MINOR       (3),
		.build=       VER_BUILD       (Lib_BUILD_RELEASE),
		.maintenance= VER_MAINTENANCE (0)
};

static MeasAsn meas_asn[FRAME_CTXS_COUNT];
static MeasAsn *asn_sr=meas_asn, *asn_lr=meas_asn+1;
static frame_data_p fdata = NULL;
static float my_speed = 0;		// m/s
static const frame_info_t* fpars = NULL;
static const coefs_data_t* coefs = NULL;
static const tef810x_info_t* tefp = NULL;

int music_aoas(target_p tg, float *music_angles);
void get_music_table(void* table);
static uint8_t music_cnts = 0;

#define HARMONIC_RANGE_START		10
#define HARMONIC_RANGE_END			80
static int harmonic_filter(measurement_group_p mgp, measurement_p mp, float rthld, float vthld)
{
	if(mp->range < HARMONIC_RANGE_START || mp->range > HARMONIC_RANGE_END)
		return FALSE;

	float r=mp->range/2, v=mp->velocity/2;
	measurement_p	m = mgp->measurements;
	while(m < (mgp->measurements+mgp->mcnt)){
		if(DELTA(m->range,r) <= rthld){ // harmonic filter
			if(DELTA(m->velocity,v) <= vthld && mp->mag < (m->mag-3)){
				if(DELTA(m->angle, mp->angle) <= 3){
					PRINTF("ham:a:%.2f,v:%.2f,r:%.2f,h:%.1f,m:%.1f\n",mp->angle,mp->velocity,mp->range,mp->vangle,mp->mag);
					return TRUE;
				}
			}
		}
		else if(m->range > r)
			break;
		m++;
	}
	return FALSE;
}

static int measurements_angle_filter(measurement_p mp)
{
	int idx = FRAME_CTX_IDX_NEAR;
	if(mp->vangle < 180.0f)
		idx = FRAME_CTX_IDX_LONG;
	if(mp->angle < fpars->aoa_start[idx] || mp->angle > fpars->aoa_end[idx])
		return TRUE;
	return FALSE;
}

#define DUPLICATED_RANGE_START	5
#define DUPLICATED_RANGE_END	43
static int measurements_filters(measurement_group_p mgp, measurement_p mp, float rthld, float vthld)
{
	if(measurements_angle_filter(mp) == TRUE)
		return TRUE;

	if(mgp->mcnt == 0)
		return FALSE;

	if(mp->range >= DUPLICATED_RANGE_START && mp->range < DUPLICATED_RANGE_END){
		measurement_p m = mgp->measurements+mgp->mcnt-1;
		while(m >= mgp->measurements){
			if(DELTA(m->range, mp->range) <= 0.5){
				if(DELTA(m->velocity,mp->velocity)<0.35f && DELTA(mp->angle,m->angle)<2.0f){
					float radian;
					if(mp->vangle < 180.0f){ // Force measurement in LR
						radian = RADIAN_OF_DEGREE(mp->angle);
						//m->range = mp->range;
						m->vangle = mp->vangle;
						m->mag = mp->mag;
						m->angle = mp->angle;
						m->x = SIN(radian)*m->range;
						m->y = COS(radian)*m->range;
						m->vy = m->velocity / (COS(radian)+0.0000001);
					}

#if 1
					else if(m->vangle < 180.0f){
						radian = RADIAN_OF_DEGREE(m->angle);
						m->range = mp->range;
						m->velocity = mp->velocity;
						m->x = SIN(radian)*mp->range;
						m->y = COS(radian)*mp->range;
						m->vy = mp->velocity / (COS(radian)+0.0000001);
					}
#endif

					PRINTF("dup:a:%.2f,v:%.2f,r:%.2f,h:%.1f,m:%.1f\n",mp->angle,mp->velocity,mp->range,mp->vangle,mp->mag);
					return TRUE;
				}
			}
			else
				break;
			m--;
		}
	}

	return harmonic_filter(mgp, mp, rthld, vthld);
}

static float mgrp_music(measurement_p mp, target_p tg)
{
	/* MUSIC alg.
	 * parameters: fpars->haoa[0~3]
	 * fpars->haoa[0], 0: turn off. bigger than 0: turn on, how many times MUSIC will be called in a frame.
	 * fpars->haoa[1], subject vehicle speed limit
	 * fpars->haoa[2], min_dist
	 * fpars->haoa[3], max_dist
	 */
	if(music_cnts < fpars->haoa[0] && ((int16_t)my_speed < fpars->haoa[1]) && fpars->haoa[2] < mp->range && mp->range < fpars->haoa[3]){
		float music_angles[2];
		music_cnts++;
		if(music_aoas(tg, music_angles)) {
			if(MEAS_FLAGS_WR & MEAS_FLAG_MUSIC_DEBUG)
				PRINTF("mus: %.4f@%.1fm=>[%.1f,%.1f]\n", mp->angle, mp->range, music_angles[0], music_angles[1]);

			float radian = RADIAN_OF_DEGREE(music_angles[0]);
			mp->angle = music_angles[0];
			mp->x = SIN(radian)*mp->range;
			mp->y = COS(radian)*mp->range;
			mp->vy = mp->velocity / (COS(radian)+0.0000001);
			return music_angles[1];
		}
	}
	return 180.0f;
}

static void measurements_adding(meta_meas_group_t* mmg, meta_meas_t* mm, int8_t flip)
{
	float music_a;
	if (fdata->mgrp.mcnt < MAX_COUNT_OF_MEASUREMENTS_PER_FRAME){
		measurement_p mp = &fdata->mgrp.measurements[fdata->mgrp.mcnt];
		mp->velocity = EXP_VEL(mm->vel,mmg->vel_max,flip);

		if(mp->velocity < (-MAX_VELOCITY_SUPPORTED) || (mp->velocity+my_speed) > MAX_VELOCITY_SUPPORTED)
			return;

		mp->range = mm->range;
		mp->x = mm->rng_x;
		mp->y = mm->rng_y;
		mp->vy = mp->velocity / aoaidx_cos(mm->aoaidx);
		mp->angle = DEGREE_OF_RADIAN(aoaidx_asin(mm->aoaidx));
		mp->vangle = mm->tg->vangle;
		mp->mag = SPT_LOG2DB(mm->tg->mag_log2);

		if(mp->vangle < 180.0f && DELTA(mp->velocity,-my_speed) <= DEFAULT_MUSIC_STATIONARY_VEL){ // LR and Stationary

			music_a = mgrp_music(mp, mm->tg);
			if (measurements_filters(&fdata->mgrp, mp, mmg->tgg->runit, mmg->tgg->vunit) == FALSE)
				fdata->mgrp.mcnt++;

			if(music_a < 180.0f && fdata->mgrp.mcnt < MAX_COUNT_OF_MEASUREMENTS_PER_FRAME){
				measurement_p nmp = &fdata->mgrp.measurements[fdata->mgrp.mcnt];
				float radian = RADIAN_OF_DEGREE(music_a);
				nmp->velocity = mp->velocity;
				nmp->range = mp->range;
				nmp->angle = music_a;
				nmp->vangle = mp->vangle;
				nmp->mag = mp->mag;
				nmp->x = SIN(radian)*nmp->range;
				nmp->y = COS(radian)*nmp->range;
				nmp->vy = nmp->velocity / (COS(radian)+0.0000001);
				if(MEAS_FLAGS_WR & MEAS_FLAG_MUSIC_DEBUG)
					PRINTF("mus: adding(%d) %.4f@%.1fm\n", fdata->mgrp.mcnt, nmp->angle, nmp->range);
				if (measurements_filters(&fdata->mgrp, nmp, mmg->tgg->runit, mmg->tgg->vunit) == FALSE)
					fdata->mgrp.mcnt++;
			}
		}
		else if (measurements_filters(&fdata->mgrp, mp, mmg->tgg->runit, mmg->tgg->vunit) == FALSE)
			fdata->mgrp.mcnt++;
	}
}

static int16_t measurements_inphs_bin(int16_t v)
{
	if(v >= (CHIRPS_PER_FRAME/2))
		v -= CHIRPS_PER_FRAME;
	else if(v < (-CHIRPS_PER_FRAME/2))
		v += CHIRPS_PER_FRAME;
	return v;
}

static int measurements_inout_filter(meta_meas_group_t* mmg, meta_meas_t* mm)
{
	meta_meas_t* m = mm-MAX_VELOS_PER_RANGE;
	if(m < mmg->mm)
		m = mmg->mm;

	for(; m < (mmg->mm+mmg->mm_cnt); m++){
		if(m->range == mm->range){
			if(m != mm && m->flip != kNotPaired){
				if(measurements_inphs_bin(m->tg->velocity) == measurements_inphs_bin(mm->tg->velocity))
					return FALSE;
			}
		}
		else if(m->range > mm->range)
			break;
	}
	return TRUE;
}

static void measurement_stationary(meta_meas_group_t* mmg, meta_meas_t* mm)
{
	int flip;
	for(flip = -DEFAULT_MULT_VEL;flip<=0;flip++){
		if(DELTA(EXP_VEL(mm->vel,mmg->vel_max,flip),-my_speed*aoaidx_cos(mm->aoaidx)) <= DEFAULT_GATE_STATIONARY_VEL){
			mm->flip = flip;
			if(MEAS_FLAG_ASSO_DEBUG & MEAS_FLAGS_WR)
				PRINTF("std(%.2f,%d)\n",mm->range, mm->tg->velocity);
			return;
		}
	}
}

static void measurements_allocation(meta_meas_group_t* mmg, meta_meas_t* mm)
{
	int8_t flip;
	mm->tg->pos = mm->flip;
	if (mm->flip != kNotPaired){
		measurements_adding(mmg, mm, mm->flip);
		return;
	}

	if(mm->tg->vangle < 180){
		if (measurements_inout_filter(mmg,mm) == FALSE){
			if(MEAS_FLAG_ASSO_DEBUG & MEAS_FLAGS_WR)
				PRINTF("iop(%.2f,%d)\n",mm->range, mm->tg->velocity);
			return;
		}

#if 0 // not applied because vangle is untrusted
		if(ABS(mm->tg->vangle) > 90){
			if(MEAS_FLAG_ASSO_DEBUG & MEAS_FLAGS_WR)
				PRINTF("out(%.2f,%d)\n",mm->range, mm->tg->velocity);
			return;
		}
#endif

		if(MEAS_FLAGS_WR & MEAS_FLAG_LR_VELO_EXPAND){
			for(flip = -asn_lr->mult_vel; flip < (asn_lr->mult_vel+1); flip++)
				measurements_adding(mmg, mm, flip);
		}
	}
	else if(MEAS_FLAGS_WR & MEAS_FLAG_SR_VELO_EXPAND){
		for(flip = -asn_sr->mult_vel; flip < (asn_sr->mult_vel+1); flip++)
			measurements_adding(mmg, mm, flip);
	}
}

static void measurements_merge(meta_meas_group_t* sr, meta_meas_group_t* lr)
{
	meta_meas_t* mm_sr = sr->mm;
	meta_meas_t* mm_lr = lr->mm;

	while(mm_sr < ((sr->mm+sr->mm_cnt))){
		if(mm_sr->flip == kNotPaired)
			measurement_stationary(sr, mm_sr);
		mm_sr++;
	}

	while(mm_lr < ((lr->mm+lr->mm_cnt))){
		if(mm_lr->flip == kNotPaired)
			measurement_stationary(lr, mm_lr);
		mm_lr++;
	}

	mm_sr = sr->mm;
	mm_lr = lr->mm;
	while(mm_sr < (sr->mm+sr->mm_cnt)){
		if(mm_lr < (lr->mm+lr->mm_cnt)){
			if(mm_sr->rng_y <= mm_lr->rng_y)
				measurements_allocation(sr, mm_sr++);
			else
				measurements_allocation(lr, mm_lr++);
		}
		else
			measurements_allocation(sr, mm_sr++);
	}

	while(mm_lr < (lr->mm+lr->mm_cnt))
		measurements_allocation(lr, mm_lr++);
}

// ticket-533: side lane SR measurement flip to central lane
#define SR_MEAS_FILTTER_AFTER_MERGE
#ifdef SR_MEAS_FILTTER_AFTER_MERGE
static int measurements_sr_filter(measurement_group_p mgrp)
{
	int cnt = 0;
	for(measurement_p mp = mgrp->measurements; mp < mgrp->measurements+mgrp->mcnt; mp++){
		if(mp->vangle < 180.0f){
			if(mp->range > 30.0)
				break;
			continue;
		}

		if(mp->range >= 2 && ABS(mp->angle) <= 8.0f){
			mp->score = 1;
			cnt++;
			PRINTF("srf:%d r=%.2f,a=%.2f\n",cnt,mp->range,mp->angle);
		}
	}

	return cnt;
}
#endif

void measurements_process(frame_data_p fd)
{
	uint32_t			time = STM_0.CNT.R;
	float				func_spend_time = 0;	//uint: ms
	int					idx = 0;
	measurement_p 		mp = NULL;
	target_group_p 		tgg_sr = fd->tggs, tgg_lr = fd->tggs+1;
	meta_meas_group_t 	*mmg_sr,*mmg_lr;

	fdata = fd;

	my_speed = get_eps_speed_value() * KPH_TO_MS;
	music_cnts = 0;

	// Short range measurements assocition
	mmg_sr = asn_sr->API_Association(asn_sr, tgg_sr, (tgg_sr->time-tgg_sr->x->time)*CLOCK_PERIOD_S);

	// Long range measurements association
	mmg_lr = asn_lr->API_Association(asn_lr, tgg_lr, (tgg_lr->time-tgg_lr->x->time)*CLOCK_PERIOD_S);

	if(fdata->mgrp.mcnt){
		memset(fdata->mgrp.measurements, 0, sizeof(measurement_t)*fdata->mgrp.mcnt);
		fdata->mgrp.mcnt = 0;
	}

	measurements_merge(mmg_sr, mmg_lr);

	fdata->mgrp.state = TRK_MEAS_ST_DONE;

	tgg_sr->state = TGG_ST_READY;
	tgg_lr->state = TGG_ST_READY;

#ifdef SR_MEAS_FILTTER_AFTER_MERGE		// ticket-533
	measurements_sr_filter(&fdata->mgrp);
#endif

	// for unifing veh msg, sync z4/z70/z71
	fdata->yaw_msg = (VEH_STATUS_VALID == get_veh_two_src_filtered_yaw_rate_status())?get_veh_two_src_filtered_yaw_rate_value():0.0;//Yaw source: obd or onboard.
	fdata->comp_veh_spd = get_eps_speed_value() * KPH_TO_MS;
	fdata->acc_z = (VEH_STATUS_VALID == get_veh_onboard_filtered_acc_z_status())?(get_veh_onboard_filtered_acc_z_value()/1000.0):0;

	if(MEAS_MOD_WR >= MEAS_MOD_TRACK)
		IPC_SEND_MSG_Z70(MSG_TARGETS_LIST, (void*)fdata, 0);

	PRINTF("mclt[%d,%d],vmx[%.2f,%.2f],%.1fm\n",fdata->mgrp.mcnt,music_cnts, mmg_sr->vel_max,mmg_lr->vel_max,
			(STM_0.CNT.R - time)*CLOCK_PERIOD_MS);

	if(MEAS_FLAG_ASSO_DEBUG & MEAS_FLAGS_WR)
	{
		target_p tg;
		meta_meas_t *mm;
		int idx;

		PRINTF("Meas:et=%.1fms\n",(STM_0.CNT.R-time)*CLOCK_PERIOD_MS);

		PRINTF("tgg(0):ru=%.2f,vu=%.5f,vs=%d,dt=%.4fs\n",tgg_sr->runit,tgg_sr->vunit,tgg_sr->vbins,asn_sr->time_delta);
		for(tg=tgg_sr->targets, idx=0; tg < (tgg_sr->targets+tgg_sr->tcnt); tg++){
			if(tg->aoaidx != AOAIDX_INVALID)
				PRINTF("t%d,a:%.4f,v:%d,r:%d,m:%.1f\n", idx++, DEGREE_OF_RADIAN(aoaidx_asin(tg->aoaidx)), tg->velocity,
						tg->range, SPT_LOG2DB(tg->mag_log2));
		}

		PRINTF("mmg(0):gt={x:%.1f,y:%.1f,v:%.1f},cnt=%d,vm=%.2f\n",asn_sr->gate.rng_x,asn_sr->gate.rng_y,asn_sr->gate.vel,
				mmg_sr->mm_cnt,mmg_sr->vel_max);
		for(mm=mmg_sr->mm,idx=0; idx<mmg_sr->mm_cnt; idx++,mm++)
			PRINTF("m%d,r:%.2f,a:%.4f,x:%.2f,y:%.2f,v:%.2f,f:%d\n",idx,mm->range,DEGREE_OF_RADIAN(aoaidx_asin(mm->aoaidx)),
					mm->rng_x,mm->rng_y,mm->vel,mm->flip);

		PRINTF("tgg(1):ru=%.2f,vu=%.5f,vs=%d,dt=%.4fs\n",tgg_lr->runit,tgg_lr->vunit,tgg_lr->vbins,asn_lr->time_delta);
		for(tg=tgg_lr->targets, idx=0; tg < (tgg_lr->targets+tgg_lr->tcnt); tg++){
			if(tg->aoaidx != AOAIDX_INVALID)
				PRINTF("t%d,a:%.4f,v:%d,r:%d,m:%.1f\n", idx++, DEGREE_OF_RADIAN(aoaidx_asin(tg->aoaidx)), tg->velocity,
						tg->range, SPT_LOG2DB(tg->mag_log2));
		}

		PRINTF("mmg(1):gt={x:%.1f,y:%.1f,v:%.1f},cnt=%d,vm=%.2f\n",asn_lr->gate.rng_x,asn_lr->gate.rng_y,asn_lr->gate.vel,
				mmg_lr->mm_cnt,mmg_lr->vel_max);
		for(mm=mmg_lr->mm,idx=0; idx<mmg_lr->mm_cnt; idx++,mm++)
			PRINTF("m%d,r:%.2f,a:%.4f,x:%.2f,y:%.2f,v:%.2f,f:%d\n",idx,mm->range,DEGREE_OF_RADIAN(aoaidx_asin(mm->aoaidx)),
					mm->rng_x,mm->rng_y,mm->vel,mm->flip);
	}


	if (MEAS_FLAG_LOG_MEASUREMENTS & MEAS_FLAGS_WR){
		 mp = fdata->mgrp.measurements;
		for(idx = 0; idx < fdata->mgrp.mcnt; idx++){
			PRINTF("e%d,a:%.4f,v:%.2f,r:%.2f,h:%.1f,m:%.1f\n", idx, mp->angle, mp->velocity, mp->range, mp->vangle, mp->mag);
			mp++;
		}
	}

	func_spend_time = (STM_0.CNT.R - time)*0.0000167f;
	PRINTF("mclt:tggs=>%d,%.1fm\n", fdata->mgrp.mcnt, func_spend_time);

#if JSON_LIST_EN
	reg_dbg_info("funcT", DBG_INFO_TYPE_F32);
	send_dbg_info("funcT", (uint32_t *)&func_spend_time);
	IPC_SEND_MSG_Z40(MSG_JSON_MEAS_LIST, fdata, 0);
#endif
}

aoaidxs_table_p aoaidxs = NULL;
float aoaidx_asin(int16_t idx) {return aoaidxs->asin[idx];}
float aoaidx_sin(int16_t idx) {return aoaidxs->sin[idx];}
float aoaidx_cos(int16_t idx) {return aoaidxs->cos[idx];}

void measurements_aoaidxs_set(void* table) {aoaidxs = (aoaidxs_table_p)table;}

void measurements_pars_init(void* p)
{
	fpars = (const frame_info_t*)(pars_ctx_get(FRAME_PARS_ID)->info);
	coefs = (const coefs_data_t*)(pars_ctx_get(COEFS_PARS_ID)->info);
	tefp = (const tef810x_info_t*)(pars_ctx_get(TEF_PARS_ID)->info);
	PRINTF("meas: pars(fpar:%p,coefs:%p,tefp:%p) inited\n",fpars, coefs, tefp);

	asn_sr->gate.rng_x = fpars->asso_x[FRAME_CTX_IDX_NEAR]*0.1f;
	asn_sr->gate.rng_y = fpars->asso_y[FRAME_CTX_IDX_NEAR]*0.1f;
	asn_sr->gate.vel = fpars->asso_v[FRAME_CTX_IDX_NEAR]*0.1f;
	asn_sr->gate.range = sqrtf(asn_sr->gate.rng_x*asn_sr->gate.rng_x+asn_sr->gate.rng_y*asn_sr->gate.rng_y);

	asn_lr->gate.rng_x = fpars->asso_x[FRAME_CTX_IDX_LONG]*0.1f;
	asn_lr->gate.rng_y = fpars->asso_y[FRAME_CTX_IDX_LONG]*0.1f;
	asn_lr->gate.vel = fpars->asso_v[FRAME_CTX_IDX_LONG]*0.1f;
	asn_lr->gate.range = sqrtf(asn_lr->gate.rng_x*asn_lr->gate.rng_x+asn_lr->gate.rng_y*asn_lr->gate.rng_y);
	ASSO_DEBUG("asn gate:sr[%.1f,%.1f,%.1f,%.1f],lr[%.1f,%.1f,%.1f,%.1f]\n",
			asn_sr->gate.range,asn_sr->gate.rng_x,asn_sr->gate.rng_y,asn_sr->gate.vel,
			asn_lr->gate.range,asn_lr->gate.rng_x,asn_lr->gate.rng_y,asn_lr->gate.vel);

}

void measurements_init(void)
{
	API_NewMeasAsn(asn_sr);
	asn_sr->mult_vel = DEFAULT_MULT_VEL;

	API_NewMeasAsn(asn_lr);
	asn_lr->mult_vel = DEFAULT_MULT_VEL;

	ipc_reg_msg(MSG_AOAIDXS_TABLE, "aoaidx", (msg_proc_p)measurements_aoaidxs_set);
	ipc_reg_msg(MSG_TARGETS_LIST, "tgtlist", (msg_proc_p)measurements_process);
	ipc_reg_msg(MSG_MUSIC_COEFS, "music", (msg_proc_p)get_music_table);
	pars_init_proc_reg(measurements_pars_init, NULL, "meas");
#if MEAS_DEBUG_FULL
	MEAS_FLAGS_WR |= MEAS_FLAG_ASSO_DEBUG;
#endif

}
