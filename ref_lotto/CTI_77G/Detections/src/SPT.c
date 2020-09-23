#define _SPT_C_

#include "sys_shared.h"
#include "spt.h"
#include "coefs.h"
#include "custom_math.h"
#include "LibVer.h"

#if JSON_LIST_EN
#include "json_frame_info.h"
#include "json_meas_list.h"
#endif

#define HIST_DEBUG_ON	0

extern void SPT_WAIT_CHIRP_DONE(void);
extern void SPT_FRAME_2TI(void);
extern void SPT_FRAME_1T(void);
extern void SPT_FRAME_64x2(void);
extern void SPT_DCP4D_16K(void);
extern void SPT_DCP4D_TARGETS(void);
extern void SPT_ANGLE_1024_8R_BEAM(void);
extern void SPT_ANGLE_1024_4R(void);
extern void SPT_TRAM_INIT(void);
extern void SPT_4R_DOPPLER_NOISE_BASE(void);

static void spt_ffts_done(target_group_p tgg);
static void spt_doppler_test_done(void* d);
static void spt_fft_angle(target_group_p);
static void spt_targets_complexes_get(target_group_p);
static void spt_targets_complexes_done(target_group_p);
static void spt_angle_from_fft_peaks_long(target_group_p);
static void spt_angle_from_fft_peaks_near(target_group_p);
static void SPT_dump_status(void);
static void SPT_dump_wrs(int, int);
static void spt_watches(char**, int);

const LIBS_VER_T __attribute__((section(".library_version"))) Detection_version =  {
		.id =          VER_ID          (DETECTION_LIB_VER),
		.major =       VER_MAJOR       (3),
		.minor =       VER_MINOR       (3),
		.build =       VER_BUILD       (Lib_BUILD_RELEASE),
		.maintenance = VER_MAINTENANCE (1)
};

/* shared memory allocation*/
int16_t 		__attribute__((section(".fftdata"))) fft_data[17][FFT_POINTS_PER_RX];

spt_context_t spt_contexts[] = {
		{SPT_FRAME_1T, CHIRPS_PER_FRAME*2, TEF810X_T1, 1, "f1"},			// 0
		{SPT_FRAME_1T, CHIRPS_PER_FRAME*2, TEF810X_T2, 1, "f2"},			// 1
		{SPT_FRAME_1T, CHIRPS_PER_FRAME*2, TEF810X_T3, 1, "f3"},			// 2
		{SPT_FRAME_2TI, CHIRPS_PER_FRAME*2, TEF810X_T2T3, 1, "f23"}, 		// 3
		{SPT_FRAME_64x2, CHIRPS_PER_FRAME, TEF810X_T2T3, 1, "f64"}, 		// 4
		{SPT_WAIT_CHIRP_DONE, 1, TEF810X_RSSI, 1, "clp"},					// 5
		{SPT_DCP4D_16K, 0, -1, 0, "dcp"},									// 6
		{SPT_DCP4D_TARGETS, 0, -1, 0, "dc8"},								// 7
		{SPT_ANGLE_1024_8R_BEAM, 0, -1, 0, "a8r"},							// 8
		{SPT_ANGLE_1024_4R, 0, -1, 0, "a4r"},								// 9
		{SPT_4R_DOPPLER_NOISE_BASE, 0, -1, 0, "nb"}							// 10
};

#define QUE_SIZE_OF_CTXS_NAME	16
typedef struct {
	spt_context_p			ctx;
	event_proc_p			done_cb;
	void*					done_data;
	event_proc_p			rf_cb;
	target_group_p			tggs;
	uint32_t				time;
	uint32_t				status0;
	uint32_t				aoa_time;
	//int16_t					adc_shifts[FRAME_CTXS_COUNT];
	//int16_t					fft_shifts[FRAME_CTXS_COUNT];
	//int						adc_maxs[FRAME_CTXS_COUNT];
	float 					mchp_velo_thld;
	uint8_t					chirp_time_toggles;
} spt_handle_t, *spt_handle_p;

enum {
	SPT_FBMS_STATE_INIT = 0,
	SPT_FBMS_STATE_RAWS,		// 1
	SPT_FBMS_STATE_FFTS,		// 2
	SPT_FBMS_STATE_3DFFT,		// 3
	SPT_FBMS_STATE_HIST,		// 4
	SPT_FBMS_STATE_DONE			// 5
};

typedef struct _aoas_misc {
	//float start, end;
	float sft;
}aoas_misc_t,*aoas_misc_p;

#define DEFAULT_MEAS_MODE				MEAS_MOD_TRACK
#define DEFAULT_MEAS_FLAGS				0

static spt_handle_t spt_handler={0}, *spt = &spt_handler;
static rf_configs_t rf_cfgs;
static float lambda = 3.9188;
static frame_info_p frame_info = NULL;
static event_proc_p fft3d_logger = NULL;
static event_proc_p aoa_logger = NULL;
static uint16_t	hist_peaks[2][SAMPLES_PER_CHIRP/2] = {{0},{0}};
static uint16_t	hist_thlds[2][SAMPLES_PER_CHIRP>>4] = {{0},{0}};
static aoas_misc_t	aoas_misc[FRAME_CTXS_COUNT] = {{0},{0}};
static helios_intfc_t hes_intfc = {0};
helios_intfc_p hes_intfc_p= &hes_intfc;

static const char*		ctxs_log[QUE_SIZE_OF_CTXS_NAME]={NULL};
static const char*		*ctxs_head=ctxs_log;

void* spt_work_space_get(void){return (void*)WORK_SPACE;}
void* spt_fft_data_get(void){return (void*)fft_data;}
target_group_p spt_target_group_get(int idx){return (target_group_p)&spt->tggs[idx];}

static void spt_vertical_feedback_set(void);

//=============================================================================
// SPT CONFIGURATION
//=============================================================================
retval_e SPT_cfg(uint32_t samples_per_chirp, uint32_t chirps_per_frame)
{
	SPT.CS_STATUS0.R = 0xFFFFFFFF;     // reset all status register
	SPT.CS_STATUS1.R = 0xFFFFFFFF;

	MCB.MISC2.R = 0x00000000;          // set nexus PDMA and CS-DMA throttle 0 (no throttle)

	MCB.NPC_SPECIAL_ENABLE.R = 0x00002800;     // set nexus water-mark level 2, keep nexus FIFO depth 8 (always!), keep special functionality enabled => (optimal for 4 channel tracing - see AN5123)
	MCB.MISC1.R = 0x00000030;                  // set OUT_CTE and IN_CTE to HSYNC/VSYNC from MIPI-CSI

	SPT.ACQ_GBL_CTRL_0.R = 0x00558000;         // acquisition source is MIPI/CSI, enable ADC A,B,C,D (no swap) in global acquisition control register
	SPT.ACQ_CSI_CTRL.R = 0x00000001;           // 10 MSPS, calibration channel off, real input data, interleaved input mode

	SPT.SDMA_CTRL0.R = (uint32_t)ADC_SAMPLES; 			// assign SDADC sample buffer as SDMA start address
	SPT.SDMA_CTRL1.B.SDMA_BUF_LEN = 256;    	// SDMA buffer length
	SPT.SDMA_CTRL1.B.HMASTER_ENC_DIS = 0;       // Duplicate AHB Master-ID not generated
	SPT.SDMA_CTRL1.B.DATA_ORG_CFG = 0x2;        // Tile 8 mode

	SPT.PDMA_CONTROL.R = 0x00200004;            // set PDMA burst size 8 (optimal for 4 channel tracing - see AN5123)
	SPT.ACQ_GBL_CTRL_1.B.NUM_CHRP = chirps_per_frame;        // number of chirps per frame
	SPT.ACQ_GBL_CTRL_1.B.NUM_SMPL = (samples_per_chirp / 8) - 1;    // samples per chirp: (NUM_SMPL + 1) * 8
                                                                    // initialize program start address register with init instruction set array
	SPT.GBL_CTRL.R = 0x0B;       				// enable SPT, acquisition enable

	return SUCCESS;
}

void SPT_init(void)
{
    SPT_cfg(SAMPLES_PER_CHIRP, CHIRPS_PER_FRAME);

    SPT.CS_STATUS0.R = 0xFFFFFFFF;       // RESET all CS status

    SPT.CS_PG_ST_ADDR.R = (uint32_t) SPT_TRAM_INIT;     // Address of command list

    SPT.GBL_CTRL.B.PG_ST_CTRL = 0x1;            // Start SPT program - SPT enabled prior

    while ((SPT.CS_STATUS0.R & 0x8) != 0x8); 	// Wait until SPT finished commands

	INTC.PSR[734].R = 0x8001; //set priority and core for IRQ0 interrupt
	//INTC.PSR[735].R = 0x8001; //set priority and core for IRQ1 interrupt
	INTC.PSR[736].R = 0x8001; //set priority and core for ECS interrupt
	INTC.PSR[737].R = 0x8001; //set priority and core for DMA interrupt

	SPT.CS_STATUS0.R = 0xFFFFFFFF;
    SPT.CS_INTEN0.B.PS_STOP_INTEN = 1;
    //SPT.MEM_ERR_INT_EN.R = 0xFFFFFFFF;
    //SPT.CS_INTEN1.R=0xFFFFFFF;
    SPT.DMA_ERR_INT_EN.R = 0xFFFFFFFF;

    /*
     * bit0: Doppler starting
     * bit1: RF done
     * bit2: 3DFFT Debug
     * bit3: HIST
     * bit4: PEAKS COUNT
     * bit5: na
     * bit6: LR aoa
     * bit7: SR aoa
     */

    SPT.CS_EVT1_INTEN.B.EVT1_INTEN = 0xDE;
}

void spt_init(frame_info_p info, event_proc_p rf_done, target_group_p tggs)
{
	SPT_init();
	MEAS_MOD_WR = DEFAULT_MEAS_MODE;
	MEAS_FLAGS_WR = DEFAULT_MEAS_FLAGS;
	frame_info = info;
	spt->rf_cb = rf_done;
	spt->tggs = tggs;
	//spt_pthld_update();
	//console_command_reg("watch", spt_watches);
	spt_thlds_set(FRAME_CTX_IDX_NEAR);
	spt_thlds_set(FRAME_CTX_IDX_LONG);
	spt_aoas_misc_set();
	spt_mchp_velo_thld_set();
	console_command_reg("meas", spt_watches);

	//PRINTF("spt: velo rng from %d to %d\n", VELOCITY_INPUT_MAX+1+spt_info->vrs_value-VELOCITY_INPUT_PRECISION, VELOCITY_INPUT_MAX+spt_info->vrs_value);
}

