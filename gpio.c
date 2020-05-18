#include "stm32f4xx.h"

int delay(int ms)//delays certain amount of milliseconds
{
	int i,j;
	for(i=0;i<ms;i++)
	{
		for(j=0;j<1598;j++)
		{
			//nothing
		}
	}
}

int main(void)
{
	int i;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //enabling gpioA clock
	GPIOA->MODER &= ~(GPIO_MODER_MODE5);// clearing mode for PA5
	GPIOA->MODER |= GPIO_MODER_MODE5_0;// setting PA5 to output
	while(1)
	{
		GPIOA->ODR  ^= GPIO_ODR_OD5;//toggles PA5
		delay(500);
	}
	return 0;
}