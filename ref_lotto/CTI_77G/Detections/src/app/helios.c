#include "helios.h"
#include "SPT.h"
#include "frame.h"		//frame_tgg_in_jsons
#include "console.h"		//PRINTF
//#include "SWT.h"		//clear_SWT0_counter

#define pkt_num_of_workspace		(SIZE_OF_WORK_SPACE/SIZE_PAYLOAD)
#define BIN_HIST		64
#define NUM_PEAK		32
#define BYTE2		2
#define BYTE4		4

extern void SPT_DCP4D_16K(void);

static void Dtype_op_list_def(void);
static void proc_end(void);
static void SPT_data_get(void);
static void data_segmentation(uint16_t nth_pkt, uint8_t *data_addr, uint32_t data_len);
static void adc_data_send(void);
static void range_data_send(void);
static void dpplr_data_send(void);
static void fft3d_data_send(void);
static void hist_data_send(void);
static void peak_data_send(void);

typedef enum {
	CBd_OK = 0,
	CBd_ADC = 1,
	CBd_RANGE = 2,
	CBd_DPPLP = 4,
	CBd_FFT3D = 8,
	CBd_HIST = 16,
	CBd_AOA = 32,
	CBd_MEAS = 64
}CB_data;

typedef enum{
	Bin,			//binary
	Str,			//string
	Json			//json
}ptype;

typedef enum{
	LONG,			//binary
	NEAR,			//string
	BOTH			//json
}lsmode;

typedef struct {
	uint8_t *send_addr;
	uint16_t num_pkt;
	uint16_t rmng_len;
}event_send_t, *event_send_p;

void (*Dtype_op_list[DT_LNG])(void) = {NULL};
static helios_header_t header = {0};
//static RTE_services_P rte_srv = NULL;
//static SYS_HAL_p hal = NULL;
static uint8_t long_short = 0;
static uint8_t data_stage = 0;
static uint8_t data_mask[7] = {0x1, 0x2, 0x6, 0xC, 0x1C, 0x1C, 0x5c};
static helios_t helios = {0};helios_p hes = &helios;
static event_send_t event_send = {0};event_send_p ev_send = &event_send;
static helios_intfc_p hes_intfc_p = NULL;
static uint8_t *adc_sample = (uint8_t*)ADC_SAMPLES;
static uint8_t *fft3d_log2 = (uint8_t*)FFT3D_LOG2;
static uint8_t *hist_bins = (uint8_t*)HIST_BINS;
static uint8_t *hist_tones = (uint8_t*)PEAKS_OVER_THLD;
static uint8_t *ws_sample = (uint8_t*)WORK_SPACE;
static uint16_t rmng_num_of_pkt = 0;

////////////////////////////////////////////////////////////////////////
//public
////////////////////////////////////////////////////////////////////////
void helios_init(frame_proc_p frame_func) {
	//rte_srv = get_RTE_Handler();
	//hal = get_HAL_Handler();
	hes_intfc_p = get_HES_INTFC_Handler();
	hes_intfc_p->aoaprint = aoa_printf;
	Dtype_op_list_def();
	hes->hdr_p = &header;
	hes->fproc = frame_func;
}

void helios_rcvr_handler(IsoTpLink *isotp_link) {
	if(ISOTP_RECEIVE_STATUS_FULL == isotp_link->receive_status) {
		memcpy(hes->hdr_p, isotp_link->receive_buffer, SIZE_HELIOS_HEADER);
		hes->isotp_link = isotp_link;
		Dtype_op_list[hes->hdr_p->DT]();
	}
}

helios_p get_HES_Handler(void) {
	return hes;
}

