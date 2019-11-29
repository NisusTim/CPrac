/**
* @file    ticket_machine.h
* @author  Samuel Chen
* @version V1.0.0
* @date    2019/04/30
* @brief   --
*/

#ifndef __TICKET_MACHINE_H
#define __TICKET_MACHINE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

	typedef enum
	{
		TICKET_MACHINE_SUCESS,			/**< No error. */
		TICKET_MACHINE_REPEAT,			/**< The same number already exists in the box. */
		TICKET_MACHINE_EMPTY,			/**< List is empty. */
		TICKET_MACHINE_OUT_OF_RANGE		/**< The index is greater than or equal to the number of items. */
	}TICKET_MACHINE_STATUS;

	typedef struct TicketMachine
	{
		bool* tickets;				/**< Used to indicate the tickets have not been taken away. */
		uint32_t tickets_num;		/**< [private]  */
		uint32_t remaining_tickets;	/**< [private] The number of remaining tickets. */
		uint32_t last_ticket;		/**< [private]  */
		TICKET_MACHINE_STATUS (*take_ticket)(struct TicketMachine* self, uint32_t *ticket);			/**< Take a number. */
		TICKET_MACHINE_STATUS (*recycle_ticket)(struct TicketMachine* self, uint32_t ticket);		/**< Recycle ticket. */
	}TicketMachine;

	void new_ticket_machine(TicketMachine*self);
	

#ifdef __cplusplus
}
#endif

#endif /* __TICKET_MACHINE_H */
