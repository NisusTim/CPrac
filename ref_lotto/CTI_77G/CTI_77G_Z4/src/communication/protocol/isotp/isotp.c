#ifndef CTI_UPD

#include <stdint.h>
#include <stdbool.h>
#include "isotp.h"
#include "can_hal.h"
#include "customer.h"

#if ISOTP_EN
can_burst_tx_handle_t g_can_handle;
volatile can_burst_tx_handle_p g_can_handle_p = &g_can_handle;

static IsoTpLink sg_link = {0};
static recv_event_p sg_recv_event = NULL;
//static uint8_t sg_send_buf[ISOTP_BUFSIZE];
//static uint8_t sg_recv_buf[ISOTP_BUFSIZE];
static uint8_t __attribute__((section(".isotp_buf")))sg_send_buf[ISOTP_BUFSIZE];
static uint8_t __attribute__((section(".isotp_buf")))sg_recv_buf[ISOTP_BUFSIZE];

static void isotp_just_recv(can_message_p msg);

static uint8_t isotp_ms_to_st_min(uint8_t ms);
static uint8_t isotp_st_min_to_ms(uint8_t st_min);
static int isotp_send_flow_control(IsoTpLink* link, uint8_t flow_status, uint8_t block_size, uint8_t st_min_ms);
static int isotp_send_single_frame(IsoTpLink* link, uint32_t id);
static int isotp_send_first_frame(IsoTpLink* link, uint32_t id);
static int isotp_send_consecutive_frame(IsoTpLink* link);
static int isotp_send(IsoTpLink *link, const uint8_t payload[], uint16_t size);
static int isotp_send_with_id(IsoTpLink *link, uint32_t id, const uint8_t payload[], uint16_t size);
static int isotp_receive_single_frame(IsoTpLink *link, IsoTpCanMessage *message, uint8_t len);
static int isotp_receive_first_frame(IsoTpLink *link, IsoTpCanMessage *message, uint8_t len);
static int isotp_receive_consecutive_frame(IsoTpLink *link, IsoTpCanMessage *message, uint8_t len);
static int isotp_receive_flow_conrtrol_frame(IsoTpLink *link, IsoTpCanMessage *message, uint8_t len);
static void isotp_on_can_message(IsoTpLink *link, uint8_t *data, uint8_t len);
static void isotp_poll(IsoTpLink *link);
static int isotp_send_header_and_data(IsoTpLink *link, const uint8_t *header, uint16_t header_size, const uint8_t *data, uint16_t data_size);
static int isotp_send_header_and_data_with_id(IsoTpLink *link, uint32_t id, const uint8_t *header, uint16_t header_size, const uint8_t *data, uint16_t data_size);


void isotp_init_link(void)
{
	memset(&sg_link, 0, sizeof(sg_link));
	sg_link.receive_status = ISOTP_RECEIVE_STATUS_IDLE;
	sg_link.send_status = ISOTP_SEND_STATUS_IDLE;
	sg_link.send_buffer = sg_send_buf;
	sg_link.send_buf_size = sizeof(sg_send_buf);
	sg_link.receive_buffer = sg_recv_buf;
	sg_link.recevie_buf_size = sizeof(sg_recv_buf);

	g_can_handle_p->name[0] = 'i';
	g_can_handle_p->name[1] = 's';
	g_can_handle_p->name[2] = 'o';
	g_can_handle_p->name[3] = 't';
	g_can_handle_p->name[4] = 'p';
	g_can_handle_p->ch = CAN_BURST_TX_CH_RMTP;
	g_can_handle_p->itf = CAN_BURST_TX_ITF_CAN2;

	if(1 == get_can2_dlc_status())
	{
		g_can_handle_p->can_mb = can2_tx_burst_data_register_dlc64("isotp", (event_proc_p)can2_burst_tx_handler, 0);
	}
	else
	{
		g_can_handle_p->can_mb = can2_tx_burst_data_register("isotp", (event_proc_p)can2_burst_tx_handler, 0);
	}

	return;
}

void isotp_just_send(uint32_t id, const uint8_t payload[], uint16_t size)
{
	sg_link.send_arbitration_id = id;

	isotp_send(&sg_link, payload, size);
	sg_link.send_bs_remain = size;
	isotp_poll(&sg_link);
}

