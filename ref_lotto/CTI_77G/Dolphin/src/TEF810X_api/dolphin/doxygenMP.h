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
@file doxygenMP.h
@brief Doxygen Main Page.
@mainpage Welcome to the Dolphin ES1 API Documentation

\section purpose Purpose of the API

The ES3 API provides convenient access to Dolphin functions. It also contains libraries to control the FPGA platform which is hosting Dolphin ES3 in the evaluation setup.

The API is used in NXP internal development, validation and demo as well as customers to build their own evaluation setup. Note that the API is for evaluation/study purposes only and shall not be used in production environment.

Build Date: 14/Dec/2018

\section dis Disclaimer

 Copyright(C) NXP B.V. 2016

 All rights are reserved. Reproduction in whole or in part is prohibited
 without the prior written consent of the copy-right owner.
 This source code and any compilation or derivative thereof is the sole
 property of NXP B.V. and is provided pursuant to a Software License
 Agreement. This code is the proprietary information of NXP B.V. and
 is confidential in nature. Its use and dissemination by any party other
 than NXP B.V. is strictly limited by the confidential information
 provisions of the agreement referenced above.
																			
 NXP reserves the right to make changes without notice at any time.	
 NXP makes no warranty, expressed, implied or statutory, including but
 not limited to any implied warranty of merchantability or fitness for any
 particular purpose, or that the use will not infringe any third party patent
 copyright or trademark. NXP must not be liable for any loss or damage
 arising from its use.

\section info Important Information

\subsection tandfreq Time and frequency units

For timing, us (micro seconds) is used as unit
For frequency, Hz (herts) is used as unit.
So chirp slope will have a unit of hz/us

\subsection spi SPI Message Format

	Single SPI access:

	MOSI:	M0|M1|M2|M3|M4|M5|M6|M7

	MISO:	S0|S1|S2|S3|S4|S5|S6|S7

	Burst SPI access: (2 access example)

	MOSI:	M0|M1|M2|M3|M4|M5|M6|M3'|M4'|M5'|M6'|M7

	MISO:	S0|S1|S2|S3|S4|S5|S6|S7 |S4'|S5'|S6'|S7'

	S0 - S3 are in total 32-bit returned data (ReturnedData).

	For more information, see the Dolphin Datasheet, UM and AN.

\subsection filelist File List

- dolphin.dll The Dolphin ES3 API dll.
- dolphin.lib The Dolphin ES3 API dll importing lib.
- dolphin.h The Dolphin ES3 API header file. This file includes the later 3.
- dolphinIC.h The IC API Group function decalarations.
- dolphinHost.h The Host API Group function decalarations.
- dolphinStrm.h The Streamer API Group function decalarations.
- okDolphin.dll 3rd party dependency used by dolphin.dll.
- okFrontPanelDLL.dll 3rd party dependency used by dolphin.dll.

*/