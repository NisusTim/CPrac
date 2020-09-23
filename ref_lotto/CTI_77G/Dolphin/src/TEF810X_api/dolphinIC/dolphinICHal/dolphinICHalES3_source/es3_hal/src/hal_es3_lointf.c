/*------------------------------------------------------------------------------*/
/* Copyright(C) NXP B.V. 2016													*/
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
* @file hal_es3_lointf.c
*
* @ver v5.3.0  
*
* @author
*
* @date
*
* @brief interface Control/Config API.
*
*
******************************************************************************/

#include <hal_es3.h>

#ifdef DOLPHIN_CFG_ES3

#include <es3/NXP_TEF810X_LoInterface.h>

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	DolphinIC_rval_t hal_es3_lointf_CfgMode(int mode, uint8_t b2gain)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod0A_LoInterfaceGainControlUnion_t GainControl;
		Nxp_Tef810x_Mod0A_LoInterfaceControlUnion_t LOIntControl;

		bool b1 = false;
		bool b2 = false;
		bool b3 = false;
		bool b4 = false;
		bool mux = false;

		HAL_GERRCODE_INIT;

		switch (mode)
		{
		case hal_es3_lointf_Mode_LOOPTHRU:
			// MUX=1|B1=1|B2=1|B3=1|B4=1
			b1 = true;
			b2 = true;
			b3 = true;
			b4 = true;
			mux = true;
			break;
		case hal_es3_lointf_Mode_EXTLOOUT:
			// MUX=0|B1=1|B2=1|B3=0|B4=1
			b1 = true;
			b2 = true;
			b3 = false;
			b4 = true;
			mux = false;
			break;
		case hal_es3_lointf_Mode_EXTLOIN:
			// MUX=1|B1=0|B2=1|B3=1|B4=0
			b1 = false;
			b2 = true;
			b3 = true;
			b4 = false;
			mux = true;
			break;
		case hal_es3_lointf_Mode_NORMAL:
		default:
			// MUX=0|B1=1|B2=1|B3=0|B4=0
			b1 = true;
			b2 = true;
			b3 = false;
			b4 = false;
			mux = false;
			break;
		}

		//Capture ES2 design change here:
		//For finer control, use ES2 gain control scheme: 5-bit binary code (32 choices) vs ES1 thermalmeter code
		//No need to read here, since all fields are configured below.
		//Mod-Wr
		GainControl.val_u32 = 0;
		GainControl.bits_st.GainCodeSel = b2gain;
		GainControl.bits_st.GainThermoLutSel = 1;

		glue_reg_WriteCheck(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, GainControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//LO_INTERFACE_CONTROL
		//Rd-Mod-Wr
		glue_reg_Read(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_CONTROL_U16, &LOIntControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		LOIntControl.bits_st.EnB1 = b1 ? 1 : 0;
		LOIntControl.bits_st.EnB2 = b2 ? 1 : 0;
		LOIntControl.bits_st.EnB3 = b3 ? 1 : 0;
		LOIntControl.bits_st.EnB4 = b4 ? 1 : 0;
		LOIntControl.bits_st.CntrMuxLoSpi = mux ? 1 : 0;

		//this gain is not used anymore, use LOINTF_LO_INTERFACE_GAIN_CONTROL for ES2 instead
		//regval |= (b2gain << LOINTF_LO_INTERFACE_CONTROL_GAIN_B2_SET_SPI_POS);

		glue_reg_WriteCheck(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_CONTROL_U16, LOIntControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Enable LO interface
		hal_es3_lointf_EnableLo(true);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_lointf_EnableLo(bool benable)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod0A_LoInterfaceControlUnion_t LOIntControl;

		HAL_GERRCODE_INIT;

		glue_reg_Read(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_CONTROL_U16, &LOIntControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		LOIntControl.bits_st.EnLo = benable ? 1 : 0;

		glue_reg_WriteCheck(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_CONTROL_U16, LOIntControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif //DOLPHIN_CFG_ES3