static void isotp_just_recv(can_message_p msg)
{
	isotp_on_can_message(&sg_link, msg->pkg.b, 8);
	sg_recv_event(&sg_link);
}

void isotp_rx_id_register(uint32_t id, uint32_t mask, char* name, recv_event_p event)
{
	can2_rx_id_register(id, mask, name, (event_proc_p)isotp_just_recv);

	sg_recv_event = event;
}

IsoTpLink* get_isotp_link(void)
{
	return &sg_link;
}

/* st_min to microsecond */
static uint8_t isotp_ms_to_st_min(uint8_t ms)
{
	uint8_t st_min;

	st_min = ms;
	if (st_min > 0x7F)
	{
		st_min = 0x7F;
	}

	return st_min;
}

/* st_min to msec  */
static uint8_t isotp_st_min_to_ms(uint8_t st_min)
{
	uint8_t ms;

	if (st_min >= 0xF1 && st_min <= 0xF9)
	{
		ms = 1;
	}
	else if (st_min <= 0x7F)
	{
		ms = st_min;
	}
	else
	{
		ms = 0;
	}

	return ms;
}

static int isotp_send_flow_control(IsoTpLink* link, uint8_t flow_status, uint8_t block_size, uint8_t st_min_ms)
{

	IsoTpCanMessage message;
	int ret;

	/* setup message  */
	message.as.flow_control.type = ISOTP_PCI_TYPE_FLOW_CONTROL_FRAME;
	message.as.flow_control.FS = flow_status;
	message.as.flow_control.BS = block_size;
	message.as.flow_control.STmin = isotp_ms_to_st_min(st_min_ms);

	/* send message */
#ifdef ISO_TP_FRAME_PADDING
	(void) memset(message.as.flow_control.reserve, 0, sizeof(message.as.flow_control.reserve));
	ret = isotp_user_send_can(link->send_arbitration_id, message.as.data_array.ptr, sizeof(message));
#else    
	ret = isotp_user_send_can(link->send_arbitration_id,
			message.as.data_array.ptr,
			3);
#endif

	return ret;
}

static int isotp_send_single_frame(IsoTpLink* link, uint32_t id)
{

	IsoTpCanMessage message;
	int ret;

	/* multi frame message length must greater than 7  */
//	assert(link->send_size <= 7);

	/* setup message  */
	message.as.single_frame.type = ISOTP_PCI_TYPE_SINGLE;
	message.as.single_frame.SF_DL = (uint8_t) link->send_size;
	(void) memcpy(message.as.single_frame.data, link->send_buffer, link->send_size);

	/* send message */
#ifdef ISO_TP_FRAME_PADDING
	(void) memset(message.as.single_frame.data + link->send_size, 0, sizeof(message.as.single_frame.data)
			- link->send_size);
	ret = isotp_user_send_can(id, message.as.data_array.ptr, sizeof(message));
#else
	ret = isotp_user_send_can(id,
			message.as.data_array.ptr,
			link->send_size + 1);
#endif

	return ret;
}

static int isotp_send_first_frame(IsoTpLink* link, uint32_t id)
{

	IsoTpCanMessage message;
	int ret;

	/* multi frame message length must greater than 7  */
//	assert(link->send_size > 7);

	/* setup message  */
	message.as.first_frame.type = ISOTP_PCI_TYPE_FIRST_FRAME;
	message.as.first_frame.FF_DL_low = (uint8_t) link->send_size;
	message.as.first_frame.FF_DL_high = (uint8_t) (0x0F & (link->send_size >> 8));
	(void) memcpy(message.as.first_frame.data, link->send_buffer, sizeof(message.as.first_frame.data));

	/* send message */
	ret = isotp_user_send_can(id, message.as.data_array.ptr, sizeof(message));
	if (ISOTP_RET_OK == ret)
	{
		link->send_offset += sizeof(message.as.first_frame.data);
		link->send_sn = 1;
	}

	return ret;
}

