/*---------------------------------------------------------
 File        : buzzer.h
 Device      : STM32F103C8T6
 Toolchain   : Keil uVision

 Description :
      Buzzer Driver Header

 Connection

 Buzzer -> PA8
---------------------------------------------------------*/

#ifndef __BUZZER_H
#define __BUZZER_H

#include "stm32f10x.h"
#include "delay.h"

/**************** BUZZER PIN ****************/

#define BUZZER_PIN     (1<<8)

/**************** FUNCTION PROTOTYPES ****************/

void Buzzer_Init(void);

void Buzzer_ON(void);

void Buzzer_OFF(void);

void Buzzer_Beep(unsigned int ms);

void Buzzer_LongBeep(void);

#endif