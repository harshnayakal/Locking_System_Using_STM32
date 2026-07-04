/*---------------------------------------------------------
 File        : main.c
 Device      : STM32F103C8T6
 Toolchain   : Keil uVision

 Project :
      Two Factor Authentication Locker
---------------------------------------------------------*/

#include "stm32f10x.h"
#include <string.h>

#include "delay.h"
#include "lcd.h"
#include "keypad.h"
#include "led.h"
#include "buzzer.h"
#include "otp.h"

/**************** START SWITCH ****************/

#define START_SWITCH    (1<<6)      // PB6

/**************** PASSWORD ****************/

unsigned char StoredPassword[] = "1234";

unsigned char EnteredPassword[5];

unsigned char EnteredOTP[5];

unsigned int OTP;

unsigned char Attempts = 0;

/**************** FUNCTION PROTOTYPES ****************/

void Switch_Init(void);

unsigned char Password_Check(void);

unsigned char OTP_Check(void);

void System_Lock(void);

void LCD_CountDown(unsigned int);

/****************************************************
                    MAIN PROGRAM
****************************************************/

int main(void)
{

    /* Initialize Hardware */

    Switch_Init();

    LCD_Init();

    Keypad_Init();

    LED_Init();

    Buzzer_Init();

    OTP_Init();

    /* Startup Indication */

    LED_AllON();

    Buzzer_Beep(200);

    delay_s(1);

    LED_AllOFF();

    while(1)
    {

        LCD_Clear();

        LCD_String("2FA LOCKER");

        LCD_SetCursor(1,0);

        LCD_String("PRESS SWITCH");

        /* Wait Until PB6 Pressed */

        while(GPIOB->IDR & START_SWITCH);

        delay_ms(200);

        while(!(GPIOB->IDR & START_SWITCH));

        delay_ms(200);

        /**************** PASSWORD ****************/

        LCD_Clear();

        LCD_String("ENTER PASS");

        LCD_SetCursor(1,0);

        Keypad_GetPassword(EnteredPassword,4);

        if(Password_Check()==0)
        {

            Attempts++;

            LCD_Clear();

            LCD_String("WRONG PASS");

            LCD_SetCursor(1,0);

            LCD_String("TRY AGAIN");

            Buzzer_Beep(600);

            delay_s(2);

            if(Attempts>=3)
            {
                System_Lock();

                Attempts=0;
            }

            continue;
        }

        Attempts=0;

        /**************** OTP ****************/

        OTP=OTP_Generate();

        LCD_Clear();

        LCD_String("OTP:");

        LCD_UInt(OTP);

        delay_s(3);

        LCD_Clear();

        LCD_String("ENTER OTP");

        LCD_SetCursor(1,0);

        Keypad_GetNumber(EnteredOTP,4);

        if(OTP_Check()==0)
        {

            LCD_Clear();

            LCD_String("WRONG OTP");

            LCD_SetCursor(1,0);

            LCD_String("ACCESS DENY");

            Buzzer_Beep(1000);

            delay_s(2);

            continue;
        }

        /**************** ACCESS GRANTED ****************/

        LCD_Clear();

        LCD_String("ACCESS");

        LCD_SetCursor(1,0);

        LCD_String("GRANTED");

        Buzzer_Beep(250);

        LED_UnlockSequence();

        delay_s(5);

        LCD_Clear();

        LCD_String("LOCK OPEN");

        delay_s(3);

        LED_LockSequence();

        LCD_Clear();

        LCD_String("LOCK CLOSED");

        delay_s(2);

    }

}

/*---------------------------------------------------------
Function Name : Switch_Init

Description :
    Configure PB6 as Input Pull-Up Switch
---------------------------------------------------------*/
void Switch_Init(void)
{
    /* Enable GPIOB Clock */
    RCC->APB2ENR |= (1<<3);

    /*
        PB6 Configuration

        MODE = 00  (Input)
        CNF  = 10  (Input Pull-up/Pull-down)
    */

    GPIOB->CRL &= ~(0xF<<24);
    GPIOB->CRL |=  (0x8<<24);

    /* Enable Internal Pull-up */
    GPIOB->BSRR = START_SWITCH;
}

/*---------------------------------------------------------
Function Name : Password_Check

Description :
    Compare Entered Password with Stored Password

Returns :
    1 = Password Correct
    0 = Password Wrong
---------------------------------------------------------*/
unsigned char Password_Check(void)
{
    if(strcmp((char*)EnteredPassword,
              (char*)StoredPassword)==0)
    {
        return 1;
    }

    return 0;
}

