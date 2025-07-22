
/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Asma Askri
 * @brief          : Main program body
 ******************************************************************************
 * Bare metal UART Receiver Interrupt Driver implementation
 * Each time data is received, a uart interrupt occurs
 * and LED4 is toggled
 ******************************************************************************
 */

#include "stm32f4xx.h"

#include "UART.h"

#include <stdio.h>

char key = '\0';

static void usart_callback(void);

int main(void) {


	GPIO_Init();

	uart_init(USART1, 4800) ;

	while (1) {}


}


// static so that it can be only accessed here

static void usart_callback(void) {

         // toggle LED4

	     GPIOD->ODR ^= LED_ON;

	     // display the received value , used for debugging

	     key = USART1->DR;

}

void USART1_IRQHandler(void) {

	// if a character is received

	if (USART1->SR & SR_RXNE) {

		USART1->SR &=~ SR_RXNE;

		usart_callback();

	}

}



