#include "stm32f10x.h"
#include "uart.h"
#include "delay.h"

int main()
{
	u32 count=0;
	delay_init();
	printf_init(19200);
	while(1)
	{
		delay_ms(500);
		printf("hello count=%d\r\n", count++);
	}	
}

