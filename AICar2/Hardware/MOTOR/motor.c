#include "motor.h"

void motor_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
}

void CarForward(void)//小车前进
{
//	Set_Left_Speed(5000);
//	Set_Right_Speed(5000);
	Set_Speed(3000,3000);
	left_dir=1;
	right_dir=1;
}

void CarBack(void)//小车后退
{
//	Set_Left_Speed(1000);
//	Set_Right_Speed(1000);
	Set_Speed(3000,3000);
	left_dir=0;
	right_dir=0;
}

void CarRight(void)//小车右转
{
//	Set_Left_Speed(2000);
//	Set_Right_Speed(1500);
	Set_Speed(2000,1500);
	left_dir=1;
	right_dir=1;
}

void CarLeft(void)//小车左转
{
//	Set_Left_Speed(1500);
//	Set_Right_Speed(2000);
	Set_Speed(1500,2000);
	left_dir=1;
	right_dir=1;
}

void CarStop(void)//小车停止
{
//	Set_Left_Speed(0);
//	Set_Right_Speed(0);
	Set_Speed(0,0);
}
