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

//void TIMER_Init(u16 arr,u16 psc)
//{
//	
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruture;
//	NVIC_InitTypeDef NVIC_InitStruture;
//	
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
//	
//	TIM_TimeBaseInitStruture.TIM_Period=arr;
//	TIM_TimeBaseInitStruture.TIM_Prescaler=psc;
//	TIM_TimeBaseInitStruture.TIM_ClockDivision=TIM_CKD_DIV1;
//	TIM_TimeBaseInitStruture.TIM_CounterMode=TIM_CounterMode_Up;
//	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruture);
//	
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
//	
//	NVIC_InitStruture.NVIC_IRQChannel=TIM3_IRQn;
//	NVIC_InitStruture.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStruture.NVIC_IRQChannelPreemptionPriority=0;
//	NVIC_InitStruture.NVIC_IRQChannelSubPriority=3;
//	NVIC_Init(&NVIC_InitStruture);
//	
//	TIM_Cmd(TIM3,ENABLE);
//	
//}

void TIM1_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr;  //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);  //根据指定的参数初始化TIMx的时间基数单位
	//清中断，以免一启用中断后立即产生中断
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
	//使能TIM1中断源
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
 

	//Step3.中断NVIC设置：允许中断，设置优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;    //更新事件
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //响应优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //允许中断
	NVIC_Init(&NVIC_InitStructure);                            //写入设置

	TIM_Cmd(TIM1, ENABLE);
}

void TIM1_UP_IRQHandler(void)//TIM3中断
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET)//检查指定的TIM中断发生与否:TIM 中断源
	{
		Get_Motor_Speed(&leftSpeedNow,&rightSpeedNow);
//		second++;
//		if(second==1000)//定时5s
//		{
//			CarStop();
//		}
	}
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);//清除TIMx的中断待处理位:TIM 中断源
}

