#include "stm32f10x.h"

void PWM_Init()
{
	GPIO_InitTypeDef my_GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef my_TIM_InitStruct;
	TIM_OCInitTypeDef my_TIMOC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能TIM2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	//使能GPIOA时钟
	
	GPIO_StructInit(&my_GPIO_InitStruct);											
	my_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	my_GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	my_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &my_GPIO_InitStruct);
	
	my_TIM_InitStruct.TIM_Prescaler = 1440-1;
	my_TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	my_TIM_InitStruct.TIM_Period = 1000-1;
	my_TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4, &my_TIM_InitStruct);
	TIM_ARRPreloadConfig(TIM4, ENABLE);						//使能TIMx在 ARR 上的预装载寄存器 
  TIM_Cmd(TIM4, ENABLE);

	TIM_OCStructInit(&my_TIMOC_InitStruct);		//选择默认的参数 
	my_TIMOC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	my_TIMOC_InitStruct.TIM_OutputState = TIM_OutputState_Enable;
	my_TIMOC_InitStruct.TIM_Pulse = 500;
	TIM_OC1Init(TIM4, &my_TIMOC_InitStruct);
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);	   	//使能 TIMx在 CCR1 上的预装载寄存器
	TIM_OC2Init(TIM4, &my_TIMOC_InitStruct);
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);	   	//使能 TIMx在 CCR2 上的预装载寄存器
	TIM_OC3Init(TIM4, &my_TIMOC_InitStruct);
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);	   	//使能 TIMx在 CCR3 上的预装载寄存器
  TIM_CtrlPWMOutputs(TIM4,ENABLE);  						//设置TIM4 的PWM 输出为使能  
}
	
int main()
{
	__IO u32 temp;
	
	PWM_Init();
	TIM_SetCompare1(TIM4, 200);
	TIM_SetCompare2(TIM4, 400);
	TIM_SetCompare3(TIM4, 600);
	while(1)
	{
		temp++;
	}	
}