#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "uart.h"
#include "led.h"
#include "delay.h"

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
	__IO u32 temp;
	led_init();
	delay_init();
	TIM3_Mode_Config();
	TIM3->CNT =0x7fff;
	printf_init(19200);
	while(1)
	{
		LED1_ON;
		delay_ms(200);
		LED1_OFF;
		delay_ms(200);
		if(GPIO_ReadOutputDataBit(LED2_GPIO, LED2_PIN))
		{
			GPIO_WriteBit(LED2_GPIO, LED2_PIN, Bit_RESET);
		}else{
			GPIO_WriteBit(LED2_GPIO, LED2_PIN, Bit_SET);
		}
		printf("tim3->cnt=%d\r\n", TIM3->CNT-0x7fff);	
	}	
}

