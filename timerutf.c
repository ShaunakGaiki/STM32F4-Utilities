#include "stm32f4xx.h"

void timer2_init()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	TIM2->CR1 |= TIM_CR1_DIR;//making it a down counter
	
	TIM2->PSC |= 1599;
	
	TIM2->ARR = 10000;
	
	TIM2->CR1 |= TIM_CR1_CEN;
	return;
}

int main()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODE5;
	GPIOA->MODER |= GPIO_MODER_MODE5_0;
	timer2_init();
	while(1)
	{
		if(!(TIM2->SR & TIM_SR_UIF_Msk))
		{
			//nothing
		}
		else
		{
			TIM2->SR &= ~TIM_SR_UIF;
			GPIOA->ODR ^= GPIO_ODR_OD5;
		}
	}
	return 0;
}