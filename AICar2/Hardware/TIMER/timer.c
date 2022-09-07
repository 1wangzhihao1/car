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

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr;  //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);  //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	//���жϣ�����һ�����жϺ����������ж�
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
	//ʹ��TIM1�ж�Դ
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
 

	//Step3.�ж�NVIC���ã������жϣ��������ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;    //�����¼�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //��Ӧ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //�����ж�
	NVIC_Init(&NVIC_InitStructure);                            //д������

	TIM_Cmd(TIM1, ENABLE);
}

void TIM1_UP_IRQHandler(void)//TIM3�ж�
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET)//���ָ����TIM�жϷ������:TIM �ж�Դ
	{
		Get_Motor_Speed(&leftSpeedNow,&rightSpeedNow);
//		second++;
//		if(second==1000)//��ʱ5s
//		{
//			CarStop();
//		}
	}
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);//���TIMx���жϴ�����λ:TIM �ж�Դ
}

