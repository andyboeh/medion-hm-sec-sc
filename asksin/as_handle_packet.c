#include "as_handle_packet.h"
#include "as_config_req.h"
#include "as_config_start.h"
#include "as_config_end.h"
#include "as_config_write.h"
#include "as_set_new_aes_key.h"
#include "led_blink.h"
#include "as_send.h"
#include "as_packet.h"
#include "stm8l.h"

extern bool finished;

void as_handle_packet(as_packet_t * packet)
{
	bool enter_bootloader = false;
	bool ack = false;
    bool ack_payload = true;
    as_packet_t reply_packet;

    // We prepare the reply packet here and overwrite data as needed before
    // actually sending it out
    reply_packet.length = 10;
    reply_packet.counter = packet->counter;
    reply_packet.flags = AS_FLAG_DEF;
    reply_packet.type = 0x02;

    switch(packet->type) {
    case 0x01: // CONFIG
        if(packet->length >= AS_HEADER_SIZE + 2) {
            switch(packet->payload[1]) {
            case 0x03: // CONFIG_PEER_LIST_REQ
                break;
            case 0x04: // CONFIG_PARAM_REQ
                as_config_req(packet->payload[0], packet->payload[6], &reply_packet);
                ack_payload = false;
                break;
            case 0x05:
                ack = as_config_start(packet->payload[0], packet->payload[6]);
                break;
            case 0x08:
                ack = as_config_write(packet->payload[0], packet->length - AS_HEADER_SIZE - 2, packet->payload + 2);
                break;
            case 0x06:
                ack = as_config_end(packet->payload[0]);
                break;
            }
        }
        break;
    case 0x02: // ACK
        if(packet->length >= AS_HEADER_SIZE + 1 + 4) {
            if(packet->payload[0] == 0x01) { // ACK_STATUS
                finished = true;
                as_ok = true;
                // FIXME: ack?
            }
        }
        break;
    case 0x04: // AES_KEY_EXCHANGE
        // SET_AES_KEY_INDEX
        if(packet->length >= AS_HEADER_SIZE + 16) {
            ack = as_set_new_aes_key(packet);
        }
        break;
    case 0x11: // INSTRUCTION
        if(packet->length >= AS_HEADER_SIZE + 1 && packet->payload[0] == 0xca) {
            enter_bootloader = true;
            ack = true;
        }
        break;

    }
	
	// TODO conf readback

	if (packet->flags & AS_FLAG_BIDI) { // send answer
        for(int i=0; i<3; i++) {
            reply_packet.from[i] = hm_id[i];
            reply_packet.to[i] = packet->from[i];
        }
        if(ack_payload) {
            reply_packet.payload[0] = ack ? 0x00 : 0x80;
        }

        as_send(&reply_packet);
	}

	if (enter_bootloader) {
        // disable_interrupts();
        //main_deinit();
        //RST_SR = 0xff; // reset all reset sources to signal bootloader that we jumped into it
        //__asm
        //jpf	[FLASH_START + 1] // jump far because bootloader is in upper memory region
        //__endasm;
	}

}
