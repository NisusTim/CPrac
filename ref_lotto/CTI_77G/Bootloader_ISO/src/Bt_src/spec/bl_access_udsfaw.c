/*
 * bl_access_udsfaw.c
 *
 *  Created on: 2019/10/12/
 *      Author: WoodLiu
 */


#include "bl_common.h"
#include "bl_security_funcfg.h"
#include "bl_access_udsfaw.h"
#include "bl_can.h"
#include "bl_crc32_bzip2.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 602,1532,3212,3227,3453 EOF*/
/*
 * MISRA-C:2004 20.2(602):The identifier is reserved for use by the library.
 * The Bootloader do not use any library funtion and use the underscores to
 * indicate that the function is a interal function.
 *
 * 1532:The function is only referenced in one translation unit.
 * all functions in this file are configurations in the Security Module.
 *
 * 3212:This explicit cast is redundant and could be removed.
 * ACC_UDSFAW_KEY_FROM_BUF and ACC_UDSFAW_SEED_TO_BUF are not explicit cast.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
 * Acc_UdsFawGetSeed, the seed will be modify.
 * Acc_UdsFawVerifyKey, the key is declared with const.
 *
 * MISRA-C:2004 19.7(3453):A function could probably be used instead of this
 * function-like macro.
 * ACC_UDSFAW_KEY_FROM_BUF macro do not have side-effect.
 * ACC_UDSFAW_SEED_TO_BUF macro do not have side-effect.
 *
 */

/*****************************************************************************
 *  Verify The Configurations of Macro
 *****************************************************************************/
#if ((SECM_ACCESS_KEY_SIZE != 4u) && (SECM_ACCESS_KEY_SIZE != 2u))
#error "The size of a key is only four or two, other values are invalid."
#endif

#if ((SECM_ACCESS_SEED_SIZE != 4u) && (SECM_ACCESS_SEED_SIZE != 2u))
#error "The size of a seed is only four or two, other values are invalid."
#endif
/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
#if (SECM_ACCESS_KEY_SIZE == 4u)
#define ACC_UDSFAW_KEY_MASK                (0xA5CEFDB6UL)
#define ACC_UDSFAW_KEY_FROM_BUF(buf)       BL_BE32_TO_MCU(buf)
#elif (SECM_ACCESS_KEY_SIZE == 2u)
#define ACC_UDSFAW_KEY_MASK                (0xDFB6u)
#define ACC_UDSFAW_KEY_FROM_BUF(buf)       BL_BE16_TO_MCU(buf)
#endif

#if (SECM_ACCESS_SEED_SIZE == 4u)
/** \brief It is used to calculate the random seed*/
#define ACC_UDSFAW_RANDOM_SEED             (16807UL)
#define ACC_UDSFAW_SEED_INITVALUE          (0x12350012UL)
#define ACC_UDSFAW_SEED_TO_BUF(seed,buf)   BL_MCU_TO_BE32(buf,seed)
#elif (SECM_ACCESS_SEED_SIZE == 2u)
/** \brief It is used to calculate the random seed*/
#define ACC_UDSFAW_RANDOM_SEED             (16807u)
#define ACC_UDSFAW_SEED_INITVALUE          (0x1235u)
#define ACC_UDSFAW_SEED_TO_BUF(seed,buf)   BL_MCU_TO_BE16(buf,seed)
#endif

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/
#if (SECM_ACCESS_SEED_SIZE == 4u)
typedef bl_u32_t bl_UdsFawSeed_t;
#elif (SECM_ACCESS_SEED_SIZE == 2u)
typedef bl_u16_t bl_UdsFawSeed_t;
#endif

