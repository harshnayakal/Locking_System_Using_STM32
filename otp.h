#ifndef __OTP_H
#define __OTP_H

#include "stm32f10x.h"

void OTP_Init(void);
unsigned int OTP_Generate(void);

#endif