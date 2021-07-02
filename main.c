#include "stm8l.h"
#include "medion-hm-sec-sc.h"
#include "led_on.h"
#include "led_off.h"
#include "led_init.h"
#include "led_toggle.h"
#include "tick_init.h"
#include "wait_timeout.h"
#include "get_tick.h"
#include "set_timeout.h"
#include "radio_init.h"
#include "as_poll.h"
#include "clear_singleshot_timer.h"
#include "set_singleshot_timer.h"
#include "tick_deinit.h"
#include "as_send_contact_state.h"
#include "led_blink.h"
#include "led_isr.h"
#include "tick_isr.h"
#include "singleshot_isr.h"
#include "button_init.h"
#include "button_isr.h"
#include "relay_init.h"
#include "relay_isr.h"
#include "measure_battery.h"
#include <stdbool.h>

volatile e_request request_operation = OPERATION_NONE;
volatile uint8_t timer_request = TIMER_NONE;
bool window_open = false;

static void check_rel() {
    if(PA_IDR & REL) { // magnet not present
        if(!window_open) {
            window_open = true;
            tick_init();
            as_send_contact_state();
            tick_deinit();
        }
    } else { // magnet present
        if(window_open) {
            window_open = false;
            tick_init();
            as_send_contact_state();
            tick_deinit();
        }
    }
}

static void check_operation() {
    switch(request_operation) {
    case OPERATION_CONFIG_PAIR:
        tick_init();
        as_poll();
        tick_deinit();
    break;
    case OPERATION_CHECK_REL:
        check_rel();
    break;
    case OPERATION_NONE:
    break;
    }
    request_operation = OPERATION_NONE;
}

void main(void) {
    disable_interrupts();
    led_init();
    led_off();
    relay_init();
    button_init();
    radio_init();
    enable_interrupts();
    check_rel();
    for(;;) {
        wfi();
        check_operation();
    }
}
