#include "stm32f10x.h"
#include "usart.h"

#define EU_STM32	

#ifdef DFL_STM32	
	#define LED1_OFF	GPIO_SetBits(GPIOE, GPIO_Pin_5)
	#define LED1_ON		GPIO_ResetBits(GPIOE, GPIO_Pin_5)
	#define LED2_OFF	GPIO_SetBits(GPIOB, GPIO_Pin_5)
	#define LED2_ON		GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#endif
#ifdef EU_STM32	
	#define LED1_OFF	GPIO_SetBits(GPIOE, GPIO_Pin_5)
	#define LED1_ON		GPIO_ResetBits(GPIOE, GPIO_Pin_5)
	#define LED2_OFF	GPIO_SetBits(GPIOB, GPIO_Pin_5)
	#define LED2_ON		GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#endif

void LED_Init()
{
	GPIO_InitTypeDef my_GPIO_InitStruct;

#ifdef DFL_STM32	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);
#endif
#ifdef EU_STM32
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
#endif
	my_GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	my_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
#ifdef DFL_STM32	
	my_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOE, &my_GPIO_InitStruct);	//LED1
	GPIO_Init(GPIOB, &my_GPIO_InitStruct);	//LED2
#endif
#ifdef EU_STM32
	my_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOC, &my_GPIO_InitStruct);	//LED1
	my_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOD, &my_GPIO_InitStruct);	//LED2
#endif	
}

int main()
{
	__IO u32 temp;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SysTick_Config(SystemCoreClock/1000);
	LED_Init();
	uart_init(19200);
	//TIME2_Init();
	printf("hello\r\n");
	while(1)
	{
		//temp = TIM_GetCounter(TIM2);
	}	
}

