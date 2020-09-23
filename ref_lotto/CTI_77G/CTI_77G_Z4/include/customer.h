/*
 * customer.h
 *
 *  Created on: Feb 4, 2018
 *      Author: erichu
 */

#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "customer_code.h"

//#define ENABLE_FUSION

#define ENABLE_BSW_UDS_NM
#ifdef ENABLE_BSW_UDS_NM
    #define USING_UDS_NM_CAN_0
#else
    #define USING_CUBTEK_CAN_0
#endif

#define CUSTOM_ID_HIRAIN_FAW    0U  /* Customer Hirain-FAW */
#define CUSTOM_ID_NEUSOFT       1U  /* Customer Neusoft */
#define CUSTOM_ID_AM            2U  /* Customer AM (CubTEK default) */
#define CUSTOM_ID_HIRAIN_CNHTC  3U  /* Customer Hirain-CNHTC */
#define CUSTOM_ID_TS            4U  /* Customer TSINTEL-CNHTC */
#define CUSTOM_ID_INVALID       5U

#define ISOTP_EN                1
#define JSON_LIST_EN            1

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


/*==============================================*
 *                                              *
 *          Progress bar function               *
 *                                              *
 *==============================================*/
typedef enum {
    PB_BY_CUSTOMER = 0,     // Progress bar enable by customer
    PB_DISABLE  = 1,        // Progress bar disable
    PB_ENABLE  = 2,         // Progress bar enable
    PB_INVALID = 3
} progress_bar_t;

#if (DEFAULT_CUSTOMER_ID == CUSTOM_ID_HIRAIN_FAW)
    #define CUSTOMER_DEFAULT_PB_FUNCTION    PB_DISABLE
#elif (DEFAULT_CUSTOMER_ID == CUSTOM_ID_NEUSOFT)
    #define CUSTOMER_DEFAULT_PB_FUNCTION    PB_ENABLE
#elif (DEFAULT_CUSTOMER_ID == CUSTOM_ID_HIRAIN_CNHTC)
    #define CUSTOMER_DEFAULT_PB_FUNCTION    PB_ENABLE
#elif (DEFAULT_CUSTOMER_ID == CUSTOM_ID_TS)
    #define CUSTOMER_DEFAULT_PB_FUNCTION    PB_ENABLE
#else
    #define CUSTOMER_DEFAULT_PB_FUNCTION    PB_ENABLE
#endif

/*==============================================*
 *                                              *
 *        Auto Detection function               *
 *                                              *
 *==============================================*/
typedef enum {
    AD_BY_CUSTOMER = 0,     // Autodetection enable by customer
    AD_DISABLE  = 1,        // Autodetection disable
    AD_ENABLE  = 2,         // Autodetection enable
    AD_INVALID = 3
}ad_en_status;

#if (DEFAULT_CUSTOMER_ID == CUSTOM_ID_HIRAIN_FAW)
    #define CUSTOMER_DEFAULT_AD_FUNCTION    AD_DISABLE
#elif (DEFAULT_CUSTOMER_ID == CUSTOM_ID_NEUSOFT)
    #define CUSTOMER_DEFAULT_AD_FUNCTION    AD_DISABLE
#elif (DEFAULT_CUSTOMER_ID == CUSTOM_ID_HIRAIN_CNHTC)
    #define CUSTOMER_DEFAULT_AD_FUNCTION    AD_ENABLE
#elif (DEFAULT_CUSTOMER_ID == CUSTOM_ID_TS)
    #define CUSTOMER_DEFAULT_AD_FUNCTION    AD_DISABLE
#else
    #define CUSTOMER_DEFAULT_AD_FUNCTION    AD_DISABLE
#endif

void customer_init(void);
const char* customer_name_get(uint8_t);

void upd_hw_number_get(char *num);
void upd_hw_version_get(char *ver);
void upd_sw_number_get(char *num);
void upd_sw_version_get(char *ver);

#endif /* CUSTOMER_H_ */
