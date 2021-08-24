#include "as_send_device_info.h"
#include "as_send.h"

extern uint8_t as_cnt;

void as_send_device_info()
{
    as_packet_t dev_info;

    dev_info.length = 26;
    dev_info.counter = as_cnt++;
    dev_info.flags = AS_FLAG_DEF;
    dev_info.type = 0x00;
    dev_info.payload[0] = 0x18; // fw version
    dev_info.payload[1] = 0x00;
    dev_info.payload[2] = 0x2F; //model version
    for(int i=0; i<10; i++) {
        dev_info.payload[i+3] = hm_serial[i];
        if(i<3) {
            dev_info.from[i] = hm_id[i];
            dev_info.to[i] = hm_master_id[i];
        }
    }
    dev_info.payload[13] = 0x80; // Device Subtype
    dev_info.payload[14] = 0x01; // Channel Count
    dev_info.payload[15] = 0x00;
    dev_info.payload[16] = 0x00; // Device Info
	if (!ID_IS_NULL(hm_master_id))
		dev_info.flags |= AS_FLAG_BIDI;

	as_send(&dev_info);
}
