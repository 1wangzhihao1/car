#include "encoder.h"

//把TIM1初始化为编码器接口模式
void Encoder_Init_TIM1(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	TIM_ICInitTypeDef TIM_ICInitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);    //使能定时器2的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //使能PA端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;	//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//根据设定参数初始化GPIOA

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;              //预分频器 
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;  //设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM1, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);                   //清除TIM的更新标志位
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
	TIM_SetCounter(TIM1,0);
	
	TIM1->CNT = 0x7fff;
	
	TIM_Cmd(TIM1, ENABLE); 
}

//把TIM2初始化为编码器接口模式
void Encoder_Init_TIM2(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	TIM_ICInitTypeDef TIM_ICInitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);    //使能定时器2的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);   //使能PA端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	//端口配置 PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA
  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	//端口配置 PB3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//根据设定参数初始化GPIOA

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;              //预分频器 
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;  //设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);                   //清除TIM的更新标志位
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
	//5ms测速 5ms即这里说的单位时间  	
	*leftSpeed   = getTIMx_DetaCnt(TIM1)*1000*200*0.000120830;  
	*rightSpeed  = getTIMx_DetaCnt(TIM2)*1000*200*0.000120830;
}

////读取编码器脉冲差值
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

////计算左右轮速
//void Get_Motor_Speed(int *leftSpeed,int *rightSpeed)
//{
//	static int leftWheelEncoderNow    = 0;
//	static int rightWheelEncoderNow   = 0;
//	static int leftWheelEncoderLast   = 0;
//	static int rightWheelEncoderLast  = 0;	
//	
//	//记录本次左右编码器数据
//	leftWheelEncoderNow += GetTIM2_DetaCnt(TIM2);
//	rightWheelEncoderNow+= GetTIM1_DetaCnt(TIM1);
//		
//	//5ms测速    	
//	*leftSpeed   = (leftWheelEncoderNow - leftWheelEncoderLast)*1000*200*0.000120830;  
//	*rightSpeed  = (rightWheelEncoderNow - rightWheelEncoderLast)*1000*200*0.000181245;

//	//记录上次编码器数据
//	leftWheelEncoderLast  = leftWheelEncoderNow;                    
//	rightWheelEncoderLast = rightWheelEncoderNow;                   
//}