void aoa_printf(uint8_t *data_addr, uint16_t data_len) {
	uint8_t num_pkt = data_len/SIZE_PAYLOAD, i;
	uint16_t rmng_len;
	rmng_len = data_len - num_pkt*SIZE_PAYLOAD;
	if (rmng_len)
		num_pkt++;
	for (i = 0; i < num_pkt; ++i) {
#ifdef ENABLE_SWT
		hal->SWT_HAL->clear_SWT_counter();
#endif
		if (num_pkt - 1 == i && rmng_len != 0) {
			isotp_just_send(
			   Transmitter_ID,
			   data_addr + i*SIZE_PAYLOAD,
			   rmng_len);
		} else {
			isotp_just_send(
			   Transmitter_ID,
			   data_addr+ i*SIZE_PAYLOAD,
			   SIZE_PAYLOAD);
		}
	}
}
////////////////////////////////////////////////////////////////////////
//private
////////////////////////////////////////////////////////////////////////
void mmap_handle(void) {
//	char ws[1536];
//	hes->hdr_p->PDT = Json;
//	int count = SPT_mapped(ws, 1536);
//	data_segmentation(1, (uint8_t*)ws, count);
}

void mem_handle(void) {
	uint8_t *addr = (uint8_t*)FOURCOMB(hes->hdr_p->RSVD2, hes->hdr_p->RSVD3,
							   	   	   hes->hdr_p->RSVD4, hes->hdr_p->RSVD5);
	uint16_t len = TWOCOMB(hes->hdr_p->RSVD6, hes->hdr_p->RSVD7);
	if (hes->hdr_p->RW == 0) {
		data_segmentation(1, (uint8_t*)addr, len);
	} else {
		memcpy((uint8_t*)addr, hes->isotp_link->receive_buffer + SIZE_HELIOS_HEADER, len);
		data_segmentation(1, NULL, 0);
	}
}

void text_handle(void) {

}

void param_handle(void) {
	hes->hdr_p->PDT = Json;
	char *ws =  (char*)spt_work_space_get();
	uint32_t id = FOURCOMB(hes->hdr_p->RSVD2, hes->hdr_p->RSVD3,
						 hes->hdr_p->RSVD4, hes->hdr_p->RSVD5);
	int count = pars_json_data_get(id, ws);
	data_segmentation(1, (uint8_t*)ws, count);
//	for(i=0; i<count; ++i)
//		PRINTF("%c",ws[i]);
}

void rfsp_handle(void) {
	if (hes->hdr_p->RW == 0) {
		hes->hdr_p->RSVD2 = MEAS_MOD_WR;
		hes->hdr_p->RSVD3 = MEAS_FLAGS_WR;
		hes->hdr_p->RSVD4 = data_stage;
		data_segmentation(1, NULL, 0);
	} else {
		MEAS_MOD_WR = hes->hdr_p->RSVD2;
		MEAS_FLAGS_WR = hes->hdr_p->RSVD3;
		data_stage = hes->hdr_p->RSVD4;
		hes_intfc_p->datastage = data_stage;
	}
}

void lnch_handle(void) {
	event_proc_p helios_done_CB;
	long_short = hes->hdr_p->RSVD3;
	if (data_stage == 0)
		helios_done_CB = (event_proc_p)proc_end;
	else
		helios_done_CB = (event_proc_p)SPT_data_get;
	if (!hes->hdr_p->RSVD2)
		hes->hdr_p->RSVD2 = 41;
	switch (long_short) {
		case 0:			//long
			hes->fproc->play(0, 1, hes->hdr_p->RSVD2, helios_done_CB, NULL);
			break;
		case 1:			//near
			hes->fproc->play(1, 0, hes->hdr_p->RSVD2, helios_done_CB, NULL);
			break;
		case 2:
			hes->fproc->play(1, 1, hes->hdr_p->RSVD2, helios_done_CB, NULL);
			break;
		default:
			break;
	}
}

void pause_handle(void) {
	hes->fproc->pause(NULL, 0);
}

void play_handle(void) {
	long_short = hes->hdr_p->RSVD3;
	if (!hes->hdr_p->RSVD2)
		hes->hdr_p->RSVD2 = 41;
	switch (long_short) {
		case 0:			//long
			hes->fproc->play(0, 1, hes->hdr_p->RSVD2, NULL, NULL);
			break;
		case 1:			//near
			hes->fproc->play(1, 0, hes->hdr_p->RSVD2, NULL, NULL);
			break;
		case 2:
			hes->fproc->play(1, 1, hes->hdr_p->RSVD2, NULL, NULL);
			break;
		default:
			break;
	}
}

