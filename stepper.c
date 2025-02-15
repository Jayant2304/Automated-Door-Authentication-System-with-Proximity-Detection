#include "stm32f4xx_hal.h"
#include "delay.h"
#include "stepper.h"
#include "main.h"

void motorInit(void) {
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
	 /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = STEPPER_IN3_Pin|STEPPER_IN4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = STEPPER_IN1_Pin|STEPPER_IN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void motorOn(void)
{
    // Find out which step the motor is on
    switch (stepNumber)
    {
      case 0:
          HAL_GPIO_WritePin(STEPPER_IN1_GPIO_Port, STEPPER_IN1_Pin, GPIO_PIN_SET);   // IN1
          HAL_GPIO_WritePin(STEPPER_IN2_GPIO_Port, STEPPER_IN2_Pin, GPIO_PIN_RESET); // IN2
          HAL_GPIO_WritePin(STEPPER_IN3_GPIO_Port, STEPPER_IN3_Pin, GPIO_PIN_SET); // IN3
          HAL_GPIO_WritePin(STEPPER_IN4_GPIO_Port, STEPPER_IN4_Pin, GPIO_PIN_RESET);   // IN4
        break;
      case 1:
          HAL_GPIO_WritePin(STEPPER_IN1_GPIO_Port, STEPPER_IN1_Pin, GPIO_PIN_SET);   // IN1
          HAL_GPIO_WritePin(STEPPER_IN2_GPIO_Port, STEPPER_IN2_Pin, GPIO_PIN_RESET); // IN2
          HAL_GPIO_WritePin(STEPPER_IN3_GPIO_Port, STEPPER_IN3_Pin, GPIO_PIN_RESET);   // IN3
          HAL_GPIO_WritePin(STEPPER_IN4_GPIO_Port, STEPPER_IN4_Pin, GPIO_PIN_SET); // IN4
        break;
      case 2:
          HAL_GPIO_WritePin(STEPPER_IN1_GPIO_Port, STEPPER_IN1_Pin, GPIO_PIN_RESET); // IN1
          HAL_GPIO_WritePin(STEPPER_IN2_GPIO_Port, STEPPER_IN2_Pin, GPIO_PIN_SET);   // IN2
          HAL_GPIO_WritePin(STEPPER_IN3_GPIO_Port, STEPPER_IN3_Pin, GPIO_PIN_RESET);   // IN3
          HAL_GPIO_WritePin(STEPPER_IN4_GPIO_Port, STEPPER_IN4_Pin, GPIO_PIN_SET); // IN4
        break;
      case 3:
          HAL_GPIO_WritePin(STEPPER_IN1_GPIO_Port, STEPPER_IN1_Pin, GPIO_PIN_RESET); // IN1
          HAL_GPIO_WritePin(STEPPER_IN2_GPIO_Port, STEPPER_IN2_Pin, GPIO_PIN_SET);   // IN2
          HAL_GPIO_WritePin(STEPPER_IN3_GPIO_Port, STEPPER_IN3_Pin, GPIO_PIN_SET); // IN3
          HAL_GPIO_WritePin(STEPPER_IN4_GPIO_Port, STEPPER_IN4_Pin, GPIO_PIN_RESET);   // IN4
        break;
      default:
        break;
    }
    delaymS(5);
}

void motorOff(void)
{
    // Switch off the idle current to the motor
    // Otherwise L298N module will heat up
    HAL_GPIO_WritePin(STEPPER_IN1_GPIO_Port, STEPPER_IN1_Pin, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(STEPPER_IN2_GPIO_Port, STEPPER_IN2_Pin, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(STEPPER_IN3_GPIO_Port, STEPPER_IN3_Pin, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(STEPPER_IN4_GPIO_Port, STEPPER_IN4_Pin, GPIO_PIN_RESET); // IN4
}

void stepDir(int64_t steps, float speed, int8_t dir)
{
  uint32_t delay = 60 * 1000 / 200 / speed;
  for(int x = 0; x < steps; x += 1)
  {
    // Step to the previous step
	switch (stepNumber)
	{
		case 0:
			HAL_GPIO_WritePin(STEPPER_IN1_GPIO_Port, STEPPER_IN1_Pin, GPIO_PIN_SET);   // IN1
			HAL_GPIO_WritePin(STEPPER_IN2_GPIO_Port, STEPPER_IN2_Pin, GPIO_PIN_RESET); // IN2
			HAL_GPIO_WritePin(STEPPER_IN3_GPIO_Port, STEPPER_IN3_Pin, GPIO_PIN_SET); // IN3
			HAL_GPIO_WritePin(STEPPER_IN4_GPIO_Port, STEPPER_IN4_Pin, GPIO_PIN_RESET);   // IN4
			break;
		case 1:
			HAL_GPIO_WritePin(STEPPER_IN1_GPIO_Port, STEPPER_IN1_Pin, GPIO_PIN_SET);   // IN1
			HAL_GPIO_WritePin(STEPPER_IN2_GPIO_Port, STEPPER_IN2_Pin, GPIO_PIN_RESET); // IN2
			HAL_GPIO_WritePin(STEPPER_IN3_GPIO_Port, STEPPER_IN3_Pin, GPIO_PIN_RESET);   // IN3
			HAL_GPIO_WritePin(STEPPER_IN4_GPIO_Port, STEPPER_IN4_Pin, GPIO_PIN_SET); // IN4
			break;
		case 2:
			HAL_GPIO_WritePin(STEPPER_IN1_GPIO_Port, STEPPER_IN1_Pin, GPIO_PIN_RESET); // IN1
			HAL_GPIO_WritePin(STEPPER_IN2_GPIO_Port, STEPPER_IN2_Pin, GPIO_PIN_SET);   // IN2
			HAL_GPIO_WritePin(STEPPER_IN3_GPIO_Port, STEPPER_IN3_Pin, GPIO_PIN_RESET);   // IN3
			HAL_GPIO_WritePin(STEPPER_IN4_GPIO_Port, STEPPER_IN4_Pin, GPIO_PIN_SET); // IN4
			break;
		case 3:
			HAL_GPIO_WritePin(STEPPER_IN1_GPIO_Port, STEPPER_IN1_Pin, GPIO_PIN_RESET); // IN1
			HAL_GPIO_WritePin(STEPPER_IN2_GPIO_Port, STEPPER_IN2_Pin, GPIO_PIN_SET);   // IN2
			HAL_GPIO_WritePin(STEPPER_IN3_GPIO_Port, STEPPER_IN3_Pin, GPIO_PIN_SET); // IN3
			HAL_GPIO_WritePin(STEPPER_IN4_GPIO_Port, STEPPER_IN4_Pin, GPIO_PIN_RESET);   // IN4
			break;
		default:
			break;
	}
    stepNumber = ((stepNumber + 1 * dir) + 4) % 4;
    delaymS(delay);
  }
}