static int isotp_send_consecutive_frame(IsoTpLink* link)
{

	IsoTpCanMessage message;
	uint16_t data_length;
	int ret;

	/* multi frame message length must greater than 7  */
//	assert(link->send_size > 7);

	/* setup message  */
	message.as.consecutive_frame.type = TSOTP_PCI_TYPE_CONSECUTIVE_FRAME;
	message.as.consecutive_frame.SN = link->send_sn;
	data_length = link->send_size - link->send_offset;
	if (data_length > sizeof(message.as.consecutive_frame.data))
	{
		data_length = sizeof(message.as.consecutive_frame.data);
	}
	(void) memcpy(message.as.consecutive_frame.data, link->send_buffer
			+ link->send_offset, data_length);

	/* send message */
#ifdef ISO_TP_FRAME_PADDING
	(void) memset(message.as.consecutive_frame.data + data_length, 0, sizeof(message.as.consecutive_frame.data)
			- data_length);
	ret = isotp_user_send_can(link->send_arbitration_id, message.as.data_array.ptr, sizeof(message));
#else
	ret = isotp_user_send_can(link->send_arbitration_id,
			message.as.data_array.ptr,
			data_length + 1);
#endif
	if (ISOTP_RET_OK == ret)
	{
		link->send_offset += data_length;
		if (++(link->send_sn) > 0x0F)
		{
			link->send_sn = 0;
		}
	}

	return ret;
}

static int isotp_send(IsoTpLink *link, const uint8_t payload[], uint16_t size)
{
	return isotp_send_with_id(link, link->send_arbitration_id, payload, size);
}

static int isotp_send_with_id(IsoTpLink *link, uint32_t id, const uint8_t payload[], uint16_t size)
{
	int ret;

	if (size > link->send_buf_size)
	{
		isotp_user_debug("Message to big, increase ISO_TP_MAX_MESSAGE_SIZE to set a bigger buffer\n");
		return ISOTP_RET_OVERFLOW;
	}

	if (ISOTP_SEND_STATUS_INPROGRESS == link->send_status)
	{
		isotp_user_debug("Abord previous message, which is sending in pregress\n");
		return ISOTP_RET_INPROGRESS;
	}

	/* copy into local buffer */
	link->send_size = size;
	link->send_offset = 0;
	(void) memcpy(link->send_buffer, payload, size);

	if (link->send_size < 8)
	{
		/* send single frame */
		ret = isotp_send_single_frame(link, id);
	}
	else
	{
		/* send multi-frame */
		ret = isotp_send_first_frame(link, id);

		/* init multi-frame control flags */
		if (ISOTP_RET_OK == ret)
		{
			link->send_bs_remain = 0;
			link->send_st_min = 0;
			link->send_wtf_count = 0;
			link->send_timer_st = isotp_user_get_ms();
			link->send_timer_bs = isotp_user_get_ms() + ISO_TP_DEFAULT_RESPONSE_TIMEOUT;
			link->send_protocol_resault = ISOTP_PROTOCOL_RESAULT_OK;
			link->send_status = ISOTP_SEND_STATUS_INPROGRESS;
		}
	}

	return ret;
}

static int isotp_receive_single_frame(IsoTpLink *link, IsoTpCanMessage *message, uint8_t len)
{
	/* check data length */
	if ((0 == message->as.single_frame.SF_DL) ||
		(message->as.single_frame.SF_DL > (len - 1)))
	{
		isotp_user_debug("Single-frame length too small.");
		return ISOTP_RET_LENGTH;
	}

	/* copying data */
	(void) memcpy(link->receive_buffer, message->as.single_frame.data, message->as.single_frame.SF_DL);
	link->receive_size = message->as.single_frame.SF_DL;

	return ISOTP_RET_OK;
}

static int isotp_receive_first_frame(IsoTpLink *link, IsoTpCanMessage *message, uint8_t len)
{
	uint16_t payload_length;

	if (8 != len)
	{
		isotp_user_debug("First frame should be 8 byte lenght.");
		return ISOTP_RET_LENGTH;
	}

	/* check data length */
	payload_length = message->as.first_frame.FF_DL_high;
	payload_length = (payload_length << 8) + message->as.first_frame.FF_DL_low;

	/* should not use multiple frame transmition */
	if (payload_length <= 7)
	{
		isotp_user_debug("Should not use multiple frame transmition.");
		return ISOTP_RET_LENGTH;
	}

	if (payload_length > link->recevie_buf_size)
	{
		isotp_user_debug("Multi-frame response too large for receive buffer.");
		return ISOTP_RET_OVERFLOW;
	}

	/* copying data */
	(void) memcpy(link->receive_buffer, message->as.first_frame.data, sizeof(message->as.first_frame.data));
	link->receive_size = payload_length;
	link->receive_offset = sizeof(message->as.first_frame.data);
	link->receive_sn = 1;

	return ISOTP_RET_OK;
}