void cont_handle(void) {
//	spt_set_continue_flag();
}

void adc_handle(void) {
	hes->hdr_p->DT = DT_ADC;

	if (long_short == LONG)
		rmng_num_of_pkt = SAMPLES_PER_CHIRP*CHIRPS_PER_FRAME*TOTAL_RX_ACTIVES*BYTE2/SIZE_PAYLOAD;
	else if (long_short == NEAR)
		rmng_num_of_pkt = SAMPLES_PER_CHIRP*(CHIRPS_PER_FRAME*2)*RX_ACTIVES*BYTE2/SIZE_PAYLOAD;
	else
		rmng_num_of_pkt = 0;

	if (hes->hdr_p->RW == 0) {
		ev_send->num_pkt = rmng_num_of_pkt;
		adc_data_send();
	} else {
		uint16_t pkt_len = TWOCOMB(hes->hdr_p->RSVD2, hes->hdr_p->RSVD3);

		if (pkt_len > rmng_num_of_pkt)
			PRINTF("adc packet length too long ...");

		memcpy(adc_sample + pkt_len*SIZE_PAYLOAD,
			   hes->isotp_link->receive_buffer + SIZE_HELIOS_HEADER,
			   hes->isotp_link->receive_size - SIZE_HELIOS_HEADER);
		data_segmentation(1, NULL, 0);
	}
}

void adc_data_send(void) {
	if (rmng_num_of_pkt) {
		ev_send->send_addr = adc_sample + (ev_send->num_pkt - rmng_num_of_pkt)*SIZE_PAYLOAD;
		data_segmentation(rmng_num_of_pkt, ev_send->send_addr, SIZE_PAYLOAD);
		put_event("adc_send", (event_proc_p)adc_data_send, NULL);
		--rmng_num_of_pkt;
	}
}

void range_handle(void) {
	hes->hdr_p->DT = DT_RANGE;

	if (long_short == LONG)
		rmng_num_of_pkt = 32*pkt_num_of_workspace;			//0x80000/0x4000 = 0x20
	else if (long_short == NEAR)
		rmng_num_of_pkt = 16*pkt_num_of_workspace;			//0x80000/0x4000/2
	else
		rmng_num_of_pkt = 0;

	if (hes->hdr_p->RW == 0) {
		SPT.WR_R0_IM.R = 0x0000;
		SPT.WR_R0_RE.R = 0x9000;
		SPT.WR_R1_RE.R = 0x9000;
		SPT.WR_R1_IM.R = 0x0000;
		range_data_send();
	} else {

	}

}

void range_data_send(void) {
	if (long_short == LONG)
		ev_send->num_pkt = 32*pkt_num_of_workspace - rmng_num_of_pkt;		//0x80000/0x4000 = 0x20
	else if (long_short == NEAR)
		ev_send->num_pkt = 16*pkt_num_of_workspace - rmng_num_of_pkt;		//0x80000/0x4000/2
	else
		rmng_num_of_pkt = 0;

	if (rmng_num_of_pkt) {
		if (ev_send->num_pkt * SIZE_PAYLOAD % SIZE_OF_WORK_SPACE == 0) {
			SPT_exec(SPT_DCP4D_16K, TRUE);
			SPT.WR_R0_IM.R += 0x4000;
		}
		ev_send->send_addr = ws_sample + (ev_send->num_pkt * SIZE_PAYLOAD % SIZE_OF_WORK_SPACE);
		data_segmentation(rmng_num_of_pkt, ev_send->send_addr, SIZE_PAYLOAD);
		put_event("range_send", (event_proc_p)range_data_send, NULL);
		--rmng_num_of_pkt;
	}
}

