/*------------------------------------------------------------------------------*/
/* Copyright(C) NXP B.V. 2017													*/
/*																				*/
/* All rights are reserved. Reproduction in whole or in part is prohibited		*/
/* without the prior written consent of the copy-right owner.					*/
/* This source code and any compilation or derivative thereof is the sole		*/
/* property of NXP B.V. and is provided pursuant to a Software License			*/
/* Agreement. This code is the proprietary information of NXP B.V. and			*/
/* is confidential in nature. Its use and dissemination by any party other		*/
/* than NXP B.V. is strictly limited by the confidential information			*/
/* provisions of the agreement referenced above.								*/
/*																				*/
/* NXP reserves the right to make changes without notice at any time.			*/
/* NXP makes no warranty, expressed, implied or statutory, including but		*/
/* not limited to any implied warranty of merchantability or fitness for any	*/
/* particular purpose, or that the use will not infringe any third party patent,*/
/* copyright or trademark. NXP must not be liable for any loss or damage		*/
/* arising from its use.														*/
/*------------------------------------------------------------------------------*/

/**
*
* @file hal_es3_atb.c
*
* @ver v5.3.0  
*
* @author Baris Can Kara
*
* @date 03/04/2017
*
* @brief ATB Low-Level Interface.
*
*
******************************************************************************/

/******************************************************************************
* INCLUDES
*****************************************************************************/
#include <hal_es3.h>
#include <hal_es3_ctrl.h>
#include <math.h>

#ifdef DOLPHIN_CFG_ES3