void spt_aoas_misc_set(void)
{
	//aoas_misc[FRAME_CTX_IDX_NEAR].start = RADIAN_OF_DEGREE(frame_info->aoa_start[FRAME_CTX_IDX_NEAR]);
	//aoas_misc[FRAME_CTX_IDX_NEAR].end = RADIAN_OF_DEGREE(frame_info->aoa_end[FRAME_CTX_IDX_NEAR]);
	aoas_misc[FRAME_CTX_IDX_NEAR].sft = RADIAN_OF_DEGREE(frame_info->aoa_sft[FRAME_CTX_IDX_NEAR]);
	//aoas_misc[FRAME_CTX_IDX_LONG].start = RADIAN_OF_DEGREE(frame_info->aoa_start[FRAME_CTX_IDX_LONG]);
	//aoas_misc[FRAME_CTX_IDX_LONG].end = RADIAN_OF_DEGREE(frame_info->aoa_end[FRAME_CTX_IDX_LONG]);
	aoas_misc[FRAME_CTX_IDX_LONG].sft = RADIAN_OF_DEGREE(frame_info->aoa_sft[FRAME_CTX_IDX_LONG]);
	//CORE_DEBUG("aoas:[[%.5f,%.5f,%.5f],[%.5f,%.5f,%.5f]]\n",
			//aoas_misc[FRAME_CTX_IDX_NEAR].start,aoas_misc[FRAME_CTX_IDX_NEAR].end,aoas_misc[FRAME_CTX_IDX_NEAR].sft,
			//aoas_misc[FRAME_CTX_IDX_LONG].start,aoas_misc[FRAME_CTX_IDX_LONG].end,aoas_misc[FRAME_CTX_IDX_LONG].sft);
}

void spt_mode_flags_set(uint32_t mode, uint32_t flags)
{
	if(mode != 0xFFFFFFFF)
		MEAS_MOD_WR = mode;

	if(flags != 0xFFFFFFFF) {
		MEAS_FLAGS_WR = flags;
	}
	PRINTF("meas: mod=%04lX,flags=%04lX\n", MEAS_MOD_WR, MEAS_FLAGS_WR);
}

void spt_mode_flags_get(uint32_t* mode, uint32_t* flags)
{
	if(mode != NULL)
		*mode = MEAS_MOD_WR;

	if(flags != NULL)
		*flags = MEAS_FLAGS_WR;
}

void spt_switch_tggs(target_group_p from_tggs_buff)
{
	spt->tggs = from_tggs_buff;
}

spt_context_p spt_meas_start(spt_context_e ctxid, event_proc_p done)
{
	target_group_p tgg = spt->tggs;
	if(ctxid >= SPT_CONTEXT_FRAME_2TI)
		tgg = tgg+1;

	if(done != NULL)
		tgg->done = done;

	tgg->vbins = spt_contexts[ctxid].chirps;
	if(TEF_CW_MODE==spt_context_start(ctxid, (event_proc_p)spt_ffts_done, (void*)tgg)){
	    return NULL;
	}
	    
	return spt_contexts+ctxid;
}

spt_context_p spt_long_start(event_proc_p done)
{
	return spt_meas_start(frame_info->ctxs[FRAME_CTX_IDX_LONG], done);
}

spt_context_p spt_near_start(event_proc_p done)
{
	return spt_meas_start(frame_info->ctxs[FRAME_CTX_IDX_NEAR], done);
}

/*
 * spt_start_frame()
 * tn : 0=T1(128), 1=T2(128), 3=T3(128), 4=T1T2 interleaved(256), others=T1T2(128,128)
 */
tef_mode_e spt_context_start(spt_context_e ctxid, event_proc_p done_cb, void* done_data)
{
	spt_context_p ctx;
	int8_t profile;
	if (ctxid >= SPT_CONTEXT_INVALID) {
		PRINTF("Invalid spt context!\n");
		return TEF_NORMAL_MODE;
	}

	ctx = &spt_contexts[ctxid];

	spt->done_cb = done_cb;
	spt->done_data = done_data;
	spt->ctx = ctx;
	spt->time = STM_0.CNT.R;

	profile = ctx->profile;
	if(ctx->chirps >= CHIRPS_PER_FRAME) {
		SPT.WR_R4_RE.R = ctx->chirps;
		if(MEAS_FLAGS_WR & MEAS_FLAG_FROM_RAWS){
			profile = -1;
		}

		SPT.WR_R4_IM.R = 0;
	}

	CORE_DEBUG("spt:%s,tgg(%p)\n", ctx->name,spt->done_data);
	*ctxs_head++ = ctx->name;
	if(ctxs_head == &ctxs_log[QUE_SIZE_OF_CTXS_NAME])
		ctxs_head = ctxs_log;

	if(SPT_exec(ctx->sfp, FALSE) == FALSE)
		return TEF_NORMAL_MODE;

	if(profile != -1){
		CORE_DEBUG("spt:rfp %d\n", ctx->profile);
		while(SPT.CS_STATUS0.B.PS_WAIT == 0);
		if(NULL==TEF810x_chirp_start(ctx->profile, ctx->chirps, ctx->repeat)){
			return TEF_CW_MODE;
		}
	}
	return TEF_NORMAL_MODE;
}

static void spt_ctxs_dump(void)
{
	const char* *ctxs_tail = ctxs_head;

	if(*ctxs_tail == NULL)
		return;

	PRINTF("spt: ctxs[%s,",*ctxs_tail++);
	if(ctxs_tail == &ctxs_log[QUE_SIZE_OF_CTXS_NAME])
		ctxs_tail = ctxs_log;

	while(ctxs_tail != ctxs_head){

		if(*ctxs_tail == NULL)
			break;

		PRINTF("%s,", *ctxs_tail);
		ctxs_tail++;
		if(ctxs_tail == &ctxs_log[QUE_SIZE_OF_CTXS_NAME])
			ctxs_tail = ctxs_log;
	}
	PRINTF("\b]\n");
}

uint32_t spt_txrx_test(int tx, event_proc_p dcb)
{
	if(tx < 3) {
		MEAS_MOD_WR = MEAS_MOD_RAW;
		spt_context_start(tx, dcb, NULL);
		return ADC_SAMPLES;
	}
	return -1;
}

/*
 * Fix high-speed on-coming ghost due HW's signal phase wrong place
 * Jira : ticket-141, High speed oncoming ghost on my lane
 */
void spt_mchp_velo_thld_set(void)
{
	float idle = frame_info->multi_chirp[FRAME_CTX_IDX_LONG], ct=26.3;
	get_rf_profile_config(TEF810X_T2T3, &rf_cfgs);
	ct = rf_cfgs.chirp_time;
	lambda = LIGHT_SPEED/rf_cfgs.freq;
	spt->mchp_velo_thld  = 1.45*250000*lambda*idle/(ct*ct+ct*idle); // m/s => half of max speed = lambda/(2*2T)
	PRINTF("mchp: lambda=%.4fmm, thld=%.2fm/s\n",lambda*1000,spt->mchp_velo_thld);
}

float multi_chirp_time_get(void)
{
	#define MULTI_SPD_MY_SPD_HYST			0.6
	typedef enum {
		MCHP_ST_LOW = 0,
		MCHP_ST_HIGH
	}MCHP_ST_E;

	static MCHP_ST_E mchp_st = MCHP_ST_LOW;
	float idle = frame_info->multi_chirp[FRAME_CTX_IDX_LONG];
	float my_spd = get_eps_speed_value() * KPH_TO_MS; // m/s

	if(mchp_st == MCHP_ST_LOW){
		if(spt->chirp_time_toggles)
			idle += (idle+3);
		else
			idle = 0;
		if(my_spd >= (spt->mchp_velo_thld+MULTI_SPD_MY_SPD_HYST))
			mchp_st = MCHP_ST_HIGH;
	}
	else {
		if(spt->chirp_time_toggles)
			idle = 0;
		if(my_spd < (spt->mchp_velo_thld-MULTI_SPD_MY_SPD_HYST))
			mchp_st = MCHP_ST_LOW;
	}
	CORE_DEBUG("mchp: LR[%d,%d],[%.1f,%.2f,%.1f]\n",mchp_st,spt->chirp_time_toggles, my_spd, spt->mchp_velo_thld, idle);
	return idle;
}

void spt_multi_chirps(target_group_p tgg, float ct)
{
	if(frame_info->multi_chirp[tgg->idx]){
		int idle;
		if(tgg->idx == FRAME_CTX_IDX_LONG){
			idle = multi_chirp_time_get();
			chg_Tef810x_profile_idle_time(0,idle);
			chg_Tef810x_profile_idle_time(1,idle);
			spt->chirp_time_toggles = (spt->chirp_time_toggles+1)%2;
		}
		else{
			idle = frame_info->multi_chirp[FRAME_CTX_IDX_NEAR]*spt->chirp_time_toggles;
			chg_Tef810x_profile_idle_time(2,idle);
			CORE_DEBUG("mchp: tgg[%d]=[%u,%d]\n",tgg->idx, spt->chirp_time_toggles, idle);
			if(frame_info->on[FRAME_CTX_IDX_LONG]==0)
				spt->chirp_time_toggles = (spt->chirp_time_toggles+1)%2;
		}
	}
}


/*static void spt_adc_shifts(target_group_p tgg)
{
	int maxs[4];
	maxs[0] = (int16_t)SPT.ACQ_STATUS_A1.B.CH_A_MAX-(int16_t)SPT.ACQ_STATUS_A1.B.CH_A_MIN;
	maxs[1] = (int16_t)SPT.ACQ_STATUS_B1.B.CH_B_MAX-(int16_t)SPT.ACQ_STATUS_B1.B.CH_B_MIN;
	maxs[2] = (int16_t)SPT.ACQ_STATUS_C1.B.CH_C_MAX-(int16_t)SPT.ACQ_STATUS_C1.B.CH_C_MIN;
	maxs[3] = (int16_t)SPT.ACQ_STATUS_D1.B.CH_D_MAX-(int16_t)SPT.ACQ_STATUS_D1.B.CH_D_MIN;
	if(maxs[0] < maxs[1])
		maxs[0] = maxs[1];
	if(maxs[0] < maxs[2])
		maxs[0] = maxs[2];
	if(maxs[0] < maxs[3])
		maxs[0] = maxs[3];

	SPT.WR_R5_RE.R = 5;
	maxs[1] = 0xC000;
	while(SPT.WR_R5_RE.R <= 10) {
		if(maxs[0] & maxs[1])
			break;
		SPT.WR_R5_RE.R += 1;
		maxs[1] >>= 1;
	}
	SPT.CS_SW_EVTREG.B.SW_EVTREG = 1<<2;
	spt->adc_maxs[tgg->idx] = maxs[0];
	spt->adc_shifts[tgg->idx] = SPT.WR_R5_RE.R;
}

static void spt_fft_shifts(target_group_p tgg)
{
	int bits = 0x800000;
	SPT.WR_R5_RE.R = 0;
	spt->fftmax = SPT.WR_R6_RE.R;
	while(bits > 0x800) {
		if(bits & spt->fftmax)
			break;
		SPT.WR_R5_RE.R += 1;
		bits >>= 1;
	}
	SPT.WR_R5_RE.R -= 1;
	spt->fft_shifts[tgg->idx] = SPT.WR_R5_RE.R;
	SPT.CS_SW_EVTREG.B.SW_EVTREG = 1<<2;
}*/

