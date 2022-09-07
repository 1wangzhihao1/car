#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "motor.h"
#include "pwm.h"
#include "timer.h"
#include "OLED.h"
#include "encoder.h"
#include "pid.h"
#include "bluetooth.h"

/*����˵��
PWM1->PB7��������
PWM2->PB6��������
DIR1->PA2
DIR2->PA3
TIM2���������ٶ�
TIM1���������ٶ�
*/

extern int leftSpeedNow;
extern int rightSpeedNow;

int main(void)
{		   
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	motor_init();
	uart_init(9600);
	TIM4_PWM_Init(0,0);
	OLED_Init();
	PID_param_init();
	Encoder_Init_TIM3();
	Encoder_Init_TIM2();
	TIM1_Int_Init(499,7199);//TimeOut=(49+1)(7199+1)/72kHz=5ms
	blueToothInit();//������ʼ��
	
	OLED_ShowString(1, 3, "A SLOW CAR!");
	OLED_ShowString(3, 1, "SPEED:");
	
	Set_Speed(1000,500);
	//CarForward();
	printf("-----ָ��-----\n\
	0x01��С������\n\
	0x02��С������\n\
	0x03��С������\n\
	0x04��С��ǰ��\n\
	0x05��С��ɲ��\n\
	0x06�����ֹͣ\n\
	0x07��С����ʱ��\n\
	0x08��С��ת��ֹͣ\n\
	0x09��С��˳ʱ��\n");
   	while(1)
	{
		OLED_ShowNum(4,1,leftSpeedNow,2);
		OLED_ShowString(4,3,"m/s");
		OLED_ShowNum(4,8,rightSpeedNow,2);
		OLED_ShowString(4,10,"m/s");
		if(BLUE_TOOTH_STATE != Bit_SET)//��������Ͽ���С����һֱ��ɲ��״̬
		{
			CarStop();
		}
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