static int isotp_receive_consecutive_frame(IsoTpLink *link, IsoTpCanMessage *message, uint8_t len)
{
	uint16_t remaining_bytes;

	/* check sn */
	if (link->receive_sn != message->as.consecutive_frame.SN)
	{
		return ISOTP_RET_WRONG_SN;
	}

	/* check data length */
	remaining_bytes = link->receive_size - link->receive_offset;
	if (remaining_bytes > sizeof(message->as.consecutive_frame.data))
	{
		remaining_bytes = sizeof(message->as.consecutive_frame.data);
	}
	if (remaining_bytes > len - 1)
	{
		isotp_user_debug("Consecutive frame too short.");
		return ISOTP_RET_LENGTH;
	}

	/* copying data */
	(void) memcpy(link->receive_buffer + link->receive_offset, message->as.consecutive_frame.data, remaining_bytes);

	link->receive_offset += remaining_bytes;
	if (++(link->receive_sn) > 0x0F)
	{
		link->receive_sn = 0;
	}

	return ISOTP_RET_OK;
}

static int isotp_receive_flow_conrtrol_frame(IsoTpLink *link, IsoTpCanMessage *message, uint8_t len)
{
	/* check message length */
	if (len < 3)
	{
		isotp_user_debug("Flow control frame too short.");
		return ISOTP_RET_LENGTH;
	}

	return ISOTP_RET_OK;
}