void dpplr_handle(void) {
	hes->hdr_p->DT = DT_DPPLR;

	if (long_short == LONG)
		rmng_num_of_pkt = 32*pkt_num_of_workspace;			//0x80000/0x4000 = 0x20
	else if (long_short == NEAR)
		rmng_num_of_pkt = 16*pkt_num_of_workspace;			//0x80000/0x4000/2
	else
		rmng_num_of_pkt = 0;

	if (hes->hdr_p->RW == 0) {
		SPT.WR_R0_IM.R = 0x80000;
		SPT.WR_R0_RE.R = 0x9000;
		SPT.WR_R1_RE.R = 0x9000;
		SPT.WR_R1_IM.R = 0x0000;
		dpplr_data_send();
	} else {

	}
}

void dpplr_data_send(void) {
	if (long_short == LONG)
		ev_send->num_pkt = 32*pkt_num_of_workspace - rmng_num_of_pkt;		//0x80000/0x4000 = 0x20
	else if (long_short == NEAR)
		ev_send->num_pkt = 16*pkt_num_of_workspace - rmng_num_of_pkt;		//0x80000/0x4000/2
	else
		rmng_num_of_pkt = 0;

	if (rmng_num_of_pkt) {
		if (ev_send->num_pkt * SIZE_PAYLOAD % SIZE_OF_WORK_SPACE == 0) {								//0x8000/1024
			SPT_exec(SPT_DCP4D_16K, TRUE);
			SPT.WR_R0_IM.R += 0x4000;
		}
		ev_send->send_addr = ws_sample + (ev_send->num_pkt * SIZE_PAYLOAD % SIZE_OF_WORK_SPACE);
		data_segmentation(rmng_num_of_pkt, ev_send->send_addr, SIZE_PAYLOAD);
		put_event("dpplr_send", (event_proc_p)dpplr_data_send, NULL);
		--rmng_num_of_pkt;
	}
}

void fft3d_handle(void) {
	hes->hdr_p->DT = DT_FFT3D;

	if (long_short == LONG)
		rmng_num_of_pkt = SAMPLES_PER_CHIRP*CHIRPS_PER_FRAME*BYTE4/SIZE_PAYLOAD;
	else if (long_short == NEAR)
		rmng_num_of_pkt = SAMPLES_PER_CHIRP/2*CHIRPS_PER_FRAME*BYTE4/SIZE_PAYLOAD;
	else
		rmng_num_of_pkt = 0;

	if (hes->hdr_p->RW == 0) {
		ev_send->num_pkt = rmng_num_of_pkt;
		fft3d_data_send();
	} else {
		uint16_t pkt_len = TWOCOMB(hes->hdr_p->RSVD2, hes->hdr_p->RSVD3);

		if (pkt_len > rmng_num_of_pkt)
			PRINTF("fft3d packet length too long ...");

		memcpy(fft3d_log2 + pkt_len*SIZE_PAYLOAD,
			   hes->isotp_link->receive_buffer + SIZE_HELIOS_HEADER,
			   hes->isotp_link->receive_size - SIZE_HELIOS_HEADER);
		data_segmentation(1, NULL, 0);
	}
}

void fft3d_data_send(void) {
	if (rmng_num_of_pkt) {
		if (long_short == LONG)
			ev_send->send_addr = fft3d_log2 + (ev_send->num_pkt - rmng_num_of_pkt)*SIZE_PAYLOAD;
		else if (long_short == NEAR)
			ev_send->send_addr = fft3d_log2+0x20000 + (ev_send->num_pkt - rmng_num_of_pkt)*SIZE_PAYLOAD;
		else
			ev_send->send_addr = 0;

		data_segmentation(rmng_num_of_pkt, ev_send->send_addr, SIZE_PAYLOAD);
		put_event("fft3d_send", (event_proc_p)fft3d_data_send, NULL);
		--rmng_num_of_pkt;
	}
}

