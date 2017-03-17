/**
* 本文件主要提供控制德飞莱实验板的led库函数
* 作者：liuke
*/

#include "stm32f10x.h"

#ifndef _MY_LED_H
#define _MY_LED_H

#define BOARD	0			//定义实验板 0为德飞莱实验板 1是EU实验板
#if BOARD == 0
	#define LED1_GPIO		GPIOE
	#define LED2_GPIO		GPIOB
	#define LED1_PIN		GPIO_Pin_5
	#define LED2_PIN		GPIO_Pin_5
#elif	BOARD == 1
	#define LED1_GPIO		GPIOC
	#define LED2_GPIO		GPIOD
	#define LED1_PIN		GPIO_Pin_0
	#define LED2_PIN		GPIO_Pin_3
#endif
	
#define LED2_ON		GPIO_ResetBits(LED2_GPIO, LED2_PIN)
#define LED2_OFF	GPIO_SetBits(LED2_GPIO, LED2_PIN)
#define LED1_ON		GPIO_ResetBits(LED1_GPIO, LED1_PIN)
#define LED1_OFF	GPIO_SetBits(LED1_GPIO, LED1_PIN)

void led_init(void);		//初始化led等的io口

#endif
