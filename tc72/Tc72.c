/**
 * tc72.c
 *
 *  Created on: Wed May 24 2023
 *  Author    : Abdullah Darwish
 */
#include "Spi.h"
#include "tc72.h"

void Tc72_Init(unsigned char Mode) {
    Tc72_RegisterWrite(0x80, Mode);
}

void Tc72_RegisterWrite(unsigned char RegAdd, unsigned char Data) {
  Spi1_TransmitRecieveByte(RegAdd | (1 << 7));
  Spi1_TransmitRecieveByte(Data);
}

void Tc72_RegisterRead(unsigned char RegAdd, unsigned char* DataPtr) {
    Spi1_TransmitRecieveByte(RegAdd & (~(1 << 7)));
    *DataPtr = Spi1_TransmitRecieveByte(0);
}
