/*
 * usart.c
 *
 *  Created on: Mar 31, 2023
 *      Author: Medrano
 */

#include "usart.h"


#define SYS_FREQ		16000000
#define UART_BAUDRATE	115200


static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate);

int __io_putchar(int ch)
{
	uart2_write(ch);

	return ch;
}


void uart2_tx_init(void)
{
	RCC_TypeDef *pRCC = RCC;
	GPIO_TypeDef *pGPIOA = GPIOA;
	USART_TypeDef *pUART2 = USART2;


	/*******Configure UART GPIO pins*********/

	//1. Enable clock access to GPIOA
	pRCC->AHB1ENR |= (1<<0);

	//2. Set PA2 and PA3 mode to alternate function mode
	pGPIOA->MODER |= (2 << 4);
	pGPIOA->MODER |= (2 << 6);

	//3. Set PA2 and PA3 alternate function type to UART_TX(AF07)
	pGPIOA->AFR[0] |= (7<<8);
	pGPIOA->AFR[0] |= (7<<12);

	/********Configure UART*********/
	//PA2 and PA3

	//1. Enable clock access to UART2
	pRCC->APB1ENR |= (1 << 17);

	//2. Configure baud rate
	pUART2->BRR |= compute_uart_bd(SYS_FREQ, UART_BAUDRATE);

	//3. Configure the transfer direction
	pUART2->CR1 |= (1 << 3);

	//4. Enable UART module
	pUART2->CR1 |= (1 << 13);
}


void uart2_write_array(uint8_t *data, uint32_t len)
{
	for(uint32_t i=0; i<len; i++)
	{
		uart2_write(data[i]);
	}

}


void uart2_write(uint8_t ch)
{
	USART_TypeDef *pUART2 = USART2;

	/* Make sure transmit */
	while(!(pUART2->SR & (1<<7)));

	// Write to the transmit data register
	pUART2->DR = ch;

	/* Make sure transmission is complete */
	while(!(pUART2->SR & (1<<6)));
}


static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate)
{
	return ((periph_clk + (baudrate/2))/baudrate);
}
