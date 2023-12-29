#include "as_handle_cyclic_info.h"
#include "rtc_battery_timer_enable.h"
#include "rtc_battery_timer_disable.h"
#include "as_defines.h"

void as_handle_cyclic_info(void) {
    if(*cyclic_info) {
        rtc_battery_timer_enable();
    } else {
        rtc_battery_timer_disable();
    }
}
