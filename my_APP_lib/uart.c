/**
* ���ļ���Ҫ�ṩ���Ƶ·���ʵ����led�⺯��
* ���ߣ�liuke
*/
#include "uart.h"


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/******************************************************
* ��������: printf_init
* ��������: ���ڳ�ʼ��
* ��    ��: ��
******************************************************/
void printf_init(u32 baudRate)
{
	//uart��io�ڳ�ʼ��
	GPIO_InitTypeDef io_init_struct;
	USART_InitTypeDef uart_init_struct;
	NVIC_InitTypeDef NVIC_init_struct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);		//ʹ��uart��io�ڵ�ʱ��
	io_init_struct.GPIO_Pin = GPIO_Pin_10;
	io_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	io_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//RXD��������
	GPIO_Init(GPIOA, &io_init_struct);
	io_init_struct.GPIO_Pin = GPIO_Pin_9;
	io_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;		//TXD�������
	GPIO_Init(GPIOA, &io_init_struct);

	USART_DeInit(USART1);  					//��λ����1
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//���ȼ����鷽ʽ
	NVIC_init_struct.NVIC_IRQChannel = USART1_IRQn;				//����1���ȼ�ͨ�� ��stm32f10x.h
   	NVIC_init_struct.NVIC_IRQChannelPreemptionPriority = 3;		//��ռ���ȼ�
	NVIC_init_struct.NVIC_IRQChannelSubPriority = 3;			//�����ȼ�
	NVIC_init_struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_init_struct);

	uart_init_struct.USART_BaudRate = baudRate;										//������
	uart_init_struct.USART_WordLength = USART_WordLength_8b;						//����λ 8λ
    uart_init_struct.USART_StopBits = USART_StopBits_1;								//ֹͣλ
	uart_init_struct.USART_Parity = USART_Parity_No;								//��żУ��
	uart_init_struct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;						//���պͷ��ͷ�ʽ
   	uart_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽʹ�ܻ���ʧ��
	USART_Init(USART1, &uart_init_struct);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									//ʹ�ܽ����ж�
	USART_Cmd(USART1, ENABLE);		//�򿪴���

	printf("\n\rUART TEST!\n���ڳ�ʼ����ϡ���\n");
}


PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* ѭ���ȴ�ֱ�����ͽ���*/
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}


