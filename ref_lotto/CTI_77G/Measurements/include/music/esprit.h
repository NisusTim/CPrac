
#ifndef __ESPRIT_H__
#define __ESPRIT_H__

#include <f2c.h>
//#include <clapack.h>
#include <stdint.h>
#define RX_ARRAY_SIZE       4
#define RX_CENTER           0       // 0,1,(2),3
#define EIGEN_UNIT          RX_ARRAY_SIZE
#define SVD_UNIT            (RX_ARRAY_SIZE - 1)
#define EIGEN_MAX           (EIGEN_UNIT * 2)
#define SVD_MAX             (SVD_UNIT * 2)
#define PRINT_FORMAT_CM	    "% 06.4f%+06.4fi  "
#define PRINT_FORMAT_RV     "% 06.4f  "
/*
#ifndef __ESPRIT_PRINT_C__
void dv_print(double *buffer, int size);
void zm_print(double *buffer, int row, int col);
void cm_print(char *title, float *buffer, int row, int col);
void rv_print(float *buffer, int size);
void enable_print();
void disable_print();
#endif
*/
#ifndef __ESPRIT_CORE_C__
//void rx_to_herm(complex *Rx, complex *H, int order);
//void herm_eigen(complex *H, complex *E1, complex *E2, int order);
//void svd_inverse(complex *E1, complex *E1i, int order);
//void final_multiply(complex *E1i, complex *E2, complex *Z, int order);
void rec_cov_spasmoo(const complex* rec, complex* cov_sm, int rx, int* array);
int peak_max2(const float* SP, float* ind);
void noisespa_AOAH(complex* a, complex* u, complex* AU, int order, int* array);
void mag2_recpc(complex* Z, float* S, int N);
#endif

#ifndef __ESPRIT_C__
// call before any esprit calculation
//void esprit_init(float, int);
//int MUSIC(int opts, complex* r, float* ind, float *SP);
int MUSIC(complex* r, float* ind);
//void AOAfun(int* ant_mat);
//void MUSIC(int M, int* arry, complex* r, int* AOAnum, float* ind);
// Rx    => input Rx data
// deg   => result angle in degree
// z     => result complex
// mode  => Tx operation mode
//void esprit(float *Rx, float *deg, float *z, int order);
//void esprit_1(float *Rx, float *deg, float *z);
#endif
/*
#ifndef __RX_CALIB_C__

void rx_calib(float *Rx, float *table, int order);
void rx_calib_int(int32_t *Rx_int, float *Rx, float *table, int order);
void rx_calib_1(float *Rx, float *table);
void rx_calib_1_int(int32_t *Rx_int, float *Rx, float *table);
void rx_calib_table_get(float *Rx, float *table, int order);
void rx_calib_table_get_int(int32_t *Rx_int, float *table, int order);
#endif
//*/
#endif /*__ESPRIT_H__*/


