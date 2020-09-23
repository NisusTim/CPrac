/*
 * netagent.c
 *
 *  Created on: 2017�~4��11��
 *      Author: erichu
 */


#include "sys_shared.h"
#include "spt.h"

extern frame_data_t frame_data;
extern void SPT_FFT16x32(void);

typedef struct {
	uint32_t		time;
	uint16_t		size_of_enet_packets;
	uint16_t		pkts;
	uint16_t		idx;
	uint16_t		seq_id;
	uint16_t		frm_attr[8];
	target_group_p	tgg;
	uint32_t		offs;
	uint8_t			ack_id;
	uint8_t			wait_done;
}netagent_handle_t, *netagent_handle_p;

static netagent_handle_t na_handle={0}, *na = &na_handle;

static void na_tester(char**,int);
static void na_raw_start(target_group_p);
static void na_fft_start(target_group_p);
static void na_fft3d_start(target_group_p);
static void na_fft_send(uint32_t);
static void na_aoa_handler(target_group_p);
static void na_measurements_start(target_group_p);

void na_init(void)
{
	ENET_init();
	console_command_reg("na", na_tester);
	na->size_of_enet_packets = enet_tx_done_reg(NULL, NULL);
}

void na_fndat_start(uint8_t type, uint16_t pkts, uint16_t pkts_total)
{
	na->frm_attr[FRM_ATTR_PKTSZ_SEQ] = pkts;
	na->frm_attr[FRM_ATTR_PKTSZ_TOTAL] = pkts_total;
	na->frm_attr[FRM_ATTR_FS_TYPE] = (((uint16_t)na->tgg->idx)<<8) + type;
	na->frm_attr[FRM_ATTR_FN] = frame_data.counter;

	if(type == NAPT_RAW) {
		na->frm_attr[FRM_ATTR_SPEED] = get_eps_speed_value();
		na->frm_attr[FRM_ATTR_YAW] = get_veh_filtered_yaw_rate_value();
		na->frm_attr[FRM_ATTR_STEERING] = get_steering_angle_value();
	}
}

void na_raw_repeat(int d)
{
	uint32_t raw;
	uint16_t end;

	if(na->idx >= na->pkts){ // 4 packet per chirps
		enet_tx_done_reg(NULL, NULL);
		//PRINTF("na: raw done in %ldus\n", (uint32_t)((STM_0.CNT.R-na->time)*CLOCK_PERIOD_US));
		return;
	}

	end = na->idx + na->size_of_enet_packets;
	if(end > na->pkts)
		end = na->pkts;

	raw = na->offs+(uint32_t)na->idx*SIZE_OF_ENET_PACKET_DATA;
	while(na->idx < end) {
		if(enet_add_packet(NAMISC_DATA, NAPT_RAW, na->frm_attr[na->idx&0x07], na->idx+na->seq_id, (uint8_t*)raw, SIZE_OF_ENET_PACKET_DATA) == TRUE) {
			na->idx++;
			raw += SIZE_OF_ENET_PACKET_DATA;
		}
	}
}

void na_raw_start(target_group_p tgg)
{
	if(!tgg)
		return;

	na->wait_done = 1;
	na->tgg = tgg;
	na->time = STM_0.CNT.R;
	enet_tx_done_reg((event_proc_p)na_raw_repeat, NULL);
	na->pkts = (SAMPLES_PER_CHIRP*2*CHIRPS_PER_FRAME*8)/SIZE_OF_ENET_PACKET_DATA;
	na->offs = ADC_SAMPLES;
	na->idx = 0;
	na->seq_id += 0x1000;

	if(frame_ctx_seq_get())
		na->seq_id |= 0x0400;
	else
		na->seq_id &= 0xF000;

	na_fndat_start(NAPT_RAW, na->pkts, na->pkts);
	PRINTF("na:raw(%u) %04X %.1fms\n", (uint16_t)frame_data.counter, na->seq_id, STM_0.CNT.R*CLOCK_PERIOD_MS);
	na_raw_repeat(NULL);
}

