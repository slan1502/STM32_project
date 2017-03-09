#include "stm32f10x.h"

void PWM_Init()
{
	GPIO_InitTypeDef my_GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef my_TIM_InitStruct;
	TIM_OCInitTypeDef my_TIMOC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ��TIM2ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	//ʹ��GPIOAʱ��
	
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
	TIM_ARRPreloadConfig(TIM4, ENABLE);						//ʹ��TIMx�� ARR �ϵ�Ԥװ�ؼĴ��� 
  TIM_Cmd(TIM4, ENABLE);

	TIM_OCStructInit(&my_TIMOC_InitStruct);		//ѡ��Ĭ�ϵĲ��� 
	my_TIMOC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	my_TIMOC_InitStruct.TIM_OutputState = TIM_OutputState_Enable;
	my_TIMOC_InitStruct.TIM_Pulse = 500;
	TIM_OC1Init(TIM4, &my_TIMOC_InitStruct);
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);	   	//ʹ�� TIMx�� CCR1 �ϵ�Ԥװ�ؼĴ���
	TIM_OC2Init(TIM4, &my_TIMOC_InitStruct);
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);	   	//ʹ�� TIMx�� CCR2 �ϵ�Ԥװ�ؼĴ���
	TIM_OC3Init(TIM4, &my_TIMOC_InitStruct);
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);	   	//ʹ�� TIMx�� CCR3 �ϵ�Ԥװ�ؼĴ���
  TIM_CtrlPWMOutputs(TIM4,ENABLE);  						//����TIM4 ��PWM ���Ϊʹ��  
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