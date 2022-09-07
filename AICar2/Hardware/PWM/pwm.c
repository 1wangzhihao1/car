#include "pwm.h"

void TIM4_PWM_Init(u16 value_left,u16 value_right) 
{   
	TIM_TimeBaseInitTypeDef TIM_Timeinit;//���嶨ʱ����ʼ���ṹ��
    TIM_OCInitTypeDef TIM_OCInitstruct;
         
    GPIO_InitTypeDef    GPIO_InitStrucyure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//ʹ�ܶ�ʱ��4ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);// ʹ��GPIO
 
 
    GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_AF_PP;//��Ϊ�����������GPIO_Mode_AF_PP
    GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_6;
    GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStrucyure);//��ʼ��IO��   
	
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_AF_PP;//��Ϊ�����������GPIO_Mode_AF_PP
    GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_7;
    GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStrucyure);//��ʼ��IO��
 
	TIM_Timeinit.TIM_ClockDivision = TIM_CKD_DIV1 ;      
	TIM_Timeinit.TIM_CounterMode =  TIM_CounterMode_Up;//�������:TIM����Ƚϼ��Ը�
				
	TIM_Timeinit.TIM_Prescaler = 0;//Ԥ��Ƶϵ��Ϊ0  ��Ƶ��Ϊ����Ƶ72mhz/1 = 72Mhz
	TIM_Timeinit.TIM_Period = 7199;//72MHZ /(7199+1) = 10KHZ  7199 Ϊ������ֵ
	TIM_TimeBaseInit(TIM4,&TIM_Timeinit); 
 
	TIM_OCInitstruct.TIM_Pulse = value_left;//ռ�ձ� ������0-6500
	TIM_OCInitstruct.TIM_OCMode =   TIM_OCMode_PWM2 ;//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitstruct.TIM_OCNPolarity  = TIM_OCPolarity_High ;   //���������
	TIM_OCInitstruct.TIM_OutputState = TIM_OutputState_Enable ;        //      
	TIM_OC1Init(TIM4,&TIM_OCInitstruct);//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx  
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);//CH1Ԥװ��ʹ��
	
	TIM_OCInitstruct.TIM_Pulse = value_right;//ռ�ձ� ������0-6500
	TIM_OCInitstruct.TIM_OCMode =   TIM_OCMode_PWM2 ;//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitstruct.TIM_OCNPolarity  = TIM_OCPolarity_High ;   //���������
	TIM_OCInitstruct.TIM_OutputState = TIM_OutputState_Enable ;        //      
	TIM_OC2Init(TIM4,&TIM_OCInitstruct);//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx 
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);//CH2Ԥװ��ʹ��
	
	TIM_Cmd(TIM4,ENABLE);  //ʹ�ܶ�ʱ��
     
}

void Set_Speed(u16 Compare_left,u16 Compare_right)
{
	TIM4_PWM_Init(7000-Compare_left,7000-Compare_right);
}

//void Set_Right_Speed(u16 Compare)
//{
//	TIM4_PWM_Init(7000-Compare);
//}

