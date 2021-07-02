#include "as_decode.h"

void as_decode(uint8_t len, uint8_t *buf)
{
	uint8_t i, t;
	uint8_t prev = buf[0];
	buf[0] = (~buf[0]) ^ 0x89;

	for (i = 1; i < len - 1; i++) {
		t = buf[i];
		buf[i] = (prev + 0xdc) ^ buf[i];
		prev = t;
	}

	buf[i] ^= buf[1];
}
