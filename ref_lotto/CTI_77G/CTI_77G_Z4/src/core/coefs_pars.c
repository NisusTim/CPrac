/*
 * coefs_pars.c
 *
 *  Created on: Feb 16, 2019
 *      Author: erichu
 */

#include "sys_shared.h"
#include "windows.h"
#include "coefs.h"

#define COEFS_PARS_VERSION_MAJOR		0x01
#define COEFS_PARS_VERSION_MINOR		0x01
#define VERSION_OF_COEFS_PARS    		(((uint16_t)COEFS_PARS_VERSION_MAJOR<<8) | COEFS_PARS_VERSION_MINOR)

#define DEFAULT_FCW_AOPTS				0x00F770F7
#define DEFAULT_WIN_TYPE				WIN_TYPE_BLACKMAN
#define DEFAULT_WIN_FACTOR				DEFAULT_BLACKMAN_FACTOR


//extern rv_cmps_data_t rv_cmps_data;
static calib_iron_info_t calib_iron_info = {0};

typedef struct {
	pars_header_t	hdr;
	coefs_data_t	pars;
}coefs_pars_t, *coefs_pars_p;

coefs_pars_t __attribute__((section(".clbrpars"))) coefs_parameters;
const coefs_pars_t default_coefs = {
		.hdr = {
			.base=(uint32_t)&coefs_parameters,
			.version=VERSION_OF_COEFS_PARS,
			.size = sizeof(coefs_pars_t),
			.id=COEFS_PARS_ID,
			.chksum = 0,
			.mask=0,
		},
		.pars={ // FCW V4 Antenna
			.coefs={{1.00000,0.00000},{0.64249,0.76630},{-0.49026,-0.87158},{0.79348,-0.60859},
					{0.83014,-0.55755},{0.96703,0.25467},{-0.90347,-0.42865},{0.28121,-0.95965}},

			.opts_aoa = 0x00F770F7,		// R0123XXXX01234567
			.opts_fft3d = 0x0000F077,
			.win_types = {DEFAULT_WIN_TYPE, DEFAULT_WIN_TYPE},
			.win_factors = {DEFAULT_WIN_FACTOR, DEFAULT_WIN_FACTOR},
			.maps_ant = {0,3,5,8,8,11,13,16,-1,-1,-1,-1}
		}
};

const coefs_data_t fcw_dual_calib_data = {
		.coefs={{1.00000,0.00000},{0.37623,-0.92652},{-0.96087,0.27699},{-0.67572,0.73715},
				{0.03664,0.99933},{0.94019,0.34064},{-0.30755,-0.95153},{-0.76483,-0.64423}},

		.opts_aoa = DEFAULT_FCW_AOPTS,		// R0123XXXX01234567
		.opts_fft3d = 0x0000F0EE,
		.win_types = {DEFAULT_WIN_TYPE,DEFAULT_WIN_TYPE},
		.win_factors = {DEFAULT_WIN_FACTOR,DEFAULT_WIN_FACTOR},
		.maps_ant = {0,3,5,8,8,11,13,16,-1,-1,-1,-1}
};

calib_iron_pars_t calib_iron_parameters = {
		.hdr = {
			.base=(uint32_t)&calib_iron_parameters,
			.version=VERSION_OF_CALIB_IRON_PARS,
			.size = sizeof(calib_iron_pars_t),
			.id=CALIB_IRON_PARS_ID,
			.chksum = 0,
			.mask=0,
		},
		.pars={
			.equipment_magdB_threshold = 60,
			.equipment_angle_tolerance = 3,
			.equipment_vangle_tolerance = 30,
			.equipment_magdB_dif_tolerance = 10,
			.number_of_inspections = 5,
			.correct_cnt_threshold = 3,
			.not_found_cnt_threshold = 3,
			.range_err_cnt_threshold = 3,
			.aoa_err_cnt_threshold =3,
			.vaoa_err_cnt_threshold =3,
			.number_of_measurement=20,
			.calib_iron_bandwidth=1000,             //bandwith=1000Mhz
			.vangle_compensation_table={69.5, 59.5, 48, 40.75, 37, 36, 31.5, 30, 20, 10, 0},
			
			.target_offset_angle=0,
			.target_distance=1.2,
			.alignment_completion_flag=CALIB_IRON_NOT_COMPLETED,
			.radar_alignment_result=CALIB_EQUIPMENT_PROCESSING,
			.h_alignment_angle=0,
	        .v_alignment_angle=0,
	        .alignment_received_power=0
		}
};
static void coefs_iron_tester(char** args, int count);
coefs_data_p coefs=&coefs_parameters.pars;
calib_iron_data_p calib_iron_p=&calib_iron_parameters.pars;

#define JSON_CLBR_INFO_COEFS 		"\t\t\"coefs\":{\"t\":\"f64\",\"o\":%d,\"v\":[%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f]},\n"
#define JSON_CLBR_INFO_OPTS_AOA 	"\t\t\"opts_aoa\":{\"t\":\"u32\",\"o\":%d,\"v\":%lu},\n"
#define JSON_CLBR_INFO_OPTS_FFT3D 	"\t\t\"opts_fft3d\":{\"t\":\"u32\",\"o\":%d,\"v\":%lu},\n"
#define JSON_CLBR_INFO_WIN_FACTORS 	"\t\t\"win_factors\":{\"t\":\"i8\",\"o\":%d,\"v\":[%d,%d]},\n"
#define JSON_CLBR_INFO_WIN_TYPES 	"\t\t\"win_types\":{\"t\":\"i8\",\"o\":%d,\"v\":[%d,%d]},\n"
#define JSON_CLBR_INFO_MAPS_ANT		"\t\t\"maps_ant\":{\"t\":\"i8\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]}\n"

#define JSON_CLBI_INFO_MAG_DB                   "\t\t\"equipment_magdB_threshold\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_CLBI_INFO_ANGLE                    "\t\t\"equipment_angle_tolerance\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_CLBI_INFO_VANGLE                    "\t\t\"equipment_vangle_tolerance\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_CLBI_INFO_MAG_DIF                  "\t\t\"equipment_magdB_dif_tolerance\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_CLBI_INFO_NUMBER                   "\t\t\"number_of_inspections\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_CLBI_INFO_CORRECT                  "\t\t\"correct_cnt_threshold\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_CLBI_INFO_NO_FOUND                 "\t\t\"not_found_cnt_threshold\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_CLBI_INFO_RANGE_ERR                "\t\t\"range_err_cnt_threshold\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_CLBI_INFO_AOA_ERR                  "\t\t\"aoa_err_cnt_threshold\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_CLBI_INFO_VAOA_ERR                 "\t\t\"vaoa_err_cnt_threshold\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_CLBI_INFO_NUMBER_OF_MEAS           "\t\t\"number_of_measurement\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_CLBI_INFO_BANDWIDTH                "\t\t\"calib_iron_bandwidth\":{\"t\":\"u16\",\"o\":%d,\"v\":%d},\n"
#define JSON_CLBI_INFO_VANGLE_COMPENSATION      "\t\t\"vangle_compensation_table\":{\"t\":\"f32\",\"o\":%d,\"v\":[%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f]},\n"
#define JSON_CLBI_INFO_TAR_OFFSET_ANGLE         "\t\t\"target_offset_angle\":{\"t\":\"f32\",\"o\":%d,\"v\":%f},\n"
#define JSON_CLBI_INFO_TAR_DISTANCE             "\t\t\"target_distance\":{\"t\":\"f32\",\"o\":%d,\"v\":%f},\n"
#define JSON_CLBI_INFO_COMPLETION_FLAG          "\t\t\"alignment_completion_flag\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_CLBI_INFO_ALIGNMENT_RESULT         "\t\t\"radar_alignment_result\":{\"t\":\"u32\",\"o\":%d,\"v\":%d},\n"
#define JSON_CLBI_INFO_H_ALIGNMENT_ANGLE        "\t\t\".h_alignment_angle\":{\"t\":\"f32\",\"o\":%d,\"v\":%f},\n"    
#define JSON_CLBI_INFO_V_ALIGNMENT_ANGLE        "\t\t\"v_alignment_angle\":{\"t\":\"f32\",\"o\":%d,\"v\":%f},\n"
#define JSON_CLBI_INFO_RECEIVED_POWER           "\t\t\"alignment_received_power\":{\"t\":\"f32\",\"o\":%d,\"v\":%f}\n"

