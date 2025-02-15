#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "stm32f4xx.h"

#define Trig_high GPIOA->BSRR=GPIO_BSRR_BS_0 // turn on PA0 (trig pin)
#define Trig_low GPIOA->BSRR=GPIO_BSRR_BR_0 // turn off PA0 (trig pin)

uint32_t run_ultrasonic(void);
uint32_t read_echo(uint32_t timeout);
void ultrasonic_init(void);

#endif