static void spt_rf_done(target_group_p tgg)
{
	float *rng_bound = frame_info->rng_near;

	if(tgg->state != TGG_ST_READY){
		PRINTF("rfd: tgg(%d) not ready(%d), SPT skipped\n",tgg->idx,tgg->state);
		spt->done_cb = NULL;
		SPT.CS_MODE_CTRL.B.STOP = 1;
		tgg->tcnt = 0;
		tgg->state = TGG_ST_READY;
		tgg->done(tgg);
		return;
	}

	get_rf_config(&rf_cfgs);
	tgg->time = STM_0.CNT.R;
	tgg->runit = (float)(LIGHT_SPEED*0.5/rf_cfgs.bw);
	tgg->vunit = (float)((500000*lambda)/(spt->ctx->chirps*rf_cfgs.chirp_time)); // mps not kph
	tgg->state = TGG_ST_FFTS;

	if(spt->rf_cb)
		spt->rf_cb(tgg);

	if(tgg->rcnt == TOTAL_RX_ACTIVES)
		rng_bound = frame_info->rng_long;

	tgg->end = (uint16_t)(rng_bound[1]/tgg->runit);
	tgg->start = (uint16_t)(rng_bound[0]/tgg->runit);
	if(tgg->start == 0)
		tgg->start = 1;

	if(tgg->start >= (SAMPLES_PER_CHIRP/4) || tgg->end >= (SAMPLES_PER_CHIRP/2))
		PRINTF("spt:rng err %d~%d!\n", tgg->start, tgg->end);

	if(tgg->idx == FRAME_CTX_IDX_LONG){

		if(tgg->end >= (SAMPLES_PER_CHIRP/2))
			tgg->end = SAMPLES_PER_CHIRP/2;

		tef_vco_check();
//		if(frame_info->on[FRAME_CTX_IDX_NEAR] == 0)
		tef_safety_check(NULL,0);
#if JSON_LIST_EN
		send_long_range_rf_data_to_frame_info(rf_cfgs.txgain, rf_cfgs.rxgain, (float)rf_cfgs.chirp_time);
#endif
	}
	else {
		if(tgg->end >= (SAMPLES_PER_CHIRP/4))
			tgg->end= SAMPLES_PER_CHIRP/4;

//		tef_safety_check(NULL,0);
#if JSON_LIST_EN
		send_short_range_rf_data_to_frame_info(rf_cfgs.txgain, rf_cfgs.rxgain, (float)rf_cfgs.chirp_time);
		send_short_range_rf_data_to_meas_list(tgg);
#endif
	}

	PRINTF("bw=%.fM,tg=%d,rg=%d,%d~%d,ct=%.1f,ru=%.2f,vu=%.5f\n",
		(float)rf_cfgs.bw/1000000, rf_cfgs.txgain, rf_cfgs.rxgain,tgg->start,tgg->end,
		(float)rf_cfgs.chirp_time, tgg->runit,tgg->vunit);

	spt_multi_chirps(tgg, rf_cfgs.chirp_time);
	spt_vertical_feedback_set();
}

void spt_debug_reg(event_proc_p fft3d,event_proc_p aoa)
{
	fft3d_logger = fft3d;
	aoa_logger = aoa;
}

float spt_log2db(uint16_t log2)
{
	float db = (log2>>8)*3.01f;
	log2 &= 0xFF;
	db += (((float)log2/256)*3.01);
	return db;
}

static uint16_t spt_10xdb2log(int16_t db)
{
	return (uint16_t)((db/30.1f)*256);
}

void spt_thlds_set(int idx)
{
	int16_t j = 0, k = frame_info->thld_bins[idx], l=0;
	int16_t thld, *thlds, bin_steps;
	if (idx == FRAME_CTX_IDX_LONG){
		thlds = frame_info->thld_long;
		bin_steps = SAMPLES_PER_CHIRP>>4;
	}
	else{
		thlds = frame_info->thld_near;
		bin_steps = SAMPLES_PER_CHIRP>>5;
	}

	thld = spt_10xdb2log(thlds[l]);

	for(int i=0; i < bin_steps; i++){
		j = i<<3;
		if(j >= k && l < (STEPS_OF_THLD-1)) {
			k = k+frame_info->thld_bins[idx];
			l++;
			thld = spt_10xdb2log(thlds[l]);
		}
		hist_thlds[idx][i] = thld;
	}
}

typedef struct {
	int16_t idx;
	uint16_t val;
}peak_value_t, *peak_value_p;
static void hist_threshold(target_group_p tgg)
{
	uint32_t offs = SPT.WR_R33_IM.R>>10;
	uint16_t *hist = (uint16_t*)(HIST_BINS+SPT.WR_R33_IM.R);
	peak_value_p peak = (peak_value_p)PEAKS_DATA;
	uint16_t idx = peak->idx;

	if((frame_info->flags & FRAME_FLAG_HIST_THLD_PEAK) == 0){
		while(idx < 64){
			if(hist[idx] == 0)
				break;
			idx++;
		}
	}

	SPT.WR_R47_RE.R = (idx<<8)+hist_thlds[tgg->idx][offs];
	hist_peaks[tgg->idx][SPT.WR_R33_IM.R>>7] = SPT.WR_R47_RE.R;

#if HIST_DEBUG_ON
	PRINTF("\nhist(%ld):peak(%d,%02X),idx=%d,thld=%04lX\n",SPT.WR_R33_IM.R>>7,
			peak->idx,peak->val,idx, SPT.WR_R47_RE.R);

	if(fft3d_logger != NULL) {
		PRINTF("%08lX %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
				(uint32_t)hist,hist[0],hist[1],hist[2],hist[3],hist[4],hist[5],hist[6],hist[7],
				hist[8],hist[9],hist[10],hist[11],hist[12],hist[13],hist[14],hist[15]);
		hist += 16;
		PRINTF("%08lX %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
				(uint32_t)hist,hist[0],hist[1],hist[2],hist[3],hist[4],hist[5],hist[6],hist[7],
				hist[8],hist[9],hist[10],hist[11],hist[12],hist[13],hist[14],hist[15]);
		hist += 16;
		PRINTF("%08lX %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
				(uint32_t)hist,hist[0],hist[1],hist[2],hist[3],hist[4],hist[5],hist[6],hist[7],
				hist[8],hist[9],hist[10],hist[11],hist[12],hist[13],hist[14],hist[15]);
		hist += 16;
		PRINTF("%08lX %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
				(uint32_t)hist,hist[0],hist[1],hist[2],hist[3],hist[4],hist[5],hist[6],hist[7],
				hist[8],hist[9],hist[10],hist[11],hist[12],hist[13],hist[14],hist[15]);
	}
#endif
	SPT.CS_SW_EVTREG.B.SW_EVTREG = 1<<2;
}

typedef struct {
	peak_value_t vals[SAMPLES_PER_CHIRP/2][MAX_TONES_PER_RANGE];
}tones_peak_t, *tones_peaks_p;
static void spt_tones_get(target_group_p tgg)
{
	tones_peaks_p tps = (tones_peaks_p)PEAKS_OVER_THLD;
	peak_value_p pv;
	uint16_t rng = tgg->start;
	uint16_t lsr = 0;
	target_p tg = tgg->targets;

	tgg->tcnt = 0;
	if(tgg->idx == FRAME_CTX_IDX_LONG){
		lsr = (uint16_t)(frame_info->rng_long[2]/tgg->runit);
		if(lsr)
			rng = 1;
	}

	while(rng < tgg->end) {
		pv = tps->vals[rng];
		while(pv < tps->vals[rng+1]){
			if(!pv->val){
				break;
			}

			tg->range = rng;
			tg->velocity = pv->idx>>1;
			tg->mag_log2 = pv->val;

			if(tgg->rcnt == TOTAL_RX_ACTIVES) {
				int v = tg->velocity-(CHIRPS_PER_FRAME/2);

				if(v >= CHIRPS_PER_FRAME)
					v -= CHIRPS_PER_FRAME;
				else if(v < 0)
					v += CHIRPS_PER_FRAME;

				tg->pos = (tgg->vbins/2) * rng + v;
			}
			else {
				tg->pos = tgg->vbins * rng + tg->velocity;
			}

			if(tg->range >= lsr || tg->velocity == (tgg->vbins>>1) || (frame_info->flags & FRAME_FLAG_STANDING_LSR)==0){
				tgg->tcnt++;
				tg++;
				if(tgg->tcnt >= frame_info->tcnts[tgg->idx]){
					PRINTF("tgg[%d]: target list full\n",tgg->idx);
					return;
				}
			}

			pv++;
		}

		if(rng < lsr || rng >= tgg->start)
			rng++;
		else
			rng = tgg->start;
	}
	//PRINTF("tgg[%d]:tcnt=%d\n", tgg->idx, tgg->tcnt);
}


static void spt_ffts_done(target_group_p tgg)
{
	CORE_DEBUG("ffts(%d):tgg(%p,%d),time=%.2fms\n",tgg->idx,tgg,tgg->state,(float)spt->time*0.000016667f);

	if(MEAS_MOD_WR >= MEAS_MOD_COMPLEXES && SPT_FBMS_STATE_WR == SPT_FBMS_STATE_HIST){
		tgg->state = TGG_ST_FFTS_DONE;
		spt_tones_get(tgg);
		spt_targets_complexes_get(tgg);
	}
	else {
		tgg->done(tgg);
		tgg->state = TGG_ST_READY;
	}
}


