#include "stm32f4xx.h"

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOA->MODER &= ~(GPIO_MODER_MODE5);//Clear
	GPIOA->MODER |= GPIO_MODER_MODE5_0;//Set to output
	GPIOA->BSRR = GPIO_BSRR_BS5;//turn on led
	
	return 0;
}