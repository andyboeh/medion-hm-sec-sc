#ifndef MEDION_HM_SEC_SC_H
#define MEDION_HM_SEC_SC_H

// B3
#define nSEL (1u<<3)
// B4
#define nIRQ (1u<<4)
// B7
#define MISO (1u<<7)
// B5
#define SCLK (1u<<5)
// B6
#define MOSI (1u<<6)
// A7
#define LED (1<<7)
// A6
#define REL (1<<6)
// A5
#define BUTTON (1<<5)

#define F_CPU 2000000UL  // 2MHz

typedef enum {
    OPERATION_NONE = 0,
    OPERATION_CHECK_REL,
    OPERATION_BUTTON_SHORT,
    OPERATION_BUTTON_LONG,
    OPERATION_ENTER_HALT,
} e_request;

typedef enum {
    BUTTON_PRESS_NONE = 0,
    BUTTON_PRESS_SHORT,
    BUTTON_PRESS_LONG
} e_button_press_type;

#define TIMER_NONE    0x00
#define TIMER_BUTTON  (1 << 1)
#define TIMER_REL     (1 << 2)

// Set battery state to low if it is
// below threshold
// Refuse operation if we are critical
#define BAT_THRESHOLD_LOW      22
#define BAT_THRESHOLD_CRITICAL 19

#endif //MEDION_HM_SEC_SC_H
