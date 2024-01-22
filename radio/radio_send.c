#include "radio_send.h"
#include "as_encode.h"
#include "as_decode.h"
#include "crc16.h"
#include "radio_white.h"
#include "radio_write_reg.h"
#include "radio_write_burst.h"
#include "radio_defines.h"
#include "si4430.h"

extern e_radio_state radio_state;


void radio_send(as_packet_t * pkg)
{
	uint16_t crc;
	uint8_t length = pkg->length; // the whitening changes pkg->length, so we use a local copy

    as_encode(length, pkg->data + 1);
	crc = crc16(0xffff, length + 1, pkg->data);
	pkg->data[length + 1] = crc >> 8;
	pkg->data[length + 2] = crc & 0xff;

    radio_white(length + 3, pkg->data); // 1 byte length + 2 byte crc

    radio_write_reg(SI4430_OMFC2, SI4430_FFCLRRX | SI4430_FFCLRTX); // clear fifos
    radio_write_reg(SI4430_OMFC2, 0);
    radio_write_reg(SI4430_PKLEN, length + 3);
    radio_write_burst(SI4430_FIFO, length + 3, pkg->data);
    radio_write_reg(SI4430_OMFC1, SI4430_TXON); // enter transmit mode

	// undo any changes made to pkg
    radio_white(length + 3, pkg->data);
    as_decode(length, pkg->data + 1);

	radio_state = radio_sending;
}