#include <es3/NXP_TEF810X_ChirpAfc.h>
#include <es3/NXP_TEF810X_TimingEngine.h>
#include <es3/NXP_TEF810X_Ism.h>
#include <es3/NXP_TEF810X_CentralControl.h>
#include <es3/NXP_TEF810X_TX.h>
#include <es3/NXP_TEF810X_Atb.h>

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	DolphinIC_rval_t hal_es3_atb_Init(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t regVal = 0x00;
		Nxp_Tef810x_Mod16_LdoAtbControlUnion_t ATB_LDO_Control;

		HAL_GERRCODE_INIT;
		//Enable LDO for the ATB if it is not already enabled
		glue_reg_Read(ATB_MODULE_ADDRESS, NXP_TEF810X_MOD16_LDO_ATB_CONTROL_U16, &ATB_LDO_Control.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (ATB_LDO_Control.bits_st.LdoEnAtb == 0)
		{
			ATB_LDO_Control.bits_st.LdoEnAtb = 1;
			glue_reg_WriteCheck(ATB_MODULE_ADDRESS, NXP_TEF810X_MOD16_LDO_ATB_CONTROL_U16, ATB_LDO_Control.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			//wait 25us for LDO to settle
			glue_Sleep(0.025);
		}

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_atb_TempReadout(uint8_t _chooseATB, uint16_t _chooseIP, float * p_TempC)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint8_t ATB_atb_pol = 1;
		uint8_t ATB_atb_gain = 1;
		
		float(*p_ADC_Read0) = 0;
		float(*p_ADC_Read1) = 0;

		uint32_t ATB_CONFIG_REG = 0x00;
//		uint32_t ATB_ADC_BUF_REG = 0x00;
//		uint32_t ATB_DC_BUS_REG = 0x00;
		uint32_t ATB_EN_REGISTER = 0x00;
		uint32_t ATB_AC_EN_REGISTER = 0x00;
		uint32_t MODULE_ADDRESS = _chooseIP;
		uint32_t TX_ATB_SEL = 0x00;
		uint32_t CAFC_ATB_SEL = 0x00;
//		uint32_t regVal = 0x00;
		//hardcoded OTP values
		uint32_t OTP_224 = g_OTPShadowLUT_ES3[9]; 		//Hardcoded OTP values for address 224 (for chirp)
		uint32_t OTP_228 = g_OTPShadowLUT_ES3[10]; 		//Hardcoded OTP values for address 228 (for TXs)
		uint32_t OTP_250 = g_OTPShadowLUT_ES3[20];		//Hardcoded OTP values for address 250 (for ATB1)
//		uint32_t OTP_254 = g_OTPShadowLUT_ES3[21];		//Hardcoded OTP values for address 254 (for ATB2)

		//uint32_t OTP_224 = 0xd70ad8fd; 		//Hardcoded OTP values for address 224 (for chirp)
		//uint32_t OTP_228 = 0x9705c570; 		//Hardcoded OTP values for address 228 (for TXs)
		//uint32_t OTP_250 = 0xbf3fb060;		//Hardcoded OTP values for address 250 (for ATB1)
		//uint32_t OTP_254 = 0xdfdf5850;		//Hardcoded OTP values for address 254 (for ATB2)
		//variables
//		uint32_t	ADC_raw = 0x00;			//Raw readout value from BIST-ADC
		uint32_t	v125 = 0x00;			//LSB ->voltage reading at 125C in WT (u32)
		float		fV125 = 0;				//LSB ->voltage reading at 125C in WT (f)
//		float		fV125_mv = 0;			//mV ->voltage reading at 125C in WT (f)
		float		gain_TS = 1.07f;			//mV/K -> use fixed gain_TS of 1.001 based on ATE data (artf598986)
//		float		T_v_ADC = 0x00;			//mV ->Temp.in mV after correction from ADC
		float		typical_gain = 1.800f;	//mV/LSB -> fixed gain for BISTADC readout
		float		gainOTP_f = 0;			//conversion coefficient uV / LSB (f)
		uint32_t	gainOTP = 0x00;			//conversion coefficient uV / LSB (u32)
		uint32_t	error_offset = 0x00;	//LSB -> readout error offset (u32)
		float		T_c = 0;				//C -> Temp.in C
//		float		error_offset_f = 0;		//LSB -> readout error offset (f)
		float 		gain_total = 0;
		float		ADC_raw0 = 0;			//ADC_RAW0 -> LSB reading from ATB-BISTADC /w polarity0
		float		ADC_raw1 = 0;			//ADC_RAW1 -> LSB reading from ATB-BISTADC /w polarity1
		float		ADC_avg = 0;			//Avg. of two polarity readings

		Nxp_Tef810x_Mod00_Atb1EnRegisterUnion_t				atbEn;
		Nxp_Tef810x_Mod00_Atb1AcEnRegisterUnion_t			atbAcEn;
		Nxp_Tef810x_Mod16_Atb1ConfigRegisterUnion_t			atbConfig;
		Nxp_Tef810x_Mod06_ControlSpareUnion_t				CafcCctrlSpare;
		
		Nxp_Tef810x_Mod06_AtbUnion_t						CafcAtb;
		Nxp_Tef810x_Mod06_FuncsafeMonTemperatureVcoUnion_t	TempSensorCtrl;
		Nxp_Tef810x_Mod11_TsPdUnion_t						TxTsPd;
		Nxp_Tef810x_Mod11_Atb1Union_t						TxAtb;
		Nxp_Tef810x_Mod11_TsSelUnion_t						TxTsSel;
		Nxp_Tef810x_Mod11_Atb1Union_t						TxAtb2;
		Nxp_Tef810x_Mod11_TsSelUnion_t						Tx2TsSel;
		Nxp_Tef810x_Mod11_TsPdUnion_t						Tx3TsPd;
		Nxp_Tef810x_Mod11_Atb1Union_t						Tx3Atb;
		Nxp_Tef810x_Mod11_TsSelUnion_t						Tx3TsSel;
//		Nxp_Tef810x_Mod06_ControlSpareUnion_t				CafcCtrlSpare;
		///*-----------------------------------------------------*///
		HAL_GERRCODE_INIT;

		p_ADC_Read0 = &ADC_raw0;
		p_ADC_Read1 = &ADC_raw1;
		if (_chooseATB == 1)
		{
			ATB_CONFIG_REG = NXP_TEF810X_MOD16_ATB1_CONFIG_REGISTER_U16;
//			ATB_ADC_BUF_REG = NXP_TEF810X_MOD16_ADC_BUF1_CONTROL_REG_U16;
//			ATB_DC_BUS_REG = NXP_TEF810X_MOD16_ATB1_U16;
			ATB_EN_REGISTER = NXP_TEF810X_MOD00_ATB1_EN_REGISTER_U16;
			ATB_AC_EN_REGISTER = NXP_TEF810X_MOD00_ATB1_AC_EN_REGISTER_U16;
			TX_ATB_SEL = NXP_TEF810X_MOD11_ATB1_U16;
			CAFC_ATB_SEL = NXP_TEF810X_MOD06_ATB_U16;
		}
		else if (_chooseATB == 2)
		{
			ATB_CONFIG_REG = NXP_TEF810X_MOD16_ATB2_CONFIG_REGISTER_U16;
//			ATB_ADC_BUF_REG = NXP_TEF810X_MOD16_ADC_BUF1_CONTROL_REG_U16;
//			ATB_DC_BUS_REG = NXP_TEF810X_MOD16_ATB2_U16;
			ATB_EN_REGISTER = NXP_TEF810X_MOD00_ATB2_EN_REGISTER_U16;
			ATB_AC_EN_REGISTER = NXP_TEF810X_MOD00_ATB2_AC_EN_REGISTER_U16;
			TX_ATB_SEL = NXP_TEF810X_MOD11_ATB2_U16;
			CAFC_ATB_SEL = 0;
		}
		else
		{
			DbgInfo("Check your input parameters!\n");
			HAL_GEC_ASSERT(DOLPHINIC_EC_INPUTOUTOFRANGE);
		}
		//START CALCULATIONS
		//parse conversion coefficient uV / LSB (u32)
		gainOTP = OTP_250 & 0xFF;
		//flip bits
		gainOTP = hal_es3_bit_flip(gainOTP, 8);
		//convert to integer from 2s complement
		gainOTP_f = hal_es3_2sComplement(gainOTP, 8); //uV/LSB
		// calculate overall gain
		gain_total = (typical_gain + (gainOTP_f / 1000)); //mV/LSB

		//ATB CONFIGURATIONS
		//Declare Atb En Register
		

		//Configure ATB1 connections
		

		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, ATB_AC_EN_REGISTER, &atbAcEn.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		atbAcEn.bits_st.EnAtb1SsbmodAcGnd = 1;
		atbAcEn.bits_st.EnAtb1Rx1AcGnd = 1;
		atbAcEn.bits_st.EnAtb1AdcAcGnd = 1;
		atbAcEn.bits_st.EnAtb1DcToInt0 = 1;
		atbAcEn.bits_st.EnAtb1DcToInt180 = 1;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, ATB_AC_EN_REGISTER, atbAcEn.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//configure ATB1 buffer
		
		glue_reg_Read(ATB_MODULE_ADDRESS, ATB_CONFIG_REG, &atbConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		atbConfig.bits_st.EnAtb1AdcSwp = 1;
		atbConfig.bits_st.EnAtb1AdcSwn = 1;
		atbConfig.bits_st.EnAtb1RtrimRpGnd = 1;
		atbConfig.bits_st.EnAtb1RtrimRnGnd = 1;
		atbConfig.bits_st.SetAtb1Rtrim = 8;
		atbConfig.bits_st.SetAtb1RtrimRn = 8;

		glue_reg_WriteCheck(ATB_MODULE_ADDRESS, ATB_CONFIG_REG, atbConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);



		//IP specific config. and calculations
		switch (MODULE_ADDRESS)
		{
		case 0x06:
		{
			//parse the BISTADC reading at 125C in WT (u32) [LSB]
			v125 = (OTP_224 & 0xFFC00000) >> 22;
			//flip bits
			fV125 = hal_es3_bit_flip(v125, 10);  //LSB
			//convert the LSB to mV
			//fV125_mv = fV125 * gain_total;

			//parse error offset (u32)
			error_offset = (OTP_250 & 0xFF0000) >> 16;
			//flip bits
			error_offset = hal_es3_bit_flip(error_offset, 8);
			//convert to integer from 2s complement
	//		error_offset_f = hal_es3_2sComplement(error_offset, 8); //LSB
			

			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, ATB_EN_REGISTER, &atbEn.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			atbEn.bits_st.Atb1En = 1;
			atbEn.bits_st.Atb1Set = 6;

			glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, ATB_EN_REGISTER, atbEn.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Enable bias for temperature sensor
			
			glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CONTROL_SPARE_U16, &CafcCctrlSpare.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			CafcCctrlSpare.bits_st.CtlIbiasTs100UEnLs = 1;

			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CONTROL_SPARE_U16, CafcCctrlSpare.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//enable ATB DC test bus, choose  temp. sens. output buffer
			if (CAFC_ATB_SEL == 0)
				HAL_GEC_ASSERT(DOLPHINIC_EC_INPUTOUTOFRANGE);
			
			glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, CAFC_ATB_SEL, &CafcAtb.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			CafcAtb.bits_st.AtbEn = 1;
			CafcAtb.bits_st.AtbSet = 7;

			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, CAFC_ATB_SEL, CafcAtb.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			
			glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_TEMPERATURE_VCO_U16, &TempSensorCtrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			TempSensorCtrl.bits_st.CtlTempSensorChopperSpi = 0;

			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_TEMPERATURE_VCO_U16, TempSensorCtrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_atb_read_BISTADC(_chooseATB, ATB_atb_pol, ATB_atb_gain, p_ADC_Read0);

			TempSensorCtrl.bits_st.CtlTempSensorChopperSpi = 1;

			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_TEMPERATURE_VCO_U16, TempSensorCtrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_atb_read_BISTADC(_chooseATB, ATB_atb_pol, ATB_atb_gain, p_ADC_Read1);
			break;
		}
		case 0x11:
		{
			//parse the BISTADC reading at 125C in WT (u32) [LSB]
			v125 = (OTP_228 & 0xFFC00000) >> 22;
			
			//flip bits
			fV125 = hal_es3_bit_flip(v125, 10);  //LSB
			DbgInfo("V125-Raw =  %f \n", fV125);
			//convert the LSB to mV
			//fV125_mv = fV125 * gain_total;

			//parse error offset (u32)
			error_offset = (OTP_250 & 0xFF0000) >> 16;
			DbgInfo("ErrorOffset-Raw =  %d \n", error_offset);
			//flip bits
			error_offset = hal_es3_bit_flip(error_offset, 8);
			//convert to integer from 2s complement
//			error_offset_f = hal_es3_2sComplement(error_offset, 8); //LSB
			

			//Enable ATB1 and choose CAFC

			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, ATB_EN_REGISTER, &atbEn.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			atbEn.bits_st.Atb1En = 1;
			atbEn.bits_st.Atb1Set = 0x11;

			glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, ATB_EN_REGISTER, atbEn.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Activate temperature sensor
			
			glue_reg_Read(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_PD_U16, &TxTsPd.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			TxTsPd.bits_st.TsPdSpi = 0;

			glue_reg_WriteCheck(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_PD_U16, TxTsPd.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//enable ATB DC test bus, choose  temp. sens. output buffer
			
			glue_reg_Read(TX1_MODULE_ADDRESS, TX_ATB_SEL, &TxAtb.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			TxAtb.bits_st.Atb1En = 1;
			TxAtb.bits_st.Atb1Set = 0xE;

			glue_reg_WriteCheck(TX1_MODULE_ADDRESS, TX_ATB_SEL, TxAtb.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Set the polarity to zero (bit8)
			
			glue_reg_Read(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_SEL_U16, &TxTsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			TxTsSel.bits_st.TsBufGainCtrlSpi = 0;

			glue_reg_WriteCheck(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_SEL_U16, TxTsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_atb_read_BISTADC(_chooseATB, ATB_atb_pol, ATB_atb_gain, p_ADC_Read0);

			TxTsSel.bits_st.TsBufGainCtrlSpi = 1;

			glue_reg_WriteCheck(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_SEL_U16, TxTsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_atb_read_BISTADC(_chooseATB, ATB_atb_pol, ATB_atb_gain, p_ADC_Read1);

			break;
		}
		case 0x12:
		{
			//parse the BISTADC reading at 125C in WT (u32) [LSB]
			v125 = (OTP_228 & 0x003FF000) >> 12;
			
			//flip bits
			fV125 = hal_es3_bit_flip(v125, 10);  //LSB
			DbgInfo("V125-Raw =  %f \n", fV125);
			//convert the LSB to mV
			//fV125_mv = fV125 * gain_total;

			//parse error offset (u32)
			error_offset = (OTP_250 & 0xFF0000) >> 16;
			DbgInfo("ErrorOffset-Raw =  %d \n", error_offset);
			//flip bits
			error_offset = hal_es3_bit_flip(error_offset, 8);
			//convert to integer from 2s complement
//			error_offset_f = hal_es3_2sComplement(error_offset, 8); //LSB


			//Enable ATB1 and choose CAFC

			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, ATB_EN_REGISTER, &atbEn.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			atbEn.bits_st.Atb1En = 1;
			atbEn.bits_st.Atb1Set = 0x12;

			glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, ATB_EN_REGISTER, atbEn.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			//Activate temperature sensor
			
			glue_reg_Read(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_PD_U16, &TxTsPd.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			TxTsPd.bits_st.TsPdSpi = 0;

			glue_reg_WriteCheck(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_PD_U16, TxTsPd.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//enable ATB DC test bus, choose  temp. sens. output buffer
			
			glue_reg_Read(TX2_MODULE_ADDRESS, TX_ATB_SEL, &TxAtb2.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			TxAtb2.bits_st.Atb1En = 1;
			TxAtb2.bits_st.Atb1Set = 0xE;

			glue_reg_WriteCheck(TX2_MODULE_ADDRESS, TX_ATB_SEL, TxAtb2.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Set the polarity to zero (bit8)
			
			glue_reg_Read(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_SEL_U16, &Tx2TsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			Tx2TsSel.bits_st.TsBufGainCtrlSpi = 0;

			glue_reg_WriteCheck(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_SEL_U16, Tx2TsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_atb_read_BISTADC(_chooseATB, ATB_atb_pol, ATB_atb_gain, p_ADC_Read0);

			Tx2TsSel.bits_st.TsBufGainCtrlSpi = 1;

			glue_reg_WriteCheck(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_SEL_U16, Tx2TsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_atb_read_BISTADC(_chooseATB, ATB_atb_pol, ATB_atb_gain, p_ADC_Read1);
			break;
			}

		case 0x13:
		{
			//parse the BISTADC reading at 125C in WT (u32) [LSB]
			v125 = (OTP_228 & 0x00000FFC) >> 2;
			
			//flip bits
			fV125 = hal_es3_bit_flip(v125, 10);  //LSB
			DbgInfo("V125-Raw =  %f \n", fV125);
			//convert the LSB to mV
			//fV125_mv = fV125 * gain_total;


			//parse error offset (u32)
			error_offset = (OTP_250 & 0xFF0000) >> 16;
			DbgInfo("ErrorOffset-Raw =  %d \n", error_offset);
			//flip bits
			error_offset = hal_es3_bit_flip(error_offset, 8);
			//convert to integer from 2s complement
//			error_offset_f = hal_es3_2sComplement(error_offset, 8); //LSB

			//Enable ATB1 and choose CAFC

			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, ATB_EN_REGISTER, &atbEn.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			atbEn.bits_st.Atb1En = 1;
			atbEn.bits_st.Atb1Set = 0x13;

			glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, ATB_EN_REGISTER, atbEn.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Activate temperature sensor
			
			glue_reg_Read(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_PD_U16, &Tx3TsPd.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			Tx3TsPd.bits_st.TsPdSpi = 0;

			glue_reg_WriteCheck(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_PD_U16, Tx3TsPd.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//enable ATB DC test bus, choose  temp. sens. output buffer
			glue_reg_Read(TX3_MODULE_ADDRESS, TX_ATB_SEL, &Tx3Atb.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			Tx3Atb.bits_st.Atb1En = 1;
			Tx3Atb.bits_st.Atb1Set = 0xE;

			glue_reg_WriteCheck(TX3_MODULE_ADDRESS, TX_ATB_SEL, Tx3Atb.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Set the polarity to zero (bit8)
			
			glue_reg_Read(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_SEL_U16, &Tx3TsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			Tx3TsSel.bits_st.TsBufGainCtrlSpi = 0;

			glue_reg_WriteCheck(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_SEL_U16, Tx3TsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_atb_read_BISTADC(_chooseATB, ATB_atb_pol, ATB_atb_gain, p_ADC_Read0);

			Tx3TsSel.bits_st.TsBufGainCtrlSpi = 1;

			glue_reg_WriteCheck(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_SEL_U16, Tx3TsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_atb_read_BISTADC(_chooseATB, ATB_atb_pol, ATB_atb_gain, p_ADC_Read1);

			break;
			}
		}

		ADC_avg = (fabsf(ADC_raw0 - 512) + fabsf(ADC_raw1 - 512)) * 0.5f; 

		// Temp = 125[C] + (avg(code_tx) [LSB] ?code_125 [LSB]) x ( gain[mV/LSB] / gain_TS [mV/C] )
		T_c = 125 + (ADC_avg - fV125) * gain_total / gain_TS;
		DbgInfo("Calculated Temp =  %f \n", T_c);
		if (p_TempC != NULL){ *p_TempC = T_c; }

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_atb_read_BISTADC(uint8_t _atb, uint8_t _polarity, uint8_t _gainADC, float * readOut)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint32_t ADC_raw = 0x0;
//		uint32_t ATB_CONFIG_REG = 0x00;
		uint32_t ATB_ADC_BUF_REG = 0x00;

		Nxp_Tef810x_Mod16_AdcBuf1ControlRegUnion_t		AtbAdcBuff;
		Nxp_Tef810x_Mod16_AtbControlRegisterUnion_t		AtbControl;
		Nxp_Tef810x_Mod16_AtbDataRegisterUnion_t		AtbData;
		///*----------------------------*///

		HAL_GERRCODE_INIT;

		if (_atb == 1)
		{
//			ATB_CONFIG_REG = NXP_TEF810X_MOD16_ATB1_CONFIG_REGISTER_U16;
			ATB_ADC_BUF_REG = NXP_TEF810X_MOD16_ADC_BUF1_CONTROL_REG_U16;

		}
		else if (_atb == 2)
		{
//			ATB_CONFIG_REG = NXP_TEF810X_MOD16_ATB2_CONFIG_REGISTER_U16;
			ATB_ADC_BUF_REG = NXP_TEF810X_MOD16_ADC_BUF2_CONTROL_REG_U16;

		}
		else
		{
			DbgInfo("Check your input parameters!\n");
			HAL_GEC_ASSERT(DOLPHINIC_EC_INPUTOUTOFRANGE);
		}
		//configure ATB-ADC buffer
		
		glue_reg_Read(ATB_MODULE_ADDRESS, ATB_ADC_BUF_REG, &AtbAdcBuff.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		AtbAdcBuff.bits_st.PolAdcbuf1 = _polarity;
		AtbAdcBuff.bits_st.SelGainAdcbuf1 = _gainADC;
		AtbAdcBuff.bits_st.EnAdcbuf1 = 1;

		glue_reg_WriteCheck(ATB_MODULE_ADDRESS, ATB_ADC_BUF_REG, AtbAdcBuff.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Sample ATB-ADC for temperature
		glue_reg_Read(ATB_MODULE_ADDRESS, NXP_TEF810X_MOD16_ATB_CONTROL_REGISTER_U16, &AtbControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		AtbControl.bits_st.Adc2Fs = 1;
		AtbControl.bits_st.Adc1Fs = 1;
		AtbControl.bits_st.PonLs = 1;

		glue_reg_WriteCheck(ATB_MODULE_ADDRESS, NXP_TEF810X_MOD16_ATB_CONTROL_REGISTER_U16, AtbControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		AtbControl.bits_st.Adc2Fs = 0;
		AtbControl.bits_st.Adc1Fs = 0;
		AtbControl.bits_st.PonLs = 1;

		glue_reg_WriteCheck(ATB_MODULE_ADDRESS, NXP_TEF810X_MOD16_ATB_CONTROL_REGISTER_U16, AtbControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//TODO::should we check the ready bit for the BISTADC ? Debug and confirm that we get reaady bit set.
		glue_reg_Read(ATB_MODULE_ADDRESS, NXP_TEF810X_MOD16_ATB_DATA_REGISTER_U16, &AtbData.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (_atb == 0x1)
			ADC_raw = AtbData.bits_st.Adc1Data;
		else
			ADC_raw = AtbData.bits_st.Adc2Data;
		DbgInfo("ADC-RAW with polartiy %d, =  %d \n", AtbAdcBuff.bits_st.PolAdcbuf1, ADC_raw);
		*readOut = (float)ADC_raw;

		return HAL_GERRCODE;
	}
#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif //DOLPHIN_CFG_ES3
