#include "as_send_status.h"
#include "as_send.h"
#include "as_packet.h"

extern uint8_t as_cnt;

void as_send_status() {
    as_packet_t status;
    status.length = AS_HEADER_SIZE + 1;
    status.counter = as_cnt++;
    status.flags = AS_FLAG_DEF;
    status.type = 0x41;
    status.from[0] = hm_id[0];
    status.from[1] = hm_id[1];
    status.from[2] = hm_id[2];
    status.to[0] = hm_master_id[0];
    status.to[1] = hm_master_id[1];
    status.to[2] = hm_master_id[2];
    status.payload[0] = 0;
	if (!ID_IS_NULL(hm_master_id))
		status.flags |= AS_FLAG_BIDI;

	as_send(&status);
}
