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
* @file hal_es3_ctrl.c
*
* @ver v5.3.0  
*
* @author
*
* @date 04/02/2016
*
*
*
******************************************************************************/

/******************************************************************************
* INCLUDES
*****************************************************************************/
#include <math.h>
#include <hal_es3.h>
#include <hal_es3_ctrl.h>

#ifdef DOLPHIN_CFG_ES3

#include <es3/NXP_TEF810X_CentralControl.h>

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

//lookup table for standard CRC32 poly 0xEDB88320(reflected, lsb first) 
//(or 0x04C11DB7(msb first))
static const uint32_t CRC32Table[256] =
{
	0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
	0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
	0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
	0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
	0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
	0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
	0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
	0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
	0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
	0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
	0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
	0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
	0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
	0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
	0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
	0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
	0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
	0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
	0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
	0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
	0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
	0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
	0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
	0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
	0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
	0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
	0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
	0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
	0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
	0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
	0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
	0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D,
};

#ifndef SB_BINARYSEARCH_ENABLE
//local candidate subband list
static int32_t SBCandidate[NUM_SUBBANDS_ES3];

/**
@brief This local helper function returns max value in certain column in the input matrix

@return int The current subband, -1 means outside the boundaries of the VCO table.
@param[in] input VCO table of type VCOTableItemES3_t.
@param[in] size The size of the VCO table.
*/
static double findMaxinCol(const VCOTableItemES3_t* input, int size)
{
	double max = 0;

	if (size > 0)
	{
		for (int loop0 = 0; loop0 < size; loop0++)
		{
			if (input[loop0].BW > max)
				max = input[loop0].BW;
		}
		return max;
	}
	else
		return 0;
}

/**
@brief This local helper function returns the current subband that the input frequency is located.

It searches the input frequency according to fBegins of the subbands or fEnds of the subbands depending on input parameter lowerSide.

@return int The current subband, -1 means outside the boundaries of the VCO table.
@param[in] freqInput The input frequency under search.
@param[in] input VCO table of type VCOTableItemES3_t
@param[in] lowerSide Whether to search according to fBegins or fEnds in the VCO table.
@param[in] size The size of the VCO table.
*/
static int searchCurrentBand(float freqInput, const VCOTableItemES3_t* input, const bool lowerSide, const int size)
{
	if (freqInput < input[0].fBegin) //outside the minmimum frequency
		return -1;
	else if (freqInput > input[size - 1].fEnd) //outside the maximum frequency
		return -1;

	//search using the lower boundaries (fBegins)
	if (lowerSide)
	{
		for (int loop0 = 0; loop0 < size - 1; loop0++)
		{
			if (freqInput >= input[loop0].fBegin && freqInput < input[loop0 + 1].fBegin)
				return loop0;
		}

		//in the last subband, return size-1
		if (freqInput >= input[size - 1].fBegin && freqInput < input[size - 1].fEnd)
			return size - 1;
	}
	else//using the higher boundaries (fEnds)
	{
		for (int loop0 = 1; loop0 < size; loop0++)
		{
			if (freqInput > input[loop0 - 1].fEnd && freqInput <= input[loop0].fEnd)
				return loop0;
		}

		//in the first subband, return 0
		if (freqInput > input[0].fBegin && freqInput <= input[0].fEnd)
			return 0;
	}

	return -1;
}


