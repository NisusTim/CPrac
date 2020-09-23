#ifndef _SPT_H_
#define _SPT_H_

/* --------------------------------------------------------------------------- 
|   SPT
|----------------------------------------------------------------------------- */  
#include "target.h"
#include "detections.h"
#include "event.h"
#define FFT_POINTS_PER_RX				(CHIRPS_PER_FRAME*SAMPLES_PER_CHIRP/2)

#define SIZE_OF_WORK_SPACE		0x10000
#define SIZE_OF_DOPPLER_DATA	0x80000
#define SIZE_OF_RANGE_DATA		0x80000
#define SIZE_OF_ADC_SAMPLES		0x100000
#define SIZE_OF_FFT3D_LOG2		0x40000
#define SIZE_OF_PEAKS_OVER_THLD	0x8000
#define SIZE_OF_HIST_BINS		0x8000

#define MAX_TONES_PER_RANGE		(SIZE_OF_PEAKS_OVER_THLD/(256*4))

#ifndef _SPT_C_
	extern uint16_t fft_data[18][FFT_POINTS_PER_RX];
#endif

/* Must be same value with CTI_77G.spt #define */
#define RANGE_DATA 				((uint32_t)fft_data)						// 0x40000000, 512KB
#define ADC_SAMPLES				(((uint32_t)fft_data)+0x8000)				// 0x40008000, 1MB
#define DOPPLER_DATA 			(((uint32_t)fft_data)+SIZE_OF_RANGE_DATA)	// 0x40080000, 512KB
#define WORK_SPACE 				((uint32_t)DOPPLER_DATA+SIZE_OF_DOPPLER_DATA)// 0x40100000, 64KB

#define DOPPLER_64x2 			((uint32_t)fft_data+0x40000)
#define WORK_SPACE_64x2 		((uint32_t)fft_data+0x80000)
#define FFT3D_LOG2_64x2 		RANGE_DATA									// 0x40000000, 128KB
#define HIST_BINS_64x2 			(RANGE_DATA+0x20000)						// 0x40020000, 32KB
#define PEAKS_OVER_THLD_64x2 	(HIST_BINS_64x2+0x8000)						// 0x40028000, 32KB
#define TARGET_AOA_64x2 		(PEAKS_OVER_THLD_64x2+0x8000)				// 0x40030000, 64KB
#define FFT3D_DEBUG_64x2 		(TARGET_AOA_64x2)							// 0x40030000, 64KB
#define PEAKS_DATA_64x2 		(WORK_SPACE_64x2+0xE000)

#define FFT3D_LOG2				RANGE_DATA									// 0x40000000, 256KB
#define HIST_BINS				(FFT3D_LOG2+SIZE_OF_FFT3D_LOG2)				// 0x40040000, 32KB
#define PEAKS_OVER_THLD			(HIST_BINS+SIZE_OF_HIST_BINS)				// 0x40048000, 32KB
#define FFT3D_DEBUG_DATA		(PEAKS_OVER_THLD+SIZE_OF_PEAKS_OVER_THLD)	// 0x40050000, 64KB
#define TARGET_AOA_DATA			(FFT3D_DEBUG_DATA)							// 0x40050000, 64KB
#define AOA_FFT_DATA			WORK_SPACE									// 0x40100000, 24KB
#define FFT16_DOPPLER_DATA		(WORK_SPACE+0x4000)							// 0x40106000, ~=36KB
#define PEAKS_DATA				(WORK_SPACE+0xE000)							// 0x4010E000, ~=8KB

#define SPT_DATA_PACK_16CMPX_READ	0x03
#define SPT_DATA_PACK_16CMPX_WRITE	0x01
#define SPT_DATA_PACK_24CMPX_READ	0x07
#define SPT_DATA_PACK_24CMPX_WRITE	0x05
#define SPT_DATA_PACK_24REAL_READ	0x0B
#define SPT_DATA_PACK_24REAL_WRITE	0x09
#define SPT_DATA_PACK_16REAL_READ	0x0F
#define SPT_DATA_PACK_16REAL_WRITE	0x0D
#define SPT_DATA_PACK_CP4D_READ		0x2F
#define SPT_DATA_PACK_CP4D_WRITE	0x2D

#define	TRAM_TWIDDLES_1024 		0x4000
#define TRAM_TWIDDLES_512 		0x4400
#define	TRAM_WINDOW_512 		0x4600
#define	TRAM_TWIDDLES_256 		0x4800
#define	TRAM_WINDOW_256 		0x4900
#define TRAM_TWIDDLES_128	 	0x4A00
#define	TRAM_WINDOW_128 		0x4A80
#define TRAM_TWIDDLES_64		0x4B00
#define	TRAM_WINDOW_64 			0x4B40
#define TRAM_TWIDDLES_16		0x4B80
#define TRAM_FFT3D_4R			0x4C00
#define TRAM_FFT3D_AMAP4		0x4C10
#define TRAM_FFT3D_AMAP8		0x4C18
#define TRAM_WORK_SPACE			0x4F00

#define DB_LOG2					3.0102999566f
#define SPT_LOG2DB(_log)		(((_log)>>8)*DB_LOG2 + ((_log)&0xFF)*(DB_LOG2/256))

typedef void (*spt_function_p)(void);

typedef enum {
	MEAS_ST_READY = 0,
	MEAS_ST_RAW,
	MEAS_ST_RANGE,
	MEAS_ST_FFTS,
	MEAS_ST_COMPLEXES,
	MEAS_ST_ANGLE,
	MEAS_ST_TEF810,
	MEAS_ST_ERROR,
	MEAS_ST_INVALID
}meas_state_e;

