#include "stm32f4xx.h"
// button on PC13 (Port C, Pin 13)

int main(void)
{
	int result;
 	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //enabling gpioA clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; //enabling gpioC clock
	GPIOA->MODER &= ~(GPIO_MODER_MODE5);// clearing mode for PA5
	GPIOA->MODER |= GPIO_MODER_MODE5_0;// setting PA5 to output
	GPIOC->MODER &= ~(GPIO_MODER_MODE13);// clears PC13, which makes it an input
	while(1)
	{
		GPIOA->ODR &= ~(GPIO_ODR_OD5);
		result=GPIOC->IDR & GPIO_IDR_ID13_Msk;
		if(result==0)
		{
			GPIOA->ODR |= GPIO_ODR_OD5;//turn on the led
		}
	}
	return 0;
}
