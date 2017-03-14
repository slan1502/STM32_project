/**
* 本文件主要提供控制德飞莱实验板的led库函数
* 作者：liuke
*/
#include "led.h"

void led_init()
{
	GPIO_InitTypeDef gpin_init_struct;
	//使能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);
	
	gpin_init_struct.GPIO_Pin = GPIO_Pin_5;
	gpin_init_struct.GPIO_Speed = GPIO_Speed_2MHz;
	gpin_init_struct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &gpin_init_struct);				//B口led1 
	GPIO_Init(GPIOE, &gpin_init_struct);				//E口led2 
}
