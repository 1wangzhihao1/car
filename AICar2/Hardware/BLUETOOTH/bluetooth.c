#include "bluetooth.h"

void blueToothInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʱ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������
	//����״̬����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