void na_dcp4d_done(void* x)
{
	uint32_t end = na->idx+64, data=WORK_SPACE;
	uint8_t	type = NAPT_RANGE;

	if(na->offs >= (DOPPLER_DATA-RANGE_DATA))
		type = NAPT_DOPPLER;

	while(na->idx < end) {
		if(enet_add_packet(NAMISC_DATA, type, na->pkts, na->idx, (uint8_t*)data, SIZE_OF_ENET_PACKET_DATA) == TRUE) {
			data += SIZE_OF_ENET_PACKET_DATA;
			na->idx++;
		}
	}

	//PRINTF("na: dcp4d send %04X\n", na->idx-64);
}

static void na_fft_send(uint32_t offs){

	na->seq_id = 0;
	na->offs = offs;
	na->pkts = 64; // total packets of doppler and ranged data
	na->idx = offs/256;
	if(na->idx >= 2048)
		na->idx -= 2048;

	SPT.WR_R0_IM.R = na->offs + RANGE_DATA;
	SPT.WR_R0_RE.R = 0x9000;
	SPT.WR_R1_RE.R = 0x9000;
	SPT.WR_R1_IM.R = 0;

	//PRINTF("na fft: offs=%06lX, WR0_RE=%06X, WR0_IM=%06X, WR1_RE=%06X, WR1_IM=%06X\n", offs,
			//SPT.WR_R0_RE.R, SPT.WR_R0_IM.R, SPT.WR_R1_RE.R, SPT.WR_R1_IM.R);

	spt_context_start(SPT_CONTEXT_DCP4D_16K, na_dcp4d_done, NULL);
}

static void na_fft_start(target_group_p tgg)
{
	if (MEAS_MOD_WR == MEAS_MOD_FFT)
		na_fft_send(0);
	else
		na_fft_send(DOPPLER_DATA-RANGE_DATA); // Doppler data
}

static void na_fft3d_start(target_group_p tgg)
{
	uint8_t	type = NAPT_FFT3D;
	uint32_t raw;
	int end;

	na->seq_id = 0;
	na->offs = FFT3D_DEBUG_DATA;
	na->pkts = 64;
	na->idx = SPT.WR_R6_RE.R*na->pkts;
	end = na->idx + na->pkts;
	na->wait_done = 1;
	PRINTF("na: fft3d secs=%ld,idx=%d,pkts=%d\n",
		SPT.WR_R6_RE.R, na->idx, na->pkts);
	raw = na->offs;
	while(na->idx < end) {
		if(enet_add_packet(NAMISC_DATA, type, na->pkts, na->idx, (uint8_t*)raw, SIZE_OF_ENET_PACKET_DATA) == TRUE) {
			na->idx++;
			raw += SIZE_OF_ENET_PACKET_DATA;
		}
	}
}

static void na_hist_start(target_group_p tgg)
{
	uint8_t	type = NAPT_HIST;
	uint32_t raw;

	na->seq_id = 0;
	na->idx = 0;
	if(tgg->rcnt == TOTAL_RX_ACTIVES) {
		na->offs = FFT3D_LOG2;
		na->pkts = 256+32;
	}
	else {
		na->offs = FFT3D_LOG2+0x20000;
		na->pkts = 128+16;
	}
	//PRINTF("na: log2/hist offs=%08lX, pkts=%d\n", na->offs, na->pkts);

	raw = na->offs;
	while(na->idx < na->pkts) {
		if(enet_add_packet(NAMISC_DATA, type, na->pkts, na->idx, (uint8_t*)raw, SIZE_OF_ENET_PACKET_DATA) == TRUE) {
			na->idx++;
			raw += SIZE_OF_ENET_PACKET_DATA;
		}
	}
}

