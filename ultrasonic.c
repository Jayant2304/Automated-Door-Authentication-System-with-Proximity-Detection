#include "ultrasonic.h"
#include "delay.h"
#include "main.h"

void ultrasonic_init(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //enable GPIOA Clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //enable GPIOD Clock
	GPIOA->MODER |= (1<<0);   //set PA0 to Output
	GPIOD->MODER &= 0xFF3FFFFF;
	GPIOA->MODER &= ~(3 << 2); // Clear PA1 mode bits
}

uint32_t run_ultrasonic(void)
{
		Trig_low; //turn off trig
		delayuS(4); //wait 4uS
		Trig_high;   //turn on trig
		delayuS(10);
		Trig_low;
		duration=read_echo(400000);    //measure the time of echo pin
		distance=(float)(((duration)/59.0));
		return distance;
}

uint32_t read_echo(uint32_t timeout) {
    uint32_t duration = 0;

    // Wait for Echo pin to go high
    while (!(GPIOA->IDR & GPIO_IDR_ID1)) {
        duration++;
        //delayuS(1);
        if (duration > timeout) return 0; // Timeout
    }

    duration = 0;

    // Measure how long Echo pin stays high
    while (GPIOA->IDR & GPIO_IDR_ID1) {
        duration++;
        //delayuS(1);
        if (duration > timeout) return 0; // Timeout
    }

    return duration;
}