static void coefs_pars_set(void)
{
	pars_set((pars_ctx_p)&coefs_parameters);
}

static int coefs_info_in_jsons(char* ws)
{
	int cnt = 0;
	if(ws){
		cnt = sprintf(ws,"{\n");
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_ID, (char)(COEFS_PARS_ID>>24),(char)(COEFS_PARS_ID>>16),(char)(COEFS_PARS_ID>>8),(char)(COEFS_PARS_ID));
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_VERSION, coefs_parameters.hdr.version);
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_SIZE, coefs_parameters.hdr.size  - sizeof(pars_header_t));

		cnt += sprintf(ws+cnt,"\t\"info\":{\n");
		cnt += sprintf(ws+cnt,JSON_CLBR_INFO_COEFS,offsetof(coefs_data_t, coefs),coefs_parameters.pars.coefs[0].re, coefs_parameters.pars.coefs[0].im,
				coefs_parameters.pars.coefs[1].re, coefs_parameters.pars.coefs[1].im,coefs_parameters.pars.coefs[2].re, coefs_parameters.pars.coefs[2].im, coefs_parameters.pars.coefs[3].re, coefs_parameters.pars.coefs[3].im,
				coefs_parameters.pars.coefs[4].re, coefs_parameters.pars.coefs[4].im,coefs_parameters.pars.coefs[5].re, coefs_parameters.pars.coefs[5].im, coefs_parameters.pars.coefs[6].re, coefs_parameters.pars.coefs[6].im,
				coefs_parameters.pars.coefs[7].re,coefs_parameters.pars.coefs[7].im);
		cnt += sprintf(ws+cnt, JSON_CLBR_INFO_OPTS_AOA,offsetof(coefs_data_t, opts_aoa), coefs_parameters.pars.opts_aoa);
		cnt += sprintf(ws+cnt, JSON_CLBR_INFO_OPTS_FFT3D,offsetof(coefs_data_t, opts_fft3d), coefs_parameters.pars.opts_fft3d);
		cnt += sprintf(ws+cnt, JSON_CLBR_INFO_WIN_TYPES,offsetof(coefs_data_t, win_types),coefs_parameters.pars.win_types[0],coefs_parameters.pars.win_types[1]);
		cnt += sprintf(ws+cnt, JSON_CLBR_INFO_WIN_FACTORS,offsetof(coefs_data_t, win_factors),coefs_parameters.pars.win_factors[0],coefs_parameters.pars.win_factors[1]);
		cnt += sprintf(ws+cnt, JSON_CLBR_INFO_MAPS_ANT,offsetof(coefs_data_t, maps_ant), coefs_parameters.pars.maps_ant[0],coefs_parameters.pars.maps_ant[1],
				coefs_parameters.pars.maps_ant[2],coefs_parameters.pars.maps_ant[3],coefs_parameters.pars.maps_ant[4],coefs_parameters.pars.maps_ant[5],coefs_parameters.pars.maps_ant[6],coefs_parameters.pars.maps_ant[7],
				coefs_parameters.pars.maps_ant[8],coefs_parameters.pars.maps_ant[9],coefs_parameters.pars.maps_ant[10],coefs_parameters.pars.maps_ant[11]);
		cnt += sprintf(ws+cnt, "\t}\n}\n");
	}
	return cnt;
}

static int clbi_info_in_jsons(char* ws)
{
	int cnt = 0;
	if(ws){
		cnt = sprintf(ws,"{\n");
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_ID, (char)(CALIB_IRON_PARS_ID>>24),(char)(CALIB_IRON_PARS_ID>>16),(char)(CALIB_IRON_PARS_ID>>8),(char)(CALIB_IRON_PARS_ID));
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_VERSION, calib_iron_parameters.hdr.version);
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_SIZE, calib_iron_parameters.hdr.size- sizeof(pars_header_t));

		cnt += sprintf(ws+cnt,"\t\"info\":{\n");

		cnt += sprintf(ws+cnt, JSON_CLBI_INFO_MAG_DB,offsetof(calib_iron_data_t, equipment_magdB_threshold), calib_iron_parameters.pars.equipment_magdB_threshold);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_ANGLE,offsetof(calib_iron_data_t, equipment_angle_tolerance), calib_iron_parameters.pars.equipment_angle_tolerance);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_VANGLE,offsetof(calib_iron_data_t, equipment_vangle_tolerance), calib_iron_parameters.pars.equipment_vangle_tolerance);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_MAG_DIF,offsetof(calib_iron_data_t, equipment_magdB_dif_tolerance), calib_iron_parameters.pars.equipment_magdB_dif_tolerance);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_NUMBER,offsetof(calib_iron_data_t, number_of_inspections), calib_iron_parameters.pars.number_of_inspections);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_CORRECT,offsetof(calib_iron_data_t, correct_cnt_threshold), calib_iron_parameters.pars.correct_cnt_threshold);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_NO_FOUND,offsetof(calib_iron_data_t, not_found_cnt_threshold), calib_iron_parameters.pars.not_found_cnt_threshold);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_RANGE_ERR,offsetof(calib_iron_data_t, range_err_cnt_threshold), calib_iron_parameters.pars.range_err_cnt_threshold);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_AOA_ERR,offsetof(calib_iron_data_t, aoa_err_cnt_threshold), calib_iron_parameters.pars.aoa_err_cnt_threshold);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_VAOA_ERR,offsetof(calib_iron_data_t, vaoa_err_cnt_threshold), calib_iron_parameters.pars.vaoa_err_cnt_threshold);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_NUMBER_OF_MEAS,offsetof(calib_iron_data_t, number_of_measurement), calib_iron_parameters.pars.number_of_measurement);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_BANDWIDTH,offsetof(calib_iron_data_t, calib_iron_bandwidth), calib_iron_parameters.pars.calib_iron_bandwidth);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_VANGLE_COMPENSATION,offsetof(calib_iron_data_t, vangle_compensation_table), calib_iron_parameters.pars.vangle_compensation_table[0],
            calib_iron_parameters.pars.vangle_compensation_table[1],calib_iron_parameters.pars.vangle_compensation_table[2],calib_iron_parameters.pars.vangle_compensation_table[3],
            calib_iron_parameters.pars.vangle_compensation_table[4],calib_iron_parameters.pars.vangle_compensation_table[5],calib_iron_parameters.pars.vangle_compensation_table[6],
            calib_iron_parameters.pars.vangle_compensation_table[7],calib_iron_parameters.pars.vangle_compensation_table[8],calib_iron_parameters.pars.vangle_compensation_table[9],calib_iron_parameters.pars.vangle_compensation_table[10]);
        
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_TAR_OFFSET_ANGLE,offsetof(calib_iron_data_t, target_offset_angle), calib_iron_parameters.pars.target_offset_angle);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_TAR_DISTANCE,offsetof(calib_iron_data_t, target_distance), calib_iron_parameters.pars.target_distance);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_COMPLETION_FLAG,offsetof(calib_iron_data_t, alignment_completion_flag), calib_iron_parameters.pars.alignment_completion_flag);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_ALIGNMENT_RESULT,offsetof(calib_iron_data_t, radar_alignment_result), calib_iron_parameters.pars.radar_alignment_result);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_H_ALIGNMENT_ANGLE,offsetof(calib_iron_data_t, h_alignment_angle), calib_iron_parameters.pars.h_alignment_angle);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_V_ALIGNMENT_ANGLE,offsetof(calib_iron_data_t, v_alignment_angle), calib_iron_parameters.pars.v_alignment_angle);
        cnt += sprintf(ws+cnt, JSON_CLBI_INFO_RECEIVED_POWER,offsetof(calib_iron_data_t, alignment_received_power), calib_iron_parameters.pars.alignment_received_power);
		cnt += sprintf(ws+cnt, "\t}\n}\n");
	}
	return cnt;
}

