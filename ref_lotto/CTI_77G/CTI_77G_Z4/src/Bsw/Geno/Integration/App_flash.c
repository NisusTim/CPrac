/*  BEGIN_FILE_HDR
************************************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information contained in this 
*   doc should not be reproduced, or used, or disclosed without the written authorization from 
*   HiRain Technologies.
************************************************************************************************
*   File Name       : App_flash.c
************************************************************************************************
*   Project/Product : Bootloader
*   Title           : Fls driver module Source File
*   Author          : ning.chen
************************************************************************************************
*   Description     : This module is his flash driver 
*
************************************************************************************************
*   Limitations     : 
*                     
*
************************************************************************************************
*
************************************************************************************************
*   Revision History:
* 
*   Version     Date          Initials      CR#                    Descriptions
*   ---------   ----------    ------------  ----------             ---------------
*   1.0         2013/03/13    ning.chen     N/A                    Original
*   1.0.1       2013/06/07    ning.chen     N/A                    FlashErase add HBS&LMS clear to zero code    
*   1.0.2       2013/10/25    ning.chen     N/A                    FlashErase&FlashWrite add kFlashFailed return code , always clear EHV&PGM&ERS bit                    
************************************************************************************************
* END_FILE_HDR*/
#include "App_flash.h"


static Fls_SectorSlecType __Flash_SectorSelect(bl_Address_t addr);
static void Bl_MemCpy(bl_Buffer_t *des,const bl_Buffer_t *src, bl_Size_t size);

/******************************************************************************
* Flash Description
******************************************************************************/    
static Fls_SectorInfoType gs_FlsSectInfoArray[FLS_SECTOR_MAX_NUM]=
{
	     {DFLS_ADDRESS_START_L0, DFLS_ADDRESS_END_L0, DFLS_SECTOR0_L0, FLASH_LOW_BLOCK},
	     {DFLS_ADDRESS_START_L1, DFLS_ADDRESS_END_L1, DFLS_SECTOR2_L2, FLASH_LOW_BLOCK},
	     {DFLS_ADDRESS_START_L2, DFLS_ADDRESS_END_L2, DFLS_SECTOR1_L1, FLASH_LOW_BLOCK},
	     {DFLS_ADDRESS_START_L3, DFLS_ADDRESS_END_L3, DFLS_SECTOR3_L3, FLASH_LOW_BLOCK},
};
 
