#include "radio_poll.h"
#include "as_packet.h"
#include "radio_wait_int.h"
#include "get_tick.h"
#include "radio_received.h"
#include "radio_send.h"
#include "radio_enter_receive.h"
#include "radio_receive.h"
#include "radio_sent.h"

volatile as_packet_t packet;
volatile as_packet_t testpkg = { .data = { 14, 0x08, 0x90, 0x11, 0x2e, 0x16, 0x6e, 0x0F, 0x4D, 0x55, 0x02, 0x01, 0xC8, 0x00, 0x00 } };

void radio_poll()
{
    if (!radio_wait_int(get_tick() + 5000)) {
        //if (++stati_in == sizeof(stati) / sizeof(status_t))
        //	stati_in = 0;
#ifdef LCD_INCLUDED
		lcd_data.value = stati_in & 0xf;
#endif
	}

	if (radio_received()) {
		if (!radio_receive(&packet, 14))
			__asm__ ("break");

		testpkg.counter = packet.counter; // answer with same seq-id
		radio_send(&testpkg);
	}
	else if (radio_sent())
		radio_enter_receive(14);
}
