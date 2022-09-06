#ifndef _ENCODER_H
#define _ENCODER_H

#include "sys.h"
#include "OLED.h"

#define ENCODER_TIM_PERIOD (u16)(65535)   //���ɴ���65535 ��ΪF103�Ķ�ʱ����16λ�ġ�
#define ENCODER_RESOLUTION 11    /*������һȦ������������*/
#define ENCODER_MULTIPLE 4       /*��������Ƶ��ͨ����ʱ���ı�����ģʽ����*/
#define MOTOR_REDUCTION_RATIO 34 /*����ļ��ٱ�*/
/*���תһȦ�ܵ�������(��ʱ���ܶ�����������) = ����������������*��������Ƶ*������ٱ� */
#define TOTAL_RESOLUTION ( ENCODER_RESOLUTION*ENCODER_MULTIPLE*MOTOR_REDUCTION_RATIO ) 

void Encoder_Init_TIM1(void);
void Encoder_Init_TIM2(void);
u16 getTIMx_DetaCnt(TIM_TypeDef * TIMx);
void Get_Motor_Speed(int *leftSpeed,int *rightSpeed);
void calc_motor_rotate_speed(void);

#endif


