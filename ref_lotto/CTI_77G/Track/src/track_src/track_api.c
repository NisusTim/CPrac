
/*
 * track_api.c
 *
 *  Created on: 2017/08/23
 *      Author: Benson
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(CTI_Z7_0)
#include "sys_shared.h"
#include "LibVer.h"
#endif
#include "frame.h"
#include "tracking.h"
#include "track_api.h"
#include "track_lib.h"
#include "track_fcw.h"
#include "track_warning.h"

#if defined(CTI_Z7_0)
const LIBS_VER_T __attribute__((section(".library_version"))) Track_Version =  {
		.id =          VER_ID          (TRACK_LIB_VER),
		.major =       VER_MAJOR       (3),
		.minor =       VER_MINOR       (5),
		.build =       VER_BUILD       (Lib_BUILD_RELEASE),
		.maintenance = VER_MAINTENANCE (2)
};
#endif

static const tracking_pars_t *trkpars = NULL;
static tracking_pars2_t *trkpars2 = NULL;
static tracking_api_st trkapi;

tracking_api_st* track_api_init(frame_data_t *fdata, const tracking_pars_t *pars, tracking_pars2_t *pars2, const void *warn)
{
	trkpars = pars;
	trkpars2 = pars2;
	memset(&fdata->trkctx, 0, sizeof(tracking_ctx_st));
	track_lib_init(fdata, trkpars, trkpars2, &fdata->trkctx);

	memset(&trkapi, 0, sizeof(tracking_api_st));
    if (trkpars->info.mode == TRACKING_MODE_FCW) {
#ifdef USING_FCW_MODE
		trkapi.track_frame_rate_set = track_lib_frame_rate_set;
		trkapi.track_frame_init = track_fcw_frame_init;
		trkapi.track_frame = track_fcw_frame;
		trkapi.track_target_filtering = track_fcw_target_filtering;
		trkapi.track_target_get = track_fcw_target_get;
		trkapi.track_ipc_handler = NULL;
		trkapi.track_target_dump = track_fcw_target_dump;
        track_fcw_init(fdata, trkpars, trkpars2, warn, &fdata->trkctx);
#endif
    }
    track_warning_init(trkpars, warn, &fdata->trkctx);

    return &trkapi;
}

