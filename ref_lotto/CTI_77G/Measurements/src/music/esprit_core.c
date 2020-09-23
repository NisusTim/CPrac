
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define __ESPRIT_CORE_C__
#include <esprit.h>

complex r[EIGEN_MAX];


// get the first hermitian matrix from input Rx data
//void rx_to_herm(complex *Rx, complex *H, int order)
//{
//  integer m = order;
//  integer n = order;
//  integer k = 1;
//  integer lda = order;
//  integer ldb = order;
//  integer ldc = order;
//  complex alpha = {1, 0};
//  
//  memcpy(r, Rx, sizeof(complex)*order);
//  
//  //cm_print("before hermitian", (float *)r, order, 1);
//  
//  memset(H, 0, sizeof(complex)*order*order);  
//  cgemm_("N", "C", &m, &n, &k, &alpha, r, &lda, r, &ldb, &alpha, H, &ldc);
//}
//
//real w[EIGEN_MAX];
//
//complex work[EIGEN_MAX * 3];
//real rwork[EIGEN_MAX * 3];
//real iwork[EIGEN_MAX * 3];
//
//void herm_eigen(complex *H, complex *E1, complex *E2, int order)
//{
//  integer n = order;
//  integer lda = order;
//  integer lwork = sizeof(real) * order * 3;
//  integer info;
//  
//  memset(work, 0, sizeof(work));
//  memset(rwork, 0, sizeof(rwork));
//  cheev_("V", "U", &n, H, &lda, w, work, &lwork, rwork, &info);
//  
//  //cm_print("eigenvecter", (float *)H, order, order);
//  
//  // get the last eigen vector, it is just corresponding to the max eigenvalue
//  // note that the data is arranged in column major order
//  if(order == 8)
//  {
//    E1[0].r = H[56].r;   E1[0].i = H[56].i;    // r1
//    E1[1].r = H[57].r;   E1[1].i = H[57].i;    // r2
//    E1[2].r = H[58].r;   E1[2].i = H[58].i;    // r3
//    E1[3].r = H[60].r;   E1[3].i = H[60].i;    // r5
//    E1[4].r = H[61].r;   E1[4].i = H[61].i;    // r6
//    E1[5].r = H[62].r;   E1[5].i = H[62].i;    // r7
//  
//    E2[0].r = H[57].r;   E2[0].i = H[57].i;    // r2
//    E2[1].r = H[58].r;   E2[1].i = H[58].i;    // r3
//    E2[2].r = H[59].r;   E2[2].i = H[59].i;    // r4
//    E2[3].r = H[61].r;   E2[3].i = H[61].i;    // r6
//    E2[4].r = H[62].r;   E2[4].i = H[62].i;    // r7
//    E2[5].r = H[63].r;   E2[5].i = H[63].i;    // r8 
//  }
//  else if(order == 4)
//  {
//    E1[0].r = H[12].r;   E1[0].i = H[12].i;    // r1
//    E1[1].r = H[13].r;   E1[1].i = H[13].i;    // r2
//    E1[2].r = H[14].r;   E1[2].i = H[14].i;    // r3
//    
//    E2[0].r = H[13].r;   E2[0].i = H[13].i;    // r2
//    E2[1].r = H[14].r;   E2[1].i = H[14].i;    // r3
//    E2[2].r = H[15].r;   E2[2].i = H[15].i;    // r4
//  }
//}
//
//
//complex a[SVD_MAX];
//complex u[SVD_MAX*SVD_MAX];
//complex vt[1*1];
//real s[1];
//integer ipiv[1];