static void spt_targets_complexes_get(target_group_p tgg)
{
	if(tgg == NULL){
		PRINTF("spt: NULL tgg to get complexes!\n");
		return;
	}

	CORE_DEBUG("spt:tgg(%p,%d),dc8(%d,%d)!\n", tgg, tgg->state, tgg->idx, tgg->tcnt);

	if(tgg->tcnt == 0) {
		tgg->state = TGG_ST_READY;
		tgg->done(tgg);
		return;
	}

	if (tgg->state <= TGG_ST_FFTS_DONE){
		tgg->start = 0;
		tgg->end = MAX_COMPLEXES_CAN_GET;
		tgg->state = TGG_ST_COMPLEX;
	}
	else if(tgg->state == TGG_ST_COMPLEX){
		tgg->start = tgg->end;
		tgg->end = tgg->start+MAX_COMPLEXES_CAN_GET;
	}
	else {
		PRINTF("tgg[%d]: invalid state(%d) to get cmplxes(%d)\n", tgg->idx, tgg->state, tgg->tcnt);
		return;
	}

	if(tgg->end > tgg->tcnt)
		tgg->end = tgg->tcnt;

	//PRINTF("tgg[%d]: cmplxes(%d:%d),cnt=%d\n", tgg->idx, tgg->start,tgg->end, tgg->tcnt);

	int idx = 0, end = tgg->end-tgg->start;
	target_p tg = tgg->targets+tgg->start;
	spt_work_reg_p wr = (spt_work_reg_p)&(SPT.WR_R0_RE.R);
	wr->re = 0x8000;
	wr->im = 0;
	wr++;

	while(idx < end){
		wr->im = (tg->pos&0xFFFC)*2;
		wr->re = (0x8000)+idx*64;
		wr++;
		idx++;
		tg++;
	}
	wr->im=0xFFFFFF;
	wr->re=0xFFFFFF;

	spt_context_start(SPT_CONTEXT_TARGETS_GET, (event_proc_p)spt_targets_complexes_done, (void*)tgg);
}

static void spt_targets_complexes_done(target_group_p tgg)
{
	int cnt = 0, idx=0, end = tgg->end-tgg->start;

	if(tgg == NULL){
		PRINTF("spt:can't get complexes w/o target group!\n");
		return;
	}

	CORE_DEBUG("tgg:%p,cpx %d:%d,cnt=%d\n", tgg, tgg->idx, tgg->state, tgg->tcnt);

	target_p tg = tgg->targets+tgg->start;
	complex24_p tc = (complex24_p)WORK_SPACE, src, dest;

	while(cnt < end){

		dest = tg->cmplx;
		src = &tc[cnt*64+(tg->pos&0x3)];

		idx = 0;
		while (idx < tgg->rcnt) {
			dest[idx] = *src;
			src += 8;
			idx++;
		}
		cnt++;
		tg++;
	}

	if(tgg->end < tgg->tcnt)
		spt_targets_complexes_get(tgg);

	else if(MEAS_MOD_WR > MEAS_MOD_COMPLEXES)
		spt_fft_angle(tgg);

	else {
		tgg->state = TGG_ST_READY;
		tgg->done(tgg);
	}
}

#define MAX_ANGLE_PEAKS_PER_TARGET 	0x8
typedef struct {
	uint16_t	cs[MAX_COUNT_OF_TARGET];
	uint16_t	*ses;
}peak_counts_t, *peak_counts_p;

typedef struct {
	peak_value_t 	vs[MAX_COUNT_OF_TARGET][MAX_ANGLE_PEAKS_PER_TARGET];
	peak_counts_t	counts;
}peak_blocks_t, *peak_blocks_p;

/*******************************************************************************
 * angle fft memory map on work_space base : 0x40100000
 * sizeof(target_aoa_data_t
 */
static void spt_fft_angle(target_group_p tgg)
{
	peak_blocks_p pblk = (peak_blocks_p)PEAKS_DATA;
	peak_counts_p pcounts = &pblk->counts;

	target_p tg = tgg->targets;
	target_aoa_data_p tad = (target_aoa_data_p)TARGET_AOA_DATA;

	spt->aoa_time = STM_0.CNT.R;
	memset((void*)tad, 0, sizeof(target_aoa_data_t)*tgg->tcnt);
	pcounts->ses = pcounts->cs;
	while(pcounts->ses != (pcounts->cs+tgg->tcnt)){
		*pcounts->ses = 0;
		pcounts->ses++;
	}
	pcounts->ses = pcounts->cs;

	SPT.WR_R5_RE.R = tgg->tcnt;
	SPT.WR_R10_IM.R = sizeof(target_aoa_data_t);
	SPT.WR_R10_RE.R = 0;

	tgg->state = TGG_ST_AOA;
	if(tgg->rcnt == RX_ACTIVES) {
		coefs_target_cmplx_cmps(tg, tad, RX_ACTIVES);
		if(tgg->tcnt >= 2){
			coefs_target_cmplx_cmps(&tg[1], &tad[1], RX_ACTIVES);
		}

		spt_context_start(SPT_CONTEXT_ANGLE_1024_4R, (event_proc_p)spt_angle_from_fft_peaks_near, (void*)tgg);
	}
	else  {
		coefs_target_cmplx_cmps(tg, tad, TOTAL_RX_ACTIVES);
		//print_cmpsed_cmplx(tad,TOTAL_RX_ACTIVES);
		if(tgg->tcnt >= 2){
			coefs_target_cmplx_cmps(tg+1, tad+1, TOTAL_RX_ACTIVES);
			//print_cmpsed_cmplx(tad+1,TOTAL_RX_ACTIVES);
			if(tgg->tcnt >= 3){
				coefs_target_cmplx_cmps(tg+2, tad+2, TOTAL_RX_ACTIVES);
				//print_cmpsed_cmplx(tad+2,TOTAL_RX_ACTIVES);
			}
		}

		SPT.WR_R1_IM.R = offsetof(target_aoa_data_t, pv);
		SPT.WR_R1_RE.R = 0x9000;
		spt_context_start(SPT_CONTEXT_ANGLE_1024_8R, (event_proc_p)spt_angle_from_fft_peaks_long, (void*)tgg);
	}

	if(MEAS_FLAG_AOA_DEBUG & MEAS_FLAGS_WR)
		PRINTF("aoa:tgg[%d]=>targets(%lX,%lX),time=%.2fus\n",tgg->idx,SPT.WR_R0_IM.R,
				SPT.WR_R10_IM.R,((float)(STM_0.CNT.R - spt->aoa_time)*CLOCK_PERIOD_US));
	else {
		CORE_DEBUG("aoa: tgg(%p,%d,%d)\n",tgg,tgg->idx,tgg->state);
	}
}

const float asin_table[]={
		0.0000,0.1119,0.2238,0.3357,0.4476,0.5595,0.6715,0.7834,0.8953,1.0072,1.1191,1.2311,1.3430,1.4549,1.5669,1.6788,
		1.7908,1.9027,2.0147,2.1267,2.2387,2.3507,2.4627,2.5747,2.6867,2.7988,2.9108,3.0229,3.1349,3.2470,3.3591,3.4712,
		3.5833,3.6955,3.8076,3.9198,4.0319,4.1441,4.2563,4.3686,4.4808,4.5931,4.7053,4.8176,4.9299,5.0423,5.1546,5.2670,
		5.3794,5.4918,5.6042,5.7167,5.8292,5.9417,6.0542,6.1667,6.2793,6.3919,6.5045,6.6171,6.7298,6.8425,6.9552,7.0680,
		7.1808,7.2936,7.4064,7.5193,7.6321,7.7451,7.8580,7.9710,8.0840,8.1971,8.3101,8.4232,8.5364,8.6496,8.7628,8.8760,
		8.9893,9.1026,9.2160,9.3294,9.4428,9.5562,9.6697,9.7833,9.8969,10.0105,10.1241,10.2378,10.3516,10.4653,10.5792,10.6930,
		10.8069,10.9209,11.0349,11.1489,11.2630,11.3771,11.4913,11.6055,11.7198,11.8341,11.9484,12.0628,12.1773,12.2918,12.4064,12.5210,
		12.6356,12.7503,12.8651,12.9799,13.0948,13.2097,13.3247,13.4397,13.5548,13.6699,13.7851,13.9004,14.0157,14.1311,14.2465,14.3620,
		14.4775,14.5931,14.7088,14.8245,14.9403,15.0562,15.1721,15.2881,15.4041,15.5202,15.6364,15.7526,15.8689,15.9853,16.1017,16.2182,
		16.3348,16.4515,16.5682,16.6850,16.8018,16.9188,17.0358,17.1529,17.2700,17.3872,17.5045,17.6219,17.7394,17.8569,17.9745,18.0922,
		18.2100,18.3278,18.4457,18.5637,18.6818,18.8000,18.9182,19.0366,19.1550,19.2735,19.3921,19.5108,19.6296,19.7484,19.8674,19.9864,
		20.1055,20.2247,20.3440,20.4634,20.5829,20.7025,20.8222,20.9419,21.0618,21.1818,21.3018,21.4220,21.5423,21.6626,21.7831,21.9036,
		22.0243,22.1451,22.2659,22.3869,22.5080,22.6292,22.7505,22.8719,22.9934,23.1150,23.2367,23.3586,23.4805,23.6026,23.7248,23.8471,
		23.9695,24.0920,24.2147,24.3374,24.4603,24.5833,24.7064,24.8297,24.9530,25.0765,25.2001,25.3239,25.4477,25.5717,25.6958,25.8201,
		25.9445,26.0690,26.1936,26.3184,26.4433,26.5684,26.6936,26.8189,26.9444,27.0700,27.1957,27.3216,27.4476,27.5738,27.7001,27.8266,
		27.9532,28.0799,28.2069,28.3339,28.4611,28.5885,28.7160,28.8437,28.9715,29.0995,29.2277,29.3560,29.4845,29.6131,29.7419,29.8709,
		30.0000,30.1293,30.2588,30.3884,30.5182,30.6482,30.7784,30.9087,31.0392,31.1699,31.3008,31.4319,31.5631,31.6945,31.8262,31.9580,
		32.0900,32.2221,32.3545,32.4871,32.6198,32.7528,32.8860,33.0193,33.1529,33.2867,33.4206,33.5548,33.6892,33.8238,33.9586,34.0936,
		34.2289,34.3643,34.5000,34.6359,34.7720,34.9084,35.0449,35.1817,35.3188,35.4560,35.5935,35.7313,35.8692,36.0075,36.1459,36.2846,
		36.4236,36.5628,36.7022,36.8419,36.9819,37.1221,37.2626,37.4033,37.5443,37.6856,37.8271,37.9690,38.1110,38.2534,38.3960,38.5390,
		38.6822,38.8257,38.9695,39.1136,39.2579,39.4026,39.5476,39.6929,39.8384,39.9843,40.1305,40.2771,40.4239,40.5711,40.7185,40.8664,
		41.0145,41.1630,41.3118,41.4609,41.6104,41.7603,41.9105,42.0610,42.2119,42.3632,42.5148,42.6669,42.8192,42.9720,43.1251,43.2786,
		43.4325,43.5868,43.7415,43.8966,44.0521,44.2080,44.3644,44.5211,44.6783,44.8359,44.9939,45.1523,45.3112,45.4706,45.6304,45.7907,
		45.9514,46.1126,46.2742,46.4364,46.5990,46.7621,46.9257,47.0898,47.2544,47.4196,47.5852,47.7514,47.9181,48.0853,48.2531,48.4215,
		48.5904,48.7598,48.9299,49.1005,49.2717,49.4435,49.6160,49.7890,49.9626,50.1369,50.3118,50.4874,50.6636,50.8405,51.0180,51.1962,
		51.3752,51.5548,51.7351,51.9162,52.0980,52.2805,52.4638,52.6479,52.8327,53.0183,53.2048,53.3920,53.5801,53.7690,53.9588,54.1494,
		54.3409,54.5333,54.7266,54.9209,55.1161,55.3122,55.5094,55.7075,55.9066,56.1068,56.3080,56.5102,56.7136,56.9180,57.1236,57.3304,
		57.5383,57.7473,57.9577,58.1692,58.3820,58.5961,58.8116,59.0283,59.2465,59.4660,59.6870,59.9095,60.1334,60.3589,60.5860,60.8147,
		61.0450,61.2770,61.5107,61.7462,61.9835,62.2227,62.4638,62.7068,62.9519,63.1990,63.4483,63.6997,63.9534,64.2095,64.4679,64.7287,
		64.9922,65.2582,65.5270,65.7985,66.0729,66.3504,66.6309,66.9147,67.2018,67.4923,67.7865,68.0844,68.3862,68.6920,69.0021,69.3167,
		69.6359,69.9599,70.2891,70.6236,70.9638,71.3099,71.6623,72.0214,72.3876,72.7612,73.1430,73.5332,73.9327,74.3422,74.7623,75.1941,
		75.6385,76.0968,76.5705,77.0611,77.5707,78.1018,78.6574,79.2412,79.8582,80.5148,81.2198,81.9861,82.8334,83.7945,84.9341,86.4184,
		90.0000};

