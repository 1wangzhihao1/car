#include "timer.h"

u16 second=0;
u8 now_num;//当前的编码模式记录的值
int leftSpeedNow=0;
int rightSpeedNow=0;

int Encoder_Left,Encoder_Right;
int Left_t,Right_t,Encoder_R,Encoder_L;
int Moto_Front_Left,Moto_Front_Right,Moto_Back_Left,Moto_Back_Right; 
int para1,para2,para3,para4;//增量
int SetPoint1=30;//设置目标值单位RPM
int SetPoint2=30;

void TIMER_Init(u16 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruture;
	NVIC_InitTypeDef NVIC_InitStruture;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitStruture.TIM_Period=arr;
	TIM_TimeBaseInitStruture.TIM_Prescaler=psc;
	TIM_TimeBaseInitStruture.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruture.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruture);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	NVIC_InitStruture.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStruture.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruture.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruture.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruture);
	
	TIM_Cmd(TIM3,ENABLE);
	
}

void TIM3_IRQHandler(void)//TIM3中断
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)//检查指定的TIM中断发生与否:TIM 中断源
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清除TIMx的中断待处理位:TIM 中断源
		Get_Motor_Speed(&leftSpeedNow,&rightSpeedNow);
		//printf("编码器脉冲为%d\r\n",encode);
		//speed=encode/500.0f/4.0f;
		//printf("编码器速度为%f\r\n",speed);
//		second++;
//		if(second==1000)//定时5s
//		{
//			CarStop();
//			//second=0;
//		}
//		Get_Motor_Speed(&leftSpeedNow,&rightSpeedNow);
		now_num=TIM2->CNT;
		TIM2->CNT=0x7fff;//每产生一次中断令TIM2->CNT的值为0x7FFF，里面记录的是编码器输出脉冲的上升和下降沿个数，我设置的上限为0xFFFF，设置0x7FFF的好处
//是可以知道是正转还是反转但是我的程序设置的是正转，如果要设置反转，把main.c里面的now_num-32767换成32767-now_num即可，原因是定时器编码器模式正转正计数，
//反转反计数	
		
	}
	 

}

