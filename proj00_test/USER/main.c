#include "stm32f10x.h"
#include "uart.h"
#include "led.h"
#include "delay.h"


int main()
{
	__IO u32 temp;
	led_init();
	delay_init();
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
			
	}	
}

