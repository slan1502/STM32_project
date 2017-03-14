/**
* 本文件主要提供控制德飞莱实验板的led库函数
* 作者：liuke
*/

#include "stm32f10x.h"

#ifndef _MY_LED_H
#define _MY_LED_H

#define LED2_ON		GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#define LED2_OFF	GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define LED1_ON		GPIO_ResetBits(GPIOE, GPIO_Pin_5)
#define LED1_OFF	GPIO_SetBits(GPIOE, GPIO_Pin_5)

void led_init(void);		//初始化led等的io口

#endif