static void spt_angle_from_fft_peaks_long(target_group_p tgg)
{
	float radian, delta, tmp;
	int idx;
	target_p tg = tgg->targets;
	peak_blocks_p pksp=(peak_blocks_p)PEAKS_DATA;
	target_aoa_data_p tad = ((target_aoa_data_p)TARGET_AOA_DATA);

	peak_counts_p pcntp = &pksp->counts;
	peak_value_p pvsp = pksp->vs[0], pv;
	uint8_t r4_5 = coefs_overlapped_rx_get();

	pcntp->ses = pcntp->cs;
	while(pcntp->ses < &pcntp->cs[tgg->tcnt]){

		tg->aoaidx = AOAIDX_INVALID;

		if(*pcntp->ses == 0) {
			PRINTF("spt: %d apks err %03X\n", (pcntp->ses - pcntp->cs), *pcntp->ses);
			//print_cmpsed_cmplx(tad, TOTAL_RX_ACTIVES);
			pcntp->ses++;
			pvsp += MAX_ANGLE_PEAKS_PER_TARGET;
			tg++;
			tad++;
			continue;
		}

		if(*pcntp->ses >= MAX_ANGLE_PEAKS_PER_TARGET)
			*pcntp->ses = MAX_ANGLE_PEAKS_PER_TARGET-1;

		if(*pcntp->ses > 1) {
			idx = 0;
			if((pvsp[1].idx - pvsp[0].idx) > 1024)
				pvsp[1].idx -= 2048;

			for(pv = pvsp; pv < (pvsp+*pcntp->ses); pv++)
				idx += (pv->idx/2);

			idx = idx/(*pcntp->ses);
			if(idx < 0)
				idx += 1024;
		}
		else
			idx = (pvsp->idx>>1);

		if(r4_5) {
            tg->vangle = DEGREE_OF_RADIAN(coefs_phase_differ(&tad->t2[r4_5],&tad->t1[r4_5])) + frame_info->hsft;
            if (tg->vangle > 180) {
            	tg->vangle = tg->vangle - 360;
            } else if (tg->vangle < -180) {
            	tg->vangle = tg->vangle + 360;
            }
		}
		else
			tg->vangle = 0;

		tg->velocity -= (CHIRPS_PER_FRAME);

		//print_cmpsed_cmplx(tad, TOTAL_RX_ACTIVES);
		if(MEAS_FLAG_AOA_DEBUG & MEAS_FLAGS_WR){
			complex24_t tv0,tv1;
			tv0.re = tad->tv[0].re;
			tv0.im = tad->tv[0].im;
			tv1.re = tad->tv[1].re;
			tv1.im = tad->tv[1].im;
			float phd = DEGREE_OF_RADIAN(coefs_phase_differ(&tv0,&tv1));
			PRINTF("aoa:r=%d,v=%d,pks=%d,idx=%d,va=%d,phd=%.1f\n",tg->range,tg->velocity,*pcntp->ses,idx,tg->vangle,phd);
		}
		else{
			CORE_DEBUG("aoa:r=%d,v=%d,pks=%d,idx=%d,a=%.5f,va=%d\n",tg->range,tg->velocity,*pcntp->ses,idx,aoaidx_asin(idx),tg->vangle);
			//CORE_DEBUG("aoa:r=%d,v=%d,pks=%d,idx=%.1f,va=%d\n",tg->range,tg->velocity,*pcntp->ses,idx,tg->vangle);
		}

		radian = aoaidx_asin(idx)-aoas_misc[FRAME_CTX_IDX_LONG].sft;
		delta = ABSF(aoas_misc[FRAME_CTX_IDX_LONG].sft);
		if(aoas_misc[FRAME_CTX_IDX_LONG].sft>0){
			for(;idx>0;idx--){
				tmp = DELTA(aoaidx_asin(idx-1),radian);
				if(tmp < delta){
					delta = tmp;
				}
				else
					break;
			}
			CORE_DEBUG("aoa_sft:[%.5f,%.5f,%.5f]\n",radian,aoaidx_asin(idx),delta);
		}
		else if(aoas_misc[FRAME_CTX_IDX_LONG].sft<0){
			for(;idx<(AOAIDX_INVALID-1);idx++){
				tmp = DELTA(aoaidx_asin(idx+1),radian);
				if(tmp < delta){
					delta = tmp;
				}
				else
					break;
			}
			CORE_DEBUG("aoa_sft:[%.5f,%.5f,%.5f]\n",radian,aoaidx_asin(idx),delta);
		}

		tg->aoaidx = idx;

		/*if(radian > aoas_misc[FRAME_CTX_IDX_LONG].start &&
					radian < aoas_misc[FRAME_CTX_IDX_LONG].end){
			tg->aoaidx = idx;
		}*/

		pcntp->ses++;
		pvsp += MAX_ANGLE_PEAKS_PER_TARGET;

		tg++;
		tad++;
	}

	tgg->state = TGG_ST_PARSING;
	if(MEAS_FLAG_AOA_DEBUG & MEAS_FLAGS_WR)
		PRINTF("aoa tgg[%d]: tcnt=%d,time=%.2fms\n",tgg->idx, tgg->tcnt, ((float)(STM_0.CNT.R - spt->aoa_time)*CLOCK_PERIOD_MS));
	else
		CORE_DEBUG("spt:aoa tggs[%d]=>%d\n", tgg->idx, tgg->tcnt);

	tgg->done(tgg);
}

static void spt_angle_from_fft_peaks_near(target_group_p tgg)
{
	float radian, delta, tmp;
	int idx;
	target_p tg = tgg->targets;
	peak_blocks_p peaks=(peak_blocks_p)PEAKS_DATA;
	peak_value_p pvs = peaks->vs[0], pv;
	peak_counts_p pcnt = &peaks->counts;
	target_aoa_data_p tad = ((target_aoa_data_p)TARGET_AOA_DATA);
	pcnt->ses = pcnt->cs;
	while(pcnt->ses < &pcnt->cs[tgg->tcnt]){

		tg->aoaidx = AOAIDX_INVALID;
		if(*pcnt->ses == 0 || *pcnt->ses >= MAX_ANGLE_PEAKS_PER_TARGET) {
			PRINTF("aoa(%d): pks err %03X\n", pcnt->ses-pcnt->cs, *pcnt->ses);
			//print_cmpsed_cmplx(tad, RX_ACTIVES);
			pcnt->ses++;
			pvs += MAX_ANGLE_PEAKS_PER_TARGET;
			tg++;
			tad++;
			continue;
		}

		if(*pcnt->ses > 1) {
			idx = 0;
			if((pvs[1].idx - pvs[0].idx) > 1024)
				pvs[1].idx -= 2048;

			for(pv = pvs; pv < (pvs+*pcnt->ses); pv++)
				idx += (pv->idx/2);

			idx = idx/(*pcnt->ses);
			if(idx < 0)
				idx += 1024;
		}
		else
			idx = (pvs->idx >> 1);

		if(MEAS_FLAG_AOA_DEBUG & MEAS_FLAGS_WR)
			PRINTF("aoa:r=%d,v=%d,pks=%d,idx=%d,a=%.4f\n", tg->range, tg->velocity,*pcnt->ses, idx, aoaidx_asin(idx));

		//if(frame_info->aoa_coefs[FRAME_CTX_IDX_NEAR])
			//tg->angle = tg->angle*frame_info->aoa_coefs[FRAME_CTX_IDX_NEAR];

		// shift the angle by far/near context
		// tg->angle -= frame_info->aoa_sft[FRAME_CTX_IDX_NEAR];

		radian = aoaidx_asin(idx)-aoas_misc[FRAME_CTX_IDX_NEAR].sft;
		delta = ABSF(aoas_misc[FRAME_CTX_IDX_NEAR].sft);
		if(aoas_misc[FRAME_CTX_IDX_NEAR].sft>0){
			for(;idx>0;idx--){
				tmp = DELTA(aoaidx_asin(idx-1),radian);
				if(tmp < delta){
					delta = tmp;
				}
				else
					break;
			}
			CORE_DEBUG("aoa_sft:[%.5f,%.5f,%.5f]\n",radian,aoaidx_asin(idx),delta);
		}
		else if(aoas_misc[FRAME_CTX_IDX_NEAR].sft<0){
			for(;idx<(AOAIDX_INVALID-1);idx++){
				tmp = DELTA(aoaidx_asin(idx+1),radian);
				if(tmp < delta){
					delta = tmp;
				}
				else
					break;
			}
			CORE_DEBUG("aoa_sft:[%.5f,%.5f,%.5f]\n",radian,aoaidx_asin(idx),delta);
		}

		tg->aoaidx = idx;
		/*if(radian > aoas_misc[FRAME_CTX_IDX_NEAR].start &&
				radian < aoas_misc[FRAME_CTX_IDX_NEAR].end){
			tg->aoaidx = idx;
		}*/

		tg->velocity -= CHIRPS_PER_FRAME;

		pcnt->ses++;
		pvs += MAX_ANGLE_PEAKS_PER_TARGET;
		tg++;
		tad++;
	}
	tgg->state = TGG_ST_PARSING;
	if(MEAS_FLAG_AOA_DEBUG & MEAS_FLAGS_WR)
		PRINTF("aoa(%d): near time=%.2fms\n",tgg->tcnt, ((float)(STM_0.CNT.R - spt->aoa_time)*CLOCK_PERIOD_MS));
	else
		CORE_DEBUG("spt:aoa tggs[%d] %d\n", tgg->idx, tgg->tcnt);

	tgg->done(tgg);
}

