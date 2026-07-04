/*---------------------------------------------------------
 File        : lcd.c
 Device      : STM32F103C8T6
 Toolchain   : Keil uVision

 Description :
      16x2 LCD Driver (8-bit Mode)

 Connections

 RS -> PB0
 EN -> PB1
 D0 -> PB8
 D1 -> PB9
 D2 -> PB10
 D3 -> PB11
 D4 -> PB12
 D5 -> PB13
 D6 -> PB14
 D7 -> PB15
---------------------------------------------------------*/

#include "lcd.h"

/*---------------------------------------------------------
Function Name : LCD_Command

Description :
    Send Command to LCD
---------------------------------------------------------*/
void LCD_Command(unsigned char cmd)
{
    /* RS = 0 */
    GPIOB->BRR = (1<<LCD_RS);

    /* Clear PB8-PB15 */
    GPIOB->ODR &= 0x00FF;

    /* Put command on data bus */
    GPIOB->ODR |= ((unsigned int)cmd << 8);

    /* Enable Pulse */
    GPIOB->BSRR = (1<<LCD_EN);
    delay_us(2);

    GPIOB->BRR = (1<<LCD_EN);

    delay_ms(2);
}

/*---------------------------------------------------------
Function Name : LCD_Char

Description :
    Send Character to LCD
---------------------------------------------------------*/
void LCD_Char(unsigned char data)
{
    /* RS = 1 */
    GPIOB->BSRR = (1<<LCD_RS);

    /* Clear Data Pins */
    GPIOB->ODR &= 0x00FF;

    /* Send Data */
    GPIOB->ODR |= ((unsigned int)data << 8);

    /* Enable Pulse */
    GPIOB->BSRR = (1<<LCD_EN);

    delay_us(2);

    GPIOB->BRR = (1<<LCD_EN);

    delay_ms(2);
}

/*---------------------------------------------------------
Function Name : LCD_String

Description :
    Display String
---------------------------------------------------------*/
void LCD_String(unsigned char *str)
{
    while(*str)
    {
        LCD_Char(*str);
        str++;
    }
}

/*---------------------------------------------------------
Function Name : LCD_Clear

Description :
    Clear LCD
---------------------------------------------------------*/
void LCD_Clear(void)
{
    LCD_Command(LCD_CLEAR);

    delay_ms(2);
}

/*---------------------------------------------------------
Function Name : LCD_SetCursor

Description :
    Move Cursor
---------------------------------------------------------*/
void LCD_SetCursor(unsigned char row,unsigned char col)
{
    unsigned char address;

    if(row==0)
    {
        address = LCD_LINE1 + col;
    }
    else
    {
        address = LCD_LINE2 + col;
    }

    LCD_Command(address);
}

/*---------------------------------------------------------
Function Name : LCD_UInt

Description :
    Display Unsigned Integer
---------------------------------------------------------*/
void LCD_UInt(unsigned int num)
{
    unsigned char buffer[10];
    signed char i = 0;

    if(num == 0)
    {
        LCD_Char('0');
        return;
    }

    while(num > 0)
    {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    while(i > 0)
    {
        LCD_Char(buffer[--i]);
    }
}

/*---------------------------------------------------------
Function Name : LCD_Init

Description :
    Initialize LCD in 8-bit Mode
---------------------------------------------------------*/
void LCD_Init(void)
{
    /* Enable GPIOB Clock */
    RCC->APB2ENR |= (1<<3);

    /*-----------------------------------------------------
      PB0, PB1 Output Push-Pull
    -----------------------------------------------------*/
    GPIOB->CRL &= ~((0xF<<0) | (0xF<<4));

    GPIOB->CRL |=  ((0x2<<0) | (0x2<<4));

    /*-----------------------------------------------------
      PB8-PB15 Output Push-Pull
    -----------------------------------------------------*/
    GPIOB->CRH = 0x22222222;

    delay_ms(20);

    /* LCD Initialization Sequence */

    LCD_Command(0x30);
    delay_ms(5);

    LCD_Command(0x30);
    delay_ms(1);

    LCD_Command(0x30);
    delay_ms(1);

    LCD_Command(LCD_MODE_8BIT);

    LCD_Command(LCD_OFF);

    LCD_Clear();

    LCD_Command(LCD_ENTRY_RIGHT);

    LCD_Command(LCD_ON);

    LCD_Command(LCD_HOME);

    delay_ms(2);
}