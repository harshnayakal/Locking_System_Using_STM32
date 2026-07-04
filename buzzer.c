/*---------------------------------------------------------
 File        : buzzer.c
 Device      : STM32F103C8T6
 Toolchain   : Keil uVision

 Description :
      Buzzer Driver Source File

 Connection

 Buzzer -> PA8
---------------------------------------------------------*/

#include "buzzer.h"

/*---------------------------------------------------------
Function Name : Buzzer_Init

Description :
    Configure PA8 as Output Push-Pull
---------------------------------------------------------*/
void Buzzer_Init(void)
{
    /* Enable GPIOA Clock */
    RCC->APB2ENR |= (1 << 2);

    /*
        PA8 Configuration

        MODE = 10 (Output 2MHz)
        CNF  = 00 (Push-Pull)
    */

    GPIOA->CRH &= ~(0xF << 0);
    GPIOA->CRH |=  (0x2 << 0);

    /* Turn OFF Buzzer */
    Buzzer_OFF();
}

/*---------------------------------------------------------
Function Name : Buzzer_ON

Description :
    Turn ON Buzzer
---------------------------------------------------------*/
void Buzzer_ON(void)
{
    GPIOA->BSRR = BUZZER_PIN;
}

/*---------------------------------------------------------
Function Name : Buzzer_OFF

Description :
    Turn OFF Buzzer
---------------------------------------------------------*/
void Buzzer_OFF(void)
{
    GPIOA->BRR = BUZZER_PIN;
}

/*---------------------------------------------------------
Function Name : Buzzer_Beep

Description :
    Generate Beep for Specified Time

Parameter :
    ms -> Duration in milliseconds
---------------------------------------------------------*/
void Buzzer_Beep(unsigned int ms)
{
    Buzzer_ON();

    delay_ms(ms);

    Buzzer_OFF();
}

/*---------------------------------------------------------
Function Name : Buzzer_LongBeep

Description :
    Generate Long Beep
---------------------------------------------------------*/
void Buzzer_LongBeep(void)
{
    Buzzer_ON();

    delay_ms(1500);

    Buzzer_OFF();
}