/*
 * Execute spt command script in addr
 */
int SPT_exec(spt_function_p sptfp, int block)
{
	static spt_context_p pctxp = NULL;
	static uint8_t busy = 0;
	if(SPT.CS_STATUS0.R){
		PRINTF("SPT: busy,%08lX,st=%ld,%s:%p not exed, x-ctx is %s!\n",
				SPT.CS_STATUS0.R, SPT_FBMS_STATE_WR, spt->ctx->name, sptfp, pctxp->name);
		spt_ctxs_dump();
		SPT_dump_status();
		if(busy == 1 || SPT.CS_STATUS2.B.WAITREG_FAD){ // reset if frame done not recved
		    reset_system();
		}

		busy = 1;
		return FALSE;
	}
	busy = 0;

	//SPT.EVENT_RST_CTRL.R = 0x07;
	SPT.CS_SW_EVTREG.B.SW_EVTREG = 0;
	SPT.GBL_STATUS.R = 0x07;
	SPT.CS_STATUS0.R = 0xFFFFFFFF;
	SPT.CS_PG_ST_ADDR.R = (uint32_t)sptfp;

	if(block) {
		spt->ctx = NULL;
	}

	SPT.GBL_CTRL.B.PG_ST_CTRL = 0x01;

	if(block) {
		while (SPT.CS_STATUS0.R);
		pctxp = NULL;
	}
	else
		pctxp = spt->ctx;

	return TRUE;
}

/*
 * send event to spt
 */
void SPT_sw_evt(int number)
{
	if (number > 7){
		PRINTF("Invalid SW EVT number %d\n", number);
		return;
	}

	if (number == -1)
		number = 0;
	else
		number = 1 << number;

	SPT.CS_SW_EVTREG.B.SW_EVTREG = number;
}

/*
 * Print SPT mapped data to console
 */
void SPT_mapped(void)
{
    PRINTF("range:%08lX:%08X\ndoppler:%08lX:%08X\nsample:%08lX:%08X\nworkspace:%08lX:%08X\n",
    		(uint32_t)RANGE_DATA, 0x80000,
			(uint32_t)DOPPLER_DATA, 0x80000,
			(uint32_t)ADC_SAMPLES, 0x100000,
			(uint32_t)WORK_SPACE, 0x10000);
}

void SPT_dump_wrs(int start, int end)
{
	spt_work_reg_p wr = (spt_work_reg_p)&(SPT.WR_R0_RE.R);
	uint16_t idx = 0;

	if(start < end) {
		start &= 0xFFFC;
		wr += start;
		idx = start;
	}

	if (end == 0 || end > 48)
		end = 48;

	while(idx < end) {
		PRINTF("W%02d~%02d(RE,IM):(%06lX,%06lX),(%06lX,%06lX),(%06lX,%06lX),(%06lX,%06lX)\n",
				idx, idx+3, wr[0].re, wr[0].im,	wr[1].re, wr[1].im,
				wr[2].re, wr[2].im, wr[3].re, wr[3].im);
		wr += 4;
		idx += 4;
	}
}

void SPT_dump_status(void)
{
	PRINTF("Curr Inst@%08lX: %08lX %08lX %08lX %08lX\n", SPT.CS_CURR_INST_ADDR.R, SPT.CS_CURR_INST0.R,
			SPT.CS_CURR_INST1.R,SPT.CS_CURR_INST2.R, SPT.CS_CURR_INST3.R);

	PRINTF("Curr ErrI@%08lX: %08lX %08lX %08lX %08lX\n", SPT.CS_ERR_INST_ADDR.R, SPT.CS_ERR_INST0.R,
			SPT.CS_ERR_INST1.R,SPT.CS_ERR_INST2.R, SPT.CS_ERR_INST3.R);

	PRINTF("SPT Status: GBL=%08lX, S0=%08lX, S1=%08lX, S2=%08lX, S3=%08lX, DMA=%08lX, MEM=%08lX\n", SPT.GBL_STATUS.R,
			spt->status0, SPT.CS_STATUS1.R, SPT.CS_STATUS2.R, SPT.CS_STATUS3.R, SPT.DMA_ERR_STATUS.R,
			SPT.MEM_ERR_STATUS.R);
}

void dma_err_proc(uint32_t status)
{
	if(spt->ctx)
		PRINTF("SPT DMA error %08lX by ctx %s\n", status, spt->ctx->name);
	else
		PRINTF("SPT DMA error %08lX by unknown ctx\n", status);

	SPT_dump_status();
	SPT_dump_wrs(0, 48);
	console_flush();
	ILLEGAL_PROC(NULL);
}

void spt_ecs_isr(void)
{
	if (SPT.CS_STATUS0.B.PS_STOP) {
		spt->status0 = SPT.CS_STATUS0.R;
		if(spt->done_cb && spt->ctx) {
			spt->time = STM_0.CNT.R - spt->time;
			put_event(spt->ctx->name, (event_proc_p)spt->done_cb, (void*)spt->done_data);
			spt->done_cb = NULL;
		}
	}
	SPT.CS_STATUS0.R = 0xFFFFFFFF;  // clear all status bit

	if (SPT.DMA_ERR_STATUS.R & 0x1FFE) {
		put_event("dma", (event_proc_p)dma_err_proc, (void*)SPT.DMA_ERR_STATUS.R);
		SPT.DMA_ERR_STATUS.R = 0x1FFE;
	}
}

/*
 * DMA ERR ISR handler
 */
void spt_dma_isr(void)
{
	put_event("dma", (event_proc_p)dma_err_proc, (void*)SPT.DMA_ERR_STATUS.R);
	SPT.DMA_ERR_STATUS.R = 0x1FFE;
}

/*
 * EVTREG1 ISR handler
 */
void spt_irq0(void)
{
	// RNG FFT done event
	if(SPT.CS_EVTREG1.R & 0x01) {
		//spt_fft_shifts((target_group_p)spt->done_data);
		SPT.CS_EVTREG1.R = 0x01;
	}

	// RF done event
	if(SPT.CS_EVTREG1.R & 0x02) {
		//spt_adc_shifts((target_group_p)spt->done_data);
		put_event("rfd", (event_proc_p)spt_rf_done, spt->done_data);
		SPT.CS_EVTREG1.R = 0x02;
	}

	if(SPT.CS_EVTREG1.R & 0x04){
		if(fft3d_logger != NULL)
			put_event("fft3", fft3d_logger, spt->done_data);
		else
			SPT.CS_SW_EVTREG.B.SW_EVTREG = 1<<2;
		SPT.CS_EVTREG1.R = 0x04;
	}

	if(SPT.CS_EVTREG1.R & 0x08) {
#if HIST_DEBUG_ON
		put_event("hist", (event_proc_p)hist_threshold, spt->done_data);
#else
		hist_threshold((target_group_p)spt->done_data);
#endif
		SPT.CS_EVTREG1.R = 0x08;
	}

	if(SPT.CS_EVTREG1.R & 0x10) {
		SPT.CS_SW_EVTREG.B.SW_EVTREG = 1<<2; // AGGREGATION_DONE_EVENT
		SPT.CS_EVTREG1.R = 0x10;
	}

	if(SPT.CS_EVTREG1.R & 0x20)
		SPT.CS_EVTREG1.R = 0x20;

	if(SPT.CS_EVTREG1.R & 0x40) {
		peak_counts_p pcounts = &((peak_blocks_p)PEAKS_DATA)->counts;
		complex24_p  vals = (complex24_p)WORK_SPACE;
		target_aoa_data_p tad = ((target_aoa_data_p)TARGET_AOA_DATA)+SPT.WR_R6_RE.R;
		peak_value_p pk = (peak_value_p)(tad->pv[0]);
		int idx = pk->idx>>1;
		pcounts->cs[SPT.WR_R6_RE.R] = (SPT.PDMA_TRANSFER_COUNT_STATUS.R>>16);
		tad->tv[0].re=(float)vals[idx].re;
		tad->tv[0].im=(float)vals[idx].im;
		idx += 1024;
		tad->tv[1].re=(float)vals[idx].re;
		tad->tv[1].im=(float)vals[idx].im;
		idx = SPT.WR_R6_RE.R+3;

		SPT.CS_EVTREG1.R = 0x40;
		if(aoa_logger)
			put_event("aoa8", (event_proc_p)aoa_logger, spt->tggs+FRAME_CTX_IDX_LONG);
		else
			SPT.CS_SW_EVTREG.B.SW_EVTREG = 1<<2; // AGGREGATION_DONE_EVENT

		if(SPT.WR_R5_RE.R > idx){
			target_p tg = spt->tggs[FRAME_CTX_IDX_LONG].targets+idx;
			coefs_target_cmplx_cmps(tg, ((target_aoa_data_p)TARGET_AOA_DATA)+idx, TOTAL_RX_ACTIVES);
		}
	}

	if(SPT.CS_EVTREG1.R & 0x80) {
		peak_counts_p pcounts = &((peak_blocks_p)PEAKS_DATA)->counts;
		pcounts->cs[SPT.WR_R6_RE.R] = (SPT.PDMA_TRANSFER_COUNT_STATUS.R>>16);
		int idx = SPT.WR_R6_RE.R+2;
		target_p tg = spt->tggs[0].targets+idx;
		target_aoa_data_p tad = ((target_aoa_data_p)TARGET_AOA_DATA)+idx;

		SPT.CS_EVTREG1.R = 0x80;
		if(aoa_logger)
			put_event("aoa4", (event_proc_p)aoa_logger, spt->tggs);
		else
			SPT.CS_SW_EVTREG.B.SW_EVTREG = 1<<2; // AGGREGATION_DONE_EVENT


		if(SPT.WR_R5_RE.R > idx)
			coefs_target_cmplx_cmps(tg, tad, RX_ACTIVES);
	}
}

