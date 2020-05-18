#include "stm32f4xx.h"
#include <stdio.h>

int count;

void timer2_init()
{	
	//enable the clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	
	//setting to alternate function for timer
	GPIOA->MODER &= ~GPIO_MODER_MODE0;
	GPIOA->MODER |= GPIO_MODER_MODE0_1;
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL0_0;
	
	//making PC13 input
	GPIOC->MODER &= ~GPIO_MODER_MODE13;
	
	//reset value is 0x0000
	TIM2->SMCR = 0;
	TIM2->SMCR |= TIM_SMCR_ECE;
	TIM2->SMCR |= TIM_SMCR_ETF_0 | TIM_SMCR_ETF_1;
	//TIM2->SMCR |= TIM_SMCR_MSM;
	TIM2->SMCR |= TIM_SMCR_TS_0 | TIM_SMCR_TS_1 | TIM_SMCR_TS_2;
	TIM2->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_2;
	
	//enable
	TIM2->CR1 = 1;
	
	return;
}

int main()
{
	timer2_init();
	while(1)
		count = TIM2->CNT;
	return 0;
	
}