static void coefs_pars_dump(void)
{
	PRINTF("calib pars(%d):\n",sizeof(coefs_pars_t));
	PRINTF("calib coefs: (%.5f,%.5fj)(%.5f,%.5fj)(%.5f,%.5fj)(%.5f,%.5fj)",coefs_parameters.pars.coefs[0].re, coefs_parameters.pars.coefs[0].im,
			coefs_parameters.pars.coefs[1].re, coefs_parameters.pars.coefs[1].im,	coefs_parameters.pars.coefs[2].re, coefs_parameters.pars.coefs[2].im, coefs_parameters.pars.coefs[3].re, coefs_parameters.pars.coefs[3].im);

	PRINTF("(%.5f,%.5fj)(%.5f,%.5fj)(%.5f,%.5fj)(%.5f,%.5fj)\n",coefs_parameters.pars.coefs[4].re, coefs_parameters.pars.coefs[4].im,
			coefs_parameters.pars.coefs[5].re, coefs_parameters.pars.coefs[5].im,coefs_parameters.pars.coefs[6].re, coefs_parameters.pars.coefs[6].im, coefs_parameters.pars.coefs[7].re, coefs_parameters.pars.coefs[7].im);

	PRINTF("calib aopts: %04lXh\n", coefs_parameters.pars.opts_aoa);
	PRINTF("calib fopts: %04lXh\n", coefs_parameters.pars.opts_fft3d);

	PRINTF("calib wins: [(%d,%d), (%d,%d)], 0:(none,na),1:(hamming,alpha*100),2:(cheby,db value),3:(blackman,alpha*100)\n",
			coefs_parameters.pars.win_types[WIN_IDX_RANGE], coefs_parameters.pars.win_factors[WIN_IDX_RANGE],coefs_parameters.pars.win_types[WIN_IDX_DOPPLER], coefs_parameters.pars.win_factors[WIN_IDX_DOPPLER]);

	PRINTF("calib amap: [%d, %d, %d, %d, %d, %d, %d, %d]\n",coefs_parameters.pars.maps_ant[0],coefs_parameters.pars.maps_ant[1],coefs_parameters.pars.maps_ant[2],coefs_parameters.pars.maps_ant[3],
				coefs_parameters.pars.maps_ant[4],coefs_parameters.pars.maps_ant[5],coefs_parameters.pars.maps_ant[6],coefs_parameters.pars.maps_ant[7]);

}

static void coefs_iron_pars_dump(void)
{
    PRINTF("calib-iron pars(%d):\n",sizeof(calib_iron_data_t)+SIZE_OF_PARS_CTX_HEADER);
    PRINTF("calib-iron mag %3d              //equipment_magdB_threshold (dB)\n", calib_iron_parameters.pars.equipment_magdB_threshold);
    PRINTF("calib-iron angle %3d            //equipment_angle_tolerance\n", calib_iron_parameters.pars.equipment_angle_tolerance);
    PRINTF("calib-iron vangle %3d           //equipment_vangle_tolerance\n", calib_iron_parameters.pars.equipment_vangle_tolerance);
    PRINTF("calib-iron magdiff %3d          //equipment_magdB_dif_tolerance\n", calib_iron_parameters.pars.equipment_magdB_dif_tolerance);
	PRINTF("calib-iron num %3d              //number_of_inspections\n", calib_iron_parameters.pars.number_of_inspections);
	PRINTF("calib-iron correct %3d          //correct_cnt_threshold\n", calib_iron_parameters.pars.correct_cnt_threshold);
	PRINTF("calib-iron notfound %3d         //not_found_cnt_threshold\n", calib_iron_parameters.pars.not_found_cnt_threshold);
	PRINTF("calib-iron range %3d            //range_err_cnt_threshold\n", calib_iron_parameters.pars.range_err_cnt_threshold);
	PRINTF("calib-iron aoa %3d              //aoa_err_cnt_threshold\n", calib_iron_parameters.pars.aoa_err_cnt_threshold);
	PRINTF("calib-iron vaoa %3d             //vaoa_err_cnt_threshold\n", calib_iron_parameters.pars.vaoa_err_cnt_threshold);
	PRINTF("calib-iron measu_num %3d        //number_of_measurement\n", calib_iron_parameters.pars.number_of_measurement);
	PRINTF("calib-iron bw %4d              //calib_iron_bandwidth [150,300,450,600,1000Mzh]\n", calib_iron_parameters.pars.calib_iron_bandwidth);
	PRINTF("calib-iron tar_angle %.2f       //target_offset_angle\n", calib_iron_parameters.pars.target_offset_angle);
	PRINTF("calib-iron tar_distance %.2f    //target_distance\n", calib_iron_parameters.pars.target_distance);
	
	PRINTF("calib-iron va_comp %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f \n//vangle_compensation_value_table 0.9m, 1.05m, 1.2m ...2.4m\n", 
	    calib_iron_parameters.pars.vangle_compensation_table[0],calib_iron_parameters.pars.vangle_compensation_table[1],
	    calib_iron_parameters.pars.vangle_compensation_table[2],calib_iron_parameters.pars.vangle_compensation_table[3],
	    calib_iron_parameters.pars.vangle_compensation_table[4],calib_iron_parameters.pars.vangle_compensation_table[5],
	    calib_iron_parameters.pars.vangle_compensation_table[6],calib_iron_parameters.pars.vangle_compensation_table[7],
	    calib_iron_parameters.pars.vangle_compensation_table[8],calib_iron_parameters.pars.vangle_compensation_table[9],
	    calib_iron_parameters.pars.vangle_compensation_table[10]);
	
	
	PRINTF("\n \nalignment_completion_flag= %x  \n", calib_iron_parameters.pars.alignment_completion_flag);
	PRINTF("radar_alignment_result= %d  \n", calib_iron_parameters.pars.radar_alignment_result);
	PRINTF("h_alignment_angle= %.2f  \n", calib_iron_parameters.pars.h_alignment_angle);
	PRINTF("v_alignment_angle= %.2f  \n", calib_iron_parameters.pars.v_alignment_angle);
	PRINTF("alignment_received_power= %.2f  \n", calib_iron_parameters.pars.alignment_received_power);
}