int hal_es3_ctrl_SelectSubBand(double *effFc, float effBW, float tSettle, float tSample, float tJumpback, float *fStart, float *fStop, bool downChirp, float *usedBW, bool narrowBand, uint8_t *subBand)
{
	//sign of the slope according to downChirp
	float slopeSign = downChirp ? -1 : 1;

	//chirp slope
	double fSlope = slopeSign * effBW / tSample;

	//temp frequency parameters
	//depending on downChirp, FStart can be lower or higher than FStop.
	double tmpFStart = *effFc - slopeSign * effBW / 2 - tSettle*fSlope;
	double tmpFStop = *effFc + slopeSign * effBW / 2 + tJumpback*fSlope;
	float tmpUsedBW = fabs(tmpFStop - tmpFStart);

	//work with low/high frequency rather than tmpFStart and tmpFStop, this simplifies the implementation.
	float FLow = downChirp ? tmpFStop : tmpFStart;
	float FHigh = downChirp ? tmpFStart : tmpFStop;

	DbgInfo("narrowBand:%d\n", narrowBand);
	DbgInfo("tmpUsedBW:%f\n", tmpUsedBW);

	//choose wide or narrow subband according to user input.
	const VCOTableItemES3_t* vcoTable;

	if (narrowBand)
	{
		double maxUsableBWNarrowBand = findMaxinCol(VCOTableNBES3, NUM_SUBBANDS_ES3);
		if (tmpUsedBW <= maxUsableBWNarrowBand)
		{
			vcoTable = VCOTableNBES3;
			DbgInfo("using narrow band!\n");
		}
		else //effBW input is too large for narrow bands
			return -1;
	}
	else
	{
		//max usable BWs
		double maxUsableBWWideBand = findMaxinCol(VCOTableWBES3, NUM_SUBBANDS_ES3);
		if (tmpUsedBW <= maxUsableBWWideBand)
		{
			vcoTable = VCOTableWBES3;
			DbgInfo("using wide band!\n");
		}
		else //effBW input is too large for wide bands
			return -1;
	}

	//subband candidate list, init to -1 (invalid subband)
	memset(&SBCandidate[0x00], 0x00, (sizeof(int32_t) * NUM_SUBBANDS_ES3));

	//number of possible subband candidates
	int numSBCandi = 0;

	//search for possible subband candidate with strict user input constraints
	for (int loop0 = 0; loop0 < NUM_SUBBANDS_ES3; loop0++)
	{
		if ((FLow >= vcoTable[loop0].fBegin) && (FHigh <= vcoTable[loop0].fEnd))
		{
			//record candidates
			numSBCandi++;
			SBCandidate[numSBCandi - 1] = loop0;
		}
	}

	//process the candidate list
	if (numSBCandi > 0) //there is at least 1 suitable subband.
	{
		//display the candidates
		for (int loop0 = 0; loop0 < numSBCandi; loop0++)
		{
			DbgInfo("Candidate subband inx(%d) %d %e %e %e \n", loop0, SBCandidate[loop0], vcoTable[SBCandidate[loop0]].fBegin
				, vcoTable[SBCandidate[loop0]].fEnd, vcoTable[SBCandidate[loop0]].BW);
		}

		if (numSBCandi > 1) //more than one suitable subband
		{
			//choose the best-fit candidate
			//Criteria: effFc is closest to the center of the subband
			float minDiffEffFcAndBandCenter = 10e10;//just a substantially large number
			for (int loop0 = 0; loop0 < numSBCandi; loop0++)
			{
				float bandCenter = (vcoTable[SBCandidate[loop0]].fBegin + vcoTable[SBCandidate[loop0]].fEnd) / 2;
				float diff = fabsf(*effFc - bandCenter);
				if (diff < minDiffEffFcAndBandCenter)
				{
					minDiffEffFcAndBandCenter = diff;
					*subBand = SBCandidate[loop0];
				}
			}
		}
		else //only one suitable subband
			*subBand = SBCandidate[0];

		//assign output values.
		*fStart = tmpFStart;
		*fStop = tmpFStop;
		*usedBW = tmpUsedBW;

		DbgInfo("Selected subband is:%d, fStart:%f, usedBW:%f, totalFc26:%f\n", *subBand, *fStart, *usedBW, (*fStart + (*usedBW) / 2) / 3);

		//successful!
		return 0;
	}
	else if (numSBCandi == 0) //no suitble subband under strict user constraints
	{
		//Try to shift effFc within a constraint to a place where it fits the effBW.
		//Shift criteria: (always shift the lower frequency boundary, which is equivalent to shifting effFc)
		//shift the FLow from the current band within -2 ~ +3 bands
		//if there are multiple possible shifts, choose the one with least deviation from user input effFc.

		//hard limits on number of shifts
		const int loShftLim = 2;
		const int hiShftLim = loShftLim + 1;

		//real limits on shift, will be calculated on the fly also considering boundary conditions.
		int leftLim = loShftLim;
		int rightLim = hiShftLim;

		//the deviation from oringinal effFc, init to a large number.
		float fcDeviationL = 10e10;
		float fcDeviationR = 10e10;

		//current subband
		int currSBFLow = -1;
		int currSBFHigh = -1;

		//shift counters
		int loopL = 0; //0 means, for left shift, first check in current subband.
		int loopR = 1;


		//search for FLow according to FBegins
		currSBFLow = searchCurrentBand(FLow, vcoTable, true, NUM_SUBBANDS_ES3);
		if (currSBFLow != -1)//Flow is not outside the whole subband table.
		{

			//first try to shift to the LOWER frequency bands.
			//attention "<="
			//attention min(), for lower boundaries
			leftLim = min(loShftLim, currSBFLow);
			for (loopL = 0; loopL <= leftLim; loopL++)
			{
				float diffFHigh = FHigh - vcoTable[currSBFLow - loopL].fEnd;
				float diffFLow = FLow - vcoTable[currSBFLow - loopL].fBegin;

				if (diffFHigh <= diffFLow) //the shift is possible and must be the smallest shift.
				{
					fcDeviationL = diffFHigh;
					//the first possible one is the one with the least deviation in effFc.
					break;
				}
			}

			//then try to shift to the HIGHER frequency bands.
			//attention for min() for higher boundaries
			rightLim = min(hiShftLim, NUM_SUBBANDS_ES3 - 1 - currSBFLow);
			for (loopR = 1; loopR <= rightLim; loopR++)
			{
				double diffFHigh = vcoTable[currSBFLow + loopR].fEnd - FHigh;
				double diffFLow = vcoTable[currSBFLow + loopR].fBegin - FLow;

				if (diffFLow <= diffFHigh) //the shift is possible and must be the smallest shift.
				{
					fcDeviationR = diffFLow;
					break;
				}
			}
		}
		else//FLow is either lower than smallest fBegin or higher than largest fEnd
		{
			//search for FHigh accoring to FEnds
			currSBFHigh = searchCurrentBand(FHigh, vcoTable, false, NUM_SUBBANDS_ES3);
			if (currSBFHigh != -1)//tmpFStop is not outside the whole subband table. This happens when effFc is chosen near the beginning of the VCO table
			{
				//in this case, ONLY right shift needs to be considered
				//saturate left shfit counter.
				loopL = loShftLim + 1;

				rightLim = min(hiShftLim - 1, NUM_SUBBANDS_ES3 - 1 - currSBFHigh);
				//loopR is init to 0 rather than 1, since this refers to FEnd
				for (loopR = 0; loopR <= rightLim; loopR++)
				{
					float diffFHigh = vcoTable[currSBFHigh + loopR].fEnd - FHigh;
					float diffFLow = vcoTable[currSBFHigh + loopR].fBegin - FLow;

					if (diffFLow <= diffFHigh) //the shift is possible and must be the samllest shift.
					{
						fcDeviationR = diffFLow;
						break;
					}
				}
			}
			else
				return -2; // fLow and fHigh are both outside whole band table, no need to try shifts.
		}


		//check if there is any possible shift, this condition is due to the use of "break" in the above two loops
		if (loopL + loopR < leftLim + rightLim + 2)
		{
			//choose the shift with the least deviation in effFc
			if (fcDeviationL <= fcDeviationR)
			{
				tmpFStart -= fcDeviationL;
				tmpFStop -= fcDeviationL;

				//assgin outputs
				*subBand = ((currSBFHigh != -1) ? currSBFHigh : currSBFLow) - loopL;
				*effFc -= fcDeviationL;
				*fStart = tmpFStart;
				*fStop = tmpFStop;
				*usedBW = fabs(tmpFStop - tmpFStart);

				DbgInfo("Selected subband is:%d, fStart:%f, usedBW:%f\n", *subBand, *fStart, *usedBW);

				//shift to left (lower freq)
				return 1;
			}
			else
			{
				tmpFStart += fcDeviationR;
				tmpFStop += fcDeviationR;

				//assgin outputs
				*subBand = ((currSBFHigh != -1) ? currSBFHigh : currSBFLow) + loopR;
				*effFc += fcDeviationR;
				*fStart = tmpFStart;
				*fStop = tmpFStop;
				*usedBW = fabs(tmpFStop - tmpFStart);

				DbgInfo("Selected subband is:%d, fStart:%f, usedBW:%f, totalFc26:%f\n", *subBand, *fStart, *usedBW, (*fStart + (*usedBW) / 2) / 3);

				//shift to right (high freq)
				return 2;
			}
		}
		else//tried to find shifts, but no shift is possible.
			return -3;

		return -10;//this should not be reached. something must be wrong.
	}

	//nothing works, failed. this should not be reached. something must be wrong.
	return -11;
}
#endif


