/*
 * version.h
 *
 *  Created on: 2019/10/16
 *      Author: WoodLiu
 */

#ifndef VERSION_H_
#define VERSION_H_

#include "bl_typedefs.h"
#include "customer.h"
/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
#define PROJECT_CODE            "93G003"
#define DEFAULT_BL_NUMBER       "B005"

#define REV_MAJOR           3
#define DEFAULT_REV_PROD    0
#define DEFAULT_REV_CUSID   DEFAULT_CUSTOMER_ID
#define REV_MINOR           4
#define DEFAULT_REV_BUILD   REV_BUILD_RELEASE
#define REV_MAINTENANCE     0
#define REV_SVN             0

#define LENGTH_OF_BL_VERSION		(16)

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/
typedef enum {
	REV_BUILD_ALPHA=0,
	REV_BUILD_BETA,
	REV_BUILD_RELEASE
}REV_BUILD_E;


/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/
typedef struct {
	bl_u16_t	svn;
	bl_u16_t	minor;
	bl_u8_t		product;
	bl_u8_t		major;
	bl_u8_t		cusid;
	bl_u8_t		build:2;
	bl_u8_t		maintenance:6;
}bl_revision_t,*bl_revision_p;

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
extern void version_init();
extern char* get_bl_number();
extern char* get_bl_version();
extern const bl_revision_p get_bl_revision();

#endif /* VERSION_H_ */
