#include "stm32f4xx_hal.h"

void delayuS(uint32_t us) //delay for certain amount in microseconds
{
		for(uint32_t i =0;i<(us);i++){

			while(!(TIM1->SR & TIM_SR_UIF)){}   /*wait for UIF set*/
			TIM1->SR &= ~TIM_SR_UIF;

	}
}

void delaymS(uint32_t ms) //delay for certain amount in milliseconds
{
	for (uint32_t i = 0; i < ms; i++) {
		delayuS(1000);
	}
}