uint32_t hal_es3_CRC_ComputeCRC32(const void* data, unsigned int len, uint32_t previousCRC32)
{
//	uint32_t sp1_loop1 = 0x00;

	uint32_t CRC = ~previousCRC32;
	//take in data byte by byte
	unsigned char* current = (unsigned char*)data;

	//uint32_t * sp_buff = ( uint32_t * )data;
	//for( sp1_loop1 = 0x00; sp1_loop1 < ((len)/sizeof(uint32_t)); sp1_loop1++ )
	//{
	//	DbgInfo("[0x%x]:0x%x\n", sp1_loop1, sp_buff[sp1_loop1]);
	//}

#ifdef DOLPHIN_CFG_HOST_OPALKELLY
	//calc loop
	while (len--)
		CRC = (CRC >> 8) ^ CRC32Table[(CRC & 0xFF) ^ *current++];

	return ~CRC;
#endif

#ifdef DOLPHIN_CFG_HOST_S32R274
	//assume input data *data is uint32_t with big-endianness
	while(len>0)
	{
		for (int loop0=3;loop0>=0;loop0--)
		{
			// emulate little-endian calculation
			CRC = (CRC >> 8) ^ CRC32Table[(CRC & 0xFF) ^ *(current+loop0)];
		}
		// jump to next uint32 value
		current+=4;
		len-=4;
	}

	return ~CRC;
#endif
}