static void coefs_pars_tester(char** args, int count)
{
	if(count > 2) {
		if(!strcmp("get", args[1])){
			float clb = strtof(args[2], NULL);
			float clb_angle = 0;
            float temp;

            if(count > 4){
            	uint16_t calib_bw = (uint16_t)atoi(args[4]);
            	if(set_calibration_bandwidth(calib_bw) != 0){
            		PRINTF("set bandwidth failed!\n");
            	}
            }

            temp=frame_get_rngs_long_start();
            if(clb<=temp){
                if((clb-0.5)>=1){
                    frame_set_rngs_long_start(clb-0.5,0);
                }else{
                    frame_set_rngs_long_start(1,0);
                }
            }

			if(count > 3)
				clb_angle = strtof(args[3], NULL);

			if(clb > 0)
				coefs_calib_start(clb, clb_angle,CAL_OPT_CIRCUIT,NULL);

			return;
		}

		else if(!strcmp("amap", args[1]) && count >= 10) {
			coefs_parameters.pars.maps_ant[0] = strtoul(args[2], NULL, 10);
			coefs_parameters.pars.maps_ant[1] = strtoul(args[3], NULL, 10);
			coefs_parameters.pars.maps_ant[2] = strtoul(args[4], NULL, 10);
			coefs_parameters.pars.maps_ant[3] = strtoul(args[5], NULL, 10);
			coefs_parameters.pars.maps_ant[4] = strtoul(args[6], NULL, 10);
			coefs_parameters.pars.maps_ant[5] = strtoul(args[7], NULL, 10);
			coefs_parameters.pars.maps_ant[6] = strtoul(args[8], NULL, 10);
			coefs_parameters.pars.maps_ant[7] = strtoul(args[9], NULL, 10);
			pars_set((pars_ctx_p)&coefs_parameters);
			coefs_cmps_set(COEFS_CMPS_ALL);
		}
		else if(!strcmp("coefs", args[1]) && count >= 18) {
			coefs_parameters.pars.coefs[0].re = strtof(args[2], NULL);
			coefs_parameters.pars.coefs[0].im = strtof(args[3], NULL);
			coefs_parameters.pars.coefs[1].re = strtof(args[4], NULL);
			coefs_parameters.pars.coefs[1].im = strtof(args[5], NULL);
			coefs_parameters.pars.coefs[2].re = strtof(args[6], NULL);
			coefs_parameters.pars.coefs[2].im = strtof(args[7], NULL);
			coefs_parameters.pars.coefs[3].re = strtof(args[8], NULL);
			coefs_parameters.pars.coefs[3].im = strtof(args[9], NULL);
			coefs_parameters.pars.coefs[4].re = strtof(args[10], NULL);
			coefs_parameters.pars.coefs[4].im = strtof(args[11], NULL);
			coefs_parameters.pars.coefs[5].re = strtof(args[12], NULL);
			coefs_parameters.pars.coefs[5].im = strtof(args[13], NULL);
			coefs_parameters.pars.coefs[6].re = strtof(args[14], NULL);
			coefs_parameters.pars.coefs[6].im = strtof(args[15], NULL);
			coefs_parameters.pars.coefs[7].re = strtof(args[16], NULL);
			coefs_parameters.pars.coefs[7].im = strtof(args[17], NULL);
			pars_set((pars_ctx_p)&coefs_parameters);
			coefs_cmps_set(COEFS_CMPS_ALL);
		}
		else if(!strcmp("aopts", args[1])) {
			coefs_parameters.pars.opts_aoa = strtoul(args[2], NULL, 16);
			pars_set((pars_ctx_p)&coefs_parameters);
			coefs_cmps_set(COEFS_CMPS_ALL);
		}
		else if(!strcmp("fopts", args[1])) {
			coefs_parameters.pars.opts_fft3d = strtoul(args[2], NULL, 16);
			pars_set((pars_ctx_p)&coefs_parameters);
			coefs_cmps_set(COEFS_CMPS_ALL);
		}
		else if(!strcmp("wins", args[1])) {
			if(count > 3) {
				coefs_parameters.pars.win_types[WIN_IDX_RANGE] = strtoul(args[2], NULL, 10);
				coefs_parameters.pars.win_factors[WIN_IDX_RANGE] = strtoul(args[3], NULL, 10);
				if(count > 5) {
					coefs_parameters.pars.win_types[WIN_IDX_DOPPLER] = strtoul(args[4], NULL, 10);
					coefs_parameters.pars.win_factors[WIN_IDX_DOPPLER] = strtoul(args[5], NULL, 10);
				}
				//if(windows_set(coefs_parameters.pars.win_types, coefs_parameters.pars.win_factors) == TRUE)
				pars_set((pars_ctx_p)&coefs_parameters);
				coefs_cmps_set(COEFS_CMPS_WIN_ONLY);
			}
		}
	}
	coefs_pars_dump();
}



void coefs_pars_init(void)
{
	uint16_t prod = product_info_get()->product;

	memcpy((void*)&coefs_parameters, (void*)&default_coefs, sizeof(coefs_pars_t));

	switch(prod)
	{
		case PROD_ID_FCW_DUAL:
			memcpy((void*)&coefs_parameters.pars, (void*)&fcw_dual_calib_data, sizeof(fcw_dual_calib_data));
			break;
		default:
			break;
	}

	pars_get((pars_ctx_p)&coefs_parameters, coefs_pars_dump, coefs_info_in_jsons);
	console_command_reg("calib", coefs_pars_tester);
	pars_get((pars_ctx_p)&calib_iron_parameters, coefs_iron_pars_dump, clbi_info_in_jsons);
	console_command_reg("calib-iron", coefs_iron_tester);
	coefs_init(coefs, coefs_pars_set);
	calib_iron_init(calib_iron_p);
	//PRINTF("clb: %08lX:%08lX init done\n", COEFS_PARS_ID, coefs_parameters.hdr.id);
}

//------equipment detection for calib-iron----------------------------------------------------------------
typedef struct{
    float clb_range;
    float clb_angle;
    float runit;
    double minus_target_mag;
    double target_mag;
    double plus_target_mag;
    float target_angle;
    float target_vangle;
    float spt_long_start_temp;
    float spt_angle_temp;
    float spt_vangle_temp;
    uint32_t calib_iron_elapsed_time;
    float vangle_compensation_value;
}detect_equipment_para_t, *detect_equipment_para_p;

static void calib_iron_get(detect_equipment_para_p para_p);
static void detect_equipment_start(void);
static void detect_equipment_proc(void);

static detect_equipment_para_t para;
static uint8_t detect_equipment_counter;
static double tg_mag;
static uint8_t check_equipment_step=0;

iron_calib_done_p   iron_calib_done=NULL;
iron_calib_result_t iron_calib_result={0,0,0};

static void reset_asft_hsft(void)
{
    para.spt_angle_temp=frame_get_aoa_shift(0);
    para.spt_vangle_temp=frame_get_hsft();
    frame_rng_aoa_set(0,0,0,0,0);
    frame_set_hsft(0,0);
}

