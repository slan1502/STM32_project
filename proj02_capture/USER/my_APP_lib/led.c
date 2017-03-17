/**
* 本文件主要提供控制德飞莱实验板的led库函数
* 作者：liuke
*/
#include "led.h"

void led_init()
{
	GPIO_InitTypeDef gpin_init_struct;
	//使能时钟
#if BOARD == 0
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);
#elif	BOARD == 1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
#endif	
	gpin_init_struct.GPIO_Pin = LED1_PIN;
	gpin_init_struct.GPIO_Speed = GPIO_Speed_2MHz;
	gpin_init_struct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LED1_GPIO, &gpin_init_struct);				//led1 
	gpin_init_struct.GPIO_Pin = LED2_PIN;
	GPIO_Init(LED2_GPIO, &gpin_init_struct);				//led2 
}
