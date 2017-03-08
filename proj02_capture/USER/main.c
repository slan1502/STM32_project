#include "stm32f10x.h"

void TIME2_Init()
{
	GPIO_InitTypeDef my_GPIO_InitStruct;
	NVIC_InitTypeDef my_NVIC_InitStruct;
	TIM_TimeBaseInitTypeDef my_TIM_InitStruct;
	TIM_ICInitTypeDef my_TIMIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能TIM2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA时钟
	
	GPIO_StructInit(&my_GPIO_InitStruct);											
	my_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	my_GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	my_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &my_GPIO_InitStruct);
	
	my_NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	my_NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	my_NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	my_NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&my_NVIC_InitStruct);
	
	my_TIM_InitStruct.TIM_Prescaler = 0;
	my_TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	my_TIM_InitStruct.TIM_Period = 5;
	my_TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &my_TIM_InitStruct);
	
	TIM_ICStructInit(&my_TIMIC_InitStruct);		//选择默认的参数 
	my_TIMIC_InitStruct.TIM_ICFilter = 6;
	TIM_ICInit(TIM2, &my_TIMIC_InitStruct);
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI1, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_SetCounter(TIM2, 0); 
  TIM_Cmd(TIM2, ENABLE);
}
	
int main()
{
	__IO u32 temp;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	TIME2_Init();
	//SysTick_Config(SystemCoreClock/1000);
	while(1)
	{
		temp = TIM_GetCounter(TIM2);
	}	
}