static void na_fft16_send(void)
{
	uint8_t	type = NAPT_FFT16;
	uint32_t raw;

	na->seq_id = 0;
	na->idx = 0;
	na->offs = WORK_SPACE+0x8000;
	na->pkts = 16;
	PRINTF("na: fft16 offs=%08lX, pkts=%d\n", na->offs, na->pkts);

	raw = na->offs;
	while(na->idx < na->pkts) {
		if(enet_add_packet(NAMISC_DATA, type, na->pkts, na->idx, (uint8_t*)raw, SIZE_OF_ENET_PACKET_DATA) == TRUE) {
			na->idx++;
			raw += SIZE_OF_ENET_PACKET_DATA;
		}
	}
}

static void na_aoa_handler(target_group_p tgg)
{
#if 1
	na->tgg = tgg;
	na->pkts = 24; // 24KB LR
	if(tgg->rcnt == RX_ACTIVES)
		na->pkts = 8;		// 8KB SR

	na->offs = AOA_FFT_DATA;
	na->seq_id = 0;
	na->idx = SPT.WR_R6_RE.R*na->pkts;
	na->wait_done = 1;

	int end = na->idx+na->pkts;
	PRINTF("na: aoa tgidx=%04lX, start=%04X, pkts=%d\n", SPT.WR_R6_RE.R, na->idx, na->pkts);
	uint8_t *ws=(uint8_t*)na->offs;
	while(na->idx < end) {
		if(enet_add_packet(NAMISC_DATA, NAPT_AOA_DATA, na->pkts, na->idx,
				(uint8_t*)ws, SIZE_OF_ENET_PACKET_DATA) == TRUE) {
			na->idx++;
			ws += SIZE_OF_ENET_PACKET_DATA;
		}
	}
#else
	target_aoa_data_p tad = (target_aoa_data_p)TARGET_AOA_DATA;
	print_cmpsed_cmplx(tad+SPT.WR_R6_RE.R,tgg->rcnt);
	SPT.CS_SW_EVTREG.B.SW_EVTREG = 1<<2; // AGGREGATION_DONE_EVENT
#endif
}

static void na_measurements_start(target_group_p tgg)
{
	uint8_t *ws=(uint8_t*)WORK_SPACE;
	int cnt = frame_tgg_in_jsons(tgg, (char*)ws);
	uint16_t count = 0;

	na->offs = (uint32_t)ws;
	na->seq_id = 0;
	na->idx = 0;
	na->pkts = cnt/SIZE_OF_ENET_PACKET_DATA;
	if(cnt&(SIZE_OF_ENET_PACKET_DATA-1))
		na->pkts++;

	PRINTF("na: meas cnt=%04X, pkts=%d\n", cnt, na->pkts);
	while(na->idx < na->pkts) {
		if(cnt > SIZE_OF_ENET_PACKET_DATA)
			count = SIZE_OF_ENET_PACKET_DATA;
		else
			count = cnt;
		if(enet_add_packet(NAMISC_DATA, NAPT_MEASUREMENTS, na->pkts, na->idx, ws, count) == TRUE) {
			na->idx++;
			ws += SIZE_OF_ENET_PACKET_DATA;
			cnt -= count;
		}
	}
}

/*
 * type : DT_ACK
 * attr : origin type of ack
 * idx  : reserved
 * data : message of ack
 */
void na_ack(uint8_t type, uint16_t attr, uint16_t idx, void* data, uint16_t sz)
{
	if(data != NULL && sz){
		enet_txbuf_p tb=enet_txbuf_get();
		memcpy((void*)tb->buf, data, sz);
		enet_add_packet(NAMISC_ACK, type, attr, idx, tb->buf, sz);
	}
	else
		enet_add_packet(NAMISC_ACK, type, attr, idx, NULL, 0);
	//PRINTF("na ack: %01X:%03X\n", type, sub);
}