static void restore_asft_hsft(void)
{
    frame_rng_aoa_set(para.spt_angle_temp,0,0,0,0);
    frame_set_hsft(para.spt_vangle_temp,0);
}

static void set_aoa_sft(float angle, float vangle )
{
    frame_set_rngs_long_start(para.spt_long_start_temp,0);      //restored spt rngs long start
    
    if(DELTA(angle,0)>calib_iron_parameters.pars.equipment_angle_tolerance){
        calib_iron_info.calibration_result=CALIB_EQUIPMENT_AOA_ERR;
        restore_asft_hsft();
    }else 
    if(DELTA(vangle,para.vangle_compensation_value)>calib_iron_parameters.pars.equipment_vangle_tolerance){
        calib_iron_info.calibration_result=CALIB_EQUIPMENT_VAOA_ERR;
        restore_asft_hsft();
    }else{
        frame_set_aoa_shift(0,angle+frame_get_aoa_shift(0));
        frame_set_aoa_shift(1,angle+frame_get_aoa_shift(1));
        vangle-=para.vangle_compensation_value;
        frame_set_hsft(frame_get_hsft()-vangle,1);
        PRINTF(" set aoa_sft0 =%.4f, aoa_sft1 =%.4f, hsft=%.4f \n", frame_get_aoa_shift(0),frame_get_aoa_shift(1),frame_get_hsft());
    }
    iron_calib_result.iron_angle=0-angle;
    iron_calib_result.iron_vangle=0-((180*asin(vangle/716.04))/PI);
    save_calib_iron_result_to_EE(calib_iron_info.calibration_result,&iron_calib_result);
    calib_iron_info.calibration_sta = CALIB_STATUS_DONE;
    if(iron_calib_done!=NULL){
        iron_calib_done(calib_iron_info.calibration_result,&iron_calib_result);
        iron_calib_done=NULL;
    }
    iron_calib_result.iron_angle=0;
    iron_calib_result.iron_vangle=0;
    iron_calib_result.iron_mag=0;
    
    set_tef810x_production_mode(kNORMAL_MODE);
    PRINTF("total time= %.1fms\n", (STM_0.CNT.R-para.calib_iron_elapsed_time)*0.0000167f);
}

static double _complex_mag_get(int32_t imag, int32_t real)
{
	double res = pow((double)real,2) + pow((double)imag,2);
	return sqrt(res);
}

static void meas_equipment_done(void* d)
{
	uint8_t i,j;
    target_group_p tgg=(target_group_p)d;
	target_p tg = tgg->targets;
	para.runit=tgg->runit;
    tg_mag=0;

	if(tg){
		if(tgg->idx == FRAME_CTX_IDX_LONG)
		    j=8;
		else
		    j=4;

		tg_mag=0;
		for(i=0;i<j;i++)
		{
		   tg_mag+= _complex_mag_get((float)tg->cmplx[i].im, (float)tg->cmplx[i].re);

		}
		tg_mag=tg_mag/j;

		if(check_equipment_step==0)
		{
		    para.target_angle=DEGREE_OF_RADIAN(aoaidx_asin(tg->aoaidx));
		    para.target_vangle=tg->vangle-para.vangle_compensation_value;
		}

		check_equipment_step++;
	    put_event("clbi", (event_proc_p)detect_equipment_proc, NULL);
	}
}

static void detect_equipment_proc(void)
{
    float meas_range;
    
    if(check_equipment_step==0)
    {
        spt_doppler_get(FRAME_CTX_IDX_LONG, para.clb_range, meas_equipment_done);
    }
    else
    if(check_equipment_step==1)
    {
        para.target_mag=tg_mag;
        meas_range=para.clb_range-(para.runit*2);
        if(meas_range<=0)
        {
            meas_range=para.runit;
        }
        spt_doppler_get(FRAME_CTX_IDX_LONG, meas_range, meas_equipment_done);
    }
    else
    if(check_equipment_step==2)
    {
        para.minus_target_mag=tg_mag;
        meas_range=para.clb_range+(para.runit*2);
        spt_doppler_get(FRAME_CTX_IDX_LONG, meas_range, meas_equipment_done);
    }
    else
    if(check_equipment_step==3)
    {
        para.plus_target_mag=tg_mag;
        //PRINTF("mag_0=%.1f, mag_1=%.1f,mag_2=%.1f\n",para.minus_target_mag,para.target_mag,para.plus_target_mag);
        calib_iron_get(&para);
    }
}

static void detect_equipment_start(void)
{
    check_equipment_step=0;
    detect_equipment_proc();
}

