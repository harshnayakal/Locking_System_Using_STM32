/*---------------------------------------------------------
 File        : delay.c
 Device      : STM32F103C8T6
 Toolchain   : Keil uVision

 Description :
    Software Delay Functions
    CPU Clock : 72 MHz
---------------------------------------------------------*/

#include "delay.h"

/*---------------------------------------------------------
Function Name : delay_us

Description :
    Delay in Microseconds

Parameter :
    us -> Number of Microseconds
---------------------------------------------------------*/
void delay_us(unsigned int us)
{
    unsigned int i;

    while(us--)
    {
        /* Approximate 1 us delay @72 MHz */
        for(i = 0; i < 12; i++)
        {
            __NOP();
        }
    }
}

/*---------------------------------------------------------
Function Name : delay_ms

Description :
    Delay in Milliseconds

Parameter :
    ms -> Number of Milliseconds
---------------------------------------------------------*/
void delay_ms(unsigned int ms)
{
    while(ms--)
    {
        delay_us(1000);
    }
}

/*---------------------------------------------------------
Function Name : delay_s

Description :
    Delay in Seconds

Parameter :
    sec -> Number of Seconds
---------------------------------------------------------*/
void delay_s(unsigned int sec)
{
    while(sec--)
    {
        delay_ms(1000);
    }
}