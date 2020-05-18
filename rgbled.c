#include "stm32f4xx.h"

/*
KEY:
RED LED: PIN A0 on arduino; pin PA0 on nucleo
GREEN LED: PIN A1 on arduino; pin PA1 on nucleo
BLUE LED: PIN A2 on arduino; pin PA4 on nucleo

RED BUTTON: D3 on arduino; PB3 on nucleo
GREEN BUTTON: D5 on arduino; PB4 on nucleo
BLUE BUTTON: D4 on arduino; PB5 on nucleo
*/

int main()
{
	int result[3];
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;//enabling clocks
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;//enabling clocks
	//TESTING THE LED WITHOUT INVOLVING BUTTONS
	GPIOA->MODER &= ~GPIO_MODER_MODE0;//clearing 
	GPIOA->MODER |= GPIO_MODER_MODE0_0;//setting as an output
	GPIOA->MODER &= ~GPIO_MODER_MODE1;//clearing 
	GPIOA->MODER |= GPIO_MODER_MODE1_0;//setting as an output
	GPIOA->MODER &= ~GPIO_MODER_MODE4;//clearing 
	GPIOA->MODER |= GPIO_MODER_MODE4_0;//setting as an output
	GPIOA->BSRR |= GPIO_BSRR_BS0;//turning off the red led, since the pin is the cathode
	GPIOA->BSRR |= GPIO_BSRR_BS1;
	GPIOA->BSRR |= GPIO_BSRR_BS4;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4;// clearing
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD4_0;//setting
	
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5;//clearing
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD5_1;//setting
	
	GPIOA->OTYPER |= GPIO_OTYPER_OT0;//this makes the red output open drain

	//NOW BUTTON INPUT
	while(1)
	{
		GPIOA->BSRR |= GPIO_BSRR_BS0;//turning off the red led, since the pin is the cathode
		GPIOA->BSRR |= GPIO_BSRR_BS1;
		GPIOA->BSRR |= GPIO_BSRR_BS4;
		result[0] = GPIOB->IDR & GPIO_IDR_ID3_Msk;
		if(result[0]==0)
		{
			GPIOA->BSRR |= GPIO_BSRR_BR0;
		}
		result[1] = GPIOB->IDR & GPIO_IDR_ID4_Msk;
		if(result[1]==0)
		{
			GPIOA->BSRR |= GPIO_BSRR_BR1;
		}
		result[2] = GPIOB->IDR & GPIO_IDR_ID5_Msk;
		if(result[2])
		{
			GPIOA->BSRR |= GPIO_BSRR_BR4;
		}
	}
	return 0;
}