static void calib_iron_get(detect_equipment_para_p para_p)
{
    static float calib_iron_get_mag_max=0;
    static float calib_iron_get_mag_min=1000;
    static uint8_t equipment_not_found_cnt=0;
    static uint8_t equipment_range_err_cnt=0;
    static uint8_t equipment_aoa_err_cnt=0;
    static uint8_t equipment_vaoa_err_cnt=0;
    static uint8_t equipment_correct_cnt=0;
    float target_mag_db;

    //PRINTF("calib_iron_get [%.1f,%lf,%lf,%lf,%.1f,%.1f] \n",para_p->clb_range,para_p->minus_target_mag,para_p->target_mag,para_p->plus_target_mag,para_p->target_angle,para_p->target_vangle);

    detect_equipment_counter++;

    target_mag_db=20*log10(para_p->target_mag);

    PRINTF("magdB=%.1fdB, angle=%.1f, vangle=%.1f\n",target_mag_db,para_p->target_angle,para_p->target_vangle);
    iron_calib_result.iron_mag+=target_mag_db;
    iron_calib_result.iron_angle+=para_p->target_angle;
    iron_calib_result.iron_vangle+=para_p->target_vangle;
    
    if(calib_iron_get_mag_max<target_mag_db)
    {
        calib_iron_get_mag_max= target_mag_db;
    }
    if(calib_iron_get_mag_min>target_mag_db)
    {
        calib_iron_get_mag_min= target_mag_db;
    }

    if(target_mag_db<calib_iron_parameters.pars.equipment_magdB_threshold)
    {
        equipment_not_found_cnt++;
        PRINTF("CALIB_EQUIPMENT_NOT_FOUND %d\n",equipment_not_found_cnt);
    }
    else
    if((para_p->target_mag<=para_p->minus_target_mag)||(para_p->target_mag<=para_p->plus_target_mag))
    {
        equipment_range_err_cnt++;
        PRINTF("CALIB_EQUIPMENT_RANGE_ERR %d\n",equipment_range_err_cnt);
    }
    else
    if(DELTA(para_p->target_angle,0)>calib_iron_parameters.pars.equipment_angle_tolerance)
    {
        equipment_aoa_err_cnt++;
        PRINTF("CALIB_EQUIPMENT_AOA_ERR %d\n",equipment_aoa_err_cnt);
    }
    else
    if(DELTA(para_p->target_vangle,0)>calib_iron_parameters.pars.equipment_vangle_tolerance)
    {
        equipment_vaoa_err_cnt++;
        PRINTF("CALIB_EQUIPMENT_VAOA_ERR %d\n",equipment_vaoa_err_cnt);
    }
    else
    {
        equipment_correct_cnt++;
        PRINTF("CALIB_EQUIPMENT_CORRECT %d\n",equipment_correct_cnt);
    }

    if(detect_equipment_counter>=calib_iron_parameters.pars.number_of_inspections)
    {
        float temp;
        iron_calib_result.iron_mag=iron_calib_result.iron_mag/detect_equipment_counter;
        iron_calib_result.iron_angle=0-(iron_calib_result.iron_angle/detect_equipment_counter);
        temp=iron_calib_result.iron_vangle/detect_equipment_counter;
        iron_calib_result.iron_vangle=0-((180*asin(temp/716.04))/PI);
        
        detect_equipment_counter=0;

        if((calib_iron_get_mag_max-calib_iron_get_mag_min)>calib_iron_parameters.pars.equipment_magdB_dif_tolerance)
        {
        	calib_iron_info.calibration_result = CALIB_EQUIPMENT_SIGNAL_MAG_ERR;
        	PRINTF("CALIB_EQUIPMENT_SIGNAL_MAG_ERR--done\n");
        }
        else
        if(equipment_correct_cnt>=calib_iron_parameters.pars.correct_cnt_threshold)
        {
        	calib_iron_info.calibration_result = CALIB_EQUIPMENT_CORRECT;
            PRINTF("CALIB_EQUIPMENT_CORRECT--done\n");
            coefs_calib_start(para.clb_range, para.clb_angle,CAL_OPT_BUMPER, set_aoa_sft);

        }
        else
        if(equipment_not_found_cnt>=calib_iron_parameters.pars.not_found_cnt_threshold)
        {
            calib_iron_info.calibration_result=CALIB_EQUIPMENT_NOT_FOUND;
            PRINTF("CALIB_EQUIPMENT_NOT_FOUND--done\n");
        }
        else
        if(equipment_range_err_cnt>=calib_iron_parameters.pars.range_err_cnt_threshold)
        {
            calib_iron_info.calibration_result=CALIB_EQUIPMENT_RANGE_ERR;
            PRINTF("CALIB_EQUIPMENT_RANGE_ERR--done\n");
        }
        else
        if(equipment_aoa_err_cnt>=calib_iron_parameters.pars.aoa_err_cnt_threshold)
        {
            calib_iron_info.calibration_result=CALIB_EQUIPMENT_AOA_ERR;
            PRINTF("CALIB_EQUIPMENT_AOA_ERR--done\n");
        }
        else
        if(equipment_vaoa_err_cnt>=calib_iron_parameters.pars.vaoa_err_cnt_threshold)
        {
            calib_iron_info.calibration_result=CALIB_EQUIPMENT_VAOA_ERR;
            PRINTF("CALIB_EQUIPMENT_VAOA_ERR--done\n");
        }
        else
        {
            calib_iron_info.calibration_result=CALIB_EQUIPMENT_RADAR_HW_ERR;
            PRINTF("CALIB_EQUIPMENT_RADAR_HW_ERR--done\n");
        }

        calib_iron_get_mag_max=0;
        calib_iron_get_mag_min=1000;
        equipment_not_found_cnt=0;
        equipment_range_err_cnt=0;
        equipment_aoa_err_cnt=0;
        equipment_correct_cnt=0;
        
        if(calib_iron_info.calibration_result!=CALIB_EQUIPMENT_CORRECT){
            save_calib_iron_result_to_EE(calib_iron_info.calibration_result,&iron_calib_result);
            calib_iron_info.calibration_sta = CALIB_STATUS_DONE;
            if(iron_calib_done!=NULL){
                iron_calib_done(calib_iron_info.calibration_result,&iron_calib_result);
                iron_calib_done=NULL;
            }
            frame_set_rngs_long_start(para.spt_long_start_temp,0);      //restored spt rngs long start
            restore_asft_hsft();
            iron_calib_result.iron_angle=0;
            iron_calib_result.iron_vangle=0;
            iron_calib_result.iron_mag=0;
            PRINTF("total time= %.1fms\n", (STM_0.CNT.R-para.calib_iron_elapsed_time)*0.0000167f);
        }
    }
    else
    {
        para_p->minus_target_mag=0;
        para_p->target_mag=0;
        para_p->plus_target_mag=0;
        detect_equipment_start();
    }
}

#if 0
static void iron_test(calib_equipment_e result,iron_calib_result_p result_value)
{
    PRINTF("result=%d a=%.2f va=%.2f m=%.2f \n",result,result_value->iron_angle,result_value->iron_vangle, result_value->iron_mag);
}
#endif

static float get_vangle_compensation_value(uint8_t index)
{
//index = 6 ==> 0.9m
//index = 7 ==> 1.05m
//....
//index  16 ==> 2.4m
   
    if(index<6){
        index=6;
    }else if(index>16){
        index=16;
    }
    return calib_iron_parameters.pars.vangle_compensation_table[index-6];
}

void get_tgg_real_range_done(void* d)
{
	target_group_p tgg = (target_group_p)d;
	target_p tg = tgg->targets;
	target_t temp;
	temp.range=0;
    temp.mag_log2=0;
    
    if (!d){
		PRINTF("clbi: get tgg falied!\n");
		return;
	}else{
		int idx=0;
		while(tg < (tgg->targets+tgg->tcnt)){
			if((DEGREE_OF_RADIAN(aoaidx_asin(tg->aoaidx)) != 180.0)&&(tg->velocity==0)){
				PRINTF("e%d,a=%.3f,v=%f,r=%.2f,h:%d, m:%.2f \n",idx++,DEGREE_OF_RADIAN(aoaidx_asin(tg->aoaidx)),(float)tg->velocity*tgg->vunit,(float)tg->range*tgg->runit,tg->vangle,spt_log2db(tg->mag_log2));
				if(tg->mag_log2>temp.mag_log2){
				    temp.mag_log2=tg->mag_log2;
				    temp.aoaidx=tg->aoaidx;
				    temp.vangle=tg->vangle;
				    temp.range=tg->range;
				}
			}
			if(((float)tg->range*tgg->runit)>(para.clb_range+0.5f)){    
			    break;
			}
			tg++;
		}
	}
	para.clb_range=(float)temp.range*tgg->runit;
	PRINTF("target range=%.2f,mag=%.2f\n", para.clb_range,spt_log2db(temp.mag_log2));
	if(temp.mag_log2==0){
	    PRINTF("CALIB_EQUIPMENT_NOT_FOUND--done\n");
	    if(calib_iron_info.calibration_sta==CALIB_STATUS_START){
	        calib_iron_info.calibration_result=CALIB_EQUIPMENT_NOT_FOUND;
	        iron_calib_result.iron_angle=0;
            iron_calib_result.iron_vangle=0;
            iron_calib_result.iron_mag=0;
            
	        save_calib_iron_result_to_EE(calib_iron_info.calibration_result,&iron_calib_result);
            calib_iron_info.calibration_sta = CALIB_STATUS_DONE;
            if(iron_calib_done!=NULL){
                iron_calib_done(calib_iron_info.calibration_result,&iron_calib_result);
                iron_calib_done=NULL;
            }
            frame_set_rngs_long_start(para.spt_long_start_temp,0);      //restored spt rngs long start
            restore_asft_hsft();
            PRINTF("total time= %.1fms\n", (STM_0.CNT.R-para.calib_iron_elapsed_time)*0.0000167f);
        }
       
    }else{
        para.vangle_compensation_value=get_vangle_compensation_value(temp.range);
        PRINTF("vangle_compensation_value=%f\n",para.vangle_compensation_value);
        if(calib_iron_info.calibration_sta==CALIB_STATUS_START){
            calib_iron_info.calibration_sta = CALIB_STATUS_BUSY;
        }
        put_event("clbi", (event_proc_p)detect_equipment_start, NULL);
    }
}