/*
 * EVTREG2 ISR handler
 */
void spt_irq1(void)
{
	//put_event("iq1", NULL);
	SPT.CS_EVTREG2.R = 0xFF;
}


static uint32_t  spt_mem_command[] __attribute__((aligned(16))) = {
		0xA1010200, (uint32_t)0xDEADDEAD, 0x46000000, 0x01000001,
		0x10000000, 0x00000000, 0x00000000, 0x00000000};

void SPT_mem(uint8_t packing, uint16_t vsz, uint16_t spt, uint32_t sram)
{
	uint8_t *pack = ((uint8_t*)spt_mem_command)+1;
	uint16_t *sz = ((uint16_t*)spt_mem_command)+1;
	uint16_t *spt_addr = ((uint16_t*)spt_mem_command)+4;
	uint32_t *sys_addr = spt_mem_command+1;
	//PRINTF("spt: mem@%p(%d,%d,%04X,%08lX)\n",spt_mem_command,packing,vsz,spt,sram);
	//console_flush();
	*pack = packing;
	*sz = vsz;
	*spt_addr = spt;
	*sys_addr = sram;
	SPT_exec((spt_function_p)spt_mem_command, TRUE);
}

static void spt_meas_test_done(void* x)
{
	PRINTF("spt:test in %ldus\n#", (uint32_t)((float)(STM_0.CNT.R - spt->time)*CLOCK_PERIOD_US));
}

/******************************************************************************
Function : console commands
******************************************************************************/
static void spt_watches(char** args, int count)
{
	if(count > 1) {
		if(!strcmp(args[1], "wrs")) {
			uint32_t d0=0, d1=48;
			if(count > 2)
				d0 = strtoul(args[2], NULL, 16);
			if(count > 3)
				d1 = strtoul(args[3], NULL, 16);
			SPT_dump_wrs(d0, d1);
		}

		else if(!strcmp(args[1], "status"))
			SPT_dump_status();

		else if(!strcmp(args[1], "mem") && count > 5) {
			uint8_t pack = strtoul(args[2],NULL, 16);
			uint16_t vsz = strtoul(args[3],NULL, 16);
			uint16_t spt = strtoul(args[4],NULL, 16)&0xFFFFFFF0;
			uint32_t sram = (uint32_t)strtoul(args[5],NULL, 16)&0xFFFFFFF0;
			SPT_mem(pack, vsz, spt, sram);
		}

		else if(!strcmp(args[1], "ctxs"))
			spt_ctxs_dump();

		else if(!strcmp(args[1],"trx")){
			uint16_t tx = 0;
			if(count > 2)
				tx = strtoul(args[2],NULL, 16);

			spt_txrx_test(tx, spt_meas_test_done);
		}

		else if(!strcmp(args[1], "tad") && count > 2) {
			target_aoa_data_p tad=(target_aoa_data_p)WORK_SPACE;
			int16_t idx = 0, order=TOTAL_RX_ACTIVES;
			idx = (int16_t)strtoul(args[2], NULL, 10);
			if(count > 3)
				order = (int16_t)strtoul(args[3], NULL, 10);
			if(idx < MAX_COUNT_OF_TARGET)
				print_cmpsed_cmplx(tad+idx, order);
		}

		else if(!strcmp("doppler", args[1]) && count > 3) {
			float rng = strtof(args[3], NULL);
			if(!strcmp("long", args[2])){
				spt_doppler_get(FRAME_CTX_IDX_LONG, rng, spt_doppler_test_done);
			}
			else {
				spt_doppler_get(FRAME_CTX_IDX_NEAR, rng, spt_doppler_test_done);
			}
		}

		/*else if(!strcmp(args[1],"adcs")){
			PRINTF("adc(val,sft): LR(%04X,%d),SR(%04X,%d)\n",spt->adc_maxs[1],
					spt->adc_shifts[1],spt->adc_maxs[0],spt->adc_shifts[0]);
		}*/

		else if(!strcmp(args[1],"thld")){
			if(frame_info->on[FRAME_CTX_IDX_LONG]){
				int i;
				PRINTF("LR: thlds per range bin");
				for(i = 0; i<(SAMPLES_PER_CHIRP>>1); i=i+8){
					PRINTF("\n%03d~%03d: %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f",i, i+8,
							hist_peaks[1][i]*3.01f/256,hist_peaks[1][i+1]*3.01f/256,
							hist_peaks[1][i+2]*3.01f/256,hist_peaks[1][i+3]*3.01f/256,
							hist_peaks[1][i+4]*3.01f/256,hist_peaks[1][i+5]*3.01f/256,
							hist_peaks[1][i+6]*3.01f/256,hist_peaks[1][i+7]*3.01f/256);
				}
				PRINTF("\n\nLR: thlds offset per 8 range bins\n");
				for(i = 0; i<(SAMPLES_PER_CHIRP>>4); i=i+8){
					PRINTF("%03d: %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\n",i*8,
							hist_thlds[1][i]*3.01f/256,hist_thlds[1][i+1]*3.01f/256,
							hist_thlds[1][i+2]*3.01f/256,hist_thlds[1][i+3]*3.01f/256,
							hist_thlds[1][i+4]*3.01f/256,hist_thlds[1][i+5]*3.01f/256,
							hist_thlds[1][i+6]*3.01f/256,hist_thlds[1][i+7]*3.01f/256);
				}
			}

			if(frame_info->on[FRAME_CTX_IDX_NEAR]){
				PRINTF("\nSR: thlds per range bins\n");
				for(int i = 0; i<(SAMPLES_PER_CHIRP>>2); i=i+8){
					PRINTF("%03X: %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\n",i,
							hist_peaks[0][i]*3.01f/256,hist_peaks[0][i+1]*3.01f/256,
							hist_peaks[0][i+2]*3.01f/256,hist_peaks[0][i+3]*3.01f/256,
							hist_peaks[0][i+4]*3.01f/256,hist_peaks[0][i+5]*3.01f/256,
							hist_peaks[0][i+6]*3.01f/256,hist_peaks[0][i+7]*3.01f/256);
				}

				PRINTF("\nSR: thlds offset per 8 range bins\n");
				for(int i = 0; i<16; i=i+8){
					PRINTF("%03X: %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\n",i*8,
						hist_thlds[0][i]*3.01f/256,hist_thlds[0][i+1]*3.01f/256,
						hist_thlds[0][i+2]*3.01f/256,hist_thlds[0][i+3]*3.01f/256,
						hist_thlds[0][i+4]*3.01f/256,hist_thlds[0][i+5]*3.01f/256,
						hist_thlds[0][i+6]*3.01f/256,hist_thlds[0][i+7]*3.01f/256);
				}
			}
		}

		else if(!strcmp("mod", args[1])) {
			MEAS_MOD_WR = strtoul(args[2], NULL, 16);
			if(count > 3)
				MEAS_FLAGS_WR = strtoul(args[3], NULL, 16);
		}
		else if(!strcmp("flags", args[1]))
			MEAS_FLAGS_WR = strtoul(args[2], NULL, 16);

		else if(!strcmp("ctx", args[1]) && count > 2){
			uint32_t dat = strtoul(args[2], NULL, 16);
			if(dat <= SPT_CONTEXT_INVALID)
				spt_context_start(dat, spt_meas_test_done, NULL);
		}

		else if(!strcmp("get", args[1])){
			if (count > 3)
				SPT.WR_R8_IM.R = strtoul(args[3], NULL, 16);
			else
				SPT.WR_R8_IM.R = 0;

			if(!strcmp("near", args[2]))
				spt_near_start(spt_meas_test_done);
			else
				spt_long_start(spt_meas_test_done);
		}

		else if(!strcmp("fftd", args[1])){
			uint32_t dat = strtoul(args[2], NULL, 16);
			SPT.WR_R0_IM.R = dat;
			SPT.WR_R0_RE.R = 0x9000;
			SPT.WR_R1_RE.R = 0x9000;
			SPT.WR_R1_IM.R = 0;
			spt_context_start(SPT_CONTEXT_DCP4D_16K, spt_meas_test_done, NULL);
		}

		else if(!strcmp("json", args[1])){
			int idx = strtoul(args[2], NULL, 10);
			char *ws=(char*)WORK_SPACE;
			if(idx < FRAME_CTXS_COUNT)
				count = frame_tgg_in_jsons(&spt->tggs[idx], ws);
			else
				count = frame_tggs_in_jsons(ws);

			PRINTF("meas in json %d:\n",count);
			put_string(ws);
		}

		else if(!strcmp("vfb", args[1])){
			if(count >= 4){
				double bw = strtof(args[2], NULL);
				double hpf = strtof(args[3], NULL);
				spt_vertical_feedback_mode(bw, hpf);
				PRINTF("spt: pars@%p\n", frame_info);
			}
			else
				spt_resume_to_normal_mode();
		}
	}
	else {
		PRINTF("meas: mod=%lX,[RAW,RNG,FFT,BEAMFORM,MAXS,COMPLEX,MEAS,TRACK]\n",MEAS_MOD_WR);
		PRINTF("meas: flags=%lX,b0:from raw,b1:debug,b4:velo\n",MEAS_FLAGS_WR);
	}
}

retval_e spt_action_start(spt_context_e ctxid)
{
	spt_context_p ctx;
	int8_t profile;
	if (ctxid >= SPT_CONTEXT_INVALID) {
		PRINTF("Invalid spt context!\n");
		return ERROR;
	}

	ctx = &spt_contexts[ctxid];
	profile = ctx->profile;

	if(profile != -1){
		CORE_DEBUG("spt:rfp %d\n", ctx->profile);
		TEF810x_chirp_start(ctx->profile, ctx->chirps, ctx->repeat);
	}

	if(SPT_exec(ctx->sfp, TRUE) == FALSE)	//blocking
		return ERROR;

	return SUCCESS;
}

/***********************************************************************************************
 * doppler data get
 ***********************************************************************************************/
typedef struct rng_velo {
	float 			range;
	event_proc_p 	cb;
}doppler_info_t;

static doppler_info_t doppler_get_info = {0};

static double _complex_mag_get(int32_t imag, int32_t real)
{
	double res = pow((double)real,2) + pow((double)imag,2);
	return sqrt(res);
}

