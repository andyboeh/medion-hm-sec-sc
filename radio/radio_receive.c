#include "radio_receive.h"
#include "radio_read_burst.h"
#include "radio_white.h"
#include "crc16.h"
#include "as_decode.h"
#include "si4430.h"

bool radio_receive(as_packet_t * pkg, uint8_t max_length)
{
	radio_read_burst(SI4430_FIFO, max_length + 3, pkg->data); // 3 = 1 byte length + 2 byte crc
	radio_white(max_length + 3, pkg->data);
	if (pkg->length < max_length) // avoid accessing invalid memory
		max_length = pkg->length;
	if (crc16(0xffff, max_length + 3, pkg->data) != 0)
		return false;
    as_decode(max_length, pkg->data + 1);

	return true;
}
