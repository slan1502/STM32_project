/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * 文件名  ：main.c
 * 作者    ：VeryAI Team
 * 库版本  ：ST3.5.0
 * 实验平台：VeryAI STM32开发板
 * 描述    ：LED驱动代码  
 *
 * 论坛    ：http://www.veryai.com
 * 淘宝    ：http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"
	 
void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif





























