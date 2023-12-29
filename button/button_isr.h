#ifndef BUTTON_ISR_H
#define BUTTON_ISR_H

void button_isr(void) __interrupt(13);
void handle_button_pressed(void);
void handle_button_released(void);

#endif //BUTTON_ISR_H
