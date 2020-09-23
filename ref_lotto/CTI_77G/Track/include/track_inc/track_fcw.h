/*
 * track_data.h
 *
 *  Created on: 2017/08/23
 *      Author: Benson
 */

#ifndef __TRACK_FCW_H__
#define __TRACK_FCW_H__

int track_fcw_init(frame_data_t *fdata, const tracking_pars_t *trkp, const tracking_pars2_t *trkp2, const void *warn, tracking_ctx_st *ctx);
int track_fcw_frame_init(uint16_t frame, float speed, float yaw, float radius, uint8_t gear, uint8_t door, float acc_z);
int track_fcw_frame(void);
int track_fcw_target_filtering(void);
int track_fcw_target_get(target_st *output);
int track_fcw_target_dump(void);

#endif // __TRACK_FCW_H__
