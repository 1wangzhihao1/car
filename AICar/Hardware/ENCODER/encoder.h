#ifndef _ENCODER_H
#define _ENCODER_H

#include "sys.h"
#include "OLED.h"

#define ENCODER_TIM_PERIOD (u16)(65535)   //不可大于65535 因为F103的定时器是16位的。
#define ENCODER_RESOLUTION 11    /*编码器一圈的物理脉冲数*/
#define ENCODER_MULTIPLE 4       /*编码器倍频，通过定时器的编码器模式设置*/
#define MOTOR_REDUCTION_RATIO 34 /*电机的减速比*/
/*电机转一圈总的脉冲数(定时器能读到的脉冲数) = 编码器物理脉冲数*编码器倍频*电机减速比 */
#define TOTAL_RESOLUTION ( ENCODER_RESOLUTION*ENCODER_MULTIPLE*MOTOR_REDUCTION_RATIO ) 

void Encoder_Init_TIM1(void);
void Encoder_Init_TIM2(void);
u16 getTIMx_DetaCnt(TIM_TypeDef * TIMx);
void Get_Motor_Speed(int *leftSpeed,int *rightSpeed);
void calc_motor_rotate_speed(void);

#endif


