/*
 * bl_image_security.h
 *
 *  Created on: 2018/12/10
 *      Author: WoodLiu
 */

#ifndef INC_BL_IMAGE_SECURITY_H_
#define INC_BL_IMAGE_SECURITY_H_

#include <cstdint>

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

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/
struct _tag_ImgSec_Ops
{
	void (*encryption)(uint32_t addr, uint8_t *buf, uint16_t len);
	void (*decryption)(uint32_t addr, uint8_t *buf, uint16_t len);
};

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/
extern const bl_ImgSec_Ops_t g_ImgSecOps;


/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
extern void image_encryption(uint32_t addr, uint8_t *buf, uint16_t len);
extern void image_decryption(uint32_t addr, uint8_t *buf, uint16_t len);

#endif /* INC_BL_IMAGE_SECURITY_H_ */
