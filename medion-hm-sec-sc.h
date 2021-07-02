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
    OPERATION_CONFIG_PAIR,
    OPERATION_CHECK_REL,
} e_request;

#define TIMER_NONE    0x00
#define TIMER_BUTTON  (1 << 1)
#define TIMER_REL     (1 << 2)

#endif //MEDION_HM_SEC_SC_H
