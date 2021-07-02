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
#include <stdbool.h>

extern volatile uint16_t tick_count;
extern volatile uint16_t timeout_at;
extern volatile bool wait_for_timeout;

static volatile e_request request_operation = OPERATION_NONE;
static volatile uint8_t timer_request = TIMER_NONE;
bool window_open = false;

void tick_isr() __interrupt(19) {
    TIM2_SR1 &= ~(1<<0); // Clear interrupt
    tick_count++;
    if(wait_for_timeout) {
        if(tick_count == timeout_at) {
            wait_for_timeout = false;
        }
    }
}

void singleshot_isr() __interrupt(21) {
    TIM3_SR1 &= ~(1 << 0); // Clear interrupt
    if(timer_request & TIMER_BUTTON) {
        request_operation = OPERATION_CONFIG_PAIR;
    }
    if(timer_request & TIMER_REL) {
        request_operation = OPERATION_CHECK_REL;
    }
    timer_request = TIMER_NONE;
    clear_singleshot_timer();
}

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

void button_isr() __interrupt(13) {
    EXTI_SR1 |= BUTTON;
    clear_singleshot_timer();
    set_singleshot_timer(20);
    timer_request |= TIMER_BUTTON;
}

void rel_isr() __interrupt(14) {
    EXTI_SR1 |= REL;
    clear_singleshot_timer();
    set_singleshot_timer(100);
    timer_request |= TIMER_REL;
}

static void rel_init() {
    PA_DDR &= ~REL; // Configure input
    PA_CR1 |= REL; // Enable pull-up
    PA_CR2 |= REL; // Enable external interrupt
    EXTI_CR2 |= (1 << 4) | (1 << 5); // Enable rising and falling edge interrupt
}

static void button_init() {
    PA_DDR &= ~BUTTON;
    PA_CR1 |= BUTTON;
    PA_CR2 |= BUTTON;
    EXTI_CR2 |= (1 << 3); // | (1 << 2); // Falling edge interrupt
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
    rel_init();
    button_init();
    radio_init();
    enable_interrupts();
    check_rel();
    for(;;) {
        wfi();
        check_operation();
    }
}