/*********************************************************************************************************************/
/* DriverCode                                                                                                        */
/*********************************************************************************************************************/
 void  FlashInit(bl_FlashDrvParam_t* fp)
{
    /* unlock  blocks*/

    /* Enable erass or program */
    WRITE32(FLS_BASE_ADDRESS + C55FMC_C_LOCK0, 0x00000000);
    //WRITE32(FLS_BASE_ADDRESS + C55FMC_C_LOCK1, 0x00000000);
   // WRITE32(FLS_BASE_ADDRESS + C55FMC_C_LOCK2, 0x00000000);
    //WRITE32(FLS_BASE_ADDRESS + C55FMC_C_LOCK3, 0x00000000);

    WRITE32(FLS_BASE_ADDRESS,0);
    
    fp->errCode = BL_ERR_OK;
      
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : FlashDeinit
*
* Description   : Flash moudle deinit 
*
* Inputs        : fp:standard HIS input parameters structure
*
* Outputs       : None
* 
* Limitations   : None
*                 
************************************************************************************************
END_FUNCTION_HDR */
void  FlashDeinit(bl_FlashDrvParam_t* fp)
{
    /*disable erass or program */
    WRITE32(FLS_BASE_ADDRESS + C55FMC_C_LOCK0, 0xFFFFFFFF);
    WRITE32(FLS_BASE_ADDRESS + C55FMC_C_LOCK1, 0xFFFFFFFF);
    WRITE32(FLS_BASE_ADDRESS + C55FMC_C_LOCK2, 0xFFFFFFFF);
    WRITE32(FLS_BASE_ADDRESS + C55FMC_C_LOCK3, 0xFFFFFFFF);

    WRITE32(FLS_BASE_ADDRESS,0);

    fp->errCode = BL_ERR_OK;
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : FlashErase
*
* Description   : Flash moudle erase
*
* Inputs        : fp:standard HIS input parameters structure
*
* Outputs       : None
* 
* Limitations   : erase only 1 sector
*                 
************************************************************************************************
END_FUNCTION_HDR */
void  FlashErase(bl_FlashDrvParam_t* fp)
{
    Fls_SectorSlecType temp;

    /* Check the high voltage operation */
    if (READ32(FLS_BASE_ADDRESS) & (C55FMC_MCR_ERS | C55FMC_MCR_PGM))
    {
        /* If any P/E operation in progress return error */
        fp->errCode = BL_ERR_NOT_OK;
    }
    else if((fp->address < FLASH_START_ADRESS) 
         || (fp->address > FLASH_END_ADRESS))
    {
        /* Address error*/
        fp->errCode = BL_ERR_NOT_OK;
    }
    else
    {
        /* Set MCR ERS bit */
        SET32(FLS_BASE_ADDRESS, C55FMC_MCR_ERS);

        /*Find the erass block num*/
        temp = __Flash_SectorSelect(fp->address);    

        if((temp.Blocktype == FLASH_LOW_BLOCK)
        ||(temp.Blocktype == FLASH_MID_BLOCK))
        {
            WRITE32((FLS_BASE_ADDRESS + C55FMC_C_SEL0), temp.SectorId);
            WRITE32((FLS_BASE_ADDRESS + C55FMC_C_SEL1), 0);
            WRITE32((FLS_BASE_ADDRESS + C55FMC_C_SEL2), 0);
        }	
        if(temp.Blocktype == FLASH_HIGH_BLOCK)
        {
            WRITE32((FLS_BASE_ADDRESS + C55FMC_C_SEL1), ((temp.SectorId)&0xFFFF));
            WRITE32((FLS_BASE_ADDRESS + C55FMC_C_SEL0), 0);
            WRITE32((FLS_BASE_ADDRESS + C55FMC_C_SEL2), 0);
        }	
        if(temp.Blocktype == FLASH_MH_BLOCK)
        {
            WRITE32((FLS_BASE_ADDRESS + C55FMC_C_SEL2), ((temp.SectorId)&0xFFFF));
            WRITE32((FLS_BASE_ADDRESS + C55FMC_C_SEL0), 0);
            WRITE32((FLS_BASE_ADDRESS + C55FMC_C_SEL1), 0);
        }	

        /* Write the block selection registers */
        /* Interlock write */
        WRITE32(fp->address, 0xFFFFFFFF);
        /* Set MCR EHV bit */
        SET32(FLS_BASE_ADDRESS, C55FMC_MCR_EHV);

        while((READ32(FLS_BASE_ADDRESS) & C55FMC_MCR_DONE) != C55FMC_MCR_DONE)
        {
            /*SWT_0.SR.R = 0xA602;
            SWT_0.SR.R = 0xB480;*/
        }

        if(0 == (READ32(FLS_BASE_ADDRESS) & C55FMC_MCR_PEG))
        {
            /* opration failed return error */
            fp->errCode = BL_ERR_NOT_OK;
        }
        else
        {
            fp->errCode = BL_ERR_OK;
        }

        /* Finish the erase operation */
        C55FMC.MCR.B.EHV = 0;       
        C55FMC.MCR.B.ERS = 0;
    }
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : FlashWrite
*
* Description   : Flash moudle write 
*
* Inputs        : fp:standard HIS input parameters structure
*
* Outputs       : None
* 
* Limitations   : write 1 page 
*                 
************************************************************************************************
END_FUNCTION_HDR */
void  FlashWrite(bl_FlashDrvParam_t* fp)
{    
    /* Check the high votage operation */
    if (READ32(FLS_BASE_ADDRESS) & (C55FMC_MCR_ERS | C55FMC_MCR_PGM))
    {
        /* If any P/E operation in progress return error */
        fp->errCode = BL_ERR_NOT_OK;
    }
    else if (((fp->address-0x00F98000) % 8) != 0)
    {
        fp->errCode = BL_ERR_NOT_OK;
    }
    else
    {
        /* Set MCR PGM bit */
        SET32(FLS_BASE_ADDRESS, C55FMC_MCR_PGM);
        WRITE64(fp->address, *((bl_u64_t *)fp->buffer));

        /* Set MCR EHV bit */
        SET32(FLS_BASE_ADDRESS, C55FMC_MCR_EHV);

        while((READ32(FLS_BASE_ADDRESS)&C55FMC_MCR_DONE)!=C55FMC_MCR_DONE)
        {
            /*SWT_0.SR.R = 0xA602;
            SWT_0.SR.R = 0xB480;*/      
        }

        if(0 == (READ32(FLS_BASE_ADDRESS) & C55FMC_MCR_PEG))
        {
            /* opration failed return error */
            fp->errCode = BL_ERR_NOT_OK;
        }
        else
        {
            fp->errCode = BL_ERR_OK;
        }

        /* Finish the erase operation */
        C55FMC.MCR.B.EHV = 0;
        C55FMC.MCR.B.PGM = 0;
    }
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : __Flash_SectorSelect
*
* Description   : Find the erass block num
*
* Inputs        : fp:standard HIS input parameters structure
*
* Outputs       : None
* 
* Limitations   : 
*                 
************************************************************************************************
END_FUNCTION_HDR */
static Fls_SectorSlecType __Flash_SectorSelect(bl_Address_t addr)
{
     bl_u16_t sct;
     Fls_SectorSlecType temp;
     
     for(sct=0; sct<FLS_SECTOR_MAX_NUM; sct++)
     {
         if ((addr >= gs_FlsSectInfoArray[sct].BlockAddressStart) &&
            (addr <= gs_FlsSectInfoArray[sct].BlockAddressEnd))
         {
             temp.SectorId = gs_FlsSectInfoArray[sct].SectorId;
             temp.Blocktype = gs_FlsSectInfoArray[sct].Blocktype;
             break;
         }        
     }
     return temp;
} 
/**************************************************************************//**
 *
 *  \details Read the data from the flash device by the flash driver.
 *
 *  \param[in]  address - the memory address of the data to be read from.
 *  \param[in]  size    - the size of the data to be read.
 *  \param[out] buffer  - the saving address pointer of the data to be read.
 *
 *  \return If the data is read successfully returns BL_ERR_OK,
 *          otherwise returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK     - read data successfully.
 *  \retval BL_ERR_NOT_OK - read data unsuccessfully.
 *
 *  \note   if the FLASHIF_FUN_SPECIAL_READ is ON, the flash driver supply the
 *          special read interface.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Flash_Read(bl_Address_t address,
                       bl_Size_t size,
                       bl_Buffer_t *buffer)
{
    Bl_MemCpy(buffer, (const bl_Buffer_t *)address, size);
}

/**************************************************************************//**
 *
 *  \details Copy the data from src to des.
 *
 *  \param[out] des  - the destination address.
 *  \param[in]  src  - the source address.
 *  \param[in]  size - the size of the data.
 *
 *  \since V1.0.0
 *
 *****************************************************************************/
static void Bl_MemCpy(bl_Buffer_t *des,const bl_Buffer_t *src, bl_Size_t size)
{
    bl_u32_t i;
	
	if (des != src)
    {
		for (i = 0; i < size; i++)
		{
			des[i] = src[i];
		}
    }

}



