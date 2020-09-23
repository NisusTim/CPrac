/*
 * can_cmd.h
 *
 *  Created on: 2017¦~9¤ë15¤é
 *      Author: erichu
 */

#ifndef CAN_CMD_H_
#define CAN_CMD_H_

#define CAN_CMD_ACK_AGREE			0x01
#define CAN_CMD_ACK_REJECT			0x00
#define CAN_INFO_DEVICE_77G			0x01

enum {
	CAN_CMD_UPD_RESET 		= 0x99,
	CAN_CMD_UPD_REQUEST		= 0xA0,
	CAN_CMD_UPD_DATA		= 0xA2,
	CAN_CMD_UPD_DATA_DONE 	= 0xA4,
	CAN_CMD_UPD_PREPARE		= 0xA6,
	CAN_CMD_UPD_KEY 		= 0xA7,
	CAN_CMD_UPD_AUTH 		= 0xA8,
	CAN_CMD_UPD_VERSION 	= 0xDA,
	CAN_CMD_INVALID			= 0xFF
};


enum {
	CAN_INFO_IMG_ALL = 0x00,
	CAN_INFO_IMG_Z4A,
	CAN_INFO_IMG_Z4B,
	CAN_INFO_IMG_Z7A,
	CAN_INFO_IMG_Z7B,
	CAN_INFO_IMG_Z71,
};

void can_cmd_init(void);


#endif /* CAN_CMD_H_ */
