/**
* ���ļ���Ҫ�ṩ���Ƶ·���ʵ����led�⺯��
* ���ߣ�liuke
*/
#include "led.h"

void led_init()
{
	GPIO_InitTypeDef gpin_init_struct;
	//ʹ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);
	
	gpin_init_struct.GPIO_Pin = GPIO_Pin_5;
	gpin_init_struct.GPIO_Speed = GPIO_Speed_2MHz;
	gpin_init_struct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &gpin_init_struct);				//B��led1 
	GPIO_Init(GPIOE, &gpin_init_struct);				//E��led2 
}
