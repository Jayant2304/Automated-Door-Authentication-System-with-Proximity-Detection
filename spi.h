#ifndef SPI_H
#define SPI_H

#include "stm32f4xx_hal.h"

void SPI_Init();
void spi1_transmit(uint8_t *data,uint32_t size);
void spi1_receive(uint8_t *data,uint32_t size);

#endif