#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "motor.h"
#include "pwm.h"
#include "timer.h"
#include "OLED.h"
#include "encoder.h"
#include "pid.h"

/*连接说明
PWM1->PB7控制右轮
PWM2->PB6控制左轮
DIR1->PA2
DIR2->PA3
TIM2测量左轮速度
TIM1测量右轮速度
*/

float target_speed=0.7;//记录目标的速度,单位cm/ms
float actual_speed;//记录实际速度,单位cm/ms
float new_speed_difference;//记录当前速度差值
float before_speed_difference;//记录之前速度差值
float before2_speed_difference;//记录之前之前速度差值
float Cumulative_speed_difference;//记录累计速度
float add_speed;//记录添加速度
 
float kp=100;
float ki=90;
float kd=100;
 
int out=0;//占空比

extern u16 second;
extern u8 now_num;
extern int leftSpeedNow;
extern int rightSpeedNow;

int main(void)
{		   
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	motor_init();
	uart_init(9600);
	TIM4_PWM_Init(0,0);
	//Remote_Init();
	OLED_Init();
	PID_param_init();
	Encoder_Init_TIM1();
	Encoder_Init_TIM2();
	TIMER_Init(499,7199);//TimeOut=(4999+1)(71+1)/72kHz=5ms
	
	OLED_ShowString(1, 3, "A SLOW CAR!");
	OLED_ShowString(3, 1, "SPEED:");
	
	
	Set_Speed(600,3000);
	//CarStop();
   	while(1)
	{
		//delay_ms(15);
		OLED_ShowNum(4,1,rightSpeedNow,3);
		OLED_ShowNum(4,5,leftSpeedNow,3);
		//OLED_ShowNum(4,1,leftSpeedNow,3);
		//OLED_ShowNum(4,5,rightSpeedNow,3);		
//		printf("L=%d,R=%d\r\n",leftSpeedNow,rightSpeedNow);
//		delay_ms(15);
//		ired_value=Remote_Scan();
//		if(ired_value)
//		{
//			switch(ired_value)
//			{
//				case 24:CarForward();break;
//				case 16:CarLeft();break;
//				case 90:CarRight();break;
//				case 74:CarBack();break;
//				case 56:CarStop();break;
//			}
//		}		
	}
}
