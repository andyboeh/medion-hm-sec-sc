#include "as_listen.h"
#include "get_tick.h"
#include "radio_enter_receive.h"
#include "radio_wait.h"
#include "as_handle_packet.h"
#include "tick_elapsed.h"
#include "radio_receive.h"
#include "stm8l.h"

uint8_t as_cnt = 0;
bool finished;
const uint8_t * hm_id = EEPROM_START; // 3 byte
const uint8_t * hm_serial = EEPROM_START + 3; // 10 byte
const uint8_t * hm_master_id = EEPROM_START + 13; // 3 byte
const uint8_t * aes_key = EEPROM_START + 16; // 16 byte
const uint8_t * aes_channel0 = EEPROM_START + 32; // 1 byte
const uint8_t * aes_channel1 = EEPROM_START + 33; // 1 byte
const uint8_t * aes_key_index = EEPROM_START + 34; // 1 byte
const uint8_t * cyclic_info = EEPROM_START + 35; // 1 byte
const uint8_t * sabotage_message = EEPROM_START + 36; // 1 byte
const uint8_t * transmit_try_max = EEPROM_START + 37; // 1 byte
const uint8_t * link_address1 = EEPROM_START + 38; // 3 byte
const uint8_t * link_channel1 = EEPROM_START + 41; // 1 byte
const uint8_t * link_address2 = EEPROM_START + 42; // 3 byte
const uint8_t * link_channel2 = EEPROM_START + 45; // 1 byte
const uint8_t * link_address3 = EEPROM_START + 46; // 3 byte
const uint8_t * link_channel3 = EEPROM_START + 49; // 1 byte
const uint8_t * link_address4 = EEPROM_START + 50; // 3 byte
const uint8_t * link_channel4 = EEPROM_START + 53; // 1 byte
const uint8_t * msg_for_pos = EEPROM_START + 54; // 1 byte
const uint8_t * event_delay_time = EEPROM_START + 55; // 1 byte
const uint8_t * led_on_time = EEPROM_START + 56; // 1 byte
const uint8_t * peer_transmit_try_max = EEPROM_START + 57; // 1 byte

void as_listen(void) {
	uint16_t timeout_at = get_tick() + 2000;

	while (!finished && !tick_elapsed(timeout_at)) {
		as_packet_t packet;

		radio_enter_receive(MAX_LENGTH);
		if (!radio_wait(timeout_at))
			return;
	
		if (!radio_receive(&packet, MAX_LENGTH)) {
			__asm__ ("break");
			continue; // if crc check fails, continue receiving
		}

		if (CMP_ID(packet.to, hm_id) != 0) {
			__asm__ ("break");
			continue; // not for us
		}
		if (!ID_IS_NULL(hm_master_id) && CMP_ID(packet.from, hm_master_id) != 0)
			continue; // not from our master

		if (packet.counter != as_cnt) {
			//__asm__ ("break");
			//continue;
			// TODO ??
		}
		as_cnt++;

        as_handle_packet(&packet, NULL);
		timeout_at = get_tick() + 1000;
	}
}
