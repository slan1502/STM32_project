/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * ����    ��VeryAI Team
 * ��汾  ��ST3.5.0
 * ʵ��ƽ̨��VeryAI STM32������
 * ����    ��SPI��������  
 *
 * ��̳    ��http://www.veryai.com
 * �Ա�    ��http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#ifndef __SPI_H
#define __SPI_H
#include "sys.h"

void SPI1_Init(void);			 						//��ʼ��SPI1��
void SPI2_Init(void);			 						//��ʼ��SPI2��
void SPI1_SetSpeed(u8 SpeedSet); 			//����SPI1�ٶ�  		 
void SPI2_SetSpeed(u8 SpeedSet); 			//����SPI2�ٶ�   
u8 SPI1_ReadWriteByte(u8 TxData);			//SPI1���߶�дһ���ֽ�
u8 SPI2_ReadWriteByte(u8 TxData);			//SPI2���߶�дһ���ֽ�
		 
#endif
