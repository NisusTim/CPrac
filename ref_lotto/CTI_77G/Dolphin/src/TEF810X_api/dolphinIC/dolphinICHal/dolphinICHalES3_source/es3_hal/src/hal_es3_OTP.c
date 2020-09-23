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
* @file hal_es3_OTP.h
*
* @ver v5.3.0  
*
* @author
*
* @date 19/Oct/2017
*
* @brief OTP low level interface
*
*
******************************************************************************/

#include <hal_es3.h>
#include <hal_es3_ctrl.h>

#include <es3/NXP_TEF810X_CentralControl.h>
#include <es3/NXP_TEF810X_Otp.h>
#include <es3/NXP_TEF810X_Tx.h>
#include <es3/NXP_TEF810X_ChirpAfc.h>
#ifdef DOLPHIN_CFG_ES3

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	//OTP default values
	hal_es3_ism_OtpLUTValuePair_t g_DefaultEmuValueES3[ES3_DEV_OTP_EMU_SIZE] = {
		{ 0x200, 0x00 },
		{ 0x204, 0x00 },
		{ 0x208, 0x9221de10 },
		{ 0x20C, 0x000873c4 },
		//this register 0x210 contains site, mask and wafer info, 
		//use 0x1234ABCD to identify if this field is loaded from OTP or from emulated value
		{ 0x210, 0x1234ABCD/*0x4828708f*/ }, 
		{ 0x214, 0x0000500b },
		{ 0x218, 0x00000380 },
		{ 0x21C, 0x64a43064 },
		{ 0x220, 0x2c2cbc55 },
		{ 0x224, 0xd70ad8fd },
		{ 0x228, 0x9705c570 },
		{ 0x22C, 0xd5956358 },
		{ 0x230, 0xadad6d00 },
		{ 0x234, 0x0 },
		{ 0x238, 0xe2000000 },
		{ 0x23C, 0x02f008c4 },   //0x2f050c4,
		{ 0x240, 0x10010010 },  //0x11111111??  0x01165164
		{ 0x244, 0x0100AAE0 },
		{ 0x248, 0x5e6c395F },
		{ 0x24C, 0xba420088 },
		{ 0x250, 0xbf3fb060 },
		{ 0x254, 0xdfdf5850 },
		{ 0x258, 0xcd0528ba },
		{ 0x25C, 0xcd134cd0 },
		{ 0x260, 0x0 },
		{ 0x264, 0x30 },
		{ 0x268, 0x0 },
		{ 0x26C, 0x44644464 },
		{ 0x270, 0x30000000 }

	};


	//OTP table descriptions (from source v74), for each OTP address.
	//Note: specifying size of the arrays is necessary since sizeof operator is used on these arrays.
	const OtpTableDiscpES3_t reg_21C_cat1_ES3[31] = { 
		{ 0x21C, 18, 0xFC0000, 0x9, 0x024, 8, 0x3F00, 6},
		{ 0x21C, 18, 0xFC0000, 0x9, 0x00C, 0, 0x3F, 6},
		{ 0x21C, 18, 0xFC0000, 0x9, 0x010, 0, 0x3F, 6},
		{ 0x21C, 18, 0xFC0000, 0x9, 0x014, 0, 0x3F, 6},
		{ 0x21C, 18, 0xFC0000, 0x9, 0x018, 0, 0x3F, 6},
		{ 0x21C, 18, 0xFC0000, 0x9, 0x034, 16, 0x3F0000, 6},
		{ 0x21C, 18, 0xFC0000, 0x9, 0x058, 0, 0x3F, 6},
		{ 0x21C, 18, 0xFC0000, 0x9, 0x000, 8, 0x3F00, 6},
		{ 0x21C, 18, 0xFC0000, 0x9, 0x004, 8, 0x3F00, 6},
		{ 0x21C, 18, 0xFC0000, 0x9, 0x008, 8, 0x3F00, 6},
		{ 0x21C, 11, 0xF800, 0x9, 0x048, 0, 0x1F, 5},
		{ 0x21C, 11, 0xF800, 0xC, 0x000, 24, 0x1F000000, 5},
		{ 0x21C, 11, 0xF800, 0xC, 0x020, 8, 0x1F00, 5},
		{ 0x21C, 2, 0xFC, 0x9, 0x028, 0, 0x3F, 6},
		{ 0x21C, 2, 0xFC, 0x9, 0x02C, 0, 0x3F, 6},
		{ 0x21C, 2, 0xFC, 0x9, 0x030, 0, 0x3F, 6},
		{ 0x21C, 2, 0xFC, 0x9, 0x020, 8, 0x3F00, 6},
		{ 0x21C, 2, 0xFC, 0x9, 0x01C, 0, 0x3F, 6},
		{ 0x21C, 2, 0xFC, 0x9, 0x044, 0, 0x3F, 6},
		{ 0x21C, 2, 0xFC, 0x9, 0x034, 8, 0x3F00, 6},
		{ 0x21C, 2, 0xFC, 0x9, 0x054, 0, 0x3F, 6},
		{ 0x21C, 26, 0xFC000000, 0x9, 0x038, 0, 0x3F, 6},
		{ 0x21C, 26, 0xFC000000, 0x9, 0x020, 0, 0x3F, 6},
		{ 0x21C, 26, 0xFC000000, 0x9, 0x03C, 0, 0x3F, 6},
		{ 0x21C, 26, 0xFC000000, 0x9, 0x024, 0, 0x3F, 6},
		{ 0x21C, 26, 0xFC000000, 0x9, 0x040, 0, 0x3F, 6},
		{ 0x21C, 26, 0xFC000000, 0x9, 0x034, 0, 0x3F, 6},
		{ 0x21C, 26, 0xFC000000, 0x9, 0x000, 0, 0x3F, 6},
		{ 0x21C, 26, 0xFC000000, 0x9, 0x004, 0, 0x3F, 6},
		{ 0x21C, 26, 0xFC000000, 0x9, 0x008, 0, 0x3F, 6}
	};

	const OtpTableDiscpES3_t reg_220_cat1_ES3[2] = { 
		{ 0x220, 18, 0xFC0000, 0x11, 0x02C, 0, 0x3F, 6},
		{ 0x220, 26, 0xFC000000, 0x6, 0x060, 0, 0x3F, 6}
	};

	const OtpTableDiscpES3_t reg_220_cat2_ES3[1] = { 
		{ 0x220, 9, 0xFE00, 0x6, 0x008, 0, 0x7F, 7}
	};

	const OtpTableDiscpES3_t reg_234_cat1_ES3[2] = {
	{ 0x234, 18, 0xFC0000, 0x12, 0x02C, 0, 0x3F, 6 },
	{ 0x234, 10, 0xFC00, 0x13, 0x02C, 0, 0x3F, 6 }
	};

	const OtpTableDiscpES3_t reg_23C_cat1_ES3[10] = { 
		{ 0x23C, 19, 0xF80000, 0x16, 0x030, 4, 0x1F0, 5},
		{ 0x23C, 11, 0xF800, 0x6, 0x038, 0, 0x1F, 5},
		{ 0x23C, 11, 0xF800, 0x6, 0x03C, 0, 0x1F, 5},
		{ 0x23C, 11, 0xF800, 0x6, 0x034, 0, 0x1F, 5},
		{ 0x23C, 11, 0xF800, 0xC, 0x004, 16, 0x1F0000, 5},
		{ 0x23C, 11, 0xF800, 0xC, 0x004, 8, 0x1F00, 5},
		{ 0x23C, 11, 0xF800, 0xC, 0x004, 0, 0x1F, 5},
		{ 0x23C, 11, 0xF800, 0xC, 0x020, 0, 0x1F, 5},
		{ 0x23C, 2, 0xFC, 0x1, 0x05C, 16, 0x3F0000, 6},
		{ 0x23C, 25, 0xFE000000, 0x15, 0x044, 0, 0x7F, 7}
	};

	const OtpTableDiscpES3_t reg_240_cat2_ES3[3] = { 
		{ 0x240, 28, 0xF0000000, 0xD, 0x094, 0, 0xF, 4},
		{ 0x240, 16, 0xF0000, 0xE, 0x094, 0, 0xF, 4},
		{ 0x240, 4, 0xF0, 0xF, 0x094, 0, 0xF, 4}
	};

	const OtpTableDiscpES3_t reg_244_cat1_ES3[12] = { 
		{ 0x244, 8, 0xFF00, 0x11, 0x004, 0, 0xFF, 8},
		{ 0x244, 8, 0xFF00, 0x11, 0x00C, 0, 0xFF, 8},
		{ 0x244, 8, 0xFF00, 0x11, 0x014, 0, 0xFF, 8},
		{ 0x244, 8, 0xFF00, 0x11, 0x01C, 0, 0xFF, 8},
		{ 0x244, 8, 0xFF00, 0x12, 0x004, 0, 0xFF, 8},
		{ 0x244, 8, 0xFF00, 0x12, 0x00C, 0, 0xFF, 8},
		{ 0x244, 8, 0xFF00, 0x12, 0x014, 0, 0xFF, 8},
		{ 0x244, 8, 0xFF00, 0x12, 0x01C, 0, 0xFF, 8},
		{ 0x244, 8, 0xFF00, 0x13, 0x004, 0, 0xFF, 8},
		{ 0x244, 8, 0xFF00, 0x13, 0x00C, 0, 0xFF, 8},
		{ 0x244, 8, 0xFF00, 0x13, 0x014, 0, 0xFF, 8},
		{ 0x244, 8, 0xFF00, 0x13, 0x01C, 0, 0xFF, 8}
	};

	const OtpTableDiscpES3_t reg_244_cat2_ES3[1] = { 
		{ 0x244, 24, 0xF000000, 0x10, 0x094, 0, 0xF, 4}
	};

	const OtpTableDiscpES3_t reg_248_cat1_ES3[5] = { 
		{ 0x248, 20, 0xF00000, 0x6, 0x05C, 12, 0xF000, 4},
		{ 0x248, 6, 0xC0, 0x15, 0x01C, 5, 0x60, 2},
		{ 0x248, 4, 0x30, 0x15, 0x008, 5, 0x60, 2},
		{ 0x248, 2, 0xC, 0x15, 0x024, 5, 0x60, 2},
		{ 0x248, 0, 0x3, 0x15, 0x010, 5, 0x60, 2}
	};

	const OtpTableDiscpES3_t reg_248_cat2_ES3[5] = { 
		{ 0x248, 16, 0xF0000, 0x6, 0x05C, 8, 0xF00, 4},
		{ 0x248, 12, 0xF000, 0x6, 0x05C, 4, 0xF0, 4},
		{ 0x248, 8, 0xF00, 0x6, 0x05C, 0, 0xF, 4},
		{ 0x248, 28, 0xF0000000, 0x6, 0x054, 4, 0xF0, 4},
		{ 0x248, 24, 0xF000000, 0x6, 0x054, 0, 0xF, 4}
	};

	const OtpTableDiscpES3_t reg_24C_cat1_ES3[17] = { 

		{ 0x24C, 9, 0xFE00, 0x9, 0x05C, 0, 0x7F, 7},
		{ 0x24C, 3, 0xF8, 0x6, 0x004, 0, 0x1F, 5},
		{ 0x24C, 3, 0xF8, 0x6, 0x010, 0, 0x1F, 5},
		{ 0x24C, 3, 0xF8, 0x6, 0x01C, 0, 0x1F, 5},
		{ 0x24C, 3, 0xF8, 0x6, 0x028, 0, 0x1F, 5},
		{ 0x24C, 3, 0xF8, 0x6, 0x004, 8, 0x1F00, 5},
		{ 0x24C, 3, 0xF8, 0x6, 0x010, 8, 0x1F00, 5},
		{ 0x24C, 3, 0xF8, 0x6, 0x01C, 8, 0x1F00, 5},
		{ 0x24C, 3, 0xF8, 0x6, 0x028, 8, 0x1F00, 5},
		{ 0x24C, 3, 0xF8, 0x6, 0x09C, 0, 0x1F, 5},
		{ 0x24C, 3, 0xF8, 0x6, 0x008, 16, 0x1F0000, 5},
		{ 0x24C, 3, 0xF8, 0x6, 0x014, 16, 0x1F0000, 5},
		{ 0x24C, 3, 0xF8, 0x6, 0x020, 16, 0x1F0000, 5},
		{ 0x24C, 3, 0xF8, 0x6, 0x02C, 16, 0x1F0000, 5},
		{ 0x24C, 3, 0xF8, 0xC, 0x018, 8, 0x1F00, 5},
		{ 0x24C, 3, 0xF8, 0xC, 0x054, 0, 0x1F, 5},
		{ 0x24C, 28, 0xF0000000, 0x11, 0x024, 24, 0xF000000, 4}
	};

	const OtpTableDiscpES3_t reg_24C_cat2_ES3[3] = { 

		{ 0x24C, 24, 0xF000000, 0x11, 0x024, 0, 0xF, 4},
		{ 0x24C, 24, 0xF000000, 0x12, 0x024, 0, 0xF, 4},
		{ 0x24C, 24, 0xF000000, 0x13, 0x024, 0, 0xF, 4}
	};

	const OtpTableDiscpES3_t reg_264_cat1_ES3[4] = { 
		{ 0x264, 3, 0xF8, 0xC, 0x008, 0, 0x1F, 5},
		{ 0x264, 3, 0xF8, 0x0, 0x020, 4, 0x1F0, 5},
		{ 0x264, 3, 0xF8, 0x0, 0x028, 4, 0x1F0, 5},
		{ 0x264, 3, 0xF8, 0x0, 0x02C, 4, 0x1F0, 5}
	};

	const OtpTableDiscpES3_t reg_26C_cat1_ES3[4] = { 
		{ 0x26C, 26, 0xFC000000, 0x15, 0x05C, 0, 0x3F, 6},
		{ 0x26C, 18, 0xFC0000, 0x15, 0x060, 0, 0x3F, 6},
		{ 0x26C, 10, 0xFC00, 0x15, 0x064, 0, 0x3F, 6},
		{ 0x26C, 2, 0xFC, 0x15, 0x068, 0, 0x3F, 6}
	};

	const OtpTableDiscpES3_t reg_270_cat1_ES3[3] = { 
		{ 0x270, 27, 0xF8000000, 0x0, 0x024, 4, 0x1F0, 5} ,
		{ 0x270, 4, 0xF0, 0x12, 0x024, 24, 0xF000000, 4 },
		{ 0x270, 0, 0xF, 0x13, 0x024, 24, 0xF000000, 4 }
	};

	//OTP LUT for storing actual used OTP values
	static uint32_t g_aOtpLUT_ES3[ES3_DEV_OTP_LUT_SIZE + 0x02] = { 0x00 }; // Added 0x01, since Index-0 is Invalid ...
	uint32_t * g_OTPShadowLUT_ES3 = NULL;

	/*
	*  Note that hal_es3_OTP_checkValidIP is only used to make current reference code compatible with OTP disabled samples
	*  The goal is to disable all errors created by trying to access/configure a disabled IP thus allowing for the API to 
	*  complete succesfully for the enabled modules.
	*  This function is used:
	*		- in every SPI write to determine write access
	*		- in Fit test to know which errors cannot be injected
	*		- specially when performing a writeCheck to CC->IP_LEVEL_PON_ENABLE
	*  For a real application no access/configuration should be performed to a disabled IP.
	*/
	DolphinIC_rval_t hal_es3_OTP_checkValidIP(uint32_t mod_add, uint32_t * PON_mask, uint32_t *FIT_mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod00_IpLevelPonEnableUnion_t IpLevelPonEnable;


		//Below we declare an array with every element index matching one module address
		//Not 0 elements correspond to IPs that can be disabled (Coms, LO, Txs & Rxs)
		uint32_t variant_bits[24] = {0,3,1,2,0,0,0,0,0,0,0,0,0,7,8,9,10,4,5,6,0,0,0,0};
		/*Define the power on bits associated with every IP that can be OTP disabled
		* When trying to turn on a disabled IP the SPI readback will be 0, so we need how to mask the readback value
		* Order is: Tx1, Tx2, Tx3, Rx1, Rx2, Rx3, Rx4 [as this matches the bit order in otp for disabled ips]
		*/
		
		uint32_t pon[7] = {0x20000,0x40000,0x80000,0x2000,0x4000,0x8000,0x10000};
		//In the same order as above, bits to mask for the supply FIT
		uint32_t fit_supply[7] = {0x1,0x2,0x4,0x88,0x110,0x220,0x440};
		//In the same order as above, bits to mask for the tx FIT
		uint32_t fit_tx[7] = {0x49249,0x92492,0x124924,0x0,0x0,0x0,0x0};
		//In the same order as above, bits to mask for the rx FIT
		uint32_t fit_rx[7] = {0x0,0x0,0x0,0x1111111,0x2222222,0x4444444,0x8888888};
		uint32_t _pon_mask = 0x0;
		uint32_t _sup_mask = 0x0;
		uint32_t _tx_mask = 0x0;
		uint32_t _rx_mask = 0x0;
		//2D array that holds masks to be applied in case of an RX or TX is PON disabled by the user. Each column represents an RX or TX as above.
		//first row for supply, second for TX and third for RX mask
		//uint32_t userPONMask[3][7] = {0x1}
		

		HAL_GERRCODE_INIT;
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16, &IpLevelPonEnable.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//If the pointer PON_mask is not empty return the full mask to apply when doing a write check to 'CC->IP_LEVEL_PON_ENABL'
		if (PON_mask != NULL){
			for(int i = 3; i<10; i++){
				if ((g_OTPShadowLUT_ES3[0] & 0x1<<i) > 0) _pon_mask |= pon[i-3];
			}
			*PON_mask= ~_pon_mask;
			DbgInfo("PON mask 0x%x\n", ~_pon_mask);
		}

		//If the pointer FIT_mask is not empty return the set of 3 mask (supply, tx & rx) to apply when performing internal FIT
		if (FIT_mask != NULL){
			for(int i = 3; i<10; i++){
				if ((g_OTPShadowLUT_ES3[0] & 0x1<<i) > 0) {
					_sup_mask|=fit_supply[i-3];
					_tx_mask|=fit_tx[i-3];
					_rx_mask|=fit_rx[i-3];
				}
			}
			//repeat the same process to include PON disabled IPs to the FIT mask sets
			for (int i = 13; i<20; i++) {
				if ((IpLevelPonEnable.val_u32 & (0x1 << i)) == 0) {
					if (i < 17) {
						_sup_mask |= fit_supply[i - 10];
						//_tx_mask |= fit_tx[i - 17];
						_rx_mask |= fit_rx[i - 10];
					}
					else
					{
						_sup_mask |= fit_supply[i - 17];
						_tx_mask |= fit_tx[i - 17];
						//_rx_mask |= fit_rx[i - 10];
					}
				}
			}
			DbgInfo("FIT masks 0x%x 0x%x 0x%x\n", _sup_mask, _tx_mask, _rx_mask);
			FIT_mask[0]= _sup_mask;
			FIT_mask[1]= _tx_mask;
			FIT_mask[2]= _rx_mask;
		}

		//Using the above array with an element for each IP module address, determine if the module that is being written
		//is disabled (module can be disabled and OTP says it is) and return an error if so
		if ((variant_bits[mod_add]==0)|(((0x1<<(variant_bits[mod_add]-1)) & g_OTPShadowLUT_ES3[0]) == 0)) return DOLPHINIC_NOERROR;
		else {
			DbgErr("Tried to write to deactivated module 0x%x (%x) \n", mod_add, g_OTPShadowLUT_ES3[0]);
			return DOLPHINIC_EC_IPNOTACTIVATED; //Should be using the define for error assertion but don't want to end the parent function because of this ...
		}
	}

	DolphinIC_rval_t hal_es3_OTP_Load(void)
	{
		
		///* DECLARE LOCAL VARIABLES HERE *///
		uint32_t sum = 0x00;
		uint32_t loop_inx = 0x00;
		uint32_t shadow_inx;
		uint32_t crc32off;
		uint32_t calcu_crc32;

		Nxp_Tef810x_Mod17_OtpStatusUnion_t OTPStatus;

		HAL_GERRCODE_INIT;

		// chk for ready_for_read in otp_status register
		glue_reg_Read(OTP_MODULE_ADDRESS, NXP_TEF810X_MOD17_OTP_STATUS_U16, &OTPStatus.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		if (OTPStatus.bits_st.ReadyForRead == 0x00)
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_INVALIDOTP);

		// Start from Indx 0x01, since Indx 0x00 is invalid ...
		g_OTPShadowLUT_ES3 = &g_aOtpLUT_ES3[0x01];

		// Read all 32 registers of OTP ...
		// Burst Read in Sequential mode ...
		// Max speed of reading OTP is 20MHz
		glue_reg_BurstRead(OTP_MODULE_ADDRESS, NXP_TEF810X_MOD17_OTP_DATA_RD_REG_U16, &g_aOtpLUT_ES3[0x00], ( ES3_DEV_OTP_LUT_SIZE + 0x01 ), false, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		crc32off = OTP_CRC32_COMPU_CRCOFF_ES3;//31(dec)

		g_OTPShadowLUT_ES3[ crc32off - 1 ] = g_OTPShadowLUT_ES3[ crc32off ];

		// For CRC verification, please see UM v0.52, section 2.1.5.5 OTP CRC.
		// OTP uses the IEEE-802.3 CRC32 Ethernet Standard algorithm, this can be replaced by AUTOSAR 32-bit CRC.
		calcu_crc32 = hal_es3_CRC_ComputeCRC32((const void*)&g_OTPShadowLUT_ES3[OTP_CRC32_COMPU_START_OFF_ES3]
											, ( OTP_CRC32_COMPU_LEN_ES3 * sizeof(uint32_t))
											, 0x00 );

		//print out readout OTP values
		for (loop_inx = OTP_CRC32_COMPU_START_OFF_ES3; loop_inx < ( OTP_CRC32_COMPU_START_OFF_ES3 + OTP_CRC32_COMPU_LEN_ES3 + 0x02 ); loop_inx++)
		{
			DbgInfo("0x%x - 0x%x \n",
				(NXP_TEF810X_MOD17_OTP_DATA_RD_REG_U16 + (loop_inx * sizeof(uint32_t)))
				, g_OTPShadowLUT_ES3[loop_inx]);
		}

		if( calcu_crc32 != OTP_CRC32_MAGIC_CONST_ES3 )
		{
			DbgInfo("OTP CRC Chk Failed Act(0x%X) Exp(0x%X) !!!\n", calcu_crc32, OTP_CRC32_MAGIC_CONST_ES3 );
		}
		else
		{
			DbgInfo("OTP CRC Chk OK!!! \n");
		}

		// For Debug ...
		DbgInfo("OTP Content ... \n");
		for (loop_inx = 0x00; loop_inx < ES3_DEV_OTP_EMU_SIZE; loop_inx++)
		{
			shadow_inx = ((g_DefaultEmuValueES3[loop_inx].offset - ES3_DEV_OTP_START_OFFSET) >> 0x02);

			DbgInfo("[IF]Src_off(0x%x), Shd_inx(0x%x), Val(0x%x) \n", g_DefaultEmuValueES3[loop_inx].offset, shadow_inx, g_OTPShadowLUT_ES3[shadow_inx]);

			if ((g_OTPShadowLUT_ES3[shadow_inx] != 0x00) && (g_OTPShadowLUT_ES3[shadow_inx] != 0xdeadbeef))
			{
				// Soc With Valid OTP ...
				sum += g_OTPShadowLUT_ES3[shadow_inx];
				DbgInfo("Real OTP content.. \n");
				DbgInfo("[IF]Src_off(0x%x), Shd_inx(0x%x), Val(0x%x) \n", g_DefaultEmuValueES3[loop_inx].offset, shadow_inx, g_OTPShadowLUT_ES3[shadow_inx]);
			}
			else
			{
				// Soc With In-Valid OTP, Continue with Default or Emulated Value ...
				g_OTPShadowLUT_ES3[shadow_inx] = g_DefaultEmuValueES3[loop_inx].value;
				sum += g_OTPShadowLUT_ES3[shadow_inx];
				DbgInfo("Hardcoded OTP content.. \n");
				DbgInfo("[IF]Src_off(0x%x), Shd_inx(0x%x), Val(0x%x) \n", g_DefaultEmuValueES3[loop_inx].offset, shadow_inx, g_OTPShadowLUT_ES3[shadow_inx]);
			}
		}

		if (sum != 0x00)
			return DOLPHINIC_NOERROR;
		else
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_INVALIDOTP);
	}


	DolphinIC_rval_t hal_es3_OTP_LoadFromGlobal(const OtpTableDiscpES3_t * tbl_base, uint32_t tbl_size, uint32_t IP_PON_Mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint32_t shadow_inx = 0x00;
		uint32_t loop_inx;
		uint32_t reg_val ;
		uint32_t mod_cfg_val ;
		uint32_t read_val ;

		HAL_GERRCODE_INIT;
		
		//array index of corresponding src_off (+1 to compensate first dummy read value)
		shadow_inx = ((tbl_base[0x00].src_off - ES3_DEV_OTP_START_OFFSET) >> 0x02);


		for (loop_inx = 0x00; loop_inx < tbl_size; loop_inx++)
		{
			reg_val = 0x00;
			mod_cfg_val = 0x00;
			read_val = 0x00;

			mod_cfg_val = ((g_OTPShadowLUT_ES3[shadow_inx]) & tbl_base[loop_inx].src_msk) >> tbl_base[loop_inx].src_pos;

			//flip the bits
			mod_cfg_val = hal_es3_bit_flip(mod_cfg_val, tbl_base[loop_inx].n_bits);

			if (hal_es3_CheckUserPONEn(IP_PON_Mask, tbl_base[loop_inx].dst_mod) != DOLPHINIC_EC_IPNOTACTIVATED)
			{
				glue_reg_Read(tbl_base[loop_inx].dst_mod, tbl_base[loop_inx].dst_reg, &reg_val, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				reg_val &= ~(tbl_base[loop_inx].dst_msk);
				reg_val |= (mod_cfg_val << tbl_base[loop_inx].dst_pos);

				glue_reg_Write(tbl_base[loop_inx].dst_mod, tbl_base[loop_inx].dst_reg, reg_val, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				// Data integirty Check ...
				glue_reg_Read(tbl_base[loop_inx].dst_mod, tbl_base[loop_inx].dst_reg, &read_val, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				//DbgErr("OTP_Write_Done -> SrcOff(0x%x), Dest(0x%x::0x%x) Act(0x%x) Exp(0x%x) \n",
				//	tbl_base[0x00].src_off, tbl_base[loop_inx].dst_mod,
				//	tbl_base[loop_inx].dst_reg, (read_val & tbl_base[loop_inx].dst_msk)
				//	, (reg_val & tbl_base[loop_inx].dst_msk));

				if (((reg_val & tbl_base[loop_inx].dst_msk) != (read_val & tbl_base[loop_inx].dst_msk)) && (hal_es3_OTP_checkValidIP(tbl_base[loop_inx].dst_mod, NULL, NULL) == DOLPHINIC_NOERROR))
				{
					DbgErr("Err %s OTP LUT Discp SrcOff(0x%x), Dest(0x%x::0x%x) Act(0x%x) Exp(0x%x) \n",
						__FUNCTION__, tbl_base[0x00].src_off, tbl_base[loop_inx].dst_mod,
						tbl_base[loop_inx].dst_reg, (read_val & tbl_base[loop_inx].dst_msk)
						, (reg_val & tbl_base[loop_inx].dst_msk));
					HAL_GEC_FUNEXIT(DOLPHINIC_EC_CALLFAILED);
				}
			}
		}

		return HAL_GERRCODE;
	}
	

	DolphinIC_rval_t hal_es3_OTP_CompensateOTP(double effFc, bool applyOverFreq) {

		///* DECLARE LOCAL VARIABLES HERE *///
		sampleInfo_t TP;
//		uint16 swCase_token = 0;
		int i;
		int j;

		HAL_GERRCODE_INIT;

		hal_es3_OTP_GetChipInfo(&TP);

		DbgInfo("ES%x - TestProgram_FT V%d.%d \n", TP.maskVersion, TP.tpMajor_ft , TP.tpMinor_ft);
		DbgInfo("ES%x - TestProgram_WT V%d.%d \n", TP.maskVersion, TP.tpMajor_wt, TP.tpMinor_wt );
		DbgInfo("WaferTest %.2d/%.2d/20%.2d \n", TP.wtDay, TP.wtMonth, TP.wtYear);

		if (TP.maskVersion == 0) {
			DbgInfo("This device does not have OTP content, aborting compensation routine! \n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_INVALIDOTP);
			return HAL_GERRCODE;
		}

		if (TP.maskVersion != 3) {
			DbgInfo("This is an ES%x device, OTP compensation will not apply! \n", TP.maskVersion);
		}
		else {

			//Errata v1.0 Notification 4.6 & artf621411
			for (i = 0; i < 3; i++) {
				if (hal_es3_OTP_checkValidIP((0x11 + i), NULL, NULL) != DOLPHINIC_EC_IPNOTACTIVATED){
					for (j = 0; j < 4; j++) {
						hal_es3_OTP_CorrectLOx3Gain((0x11 + i), j, 3, 621411, effFc, applyOverFreq);
					}
				}
			}

			//ES3 sample, only FT'd
			if (TP.tpMajor_wt == 0 && TP.tpMinor_wt == 0) {
				
				//known issue with only FT'd samples. (see: artf577890)
					//correct the temperature sensor limits
				if (hal_es3_OTP_checkValidIP((0x11), NULL, NULL) != DOLPHINIC_EC_IPNOTACTIVATED) hal_es3_OTP_CorrectTempSensor(0x11, 3);
				if (hal_es3_OTP_checkValidIP((0x12), NULL, NULL) != DOLPHINIC_EC_IPNOTACTIVATED) hal_es3_OTP_CorrectTempSensor(0x12, 3);
				if (hal_es3_OTP_checkValidIP((0x13), NULL, NULL) != DOLPHINIC_EC_IPNOTACTIVATED) hal_es3_OTP_CorrectTempSensor(0x13, 3);
				hal_es3_OTP_CorrectTempSensor(0x06, 3);
			}

			if (TP.tpMajor_ft == 4 && TP.tpMinor_ft < 21 &&
				TP.tpMajor_wt == 4 && TP.tpMinor_wt == 0) {

				//known issue with early
				//correct the LOx3 gain. artf581505
				for (i = 0; i < 3; i++) {
					if (hal_es3_OTP_checkValidIP((0x11 + i), NULL, NULL) != DOLPHINIC_EC_IPNOTACTIVATED){
						for (j = 0; j < 4; j++) {
							hal_es3_OTP_CorrectLOx3Gain((0x11 + i), j, 3, 581505, effFc, applyOverFreq);
						}
					}
				}
			}

		

		}

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_OTP_CorrectTempSensor(uint16_t moduleID, uint16_t offset) {
		Nxp_Tef810x_Mod11_TsSelUnion_t TsSel;
		Nxp_Tef810x_Mod06_FuncsafeMonTemperatureVcoUnion_t FuncsafeMonTemperatureVco;

		HAL_GERRCODE_INIT;

		
		if (moduleID != 0x06) {
			glue_reg_Read(moduleID, NXP_TEF810X_MOD11_TS_SEL_U16, &TsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			TsSel.bits_st.TsSelSpi = TsSel.bits_st.TsSelSpi + offset;
			glue_reg_WriteCheck(moduleID, NXP_TEF810X_MOD11_TS_SEL_U16, TsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		else {		
			glue_reg_Read(moduleID, NXP_TEF810X_MOD06_FUNCSAFE_MON_TEMPERATURE_VCO_U16, &FuncsafeMonTemperatureVco.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			FuncsafeMonTemperatureVco.bits_st.CtlTempSensorMaxTempThresholdSelSpi =
				FuncsafeMonTemperatureVco.bits_st.CtlTempSensorMaxTempThresholdSelSpi + offset;
			glue_reg_WriteCheck(moduleID, NXP_TEF810X_MOD06_FUNCSAFE_MON_TEMPERATURE_VCO_U16, FuncsafeMonTemperatureVco.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		}
		return HAL_GERRCODE;

	}

	DolphinIC_rval_t hal_es3_OTP_CorrectLOx3Gain(uint16_t moduleID, uint16_t TXprofile, uint16_t offset, uint32_t artfID, double effFc, bool applyOverFreq) {

		Nxp_Tef810x_Mod11_GLox3GainProfileUnion_t GLox3GainProfile0;
		uint8_t ptat_val = 0x00;
		uint8_t bg_val = 0x0;
		uint32_t OTP_244 = g_OTPShadowLUT_ES3[17]; 		//Hardcoded OTP values for address 244 (TX Bias)
		HAL_GERRCODE_INIT;
		
		if (hal_es3_OTP_checkValidIP(moduleID, NULL, NULL) == DOLPHINIC_EC_IPNOTACTIVATED) return HAL_GERRCODE;

		glue_reg_Read(moduleID, NXP_TEF810X_MOD11_G_LOX3_GAIN_PROFILE0_U16 + (TXprofile*8), &GLox3GainProfile0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		ptat_val = ((GLox3GainProfile0.bits_st.GLox3GainProfile0 & 0xF0) >> 4);
		bg_val = ((GLox3GainProfile0.bits_st.GLox3GainProfile0 & 0xF));
		switch(artfID)
		{
			//fix for artf581505
		case 581505:
		
			
			if (ptat_val < offset) //If the ptat_val is smaller than offset (3), then set the gain 0x03			
				GLox3GainProfile0.bits_st.GLox3GainProfile0 = 0x03;
			else {
				//otherwise, substract offset from ptat and set bg = (new)ptat + 3
				GLox3GainProfile0.bits_st.GLox3GainProfile0 = ((ptat_val - offset) << 4) + ptat_val;
			}
			break;
		
			//fix for artf621411
		case 621411:


			OTP_244 = (OTP_244 & 0x0000FF00) >> 8;
			//flip bits
			OTP_244 = hal_es3_bit_flip(OTP_244, 8);  //LSB
			//add +3 for each nibble when fc is above 79 GHz
			if(applyOverFreq == true || effFc > 79.0e9f)
			{
				bg_val = ((OTP_244 & 0x0F) >> 0) + offset;
				ptat_val = ((OTP_244 & 0xF0) >> 4) + offset;

				if (ptat_val > 0xF || bg_val > 0xF) {
					HAL_GEC_FUNEXIT(DOLPHINIC_EC_INPUTOUTOFRANGE);
				}
				else {
					GLox3GainProfile0.bits_st.GLox3GainProfile0 = (ptat_val << 4) + bg_val;
				}
				
			}
			//restore/keep original OTP values for fc < 79 GHz
			else {

				GLox3GainProfile0.bits_st.GLox3GainProfile0 = OTP_244;
			}

			break;

		default:
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_INPUTOUTOFRANGE);
			break;

		}
		glue_reg_WriteCheck(moduleID, NXP_TEF810X_MOD11_G_LOX3_GAIN_PROFILE0_U16 + (TXprofile * 8), GLox3GainProfile0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_OTP_GetChipInfo(sampleInfo_t *pChipInfo)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		HAL_GERRCODE_INIT;

		if (g_OTPShadowLUT_ES3[5] == 0x1234ABCD)
		{
			DbgInfo("Chip OTP is not valid, cannot tell which mask version it is!");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_INVALIDOTP);
		}
		else
		{
			//getting info from OTP reg 0x210
			pChipInfo->maskVersion = (g_OTPShadowLUT_ES3[4] & 0x3C000000) >> 26;
			//getting info from OTP reg 0x214
			pChipInfo->tpMinor_ft = (g_OTPShadowLUT_ES3[5] & 0x0000FE00) >> 9;
			pChipInfo->tpMajor_ft = (g_OTPShadowLUT_ES3[5] & 0x000001FC) >> 2;
			pChipInfo->tpMajor_wt = (g_OTPShadowLUT_ES3[5] & 0x01FC0000) >> 18;
			pChipInfo->tpMinor_wt = (g_OTPShadowLUT_ES3[5] & 0xFE000000) >> 25;
			//getting info from OTP reg 0x20C
			pChipInfo->wtDay = (g_OTPShadowLUT_ES3[3] & 0x0000F800) >> 11;
			pChipInfo->wtMonth = (g_OTPShadowLUT_ES3[3] & 0x00000780) >> 7;
			pChipInfo->wtYear = (g_OTPShadowLUT_ES3[3] & 0x0000007C) >> 2;

			return HAL_GERRCODE;
		}
	}


#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif