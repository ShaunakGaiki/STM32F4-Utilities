#include "stm32f4xx.h"

void timer2_init()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	
	GPIOA->MODER &= ~GPIO_MODER_MODE5;
	GPIOA->MODER |= GPIO_MODER_MODE5_1;
	
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL5;
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL5_0;
	
	TIM2->PSC = 8-1;
	
	TIM2->ARR = 40000;
	//each step is 1/200 of a ms
	
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	
	TIM2->CCR1 = 1*3000;
	
	TIM2->CCER = TIM_CCER_CC1E;
	
	TIM2->CNT = 0;
	
	TIM2->CR1 |= TIM_CR1_CEN;

	return;
}

int main()
{
	timer2_init();
	while(1);
}