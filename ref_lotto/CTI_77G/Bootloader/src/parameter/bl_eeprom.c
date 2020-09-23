/*
 * eeprom.c
 *
 *  Created on: 2017¦~10¤ë31¤é
 *      Author: erichu
 */

#include <bl_eeprom.h>
#include <stdio.h>

#include "console.h"
#include "FS8x\sbc_fs8x.h"

typedef struct {
	bl_u32_t		addr;
	bl_u32_t		lock;
	bl_u32_t		sel;
} eeprom_priv_t, *eeprom_priv_p;

const eeprom_priv_t eeprom_privs[]={
		{EE_MEM_BLOCK_0, 0xBFFEFFFF, 0x00010000},
		{EE_MEM_BLOCK_1, 0xBFFBFFFF, 0x00040000},
		{EE_MEM_BLOCK_2, 0xBFFDFFFF, 0x00020000},
		{EE_MEM_BLOCK_3, 0xBFF7FFFF, 0x00080000},
		{0x000000, 0, 0}};

////////////////////////////////////////////////////////////////////////////////
//
//  parameters eeprom hal layer
//
///////////////////////////////////////////////////////////////////////////////
static eeprom_priv_p eeprom_priv_get(bl_u32_t addr)
{
	const eeprom_priv_t *priv=eeprom_privs;
	while(priv->addr > 0){
		if(addr >= priv->addr && addr < (priv->addr+SIZE_OF_EE_MEM_BLOCK)){
			return (eeprom_priv_p)priv;
		}
		priv++;
	}

	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//  Function      eeprom_erase
////////////////////////////////////////////////////////////////////////////////
void eeprom_erase(bl_u32_t addr)
{
	eeprom_priv_p priv = eeprom_priv_get(addr);
#if (CONSOLE_ENABLE == CONSOLE_ON)
	PRINTF("ee: erase %08lX %08lX %08lX\n", addr, priv->lock, priv->sel);
#endif
	C55FMC.LOCK0.R = priv->lock;          // Unlock block

	C55FMC.MCR.B.ERS = 1;               	// Enable Erase
	C55FMC.SEL0.R = priv->sel;            // Select block for erasing
	*(bl_u64_t*)priv->addr = 0xFFFFFFFFFFFFFFFF; // Do an inter lock write (necessary)

	C55FMC.MCR.B.EHV = 1;                 // Start internal erase sequence
	while( C55FMC.MCR.B.DONE == 0 );      // Wait until done

	C55FMC.MCR.B.PEG = 1;
	C55FMC.MCR.B.EHV = 0;               // Disable high voltage
	C55FMC.MCR.B.ERS = 0;               // End erasing

	C55FMC.LOCK0.R = 0xBFFFFFFF;        // Lock block
	C55FMC.SEL0.R  = 0x00000000;        // Deselect block for erasing
}

////////////////////////////////////////////////////////////////////////////////
//  Function      flash_eeprom_write
////////////////////////////////////////////////////////////////////////////////
void eeprom_write(bl_u32_t pDest, void* pSrc, uint16_t len ){
	bl_u64_t *pOut, *pIn;
	uint16_t i, lpcnt=len/EEPROM_PAGE_SIZE;

	eeprom_priv_p priv=eeprom_priv_get(pDest);

	//PRINTF("ee: wr %lX %p %X\n", pDest, pSrc, len);
	C55FMC.MCR.B.PEAS = 0;

	C55FMC.LOCK0.R = priv->lock;        		// Unlock block
	*(bl_u64_t*)priv->addr = 0xFFFFFFFFFFFFFFFF; // Do an inter lock write (necessary)

	C55FMC.MCR.B.PGM = 1;              			// Enable Programming

	// Data must be aligned to 64bit
	pOut = (bl_u64_t*)pDest;
	pIn = (bl_u64_t*)pSrc;

	if(len&(EEPROM_PAGE_SIZE-1))
		lpcnt++;

	len = 0;
	while(len < lpcnt) {
		#ifdef ENABLE_SWT
		clear_SWT0_counter();
	  	#endif
		SWT_0.SR.R = 0xA602;
		SWT_0.SR.R = 0xB480;
		FS8x_Feed();
		for(i=0;i<(EEPROM_PAGE_SIZE/sizeof(bl_u64_t));i++)
			*pOut++ = *pIn++;           // Save data

		C55FMC.MCR.B.EHV = 1;           // Start programming
		while( C55FMC.MCR.B.DONE == 0 );// Wait until done

		C55FMC.MCR.B.EHV = 0;           // Disable high voltage
		len++;

#if (CONSOLE_ENABLE == CONSOLE_ON)
		if(C55FMC.MCR.B.PEG == 0)
			PRINTF("ee: err %p!\n", pOut);
#endif
	}

	C55FMC.MCR.B.PGM = 0;               // End programming

	C55FMC.LOCK0.R = 0xBFFFFFFF;        // Lock block
}


////////////////////////////////////////////////////////////////////////////////
//  Function      eeprom__write
////////////////////////////////////////////////////////////////////////////////
void eeprom_write64(bl_u32_t dest, bl_u64_t data){
	  eeprom_priv_p priv=eeprom_priv_get(dest);

	  //PRINTF("ee: wr64 %lx %llx %llx\n", dest, *(bl_u64_t*)dest, data);
	  C55FMC.MCR.B.PEAS = 0;
	  C55FMC.LOCK0.R = priv->lock;        // Unlock block

	  *(bl_u64_t*)(priv->addr) = 0xFFFFFFFFFFFFFFFF;  // Do an inter lock write (necessary)

	  C55FMC.MCR.B.PGM = 1;               // Enable Programming

	  *(bl_u64_t*)dest = data;           // Save data

	  C55FMC.MCR.B.EHV = 1;           // Start programming
	  while( C55FMC.MCR.B.DONE == 0 );// Wait until done

	  C55FMC.MCR.B.EHV = 0;           // Disable high voltage

	  if(C55FMC.MCR.B.PEG == 0 || C55FMC.MCR.B.RWE == 1){
		  C55FMC.MCR.B.RWE = 0;
#if (CONSOLE_ENABLE == CONSOLE_ON)
		  PRINTF("ee: 64 pgm err %lx!\n", dest);
#endif
	  }

	  C55FMC.MCR.B.PGM = 0;
	  C55FMC.LOCK0.R = 0xBFFFFFFF;        // Lock block

	  return;
}

#if (CONSOLE_ENABLE == CONSOLE_ON)
void ee_tester(char** args, int count)
{
	bl_u32_t addr = strtoul(args[2], NULL, 16);
	if(!strncmp(args[1], "erase", 5)){
		eeprom_erase(addr);
	}
	else if(!strncmp(args[1], "write", 5) && count >= 5){
		bl_u32_t src = strtoul(args[3], NULL, 16);
		count = strtoul(args[4], NULL, 16);
		eeprom_write(addr, (void*)src, count);
	}
	else if(!strncmp(args[1], "wr64", 4) && count >= 4){
		bl_u64_t data = strtoll(args[3], NULL, 16);
		eeprom_write64(addr, data);
	}
}
#endif


