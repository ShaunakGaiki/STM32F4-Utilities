#include "stm32f4xx.h"
#include <stdio.h>

void interrupt_init()
{
	__disable_irq();//disable interrupts globally
	//enable clocks
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	GPIOA->MODER &= ~GPIO_MODER_MODE5;
	GPIOA->MODER |= GPIO_MODER_MODE5_0;
	GPIOC->MODER &= ~GPIO_MODER_MODE13;//makes this an input
	
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
	
	EXTI->IMR |= EXTI_IMR_IM13;//unmask
	
	EXTI->FTSR |= EXTI_FTSR_TR13;//setting to falling edge
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	__enable_irq();
	return;
}

void EXTI15_10_IRQHandler()
{
	while(!(GPIOC->IDR & GPIO_IDR_ID13_Msk))
		GPIOA->BSRR = GPIO_BSRR_BR5;
	EXTI->PR |= EXTI_PR_PR13;
}

int main()
{
	interrupt_init();
	while(1)
	{
		GPIOA->BSRR |= GPIO_BSRR_BS5;
		for(int i=0;i<3195*100;i++)
		{
			//nothing
		}
		//nothing
		GPIOA->BSRR |= GPIO_BSRR_BR5;
		for(int i=0;i<3195*100;i++)
		{
			//nothing
		}
	}
	return 0;
}