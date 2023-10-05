/**
 * Spi.h
 *
 *  Created on: Wed May 24 2023
 *  Author    : Abdullah Darwish
 */

#ifndef SPI_H
#define SPI_H

#include "Std_Types.h"

typedef struct 
{
    uint32 CR1;
    uint32 UNUSED;
    uint32 SR;
    uint32 DR;
    uint32 CRCPR;
    uint32 RXCRCR;
    uint32 TXCRCR;
    uint32 I2SCFGR;
    uint32 I2SPR;
}SpiType;


/* Master or Slave */
#define SPI_SLAVE  0
#define SPI_MASTER 1

/* Clock Polarity */
#define SPI_IDLE_LOW  0
#define SPI_IDLE_HIGH 1

/* Clock Phase */
#define SPI_SAMPLE_FIRST_TRANSITION  0 // Read or Capture on first transition
#define SPI_SAMPLE_SOCAND_TRANSITION 1



void Spi1_Init(uint8 MasterSlave, uint8 ClkPol, uint8 ClkPhase);

uint8 Spi1_TransmitRecieveByte(uint8 TxData);

#endif /* SPI_H */
