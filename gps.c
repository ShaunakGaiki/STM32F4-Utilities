#include "stm32f4xx.h"
#include <stdio.h>

void usart2_init()
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
	
	//setting PA2 as TX
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL2_0;
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL2_1;
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL2_2;
	
	return;
}

void usart2_config()
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

void usart2_send(int c)
{
	while(!(USART_SR_TXE & USART2->SR))
	{
		//nothing
	}
	USART2->DR = c;
}

//USART1
//PA9 is Tx and PA10 is Rx
void usart1_init()
{
	//enabling clocks
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	
	//making the mode alternate function
	GPIOA->MODER &= ~GPIO_MODER_MODE9;//clearing
	GPIOA->MODER &= ~GPIO_MODER_MODE10;
	GPIOA->MODER |= GPIO_MODER_MODE9_1;//setting
	GPIOA->MODER |= GPIO_MODER_MODE10_1;
	
	//setting the alternate function to usart
	GPIOA->AFR[1] &= ~GPIO_AFRH_AFRH1;//clearing
	GPIOA->AFR[1] &= ~GPIO_AFRH_AFRH2;
	
	//setting
	GPIOA->AFR[1] |= (GPIO_AFRH_AFRH1_0 | GPIO_AFRH_AFRH1_1 | GPIO_AFRH_AFRH1_2);
	GPIOA->AFR[1] |= (GPIO_AFRH_AFRH2_0 | GPIO_AFRH_AFRH2_1 | GPIO_AFRH_AFRH2_2);
	
	return;
}

void usart1_config()
{
	//Set the baud rate that has oversampling of 16 and normal baud rate of 9600
	USART1->BRR = 0x683;//68 is the mantissa which evaluates to 104 in decimal and 3 is the fractional part
	
	//MAKING DEFAULT
	USART1->CR1=0;
	USART1->CR2=0;
	USART1->CR3=0;
	
	//ENABLING TRANSMIT
	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;
	
	//TURNING ON USART
	USART1->CR1 |= USART_CR1_UE;
	
	return;
}

char usart1_read()
{
	while(!(USART1->SR & USART_SR_RXNE))
	{
		//nothing
	}
	return USART1->DR;
}

//OVERRIDING FGETC TO READ FROM USART CONSOLE
struct __FILE{int handle;};
FILE __stdin = {0};
FILE __stdout = {1};
FILE __stderr = {2};

int fgetc(FILE *f)
{
	int c=0;
	c = usart1_read();//reading from USART
	return c;
}


int main()
{
	char buffer[100],curr;
	int i;
	usart2_init();
	usart1_init();
	usart2_config();
	usart1_config();
	while(1)
	{
		curr=(char)fgetc(stdin);
		//usart2_send(curr);
		if(curr == '\n')
		{
			curr=fgetc(stdin);
			i=0;
			while(curr != '\n')
			{
				buffer[i]=curr;
				curr=(char)fgetc(stdin);
				i++;
			}
			if(buffer[3] == 'G' && buffer[4] == 'L' && buffer[5] == 'L')
			{
				for(i=0;i<100;i++)
				{
					usart2_send(buffer[i]);
				}
				usart2_send('\n');
			}
			for(i=0;i<100;i++)
			{
				buffer[i]= '\0';
			}
		}
	}
	return 0;
}