//auxilarry functions
int hal_es3_2sComplement(uint32_t inp, int no_bits)
{
	int iInp = 0;
	bool isNeg = false;
	if (inp & (1 << (no_bits - 1)))
		isNeg = true;
	if (!isNeg)
		return inp;
	iInp = inp & ((1 << no_bits) - 1);
	iInp = (~iInp) & ((1 << no_bits) - 1);
	iInp++;
	return (-iInp);
}

/**
@brief This API flips the bits of control-words coming from OTP
*/
uint32_t hal_es3_bit_flip(uint32_t n, uint32_t bits)
{
	uint32_t n_flip;   // nrev will store the bit-reversed pattern
	int i = 0;
	int N = 1 << bits;            // find N: shift left 1 by the number of bits
	n_flip = n;
	for (i = 1; i < bits; i++)
	{
		n >>= 1;
		n_flip <<= 1;
		n_flip |= n & 1;   // give LSB of n to nrev
	}
	n_flip &= N - 1;         // clear all bits more significant than N-1

	return n_flip;
}

// Cfg the serializer for the default ...
void hal_es3_ctrl_CfgSerializerDefault(int32_t mode)
{
	switch (mode)
	{
	case 1:
	{
		hal_es3_csi2_Config(           /* for ES2 NChirps is ignored */
			DOLPHIN_CFG_FSM_CSI2_NLANES,
			DOLPHIN_CFG_FSM_CSI2_DATARATE, true);
	}
	break;

	case 2:
	{
		hal_es3_lvds_CfgMode(false, true, true, true);
	}
	break;

	case 3:
	default:
	{
		hal_es3_cif_Config(false, false, true, true); //PacketHeaderEnable = false, CRCEnable = false, NegEdgeEnable = true
	}
	break;
	}
}