static void check_clbi_para_bandwith(void)
{
    if( (calib_iron_parameters.pars.calib_iron_bandwidth != 1000)||
        (calib_iron_parameters.pars.calib_iron_bandwidth != 600)||
        (calib_iron_parameters.pars.calib_iron_bandwidth != 450)||
        (calib_iron_parameters.pars.calib_iron_bandwidth != 300)||
        (calib_iron_parameters.pars.calib_iron_bandwidth != 150))
    {
        calib_iron_parameters.pars.calib_iron_bandwidth=1000;
    }
}

static void set_tef_in_clbi_mode(void)
{
    check_clbi_para_bandwith();
    
    chg_TEF810x_banwith_cb(0,calib_iron_parameters.pars.calib_iron_bandwidth);     //Profile-0,bandwith=1000Mhz
    chg_TEF810x_banwith_cb(1,calib_iron_parameters.pars.calib_iron_bandwidth);     //Profile-1,bandwith=1000Mhz
    
    chg_tef810x_txgain_cb(0,1,1,1);     //Profile-0,tx1gain=1,tx2gain=1,tx3gain=1
    chg_tef810x_txgain_cb(1,1,1,1);     //Profile-1,tx1gain=1,tx2gain=1,tx3gain=1
    
    chg_tef810x_rxgain_cb(0,1,1,1,1);   //Profile-0,rx1gain=1,rx2gain=1,rx3gain=1,rx4gain=1
    chg_tef810x_rxgain_cb(1,1,1,1,1);   //Profile-1,rx1gain=1,rx2gain=1,rx3gain=1,rx4gain=1
    
    chg_tef810x_filter_cb(0,100,15);    //profile-0,HPF=100Khz,LPF=15Mhz
    chg_tef810x_filter_cb(1,100,15);    //profile-1,HPF=100Khz,LPF=15Mhz
    re_init_TEF810x_cb(1);				//Reinit
}

static void get_tgg_real_range(void)
{
    set_tef_in_clbi_mode();
    spt_long_start(get_tgg_real_range_done);
}

static void reset_tef_cfg_to_default()
{
    re_init_TEF810x_cb(0);
}

static void coefs_iron_tester(char** args, int count)
{
	uint8_t save=0;
	float numer;

	if(count > 2) {
        if(!strcmp("get", args[1])){
            reset_asft_hsft();
            
            float aoa=frame_get_aoa_shift(0);
	        float acoefs=frame_get_acoefs();

			para.clb_range = strtof(args[2], NULL);
			para.clb_angle = 0;

			if(count > 3)
				para.clb_angle = strtof(args[3], NULL);

			if(acoefs)
	            para.clb_angle=para.clb_angle* acoefs;
	        para.clb_angle+=aoa;

			if(para.clb_range > 0)
			{
                para.spt_long_start_temp=frame_get_rngs_long_start();
                if(para.clb_range<=para.spt_long_start_temp){
                    if((para.clb_range-0.5)>=0.5){
                        frame_set_rngs_long_start(para.clb_range-0.5,0);
                    }else{
                        frame_set_rngs_long_start(0.5,0);
                    }
                }
                PRINTF("iron-get r=%.1f a=%.1f\n",para.clb_range,para.clb_angle);
                detect_equipment_counter=0;
                get_tgg_real_range();
            }
			return;
		}

		if(!strcmp("mag", args[1])){
            calib_iron_parameters.pars.equipment_magdB_threshold = strtof(args[2], NULL);
            save=1;
		}
		else
		if(!strcmp("angle", args[1])){
		    calib_iron_parameters.pars.equipment_angle_tolerance = strtof(args[2], NULL);
		    save=1;
		}
		else
		if(!strcmp("vangle", args[1])){
		    calib_iron_parameters.pars.equipment_vangle_tolerance = strtof(args[2], NULL);
		    save=1;
		}
		else
		if(!strcmp("measu_num", args[1])){
		    calib_iron_parameters.pars.number_of_measurement = strtof(args[2], NULL);
            save=1;
		}
		else
		if(!strcmp("magdiff", args[1])){
		    calib_iron_parameters.pars.equipment_magdB_dif_tolerance = strtof(args[2], NULL);
            save=1;
		}
		else
		if(!strcmp("num", args[1])){
            numer=strtof(args[2], NULL);
            if((numer>5)&&(numer!=calib_iron_parameters.pars.number_of_inspections))
            {
                save=1;
                if(numer<calib_iron_parameters.pars.number_of_inspections)
                {
                    if(calib_iron_parameters.pars.correct_cnt_threshold>numer)
                        calib_iron_parameters.pars.correct_cnt_threshold=numer;

                    if(calib_iron_parameters.pars.not_found_cnt_threshold>numer)
                        calib_iron_parameters.pars.not_found_cnt_threshold=numer;

                    if(calib_iron_parameters.pars.range_err_cnt_threshold>numer)
                        calib_iron_parameters.pars.range_err_cnt_threshold=numer;

                    if(calib_iron_parameters.pars.aoa_err_cnt_threshold>numer)
                        calib_iron_parameters.pars.aoa_err_cnt_threshold=numer;
                        
                    if(calib_iron_parameters.pars.vaoa_err_cnt_threshold>numer)
                        calib_iron_parameters.pars.vaoa_err_cnt_threshold=numer;    
                }
                calib_iron_parameters.pars.number_of_inspections=numer;
		    }
		}
		else
		if(!strcmp("correct", args[1])){
            numer=strtof(args[2], NULL);
            if(numer<=calib_iron_parameters.pars.number_of_inspections)
            {
                calib_iron_parameters.pars.correct_cnt_threshold = numer;
                save=1;
            }
		}
		else
		if(!strcmp("notfound", args[1])){
            numer=strtof(args[2], NULL);
            if(numer<=calib_iron_parameters.pars.number_of_inspections)
            {
                calib_iron_parameters.pars.not_found_cnt_threshold = numer;
                save=1;
            }
		}
		else
		if(!strcmp("range", args[1])){
            numer=strtof(args[2], NULL);
            if(numer<=calib_iron_parameters.pars.number_of_inspections)
            {
                calib_iron_parameters.pars.range_err_cnt_threshold = numer;
                save=1;
            }
		}
		else
		if(!strcmp("aoa", args[1])){
            numer=strtof(args[2], NULL);
            if(numer<=calib_iron_parameters.pars.number_of_inspections)
            {
                calib_iron_parameters.pars.aoa_err_cnt_threshold = numer;
                save=1;
            }
		}
		else
		if(!strcmp("vaoa", args[1])){
            numer=strtof(args[2], NULL);
            if(numer<=calib_iron_parameters.pars.number_of_inspections)
            {
                calib_iron_parameters.pars.vaoa_err_cnt_threshold = numer;
                save=1;
            }
		}
		else 
		 if(!strcmp("va_comp", args[1]) && count >= 13) {
			calib_iron_parameters.pars.vangle_compensation_table[0] = strtof(args[2], NULL);
			calib_iron_parameters.pars.vangle_compensation_table[1] = strtof(args[3], NULL);
			calib_iron_parameters.pars.vangle_compensation_table[2] = strtof(args[4], NULL);
			calib_iron_parameters.pars.vangle_compensation_table[3] = strtof(args[5], NULL);
			calib_iron_parameters.pars.vangle_compensation_table[4] = strtof(args[6], NULL);
			calib_iron_parameters.pars.vangle_compensation_table[5] = strtof(args[7], NULL);
			calib_iron_parameters.pars.vangle_compensation_table[6] = strtof(args[8], NULL);
			calib_iron_parameters.pars.vangle_compensation_table[7] = strtof(args[9], NULL);
		    calib_iron_parameters.pars.vangle_compensation_table[8] = strtof(args[10], NULL);
		    calib_iron_parameters.pars.vangle_compensation_table[9] = strtof(args[11], NULL);
		    calib_iron_parameters.pars.vangle_compensation_table[10] = strtof(args[12], NULL);
		    save=1;
		}
		else
		if(!strcmp("tar_angle", args[1])){
            numer=strtof(args[2], NULL);
            calib_iron_parameters.pars.target_offset_angle = numer;
            save=1;
		}
		else
		if(!strcmp("tar_distance", args[1])){
            numer=strtof(args[2], NULL);
            calib_iron_parameters.pars.target_distance = numer;
            save=1;
		}
		else
		if(!strcmp("bw", args[1])){
            numer=strtof(args[2], NULL);
            calib_iron_parameters.pars.calib_iron_bandwidth = numer;
            save=1;
		}
		else if(!strcmp("json",args[1])){
			char* json = (char*)spt_work_space_get();
			count = clbi_info_in_jsons(json);
			json[count++] = '#';
			json[count] = '\0';
			put_string(json);
			return;
		}
		if(save)
		{
		    pars_set((pars_ctx_p)&calib_iron_parameters);
		}
	}

#if 1
	if(count==2){
	    if(!strcmp("test", args[1])){         
	        //start_iron_calibration(iron_test);
	        start_iron_calibration(NULL);
	        return;
	    }else
	    if(!strcmp("stop", args[1])){  
	         stop_iron_calibration();
	         return;
	    }else
	    if(!strcmp("init", args[1])){  
	         set_tef_in_clbi_mode();
	         return;
	    }              
	}
	
#endif
	
	coefs_iron_pars_dump();
}


