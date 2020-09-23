/*
 * bl_image_security_cfg.c
 *
 *  Created on: 2018/12/10
 *      Author: WoodLiu
 */

#include "bl_image_security_cfg.h"

const bl_ImgSec_Ops_t g_ImgSecOps =
{
	BL_IMAGE_ENCRYPTION,
	BL_IMAGE_DECRYPTION
};


const bl_ImgVer_Ops_t g_ImgVerOps =
{
    BL_IMAGE_VERIFICATION_INIT,
    BL_IMAGE_VERIFICATION_START,
    BL_IMAGE_VERIFICATION_UPDATE,
    BL_IMAGE_VERIFICATION_VERIFY
};