void hist_handle(void) {
	hes->hdr_p->DT = DT_HIST;

	if (long_short == LONG)
		rmng_num_of_pkt = SAMPLES_PER_CHIRP/2*BIN_HIST*BYTE2/SIZE_PAYLOAD;
	else if (long_short == NEAR)
		rmng_num_of_pkt = SAMPLES_PER_CHIRP/2*BIN_HIST*BYTE2/SIZE_PAYLOAD/2;
	else
		rmng_num_of_pkt = 0;

	if (hes->hdr_p->RW == 0) {
		ev_send->num_pkt = rmng_num_of_pkt;
		hist_data_send();
	} else {
		uint16_t pkt_len = TWOCOMB(hes->hdr_p->RSVD2, hes->hdr_p->RSVD3);

		if (pkt_len > rmng_num_of_pkt)
					PRINTF("hist packet length too long ...");

		memcpy(hist_bins + pkt_len*SIZE_PAYLOAD,
			   hes->isotp_link->receive_buffer + SIZE_HELIOS_HEADER,
			   hes->isotp_link->receive_size - SIZE_HELIOS_HEADER);
		data_segmentation(1, NULL, 0);
	}
}

void hist_data_send(void) {
	if (rmng_num_of_pkt) {
		ev_send->send_addr = hist_bins + (ev_send->num_pkt - rmng_num_of_pkt)*SIZE_PAYLOAD;
		data_segmentation(rmng_num_of_pkt, ev_send->send_addr, SIZE_PAYLOAD);
		put_event("hist_send", (event_proc_p)hist_data_send, NULL);
		--rmng_num_of_pkt;
	}
}

void peak_handle(void) {
	hes->hdr_p->DT = DT_PEAK;

	if (long_short == LONG)
		rmng_num_of_pkt = SAMPLES_PER_CHIRP/2*NUM_PEAK*BYTE4/SIZE_PAYLOAD;
	else if (long_short == NEAR)
		rmng_num_of_pkt = SAMPLES_PER_CHIRP/2*NUM_PEAK*BYTE4/SIZE_PAYLOAD/2;
	else
		rmng_num_of_pkt = 0;

	if (hes->hdr_p->RW == 0) {
		ev_send->num_pkt = rmng_num_of_pkt;
		peak_data_send();
	} else {
		uint16_t pkt_len = TWOCOMB(hes->hdr_p->RSVD2, hes->hdr_p->RSVD3);

		if (pkt_len > rmng_num_of_pkt)
					PRINTF("peak packet length too long ...");

		memcpy(hist_tones + pkt_len*SIZE_PAYLOAD,
			   hes->isotp_link->receive_buffer + SIZE_HELIOS_HEADER,
			   hes->isotp_link->receive_size - SIZE_HELIOS_HEADER);
		data_segmentation(1, NULL, 0);
	}
}

void peak_data_send(void) {
	if (rmng_num_of_pkt) {
		ev_send->send_addr = hist_tones + (ev_send->num_pkt - rmng_num_of_pkt)*SIZE_PAYLOAD;
		data_segmentation(rmng_num_of_pkt, ev_send->send_addr, SIZE_PAYLOAD);
		put_event("peak_send", (event_proc_p)peak_data_send, NULL);
		--rmng_num_of_pkt;
	}
}

void meas_handle(void) {
	hes->hdr_p->DT = DT_MEAS;

	if (hes->hdr_p->RW == 0) {
		hes->hdr_p->PDT = Json;
		int idx = 0;
		if (long_short == LONG)
			idx = FRAME_CTX_IDX_LONG;
		else if (long_short == NEAR)
			idx = FRAME_CTX_IDX_NEAR;
		char* ws = (char*)spt_work_space_get();
		uint32_t len = (uint32_t)frame_tgg_in_jsons(spt_target_group_get(idx), ws);
		data_segmentation(1, (uint8_t*)ws, len);
	} else {

	}
}

