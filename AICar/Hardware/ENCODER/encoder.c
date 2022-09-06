#include "encoder.h"

//��TIM1��ʼ��Ϊ�������ӿ�ģʽ
void Encoder_Init_TIM1(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	TIM_ICInitTypeDef TIM_ICInitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);    //ʹ�ܶ�ʱ��2��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //ʹ��PA�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;	//�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//�����趨������ʼ��GPIOA

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;              //Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;  //�趨�������Զ���װֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM1, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);                   //���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
	TIM_SetCounter(TIM1,0);
	
	TIM1->CNT = 0x7fff;
	
	TIM_Cmd(TIM1, ENABLE); 
}

//��TIM2��ʼ��Ϊ�������ӿ�ģʽ
void Encoder_Init_TIM2(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	TIM_ICInitTypeDef TIM_ICInitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);    //ʹ�ܶ�ʱ��2��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);   //ʹ��PA�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	//�˿����� PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA
  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	//�˿����� PB3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//�����趨������ʼ��GPIOA

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;              //Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;  //�趨�������Զ���װֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);                   //���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	TIM_SetCounter(TIM2,0);
	
	TIM2->CNT = 0x7fff;
	
	TIM_Cmd(TIM2, ENABLE); 
}

u16 getTIMx_DetaCnt(TIM_TypeDef * TIMx)
{
	u16 cnt;
	cnt = TIMx->CNT-0x7fff;
	TIMx->CNT = 0x7fff;
	return cnt;
}

void Get_Motor_Speed(int *leftSpeed,int *rightSpeed)
{
	//5ms���� 5ms������˵�ĵ�λʱ��  	
	*leftSpeed   = getTIMx_DetaCnt(TIM1)*1000*200*0.000120830;  
	*rightSpeed  = getTIMx_DetaCnt(TIM2)*1000*200*0.000120830;
}

////��ȡ�����������ֵ
//u16 GetTIM2_DetaCnt(TIM_TypeDef *TIMX)
//{
//	u16 cnt;
//	cnt = TIM2->CNT-0x7fff;
//	TIM2->CNT = 0x7fff;
//	return cnt;
//}

//u16 GetTIM1_DetaCnt(TIM_TypeDef *TIMX)
//{
//	u16 cnt;
//	cnt = TIM1->CNT-0x7fff;
//	TIM1->CNT = 0x7fff;
//	return cnt;
//}

////������������
//void Get_Motor_Speed(int *leftSpeed,int *rightSpeed)
//{
//	static int leftWheelEncoderNow    = 0;
//	static int rightWheelEncoderNow   = 0;
//	static int leftWheelEncoderLast   = 0;
//	static int rightWheelEncoderLast  = 0;	
//	
//	//��¼�������ұ���������
//	leftWheelEncoderNow += GetTIM2_DetaCnt(TIM2);
//	rightWheelEncoderNow+= GetTIM1_DetaCnt(TIM1);
//		
//	//5ms����    	
//	*leftSpeed   = (leftWheelEncoderNow - leftWheelEncoderLast)*1000*200*0.000120830;  
//	*rightSpeed  = (rightWheelEncoderNow - rightWheelEncoderLast)*1000*200*0.000181245;

//	//��¼�ϴα���������
//	leftWheelEncoderLast  = leftWheelEncoderNow;                    
//	rightWheelEncoderLast = rightWheelEncoderNow;                   
//}