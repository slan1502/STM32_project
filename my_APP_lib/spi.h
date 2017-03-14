/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * 作者    ：VeryAI Team
 * 库版本  ：ST3.5.0
 * 实验平台：VeryAI STM32开发板
 * 描述    ：SPI驱动代码  
 *
 * 论坛    ：http://www.veryai.com
 * 淘宝    ：http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#ifndef __SPI_H
#define __SPI_H
#include "sys.h"

void SPI1_Init(void);			 						//初始化SPI1口
void SPI2_Init(void);			 						//初始化SPI2口
void SPI1_SetSpeed(u8 SpeedSet); 			//设置SPI1速度  		 
void SPI2_SetSpeed(u8 SpeedSet); 			//设置SPI2速度   
u8 SPI1_ReadWriteByte(u8 TxData);			//SPI1总线读写一个字节
u8 SPI2_ReadWriteByte(u8 TxData);			//SPI2总线读写一个字节
		 
#endif
