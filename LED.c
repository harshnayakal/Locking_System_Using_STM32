/*---------------------------------------------------------
 File        : led.c
 Device      : STM32F103C8T6
 Toolchain   : Keil uVision

 Description :
      LED Driver Source File

 Connections

 LED1 -> PA12
 LED2 -> PA13
 LED3 -> PA14
 LED4 -> PA15
---------------------------------------------------------*/

#include "led.h"

/*---------------------------------------------------------
Function : LED_Init

Description :
    Initialize PA12-PA15 as Output Push Pull
---------------------------------------------------------*/
void LED_Init(void)
{
    /* Enable GPIOA Clock */
    RCC->APB2ENR |= (1 << 2);

    /*
        PA12-PA15
        Output Push Pull
        MODE = 10 (2 MHz)
        CNF  = 00
    */

    GPIOA->CRH &= ~(0xFFFF0000);
    GPIOA->CRH |=  (0x22220000);

    LED_AllOFF();
}

/*---------------------------------------------------------
Function : LED1_ON
---------------------------------------------------------*/
void LED1_ON(void)
{
    GPIOA->BSRR = LED1;
}

/*---------------------------------------------------------
Function : LED1_OFF
---------------------------------------------------------*/
void LED1_OFF(void)
{
    GPIOA->BRR = LED1;
}

/*---------------------------------------------------------
Function : LED2_ON
---------------------------------------------------------*/
void LED2_ON(void)
{
    GPIOA->BSRR = LED2;
}

/*---------------------------------------------------------
Function : LED2_OFF
---------------------------------------------------------*/
void LED2_OFF(void)
{
    GPIOA->BRR = LED2;
}

/*---------------------------------------------------------
Function : LED3_ON
---------------------------------------------------------*/
void LED3_ON(void)
{
    GPIOA->BSRR = LED3;
}

/*---------------------------------------------------------
Function : LED3_OFF
---------------------------------------------------------*/
void LED3_OFF(void)
{
    GPIOA->BRR = LED3;
}

/*---------------------------------------------------------
Function : LED4_ON
---------------------------------------------------------*/
void LED4_ON(void)
{
    GPIOA->BSRR = LED4;
}

/*---------------------------------------------------------
Function : LED4_OFF
---------------------------------------------------------*/
void LED4_OFF(void)
{
    GPIOA->BRR = LED4;
}

/*---------------------------------------------------------
Function : LED_AllON
---------------------------------------------------------*/
void LED_AllON(void)
{
    GPIOA->BSRR = LED1 | LED2 | LED3 | LED4;
}

/*---------------------------------------------------------
Function : LED_AllOFF
---------------------------------------------------------*/
void LED_AllOFF(void)
{
    GPIOA->BRR = LED1 | LED2 | LED3 | LED4;
}

/*---------------------------------------------------------
Function : LED_UnlockSequence

Description :
    LEDs turn ON one by one
---------------------------------------------------------*/
void LED_UnlockSequence(void)
{
    LED_AllOFF();

    LED1_ON();
    delay_ms(200);

    LED2_ON();
    delay_ms(200);

    LED3_ON();
    delay_ms(200);

    LED4_ON();
    delay_ms(200);
}

/*---------------------------------------------------------
Function : LED_LockSequence

Description :
    LEDs turn OFF one by one
---------------------------------------------------------*/
void LED_LockSequence(void)
{
    LED4_OFF();
    delay_ms(200);

    LED3_OFF();
    delay_ms(200);

    LED2_OFF();
    delay_ms(200);

    LED1_OFF();
    delay_ms(200);
}