void na_missed_send(uint8_t type, uint16_t idx)
{
	uint32_t data;
	uint16_t attr = na->frm_attr[idx&0x03];
	if (type == NAPT_RAW) {
		attr= na->frm_attr[idx&0x07];
		data = (uint32_t)ADC_SAMPLES+(uint32_t)idx*SIZE_OF_ENET_PACKET_DATA;
	}

	else if(type == NAPT_RANGE || type == NAPT_DOPPLER){
		data = WORK_SPACE+((idx%na->pkts)*SIZE_OF_ENET_PACKET_DATA);
		attr = na->pkts;
	}

	/*else if(type == NAPT_AOA_DATA || type == NAPT_FFT3D){
		data = na->offs + (idx%na->pkts)*SIZE_OF_ENET_PACKET_DATA;
		attr = na->pkts;
	}*/
	else if(type < NAPT_INVALID){
		data = na->offs + (idx%na->pkts)*SIZE_OF_ENET_PACKET_DATA;
		attr = na->pkts;
	}

	else {
		PRINTF("unknown missed type %d\n", type);
		return;
	}

	if(enet_add_packet(NAMISC_DATA, type, attr, na->seq_id+idx,(uint8_t*)data, SIZE_OF_ENET_PACKET_DATA) == FALSE)
		PRINTF("Failed to resend packet %d\n",idx);
}

/*
 * missed pkt:
 * attr : missed data type,
 * sub : -1, STP_start missed
 * data : missed subs
 */
void na_missed_handler(na_packet_p pkt)
{
	uint16_t *idxs = (uint16_t*)pkt->data, *end = idxs+pkt->hdr.idx;
	if((pkt->hdr.attr&0xF000) != (na->seq_id&0xF000)) {
		PRINTF("Missed chirps id %04X:%04X not matched\n", pkt->hdr.attr, na->seq_id);
		return;
	}

	PRINTF("na: tx missed %04X:%04X\n", pkt->hdr.attr, pkt->hdr.idx);
	while(idxs != end)
		na_missed_send(pkt->hdr.attr, *idxs++);
}

void na_mem_handler(na_packet_p pkt)
{
	uint32_t addr = ((uint32_t)pkt->hdr.attr<<16) + pkt->hdr.idx;
	if(pkt->hdr.misc == NAMISC_GET){
		uint16_t *d = (uint16_t*)pkt->data;
		uint32_t sz = ((uint32_t)(*d)<<16) + *(d+1);
		na->offs = addr;
		na->seq_id = 0;
		na->idx = 0;
		na->pkts = sz/SIZE_OF_ENET_PACKET_DATA;
		if(sz & (SIZE_OF_ENET_PACKET_DATA-1))
			na->pkts++;

		if(na->pkts > na->size_of_enet_packets){
			PRINTF("na: too large of mem size(%08lX) to get!\n", sz);
			return;
		}
		else
			PRINTF("na: mem %06lX:%06lX get..\n", na->offs, sz);

		while(na->idx < na->pkts) {
			if(enet_add_packet(NAMISC_DATA, NAPT_MEM, na->pkts, na->idx, (uint8_t*)addr, SIZE_OF_ENET_PACKET_DATA) == TRUE) {
				na->idx++;
				addr += SIZE_OF_ENET_PACKET_DATA;
			}
		}
	}
	else if(pkt->hdr.misc == NAMISC_SET){
		uint16_t sz = pkt->hdr.length-sizeof(nap_header_t);
		if(sz <= SIZE_OF_ENET_PACKET_DATA)
			memcpy((void*)addr, pkt->data, sz);
	}
}

void na_dump_header(na_packet_p pkt)
{
	uint16_t* d = &pkt->hdr.length;
	PRINTF("nahdr: %04X%04X %04X%04X %.1fms\n",d[0],d[1],d[2],d[3],STM_0.CNT.R*CLOCK_PERIOD_MS);
	//console_flush();
}

