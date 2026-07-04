/*---------------------------------------------------------
 File        : otp.c
 Device      : STM32F103C8T6
 Toolchain   : Keil uVision

 Description :
      4-Digit OTP Generator
---------------------------------------------------------*/

#include "otp.h"

/*---------------------------------------------------------
 Global Seed Variable
---------------------------------------------------------*/
static unsigned long OTP_Seed = 0x12345678;

/*---------------------------------------------------------
Function Name : OTP_Init

Description :
    Initialize OTP Generator
---------------------------------------------------------*/
void OTP_Init(void)
{
    OTP_Seed = 0x12345678;
}

/*---------------------------------------------------------
Function Name : OTP_Generate

Description :
    Generate Random 4-Digit OTP

Returns :
    1000 to 9999
---------------------------------------------------------*/
unsigned int OTP_Generate(void)
{
    /*
        Linear Congruential Generator (LCG)

        Xn+1 = (a × Xn + c)

        a = 1664525
        c = 1013904223
    */

    OTP_Seed = (1664525 * OTP_Seed) + 1013904223;

    /* Return OTP between 1000 and 9999 */

    return ((OTP_Seed % 9000) + 1000);
}