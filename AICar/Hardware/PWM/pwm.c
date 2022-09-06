#include "pwm.h"

void TIM4_PWM_Init(u16 value_left,u16 value_right) 
{   
	TIM_TimeBaseInitTypeDef TIM_Timeinit;//定义定时器初始化结构体
    TIM_OCInitTypeDef TIM_OCInitstruct;
         
    GPIO_InitTypeDef    GPIO_InitStrucyure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//使能定时器4时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);// 使能GPIO
 
 
    GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_AF_PP;//改为复用推挽输出GPIO_Mode_AF_PP
    GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_6;
    GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStrucyure);//初始化IO口   
	
	GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_AF_PP;//改为复用推挽输出GPIO_Mode_AF_PP
    GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_7;
    GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStrucyure);//初始化IO口
 
	TIM_Timeinit.TIM_ClockDivision = TIM_CKD_DIV1 ;      
	TIM_Timeinit.TIM_CounterMode =  TIM_CounterMode_Up;//输出极性:TIM输出比较极性高
				
	TIM_Timeinit.TIM_Prescaler = 0;//预分频系数为0  则频率为不分频72mhz/1 = 72Mhz
	TIM_Timeinit.TIM_Period = 7199;//72MHZ /(7199+1) = 10KHZ  7199 为计数总值
	TIM_TimeBaseInit(TIM4,&TIM_Timeinit); 
 
	TIM_OCInitstruct.TIM_Pulse = value_left;//占空比 这里是0-6500
	TIM_OCInitstruct.TIM_OCMode =   TIM_OCMode_PWM2 ;//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitstruct.TIM_OCNPolarity  = TIM_OCPolarity_High ;   //极性输出高
	TIM_OCInitstruct.TIM_OutputState = TIM_OutputState_Enable ;        //      
	TIM_OC1Init(TIM4,&TIM_OCInitstruct);//根据TIM_OCInitStruct中指定的参数初始化外设TIMx  
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);//CH1预装载使能
	
	TIM_OCInitstruct.TIM_Pulse = value_right;//占空比 这里是0-6500
	TIM_OCInitstruct.TIM_OCMode =   TIM_OCMode_PWM2 ;//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitstruct.TIM_OCNPolarity  = TIM_OCPolarity_High ;   //极性输出高
	TIM_OCInitstruct.TIM_OutputState = TIM_OutputState_Enable ;        //      
	TIM_OC2Init(TIM4,&TIM_OCInitstruct);//根据TIM_OCInitStruct中指定的参数初始化外设TIMx 
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);//CH2预装载使能
	
	TIM_Cmd(TIM4,ENABLE);  //使能定时器
     
}

void Set_Speed(u16 Compare_left,u16 Compare_right)
{
	TIM4_PWM_Init(7000-Compare_left,7000-Compare_right);
}

//void Set_Right_Speed(u16 Compare)
//{
//	TIM4_PWM_Init(7000-Compare);
//}

