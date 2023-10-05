/**
 * Spi.c
 *
 *  Created on: Wed May 24 2023
 *  Author    : Abdullah Darwish
 */

#include "stm32f4xx.h"
#include "Gpio.h"
#include "Gpio_Private.h"
#include "Spi.h"

#define GPIOA_P ((GpioType*) (GPIOA_BASE_ADDR))


#define SPI1_AF_EN() (GPIOA_P->AFRL |= 0x555 << (5 * 4))


#define SPI1 ((SpiType *)0x40013000)


void Spi1_Init(uint8 MasterSlave, uint8 ClkPol, uint8 ClkPhase) {

  Gpio_ConfigPin(GPIO_A, 5, GPIO_AF , GPIO_PUSH_PULL);
  Gpio_ConfigPin(GPIO_A, 6, GPIO_AF , GPIO_PUSH_PULL);
  Gpio_ConfigPin(GPIO_A, 7, GPIO_AF , GPIO_PUSH_PULL);

  SPI1_AF_EN();


  SPI1->CR1 |= (0x3 << SPI_CR1_SSI_Pos);

  SPI1->CR1 &= ~(1 << SPI_CR1_MSTR_Pos);
  SPI1->CR1 |= (MasterSlave << SPI_CR1_MSTR_Pos);

  SPI1->CR1 &= ~(1 << SPI_CR1_CPOL_Pos);
  SPI1->CR1 |= (ClkPol << SPI_CR1_CPOL_Pos);

  SPI1->CR1 &= ~(1 << SPI_CR1_CPHA_Pos);
  SPI1->CR1 |= (ClkPhase << SPI_CR1_CPHA_Pos);

  /*************************************************************************/
  // Baud Rate
  SPI1->CR1 &= ~(0x7 << SPI_CR1_BR_Pos);
  SPI1->CR1 |= (0x3 << SPI_CR1_BR_Pos);  // 16/16 -> 1MHZ
  /*************************************************************************/

  SPI1->CR1 |= (1 << SPI_CR1_SPE_Pos);
}

uint8 Spi1_TransmitRecieveByte(uint8 TxData) {
  if (SPI1->SR & (1 << SPI_SR_TXE_Pos)) {
    SPI1->DR = TxData;
    while (SPI1->SR & (1 << SPI_SR_BSY_Pos));
    return SPI1->DR;
  }
  return -1;
}