// Enable the test Mode ...
void hal_es3_ctrl_SetSerializerTestMode(int32_t mode, bool flag_enable, uint8_t test_mode_sel)
{
	switch (mode)
	{
	case 1:
	{
		hal_es3_csi2_CfgTestMode(flag_enable, DOLPHIN_CFG_FSM_CSI2_DATAPATTERN, test_mode_sel);
	}
	break;

	case 2:
	{
		hal_es3_lvds_CfgTestMode();
	}
	break;

	case 3:
	default:
	{
		hal_es3_cif_CfgTestMode();
	}
	break;
	}

}

void hal_es3_ctrl_CfgChirpTestDefault(void)
{
	double chirpperiod = 0x00;
	Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t FunctionalResetControl_ust;

	FunctionalResetControl_ust.val_u32 = 0x00;

	FunctionalResetControl_ust.bits_st.FnResetChirp = 0x01;
	hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, true, FunctionalResetControl_ust.val_u32); //0x017FF7C2

																								 // Cfg the profile-3 to test mode default ...
	chirpperiod = DOLPHIN_CFG_FSM_PROF3_DWELLTIME + DOLPHIN_CFG_FSM_PROF3_SETTLETIME \
		+ (DOLPHIN_CFG_FSM_PROF3_NSAMPLES * 0.025) + DOLPHIN_CFG_FSM_PROF3_JUMPBACKTIME \
		+ DOLPHIN_CFG_FSM_PROF3_RESETTIME;

	//configure number of chirps in a sequence
	hal_es3_teng_CfgNumChirpSeq(DOLPHIN_CFG_FSM_PROF3_NSEQ, DOLPHIN_CFG_FSM_PROF3_NCHIRPS);

	//configure sequence internal, normally keep it 1(25ns)
	hal_es3_teng_CfgSeqInterval(DOLPHIN_CFG_FSM_PROF3_SEQINTVL);

	//configure jumpback time.
	hal_es3_teng_CfgTJumpBack(DOLPHIN_CFG_FSM_PROF3_JUMPBACKTIME);

	//configure chirp profile.
	hal_es3_teng_CfgChirpProfile(DOLPHIN_CFG_FSM_TESTPROF3, 0x01, true);

	//Configure Control3 register in Timing Engine
	hal_es3_teng_UpdateProfChirpPeriod(DOLPHIN_CFG_FSM_TESTPROF3,
		DOLPHIN_CFG_FSM_PROF3_TXPON,
		DOLPHIN_CFG_FSM_PROF3_RXPON,
		chirpperiod);

	//timing_profile
	hal_es3_teng_UpdateProfTiming(DOLPHIN_CFG_FSM_TESTPROF3,
		DOLPHIN_CFG_FSM_PROF3_DWELLTIME,
		false, 25e-3,
		DOLPHIN_CFG_FSM_PROF3_TXBPS,
		DOLPHIN_CFG_FSM_PROF3_TXSW);

	//adc_profile
	hal_es3_teng_UpdateProfADC(DOLPHIN_CFG_FSM_TESTPROF3,
		DOLPHIN_CFG_FSM_PROF3_SETTLETIME,
		DOLPHIN_CFG_FSM_PROF3_NSAMPLES,
		DOLPHIN_CFG_FSM_PROF3_DEC_FACT,
		false);

	hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, false, FunctionalResetControl_ust.val_u32); //0x017FF7C2
}

#endif //DOLPHIN_CFG_ES3