static void isotp_on_can_message(IsoTpLink *link, uint8_t *data, uint8_t len)
{
	IsoTpCanMessage message;
	int ret;

	if (len < 2 || len > 8)
	{
		return;
	}

	(void) memcpy(message.as.data_array.ptr, data, len);
	(void) memset(message.as.data_array.ptr + len, 0, sizeof(message.as.data_array.ptr) - len);

	switch (message.as.common.type)
	{
	case ISOTP_PCI_TYPE_SINGLE:
	{
		/* update protocol resault */
		if (ISOTP_RECEIVE_STATUS_INPROGRESS == link->receive_status)
		{
			link->receive_protocol_resault = ISOTP_PROTOCOL_RESAULT_UNEXP_PDU;
		}
		else
		{
			link->receive_protocol_resault = ISOTP_PROTOCOL_RESAULT_OK;
		}

		/* handle message */
		ret = isotp_receive_single_frame(link, &message, len);

		if (ISOTP_RET_OK == ret)
		{
			/* change status */
			link->receive_status = ISOTP_RECEIVE_STATUS_FULL;
		}
		break;
	}
	case ISOTP_PCI_TYPE_FIRST_FRAME:
	{
		/* update protocol resault */
		if (ISOTP_RECEIVE_STATUS_INPROGRESS == link->receive_status)
		{
			link->receive_protocol_resault = ISOTP_PROTOCOL_RESAULT_UNEXP_PDU;
		}
		else
		{
			link->receive_protocol_resault = ISOTP_PROTOCOL_RESAULT_OK;
		}

		/* handle message */
		ret = isotp_receive_first_frame(link, &message, len);

		/* if overflow happend */
		if (ISOTP_RET_OVERFLOW == ret)
		{
			/* update protocol resault */
			link->receive_protocol_resault = ISOTP_PROTOCOL_RESAULT_BUFFER_OVFLW;
			/* change status */
			link->receive_status = ISOTP_RECEIVE_STATUS_IDLE;
			/* send error message */
			isotp_send_flow_control(link, PCI_FLOW_STATUS_OVERFLOW, 0, 0);
			break;
		}

		/* if receive successful */
		if (ISOTP_RET_OK == ret)
		{
			/* change status */
			link->receive_status = ISOTP_RECEIVE_STATUS_INPROGRESS;
			/* send fc frame */
			link->receive_bs_count = ISO_TP_DEFAULT_BLOCK_SIZE;
			isotp_send_flow_control(link, PCI_FLOW_STATUS_CONTINUE, link->receive_bs_count, ISO_TP_DEFAULT_ST_MIN);
			/* refresh timer cs */
			link->receive_timer_cr = isotp_user_get_ms() + ISO_TP_DEFAULT_RESPONSE_TIMEOUT;
		}

		break;
	}
	case TSOTP_PCI_TYPE_CONSECUTIVE_FRAME:
	{
		/* check if in receiving status */
		if (ISOTP_RECEIVE_STATUS_INPROGRESS != link->receive_status)
		{
			link->receive_protocol_resault = ISOTP_PROTOCOL_RESAULT_UNEXP_PDU;
			break;
		}

		/* handle message */
		ret = isotp_receive_consecutive_frame(link, &message, len);

		/* if wrong sn */
		if (ISOTP_RET_WRONG_SN == ret)
		{
			link->receive_protocol_resault = ISOTP_PROTOCOL_RESAULT_WRONG_SN;
			link->receive_status = ISOTP_RECEIVE_STATUS_IDLE;
			break;
		}

		/* if success */
		if (ISOTP_RET_OK == ret)
		{
			/* refresh timer cs */
			link->receive_timer_cr = isotp_user_get_ms() + ISO_TP_DEFAULT_RESPONSE_TIMEOUT;

			/* receive finished */
			if (link->receive_offset >= link->receive_size)
			{
				link->receive_status = ISOTP_RECEIVE_STATUS_FULL;
			}
			else
			{
				/* send fc when bs reaches limit */
				if (0 == --link->receive_bs_count)
				{
					link->receive_bs_count = ISO_TP_DEFAULT_BLOCK_SIZE;
					isotp_send_flow_control(link, PCI_FLOW_STATUS_CONTINUE, link->receive_bs_count, ISO_TP_DEFAULT_ST_MIN);
				}
			}
		}

		break;
	}
	case ISOTP_PCI_TYPE_FLOW_CONTROL_FRAME:
		/* handle fc frame only when sending in progress  */
		if (ISOTP_SEND_STATUS_INPROGRESS != link->send_status)
		{
			break;
		}

		/* handle message */
		ret = isotp_receive_flow_conrtrol_frame(link, &message, len);

		if (ISOTP_RET_OK == ret)
		{
			/* refresh bs timer */
			link->send_timer_bs = isotp_user_get_ms() + ISO_TP_DEFAULT_RESPONSE_TIMEOUT;

			/* overflow */
			if (PCI_FLOW_STATUS_OVERFLOW == message.as.flow_control.FS)
			{
				link->send_protocol_resault = ISOTP_PROTOCOL_RESAULT_BUFFER_OVFLW;
				link->send_status = ISOTP_SEND_STATUS_ERROR;
			}
			/* wait */
			else if (PCI_FLOW_STATUS_WAIT == message.as.flow_control.FS)
			{
				link->send_wtf_count += 1;
				/* wati exceed allowed count */
				if (link->send_wtf_count > ISO_TP_MAX_WFT_NUMBER)
				{
					link->send_protocol_resault = ISOTP_PROTOCOL_RESAULT_WFT_OVRN;
					link->send_status = ISOTP_SEND_STATUS_ERROR;
				}
			}
			/* permit send */
			else if (PCI_FLOW_STATUS_CONTINUE == message.as.flow_control.FS)
			{
				if (0 == message.as.flow_control.BS)
				{
					link->send_bs_remain = ISOTP_INVALID_BS;
				}
				else
				{
					link->send_bs_remain = message.as.flow_control.BS;
				}
				link->send_st_min = isotp_st_min_to_ms(message.as.flow_control.STmin);
				link->send_wtf_count = 0;
			}
		}
		break;
	default:
		break;
	};

	return;
}