typedef enum {
	SPT_CONTEXT_FRAME_T1,				// 0 near range 1
	SPT_CONTEXT_FRAME_T2,				// 1 near range 2
	SPT_CONTEXT_FRAME_T3,				// 2 near range 3
	SPT_CONTEXT_FRAME_2TI,				// 3 long range interleaved
	SPT_CONTEXT_FRAME_64x2,				// 4
	SPT_CONTEXT_CLIPPING,				// 5
	SPT_CONTEXT_DCP4D_16K,				// 6
	SPT_CONTEXT_TARGETS_GET,			// 7
	SPT_CONTEXT_ANGLE_1024_8R,			// 8
	SPT_CONTEXT_ANGLE_1024_4R,			// 9
	SPT_CONTEXT_DOPPLER_NOISE_BASE_4R,	// 10
	SPT_CONTEXT_INVALID					// 11
}spt_context_e;

typedef enum {
	MEAS_MOD_RAW=0,			// 0
	MEAS_MOD_RANGE,			// 1
	MEAS_MOD_FFT,			// 2
	MEAS_MOD_FFT3D,			// 3
	MEAS_MOD_HIST,			// 4
	MEAS_MOD_COMPLEXES,		// 5
	MEAS_MOD_MEASUREMENTS,	// 6
	MEAS_MOD_TRACK,			// 7
	MEAS_MOD_INVALID,		// 8
}meas_mode_e;

typedef enum {
	TEF_NORMAL_MODE,
	TEF_CW_MODE
}tef_mode_e;

typedef struct st_spt_context{
	spt_function_p		sfp;
	int16_t				chirps;
	int8_t 				profile;
	int8_t				repeat;
	const char*			name;
}spt_context_t, *spt_context_p;

#define STEPS_OF_THLD			6
typedef struct {
	float 			aoa_sft[FRAME_CTXS_COUNT];
	float			aoa_coefs[FRAME_CTXS_COUNT];
	float			aoa_start[FRAME_CTXS_COUNT];
	float			aoa_end[FRAME_CTXS_COUNT];
	float			rng_near[2];
	float			rng_long[3];
	uint16_t		tcnts[FRAME_CTXS_COUNT];
	int16_t			thld_long[STEPS_OF_THLD];
	int16_t			thld_near[STEPS_OF_THLD];
	uint8_t			thld_bins[FRAME_CTXS_COUNT];
	int16_t			multi_chirp[FRAME_CTXS_COUNT];
	uint8_t			on[FRAME_CTXS_COUNT];
	uint8_t			ctxs[FRAME_CTXS_COUNT];
	uint16_t		mals,mcnt;
	uint16_t		haoa[4]; // 0: number, 1:subject speed, 2: min_dist(m), 3: max_dist(m)
	uint16_t		rate;
	uint16_t		flags;
    float           hsft;
    int16_t			asso_x[FRAME_CTXS_COUNT];	// actual gate is (10^-1)m of the value
    int16_t			asso_y[FRAME_CTXS_COUNT];	// actual gate is (10^-1)m of the value
    int16_t			asso_v[FRAME_CTXS_COUNT];	// actual gate is (10^-1)m/s of the value
}frame_info_t, *frame_info_p;

typedef struct{
	uint8_t datastage;
	void (*aoaprint)(uint8_t *, uint16_t);
}helios_intfc_t, *helios_intfc_p;


int SPT_exec(spt_function_p, int);
void spt_init(frame_info_p,event_proc_p,target_group_p);
void SPT_mapped(void);
void SPT_mem(uint8_t packing, uint16_t vsz, uint16_t spt, uint32_t sram);
spt_context_p spt_meas_start(spt_context_e context_id, event_proc_p);
spt_context_p spt_long_start(event_proc_p);
spt_context_p spt_near_start(event_proc_p);
//void spt_pthld_update(void);
void spt_mode_flags_get(uint32_t*,uint32_t*);
void spt_mode_flags_set(uint32_t mode, uint32_t flags);
void spt_aoas_misc_set(void);
void spt_mchp_velo_thld_set(void);

tef_mode_e spt_context_start(spt_context_e, event_proc_p, void*);
uint32_t spt_txrx_test(int tx, event_proc_p);
retval_e spt_action_start(spt_context_e ctxid);
#if RMTP_NOISE_BASE
meas_state_e spt_noise_base_get(uint8_t sample_times, float TxChannel_noise[3][4]);
#endif
meas_state_e spt_doppler_get_by_tx_channel(spt_context_e idx, float rng, event_proc_p cb);
meas_state_e spt_doppler_get(FRAME_CTX_IDX_E idx, float rng, event_proc_p cb);
void spt_thlds_set(int);
void spt_debug_reg(event_proc_p fft3d, event_proc_p aoa);
void spt_switch_tggs(target_group_p from_tggs_buff);
uint8_t spt_profileId_to_SptContextsId(uint8_t profile);
void* spt_work_space_get(void);
void* spt_fft_data_get(void);
target_group_p spt_target_group_get(int idx);
float spt_log2db(uint16_t);

retval_e spt_vertical_feedback_mode(float bw, float hpf);
void spt_resume_to_normal_mode(void);

void get_Detection_Lib_version(char* ver32b);
helios_intfc_p get_HES_INTFC_Handler(void);

#endif /* _SPT_H_ */
