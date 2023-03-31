/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#define STM32F401xE


#include <stdint.h>
#include "stm32f4xx.h"
#include "signals.h"
#include "usart.h"
#include "arm_math.h"
#include <stdio.h>


extern float _5hz_signal[HZ_5_SIG_LEN];
extern float32_t inputSignal_f32_1kHz_15kHz[KHZ1_15_SIG_LEN];
float g_in_sig_sample;

static void plot_input_signal(void);
static void pseudo_dly(uint32_t dly);
static void serial_plot_input_sig(void);

int main(void)
{
    //char data[] = "Hello from STM32...\n\n\r";

    // Enable the floating point unit
    SCB->CPACR |= ((3<<10*2) | (3<<11*2));

    // Initialize the uart
    uart2_tx_init();

    while(1)
    {
    	//plot_input_signal();
    	serial_plot_input_sig();
    	/*for(uint32_t i=0; i<HZ_5_SIG_LEN; i++)
    	{
    		printf("%f\r\n", _5hz_signal[i]);
    	}*/
    }
}



static void plot_input_signal(void)
{
	for(uint32_t i=0;i<HZ_5_SIG_LEN; i++)
	{
		g_in_sig_sample = _5hz_signal[i];
		pseudo_dly(9000);
	}
}

static void pseudo_dly(uint32_t dly)
{
	for(uint32_t i=0; i<dly;i++);
}


static void serial_plot_input_sig(void)
{
	for(uint32_t i=0;i<KHZ1_15_SIG_LEN; i++)
	{
		printf("%f\r\n", inputSignal_f32_1kHz_15kHz[i]);
		pseudo_dly(9000);
	}
}
