#include "stm32f4xx.h"

//PA2 is TX and PA3 is RX


void usart_init()
{
	//ENABLING CLOCK
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	
	//SETTING PA2 and PA3 as alternate function
	GPIOA->MODER &= ~GPIO_MODER_MODE2;//clearing
	GPIOA->MODER &= ~GPIO_MODER_MODE3;//clearing
	GPIOA->MODER |= GPIO_MODER_MODE2_1;//setting bit 1 to make the mode 10, which is alternate function
	GPIOA->MODER |= GPIO_MODER_MODE3_1;//setting bit 1 to make the mode 10, which is alternate function
	
	//MAKING THE ALTERNATE FUNCTION USART 2
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL2;//clearing
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL3;//clearing
	
	//setting PA3 as RX
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL3_0;
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL3_1;
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL3_2;
	
	//setting PA2 as RX
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL2_0;
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL2_1;
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL2_2;
	
	return;
}

void usart_config()
{
	//Set the baud rate that has oversampling of 16 and normal baud rate of 9600
	USART2->BRR = 0x683;//68 is the mantissa which evaluates to 104 in decimal and 3 is the fractional part
	
	//MAKING DEFAULT
	USART2->CR1=0;
	USART2->CR2=0;
	USART2->CR3=0;
	
	//ENABLING TRANSMIT
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;
	
	//TURNING ON USART
	USART2->CR1 |= USART_CR1_UE;
	
	return;
}

void usart_send()
{
	while(1)
	{
		while(USART_SR_TXE & USART2->SR)
		{
			USART2->DR |= 'a';
		}
	}
}


int main()
{
	usart_init();
	usart_config();
	usart_send();
	return 0;
}