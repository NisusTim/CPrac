/*
 * bl_image_security.h
 *
 *  Created on: 2018/12/10
 *      Author: WoodLiu
 */

#ifndef INC_BL_IMAGE_SECURITY_H_
#define INC_BL_IMAGE_SECURITY_H_

#include "bl_typedefs.h"

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
#define BL_IMAGE_Z4_START_ADDR				(0x01000000UL)
#define BL_IMAGE_SECURITY_START_ADDR		(0x01000080UL)
#define BL_IMAGE_SECURITY_END_ADDR			(0x0117FFFFUL)

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/
typedef struct _tag_ImgSec_Ops bl_ImgSec_Ops_t;
typedef struct _tag_ImgVer_Ops bl_ImgVer_Ops_t;

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/
struct _tag_ImgSec_Ops
{
	void (*encryption)(bl_Address_t addr, bl_Buffer_t *buf, bl_BufferSize_t len);
	void (*decryption)(bl_Address_t addr, bl_Buffer_t *buf, bl_BufferSize_t len);
};

struct _tag_ImgVer_Ops
{
    void (*Init)(void);/**< init interface.*/
    void (*Start)(void); /**< start interface.*/
    bl_Return_t (*Update)(bl_Address_t addr, bl_Size_t size, const bl_Buffer_t *data);
    bl_Return_t (*Verify)(void);
};

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/
extern const bl_ImgSec_Ops_t g_ImgSecOps;
extern const bl_ImgVer_Ops_t g_ImgVerOps;


/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
extern void image_encryption(bl_Address_t addr, bl_Buffer_t *buf, bl_BufferSize_t len);
extern void image_decryption(bl_Address_t addr, bl_Buffer_t *buf, bl_BufferSize_t len);

extern void Image_ChecksumInit(void);
extern void Image_StartChecksum(void);
extern bl_Return_t Image_UpdateChecksum(bl_Address_t addr, bl_Size_t size, const bl_Buffer_t *data);
extern bl_Return_t Image_VerifyChecksum(void);

#endif /* INC_BL_IMAGE_SECURITY_H_ */
