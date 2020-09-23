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

/*
*
* @file dolphinIC.h
*
* @ver v5.3.0  
*
* @author
*
* @date 
*
* @brief DolphinIC library header
*
******************************************************************************/

/**
@file dolphinIC.h

@brief dolphinIC API group header file.

This API Group deals only with Dolphin chip settings.
API functions in this group always start with "chip_"

## Naming Convention

chip_(ModuleName)_(FunctionName)(parameter list)

For example:

DolphinIC_rval_t chip_ISM_Init(int32_t mode, uint8_t deci);

## Dolphin Generic Error Codes

For function return, the type DolphinIC_rval_t is used, it is equivalent to int32_t.
For details of the error codes, @see dolphin_errcodes.h

## Time and frequency units

For timing, us (micro seconds) is used as unit
For frequency, Hz (herts) is used as unit.
So chirp slope will have a unit of hz/us

For more information, see the Dolphin Datasheet, User Manual and Application Note.

## General Sequence of API Call in Normal Application

*/

#ifndef DOLPHINIC_H
#define DOLPHINIC_H
//#define SB_BINARYSEARCH_ENABLE

/******************************************************************************
* INCLUDES
*****************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <dolphin_errcodes.h>
#include <dolphin_cfg.h>

#ifdef __cplusplus
extern "C"
{
#endif

	enum dolphin_ExtPinID
	{
		DOLPHIN_EXTPIO_CHIRPSTART 	= 0x100,
		DOLPHIN_EXTPO_READYINT 		= 0x200,
		DOLPHIN_EXTPO_ERRORN 		= 0x300,
		DOLPHIN_EXTPO_ERRORRESET 	= 0x400,
		DOLPHIN_PI_TX1PS 			= 0x500,
		DOLPHIN_PI_TX2PS 			= 0x600,
		DOLPHIN_PI_TX3PS 			= 0x700
	};

	typedef int32_t dolphin_ExtPinID_t;

	// global variable to store current chip mask version
	extern uint8_t chipMaskVersion;

	/**
	@brief This API get the chip mask version using ModuleID register in CC.

	MaskVersion = 1 for ES1
	2 for ES2
	3 for ES3

	@param[out] MaskVersion The chip mask version

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CC_GetMaskVersion(uint8_t *MaskVersion);

	/**
	@brief This API initializes the DolphinIC based on Functional Safety Manual start-up sequence steps.

	The steps are the same as specified in FSM.

	@see Functional Safety Manual v2.1 section 6.9.3 - Start-up Action
	@param[in] mode Interface mode, 1-CSI2, 2-LVDS, 3-CIF*MFIO, 4(reserved), 5-Master(no data interface), 6-Slave(CSI-2), 7-Slave(LVDS)
	@param[in] deci Decimation factor, 1, 2, 4, 8, 16
	@param[in] IP_PON_Mask is used to mark the IPs that will be enabled by PON (in CC). Bit-order follows the IP_LEVEL_PIN_ENABLE register in CC. Active high.

	@return DolphinIC_rval_t
	*/
	// DolphinIC_rval_t chip_ISM_Init(int32_t mode, uint8_t deci);
	DolphinIC_rval_t chip_ISM_Init(int32_t mode, uint8_t deci, uint32_t IP_PON_Mask);

	/**
	@brief This API calibrates the CAFC amplitude to a desire value

	This API can be called at any time after initialization of the Dolphin and CAFC is done.
	This API assumes that coarse tunning is configured and subband is selected
	(ONLY FOR VALIDATION!)This API makes use of ATB and assumes that LDO are properly powered on and initialized.

	@param[in] profile The profile number that the amplitude will be calibrated for.
	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CAFC_CalibrateAmplitude(uint8_t profile);
	/**
	@brief This API calibrates the CAFC amplitude to a desire value

		This API is called as a recovery function for fault injection testing

		@param[in] profile The profile number that the amplitude will be calibrated for.
		@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CAFC_CalibrateAmplitude_InjectRecovery(uint8_t profile);

	/**
	@brief This API Enables VCOs

	Before calling this API, all IPs need to be configured correctly except the Serializer.
	That means:

	- chip_ISM_Init
	- loadOrCalVCOFreq
	- chip_TE_ChirpTrigMode
	- chip_TE_StaticConfig
	- chip_Chirp_Program
	- chip_LO_Control
	- chip_TX_Control
	- chip_RX_ProfileConfig

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CAFC_EnableVCO();

	/**
	@brief This API initialize the ATB (Analog Test Bus), making it ready for internal signal measurement.

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_ATB_Init();

	/**
	@brief This API is used to get temperature readout via BISTADC. It also calibrates the BISTADCs based on OTP value

	Before calling this API, LDO for ATB should be configured and enabled.
	See hal_es3_atb_Init( void );

	Remark: Chirp Engine does not have connection to ATB2, so Chirp + ATB2 combination is not valid.
	@return float temperature readout in C degrees
	@param[in] ATB to be used (1 or 2)
	@param[in] IP to be used (0x06: Chirp \ 0x11: TX1 \ 0x12: TX2 \ 0x13: TX3 )
	*/
	float chip_ATB_ReadTemp(uint8_t _chooseATB, uint16_t _chooseIP);

	/**
	@brief This API does Enable & Disable probing of Single SPI write cmds to file

	## API takes absoulte path (null-terminated string) of dump file as argument, open the file
	handle and probe all single spi write cmds in the syntax "spi_wr <mod_add in hex> <reg_add in hex> <data in hex>".
	Probing is diabled by calling the same API with NULL argument.

	@return DolphinIC_rval_t
	@param[in] pv_arg1 void * pointing to null terminated string of Absolute path of dump file. NULL is passed to disable probing.
	*/
	DolphinIC_rval_t chip_reg_ProbeSPIWrite( void * pv_arg1 );

	/**
	@brief This API does a single SPI write to Dolphin chip registers

	## General description of Dolphin SPI access functions

	Dolphin API offers 6 different SPI access functions. Single write and read functions are the most basic ones. It also offers burst write/read, write and at the same time read and one fully customizable SPI access function for advanced application.

	@see Dolphin Datasheet - Chapter SPI Control Interface
	@return DolphinIC_rval_t
	@param[in] ModuleAddress Module address in Dolphin
	@param[in] RegAddress Register address in the specific module
	@param[in] WriteData The data to be written to the register
	@param[out] ReturnedData Returned data (first 4 bytes) from MISO line. In this function the C/S bit is always set to 0 meaning the command and register address of current write action are returned.
	*/
	DolphinIC_rval_t chip_reg_Write(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t WriteData, uint32_t *ReturnedData);


	/**
	@brief Write multiple data (Burst Write) to Dolphin registers.

	## SR_Mode

	Dolphin allows burst access to its internal registers by extending the SPI cycles by a multiple of 32 cycles for each additional access. Burst write is restricted within the same module. You may use SR_Mode to control to write to the same register multiple times or write sequentially to many registers in a row within one module.

	When set to false, (S)equential mode is chosen, Dolphin automatically increases the register address internally. When set to true, (R)epeated mode is chosen. The IC writes to the same register.

	@see Dolphin Datasheet - Chapter SPI Control Interface
	@return DolphinIC_rval_t
	@param[in] ModuleAddress Module address in Dolphin.
	@param[in] RegAddress Register address, the first register address that the burst write is writing to.
	@param[in] WriteData A pointer to the data array which will be burst written.
	@param[in] NumWords Number of data words.
	@param[in] SR_Mode Sequential or Repeated bit. See descriptions above.
	@param[out] ReturnedData Returned data (first 4 bytes) from MISO line. In this function the C/S bit is always set to 0 meaning the command and address of the current write action is returned in bytes S2 & S3
	*/
	DolphinIC_rval_t chip_reg_BurstWrite(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *WriteData, uint8_t NumWords, bool SR_Mode, uint32_t *ReturnedData);


	/**
	@brief This API does a single SPI read from the Dolphin register

	## General description of Dolphin SPI access functions

	Dolphin API offers 6 different SPI access functions. Single write and read functions are the most basic ones. It also offers burst write/read, write and at the same time read and one fully customizable SPI access function for advanced application.

	@see Dolphin Datasheet - Chapter SPI Control Interface
	@return DolphinIC_rval_t
	@param[in] ModuleAddress Module address in Dolphin
	@param[in] RegAddress Register address in the specific module
	@param[out] ReadData A pointer to space where the read data needs to be stored.
	@param[out] ReturnedData Returned data (first 4 bytes) from MISO line. This is a read action, so the command and register address received over the MOSI line is returned in byte S2 and S3.
	*/
	DolphinIC_rval_t chip_reg_Read(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *ReadData, uint32_t *ReturnedData);


	/**
	@brief Read multiple data (Burst Read) from Dolphin registers.

	@see Dolphin Datasheet - Chapter SPI Control Interface
	@return DolphinIC_rval_t
	@param[in] ModuleAddress Module address in Dolphin
	@param[in] RegAddress Register address, the first register address that the burst read is reading from.
	@param[out] ReadData A pointer to the data array where the read data needs to be stored.
	@param[in] NumWords Number of data words to be read
	@param[in] SR_Mode Sequential or Repeated bit. When set to false, (S)equential mode is chosen, Dolphin automatically increases the register address internally. When set to true, (R)epeated mode is chosen. The IC reads from the same register.
	@param[out] ReturnedData This is a read action, so the command and register address received over the MOSI line is returned in byte S2 and S3.
	*/
	DolphinIC_rval_t chip_reg_BurstRead(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *ReadData, uint8_t NumWords, bool SR_Mode, uint32_t *ReturnedData);


	/**
	@brief Write data to a register and at the same time read data back from MISO line.

	## CS_Mode
	Dolphin provides an option to read back the data over MISO when the current access is write. Two options available based on the bit setting CS_Mode:
	false(0): Current register access: the existing content of the current register accessed is send over the MISO interface
	true(1): Stored register access: the content of the last written register over SPI interface is send over the MISO interface

	## ReturnedData

	If set to Current access (0) then the command and address of the current write action is returned in bytes S2 & S3. If set to Stored access (1), then the command and address of the last write action is returned in bytes S2 & S3.

	@see Dolphin Datasheet - Chapter SPI Control Interface
	@return DolphinIC_rval_t
	@param[in] ModuleAddress Module address in Dolphin
	@param[in] RegAddress Register address to be written.
	@param[in] WriteData The data to be written.
	@param[out] ReadData A pointer to space where the read data needs to be stored.
	@param[in] CS_Mode Current or Stored bit. See descriptions above.
	@param[out] ReturnedData This is a write action, so the returned data depends on the CS_Mode setting. See descriptions above.
	*/
	DolphinIC_rval_t chip_reg_WriteRead(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t WriteData, uint32_t *ReadData, bool CS_Mode, uint32_t *ReturnedData);


	/**
	@brief Burst Write Read provides the fullest customizable SPI write access.

	## CS_Mode
	Dolphin provides an option to read back the data over MISO when the current access is write. Two options available based on the bit setting CS_Mode:
	false(0): Current register access: the existing content of the current register accessed is send over the MISO interface
	true(1): Stored register access: the content of the last written register over SPI interface is send over the MISO interface

	## SR_Mode

	Dolphin allows burst access to its internal registers by extending the SPI cycles by a multiple of 32 cycles for each additional access. Burst write is restricted within the same module. You may use SR_Mode to control to write to the same register multiple times or write sequentially to many registers in a row within one module.

	When set to false, (S)equential mode is chosen, Dolphin automatically increases the register address internally. When set to true, (R)epeated mode is chosen. The IC writes to the same register.

	## ReturnedData

	If set to Current access (0) then the command and address of the current write action is returned in bytes S2 & S3. If set to Stored access (1), then the command and address of the last write action is returned in bytes S2 & S3.

	@see Dolphin Datasheet - Chapter SPI Control Interface
	@return DolphinIC_rval_t
	@param[in] ModuleAddress Module address in Dolphin
	@param[in] RegAddress Register address to be written.
	@param[in] WriteData The data to be written.
	@param[out] ReadData A pointer to space where the read data needs to be stored.
	@param[in] NumWords Number of data words to be written and read.
	@param[in] CS_Mode Current or Stored bit. See descriptions above.
	@param[in] SR_Mode Sequential or Repeated bit. See descriptions above.
	@param[in] loopBack
	@param[out] ReturnedData This is a write action, so the returned data depends on the CS_Mode setting. See descriptions above.
	*/
	DolphinIC_rval_t chip_reg_BurstWriteRead(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *WriteData, uint32_t *ReadData, uint8_t NumWords, bool CS_Mode, bool SR_Mode, bool LoopBack, uint32_t *ReturnedData);


	/**
	@brief This API enables/disables clock for selected IPs from Dolphin Central Control.

	## modlist

	Use modlist to choose the IP you want to control. Select IP(s) by setting corresponding bit to 1.

	Use Enable to control enable or disable the IPs' clock in modlist.

	This API will not influence the IPs that are not selected in modlist.

	@see CC_ClkEn_Reg
	@param[in] Enable Choose whether to enable or disable the selected IPs.
	@param[in] modlist Module list, select the IP(s) which you want to operate.
	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CC_IPClockEnable(bool Enable, uint32_t modlist);


	/**
	@brief This API powers on/off the selected IPs from Dolphin Central Control.

	## modlist

	Use modlist to choose the IP you want to control. Select IP(s) by setting corresponding bit to 1.

	Use Enable to control the power of the IPs in modlist.

	This API will not influence the IPs that are not selected in modlist.

	@see CC_ClkEn_Reg
	@param[in] PowerOn Choose whether to power on or off the selected IPs.
	@param[in] modlist Module list, select the IP(s) which you want to operate.
	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CC_IPPowerOn(bool PowerOn, uint32_t modlist);

	/**
	@brief This API puts selected IPs out of/into reset status from Dolphin Central Control.

	## modlist

	Use modlist to choose the IP you want to control. Select IP(s) by setting corresponding bit to 1.

	Use OutOfReset to control the reset status of the IPs in modlist.

	This API will not influence the IPs that are not selected in modlist.

	@see CC_ClkEn_Reg
	@param[in] OutOfReset Choose whether you want to put the selected IPs out of reset or in reset status.
	@param[in] modlist Module list, select the IP(s) which you want to operate.
	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CC_IPReset(bool OutOfReset, uint32_t modlist);

	/**
	@brief This API puts selected IPs out of/into functional reset status from Dolphin Central Control.

	## modlist

	Use modlist to choose the IP you want to control. Select IP(s) by setting corresponding bit to 1.

	Use OutOfReset to control the functional reset status of the IPs in modlist.

	This API will not influence the IPs that are not selected in modlist.

	@see CC_ClkEn_Reg
	@param[in] OutOfReset Choose whether you want to put the selected IPs out of functional reset or in functional reset status.
	@param[in] modlist Module list, select the IP(s) which you want to operate.
	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CC_IPFuncReset(bool OutOfReset, uint32_t modlist);

	/**
	@brief This API lets the user to choose the digital data interface.

	# Bit clock frequency

	- LVDS bit clock:
	- CIF data clock:
	- CSI2 bit clock:

	@see User Manual about bit clock and data clocks in data interfaces.
	@param[in] mode Interface mode,  CSI-2 = 0x1; LVDS = 0x2; CIF = 0x3
	@param[in] init_out_clk_freq,  Serializer out bit clk frequency @ init,( eg 240e6, 40e6 ). Cfg Master_idiv in serializer.
	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CC_SerializerInterfaceSet(int32_t mode, float init_out_clk_freq);

	/**
	@brief This API lets the user set the device in dynamic power mode.

	All txs, rxs and serializer groups are treated as 1.

	@param[in] mode, Dynamic Power Mode,  None = 0x0; Dynamic Power Mode Per Sequence = 0x1; Dynamic Power Mode Per Chirp = 0x2
	@param[in] setTx, All Txs are set in dynamic power mode. Ignored if mode is set to 'None'
	@param[in] setRx, All Rxs are set in dynamic power mode. Ignored if mode is set to 'None'
	@param[in] setLo, All LO is set in dynamic power mode. Ignored if mode is set to 'None'
	@param[in] setAdc, ADCs are set in dynamic power mode. Ignored if mode is set to 'None'
	@param[in] setChirp, Chirp is set in dynamic power mode. Ignored if mode is set to 'None'
	@param[in] setSerializer, Serializer clock and power are set in dynamic power mode. Do not use for CSI2 Ignored if mode is set to 'None'
	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CC_SetDynamicPowerMode(uint32_t mode, bool setTx, bool setRx, bool setLo, bool setAdc, bool setChirp, bool setSerializer);

	/**
	@brief This API recalibrate the four ADCs in Dolphin chip.

	User doesn't need to call this function after ADC power on since ADC will automatically calibrate itself after power on.

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_ADC_Recalibrate(void);

	/**
	@brief This API initialize the Master Clock IP in Dolphin.

	Only typical values are programmed to the chip.

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_MCLK_Config();

	/**
	@brief This API recalibrates the master clock.

	Use this function when in conditions where Master Clock may be out of lock. E.g. temperature changes and current sudden changes.

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_MCLK_Recalibrate(void);

	/**
	@brief This API configures non-profile specific settings in Timing Engine

	## Non-profile specific Timing Engine Registers

	Non-profile specific settings are configured once and used for all profiles.

	- Number of chirps per sequence
	- Interval between sequences
	- Jumpback time
	- Profile sequencing mode
	- Profile stay count
	- Profile reset enable

	Once set, these settings are all the same to all 4 profiles in Timing Engine.

	## Sequence interval (SeqInterval)

	A timer to control the gap between chirp sequence (system cycle).
	From Dolphin perspective a system cycle consists of data acquisition followed by IDLE time (data processing at MCU). The duty cycle between acquisition and idle time can be a max up to 70%. Using this timer, this can be enforced. This means before expiry of this timer, a new chirp trigger will not be entertained by the Timing engine.

	## profSelect

	This input parameter decides the sequence of using different profiles in a chirp sequence.
	- 0x00: Selects Prof-0
	- 0x01: Selects Prof-1
	- 0x02: Selects Prof-2
	- 0x03: Selects Prof-3
	- 0x04: Selects Prof-0-1
	- 0x05: Selects Prof-0-1-2
	- 0x06: Selects Prof-0-1-2-3

	## ProfileStayCnt

	This input parameter determines how many times one profile will repeat in a profile sequence
	For example, if 2 is used, and profselect is 5, then the profiles used in a chirp sequence will be:
	00-11-22-00-11-22-......

	User is responsible to use valid values as inputs! No boundary check is applied in the API.

	@param[in] NumChirp Number of chirps in a chirp sequence. Valid input:1-65534 (advise below 4096)
	@param[in] SeqInterval Time interval between chirp sequences. Min is 0.025us(1cc @40MHz)
	@param[in] tJumpback Jumpback period. Min is 0.025us(1cc @40MHz)
	@param[in] profSelect Profile sequence mode select
	@param[in] profileStayCnt Profile repeat counts in a specific profile sequence that is set by profSelect
	@param[in] ProfileResetEn Enable profile sequence reset at the end of a chirp sequence.
	@param[in] PONDelay Power on delay, delay before first chirp for stabilizing the analog circuit.
	@param[in] ISMDelay Delay for enable ISM
	@param[in] TXPonGroupDelay Group power on delay for all TXs.
	@param[in] RXPonGroupDelay Group power on delay for all RXs.
	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_TE_StaticConfig(uint16_t NumChirp, float SeqInterval, float tJumpback, int32_t profSelect, uint32_t profileStayCnt, bool ProfileResetEn, float PONDelay, float ISMDelay, float TXPonGroupDelay, float RXPonGroupDelay);

	/**
	@brief This API configures profile specific settings in Timing Engine

	This API is integrated into chip_Chirp_Program, you may not need to call this API directly.
	You can use this API to create your own advanced applications.

	## Profile specific Timing Engine Registers

	These settings need to be set for each profile.

	- Dwell time
	- Settle time
	- Number of samples
	- Decimation factor
	- Chirp period
	- Bipolar phase shift in Tx channels
	- Tx fast switch control
	- Tx active (DC power on)
	- RX active (DC power on)

	There settings are only effective to the profile that is being configured specified by ProfileNum.

	User is responsible to use valid values as inputs! No boundary check is applied in the API.

	@param[in] ProfileNum Profile number. Valid input: 0-3
	@param[in] DwellTime Dwell time. Valid input: 0.05us-102.35us (12bit, min allowed: 0x02*25ns, max allowed 0xFFE * 25ns)
	@param[in] SettleTime settle time. Valid input: 0.025us-102.35us
	@param[in] NumSamples Number of samples in a chirp. Valid input: 1-65535
	@param[in] Decimation Decimation factor. Valid input: 1, 2, 4, 8, 16
	@param[in] PDCBWWide Choose wideband mode decimation filter or narrowband mode. See datasheet for filter characteristics.
	@param[in] ChirpPeriod Chirp period (=Dwell time + Settle time + sampling time + Jumpback time + Reset time). Valid input: 0us - 104857.575us (22bit uint * 25ns)
	@param[in] BPSControl Bipolar phase shift, true: enable BPS for that channel.
	@param[in] TxSW Tx channel transmission switch, true: switch is close, transmission is on.
	@param[in] TxPON TX DC power on
	@param[in] RxPON RX DC power on

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_TE_ProfileConfig(int ProfileNum, float DwellTime, float SettleTime, uint16_t NumSamples, uint8_t Decimation, bool PDCBWWide, float ChirpPeriod, bool BPSControl[3], bool TxSW[3], bool TxPON[3], bool RxPON[4]);

	/**
	@brief This API configures the chirp trigger behavior

	By default, Dolphin is triggered by a SPI write to chirp_global_control register. However, Dolphin can be triggered by external signal (where chirp_start pin is used as input)

	## Ready interrupt mode

	- 0: ready interrupt at end of a sequence (standard use case). The MCU need memory to store a complete chirp sequence data in its buffer and wait for ready Interrupt to start processing data
	- 1: Interrupt at end of expiry of the chirp_sequence_interval_timer (radar system cycle).. IF chirp sequence interval is less than data acquisition time, then do not use this option
	- 2: Interrupt at end of every chirp (typically useful in power save mode or systems interested in real time processing or systems with less memory. Process the received data as it is being received)

	## CSI2 Frame Mode

	In CSI2 mode, a ready interrupt form TE may not be available at interface level. In this case a frame interrupt from CSI2 RX(should be TX here?) can be used by the micro controller.
	USe model is similar to the ready_int.

	- 0: CSI2 frame deactivation at end of a sequence.
	- 1: Reserved
	- 2: CSI2 frame deactivation at end of every chirp

	When using other interfaces, this parameter has no effects.

	## Chirp Start signal output mode (ChirpStartOnChirpLevel)

	This parameter has no effects when using external trigger mode.

	## External trigger

	By default, Dolphin is triggered by SPI write to register, however, Dolphin can also be triggered by external signal. When UseExtTrigger is true, chirp_start pin will be used as input to trigger the dolphin

	- Asynchronous chirp start trigger (chirp start is coming from and asynchronous source  such as MCU with an independent clock)
	- Synchronous chirp start trigger. Chirp start is coming from another Dolphin or from a MCU using Dolphin 40 MHz clock as a source to drive chirp_start)

	@param[in] ReadyIntMode Ready interrupt pin mode, see above descriptions.
	@param[in] CSI2FrameMode See above descriptions
	@param{in] ChirpPowerMode false: DC supply powered on at start of a chirp (along with chirp_start) sequence and remain on till end of sequence; true: DC supply is controlled at individual chirp level.
	@param[in] ChirpStartToggleOnChirpLevel true:chirp start signal action on individual chirp; false:chirp start action on whole chirp sequence.
	@param[in] SyncExtTrig true: Synchronous external chirp_start as trigger; false: Async external chirp_start trigger
	@param[in] UseExtTrigger true: use external trigger from MCU or another dolphin; false: SPI trigger.

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_TE_ChirpTrigMode(uint8_t ReadyIntMode, uint8_t CSI2FrameMode, bool ChirpPowerMode, bool ChirpStartToggleOnChirpLevel, bool SyncExtTrig, bool UseExtTrigger);

	/**
	@brief This API triggers one chirp sequence

	Call this API after all settings are done and chip powered up. This should be the last step in configuring Dolphin chip. After this, the data capture process can be started.

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_TE_ChirpStart(void);

	void chip_TE_WaitForReady(void);
	/**
	@brief This API load profiles across modules

	@param[in] profID Profile number 0-3

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_TE_LoadProfile(uint8_t profID);

	/**
	@brief This API accept time/frequency related inputs and translate them into Sweep Control settings.

	# Function Description

	This API is integrated into chip_Chirp_Program, you may not need to call this API directly.
	You can use this API to create your own advanced applications.

	Sweep Control controls the chirp generation and reset phase by controlling the divider value of the chirp PLL. User input will be translated and programmed to profile-specific registers.

	# Profile specific registers in Sweep Control

	- N_START_RF_PROFILEx
	- DN_CHIRP_RF_PROFILEx
	- N_STEP_CHIRP_RF_PROFILEx
	- DN_RESET_RF_PROFILEx
	- N_STEP_RESET_RF_PROFILEx
	- DIV_UPDATE_RF_PROFILEx

	x=0~3

	fStart and usedBW can be calculated using chip_CAFC_SubbandSelect or chip_CAFC_SubBandSelectBinarySearch

	@see chip_CTRL_SubBandSelect
	@see chip_CAFC_SubBandSelectBinarySearch

	@param[in] ProfileNum Profile number to be programmed
	@param[in] fStart The start frequency of the chirp, Hz
	@param[in] usedBW Occupied bandwidth including the BW consumed during tSettle and tJumpback, Hz
	@param[in] tSettle Settleing time, us
	@param[in] tSample Sampleing time, us
	@param[in] tJumpback Jumpback time, us
	@param[in] tReset Reset time, us
	@param[in] downChirp whether to use downchirp or upchirp

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_SC_ProfileConfig(int ProfileNum, float fStart, float usedBW, float tSettle, float tSample, float tJumpback, float tReset, bool downChirp);



	/**
	@brief This API configures the profile specific settings for Chirp AFC IP.

	This API is integrated into chip_Chirp_Program, you may not need to call this API directly.
	You can use this API to create your own advanced applications.

	## Profile specific settings for Chirp AFC

	- FILTER_PAR_REGISTER_PROFILE0
	- FILTER_REGISTER_PROFILE0
	- VCO_REGISTER_PROFILE0

	## Registers dependent on chirp PLL loop BW

	The following registers are also dependent on the loop BW, however, they are not part of the profile based registers.
	(This might be improved in next generation IC)

	- CP_REGISTER
	- BIAS_BLOCK_REGISTER

	The selection of relevant settings is based on 2 LUTs, you may find them in the User Manual. Other settings might also work well but the phase noise performance is not guaranteed.

	This function is not applicable for advanced chirp waveforms, e.g chirp stitching.

	@param[in] ProfileNum Profile number, 0-3
	@param[in] narrowBand Whether to use narrow band or wide band.
	@param[in] downChirp Whether to use downchirp or upchirp
	@param[in] subBand subband to use, 0-127
	@param[in] loopBW Chirp PLL loop bandwidth to use, 300kHz-1500kHz, step 50kHz
	@param[in] usedBW Total used bandwidth including tSettle and tJumpback
	@param[in] tSample sampling time.
	@param[in] tJumpback Jumpback time.
	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CAFC_ProfileConfig(int ProfileNum, bool narrowBand, bool downChirp, int subband, float loopBW, float usedBW, double effFc, float tSettle, float tSample, float tJumpback);

	/**
	@brief This API measures the chirp PLL output frequency (in 77GHz range)

	## IMPORTANT: This API is destructive to register settings.

	This API opens the PLL loop by disconnecting the loop filter. The frequency is measured by the frequency counter in the Chirp PLL.

	To have the full frequency table measured, you may use the non-destructive API chip_CAFC_VCOFreqCalibrate.

	@param[in] subband The subband to be measured.
	@param[in] lowerBound Choose if the lower boundary or the higher boundary needs to be measured.
	@param[in] narrowBand Choose if to use the narrow bands or the wide bands in the chirp VCO.
	@param[inout] freqMeas Measured frequency in 77GHz, unit:Hz.
	@param[in] waitPeriod Set wait time for frequency measurment result SPI read (in the wait loop)

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CAFC_VCOFreqMeasure(int subband, bool lowerBound, bool narrowBand, float *freqMeas, unsigned int waitPeriod, uint8_t iVCOFineOTP76G);

	/**
	@brief This API measures chosen subband frequencies and stores them in the corresponding location of VCO table global variable.

	Before using this API, the chip needs to be configured and powered-up.

	This API is non-destructive. After the execution, the settings in Chirp AFC IP will be restored to those before execution.

	## Example

	startSB = 0;
	numPoints = 5;
	Subbands to be calibrated are 0,1,2,3,4 (in total 5);

	startSB = 9;
	numPoints = -5;
	Subbands to be calibrated are 9 8 7 6 5 (in total 5);

	@see chip_CAFC_GetVCOTable
	@see chip_CAFC_SetVCOTable
	@param[in] narrowBand Choose if to measure all subbands in narrow bands or wide bands.
	@param[in] startSB The subband to start to calibrate
	@param[in] numPoints The total number of frequency to be calibrated (including the point startSB). Positive value means to the increasing direction, negative value means to the decreasing direction.
	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CAFC_VCOFreqCalibrate(bool narrowBand, uint8_t startSB, int numPoints);

	/**
	@brief This API returns the calibrated VCO subband frequency table.

	Before using this API, you need to call chip_CAFC_VCOFreqCalibrate.

	@see chip_CAFC_VCOFreqCalibrate
	@return DolphinIC_rval_t
	@param[in] narrowTable Choose which table to use (true: 1GHz VCO table, false: 2GHz VCO table)
	@param[in] fBegin Array of 128 floats for subband begin frequencies
	@param[in] fEnd Array of 128 floats for subband end frequencies
	@param[in] BW Array of 128 floats for subband bandwidthes
	*/
	DolphinIC_rval_t chip_CAFC_GetVCOTable(bool narrowTable, float *fBegin, float *fEnd, float *BW);

	/**
	@brief This API sets the calibrated VCO subband frequency table to the DLL.

	@return DolphinIC_rval_t
	@param[in] narrowTable Choose which table to use (true: 1GHz VCO table, false: 2GHz VCO table)
	@param[in] num The current subband number to be set. 0-127
	@param[in] fBegin Begin frequency of the current chosen subband
	@param[in] fEnd End frequency of the current chosen subband
	@param[in] BW BW of the current chosen subband
	*/
	DolphinIC_rval_t chip_CAFC_SetVCOTable(bool narrowTable, int num, float fBegin, float fEnd, float BW);

	/**
	@brief This API chooses the subband according to user's input based on the subband table

	Before using this API, chip_CAFC_VCOFreqCalibrate is needed.

	## Function description

	The user input effective chirp bandwidth is the first priority. When this cannot be met with user input effective fc, the user input fc will be shifted to satisfy the chirp bandwidth.

	There are two sets of subbands in Dolphin ES1, one is for 1GHz bandwidth bands, the other is for 2GHz bandwithd bands. User can choose which band he would like to operate in by using use2GBands input parameter.

	## Return code

	- 0: successful with user strict input
	- -1: effBW is too large for chosen subbands list
	- -2: boundaries are both outside whole band table, no need to try effFc shifts.
	- -3: tried to find effFc shifts, but no shift is possible.
	- -10/-11: something is really wrong, this API should never return this.

	@sa chip_CAFC_SubBandSelectBinarySearch

	@return uint32_t Error code, 0 is successful with user strict input, 1 is successful with effFc left shift, 2 is right shift, <0 is failed.
	@param[inout] effFc Effective center frequency Hz.
	@param[in] effBW Effective bandwidth of the chirp Hz, so the chirp in the sampling period ranges from effFc-effBW/2 to effFc+effBW/2 in frequency.
	@param[in] tSettle Settle time in us.
	@param[in] tSample Sampling time in us.
	@prarm[in] tJumpback Jump back time after the end of sampling time in us.
	@param[out] fStart The actual start frqeuency Hz, defined as effFc-effBW/2-tSettle*fSlope.
	@prarm[out] fStop The actual stop frequency Hz, defined as effFc+effBW/2+tJumpback*fSlope.
	@prarm[in] downChirp Set true to calculate settings for down chirp.
	@param[out] usedBW The acutal used bandwidth in the choosen subband Hz, fStop-fStart.
	@param[in] narrowBand Whether or not using the 1GHz subbands/2GHz subbands.
	@param[out] subBand The subband number to use. 0-127
	*/
	int chip_CTRL_SubBandSelect(double *effFc, float effBW, float tSettle, float tSample, float tJumpback, float *fStart, float *fStop, bool downChirp, float *usedBW, bool narrowBand, uint8_t *subBand);

	/**
	@brief This API chooses the subband according to user's input using binary search without any VCO frequency table.

	Before using this API, chip_CAFC_VCOFreqCalibrate is NOT needed. All VCO table storage space is also NOT needed.

	## Function description
	
	This function has exactly the same signatures with chip_CTRL_SubBandSelect and they are used interchangablly in chip_Chirp_Program().
	The difference is that chip_CTRL_SubBandSelect needs a pre-calibrated VCO frequency table. This table is measured by chip_CAFC_VCOFreqCalibrate() and stored in stack of the software. However, this function does not need such a table. This function will measure frequency in a smart way (in the form of binary search), so that we don't need to measure the full VCO subband table, but only maximum 7 points in the VCO subbands.

	The current limitation is that this function does not shift effFc automatically if user's input cannot be met.

	## Return code

	Dolphin standard error codes

	@return DolphinIC_rval_t Dolphin standard error codes
	@param[inout] effFc Effective center frequency Hz.
	@param[in] effBW Effective bandwidth of the chirp Hz, so the chirp in the sampling period ranges from effFc-effBW/2 to effFc+effBW/2 in frequency.
	@param[in] tSettle Settle time in us.
	@param[in] tSample Sampling time in us.
	@prarm[in] tJumpback Jump back time after the end of sampling time in us.
	@param[out] fStart The actual start frqeuency Hz, defined as effFc-effBW/2-tSettle*fSlope.
	@prarm[out] fStop The actual stop frequency Hz, defined as effFc+effBW/2+tJumpback*fSlope.
	@prarm[in] downChirp Set true to calculate settings for down chirp.
	@param[out] usedBW The acutal used bandwidth in the choosen subband Hz, fStop-fStart.
	@param[in] narrowBand Whether or not using the 1GHz subbands/2GHz subbands.
	@param[out] subBand The subband number to use. 0-127
	*/
	DolphinIC_rval_t chip_CAFC_SubBandSelectBinarySearch(double *effFc, float effBW, float tSettle, float tSample, float tJumpback, float *fStart, float *fStop, bool downChirp, float *usedBW, bool narrowBand, uint8_t *subBand);

	/**
	@brief A system-level API which configures a chirp profile in one call.

	This API integrates several chirp-related profile-based API functions to provide one single function to program the chip with certain chirp settings. By using several different API functions in sequence, the same functionality can be reached.

	## Integration of various API functions

	- chip_Chirp_SubbandSelect
	- chip_CAFC_ProfileConfig
	- chip_TE_ProfileConfig
	- chip_SC_ProfileConfig

	## Non-profile specific APIs

	Before calling chip_Chirp_Program, the following static configuration APIs need to be called.

	- chip_TE_ChirpTrigMode
	- chip_TE_StaticConfig

	@see Dolphin Datasheet
	@return int 0: success; -1: failed.
	@param[in] ProfileNum Profile number, 0-3
	@param[in] narrowBand Choose whether to use narrow band or wide band.
	@param[in] downChirp Choose whether to do a down chirp or a up chirp.
	@param[inout] effFc Effective center frequency, Hz (center at the sampling period), could be shifted by subband selection algorithm if needed.
	@param[in] effBW Effective bandwidth, Hz
	@param[in] loopBW Chirp PLL loop bandwidth, Hz, 300kHz - 1500KHz
	@param[in] tDwell Dwell time, us
	@param[in] tSettle Settling time, us
	@param[in] tJumpback Jumpback time, us
	@param[in] tReset Reset time, us
	@param[in] NumSamples Number of samples per chirp.
	@param[in] Decimation Decimation 1, 2, 4, 8, 16
	@param[in] PDCBWWide Choose wideband mode decimation filter or narrowband mode. See datasheet for filter characteristics.
	@param[in] BPSControl Bipolar phase shift control for TXs. Array of 3.
	@param[in] TxSW Fast switch control during chirp period. Array of 3.
	@param[in] TxPON TX DC power control during chirp period. Array of 3.
	@param[in] RxPON RX DC power control during chirp period. Array of 3.
	*/
	int chip_Chirp_Program(
		int ProfileNum,
		bool narrowBand, bool downChirp,
		double* effFc, float effBW, float loopBW,
		float tDwell, float tSettle, float tJumpback, float tReset,
		uint16_t NumSamples, uint8_t Decimation,
		bool PDCBWWide,
		bool BPSControl[3], bool TxSW[3], bool TxPON[3], bool RxPON[4],
		float tidle);

	/**




	@brief A system-level API which stitch profile-0 and profile-1 for wider total bandwidth

	This API stitch two chirps into one chirp with larger BW.
	Profile0 and Profile1 are used to generate the stitched chirp.

	@return int 0: success; -1: failed.
	@param[in] narrowBand Choose whether to use narrow band or wide band.
	@param[in] downChirp Choose whether to do a down chirp or a up chirp.
	@param[inout] effFc0 Desired total stitched chirp effective center frequency
	@param[in] effBW0 Desired total stitched chirp effective BW
	@param[in] loopBW Chirp PLL loop bandwidth, Hz, 300kHz - 1500KHz
	@param[in] tDwell Dwell time, us
	@param[in] tSettle Settling time, us
	@param[in] tJumpback Jumpback time, us
	@param[in] tReset Reset time, us
	@param[in] NumSamplesPerProfile Number of samples per chirp in one profile.
	@param[in] Decimation Decimation 1, 2, 4, 8, 16
	@param[in] PDCBWWide Choose wideband mode decimation filter or narrowband mode. See datasheet for filter characteristics.
	@param[in] BPSControl Bipolar phase shift control for TXs. Array of 3.
	@param[in] TxSW Fast switch control during chirp period. Array of 3.
	@param[in] TxPON TX DC power control during chirp period. Array of 3.
	@param[in] RxPON RX DC power control during chirp period. Array of 3.
	@param[in] comp1StepEn Enable "1-step higher" compensation for better RF frequency alignment or not
	*/
	int chip_Chirp_ProgramStitch(
		bool narrowBand, bool downChirp,
		double effFc0, double effBW0, float loopBW,
		float tDwell, float tSettle, float tJumpback, float tReset,
		uint16_t NumSamplesPerProfile, uint8_t Decimation,
		bool PDCBWWide,
		bool BPSControl[3], bool TxSW[3], bool TxPON[3], bool RxPON[4], bool comp1StepEn);

	/**
	@brief This API controls the LO buffers and gain of buffer 2 towards Tx/Rx path.

	## Buffer configurations

	- NORMAL	= 0x1,	MUX=0|B1=1|B2=1|B3=0|B4=0
    - LOOPTHRU	= 0x2,	MUX=1|B1=1|B2=1|B3=1|B4=1
    - EXTLOOUT	= 0x3,	MUX=0|B1=1|B2=1|B3=0|B4=1
    - EXTLOIN	= 0x4,	MUX=1|B1=0|B2=1|B3=1|B4=0

	In normal operation, use NORMAL mode.

	If LO signal needs to be observed on the LO output, you may use EXTLOOUT mode.

	EXTLOOUT and EXTLOIN are used in cascading scenarios.

	## b2gain

	5'b00000: really low;
	5'b01011: -20dBm;
	5'b01111: -17dBm;
	5'b10000: -15dBm;
	5'b10010: -12dBm;
	5'b11111: maximum;

	@see Dolphin Datasheet - LO interface chapter
	@param[in] mode Buffer configurations.
	@param[in] b2gain Buffer 2 gain, from 0(min) - 31(max)
	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_LO_Control(int mode, uint8_t b2gain);

	/**
	@brief This API controls the TX channels (even in non-chirp period)

	@param[in] TXNum TX channel to be configured. Valid input 1-3.
	@param[in] BPSExtControlEn Enable external pin control on the bipolar phase shift.
	@param[in] SPI_BPSEn Enable bipolar shift via SPI.
	@param[in] SPI_SWEn	Enable fast switch via SPI.
	@param[in] SPI_TXEn Enable TX via SPI.
	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_TX_Control(int TXNum, bool BPSExtControlEn, bool SPI_BPSEn, bool SPI_SWEn, bool SPI_TXEn);

	/**
	@brief This API configures the RX channel profiles

	## ES3 Differences
	This API is designed to be compatible to the ES1 version as much as possible.
	For LPF6dBCutOffHz, the input range is [3.75, 15]MHz as a float type number.
	For HPF6dBCutOffHz, the input setting is a limited list: 100, 200, 300, 400, 800, 1600kHz.
	If a value in between these values are used, it will be rounded to the nearest side.

	@param[in] RXNum RX channel to be configured. Valid input 1-4.
	@param[in] ProfileNum The profile in the selected channel. Valid input 0-3.
	@param[in] rxGain RX channel gain. Valid input 1-7.
	@param[in] LPF6dBCutOffHz controls the 6dB cutoff frequency of the RX LPF, Hz
	@param[in] HPF6dBCutOffHz controls the 6dB cutoff frequency of the RX HPF, Hz
	@param[in] RMSDetOn RMSDetOn Turn on RMS detector or not.
	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_RX_ProfileConfig(int RXNum, int ProfileNum, uint8_t rxGain, float LPF6dBCutOffHz, float HPF6dBCutOffHz, bool RMSDetOn);




	/**
	@brief This API lets users to Cfg the LVDS-TX Mode.

	bit_clk_phase
	0: first serial bit starts with bit_clk Fall edge
	1: first serial bit starts with bit_clk rise edge.

	frame_clk_phase
	0: Serial bit starts from Rise edge of frame_clk
	1: Serial bit starts from Fall edge of frame_clk.

	LSB/MSB of the Parallel word send first:
	0: LSB first
	1: MSB first

	User is responsible to use valid values as inputs! No boundary check is applied in the API.

	@see TRANSMITPHASECONTROL & MSBLSBCONTROL
	@param[in] bit_clk_phase,  0: first serial bit starts with bit_clk Fall edge | 1: first serial bit starts with bit_clk rise edge.
	@param[in] frame_clk_phase,  0: Serial bit starts from Rise edge of frame_clk | 1: Serial bit starts from Fall edge of frame clk.
	@param[in] msb_first,  0: LSB first | 1: MSB first
	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_LVDS_CfgMode(bool bit_clk_phase, bool frame_clk_phase, bool msb_first);

	/**
	@brief This API lets users to Cfg the CIF data mode.

	@param[in] PacketHeaderEnable,
	0: no Packet Header on transmitted data Packet.
	1: Packet Header is appended to the  Data Packet.
	Note: Packet header contains Chirp No and Sample Count(no of ADC samples sent over the CIF interface)

	@param[in] CRCEnable
	1: enable CIF CRC
	0: disable CIF CRC
	Note : This bit enables the 32-bit CRC engine and append the CRC output in the packet footer.32 -bit CRC is send as three seperated 12 bit in the packet.

	@param[in] NegEdgeEnable:
	0: data is pos  edge aligned with o/p cif clock
	1: data is neg  edge aligned with o/p cif clock.

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CIF_Config(bool PacketHeaderEnable, bool CRCEnable, bool NegEdgeEnable);

	/**
	@brief This API lets users to Cfg the CSI-2 TX.

	@param[in] NChirps, numer of chirps

	@param[in] NLanes
	0x00 : One Lane Enabled (Lane-0)
	0x01 : Two Lane Enabled (Lane-0,1)
	0x02 : Three Lane Enabled( Lane-0,1,2)
	0x03 : Four Lane Enabled( Lane-0,1,2,3)

	@param[in] DataRate:
	0: 480 Mbps
	1: 240 Mbps
	2: 120 Mbps

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CSI2_Config(uint32_t NChirps, uint32_t NLanes, uint32_t DataRate);

	/**
	@brief This API configures CSI2 to fixed pattern mode with 12bit data 0xBF5

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CSI2_CfgTestMode(void);

	/**
	@brief This API configures LVDS to fixed pattern mode with 12bit data 0x214

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_LVDS_CfgTestMode(void);

	/**
	@brief This API configures CIF to fixed pattern mode with 12bit data 0x214

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_CIF_CfgTestMode(void);

	DolphinIC_rval_t chip_FS_IntegrityCheckMClk(int32_t mode, float refFreq);

	/**
	@brief To AutoCorrect or Calibrate the LOI B2 gain LOW and HIGH
	events detected by Status Monitor during active chirp period.

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_ISM_lointf_GainCalibration(void);

	/**
	@brief To AutoCorrect or Calibrate the TX gain LOW and HIGH
	events detected by Status Monitor during active chirp period.

	@param[in] txOn - ON/OFF status of TX[0-3], array size should be 0x03.

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_ISM_tx_GainCalibration(bool txOn[3], uint8_t profile);


	/**
	@brief To AutoCorrect or Calibrate the LO interface B2 gain based on LOW and HIGH status flag
	events detected by Status Monitor during active chirp period and interface Clk/data is disabled from toggling.

	@param[in] None
	@param[in] mode - 1:CSI-2, 2:LVDS, 3:CIF-MFIO
	@return DolphinIC_rval_t
	*/

	DolphinIC_rval_t chip_ISM_lointf_GainCalibration_Mode(int32_t mode);
	/**
	@brief To AutoCorrect or Calibrate the TX gain LOW and HIGH
	events detected by Status Monitor during active chirp period and interface clk/ data is disabled from toggling.

	@param[in] txOn - ON/OFF status of TX[0-3], array size should be 0x03.
	@param[in] mode - 1:CSI-2, 2:LVDS, 3:CIF-MFIO

	@return DolphinIC_rval_t
	*/

	/*DolphinIC_rval_t chip_ISM_tx_GainCalibration_Mode(bool txOn[3], uint8_t profile, int32_t mode);*/

	//error mask and unmask functions

	void chip_ISM_MaskSupplyError( uint32_t arg_mask );
	void chip_ISM_UnMaskSupplyError( uint32_t arg_mask );
	void chip_ISM_MaskTxError( uint32_t arg_mask );
	void chip_ISM_UnMaskTxError( uint32_t arg_mask );
	void chip_ISM_MaskRxError( uint32_t arg_mask );
	void chip_ISM_UnMaskRxError( uint32_t arg_mask );
	void chip_ISM_MaskChirpError( uint32_t arg_mask );
	void chip_ISM_UnMaskChirpError( uint32_t arg_mask );
	void chip_ISM_MaskMCLOError( uint32_t arg_mask );
	void chip_ISM_UnMaskMCLOError( uint32_t arg_mask );
	void chip_ISM_MaskADCError( uint32_t arg_mask );
	void chip_ISM_UnMaskADCError( uint32_t arg_mask );

	//get function for raw errors
	uint32_t chip_ISM_GetRawMasterErrorStatus( void );
	uint32_t chip_ISM_GetRawSupplyErrorStatus( void );
	uint32_t chip_ISM_GetRawTxErrorStatus( void );
	uint32_t chip_ISM_GetRawRxErrorStatus( void );
	uint32_t chip_ISM_GetRawChirpErrorStatus( void );
	uint32_t chip_ISM_GetRawMCLOErrorStatus( void );
	uint32_t chip_ISM_GetRawADCErrorStatus( void );
	uint32_t chip_ISM_GetRawRFPowDwnErrorStatus( void );

	//get function for masked errors
	uint32_t chip_ISM_GetMasterErrorStatus( void );
	uint32_t chip_ISM_GetSupplyErrorStatus( void );
	uint32_t chip_ISM_GetTxErrorStatus( void );
	uint32_t chip_ISM_GetTxRawErrorStatus(void);
	uint32_t chip_ISM_GetRxErrorStatus( void );
	uint32_t chip_ISM_GetChirpErrorStatus( void );
	uint32_t chip_ISM_GetMCLOErrorStatus( void );
	uint32_t chip_ISM_GetADCErrorStatus( void );
	uint32_t chip_ISM_GetRFPowDwnErrorStatus( void );
	uint32_t chip_ISM_GetISMErrorStatus( void );

	/**
	@brief This API resets all errors in ISM so that ISM is in a error-free status.

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_ISM_SetMCUReset(void);

	/**
	@brief This API does Fault Injection Test for ISM module itself.

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_ISM_FIT(int32_t mode);


	/**
	@brief API computes CRC32 for given data block

	## CRC32 routine based on the IEEE-802.3 CRC32 Ethernet Standard, using default polynomial 0xEDB88320

	@param[in] Crc_DataPtr Pointer to start address of data block to be calculated.
	@param[in] Crc_Length Length of data block to be calculated in bytes.
	@param[in] Crc_StartValue32 Start value when the algorithm starts.
	@param[in] Crc_IsFirstCall TRUE : First call in a sequence or individual CRC calculation; start from initial value, ignore Crc_StartValue32.
	                           FALSE : Subsequent call in a call sequence; Crc_StartValue32 is interpreted to be the return value of the previous function call.
	@retval computed CRC32 value.
	*/
	uint32_t chip_CTRL_ComputeCRC32( const void * Crc_DataPtr, uint32_t Crc_Length, uint32_t Crc_StartValue32);


	/**
	@brief API which does the TX software driven fault injection test.

	## This API will check whether TX level low errors can be produced when LO doesn't have enough output power to TX path.

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_ISM_SWTXFit(uint8_t fitProfile);

	/**
	@brief API which does the Chirp software driven fault injection test.

	## This API will check whether Chirp unlock and min errors can be produced and flaged.

	@retrun DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_ISM_SWChirpFit(uint8_t fitProfile);

		
	/**
	@brief Update Register Shadow page with current device status.

	@retval None.
	*/

	DolphinIC_rval_t chip_ISM_Sw_FIT(uint8_t fitProfile, bool TxPON[3]);
	/**
	@brief API which does the Combined software FIT for Chirp and TX'es.

	## This API will check whether Chirp unlock and min errors as well as TX min error can be produced and flaged.

	@retrun DolphinIC_rval_t

	*/
	void chip_rshd_updateFromDev( uint8_t moduleaddress );

	/**
	@brief Device Register is checked with Shadow page content, Return True if content matches.

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_rshd_checkRegPage(uint8_t moduleaddress);

	/**
	@brief Reads content of Status Monitor and executes recovery function based on warnings triggered.

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_ISM_StatusCheckAndRecover();

	/**
	@brief Performs Interface Toggle test in selected pin.

	@return DolphinIC_rval_t
	*/
	DolphinIC_rval_t chip_ISM_InterfaceToggleTest(dolphin_ExtPinID_t en_pid);

	DolphinIC_rval_t chip_ISM_RFBIST();

	void chip_ISM_SetGPIO(uint32_t en_pid,bool on_off);
	bool chip_ISM_GetGPIO(uint32_t en_pid);

	DolphinIC_rval_t chip_ISM_Inject_error(uint32_t Error_ID, uint8_t Profile );
	DolphinIC_rval_t chip_ISM_UnMask_All_error();
	DolphinIC_rval_t chip_ISM_Recover_error_FunRst(uint32_t Error_ID);
	DolphinIC_rval_t chip_ISM_Recover_error(uint32_t Error_ID,uint8_t Profile);

	/**
	@brief	Function to correct the TX level monitor thresholds based on desired Parp and current temperature reading
	If threshold to be corrected is Min, always writes '1'.
	This function re-calculates the threshold values from the original OTP max threshold value everytime it is called.

	@param[in] TXNum : TX#, 1,2 or 3
	@param[in] typeTh : Threshold types: 0:Min, 1:Low, 2:High, 3:Max
	@param[in] targetParp : Desired output at antenna reference plane
	@param[in] readTemp : in case of true, temperature will be read from the TX under calibration
	@param[in] temp : Operation temperature that the thresholds will be corrected in case no reading from TX selected
	@param[in] effFc : effective center frequency of a chirp
	**/
	DolphinIC_rval_t chip_TX_CorrectLevelMonThresholds(int txNum, uint8_t typeTh, float Parp, bool readTemp, int temperature, float effFc);


	/**
	@brief	Function to correct ALL the TX level monitor thresholds based on desired Parp values using always internal temperature reading

	@param[in] Parp : Integer array with the desired output at antenna reference plane for [min, low, high, max] thresholds. The thresholds 
	with Parp set to 0 will not be corrected (left as they are). Type is integer for compatibility with RR UDP command set.
	@param[in] effFc : effective center frequency of a chirp
	**/      
	DolphinIC_rval_t chip_TX_SetAllMonitorThresholds(float ParpMin, float ParpLow, float ParpHigh, float ParpMax, float effFc, bool applyOverFreq);
	
	/**
	@brief Fucntion to configure CW mode

	
	@param[in] profID Profile number, 0-3
	@param[in] narrowBand Choose whether to use narrow band or wide band.
	@param[in] CWFreq CWMode frequency
	@param[in] NumSamples Number of samples per chirp.
	@param[in] loopBW Chirp PLL loop bandwidth, Hz, 300kHz - 1500KHz
	@param[in] Decimation Decimation 1, 2, 4, 8, 16
	@return DolphinIC_rval_t

	*/
	DolphinIC_rval_t chip_Chirp_CWMode(uint8_t profID, bool narrowBand, double CWFreq, uint16_t NumSamples, float loopBW, uint8_t Decimation, float tidle);


	DolphinIC_rval_t chip_TX_fPCtrl_CorrPout(uint8_t txNumb, bool isFullCalib);

	DolphinIC_rval_t chip_TX_fPCtrl_SetHighThreshold(uint8_t txNumb, uint16_t txGain);
#ifdef __cplusplus
}
#endif

#endif /* DOLPHINIC_H */
