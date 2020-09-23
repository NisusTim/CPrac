/*
 * tracking_mod.c
 *
 *  Created on: 2018/04/01
 *      Author: user
 */
#include "sys_shared.h"
#include "tracking_set.h"

int feniex_tracking_pars_set(tracking_pars_t *trkpars, fcw_warn_t *fcwwarn)
{
	trkpars->info.init_flag = 1;
	trkpars->info.mode = TRACKING_MODE_RCW;
	trkpars->info.dynamic_status = DYNAMIC_STATUS_ONCOMING_ONLY;
	trkpars->info.standing_on_off = 0.0;
	trkpars->info.view_width = 8.0;
	trkpars->info.view_angle = 45.0;
	trkpars->info.view_range = 135.0;
	fcwwarn->info.warning_ttc[0] = 5.0;
	fcwwarn->info.warning_ttc[1] = 5.0;
	fcwwarn->info.warning_path[2] = 135.0;
	pars_set((pars_ctx_p)trkpars);
	pars_set((pars_ctx_p)fcwwarn);

	return 0;
}

int hpb_tracking_pars_set(tracking_pars_t *trkpars, fcw_warn_t *fcwwarn)
{
	trkpars->info.init_flag = 1;
	trkpars->info.mode = TRACKING_MODE_RCW;
	trkpars->info.dynamic_status = DYNAMIC_STATUS_ONCOMING_ONLY;
	trkpars->info.standing_on_off = 0.0;
	trkpars->info.view_width = 8.0;
	trkpars->info.view_angle = 45.0;
	trkpars->info.view_range = 150.0;
	fcwwarn->info.warning_ttc[0] = 4.0;
	fcwwarn->info.warning_ttc[1] = 4.0;
	fcwwarn->info.pre_warning_flag = 1;
	fcwwarn->info.warning_flag = 1;
	fcwwarn->info.warning_path[2] = 150.0;
	pars_set((pars_ctx_p)trkpars);
	pars_set((pars_ctx_p)fcwwarn);

	return 0;
}

