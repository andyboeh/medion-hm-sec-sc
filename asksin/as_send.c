#include "as_send.h"
#include "radio_send.h"
#include "radio_wait.h"
#include "get_tick.h"
#include "tick_elapsed.h"
#include "radio_enter_receive.h"
#include "radio_receive.h"
#include "as_handle_packet.h"

#define MAX_ACK_LENGTH 14 // ACKStatus is 9 + 1 + 4
static as_packet_t ack_packet;

bool as_send(as_packet_t * packet) {
	bool ok = false;

	for (int try = 0; try < 3; try++) {
		uint16_t timeout_at;

		radio_send(packet);
		if (!radio_wait(get_tick() + 1000))
			__asm__("break\n"); // TODO

		if (!(packet->flags & AS_FLAG_BIDI)) {
			ok = true;
			break; // if not bidirectional don't wait for ack
		}

		timeout_at = get_tick() + 300;
		while (!tick_elapsed(timeout_at)) {

			radio_enter_receive(MAX_ACK_LENGTH);
			if (!radio_wait(timeout_at))
				continue;
		
			if (!radio_receive(&ack_packet, MAX_ACK_LENGTH)) {
				__asm__ ("break");
				continue; // if crc check fails, continue receiving
			}
			if (CMP_ID(ack_packet.to, packet->from) != 0) {
				__asm__ ("break");
				continue; // not for us
			}
			if (CMP_ID(ack_packet.from, packet->to) != 0)
				continue; // not from our target
			if (ack_packet.counter != packet->counter)
				continue; // answer to wrong/another message
			if (ack_packet.type != 0x02)
				continue; // not an ack packet
			if (ack_packet.length >= AS_HEADER_SIZE + 1 && ack_packet.payload[0] == 0x01) // ACKStatus
				as_handle_packet(&ack_packet);

			ok = true;
			break;
		}
		if (ok)
			break;
	}

	return ok;
}
