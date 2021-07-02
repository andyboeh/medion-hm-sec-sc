#include "as_send_contact_state.h"
#include "as_packet.h"
#include "as_send.h"
#include "spi_enable.h"
#include "spi_disable.h"
#include "as_listen.h"
#include <stdbool.h>
#include <stdint.h>

extern bool window_open;
extern uint8_t as_cnt;
extern bool finished;
extern bool as_ok;

void as_send_contact_state() {
    as_packet_t status;

    spi_enable();
    finished = false;
    as_ok = false;

    status.length = AS_HEADER_SIZE + 3;
    status.counter = as_cnt++;
    status.flags = AS_FLAG_DEF;
    status.type = 0x41;
    status.from[0] = hm_id[0];
    status.from[1] = hm_id[1];
    status.from[2] = hm_id[2];
    status.to[0] = hm_master_id[0];
    status.to[1] = hm_master_id[1];
    status.to[2] = hm_master_id[2];
    status.payload[0] = 0x01; // Channel 1
    status.payload[1] = 0x00; // ?
    if(window_open) {
        status.payload[2] = 0x02;
    } else {
        status.payload[2] = 0x00;
    }
    if (!ID_IS_NULL(hm_master_id))
        status.flags |= AS_FLAG_BIDI;

    as_send(&status);
    as_listen();
    spi_disable();
}
