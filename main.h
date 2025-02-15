#ifndef MAIN_H
#define MAIN_H
#include "stm32f4xx_hal.h"

#define RFID_SCK_Pin GPIO_PIN_5
#define RFID_SCK_GPIO_Port GPIOA
#define RFID_MISO_Pin GPIO_PIN_6
#define RFID_MISO_GPIO_Port GPIOA
#define RFID_MOSI_Pin GPIO_PIN_7
#define RFID_MOSI_GPIO_Port GPIOA
#define RFID_CS_Pin GPIO_PIN_0 //SDA //IRQ of RFID is not connected
#define RFID_CS_GPIO_Port GPIOB
#define RFID_RST_Pin GPIO_PIN_8
#define RFID_RST_GPIO_Port GPIOA

#define STEPPER_IN3_Pin GPIO_PIN_8
#define STEPPER_IN3_GPIO_Port GPIOC
#define STEPPER_IN4_Pin GPIO_PIN_9
#define STEPPER_IN4_GPIO_Port GPIOC
#define STEPPER_IN1_Pin GPIO_PIN_8
#define STEPPER_IN1_GPIO_Port GPIOB
#define STEPPER_IN2_Pin GPIO_PIN_9
#define STEPPER_IN2_GPIO_Port GPIOB

extern int stepNumber;
extern int dir;
extern uint32_t duration;
extern float distance;

#endif