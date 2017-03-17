#include "stm32f10x.h"
#include "my_APP_lib\uart.h"
#include "my_APP_lib\led.h"
#include "my_APP_lib\delay.h"


int main()
{
	__IO u32 temp;
	led_init();
	delay_init();
	printf_init(19200);
	printf("hello\r\n");
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

