#include "radio_init.h"
#include "spi_init.h"
#include "spi_enable.h"
#include "spi_defines.h"
#include "radio_write_reg.h"
#include "radio_write_burst.h"
#include "radio_read_reg.h"
#include "radio_defines.h"
#include "si4430.h"
#include "delay.h"
#include "spi_disable.h"
#include "stm8l.h"

e_radio_state radio_state;

// originally i wanted this to be static inside radio_init. but sdcc has a problem with that ("relocation error")
CONSTMEM uint8_t reg_1c_25[] = {
    0x1E, // IF Filter Bandwidth: IF Filter Coefficient Sets = 14, IF Filter Decimation Rates = 1
    0x40, // AFC Loop Gearshift Override: AFC Enable
    0x0a, // AFC Timing Control: shwait = 1, anwait = 2
    0x03, // Clock Recovery Gearshift Override: crslow = 3
    0xC8, // Clock Recovery Oversampling Rate: 0xC8
    0x00, // Clock Recovery Offset 2: 0
    0xA3, // Clock Recovery Offset 1: 163
    0xD7, // Clock Recovery Offset 0: 55
    0x00, // Clock Recovery Timing Loop Gain 1: 0
    0xAE  // Clock Recovery Timing Loop Gain 0: 174
};
CONSTMEM uint8_t reg_33_39[] = {
    0x0e, // Header Control 2: Fix Transmit/Receive Packet Len = 1, Sync Word Length = 3 and 2 and 1 and 0, MSB of Preamble Length = 0
    0x08, // Preamble Lenght: 8
    0x2A, // Preamble Detection Control 1: RSSI Offset = 2, Preamble Detection Threshold = 5
    0xE9, // Sync Word 3 = 0xE9
    0xCA, // Sync Word 2 = 0xCA
    0xE9, // Sync Word 1 = 0xE9
    0xCA  // Sync word 0 = 0xCA
};
CONSTMEM uint8_t reg_6d_77[] = {
    0x1F, // TX Power:LNA Switch Controller = 1, TX Output Power = 7 (max. Power)
    0x51, // TX Data Rate 1: 81
    0xEC, // TX Date Rate 0: 236
    0x2c, // Modulation Mode Control 1: Manchester Data Inversion = 1, Manchester Preamble Polarity = 1, txdtrtscale = 1
    0x22, // Modulation Mode Control 2: Modtyp = FSK (2), Modulation Source = FIFO (0x10)
    0x1E, // Frequency Deviation: 30
    0x00, // Frequency Offset 1: 0
    0x00, // Frequency Offset 2: 0
    0x73, // Frequency Band Select: Side Band Select = 1, High Band Select = 1, Frequency Band Select = 19 (860 - 870 MHz)
    0x67, // Nominal Carrier Frequency High Byte: 103
    0xC0  // Nominal Carrier Frequency Low Byte: 293
};
void radio_init(void)
{
	spi_init();
	spi_enable();

	// reset Si4431
	//_delay_us(5);
	radio_select();
	delay_us(10);
	radio_deselect();
	delay_us(41);

	//partnum = read_reg(SI4430_DEVICE_TYPE);
	//version = read_reg(SI4430_DEVICE_VERSION);

	// reset and wait for chip ready
	radio_write_reg(SI4430_OMFC1, SI4430_SWRES | SI4430_XTON);
    while (!(radio_read_reg(SI4430_STATUS2) & SI4430_CHIPRDY))
			;

	radio_write_reg(SI4430_GPIOCONF0, 0x1f); // set GPIO2 to GND output (instead of default CLK output!)
	radio_write_reg(SI4430_GPIOCONF1, 0x1f); // set GPIO2 to GND output (instead of default CLK output!)
	radio_write_reg(SI4430_GPIOCONF2, 0x1f); // set GPIO2 to GND output (instead of default CLK output!)

	// write all settings from Si443x-Register-Settings.ods
	// no - write all registers as eq3 does it. the values below were observed using the real firmware
	radio_write_burst(0x1c, sizeof(reg_1c_25), reg_1c_25);
	radio_write_reg(SI4430_RSSITH, 80);
    radio_write_reg(0x2a, 0x28); // AFC Limiter: 40

    radio_write_reg(0x30, 0x89); // Data Access Control: CRC = 1 (CRC-16), CRC Disabled, Enable Packet TX Handling = 1, Enable Packet RX Handling = 1
	radio_write_burst(0x33, sizeof(reg_33_39), reg_33_39);

    radio_write_reg(0x58, 0x80); // ChargePumpCurrentTimingOverride = 0x80
    radio_write_reg(0x59, 0x40); // Divider Current Timing = 0x40

    radio_write_reg(0x69, 0x60); // AGC Override 1: Sign = 1, AGC Enable = 1
	
	radio_write_burst(0x6d, sizeof(reg_6d_77), reg_6d_77);

	// TODO we could also enable almost full interrupt and readout the length byte as soon as possible (almost full threshold = 0)
	// TODO then with the length information we could update the almost full threshold and when it triggers again readout the packet
	// TODO the pkglen register should then only be used as absolute maximum length packet backup recognition. in case we mix anything up
	radio_write_reg(SI4430_INT1, SI4430_PKGVALID | SI4430_PKGSENT); // enable pkg valid/sent interrupt
	//radio_write_reg(SI4430_INT2, SI4430_SWDET | SI4430_PREAVAL | SI4430_RSSI | SI4430_CHIPRDY); // enable sync word detect interrupt

	radio_state = radio_idle;
	radio_write_reg(SI4430_OMFC1, 0); // goto idle mode

	WFE_CR2 |= WFE_CR2_EXTI_EV4; // nIQR is PB4 which is by default mapped to EXTI4
	PB_CR2 |= (1u<<4); // PB4 external interrupt enabled

	spi_disable();
}