static void spt_doppler_test_done(void* d)
{
	target_group_p tgg=(target_group_p)d;
	target_p tg = tgg->targets;
	
	if(tg){
		PRINTF("r(%d),v(%d),a(%.4f),h(%d):(re im phs mag)...\n", tg->range,tg->velocity,DEGREE_OF_RADIAN(aoaidx_asin(tg->aoaidx)),tg->vangle);
		PRINTF("(%ld %ldj %.2f %.1f),(%ld %ldj %.2f %.1f),(%ld %ldj %.2f %.1f),(%ld %ldj %.2f %.1f)",
			tg->cmplx[0].re,tg->cmplx[0].im,
			DEGREE_OF_RADIAN(atan2((float)tg->cmplx[0].im, (float)tg->cmplx[0].re)),
			_complex_mag_get((float)tg->cmplx[0].im, (float)tg->cmplx[0].re),
			tg->cmplx[1].re, tg->cmplx[1].im,
			DEGREE_OF_RADIAN(atan2((float)tg->cmplx[1].im, (float)tg->cmplx[1].re)),
			_complex_mag_get((float)tg->cmplx[1].im, (float)tg->cmplx[1].re),
			tg->cmplx[2].re,tg->cmplx[2].im,
			DEGREE_OF_RADIAN(atan2((float)tg->cmplx[2].im, (float)tg->cmplx[2].re)),
			_complex_mag_get((float)tg->cmplx[2].im, (float)tg->cmplx[2].re),
			tg->cmplx[3].re, tg->cmplx[3].im,
			DEGREE_OF_RADIAN(atan2((float)tg->cmplx[3].im, (float)tg->cmplx[3].re)),
			_complex_mag_get((float)tg->cmplx[3].im, (float)tg->cmplx[3].re));

		if(tgg->idx == FRAME_CTX_IDX_LONG) {
			PRINTF("(%ld %ldj %.2f %.1f),(%ld %ldj %.2f %.1f),(%ld %ldj %.2f %.1f),(%ld %ldj %.2f %.1f)\n",
				tg->cmplx[4].re,tg->cmplx[4].im,
				DEGREE_OF_RADIAN(atan2((float)tg->cmplx[4].im, (float)tg->cmplx[4].re)),
				_complex_mag_get((float)tg->cmplx[4].im, (float)tg->cmplx[4].re),
				tg->cmplx[5].re, tg->cmplx[5].im,
				DEGREE_OF_RADIAN(atan2((float)tg->cmplx[5].im, (float)tg->cmplx[5].re)),
				_complex_mag_get((float)tg->cmplx[5].im, (float)tg->cmplx[5].re),
				tg->cmplx[6].re,tg->cmplx[6].im,
				DEGREE_OF_RADIAN(atan2((float)tg->cmplx[6].im, (float)tg->cmplx[6].re)),
				_complex_mag_get((float)tg->cmplx[6].im, (float)tg->cmplx[6].re),
				tg->cmplx[7].re, tg->cmplx[7].im,
				DEGREE_OF_RADIAN(atan2((float)tg->cmplx[7].im, (float)tg->cmplx[7].re)),
				_complex_mag_get((float)tg->cmplx[7].im, (float)tg->cmplx[7].re));
		}
	}
}

static void spt_doppler_get_proc(void* d)
{
    int16_t range;
    uint8_t i;
    double mag0,mag1,mag2;
    target_group_p tgg = (target_group_p)d;
	target_p tg = tgg->targets;

	if(tgg->targets[0].mag_log2 == 0){
	    if(tgg->tcnt == 1){
	        tg->mag_log2 = 100;
		    if(doppler_get_info.cb)
			    doppler_get_info.cb(tgg);
		    doppler_get_info.cb = NULL;
		    PRINTF("\nspt: tgg[%d] dop done!\n",tgg->idx);
            tgg->state = TGG_ST_READY;
	        return;
	        
	    }else{    
	        mag0=_complex_mag_get((float)tgg->targets[0].cmplx[0].im, (float)tgg->targets[0].cmplx[0].re);
            mag1=_complex_mag_get((float)tgg->targets[1].cmplx[0].im, (float)tgg->targets[1].cmplx[0].re);
            mag2=_complex_mag_get((float)tgg->targets[2].cmplx[0].im, (float)tgg->targets[2].cmplx[0].re);
            PRINTF("mag0=%.2f,mag1=%.2f,mag2=%.2f\n",mag0,mag1,mag2);
            if((mag1>mag0)&&(mag1>mag2)){
	            tg->range = tgg->targets[1].range;
	        }
	        else 
	        if((mag2>mag0)&&(mag2>mag1)){
	            tg->range = tgg->targets[2].range;
	        }
	        
	        tgg->tcnt = 1;
            tg->aoaidx = AOAIDX_INVALID;
            tg->velocity = tgg->vbins/2;
            if(tgg->rcnt == TOTAL_RX_ACTIVES)
	            tg->pos = (int16_t)(tg->range*tgg->vbins/2)+tgg->vbins/4;
		    else
	            tg->pos = (int16_t)(tg->range*tgg->vbins)+tgg->vbins/2;
	        PRINTF("dop: %.2f,r=%.2f,v=%d,p=%d\n",doppler_get_info.range,tg->range*tgg->runit,tg->velocity,tg->pos);
	    }	    
    }
	else {    
        tgg->tcnt = 3;
   		range = (int16_t)(doppler_get_info.range/tgg->runit)-1;
        for(i=0;i<3;i++){
		    tg->aoaidx = AOAIDX_INVALID;
		    tg->range = range++;
		
		    tg->velocity = tgg->vbins/2;
		    if(tgg->rcnt == TOTAL_RX_ACTIVES)
			    tg->pos = (int16_t)(tg->range*tgg->vbins/2)+tgg->vbins/4;
		    else
			    tg->pos = (int16_t)(tg->range*tgg->vbins)+tgg->vbins/2;

		    tg->mag_log2 = 0;
		    tg++;
		}
	}
	tgg->state = TGG_ST_FFTS_DONE;
    tgg->done = (event_proc_p)spt_doppler_get_proc;
	spt_targets_complexes_get(tgg);
	
}

meas_state_e spt_doppler_get(FRAME_CTX_IDX_E idx, float rng, event_proc_p cb)
{
	if(MEAS_STATE_WR != MEAS_ST_READY)
		return MEAS_STATE_WR;

	doppler_get_info.range = rng;
	doppler_get_info.cb = cb;

	spt->tggs[FRAME_CTX_IDX_LONG].state = TGG_ST_READY;
	spt->tggs[FRAME_CTX_IDX_NEAR].state = TGG_ST_READY;
	if(idx == FRAME_CTX_IDX_LONG)
		spt_long_start(spt_doppler_get_proc);
	else if(idx == FRAME_CTX_IDX_NEAR)
		spt_near_start(spt_doppler_get_proc);
	else
		PRINTF("meas: unknown idx(%d) to get doppler\n",idx);

	return MEAS_ST_READY;
}

double target_get_db_by_cmplx(target_p tg, uint8_t map_index)
{
	double imag = 0;
	double real = 0;
	double rtval = 0;

	if(0 <= map_index && map_index <= 7)
	{
		if(NULL != tg)
		{
			imag = tg->cmplx[map_index].im;
			real = tg->cmplx[map_index].re;
			rtval = 10 * log10(imag * imag + real * real);
		}
	}

	return rtval;
}

meas_state_e spt_doppler_get_by_tx_channel(spt_context_e idx, float rng, event_proc_p cb)
{
	uint32_t mod, flags;

	if(MEAS_STATE_WR != MEAS_ST_READY)
		return MEAS_STATE_WR;

	spt_mode_flags_get(&mod,&flags);

	spt_mode_flags_set(MEAS_MOD_FFT, 0xFFFFFFFF);

	doppler_get_info.range = rng;
	doppler_get_info.cb = cb;

	if(SPT_CONTEXT_FRAME_T1 <= idx || SPT_CONTEXT_FRAME_T3 >= idx)
	{	//SPT_CONTEXT_FRAME_T1
		//SPT_CONTEXT_FRAME_T2
		//SPT_CONTEXT_FRAME_T3
		spt_meas_start(idx, spt_doppler_get_proc);
	}
	else
	{
		PRINTF("meas: unknown spt context frame(%d) to get doppler\n",idx);
	}
	return MEAS_ST_READY;
}

uint8_t spt_profileId_to_SptContextsId(uint8_t profile)
{
    uint8_t SptContextsId=0xff;
    uint8_t i;

    for(i=0;i<3;i++)
    {
        if(profile==spt_contexts[i].profile)
        {
           SptContextsId=i;
           break;
        }
    }
    return  SptContextsId;

}


/***********************************************************************************************
 * Vertical feedback APIs
 ***********************************************************************************************/
#define VFB_BW_NULL			0.0f
#define VFB_BW_DONE			-1.0f
typedef struct _vertical_feedback_rf{
	float bw;
	float hpf;
} vertical_feedback_rf_t;

vertical_feedback_rf_t vfb_rf = {VFB_BW_NULL};
retval_e spt_vertical_feedback_mode(float bw, float hpf)
{
	vfb_rf.bw = bw;
	vfb_rf.hpf = hpf;
	return SUCCESS;
}

void spt_resume_to_normal_mode(void)
{
	vfb_rf.bw = VFB_BW_DONE;
	pars_restore(FRAME_PARS_ID, NULL);
	spt_thlds_set(FRAME_CTX_IDX_LONG);  // apply thld
}

static void spt_vertical_feedback_finfo_set(void)
{
	frame_info->rng_long[0] = 2.0f;
	frame_info->rng_long[1] = 20.0f;
	frame_info->thld_long[0] = 120;
	frame_info->thld_long[1] = 100;
	frame_info->thld_long[2] = 100;
	frame_info->thld_long[3] = 100;
	frame_info->thld_long[4] = 100;
	frame_info->thld_long[5] = 100;
	frame_info->hsft = 0.0f;
	frame_info->on[0] = 0;
	frame_info->on[1] = 1;
}

static void spt_vertical_feedback_set(void)
{
	if(vfb_rf.bw != VFB_BW_NULL){
		if(vfb_rf.bw == VFB_BW_DONE){ // reset to normal mode
			unset_tef810x_long_profile();
		}
		else{ 				// enter vertical feedback mode
			sctrl_profiletiming_t rfp = {0};
			rfp.bandwidth = vfb_rf.bw;
			rfp.hpf = vfb_rf.hpf;
			set_tef810x_long_profile(&rfp);
			spt_vertical_feedback_finfo_set();
			spt_thlds_set(FRAME_CTX_IDX_LONG);  // apply thld
		}
		vfb_rf.bw = VFB_BW_NULL;
	}
}


/***********************************************************************************************
 * Helios API
 ***********************************************************************************************/
helios_intfc_p get_HES_INTFC_Handler(void) {
	return hes_intfc_p;
}



