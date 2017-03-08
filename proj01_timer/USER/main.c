#include "stm32f10x.h"

int main()
{
	__IO u32 *temp;
	*temp = 0xaabbccdd;
	SysTick_Config(SystemCoreClock/1000);
	while(1)
	{
	}	
}