static void isotp_poll(IsoTpLink *link)
{
	int ret;

	/* only polling when operation in progress */
	//if (ISOTP_SEND_STATUS_INPROGRESS == link->send_status) {
	while (ISOTP_SEND_STATUS_INPROGRESS == link->send_status)
	{

		/* continue send data */
		if (/* send data if bs_remain is invalid or bs_remain large than zero */
		(ISOTP_INVALID_BS == link->send_bs_remain || link->send_bs_remain > 0) &&
		/* and if st_min is zero or go beyond interval time */
		(0 == link->send_st_min ||
		(0 != link->send_st_min &&
		IsoTpTimeAfter(isotp_user_get_ms(), link->send_timer_st))))
		{

			ret = isotp_send_consecutive_frame(link);
			if (ISOTP_RET_OK == ret)
			{
				if (ISOTP_INVALID_BS != link->send_bs_remain)
				{
					link->send_bs_remain -= 1;
				}
				link->send_timer_bs = isotp_user_get_ms() + ISO_TP_DEFAULT_RESPONSE_TIMEOUT;
				link->send_timer_st = isotp_user_get_ms() + link->send_st_min;

				/* check if send finish */
				if (link->send_offset >= link->send_size)
				{
					link->send_status = ISOTP_SEND_STATUS_IDLE;
				}
			}
			else
			{
				link->send_status = ISOTP_SEND_STATUS_ERROR;
			}
		}

		/* check timeout */
		if (IsoTpTimeAfter(isotp_user_get_ms(), link->send_timer_bs))
		{
			link->send_protocol_resault = ISOTP_PROTOCOL_RESAULT_TIMEOUT_BS;
			link->send_status = ISOTP_SEND_STATUS_ERROR;
		}
	}

	/* only polling when operation in progress */
	if (ISOTP_RECEIVE_STATUS_INPROGRESS == link->receive_status)
	{

		/* check timeout */
		if (IsoTpTimeAfter(isotp_user_get_ms(), link->receive_timer_cr))
		{
			link->receive_protocol_resault = ISOTP_PROTOCOL_RESAULT_TIMEOUT_CR;
			link->receive_status = ISOTP_RECEIVE_STATUS_IDLE;
		}
	}

	return;
}


void isotp_custom_send(uint32_t id,
							   const uint8_t *header,
							   uint16_t header_size,
							   const uint8_t *data,
							   uint16_t data_size)
{
	sg_link.send_arbitration_id = id;

	isotp_send_header_and_data(&sg_link, header, header_size, data, data_size);
	sg_link.send_bs_remain = (header_size + data_size);
	isotp_poll(&sg_link);
}

static int isotp_send_header_and_data(IsoTpLink *link,
									  const uint8_t *header,
									  uint16_t header_size,
									  const uint8_t *data,
									  uint16_t data_size)
{
	return isotp_send_header_and_data_with_id(link, link->send_arbitration_id, header, header_size, data, data_size);
}

static int isotp_send_header_and_data_with_id(IsoTpLink *link,
											  uint32_t id,
											  const uint8_t *header,
											  uint16_t header_size,
											  const uint8_t *data,
											  uint16_t data_size)
{
	int ret;

	if ((header_size + data_size) > link->send_buf_size)
	{
		isotp_user_debug("Message to big, increase ISO_TP_MAX_MESSAGE_SIZE to set a bigger buffer\n");
		return ISOTP_RET_OVERFLOW;
	}

	if (ISOTP_SEND_STATUS_INPROGRESS == link->send_status)
	{
		isotp_user_debug("Abord previous message, which is sending in pregress\n");
		return ISOTP_RET_INPROGRESS;
	}

	/* copy into local buffer */
	link->send_size = (header_size + data_size);
	link->send_offset = 0;
	(void) memcpy(link->send_buffer, header, header_size);
	(void) memcpy((link->send_buffer + header_size), data, data_size);

	if (link->send_size < 8)
	{
		/* send single frame */
		ret = isotp_send_single_frame(link, id);
	}
	else
	{
		/* send multi-frame */
		ret = isotp_send_first_frame(link, id);

		/* init multi-frame control flags */
		if (ISOTP_RET_OK == ret)
		{
			link->send_bs_remain = 0;
			link->send_st_min = 0;
			link->send_wtf_count = 0;
			link->send_timer_st = isotp_user_get_ms();
			link->send_timer_bs = isotp_user_get_ms() + ISO_TP_DEFAULT_RESPONSE_TIMEOUT;
			link->send_protocol_resault = ISOTP_PROTOCOL_RESAULT_OK;
			link->send_status = ISOTP_SEND_STATUS_INPROGRESS;
		}
	}

	return ret;
}
#endif
#endif