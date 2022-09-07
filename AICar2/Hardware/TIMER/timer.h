#ifndef _TIMER_H
#define _TIMER_H

#include "sys.h"
#include "delay.h"
#include "motor.h"
#include "timer.h"
#include "encoder.h"
#include "usart.h"

void TIMER_Init(u16 arr,u16 psc);
void TIM1_Int_Init(u16 arr,u16 psc);

#endif

