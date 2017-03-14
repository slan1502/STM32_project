/**
* 本文件主要提供控制德飞莱实验板的led库函数
* 作者：liuke
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
* 函数名称: printf_init
* 函数功能: 串口初始化
* 参    数: 无
******************************************************/
void printf_init(u32 baudRate)
{
	//uart的io口初始化
	GPIO_InitTypeDef io_init_struct;
	USART_InitTypeDef uart_init_struct;
	NVIC_InitTypeDef NVIC_init_struct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);		//使能uart和io口的时钟
	io_init_struct.GPIO_Pin = GPIO_Pin_10;
	io_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	io_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//RXD浮空输入
	GPIO_Init(GPIOA, &io_init_struct);
	io_init_struct.GPIO_Pin = GPIO_Pin_9;
	io_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;		//TXD推挽输出
	GPIO_Init(GPIOA, &io_init_struct);

	USART_DeInit(USART1);  					//复位串口1
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//优先级分组方式
	NVIC_init_struct.NVIC_IRQChannel = USART1_IRQn;				//串口1优先级通道 见stm32f10x.h
   	NVIC_init_struct.NVIC_IRQChannelPreemptionPriority = 3;		//抢占优先级
	NVIC_init_struct.NVIC_IRQChannelSubPriority = 3;			//子优先级
	NVIC_init_struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_init_struct);

	uart_init_struct.USART_BaudRate = baudRate;										//波特率
	uart_init_struct.USART_WordLength = USART_WordLength_8b;						//数据位 8位
    uart_init_struct.USART_StopBits = USART_StopBits_1;								//停止位
	uart_init_struct.USART_Parity = USART_Parity_No;								//奇偶校验
	uart_init_struct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;						//接收和发送方式
   	uart_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式使能还是失能
	USART_Init(USART1, &uart_init_struct);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									//使能接收中断
	USART_Cmd(USART1, ENABLE);		//打开串口

	printf("\n\rUART TEST!\n串口初始化完毕……\n");
}


PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* 循环等待直到发送结束*/
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}


