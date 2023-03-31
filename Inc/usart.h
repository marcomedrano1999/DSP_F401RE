/*
 * usart.h
 *
 *  Created on: Mar 31, 2023
 *      Author: Medrano
 */

#ifndef USART_H_
#define USART_H_

#include "stm32f401xe.h"

void uart2_write_array(uint8_t *data, uint32_t len);
void uart2_write(uint8_t ch);
void uart2_tx_init(void);

#endif /* USART_H_ */
