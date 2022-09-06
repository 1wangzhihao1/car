#include "timer.h"

u16 second=0;
u8 now_num;//��ǰ�ı���ģʽ��¼��ֵ
int leftSpeedNow=0;
int rightSpeedNow=0;

int Encoder_Left,Encoder_Right;
int Left_t,Right_t,Encoder_R,Encoder_L;
int Moto_Front_Left,Moto_Front_Right,Moto_Back_Left,Moto_Back_Right; 
int para1,para2,para3,para4;//����
int SetPoint1=30;//����Ŀ��ֵ��λRPM
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

void TIM3_IRQHandler(void)//TIM3�ж�
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)//���ָ����TIM�жϷ������:TIM �ж�Դ
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//���TIMx���жϴ�����λ:TIM �ж�Դ
		Get_Motor_Speed(&leftSpeedNow,&rightSpeedNow);
		//printf("����������Ϊ%d\r\n",encode);
		//speed=encode/500.0f/4.0f;
		//printf("�������ٶ�Ϊ%f\r\n",speed);
//		second++;
//		if(second==1000)//��ʱ5s
//		{
//			CarStop();
//			//second=0;
//		}
//		Get_Motor_Speed(&leftSpeedNow,&rightSpeedNow);
		now_num=TIM2->CNT;
		TIM2->CNT=0x7fff;//ÿ����һ���ж���TIM2->CNT��ֵΪ0x7FFF�������¼���Ǳ��������������������½��ظ����������õ�����Ϊ0xFFFF������0x7FFF�ĺô�
//�ǿ���֪������ת���Ƿ�ת�����ҵĳ������õ�����ת�����Ҫ���÷�ת����main.c�����now_num-32767����32767-now_num���ɣ�ԭ���Ƕ�ʱ��������ģʽ��ת��������
//��ת������	
		
	}
	 

}

