#ifndef STEPPER_H
#define STEPPER_H

#include "stm32f4xx.h"

void motorInit(void);
void motorOn(void);
void motorOff(void);
void stepDir(int64_t steps, float speed, int8_t dir);

#endif