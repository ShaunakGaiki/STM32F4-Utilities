#include "stm32f4xx.h"
#include <stdio.h>

void delay(int ms)
{
	SysTick->LOAD = 0x003E80;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
	
	for(int i=0;i<ms;i++)
	{
		while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
		{
			//nothing
		}
	}
	return;
}

int main()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODE5;
	GPIOA->MODER |= GPIO_MODER_MODE5_0;
	GPIOA->BSRR = GPIO_BSRR_BR5;
	
	while(1)
	{
		GPIOA->BSRR |= GPIO_BSRR_BS5;
		delay(1000);
		GPIOA->BSRR = GPIO_BSRR_BR5;
		delay(1000);
	}
	return 0;
}