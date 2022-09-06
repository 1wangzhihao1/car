#ifndef _PWM_H
#define _PWM_H

#include "sys.h"

void TIM4_PWM_Init(u16 value_left,u16 value_right);
void Set_Speed(u16 Compare_left,u16 Compare_right);

#endif

