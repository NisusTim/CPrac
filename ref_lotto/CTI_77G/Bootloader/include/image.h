/*
 * image.h
 *
 *  Created on: 2019/11/6
 *      Author: WoodLiu
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "bl_typedefs.h"
#include "version.h"

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
#define IMGE_ADDR_BLDR      0x00F98000
#define IMAGE_ADDR_Z4       0x01000000
#define IMAGE_ADDR_Z70      0x010C0000
#define IMAGE_ADDR_Z71      0x01140000

#define CUBTEK_IMG_MAGIC    0x68BEEF00

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/
/*cubtek image header define*/
typedef struct {
    bl_u32_t        rchw1;
    bl_u32_t        rchw2;
    bl_u32_t        checksum;
    bl_u32_t        magic;
    bl_u32_t        addrs[3];   //0: Bootloader, 1:Z70, 2:Z71
    bl_u32_t        end;
    bl_revision_t   rev;
    char            rv[8];
    char            rd[16];
    bl_u32_t        key;
}bl_image_header_t, *bl_image_header_p;

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
extern void ImageChecker_Init(void);
extern void ImageChecker_Start(void);
extern bl_Return_t ImageChecker_Update(bl_Address_t addr, bl_Size_t size, const bl_Buffer_t *data);
extern bl_Return_t ImageChecker_Verify(void);


#endif /* IMAGE_H_ */
