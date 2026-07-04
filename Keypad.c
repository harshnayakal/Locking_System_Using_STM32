/*---------------------------------------------------------
 File        : keypad.c
 Device      : STM32F103C8T6
 Toolchain   : Keil uVision

 Description :
      4x4 Matrix Keypad Driver

 Rows
 PA0 PA1 PA2 PA3

 Columns
 PA4 PA5 PA6 PA7
---------------------------------------------------------*/

#include "keypad.h"

/* Keypad Layout */
static const char KeyMap[4][4] =
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

/*---------------------------------------------------------
Function : Keypad_Init
---------------------------------------------------------*/
void Keypad_Init(void)
{
    /* Enable GPIOA Clock */
    RCC->APB2ENR |= (1<<2);

    /*-------------------------------------------------
      PA0-PA3
      Output Push Pull 2MHz
    --------------------------------------------------*/

    GPIOA->CRL &= ~(0xFFFF);

    GPIOA->CRL |= 0x2222;

    /*-------------------------------------------------
      PA4-PA7
      Input Pull-Up
    --------------------------------------------------*/

    GPIOA->CRL &= ~(0xFFFF0000);

    GPIOA->CRL |= 0x88880000;

    /* Enable Pull-up */

    GPIOA->BSRR = COL1 | COL2 | COL3 | COL4;

    /* Set all rows HIGH */

    GPIOA->BSRR = ROW1 | ROW2 | ROW3 | ROW4;
}

/*---------------------------------------------------------
Function : Keypad_GetKey

Return :
    Pressed Key
---------------------------------------------------------*/
char Keypad_GetKey(void)
{
    unsigned char row;

    while(1)
    {
        for(row=0; row<4; row++)
        {
            /* Set all rows HIGH */

            GPIOA->BSRR = ROW1 | ROW2 | ROW3 | ROW4;

            /* Pull one row LOW */

            switch(row)
            {
                case 0:
                    GPIOA->BRR = ROW1;
                    break;

                case 1:
                    GPIOA->BRR = ROW2;
                    break;

                case 2:
                    GPIOA->BRR = ROW3;
                    break;

                case 3:
                    GPIOA->BRR = ROW4;
                    break;
            }

            delay_ms(2);

            /* Column 1 */

            if(!(GPIOA->IDR & COL1))
            {
                while(!(GPIOA->IDR & COL1));
                delay_ms(20);

                return KeyMap[row][0];
            }

            /* Column 2 */

            if(!(GPIOA->IDR & COL2))
            {
                while(!(GPIOA->IDR & COL2));
                delay_ms(20);

                return KeyMap[row][1];
            }

            /* Column 3 */

            if(!(GPIOA->IDR & COL3))
            {
                while(!(GPIOA->IDR & COL3));
                delay_ms(20);

                return KeyMap[row][2];
            }

            /* Column 4 */

            if(!(GPIOA->IDR & COL4))
            {
                while(!(GPIOA->IDR & COL4));
                delay_ms(20);

                return KeyMap[row][3];
            }
        }
    }
}
/*---------------------------------------------------------
Function : Keypad_GetPassword

Description :
    Reads Password from Keypad
    Displays '*' on LCD

Parameters :
    password -> Buffer
    length   -> Number of Characters
---------------------------------------------------------*/
void Keypad_GetPassword(unsigned char *password,
                        unsigned char length)
{
    unsigned char i = 0;
    char key;

    while(i < length)
    {
        key = Keypad_GetKey();

        /* Accept only numeric keys */
        if(key >= '0' && key <= '9')
        {
            password[i] = key;

            LCD_Char('*');      // Mask password

            i++;
        }
    }

    password[length] = '\0';
}

/*---------------------------------------------------------
Function : Keypad_GetNumber

Description :
    Reads Numeric Input (OTP)

Parameters :
    number -> Buffer
    length -> Number of Digits
---------------------------------------------------------*/
void Keypad_GetNumber(unsigned char *number,
                      unsigned char length)
{
    unsigned char i = 0;
    char key;

    while(i < length)
    {
        key = Keypad_GetKey();

        if(key >= '0' && key <= '9')
        {
            number[i] = key;

            LCD_Char(key);      // Show actual digits for OTP

            i++;
        }
    }

    number[length] = '\0';
}

/*---------------------------------------------------------
Optional Function : Keypad_WaitRelease

Description :
    Wait until all keys are released
---------------------------------------------------------*/
void Keypad_WaitRelease(void)
{
    while(!(GPIOA->IDR & COL1) ||
          !(GPIOA->IDR & COL2) ||
          !(GPIOA->IDR & COL3) ||
          !(GPIOA->IDR & COL4));

    delay_ms(20);
}