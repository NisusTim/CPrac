#include "ticket_machine.h"

static TICKET_MACHINE_STATUS take_ticket(TicketMachine* self, uint32_t* tickets);
static TICKET_MACHINE_STATUS recycle_ticket(TicketMachine* self, uint32_t tickets);

void new_ticket_machine(TicketMachine* self)
{
	for (uint32_t idx = 0; idx < self->tickets_num; idx++)
	{
		self->tickets[idx] = false;
	}

	self->last_ticket = 0u;
	self->remaining_tickets = self->tickets_num;
	self->take_ticket = take_ticket;
	self->recycle_ticket = recycle_ticket;
}

static TICKET_MACHINE_STATUS take_ticket(TicketMachine* self, uint32_t* tickets)
{
	uint32_t circuit_idx = 0;

	if (self->remaining_tickets != 0)
	{
		for (uint32_t idx = self->last_ticket; idx < self->tickets_num + self->last_ticket; idx++)
		{
			circuit_idx = idx % self->tickets_num;

			if (false == self->tickets[circuit_idx])
			{
				self->tickets[circuit_idx] = true;
				*tickets = circuit_idx + 1;
				self->last_ticket = circuit_idx;
				self->remaining_tickets--;
				return TICKET_MACHINE_REPEAT;
			}
		}
	}

	return TICKET_MACHINE_EMPTY;
}

static TICKET_MACHINE_STATUS recycle_ticket(TicketMachine* self, uint32_t tickets)
{
	if (tickets - 1 >= self->tickets_num || 0 == tickets)
	{
		return TICKET_MACHINE_OUT_OF_RANGE;
	}
	else
	{
		if (true == self->tickets[tickets - 1])
		{
			self->tickets[tickets - 1] = false;
			self->remaining_tickets++;
			return TICKET_MACHINE_SUCESS;
		}
		else
		{
			return TICKET_MACHINE_REPEAT;
		}
	}
}