void save_calib_iron_result_to_EE(calib_equipment_e iron_calib_status, iron_calib_result_p iron_calib_result)
{
    calib_iron_parameters.pars.radar_alignment_result=iron_calib_status;
    calib_iron_parameters.pars.h_alignment_angle=iron_calib_result->iron_angle;
    calib_iron_parameters.pars.v_alignment_angle=iron_calib_result->iron_vangle;
    calib_iron_parameters.pars.alignment_received_power=iron_calib_result->iron_mag;
//    calib_iron_parameters.pars.alignment_completion_flag=CALIB_IRON_COMPLETED;
    pars_set((pars_ctx_p)&calib_iron_parameters);
}


calib_status_e start_iron_calibration(iron_calib_done_p done_cb)
{
	para.calib_iron_elapsed_time=STM_0.CNT.R;
	float range =calib_iron_parameters.pars.target_distance;
	float angle =calib_iron_parameters.pars.target_offset_angle;
	
	set_tef810x_production_mode(kPRODUCTION_MODE);
	if(CALIB_STATUS_BUSY != get_calib_iron_sta())
	{
	    calib_iron_info.calibration_sta = CALIB_STATUS_START;
	    calib_iron_info.calibration_result = CALIB_EQUIPMENT_PROCESSING;
	    calib_iron_parameters.pars.radar_alignment_result=CALIB_EQUIPMENT_PROCESSING;
	    reset_asft_hsft();
	    
	    float spt_aoa=frame_get_aoa_shift(0);
	    float spt_acoefs=frame_get_acoefs();
	    
        para.spt_long_start_temp=frame_get_rngs_long_start();
        if(range<=para.spt_long_start_temp){
            if((range-0.5)>=1){
                frame_set_rngs_long_start(range-0.5,0);
            }else{
                frame_set_rngs_long_start(1,0);
            }
        }
        
	    if(spt_acoefs)
	    	angle=angle* spt_acoefs;
	    angle+=spt_aoa;
        
		para.clb_range =range;
	    para.clb_angle =angle;
	    iron_calib_done=done_cb;
	    detect_equipment_counter=0;
		get_tgg_real_range();
	    
		return CALIB_STATUS_START;
	}
	else
	{
		return CALIB_STATUS_BUSY;
	}
}

void stop_iron_calibration()
{
	reset_tef_cfg_to_default();
}

calib_status_e get_calib_iron_sta(void)
{
    return calib_iron_info.calibration_sta;
}

float get_calib_iron_target_offset_angle(void)
{
    return calib_iron_parameters.pars.target_offset_angle;
}

void set_calib_iron_target_offset_angle(float angle)
{
    calib_iron_parameters.pars.target_offset_angle=angle;
    pars_set((pars_ctx_p)&calib_iron_parameters);
}

float get_calib_iron_target_distance(void)
{
    return calib_iron_parameters.pars.target_distance;
}

void set_calib_iron_target_distance(float range)
{
    calib_iron_parameters.pars.target_distance=range;
    pars_set((pars_ctx_p)&calib_iron_parameters);
}

uint8_t get_calib_iron_alignment_completion_flag(void)
{
    return calib_iron_parameters.pars.alignment_completion_flag;
}

void set_calib_iron_alignment_completion_flag(uint8_t flag)
{
    calib_iron_parameters.pars.alignment_completion_flag=flag;
    pars_set((pars_ctx_p)&calib_iron_parameters);
}

calib_equipment_e get_calib_iron_radar_alignment_result(void)
{
    return calib_iron_parameters.pars.radar_alignment_result;
}

void set_calib_iron_radar_alignment_result(calib_equipment_e result)
{
    calib_iron_parameters.pars.radar_alignment_result=result;
    pars_set((pars_ctx_p)&calib_iron_parameters);
}


float get_calib_iron_h_alignment_angle(void)
{
    return calib_iron_parameters.pars.h_alignment_angle;
}

void set_calib_iron_h_alignment_angle(float angle)
{
    calib_iron_parameters.pars.h_alignment_angle=angle;
    pars_set((pars_ctx_p)&calib_iron_parameters);
}

float get_calib_iron_v_alignment_angle(void)
{
    return calib_iron_parameters.pars.v_alignment_angle;
}

void set_calib_iron_v_alignment_angle(float angle)
{
    calib_iron_parameters.pars.v_alignment_angle=angle;
    pars_set((pars_ctx_p)&calib_iron_parameters);
}

float get_calib_iron_alignment_received_power(void)
{
    return calib_iron_parameters.pars.alignment_received_power;
}

void set_calib_iron_alignment_received_power(float power)
{
    calib_iron_parameters.pars.alignment_received_power=power;
    pars_set((pars_ctx_p)&calib_iron_parameters);
}

calib_iron_pars_status get_calib_iron_pars_status(void)
{
//    if(calib_iron_parameters.pars.target_distance < 1.2){
//        return CALIB_IRON_PARS_DISTANCE_ERR;
//    }else
    if( calib_iron_parameters.pars.target_offset_angle!=0){
        return CALIB_IRON_PARS_ANGLE_ERR;    
    }
    
    return CALIB_IRON_PARS_CORRECT;
}
    
void coefs_rmtp_pars_init(coefs_data_p* cfs, void(**pset)(void))
{
    *cfs=coefs;
    *pset=coefs_pars_set;    
    
}