//  svd_inverse(float *E1, float *E1i)
//void svd_inverse(complex *E1, complex *E1i, int order)
//{
//  integer lda = order;
//  integer ldu = order;
//  integer ldvt = 1;
//  integer m = order;
//  integer n = 1;
//  integer lwork = order * 3;
//  integer info;
//
//  memcpy(a, E1, sizeof(a));
//  memset(u, 0, sizeof(u));  
//  memset(work, 0, sizeof(work));
//  memset(rwork, 0, sizeof(rwork));
//  cgesvd_("S", "A", &m, &n, a, &lda, s, u, &ldu, vt, &ldvt, work, &lwork, rwork, &info);
//  
//  printf("\nsvd info = %d\n", info);
//
//  for(n = 0; n < order; n ++)
//  {
//    E1i[n].r = u[n].r / s[0] * vt[0].r;
//    E1i[n].i = (-1) * u[n].i / s[0] * vt[0].r;
//  }
//}
//
//void final_multiply(complex *E1i, complex *E2, complex *Z, int order)
//{
//  integer m = 1;
//  integer n = 1;
//  integer k = order;
//  integer lda = order;
//  integer ldb = order;
//  integer ldc = 1;
//  complex alpha = {1, 0};
//  
//  memset(Z, 0, sizeof(complex));
//  cgemm_("T", "N", &m, &n, &k, &alpha, E1i, &lda, E2, &ldb, &alpha, Z, &ldc);
//}
complex H[EIGEN_MAX * EIGEN_MAX];
void rec_cov_spasmoo(const complex* rec, complex* cov_sm, int rx, int* array) {
	int i,j;
	for (i = 0; i < rx; ++i) {
		for (j = 0; j < rx; ++j) {
			H[i * rx + j].r = rec[array[i]].r * rec[array[j]].r + rec[array[i]].i * rec[array[j]].i;
			H[i * rx + j].i = -rec[array[i]].i * rec[array[j]].r + rec[array[i]].r * rec[array[j]].i;
		}
	}
	for (i = 0; i < rx * rx; ++i) {
		cov_sm[i].r = (H[i].r + H[rx * rx - 1 - i].r) / 2;
		cov_sm[i].i = (H[i].i - H[rx * rx - 1 - i].i) / 2;
	}
}
void noisespa_AOAH(complex* a, complex* u, complex* AU, int order, int* array) {
	float tempr, tempi;
	int i, j;
	for (i = 0; i < order - 2; ++i) {
		tempr = 0.f, tempi = 0.f;
		for (j = 0; j < order; ++j) {
			tempr = a[array[j]].r * u[i * order + j].r + a[array[j]].i * u[i * order + j].i + tempr;
			tempi = -a[array[j]].i * u[i * order + j].r + a[array[j]].r * u[i * order + j].i + tempi;
		}
		AU[i].r = tempr;
		AU[i].i = tempi;
	}

}

void mag2_recpc(complex* Z, float* S, int N) {
	float temp = 0.f;
	int i;
	for (i = 0; i < N; ++i)
	{
		temp = Z[i].r * Z[i].r + Z[i].i * Z[i].i + temp;
	}
	*S = 1 / temp;
}
int peak_max2(const float* SP, float* ind) {
	float max[200] = { 0 };
	float min = SP[1];
	int ind_[200] = { 0 };
	int ind_i = 0;
	int i, ind_dow;	
	for (i = 1; i <= 198; ++i)
	{
		if (min > SP[i])
			min = SP[i];
		ind_dow = 1;
		while (i + ind_dow <=199) {
			
			if (SP[i] == SP[i + ind_dow])
				ind_dow++;
			else
				break;
		}
		if (SP[i] > SP[i - 1] && SP[i] > SP[i + ind_dow]) {
			max[ind_i] = SP[i];
			ind_[ind_i] = i + floor(ind_dow / 2);
			ind_i++;
		}
	}
	float max1 = 0.f;
	float max2 = 0.f;
	//ind[0] = -999;
	//ind[1] = -999;
	for (i = 0; i < 200; ++i) {
		if (max[i] > max1) {
			max2 = max1;
			ind[1] = ind[0];
			max1 = max[i];
			//ind[0] = ind_[i];
			ind[0] = ((float)ind_[i]-100)/5;
		}
		else if (max[i] > max2) {
			max2 = max[i];
			//ind[1] = ind_[i];
			ind[1] = ((float)ind_[i]-100)/5;
		}
		if (max[i] == 0)
			break;
	}

	if (max1 > max2 * 10 && max1 > min*2)
		return 1;
	else if(max2 > min*2 && max1 > min*2)
		return 2;
	else
		return 0;
}