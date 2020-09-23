/*
 * track_warning.c
 *
 *  Created on: 2017/12/18
 *      Author: Benson
 */
#include <stdio.h>
#include <stdlib.h>
#if defined(CTI_Z7_0)
#include "sys_shared.h"
#endif
#include "product.h"
#include "frame.h"
#include "tracking.h"
#include "track_data.h"
#include "track_warning.h"

#define MAX_WARNING_SCORE 		20
#define DOOR_ZONE_IDX0			1
#define DOOR_ZONE_IDX1			4
#ifndef DEBUG_SIMU
static const product_info_t* prod = NULL;
#endif
static const tracking_pars_t *trkpars = NULL;
static const fcw_warn_t *fcwwarn = NULL;
static tracking_ctx_st *trkctx = NULL;

int track_warning_init(const tracking_pars_t *trkp, const void *warn, tracking_ctx_st *ctx)
{
	if ((trkp == NULL) || (warn == NULL) || (ctx == NULL)) {
		return 1;
	}
	trkpars = trkp;
	fcwwarn = (fcw_warn_t *)warn;
	trkctx = ctx;
#ifndef DEBUG_SIMU
	prod = product_info_get();
#endif
	
	return 0;
}

#ifdef USING_FCW_MODE
int track_condi_warning_get(target_st *t)
{
	static uint8_t Alerting_flag = 0;
	float 	enable_warning_ttc = 0.0;
	float	disable_warning_ttc = 0.0;
	float 	delay_ttc_time	=	0.0;
	static float enable_delay_time = 0.0;
	static float disable_delay_time = 0.0;

    float	cip_vy;
    float	cip_y;

	float	ittc = 0.0;
	uint8_t fpars_rate = trkctx->frame_rate;
	if (t == NULL) {
		return NO_WARNING;
	}

	enable_warning_ttc = fcwwarn->info.warning_delay[1];
	disable_warning_ttc = fcwwarn->info.warning_delay[2];
	delay_ttc_time = fcwwarn->info.warning_delay[0];
	ittc = 0;

	if((trkctx->my_speed >= fcwwarn->info.warning_ttc_v[0]) && (trkctx->my_speed <= fcwwarn->info.warning_ttc_v[1]))
	{
		if (t->vy == 0) //
	    {
	    	Alerting_flag = 0;
	    }
	    else
	    {
	    	cip_y = t->y;
	    	cip_vy = t->vy;
	    	ittc = -1 * (cip_y / cip_vy) ;
	    	if (ittc >= 0) //ttc >= 0
	    	{
	    		if(ittc <= enable_warning_ttc)//ttc need warn
	    		{
	    			enable_delay_time += (1000/fpars_rate);
	    			disable_delay_time = 0;
	    			if(enable_delay_time >= delay_ttc_time)
					{
	    				enable_delay_time = delay_ttc_time;
						Alerting_flag = 1;
					}
	    		}
	    		else if(ittc >= disable_warning_ttc)
	    		{
	    			disable_delay_time += (1000/fpars_rate);
	    			enable_delay_time = 0;
	    			if(disable_delay_time >= delay_ttc_time)
					{
	    				disable_delay_time = delay_ttc_time;
						Alerting_flag = 0;
					}
	    		}
	    		else if(ittc < disable_warning_ttc && ittc >enable_warning_ttc)
	    		{
	    			disable_delay_time = 0;
	    			enable_delay_time = 0;
	    		}
	    	}
	    	else //ttc < 0
	    	{
				disable_delay_time += (1000/fpars_rate);
				enable_delay_time = 0;
				if(disable_delay_time >= delay_ttc_time)
				{
					disable_delay_time = delay_ttc_time;
					Alerting_flag = 0;
				}
	    	}

	//   	PRINTF("ttc =%.2f,warn flag=%d\n",ittc,Alerting_flag);
	//    	PRINTF("pos_y =%.2f,vy=%.2f\n",cip_y,cip_vy);
	//    	PRINTF("ttc =%.2f,warn=%d\n",ittc,Alerting_flag);
	//    	PRINTF("enable=%.2f,disable=%.2f,delay=%.2f\n",enable_warning_ttc,disable_warning_ttc,delay_ttc_time);
	//    	PRINTF("enable time=%.2f,disable time=%.2f\n",enable_delay_time,disable_delay_time);

	    }
	}
	else
	{
		Alerting_flag = 0;
	}

    if(Alerting_flag)
    {
    	if(ittc <= fcwwarn->info.emg_warning_ttc[0])
    	{
        	t->cip_warning = EMG_WARNING;
    	}
    	else if(ittc <= fcwwarn->info.warning_ttc[0])
    	{
    		t->cip_warning = WARNING;
    	}
    	else if(ittc <= fcwwarn->info.pre_warning_ttc[0])
    	{
    		t->cip_warning = PRE_WARNING;
    	}
    	else
    	{
    		t->cip_warning = NO_WARNING;
    	}
    }
    else
    {
    	t->cip_warning = NO_WARNING;
    }
//	PRINTF("warn level= %d\n",t->cip_warning);
	return t->cip_warning;
}