void Dtype_op_list_def(void) {
	Dtype_op_list[DT_MMAP] = mmap_handle;
	Dtype_op_list[DT_MEM] = mem_handle;
	Dtype_op_list[DT_TEXT] = text_handle;
	Dtype_op_list[DT_PARAM] = param_handle;
	Dtype_op_list[DT_RFSP] = rfsp_handle;
	Dtype_op_list[DT_LNCH] = lnch_handle;
	Dtype_op_list[DT_PAUSE] = pause_handle;
	Dtype_op_list[DT_PLAY] = play_handle;
	Dtype_op_list[DT_CONT] = cont_handle;
	Dtype_op_list[DT_ADC] = adc_handle;
	Dtype_op_list[DT_RANGE] = range_handle;
	Dtype_op_list[DT_DPPLR] = dpplr_handle;
	Dtype_op_list[DT_FFT3D] = fft3d_handle;
	Dtype_op_list[DT_HIST] = hist_handle;
	Dtype_op_list[DT_PEAK] = peak_handle;
	Dtype_op_list[DT_MEAS] = meas_handle;
}

void proc_end(void) {
	memset(hes->hdr_p, 0, 8);
	hes->hdr_p->DT = DT_LNCH;
	data_segmentation(1, NULL, 0);
}

void SPT_data_get(void) {
	uint8_t op_mask = data_stage & data_mask[MEAS_MOD_WR];
	hes->hdr_p->RW = 0;
	if ((op_mask & CBd_ADC) == CBd_ADC)
		Dtype_op_list[DT_ADC]();
	if ((op_mask & CBd_RANGE) == CBd_RANGE)
		Dtype_op_list[DT_RANGE]();
	if ((op_mask & CBd_DPPLP) == CBd_DPPLP)
		Dtype_op_list[DT_DPPLR]();
	if ((op_mask & CBd_FFT3D) == CBd_FFT3D)
		Dtype_op_list[DT_FFT3D]();
	if ((op_mask & CBd_HIST) == CBd_HIST)
		Dtype_op_list[DT_HIST]();
//	if ((op_mask & CBd_AOA) == CBd_AOA)
	if ((op_mask & CBd_MEAS) == CBd_MEAS)
		Dtype_op_list[DT_MEAS]();
}

void data_segmentation(uint16_t nth_pkt, uint8_t *data_addr, uint32_t data_len) {
	if (!data_len) {
		isotp_custom_send(
			Transmitter_ID,
			(uint8_t*)hes->hdr_p,
			SIZE_HELIOS_HEADER,
			NULL,
			0);
	} else {
		uint16_t i, rmng_len;
		uint16_t num_pkt = data_len/SIZE_PAYLOAD;
		rmng_len = data_len - num_pkt*SIZE_PAYLOAD;
		if (rmng_len)
			num_pkt++;
//	uint32_t start_time = hal->TIMER_HAL->get_SMT_1_CNT();
		for (i = 0; i < num_pkt; ++i) {
/*
#ifdef ENABLE_SWT
		clear_SWT0_counter();
#endif
*/
	   		if(hes->hdr_p->DT!=DT_MEM){
				hes->hdr_p->RSVD2 = (uint8_t)(((nth_pkt - 1)*num_pkt + (num_pkt - i - 1)) >> 8 & 0xFF);
				hes->hdr_p->RSVD3 = (uint8_t)(((nth_pkt - 1)*num_pkt + (num_pkt - i - 1)) & 0xFF);
	   		}
			//PRINTF("nth_pkt: %d \n", ((nth_pkt - 1) * num_pkt + (num_pkt - i - 1) ));
			if (num_pkt - 1 == i && rmng_len != 0) {
				isotp_custom_send(
					Transmitter_ID,
					(uint8_t*)hes->hdr_p,
					SIZE_HELIOS_HEADER,
					data_addr + i*SIZE_PAYLOAD,
					rmng_len);
			} else {
				isotp_custom_send(
					Transmitter_ID,
					(uint8_t*)hes->hdr_p,
					SIZE_HELIOS_HEADER,
					data_addr + i*SIZE_PAYLOAD,
					SIZE_PAYLOAD);
			}
		}
	}
//	uint32_t end_time = hal->TIMER_HAL->get_SMT_1_CNT();
//	float total_time = (end_time-start_time) * 0.01667;
//	PRINTF("Total_Time:%f\n", total_time);
}
