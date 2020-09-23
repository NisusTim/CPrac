/*
 * lib_version.h
 *
 *  Created on: 2020/01/22
 *      Author: Jack Lee
 */

#ifndef LIB_VERSION_H_
#define LIB_VERSION_H_

#include "typedefs.h"

/*******************************************************************************
* LIB_VERSION usage definitions
*******************************************************************************/
#define Z4_LIB_VER_START_ADDR 	0x01000050	//this must match  Z4.ld lib_ver adders
#define Z70_LIB_VER_START_ADDR	0x010C0050	//this must match Z70.ld lib_ver adders
#define Z71_LIB_VER_START_ADDR	0x01140050	//this must match Z71.ld lib_ver adders
#define SIZEOF_LIB_VER_SECTIONS 0x30        //size of library version sections

#define VER_ID(LIB_ID)						((uint8_t)LIB_ID)
#define VER_MINOR(LIB_MINOR)				((uint16_t)LIB_MINOR)
#define VER_MAJOR(LIB_MAJOR)				((uint8_t)LIB_MAJOR)
#define VER_BUILD(LIB_BUILD)				((uint8_t)LIB_BUILD)
#define VER_MAINTENANCE(LIB_MAINTENANCE)	((uint8_t)LIB_MAINTENANCE)

typedef enum {
	Lib_BUILD_ALPHA=0,		//
	Lib_BUILD_BETA,
	Lib_BUILD_RELEASE
}LIB_BUILD_E;

typedef enum lib_version_list
{
	SYS_HAL_LIB_VER,		//0
	DETECTION_LIB_VER,		//1
	DOLPHIN_LIB_VER,		//2
	MEAS_LIB_VER,			//3
	TRACK_LIB_VER,			//4
	LIB_VER_INVAILD = 7
}LIB_VERSION_E;

typedef struct {
	uint8_t		id;
	uint16_t	minor;
	uint8_t		major;
	uint8_t		build:2;
	uint8_t		maintenance:6;
}LIBS_VER_T,*LIBS_VER_P;

void lib_ver_init(void);
LIBS_VER_P get_lib_ver(LIB_VERSION_E);
void dump_lib_ver(LIB_VERSION_E, char*);

#endif /* LIB_VER_H_ */