void na_packet_handler(na_packet_p pkt)
{
	uint32_t val;
	uint8_t type, ack_id;

	//na_dump_header(pkt);

	ack_id = pkt->hdr.type & 0xF0;
	if(ack_id != 0) {
		na_ack(pkt->hdr.type, pkt->hdr.attr, pkt->hdr.idx, NULL, 0);
		if(ack_id == na->ack_id)
			return;
	}

	na->ack_id = ack_id;
	type = pkt->hdr.type&0x0F;

	switch(type) {
	case NAPT_RAW :
		if(pkt->hdr.misc == NAMISC_SET){
			val = pkt->hdr.idx*SIZE_OF_ENET_PACKET_DATA;
			if(val < 0x100000){
				memcpy((void*)(val+ADC_SAMPLES), pkt->data, SIZE_OF_ENET_PACKET_DATA);
			}
			//PRINTF("na: raw set %04X:%06lX\n", pkt->hdr.idx, val);
		}
		else if(pkt->hdr.misc == NAMISC_DONE){
			if(na->wait_done) {
				if(pkt->hdr.idx == (na->seq_id&0xF000)){
					PRINTF("na: done %.1fms\n", (STM_0.CNT.R-na->time)*CLOCK_PERIOD_MS);
					na->wait_done = 0;
					if(na->tgg->idx)
						long_meas_done(na->tgg);
					else
						near_meas_done(na->tgg);
				}
				else
					PRINTF("na: done, but invalid chirps %04X:%04X\n", pkt->hdr.idx, na->seq_id&0xF000);
			}
			else
				PRINTF("na: done already!\n");
		}
		break;
	case NAPT_DOPPLER :
		pkt->data[pkt->hdr.length-8] = 0;
		PRINTF("na: %s\n", pkt->data);
		na_fft_send((DOPPLER_DATA-RANGE_DATA)+pkt->hdr.idx*256);
		break;
	case NAPT_RANGE :
		pkt->data[pkt->hdr.length-8] = 0;
		//PRINTF("na: %s\n", pkt->data);
		na_fft_send(pkt->hdr.idx*256);
		break;
	case NAPT_MEASUREMENTS:
		na_measurements_start(NULL);
		break;
	case NAPT_MEM:
		na_mem_handler(pkt);
		break;
	case NAPT_FFT3D:
		if(pkt->hdr.misc == NAMISC_DONE){
			if(na->wait_done != 0 && pkt->hdr.idx == (uint16_t)(SPT.WR_R6_RE.R)){
				na->wait_done = 0;
				SPT.CS_SW_EVTREG.B.SW_EVTREG = 1<<2; // AGGREGATION_DONE_EVENT
				if(SPT.WR_R6_RE.R == 127) {
					pkt->data[pkt->hdr.length-8] = 0;
					PRINTF("na: %s\n", pkt->data);
				}
			}
			else
				PRINTF("na: fft3d done, but seq %d:%04X:%04lX\n", na->wait_done, pkt->hdr.idx, SPT.WR_R6_RE.R);
		}
		break;
	case NAPT_AOA_DATA:
		if(pkt->hdr.misc == NAMISC_DONE){
			if(na->wait_done != 0 && pkt->hdr.idx == (uint16_t)(SPT.WR_R6_RE.R)){
				na->wait_done = 0;
				SPT.CS_SW_EVTREG.B.SW_EVTREG = 1<<2; // AGGREGATION_DONE_EVENT
				//pkt->data[pkt->hdr.length-8] = 0;
				//PRINTF("na: %s\n", pkt->data);
			}
			else
				PRINTF("na: aoa done, but seq %d:%04X:%04lX\n", na->wait_done, pkt->hdr.idx, SPT.WR_R6_RE.R);
		}
		break;
	case NAPT_MISSED :
		na_missed_handler(pkt);
		break;
	case NAPT_STRING :
		console_proc(pkt->data);
		break;
	}
}

void na_printf(char* fmt, ...)
{
	uint16_t cnt = 0;
	enet_txbuf_p tb = enet_txbuf_get();
    va_list vl;
    va_start(vl, fmt);
    cnt = vsnprintf((char*)tb->buf, SIZE_OF_ENET_PACKET_DATA, fmt, vl);
    va_end(vl);
    tb->buf[cnt] = 0;
	enet_add_packet(NAMISC_DATA, NAPT_STRING, 0,0, (uint8_t*)tb->buf, SIZE_OF_ENET_PACKET_DATA);
}