DolphinIC_rval_t hal_es3_CheckUserPONEn(uint32_t IP_PON_Mask, uint16_t mod_addr)
{
	///* DECLARE LOCAL VARIABLES HERE *///

	//mapping of IP_PON_Mask follows the order of bits in IP_LEVEL_PON_ENABLE register: e.g. RX1 = bit13, RX2 = bit14, .. , TX1 = bit17.
	//mask is active high ==> if the bit is set, corresponding IP should be enabled.

	HAL_GERRCODE_INIT;
	switch (mod_addr)
	{
	case 0x0D: //RX1
		if ((IP_PON_Mask & 0x00002000) != 0)
			return DOLPHINIC_NOERROR;
		break;
	case 0x0E: //RX2
		if ((IP_PON_Mask & 0x00004000) != 0)
			return DOLPHINIC_NOERROR;
		break;
	case 0x0F: //RX3
		if ((IP_PON_Mask & 0x00008000) != 0)
			return DOLPHINIC_NOERROR;
		break;
	case 0x10: //RX4
		if ((IP_PON_Mask & 0x00010000) != 0)
			return DOLPHINIC_NOERROR;
		break;

	case 0x11: //TX1
		if ((IP_PON_Mask & 0x00020000) != 0)
			return DOLPHINIC_NOERROR;
		break;
	case 0x12: //TX2
		if ((IP_PON_Mask & 0x00040000) != 0)
			return DOLPHINIC_NOERROR;
		break;
	case 0x13: //TX3
		if ((IP_PON_Mask & 0x00080000) != 0)
			return DOLPHINIC_NOERROR;
		break;
	case 0x06: //Chirp
		if ((IP_PON_Mask & 0x00000040) != 0)
			return DOLPHINIC_NOERROR;
		break;

	default:
		return DOLPHINIC_EC_INPUTOUTOFRANGE;
		break;
	}
	return DOLPHINIC_EC_IPNOTACTIVATED;
}

DolphinIC_rval_t hal_es3_comparePON_OTP_forIPEn(uint32_t IP_PON_Mask)
{

	///* DECLARE LOCAL VARIABLES HERE *///

	//check if the user input for IP enable is valid for the TEF810x variant
//  uint32_t regVal = 0x0;
	int indx = 0;
	uint32_t OTP_200 = 0x0;
	//all available IPs for the specific commercial variable.
	uint32_t PON_mask_OTP[8] = { 0x0, 0x007FF7C2,0x007FF7C2,0x007FF7C2,0x007BF7C2,0x007BF7C2,0x007DF7C2,0x0074F7C2 }; //OTP variant based PON settings for RX and TX
	HAL_GERRCODE_INIT;
	
	OTP_200 = (g_OTPShadowLUT_ES3[0] >> 16) & 0x0F;
	//OTP_200 = hal_es3_bit_flip(OTP_200, 4);

	switch (OTP_200)
	{

	case 4:
		for (indx = 0; indx < 32; indx++) {
			if((IP_PON_Mask & (0x1 << indx)) > (PON_mask_OTP[4] & (0x1 << indx)))
				HAL_GEC_ASSERT(DOLPHINIC_EC_INPUTOUTOFRANGE);
		}
		break;
	case 5:
		for (indx = 0; indx < 32; indx++) {
			if ((IP_PON_Mask & (0x1 << indx)) >(PON_mask_OTP[5] & (0x1 << indx)))
				HAL_GEC_ASSERT(DOLPHINIC_EC_INPUTOUTOFRANGE);
		}
		break;
	case 6:
		for (indx = 0; indx < 32; indx++) {
			if ((IP_PON_Mask & (0x1 << indx)) >(PON_mask_OTP[6] & (0x1 << indx)))
				HAL_GEC_ASSERT(DOLPHINIC_EC_INPUTOUTOFRANGE);
		}
		break;
	case 7:
		for (indx = 0; indx < 32; indx++) {
			if ((IP_PON_Mask & (0x1 << indx)) >(PON_mask_OTP[7] & (0x1 << indx)))
				HAL_GEC_ASSERT(DOLPHINIC_EC_INPUTOUTOFRANGE);
		}
		break;

	default:
		break;
	}
	return HAL_GERRCODE;
}
