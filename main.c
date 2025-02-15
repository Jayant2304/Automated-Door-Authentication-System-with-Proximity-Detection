#include "stm32f4xx_hal.h"
#include "rfid.h"
#include "spi.h"
#include "delay.h"
#include "stepper.h"
#include "ultrasonic.h"
#include <string.h>

#define SysTick_CTRL_COUNTFLAG (1UL << 16)

uint8_t rfid_id[4];
SPI_HandleTypeDef hspi1;
GPIO_InitTypeDef GPIO_InitStruct;
uint32_t duration;
float distance;
int stepNumber=0;
uint8_t reg_rfid[10][4];
uint8_t next_id = 0;

void reg_id(void) {
	for (int i = 0; i < 4; i++) {
		reg_rfid[next_id][i] = rfid_id[i];
	}
	next_id++;
}

bool check_if_reg() {
	for (int i = 0; i < next_id; i++) {
		if (rc522_compareIds(reg_rfid[i], rfid_id))
			return true;
	}
	return false;
}

void door_routine() {
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_11)) {
		if (!check_if_reg())
			reg_id();
	}
	
	if (check_if_reg()) {
		motorOn();
		stepDir(50, 30.0f, 1);
		motorOff();
		
		distance = run_ultrasonic();
		while (distance <= 10) {
			distance = run_ultrasonic();
			delaymS(100);
		}
		
		motorOn();
		stepDir(50, 30.0f, -1);
		motorOff();
	}
}

void SysTick_Handler() {
	return;
}

void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the
     device is clocked below the maximum system frequency (see datasheet). */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 |
                                RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

void TIM1_Init() {
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;  /*Enable TIM1 clock*/
		TIM1->PSC = 84 -1;  /* 168 000 000 /84 = 2000 000*/
		TIM1->ARR = 2 -1;  /* 2000 000 /2 = 1000 000*/
		TIM1->CNT =0;
		TIM1->CR1 =1;
}

int main() {
	SystemClock_Config();
	TIM1_Init();
	SPI_Init();
	rc522_init();
	ultrasonic_init();
	motorInit();
	motorOff();
	delaymS(100);
	
	while(1) {
		if (rc522_checkCard(rfid_id)) {
			rc522_regWrite8(MFRC522_REG_FIFO_LEVEL, 0x80);
			door_routine();
			memset(rfid_id, 0, 4);
			delaymS(1000);
		}
		
		delaymS(100);
	}
	
}