/**
* ���ļ���Ҫ�ṩ���Ƶ·���ʵ����led�⺯��
* ���ߣ�liuke
*/

#include "stm32f10x.h"

#ifndef _MY_LED_H
#define _MY_LED_H

#define LED2_ON		GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#define LED2_OFF	GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define LED1_ON		GPIO_ResetBits(GPIOE, GPIO_Pin_5)
#define LED1_OFF	GPIO_SetBits(GPIOE, GPIO_Pin_5)

void led_init(void);		//��ʼ��led�ȵ�io��

#endif
