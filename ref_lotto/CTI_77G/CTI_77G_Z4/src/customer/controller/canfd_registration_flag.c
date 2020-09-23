#include "can_id.h"
#include "helios.h"
#include "canfd_registration_flag.h"
#include "radar_input_controller.h"
#include "console_cmd.h"
#include "console.h"
#include "stdlib.h"

static void canfd_registration_flag(char** args, int count);

typedef enum{
	null,
	replay,
	json
}canfd_register_name_e;

typedef struct {
	uint32_t id;
	uint32_t mask;
	char* name;
	recv_event_p event;
}canfd_reg_flg_t, *canfd_reg_flg_p;		//canfd_registration_flag

static const canfd_reg_flg_t flags[] = {
	{0, 0, "null", NULL},
	{Receiver_ID, CAN_STD_ID_MASK_FULL, "replay", (recv_event_p)helios_rcvr_handler},
	{ICI_RX_ID, CAN_STD_ID_MASK_FULL, "json", (recv_event_p)json_req_handle}
};

static canfd_register_name_e flags_indx = null;
static uint16_t devid;

void canfd_registration_init(uint16_t devid_input){
	devid = devid_input;
#if JSON_LIST_EN
	flags_indx = json;
	isotp_rx_id_register(
		flags[json].id | devid,
		flags[json].mask,
		flags[json].name,
		flags[json].event);
#endif
	console_command_reg("canfd", canfd_registration_flag);
}

void canfd_registration_flag(char** args, int count){
	if (count > 1){
		if (!strcmp(args[1], "flag")) {
			flags_indx = strtol(args[2], NULL, 10);
			if(flags_indx == replay) {
				isotp_rx_id_register(
					flags[replay].id,
					flags[replay].mask,
					flags[replay].name,
					flags[replay].event);
#if JSON_LIST_EN
			} else if(flags_indx == json){
				isotp_rx_id_register(
					flags[json].id | devid,
					flags[json].mask,
					flags[json].name,
					flags[json].event);
#endif
			} else {
				isotp_rx_id_register(
					flags[null].id,
					flags[null].mask,
					flags[null].name,
					flags[null].event);
			}
		}
	} else {
		PRINTF("canfd: flag=%d, [null, replay, json]\n",flags_indx);
	}
}
