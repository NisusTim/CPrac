
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include <table.h>
#define __ESPRIT_C__
#include <esprit.h>
#include "event.h"
#include "console.h"
#include "target.h"
#include "detections.h"

#define	MUSIC_DEBUG_ENABLED
#ifdef MUSIC_DEBUG_ENABLED
#define MUSIC_DEBUG(...)	do { if(MEAS_FLAG_MUSIC_DEBUG & MEAS_FLAGS_WR) PRINTF(__VA_ARGS__);} while(0)
#else
#define MUSIC_DEBUG(...)	do { } while(0)
#endif

#define RX_ARRAY_DISTANCE   0.5                                  // unit is wave length
#define SIGN_COMPENSATION   1

int cheev_(char *jobz, char *uplo, integer *n, complex *a, integer *lda,
	   real *w, complex *work, integer *lwork, real *rwork, integer *info);

complex H[EIGEN_MAX * EIGEN_MAX];
complex E1[SVD_MAX];
complex E2[SVD_MAX];
complex E1i[SVD_MAX];
//static complex r[EIGEN_MAX];
//extern a_mat_2d;
typedef struct{
	complex vals[200][TOTAL_RX_ACTIVES];
}music_coefs_t;
music_coefs_t* music_table;
int M = 0;
int arry[TOTAL_RX_ACTIVES];
//const complex a_mat_2d[200][8] = {Table};
//const complex test[2][2] = { {{1.0f, 2.0f},{3.0f,40.0f} }, { { 87.0f, 2.0f }, { 87.0f,40.0f } } };

// option parameters registers
float distance_2_pi = RX_ARRAY_DISTANCE * 2 * PI;
int sign_compensation = SIGN_COMPENSATION;

static int MUSIC(complex* r, float* ind) {
	int i;
	int order = M;
	complex H_SS[8 * 8];
	integer n = order;
	integer lda = order;
	real w[8];
	complex work[8 * 3];
	real rwork[8 * 3];
	integer lwork = sizeof(real) * 8 * 3;
	integer info;
	float SP[200];
	complex z[6];
	rec_cov_spasmoo(r, H_SS, order, arry);
	cheev_("V", "U", &n, H_SS, &lda, w, work, &lwork, rwork, &info);
	for (i = 0; i < 200; ++i) {
		noisespa_AOAH(music_table->vals[i], H_SS, z, order, arry);
		mag2_recpc(z, &SP[i], order - 2);
	}
	return peak_max2(SP, ind);
}

void get_music_table(void* table)
{	int i;
	music_table = (music_coefs_t*)table;
	M=0;
	for(i=0; i<TOTAL_RX_ACTIVES; ++i){
		if(music_table->vals[0][i].r != 0 || music_table->vals[0][i].i != 0){
			arry[M] = i;
			M++;
		}
	}
	MUSIC_DEBUG("mus_tab@%p\n", music_table);
}

int music_aoas(target_t* tg, float *music_angles)
{
	int aoa_num, i;
	complex rs[8];
	for(i = 0; i < TOTAL_RX_ACTIVES; i++){
		rs[i].r = (float)tg->cmplx[i].re;
		rs[i].i = (float)tg->cmplx[i].im;
	}
	aoa_num = MUSIC(rs, music_angles);
	/*MUSIC_DEBUG("mus_cpx[%ld+%ldj,%ld+%ldj,%ld+%ldj,%ld+%ldj,%ld+%ldj,%ld+%ldj,%ld+%ldj,%ld+%ldj]@%dus\n",
			tg->cmplx[0].re,tg->cmplx[0].im,tg->cmplx[1].re,tg->cmplx[1].im,tg->cmplx[2].re,tg->cmplx[2].im,
			tg->cmplx[3].re,tg->cmplx[3].im,tg->cmplx[4].re,tg->cmplx[4].im,tg->cmplx[5].re,tg->cmplx[5].im,
			tg->cmplx[6].re,tg->cmplx[6].im,tg->cmplx[7].re,tg->cmplx[7].im,(int)((STM_0.CNT.R-time)*0.016667f));*/

	if (aoa_num < 2)
		return 0;

//	if (aoa_num == 1)
//		music_angles[1] = 180.0f;

	return aoa_num;
}