#if (SECM_ACCESS_KEY_SIZE == 4u)
typedef bl_u32_t bl_UdsFawKey_t;
#elif (SECM_ACCESS_KEY_SIZE == 2u)
typedef bl_u16_t bl_UdsFawKey_t;
#endif

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
/** \brief Calculate the key from the gs_UdsFawSeed.*/
static bl_UdsFawKey_t _Acc_UdsFawCalculateKey(void);

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
static bl_UdsFawSeed_t gs_UdsFawSeed;

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details Initialize the FAW security access used for UDS.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Acc_UdsFawInit(void)
{
    gs_UdsFawSeed = ACC_UDSFAW_SEED_INITVALUE;

    return ;
}

/**************************************************************************//**
 *
 *  \details Make a new seed.
 *
 *  \since  V5.0.0
 *
 *****************************************************************************/
void Acc_UdsFawMakeNewSeed(void)
{
    bl_UdsFawSeed_t UdsFawSeedDummy;

    UdsFawSeedDummy = ((bl_UdsFawSeed_t)g_dummy) << 8u;
    UdsFawSeedDummy |= g_dummy;

    gs_UdsFawSeed *= UdsFawSeedDummy;
    gs_UdsFawSeed += ACC_UDSFAW_RANDOM_SEED;


    if((gs_UdsFawSeed == 0) || (gs_UdsFawSeed == 0xFFFFFFFFUL))
    {
        gs_UdsFawSeed = ACC_UDSFAW_SEED_INITVALUE;
    }

    return ;
}

/**************************************************************************//**
 *
 *  \details Get current seed value.
 *
 *  \param[out]  seed - the value of current seed.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Acc_UdsFawGetSeed(bl_Buffer_t *seed)
{
    ACC_UDSFAW_SEED_TO_BUF(gs_UdsFawSeed,seed);

    return ;
}

static bl_u8_t _Acc_UdsFawCalculateKeyH(void)
{
    bl_u8_t Seed[4];
    bl_u8_t KeyH;
    ACC_UDSFAW_SEED_TO_BUF(gs_UdsFawSeed,Seed);
    KeyH = ((Seed[1] ^0x25)<<1) + 2;
    return KeyH;
}

static bl_u8_t _Acc_UdsFawCalculateKeyL(void)
{
    bl_u8_t Seed[4];
    bl_u8_t KeyL;
    ACC_UDSFAW_SEED_TO_BUF(gs_UdsFawSeed,Seed);
    KeyL = ((Seed[0] & 0x31)>>1) + 5;
    return KeyL;
}
/**************************************************************************
 *
 *  \details Verify the value of transmitted key whether is right.
 *
 *  \param[in]  key - the value of transmitted key.
 *
 *  \return If the transmitted key value is right return BL_ERR_OK, otherwise
 *          return BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the transmitted key value is right.
 *  \retval BL_ERR_NOT_OK - the transmitted key value is NOT right.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
bl_Return_t Acc_UdsFawVerifyKey(const bl_Buffer_t *key)
{
        bl_Return_t ret = BL_ERR_NOT_OK;

        bl_u32_t localKey;
        bl_u32_t RxKey;
        localKey = _Acc_UdsFawCalculateKey();
        RxKey = BL_BE32_TO_MCU(key);
        if(RxKey == localKey)
        {
            ret = BL_ERR_OK;
        }

        return ret;
 }


/**************************************************************************//**
 *
 *  \details An algorithm is used to calculate the key by a seed.
 *
 *  \return the key value
 *
 *  \since V1.0.0
 *
 *****************************************************************************/
static bl_UdsFawKey_t _Acc_UdsFawCalculateKey(void)
{
    bl_UdsFawKey_t key;
    bl_u8_t i;
    bl_u32_t mask = 0xBF868693;
    if(gs_UdsFawSeed !=0)
	{
		for (i=0; i<35; i++)
		{
			if (gs_UdsFawSeed & 0x80000000)
			{
				gs_UdsFawSeed = gs_UdsFawSeed << 1;
				gs_UdsFawSeed = gs_UdsFawSeed ^ mask;
			}
			else
			{
				gs_UdsFawSeed = gs_UdsFawSeed << 1;
			}
		}
		key=gs_UdsFawSeed;
	}

    return key;
}
