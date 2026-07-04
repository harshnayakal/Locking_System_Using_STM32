/*---------------------------------------------------------
 File        : keypad.h
 Device      : STM32F103C8T6
 Toolchain   : Keil uVision

 Description :
    4x4 Matrix Keypad Header File

 Connections

 Rows
 R1 -> PA0
 R2 -> PA1
 R3 -> PA2
 R4 -> PA3

 Columns
 C1 -> PA4
 C2 -> PA5
 C3 -> PA6
 C4 -> PA7
---------------------------------------------------------*/

#ifndef __KEYPAD_H
#define __KEYPAD_H

#include "stm32f10x.h"
#include "delay.h"
#include "lcd.h"

/**************** Row Pins ****************/

#define ROW1    (1<<0)
#define ROW2    (1<<1)
#define ROW3    (1<<2)
#define ROW4    (1<<3)

/**************** Column Pins ****************/

#define COL1    (1<<4)
#define COL2    (1<<5)
#define COL3    (1<<6)
#define COL4    (1<<7)

/**************** Function Prototypes ****************/

/* Initialize Keypad GPIO */
void Keypad_Init(void);

/* Read one key */
char Keypad_GetKey(void);

/* Read Password */
void Keypad_GetPassword(unsigned char *password,
                        unsigned char length);

/* Read Numeric Input (OTP) */
void Keypad_GetNumber(unsigned char *number,
                      unsigned char length);

#endif