/*---------------------------------------------------------
Function Name : OTP_Check

Description :
    Compare Entered OTP with Generated OTP

Returns :
    1 = OTP Correct
    0 = OTP Wrong
---------------------------------------------------------*/
unsigned char OTP_Check(void)
{
    unsigned int number = 0;
    unsigned char i;

    for(i=0;i<4;i++)
    {
        number = (number * 10) +
                 (EnteredOTP[i] - '0');
    }

    if(number == OTP)
    {
        return 1;
    }

    return 0;
}

/*---------------------------------------------------------
Function Name : LCD_CountDown

Description :
    Displays Countdown on LCD
---------------------------------------------------------*/
void LCD_CountDown(unsigned int sec)
{
    while(sec)
    {
        LCD_Clear();

        LCD_String("SYSTEM LOCK");

        LCD_SetCursor(1,0);

        LCD_String("TIME : ");

        LCD_UInt(sec);

        LCD_String("s");

        delay_s(1);

        sec--;
    }
}

/*---------------------------------------------------------
Function Name : Access_Granted

Description :
    LED Unlock Animation
---------------------------------------------------------*/
void Access_Granted(void)
{
    LCD_Clear();

    LCD_String("ACCESS");

    LCD_SetCursor(1,0);

    LCD_String("GRANTED");

    Buzzer_Beep(200);

    LED_UnlockSequence();

    delay_s(5);

    LED_LockSequence();

    LCD_Clear();

    LCD_String("LOCK CLOSED");

    delay_s(2);
}

/*---------------------------------------------------------
Function Name : Access_Denied

Description :
    Wrong OTP Indication
---------------------------------------------------------*/
void Access_Denied(void)
{
    LCD_Clear();

    LCD_String("ACCESS");

    LCD_SetCursor(1,0);

    LCD_String("DENIED");

    Buzzer_Beep(1000);

    delay_s(2);
}

/*---------------------------------------------------------
Function Name : Wrong_Password

Description :
    Wrong Password Indication
---------------------------------------------------------*/
void Wrong_Password(void)
{
    LCD_Clear();

    LCD_String("WRONG");

    LCD_SetCursor(1,0);

    LCD_String("PASSWORD");

    Buzzer_Beep(600);

    delay_s(2);
}

/*---------------------------------------------------------
Function Name : System_Lock

Description :
    Lock the system after 3 wrong password attempts
---------------------------------------------------------*/
void System_Lock(void)
{
    unsigned int sec;

    LED_AllOFF();

    LCD_Clear();
    LCD_String("SYSTEM LOCK");
    LCD_SetCursor(1,0);
    LCD_String("WAIT 100 SEC");

    /* Long alarm */
    Buzzer_LongBeep();

    delay_s(2);

    /* Countdown */
    for(sec = 100; sec > 0; sec--)
    {
        LCD_CountDown(sec);
    }

    LCD_Clear();
    LCD_String("LOCK REMOVED");
    delay_s(2);

    LCD_Clear();
}

/*---------------------------------------------------------
Function Name : System_Reset

Description :
    Reset Runtime Variables
---------------------------------------------------------*/
void System_Reset(void)
{
    Attempts = 0;

    OTP = 0;

    memset(EnteredPassword,0,sizeof(EnteredPassword));

    memset(EnteredOTP,0,sizeof(EnteredOTP));
}

/*---------------------------------------------------------
Function Name : Welcome_Screen

Description :
    Display Startup Screen
---------------------------------------------------------*/
void Welcome_Screen(void)
{
    LCD_Clear();

    LCD_String("2FA LOCKER");

    LCD_SetCursor(1,0);

    LCD_String("READY");

    LED_AllON();

    delay_s(1);

    LED_AllOFF();

    LCD_Clear();
}

/*---------------------------------------------------------
Function Name : Waiting_Screen

Description :
    Display Waiting Screen
---------------------------------------------------------*/
void Waiting_Screen(void)
{
    LCD_Clear();

    LCD_String("PRESS");

    LCD_SetCursor(1,0);

    LCD_String("START SWITCH");
}

/*---------------------------------------------------------
Function Name : OTP_Display

Description :
    Display Generated OTP
---------------------------------------------------------*/
void OTP_Display(unsigned int otp)
{
    LCD_Clear();

    LCD_String("OTP:");

    LCD_UInt(otp);

    delay_s(3);

    LCD_Clear();
}

/*---------------------------------------------------------
End of File
---------------------------------------------------------*/