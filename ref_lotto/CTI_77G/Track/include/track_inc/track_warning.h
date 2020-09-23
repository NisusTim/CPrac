/*
 * track_warning.h
 *
 *  Created on: 2017/12/18
 *      Author: Benson
 */

#ifndef __TRACK_WARNING_H__
#define __TRACK_WARNING_H__

int track_warning_init(const tracking_pars_t *trkp, const void *warn, tracking_ctx_st *ctx);
#ifdef USING_FCW_MODE
	int track_condi_warning_get(target_st *target);
	int track_fcw_warning_get(target_st *target);
#endif
#ifdef USING_PDS_MODE
	void track_tbb_warning_code_get(target_st *target);
	void track_tbb_warning_score_get(target_st *target);
#endif

#endif /* __TRACK_WARNING_H__ */
