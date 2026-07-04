/*---------------------------------------------------------
 File        : lcd.h
 Device      : STM32F103C8T6
 Toolchain   : Keil uVision

 Description :
    16x2 LCD Header File
    8-bit Interface
---------------------------------------------------------*/

#ifndef __LCD_H
#define __LCD_H

#include "stm32f10x.h"
#include "delay.h"

/**************** LCD PIN DEFINITIONS ****************/

#define LCD_RS     0      // PB0
#define LCD_EN     1      // PB1

/**************** LCD COMMANDS ****************/

/* Basic Commands */
#define LCD_CLEAR          0x01
#define LCD_HOME           0x02

/* Entry Mode */
#define LCD_ENTRY_RIGHT    0x06
#define LCD_ENTRY_LEFT     0x04

/* Display Control */
#define LCD_OFF            0x08
#define LCD_ON             0x0C
#define LCD_CURSOR_ON      0x0E
#define LCD_CURSOR_BLINK   0x0F

/* Cursor Shift */
#define LCD_SHIFT_LEFT     0x10
#define LCD_SHIFT_RIGHT    0x14

/* Display Shift */
#define LCD_DISP_LEFT      0x18
#define LCD_DISP_RIGHT     0x1C

/* Function Set */
#define LCD_MODE_8BIT      0x38
#define LCD_MODE_4BIT      0x28

/* DDRAM Address */
#define LCD_LINE1          0x80
#define LCD_LINE2          0xC0

/**************** FUNCTION PROTOTYPES ****************/

/* Initialization */
void LCD_Init(void);

/* Command/Data Functions */
void LCD_Command(unsigned char cmd);
void LCD_Char(unsigned char data);

/* Display Functions */
void LCD_String(unsigned char *str);
void LCD_Clear(void);

/* Cursor Functions */
void LCD_SetCursor(unsigned char row, unsigned char col);

/* Number Display */
void LCD_UInt(unsigned int num);

#endif