static void na_tester(char** args, int count)
{
	uint8_t nm=0xFF,lm=0xFF,rate=FRAME_RATE_ONCE, mod=MEAS_MOD_INVALID;
	uint16_t idx = 0;
	event_proc_p cb = NULL;
	if(count > 2){
		if(!strcmp(args[2],"near")){
			nm=1;
			lm=0;
		}
		else if(!strcmp(args[2],"long")){
			nm=0;
			lm=1;
		}
		else if(!strcmp(args[2],"dual")){
			nm=1;
			lm=1;
		}
		else{
			nm = 0;
			lm = 0;
		}

		if(count > 3){
			rate = (uint8_t)strtoul(args[3],NULL,10); // rate if RAW, flags otherwise
			if (rate == 0)
				rate = FRAME_RATE_ONCE;
		}

		if(!strcmp(args[1],"raws")){
			if(nm == 1 || lm == 1) {
				MEAS_FLAGS_WR = 0;
				MEAS_MOD_WR = MEAS_MOD_RAW;
				PRINTF("na playing...(rate=%d,nm=%d,lm=%d)\n", rate, nm, lm);
				frame_measurements_rf_cbs_reg((event_proc_p)na_raw_start, (event_proc_p)na_raw_start);
				frame_play(nm, lm, rate, NULL, NULL);
				na->seq_id = 0x0000;
			}
			else {
				na->pkts = 1024;
				na->offs = ADC_SAMPLES;
				na->idx = 0;
				na->seq_id = 0x1000;

				na_fndat_start(NAPT_RAW, na->pkts, na->pkts);
				PRINTF("na:raw(%u) %04X %.1fms\n", (uint16_t)frame_data.counter, na->seq_id, STM_0.CNT.R*CLOCK_PERIOD_MS);
				na_raw_repeat(NULL);
			}
			return;
		}

		else if(!strcmp(args[1], "dops")){
			idx = (uint16_t)strtoul(args[2],NULL,16);
			na_fft_send((DOPPLER_DATA-RANGE_DATA)+idx*256);
		}

		if(!strcmp(args[1], "fft16")){
			SPT.WR_R0_IM.R = 0;
			SPT.WR_R0_RE.R = TRAM_WORK_SPACE;
			SPT.WR_R1_IM.R = 0;
			SPT.WR_R1_RE.R = 0x8000;
			idx = strtoul(args[2],NULL,16); // idx of velocity, only 0-7 is valid
			if(idx < 8) {
				SPT.WR_R0_IM.R = idx * 0x80;
				SPT.WR_R1_IM.R = idx * 0x40;
			}
			PRINTF("na:fft16 WR0=(%04lX,%04lX), WR1=(%04lX,%04lX)\n",
					SPT.WR_R0_IM.R,SPT.WR_R0_RE.R, SPT.WR_R1_IM.R, SPT.WR_R1_RE.R);
			SPT_exec(SPT_FFT16x32, TRUE);
			na_fft16_send();
		}

		else if(!strcmp(args[1],"hist")) {
			if(nm == 1)
				na_hist_start(&frame_data.tggs[0]);
			else if(lm == 1)
				na_hist_start(&frame_data.tggs[1]);
		}

		else if(!strcmp(args[1], "tggs")){

		}

		else if(!strcmp(args[1],"pars")){
			int cnt = 1, idx = 2, subcnt;
			uint32_t id;
			char* ws = (char*)WORK_SPACE;
			PRINTF("na: pars ");
			ws[0] = '[';
			ws += 1;
			while(idx < count) {
				memcpy(&id, args[idx], 4);
				subcnt = pars_json_data_get(id, ws);
				PRINTF("%c%c%c%c=%d,", args[idx][0], args[idx][1], args[idx][2], args[idx][3], subcnt);
				ws += subcnt;
				cnt += subcnt;
				idx += 1;
				if(idx < count)
					*ws++ = ',';
				else {
					*ws++ = ']';
				}
				cnt++;
			}

			na->pkts = cnt/SIZE_OF_ENET_PACKET_DATA;
			if(cnt&(SIZE_OF_ENET_PACKET_DATA-1))
				na->pkts++;

			PRINTF(" cnt=%d, pkts=%d\n", cnt, na->pkts);

			if(cnt == 0){
				PRINTF("na: invalid pars get!\n");
				return;
			}

			na->idx = 0;
			ws = (char*)WORK_SPACE;
			na->offs = (uint32_t)ws;
			while(na->idx < na->pkts) {
				if(cnt > SIZE_OF_ENET_PACKET_DATA)
					count = SIZE_OF_ENET_PACKET_DATA;
				else
					count = cnt;

				//PRINTF("na: pars send %d,%p,%d\n",na->idx,ws,count);
				if(enet_add_packet(NAMISC_DATA, NAPT_PARAMETERS, na->pkts, na->idx, (uint8_t*)ws, count) == TRUE) {
					na->idx++;
					ws += SIZE_OF_ENET_PACKET_DATA;
					cnt -= count;
				}
			}

			// resend last packet for dummy
			enet_add_packet(NAMISC_DATA, NAPT_PARAMETERS, na->pkts, na->pkts-1, (uint8_t*)ws-SIZE_OF_ENET_PACKET_DATA, count);
		}

		else {
			event_proc_p aoa=NULL, fft3d = NULL;
			if(count > 3)
				MEAS_FLAGS_WR = (uint32_t)strtoul(args[3],NULL,16);
			else
				MEAS_FLAGS_WR = MEAS_FLAG_FROM_RAWS | MEAS_FLAG_LOG_MEASUREMENTS | MEAS_FLAG_LR_VELO_EXPAND | MEAS_FLAG_SR_VELO_EXPAND
								| MEAS_FLAG_AOA_DEBUG | MEAS_FLAG_FFT3D_DEBUG;

			if(!strcmp(args[1],"ffts")) {
				if(MEAS_FLAGS_WR & MEAS_FLAG_FFT3D_DEBUG){
					if(count > 4)
						SPT.WR_R9_RE.R = strtoul(args[4],NULL,16); // sections number for fft16 data source to put FFT16_DOPPLER_DATA
					else
						SPT.WR_R9_RE.R = 0; // sections number for fft16 data source to put FFT16_DOPPLER_DATA

					cb = (event_proc_p)na_hist_start;
					mod = MEAS_MOD_HIST;
				}
				else {
					mod = MEAS_MOD_FFT;
					cb = (event_proc_p)na_fft_start;
				}
			}

			else if(!strcmp(args[1],"meas")){
				mod = MEAS_MOD_MEASUREMENTS;
				cb = (event_proc_p)na_measurements_start;
			}

			//enet_packet_info(1);
			if(MEAS_FLAGS_WR & MEAS_FLAG_FFT3D_DEBUG)
				fft3d = (event_proc_p)na_fft3d_start;

			if(MEAS_FLAGS_WR & MEAS_FLAG_AOA_DEBUG)
				aoa = (event_proc_p)na_aoa_handler;

			spt_debug_reg(fft3d, aoa);

			MEAS_MOD_WR = mod;
			frame_play(nm, lm, FRAME_RATE_ONCE, cb, NULL);
		}
	}
	else if(count == 2){
		if(!strcmp(args[1], "pkts")){
			enet_packet_info(0);
		}
	}
	else {
		PRINTF("na raws long/near 0~33(frames_sec) : log long/near raw data with frame rate frames_sec, 0 means one frame only\n");
		PRINTF("na ffts idx 0(rf)/1(sps) : get fft(range/doppler) data from rf or samples\n");
		PRINTF("na meas long/near 1(rf)/0(sps) : get long/near measurements data from rf or samples\n");
		PRINTF("na bfms 0(long ragge)/40000(short range) : get current beamforming data\n");
		PRINTF("na dops idx : get current dopplers data\n");
		PRINTF("na pars id : get parameters with id in json string\n");
	}
}
