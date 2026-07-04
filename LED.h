/*---------------------------------------------------------
 File        : led.h
 Device      : STM32F103C8T6
 Toolchain   : Keil uVision

 Description :
    LED Driver Header File

 Connections

 LED1 -> PA12
 LED2 -> PA13
 LED3 -> PA14
 LED4 -> PA15
---------------------------------------------------------*/

#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"
#include "delay.h"

/**************** LED PIN DEFINITIONS ****************/

#define LED1    (1<<12)
#define LED2    (1<<13)
#define LED3    (1<<14)
#define LED4    (1<<15)

/**************** FUNCTION PROTOTYPES ****************/

void LED_Init(void);

void LED_AllON(void);

void LED_AllOFF(void);

void LED1_ON(void);
void LED1_OFF(void);

void LED2_ON(void);
void LED2_OFF(void);

void LED3_ON(void);
void LED3_OFF(void);

void LED4_ON(void);
void LED4_OFF(void);

void LED_UnlockSequence(void);

void LED_LockSequence(void);

#endif