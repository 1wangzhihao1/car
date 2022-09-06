#ifndef _MOTOR_H
#define _MOTOR_H

#include "sys.h"
#include "pwm.h"
#include "delay.h"

void motor_init(void);
void CarForward(void);
void CarBack(void);
void CarLeft(void);
void CarRight(void);
void CarStop(void);

#define right_motor	PAout(0)
#define left_motor	PAout(1)
#define left_dir	PAout(2)
#define right_dir	PAout(3)

#endif

