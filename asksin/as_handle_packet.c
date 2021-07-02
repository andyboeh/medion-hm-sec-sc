#include "as_handle_packet.h"
#include "as_config_start.h"
#include "as_config_end.h"
#include "as_config_write.h"
#include "as_send.h"
#include "as_packet.h"
#include "stm8l.h"

extern bool finished;

void as_handle_packet(as_packet_t * packet)
{
	bool enter_bootloader = false;
	bool ack = false;

	if (packet->type == 0x01 && packet->length >= AS_HEADER_SIZE + 2 && packet->payload[1] == 0x05)
		ack = as_config_start(packet->payload[0], packet->payload[6]); // packet->payload[2-5] is peer id if configuring peer config
	else if (packet->type == 0x01 && packet->length >= AS_HEADER_SIZE + 2 && packet->payload[1] == 0x08)
		ack = as_config_write(packet->payload[0], packet->length - AS_HEADER_SIZE - 2, packet->payload + 2);
	else if (packet->type == 0x01 && packet->length >= AS_HEADER_SIZE + 2 && packet->payload[1] == 0x06)
		ack = as_config_end(packet->payload[0]);
	else if (packet->type == 0x11 && packet->length >= AS_HEADER_SIZE + 1 && packet->payload[0] == 0xca) { // enter bootloader
		enter_bootloader = true;
		ack = true;
    }
    else if ((packet->type == 0x41 && packet->length >= AS_HEADER_SIZE + 4) ||
             (packet->type == 0x02 && packet->length >= AS_HEADER_SIZE + 1 + 4 && packet->payload[0] == 0x01)) {
		uint8_t * data = packet->payload;
		if (packet->type == 0x02)
			data++;
        //as_valve_value = data[0];
        //as_sleep_value = data[1] | ((uint16_t)data[2] << 8);
		if (data[3] != 0xff) {
            //wanted_heat = data[3];
            //ui_update();
		}

		finished = true;
		as_ok = true;
	}
	
	// TODO conf readback

	if (packet->flags & AS_FLAG_BIDI) { // send answer
        as_packet_t dev_info;
        dev_info.length = 10;
        dev_info.counter = packet->counter;
        dev_info.flags = AS_FLAG_DEF;
        dev_info.type = 0x02;
        for(int i=0; i<3; i++) {
            dev_info.from[i] = hm_id[i];
            dev_info.to[i] = packet->from[i];
        }
        dev_info.payload[0] = ack ? 0x00 : 0x80;

		as_send(&dev_info);
	}

	if (enter_bootloader) {
		disable_interrupts();
        //main_deinit();
        //RST_SR = 0xff; // reset all reset sources to signal bootloader that we jumped into it
        //__asm
        //jpf	[FLASH_START + 1] // jump far because bootloader is in upper memory region
        //__endasm;
	}

}
