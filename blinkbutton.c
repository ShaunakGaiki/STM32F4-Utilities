#include "stm32f4xx.h"
#include <stdio.h>

int count=0;

void delay(int ms)
{
	for(int i=0;i<ms;i++)
	{
		for(int j=0;j<3195/2;j++)
		{
			//nothing
		}
	}
	return;
}

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
	GPIOC->MODER &= ~GPIO_MODER_MODE0;
	
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PC;
	
	EXTI->IMR |= EXTI_IMR_IM13;//unmask
	EXTI->IMR |= EXTI_IMR_IM0;//unmask
	
	EXTI->FTSR |= EXTI_FTSR_TR13;//setting to falling edge
	EXTI->FTSR |= EXTI_RTSR_TR0;
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	NVIC_EnableIRQ(EXTI0_IRQn);
	
	__enable_irq();
	return;
}

void EXTI15_10_IRQHandler()
{
	while(!(GPIOC->IDR & GPIO_IDR_ID13_Msk))
		GPIOA->BSRR = GPIO_BSRR_BR5;
	EXTI->PR |= EXTI_PR_PR13;
}

void EXTI0_IRQHandler()
{
	count++;
	delay(50);
	EXTI->PR |= EXTI_PR_PR0;
}

int main()
{
	interrupt_init();
	while(1)
	{
		GPIOA->BSRR |= GPIO_BSRR_BS5;
		delay(300);
		GPIOA->BSRR = GPIO_BSRR_BR5;
		delay(300);
	}
	return 0;
}
