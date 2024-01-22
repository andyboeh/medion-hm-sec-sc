#include "as_config_req.h"
#include "as_defines.h"
#include <stdbool.h>

void as_config_req(uint8_t channel, uint8_t list, as_packet_t *reply_packet) {
    if(channel == 1 && list == 1) {
        reply_packet->type = 0x10;
        reply_packet->length = AS_HEADER_SIZE + 13;
        reply_packet->payload[0] = 0x02;
        reply_packet->payload[1] = 0x08; // AES encryption
        reply_packet->payload[2] = *aes_channel1;
        reply_packet->payload[3] = 0x20; // MSG_FOR_POS
        reply_packet->payload[4] = *msg_for_pos;
        reply_packet->payload[5] = 0x21; // EVENT_DELAY_TIME
        reply_packet->payload[6] = *event_delay_time;
        reply_packet->payload[7] = 0x22; // LED_ON_TIME
        reply_packet->payload[8] = *led_on_time;
        reply_packet->payload[9] = 0x30; // TRANSMIT_TRY_MAX
        reply_packet->payload[10] = *peer_transmit_try_max;
        reply_packet->payload[11] = 0x00;
        reply_packet->payload[12] = 0x00;
    } else if(channel == 0 && list == 0) {
        reply_packet->type = 0x10;
        reply_packet->length = AS_HEADER_SIZE + 17;
        reply_packet->payload[0] = 0x02;
        reply_packet->payload[1] = 0x02;
        reply_packet->payload[2] = 0x01; // Set by default to 0x01, what is this?
        reply_packet->payload[3] = 0x09; // Cyclic Info Message
        reply_packet->payload[4] = *cyclic_info;
        reply_packet->payload[5] = 0x0a; // HMID[0]
        reply_packet->payload[6] = *hm_master_id;
        reply_packet->payload[7] = 0x0b; // HMID[1]
        reply_packet->payload[8] = *(hm_master_id+1);
        reply_packet->payload[9] = 0x0c; // HMID[2]
        reply_packet->payload[10] = *(hm_master_id+2);
        reply_packet->payload[11] = 0x10; // Sabotage Message
        reply_packet->payload[12] = *sabotage_message;
        reply_packet->payload[13] = 0x14; // Transmit Try Max
        reply_packet->payload[14] = *transmit_try_max;
        reply_packet->payload[15] = 0x00;
        reply_packet->payload[16] = 0x00;
    } else {
        reply_packet->payload[0] = 0x80; // Set payload to NACK
    }
}
