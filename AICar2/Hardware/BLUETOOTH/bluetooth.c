#include "bluetooth.h"

void blueToothInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//时钟
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//下拉输入
	//蓝牙状态引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
