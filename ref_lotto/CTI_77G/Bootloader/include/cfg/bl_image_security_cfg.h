/*
 * bl_image_security_cfg.h
 *
 *  Created on: 2018/12/10
 *      Author: WoodLiu
 */

#ifndef CFG_BL_IMAGE_SECURITY_CFG_H_
#define CFG_BL_IMAGE_SECURITY_CFG_H_
#include "bl_image_security.h"
#include "image.h"

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
#define BL_IMAGE_ENCRYPTION             (&image_encryption)
#define BL_IMAGE_DECRYPTION             (&image_decryption)

#define BL_IMAGE_VERIFICATION_INIT      (&ImageChecker_Init)
#define BL_IMAGE_VERIFICATION_START     (&ImageChecker_Start)
#define BL_IMAGE_VERIFICATION_UPDATE    (&ImageChecker_Update)
#define BL_IMAGE_VERIFICATION_VERIFY    (&ImageChecker_Verify)


#endif /* CFG_BL_IMAGE_SECURITY_CFG_H_ */
