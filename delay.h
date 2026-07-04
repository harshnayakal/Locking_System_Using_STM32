/*---------------------------------------------------------
 File        : delay.h
 Device      : STM32F103C8T6
 Toolchain   : Keil uVision

 Description :
    Delay Function Header
---------------------------------------------------------*/

#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

/* Function Prototypes */

void delay_us(unsigned int us);
void delay_ms(unsigned int ms);
void delay_s(unsigned int sec);

#endif