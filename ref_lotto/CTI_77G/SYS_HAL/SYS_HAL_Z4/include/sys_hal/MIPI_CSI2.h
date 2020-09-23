/*
 * MIPI_CSI2.h
 *
 *  Created on: 2016¦~12¤ë8¤é
 *      Author: user
 */

#ifndef MIPI_CSI2_H_
#define MIPI_CSI2_H_

#include "typedefs.h"

/*******************************************************************************
* MIPI usage definitions
*******************************************************************************/
typedef enum mipi_num_lanes
{
      MIPI_LANE1,
      MIPI_LANE2,
      MIPI_LANE3,
      MIPI_LANE4
}mipi_num_lanes_t;

typedef enum mipi_data_rate
{
	  MBITS_480,
      MBITS_240,
      MBITS_120
}mipi_data_rate_t;


#define MIPI_NUM_LANES          4                   // number of MIPI lanes: 1, 2 or 4
#define MIPI_DATA_RATE          MBITS_480           // data rate per MIPI lane: e80!
//#define MIPI_DATA_RATE          MBITS_240           // data rate per MIPI lane: 240!
//#define MIPI_DATA_RATE          MBITS_120           // data rate per MIPI lane: 120!


void CSI2_init(void);

#endif /* MIPI_CSI2_H_ */
