/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a source file to make seed and verify a key.
 *
 *  \file       bl_access_uds.c
 *  \ingroup    security_manager_module
 *  \author     xin.shang <xin.shang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      01.00.00 | 25/03/2010 | hewei.zhang      | N/A | Boot010001
 *      01.01.00 | 19/05/2010 | hewei.zhang      | N/A | Boot010002
 *      05.00.00 | 19/06/2013 | xin.shang        | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#include "bl_common.h"
#include "bl_security_funcfg.h"
#include "bl_access_uds.h"
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
 * ACC_UDS_KEY_FROM_BUF and ACC_UDS_SEED_TO_BUF are not explicit cast.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
 * Acc_UdsGetSeed, the seed will be modify.
 * Acc_UdsVerifyKey, the key is declared with const.
 *
 * MISRA-C:2004 19.7(3453):A function could probably be used instead of this
 * function-like macro.
 * ACC_UDS_KEY_FROM_BUF macro do not have side-effect.
 * ACC_UDS_SEED_TO_BUF macro do not have side-effect.
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
#define ACC_UDS_KEY_MASK                (0xA5CEFDB6UL)
#define ACC_UDS_KEY_FROM_BUF(buf)       BL_BE32_TO_MCU(buf)
#elif (SECM_ACCESS_KEY_SIZE == 2u)
#define ACC_UDS_KEY_MASK                (0xDFB6u)
#define ACC_UDS_KEY_FROM_BUF(buf)       BL_BE16_TO_MCU(buf)
#endif

#if (SECM_ACCESS_SEED_SIZE == 4u)
/** \brief It is used to calculate the random seed*/
#define ACC_UDS_RANDOM_SEED             (16807UL)
#define ACC_UDS_SEED_INITVALUE          (0x12350012UL)
#define ACC_UDS_SEED_TO_BUF(seed,buf)   BL_MCU_TO_BE32(buf,seed)
#elif (SECM_ACCESS_SEED_SIZE == 2u)
/** \brief It is used to calculate the random seed*/
#define ACC_UDS_RANDOM_SEED             (16807u)
#define ACC_UDS_SEED_INITVALUE          (0x1235u)
#define ACC_UDS_SEED_TO_BUF(seed,buf)   BL_MCU_TO_BE16(buf,seed)
#endif

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/
#if (SECM_ACCESS_SEED_SIZE == 4u)
typedef bl_u32_t bl_UdsSeed_t;
#elif (SECM_ACCESS_SEED_SIZE == 2u)
typedef bl_u16_t bl_UdsSeed_t;
#endif

#if (SECM_ACCESS_KEY_SIZE == 4u)
typedef bl_u32_t bl_UdsKey_t;
#elif (SECM_ACCESS_KEY_SIZE == 2u)
typedef bl_u16_t bl_UdsKey_t;
#endif

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
/** \brief Calculate the key from the gs_UdsSeed.*/
static bl_UdsKey_t _Acc_UdsCalculateKey(void);
static bl_UdsKey_t _Acc_UdsCalculateHirainKey(void);
static bl_UdsKey_t _Acc_UdsCalculateNeusoftKey(void);
static bl_UdsKey_t _Acc_UdsCalculateTsintelKey(void);

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
static bl_UdsSeed_t gs_UdsSeed;

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details Initialize the  security access used for UDS.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Acc_UdsInit(void)
{
    gs_UdsSeed = ACC_UDS_SEED_INITVALUE;

    return ;
}

/**************************************************************************//**
 *
 *  \details Make a new seed.
 *
 *  \since  V5.0.0
 *
 *****************************************************************************/
void Acc_UdsMakeNewSeed(void)
{
    bl_UdsSeed_t UdsSeedDummy;

    UdsSeedDummy = ((bl_UdsSeed_t)g_dummy) << 8u;
    UdsSeedDummy |= g_dummy;

    gs_UdsSeed *= UdsSeedDummy;
    gs_UdsSeed += ACC_UDS_RANDOM_SEED;


    if((gs_UdsSeed == 0) || (gs_UdsSeed == 0xFFFFFFFFUL))
    {
        gs_UdsSeed = ACC_UDS_SEED_INITVALUE;
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
void Acc_UdsGetSeed(bl_Buffer_t *seed)
{
    ACC_UDS_SEED_TO_BUF(gs_UdsSeed,seed);

    return ;
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
bl_Return_t Acc_UdsVerifyKey(const bl_Buffer_t *key)
{
        bl_Return_t ret = BL_ERR_NOT_OK;

        bl_u32_t localKey;
        bl_u32_t RxKey;
        localKey = _Acc_UdsCalculateKey();
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
static bl_UdsKey_t _Acc_UdsCalculateKey(void)
{
    bl_UdsKey_t key = 0;

    if(g_dummy_for_security == 0x7a0)
    {
        key = _Acc_UdsCalculateHirainKey();
    }
    else if(g_dummy_for_security == 0x7b0)
    {
        key = _Acc_UdsCalculateNeusoftKey();
    }
    else if(g_dummy_for_security == 0x7c1)
    {
        key = _Acc_UdsCalculateTsintelKey();
    }

    return key;
}

static bl_UdsKey_t _Acc_UdsCalculateHirainKey(void)
{
    bl_UdsKey_t key;
    bl_u8_t i;
    bl_u32_t mask = 0xBF868693;
    if(gs_UdsSeed !=0)
    {
        for (i=0; i<35; i++)
        {
            if (gs_UdsSeed & 0x80000000)
            {
                gs_UdsSeed = gs_UdsSeed << 1;
                gs_UdsSeed = gs_UdsSeed ^ mask;
            }
            else
            {
                gs_UdsSeed = gs_UdsSeed << 1;
            }
        }
        key=gs_UdsSeed;
    }

    return key;
}

static bl_UdsKey_t _Acc_UdsCalculateNeusoftKey(void)
{
    bl_UdsKey_t key;
    bl_u8_t i;
    bl_u32_t mask = 0x9B8DB46C;

    if(gs_UdsSeed !=0)
    {
        for (i=0; i<32; i++)
        {
            if (gs_UdsSeed & 0x40000000)
            {
                gs_UdsSeed = gs_UdsSeed << 1;
                gs_UdsSeed = ~gs_UdsSeed;
                gs_UdsSeed = gs_UdsSeed ^ mask;
            }
            else
            {
                gs_UdsSeed = gs_UdsSeed << 1;
            }
        }
        key=gs_UdsSeed;
    }

    return key;
}

static bl_UdsKey_t _Acc_UdsCalculateTsintelKey(void)
{
    bl_UdsKey_t key;
    bl_u8_t i;
    bl_u32_t mask = 0x45B4B5B9;

    if(gs_UdsSeed !=0)
    {
        for (i=0; i<36; i++)
        {
            if (gs_UdsSeed & 0x08000000)
            {
                gs_UdsSeed = gs_UdsSeed << 1;
                gs_UdsSeed = ~gs_UdsSeed;
                gs_UdsSeed = gs_UdsSeed ^ mask;
            }
            else
            {
                gs_UdsSeed = gs_UdsSeed << 1;
            }
        }
        key=gs_UdsSeed;
    }

    return key;
}


