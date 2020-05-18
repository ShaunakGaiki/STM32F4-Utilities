#include "stm32f4xx.h"
#include <stdio.h>

#define clearGPIO(port, pin) GPIO##port->MODER &= GPIO_MODER_MODE##pin
#define setOutput(port,pin) GPIO##port->MODER |= GPIO_MODER_MODE##pin##_0
#define writeHigh(port,pin) GPIO##port->BSRR |= GPIO_BSRR_BS##pin
#define writeLow(port,pin) GPIO##port->BSRR |= GPIO_BSRR_BR##pin

//PCx corresponds to DBx of the lcd
//PB0 is RS (register set)
//PB1 is enable
void delay(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
	{
		for(j=0;j<1598;j++)
		{
			//nothing
		}
	}
	return;
}

void lcd_setLow()
{
	writeLow(B,0);
	writeLow(B,1);
	writeLow(C,0);
	writeLow(C,1);
	writeLow(C,2);
	writeLow(C,3);
	writeLow(C,4);
	writeLow(C,5);
	writeLow(C,6);
	writeLow(C,7);
	return;
}

void lcd_command(char data)
{
	writeLow(B,0);
	GPIOC->ODR = data;
	writeHigh(B,1);
	delay(1);
	writeLow(B,1);
	delay(2);
	return;
}

void lcd_init()
{
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN);//enabling clocks
	
	//clearing and setting
	clearGPIO(B,0);
	clearGPIO(B,1);
	//clearGPIO(B,2);
	clearGPIO(C,0);
	clearGPIO(C,1);
	clearGPIO(C,2);
	clearGPIO(C,3);
	clearGPIO(C,4);
	clearGPIO(C,5);
	clearGPIO(C,6);
	clearGPIO(C,7);
	setOutput(B,0);
	setOutput(B,1);
	//setOutput(B,2);
	setOutput(C,0);
	setOutput(C,1);
	setOutput(C,2);
	setOutput(C,3);
	setOutput(C,4);
	setOutput(C,5);
	setOutput(C,6);
	setOutput(C,7);
	
	lcd_command(0x30);
	delay(5);
	lcd_command(0x30);
	delay(1);
	lcd_command(0x30);
	delay(1);
	lcd_command(0x38);
	lcd_command(0x06);
	lcd_command(0x01);
	lcd_command(0x0F);
}

void lcd_write(char data)
{
	writeHigh(B,0);
	GPIOC->ODR = data;
	writeHigh(B,1);
	delay(1);
	writeLow(B,1);
	delay(2);
	return;
}

int main()
{
	char message[11]={"Hello World"};
	delay(17);
	lcd_init();
	for(int j=0;j<4;j++)
	{
		for(int i=0;i<11;i++)
		{
			lcd_write(message[i]);
		}
	}
	return 0;
}