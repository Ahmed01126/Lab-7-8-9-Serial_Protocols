/**
 * tc72.h
 *
 *  Created on: Wed May 24 2023
 *  Author    : Abdullah Darwish
 */

#ifndef TC72_H
#define TC72_H

void Tc72_Init(unsigned char Mode);

void Tc72_RegisterWrite(unsigned char RegAdd, unsigned char Data);

void Tc72_RegisterRead(unsigned char RegAdd, unsigned char * DataPtr);

#endif /* TC72_H */
