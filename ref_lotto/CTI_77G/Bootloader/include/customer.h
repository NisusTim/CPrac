/*
 * customer.h
 *
 *  Created on: 2020/01/30
 *      Author: WoodLiu
 */

#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "customer_code.h"

#define CUSTOM_ID_HIRAIN_FAW    0U  /* Customer Hirain-FAW */
#define CUSTOM_ID_NEUSOFT       1U  /* Customer Neusoft */
#define CUSTOM_ID_AM            2U  /* Customer AM (CubTEK default) */
#define CUSTOM_ID_HIRAIN_CNHTC  3U  /* Customer Hirain-CNHTC */
#define CUSTOM_ID_TS            4U  /* Customer TSINTEL-CNHTC */
#define CUSTOM_ID_INVALID       5U

/*==============================================*
 *                                              *
 *               Customer id                    *
 *                                              *
 *==============================================*/
#ifdef OPTION_CUSTOMER_ID
    #define DEFAULT_CUSTOMER_ID OPTION_CUSTOMER_ID
#else
    #define DEFAULT_CUSTOMER_ID CUSTOM_ID_HIRAIN_FAW
#endif

/*==============================================*
 *                                              *
 *              Customer code                   *
 *                                              *
 *==============================================*/
#if (DEFAULT_CUSTOMER_ID == CUSTOM_ID_HIRAIN_FAW)
    #define CUSTOMER_CODE   CUSTOMER_HIRAIN_CODE
#elif (DEFAULT_CUSTOMER_ID == CUSTOM_ID_NEUSOFT)
    #define CUSTOMER_CODE   CUSTOMER_NEUSOFT_CODE
#elif (DEFAULT_CUSTOMER_ID == CUSTOM_ID_HIRAIN_CNHTC)
    #define CUSTOMER_CODE   CUSTOMER_HIRAIN_CNHTC_CODE
#elif (DEFAULT_CUSTOMER_ID == CUSTOM_ID_TS)
    #define CUSTOMER_CODE   CUSTOMER_TSINTEL_CODE
#else
    #define CUSTOMER_CODE   CUSTOMER_HIRAIN_CODE
#endif

#endif /* CUSTOMER_H_ */
