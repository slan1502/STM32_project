#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "uart.h"

void TIME2_Init()
{
	GPIO_InitTypeDef my_GPIO_InitStruct;
	NVIC_InitTypeDef my_NVIC_InitStruct;
	TIM_TimeBaseInitTypeDef my_TIM_InitStruct;
	TIM_ICInitTypeDef my_TIMIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能TIM2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA时钟
	//GPIO初始化
	GPIO_StructInit(&my_GPIO_InitStruct);											
	my_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	my_GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	my_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &my_GPIO_InitStruct);
	//通过NVIC初始化中断
// 	my_NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
// 	my_NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
// 	my_NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
// 	my_NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
// 	NVIC_Init(&my_NVIC_InitStruct);
	//初始化TIM2
	my_TIM_InitStruct.TIM_Prescaler = 0;
	my_TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	my_TIM_InitStruct.TIM_Period = 0xffff;
	my_TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &my_TIM_InitStruct);
	
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI1, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_ICStructInit(&my_TIMIC_InitStruct);		//选择默认的参数 
	my_TIMIC_InitStruct.TIM_ICFilter = 6;
	TIM_ICInit(TIM2, &my_TIMIC_InitStruct);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_SetCounter(TIM2, 0x7fff); 
  TIM_Cmd(TIM2, ENABLE);
}

void TIM3_Mode_Config(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_ICInitTypeDef TIM_ICInitStructure;
/*----------------------------------------------------------------*/
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
GPIO_StructInit(&GPIO_InitStructure);
/* Configure PA.06,07 as encoder input */
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
GPIO_Init(GPIOA, &GPIO_InitStructure);
/*----------------------------------------------------------------*/
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //TIM3时钟使能
TIM_DeInit(TIM3);
TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
TIM_TimeBaseStructure.TIM_Period =0xffff; //
TIM_TimeBaseStructure.TIM_Prescaler =0; //设置预分频:
TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ; //时钟分频系数：不分频 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //?????? 
	//TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
/*-----------------------------------------------------------------*/
//初始化编码模式
TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI1,
TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); //TIM_ICPolarity_Rising上升沿捕获
TIM_ICStructInit(&TIM_ICInitStructure);
TIM_ICInitStructure.TIM_ICFilter = 6; //比较滤波器
TIM_ICInit(TIM3, &TIM_ICInitStructure);
// Clear all pending interrupts
TIM_ClearFlag(TIM3, TIM_FLAG_Update);
TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //使能中断 //Reset counter
TIM3->CNT =5000;
TIM_Cmd(TIM3, ENABLE);
}

int main()
{
	__IO long temp;	
// 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	TIME2_Init();
	printf_init(19500);
	led_init();
	LED1_OFF;
	LED2_OFF;
	while(1)
	{
		temp = (int)(TIM_GetCounter(TIM2)-0x7fff)/2;
		printf("temp=%d\r\n", temp);
		LED1_ON;
		delay_ms(100);
		LED1_OFF;
		delay_ms(200);
	}	
}