int track_fcw_warning_get(target_st *t)
{
	float	cip_vy;
	float	cip_range = 0.0;
	float 	pre_warning_ttc = 0.0;
	float 	warning_ttc = 0.0;
	float 	emg_warning_ttc = 0.0;
	//float  	atv = 0.0;
	//float  	xfc = 0.0;
	//float  	xmin = 0.0;
	//float 	atv_range = 0.0;
	//float 	ttc_range = 0.0;
	float 	pre_warning_range = 0.0;
    float 	warning_range = 0.0;
	float 	emg_warning_range = 0.0;
	
	if (t == NULL) {
		return NO_WARNING;
	}
	// CIP score < 3
	if (t->cip_warning < CIP_WARNING) {
		return t->cip_warning;
	}
	if ((trkctx->my_speed > 0) && (t->vy < 0)) {
		cip_vy = ABS(t->vy);
		cip_range = t->range;
		//atv = trkpars->info.warning_atv;
		//xfc = trkpars->info.warning_factor;
		//xmin = trkpars->info.warning_min;
		if (trkctx->my_speed >= fcwwarn->info.warning_ttc_v[1]) {
			pre_warning_ttc = fcwwarn->info.pre_warning_ttc[1];
			warning_ttc = fcwwarn->info.warning_ttc[1];
			emg_warning_ttc = fcwwarn->info.emg_warning_ttc[1];
		} else if (trkctx->my_speed >= fcwwarn->info.warning_ttc_v[0]) {
			pre_warning_ttc = fcwwarn->info.pre_warning_ttc[0];
			warning_ttc = fcwwarn->info.warning_ttc[0];
			emg_warning_ttc = fcwwarn->info.emg_warning_ttc[0];
		}
		//ttc_range = ttc * cip_vy;
		//atv_range = (((cip_vy * cip_vy) / (13.34 - (2 * atv))) + (0.8 * cip_vy)) * xfc;
		//warning_range = (ttc_range > atv_range) ? ttc_range : atv_range;
		pre_warning_range =  pre_warning_ttc * cip_vy;
		warning_range = warning_ttc * cip_vy;
		emg_warning_range = emg_warning_ttc * cip_vy;
		if (fcwwarn->info.emg_warning_flag && (cip_range <= emg_warning_range) && (t->cip_warning <= EMG_WARNING)) {
			t->cip_warning = EMG_WARNING;
			t->warning_score = 20;
		} else if (fcwwarn->info.warning_flag && (cip_range <= warning_range)) {
			if (t->cip_warning <= WARNING) {
				if (t->warning_score < 5) {
					t->warning_score++;
				} else {
					t->cip_warning = WARNING;
					t->warning_score = 20;
				}
			} else if (t->cip_warning > WARNING) {
				if (t->warning_score > 0) {
					t->warning_score--;
				} else {
					t->cip_warning = WARNING;
				}
			}
		} else if (fcwwarn->info.pre_warning_flag && (cip_range <= pre_warning_range)) {
		 	if (t->cip_warning <= PRE_WARNING) {
				if (t->warning_score < 5) {
					t->warning_score++;
				} else {
					t->cip_warning = PRE_WARNING;
					t->warning_score = 20;
				}
		 	} else if (t->cip_warning > PRE_WARNING) {
		 		if (t->warning_score > 0) {
					t->warning_score--;
		 		} else {
					t->cip_warning = PRE_WARNING;
		 		}
		 	}
		} else if (fcwwarn->info.warning_flag && (cip_range <= fcwwarn->info.warning_min) && (t->cip_warning <= WARNING)) {
			t->cip_warning = WARNING;
			t->warning_score = 0;
		} else {
			t->cip_warning = CIP_WARNING;
			t->warning_score = 0;
		}

		return t->cip_warning;
	} else {
		t->cip_warning = CIP_WARNING;
		t->warning_score = 0;
	}

	return t->cip_warning;
}
#endif
