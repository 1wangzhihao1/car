#ifndef _BLUETOOTH_H
#define _BLUETOOTH_H

#include "sys.h"

#define BLUE_TOOTH_GPIO_PORT		GPIOA
#define BLUE_TOOTH_GPIO_CLK 	    RCC_APB2Periph_GPIOA
#define BLUE_TOOTH_GPIO_PIN			GPIO_Pin_11
#define BLUE_TOOTH_STATE			GPIO_ReadInputDataBit(BLUE_TOOTH_GPIO_PORT,BLUE_TOOTH_GPIO_PIN)

void blueToothInit(void);

#endif

