/*
 * image.c
 *
 *  Created on: 2019/11/8
 *      Author: WoodLiu
 */


#include "image.h"
#include "Null.h"

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
#define IMAGE_CHECKER_CHECKSUM_INIT_VALUE   0xFFFFFFFF
#define IMAGE_CHECKER_CHECKSUM_START_VALUE  0x00000000

#define BL_IMAGE_CHECKER_INIT           0
#define BL_IMAGE_CHECKER_START          1
#define BL_IMAGE_CHECKER_UPDATING       2
#define BL_IMAGE_CHECKER_VERIFING       3

#define IMGNO_BLDR  0
#define IMGNO_Z70   1
#define IMGNO_Z71   2
#define IMGNO_Z4    3
#define IMGS_COUNT  4

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/
typedef struct {
    bl_image_header_p   header;
    bl_u32_t            checksum;
    bl_u8_t             state;
}bl_image_checker, *bl_image_checker_p;

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
static void _update_checksum(bl_u32_t *checksum, bl_Size_t size, const bl_Buffer_t *data);
/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
static bl_image_checker z40_checker = {NULL, IMAGE_CHECKER_CHECKSUM_INIT_VALUE, BL_IMAGE_CHECKER_INIT};
static bl_image_checker z70_checker = {NULL, IMAGE_CHECKER_CHECKSUM_INIT_VALUE, BL_IMAGE_CHECKER_INIT};
static bl_image_checker z71_checker = {NULL, IMAGE_CHECKER_CHECKSUM_INIT_VALUE, BL_IMAGE_CHECKER_INIT};

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details Initialize the image checksum algorithm.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void ImageChecker_Init(void)
{
    z40_checker.header      = NULL;
    z70_checker.header      = NULL;
    z71_checker.header      = NULL;

    z40_checker.checksum    = IMAGE_CHECKER_CHECKSUM_INIT_VALUE;
    z70_checker.checksum    = IMAGE_CHECKER_CHECKSUM_INIT_VALUE;
    z71_checker.checksum    = IMAGE_CHECKER_CHECKSUM_INIT_VALUE;

    z40_checker.state       = BL_IMAGE_CHECKER_INIT;
    z70_checker.state       = BL_IMAGE_CHECKER_INIT;
    z71_checker.state       = BL_IMAGE_CHECKER_INIT;
}

/**************************************************************************//**
 *
 *  \details Start the image checksum algorithm.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void ImageChecker_Start(void)
{
    z40_checker.header = (bl_image_header_p)IMAGE_ADDR_Z4;
    z70_checker.header = (bl_image_header_p)z40_checker.header->addrs[IMGNO_Z70];
    z71_checker.header = (bl_image_header_p)z40_checker.header->addrs[IMGNO_Z71];

    if(z40_checker.header->magic == (CUBTEK_IMG_MAGIC | 0x40))
    {// Z40 header correct
        z40_checker.checksum    = IMAGE_CHECKER_CHECKSUM_START_VALUE;
        z40_checker.state       = BL_IMAGE_CHECKER_START;
    }

    if(z70_checker.header->magic == (CUBTEK_IMG_MAGIC | 0x70))
    {// Z70 header correct
        z70_checker.checksum    = IMAGE_CHECKER_CHECKSUM_START_VALUE;
        z70_checker.state       = BL_IMAGE_CHECKER_START;
    }

    if(z71_checker.header->magic == (CUBTEK_IMG_MAGIC | 0x71))
    {// Z71 header correct
        z71_checker.checksum    = IMAGE_CHECKER_CHECKSUM_START_VALUE;
        z71_checker.state       = BL_IMAGE_CHECKER_START;
    }
}

/**************************************************************************//**
 *
 *  \details Update the checksum value.
 *
 *  \param[in]  addr - the address of data
 *  \param[in]  size - the size of data.
 *  \param[in]  data - the value of data.
 *
 *  \return If the checksum value is calculated successfully return BL_ERR_OK,
 *          otherwise checksum value BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the checksum value is calculated successfully.
 *  \retval BL_ERR_NOT_OK - the checksum value is not calculated successfully.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
bl_Return_t ImageChecker_Update(bl_Address_t addr, bl_Size_t size, const bl_Buffer_t *data)
{
    if((addr >= (bl_Address_t)z40_checker.header) && (addr + size - 1) < (bl_Address_t)z40_checker.header->end)
    {// Z40 location
        _update_checksum(&z40_checker.checksum, size, data);
        z40_checker.state = BL_IMAGE_CHECKER_UPDATING;
    }
    else if((addr >= (bl_Address_t)z70_checker.header) && (addr + size - 1) < (bl_Address_t)z70_checker.header->end)
    {// Z70 location
        _update_checksum(&z70_checker.checksum, size, data);
        z70_checker.state = BL_IMAGE_CHECKER_UPDATING;
    }
    else if((addr >= (bl_Address_t)z71_checker.header) && (addr + size - 1) < (bl_Address_t)z71_checker.header->end)
    {// Z71 location
        _update_checksum(&z71_checker.checksum, size, data);
        z71_checker.state = BL_IMAGE_CHECKER_UPDATING;
    }
    else
    {
        return BL_ERR_NOT_OK;
    }

    return BL_ERR_OK;
}

/**************************************************************************//**
 *
 *  \details The algorithm to verify the checksum value.
 *
 *
 *  \return If the checksum value is right return BL_ERR_OK, otherwise return
 *          BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the checksum value is right.
 *  \retval BL_ERR_NOT_OK - the checksum value is NOT right.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
bl_Return_t ImageChecker_Verify(void)
{
    bl_Return_t ret = BL_ERR_NOT_OK;

    if(BL_IMAGE_CHECKER_UPDATING == z40_checker.state)
    {
        z40_checker.state = BL_IMAGE_CHECKER_VERIFING;
    }

    if(BL_IMAGE_CHECKER_UPDATING == z70_checker.state)
    {
        z70_checker.state = BL_IMAGE_CHECKER_VERIFING;
    }

    if(BL_IMAGE_CHECKER_UPDATING == z71_checker.state)
    {
        z71_checker.state = BL_IMAGE_CHECKER_VERIFING;
    }

    if(z40_checker.checksum || z70_checker.checksum || z71_checker.checksum)
    {
        ret = BL_ERR_NOT_OK;
    }
    else
    {
        //If the checksum is valid, then the checksum value should be 0
        ret = BL_ERR_OK;
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Calculate the checksum.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
static void _update_checksum(bl_u32_t *output, bl_Size_t size, const bl_Buffer_t *data)
{
    bl_u32_t *data_u32 = (bl_u32_t*)data;
    bl_u32_t checksum = 0;

    while(size > 0)
    {
        checksum += *data_u32;

        data_u32++;

        if(size < 4)
        {
            size = 0;
        }
        else
        {
            size = size - sizeof(bl_u32_t);
        }
    }

    *output += checksum;
}
