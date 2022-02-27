#include "stm8l.h"
#include "medion-hm-sec-sc.h"
#include "led_on.h"
#include "led_off.h"
#include "led_init.h"
#include "led_toggle.h"
#include "led_timer_deinit.h"
#include "wait_for_led.h"
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
#include "rtc_isr.h"
#include "button_init.h"
#include "button_isr.h"
#include "relay_init.h"
#include "relay_isr.h"
#include "measure_battery.h"
#include "as_factory_reset.h"
#include "rtc_battery_timer_enable.h"
#include <stdbool.h>

volatile e_request request_operation = OPERATION_NONE;
volatile uint8_t timer_request = TIMER_NONE;
bool window_open = false;
bool button_pressed_while_boot = false;
extern const uint8_t * cyclic_info;

static void check_rel() {
    if(PA_IDR & REL) { // magnet not present
        if(!window_open) {
            window_open = true;
            tick_init();
            as_send_contact_state(false);
            tick_deinit();
        }
    } else { // magnet present
        if(window_open) {
            window_open = false;
            tick_init();
            as_send_contact_state(false);
            tick_deinit();
        }
    }
}

static void enter_halt() {
    tick_deinit();
    clear_singleshot_timer();
    wait_for_led();
    led_timer_deinit();
    // We cancel the halt process if an interrupt thas occured in the meantime
    if(request_operation == OPERATION_NONE || request_operation == OPERATION_ENTER_HALT) {
        __asm__("halt");
    }
}

static void check_operation() {
    switch(request_operation) {
    case OPERATION_CHECK_REL:
        request_operation = OPERATION_NONE;
        check_rel();

        if(*cyclic_info) {
            rtc_battery_timer_enable();
        }
        enter_halt();
        break;
    case OPERATION_BUTTON_SHORT:
        request_operation = OPERATION_NONE;
        tick_init();
        as_poll();
        tick_deinit();

        if(*cyclic_info) {
            rtc_battery_timer_enable();
        }

        enter_halt();
        break;
    case OPERATION_BUTTON_LONG:
        if(button_pressed_while_boot) {
            button_pressed_while_boot = false;
            as_factory_reset();
            led_blink(LED_BLINK_THRICE);
        }
        request_operation = OPERATION_NONE;
        enter_halt();
        break;
    case OPERATION_MEASURE_BATTERY:
        request_operation = OPERATION_NONE;
        tick_init();
        measure_battery();
        as_send_contact_state(true);
        tick_deinit();
        enter_halt();
        break;
    case OPERATION_ENTER_HALT:
        request_operation = OPERATION_NONE;
        enter_halt();
        break;
    case OPERATION_NONE:
    break;
    }
}

static void gpio_configure_unused() {
    PA_DDR = 0;
    PA_CR1 = 0xff;
    PB_DDR = 0;
    PB_CR1 = 0xff;
    PC_DDR = 0;
    PC_CR1 = 0xff;
    PD_DDR = 0;
    PD_CR1 = 0xff;
    PE_DDR = 0;
    PE_CR1 = 0xff;
    PF_DDR = 0;
    PF_CR1 = 0xff;
}

void main(void) {
    disable_interrupts();
    gpio_configure_unused();
    led_init();
    led_off();
    relay_init();
    button_init();
    radio_init();
    // If the battery is critically low,
    // refuse operation.
    if(measure_battery() <= BAT_THRESHOLD_CRITICAL)
        __asm__("halt");

    enable_interrupts();
    check_rel();
    rtc_battery_timer_enable();
    request_operation = OPERATION_ENTER_HALT;
    for(;;) {
        check_operation();
    }
}
