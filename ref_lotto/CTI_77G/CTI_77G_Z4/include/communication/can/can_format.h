/*
 * can_format.h
 *
 *  Created on: 2018年8月22日
 *      Author: WoodLiu
 */

#ifndef COMMUNICATION_CAN_CAN_FORMAT_H_
#define COMMUNICATION_CAN_CAN_FORMAT_H_

#include "typedefs.h"

/*Transfer Format*/
typedef union  Motorola_Fromat{
  uint64_t R;
  struct {
	  uint64_t bit63to56 :8;
	  uint64_t bit55to48 :8;
	  uint64_t bit47to40 :8;
	  uint64_t bit39to32 :8;
	  uint64_t bit31to24 :8;
	  uint64_t bit23to16 :8;
	  uint64_t bit15to8 :8;
	  uint64_t bit7to0 :8;
  } B;
} MOTOROLA_FROMAT;

typedef union  Intel_Fromat{
  uint64_t R;
  struct {
	  uint64_t bit7to0 :8;
	  uint64_t bit15to8 :8;
	  uint64_t bit23to16 :8;
	  uint64_t bit31to24 :8;
	  uint64_t bit39to32 :8;
	  uint64_t bit47to40 :8;
	  uint64_t bit55to48 :8;
	  uint64_t bit63to56 :8;
  } B;
} INTEL_FROMAT;


uint64_t intel_to_motorola(uint64_t data);
uint64_t motorola_to_intel(uint64_t data);

#endif /* COMMUNICATION_CAN_CAN_FORMAT_H_ */
