#include "radio_switch_100k.h"
#include "radio_write_burst.h"
#include "radio_write_reg.h"

// originally i wanted this to be static inside radio_switch_100k. but sdcc has a problem with that ("relocation error")
CONSTMEM uint8_t reg_1c_25_100k[] = {
    0x9A,
    0x44,
    0x0A,
    0x03,
    0x3C,
    0x02,
    0x22,
    0x22,
    0x07,
    0xFF
};
CONSTMEM uint8_t reg_6e_72[] = {
    0x19,
    0x9A,
    0x0C,
    0x22,
    0x4C
};
void radio_switch_100k(void)
{

	// write all changed settings from Si443x-Register-Settings-100k.ods
	radio_write_burst(0x1c, sizeof(reg_1c_25_100k), reg_1c_25_100k);
    radio_write_reg(0x2a, 0x48); // AFC Limiter: 72
    radio_write_reg(0x58, 0xC0); // ChargePumpCurrentTimingOverride = 0xC0
	radio_write_burst(0x6e, sizeof(reg_6e_72), reg_6e_72);
}
