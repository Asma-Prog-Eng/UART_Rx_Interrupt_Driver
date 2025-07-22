
/* Developo USART Tranceiver
 * USART peripheral : USART1
 * Rx Pin = PB7
 * Tx Pin = PB6
 *
 * */

#include "stm32f4xx.h"

#include "UART.h"

#include <stdio.h>

#define USARTEN            (1U << 4)

#define GPIODEN            (1U << 3)

#define GPIOBEN            (1U << 1)

#define AF7_Rx             ((1U << 28) |(1U << 29) | (1U << 30))

#define AF7_Tx             ((1U << 24) |(1U << 25) | (1U << 26))

#define GPIOB_MODER_1      (1U << 14)

#define GPIOB_MODER_2      (1U << 15)

#define GPIOB_MODER_3      (1U << 12)

#define GPIOB_MODER_4      (1U << 13)

#define GPIOD_MODER_1   (1U << 24)

#define GPIOD_MODER_2   (1U << 25)

#define GPIODEN         (1U << 3)

#define SR_RXNE            (1U << 5)

#define SR_TXE             (1U << 7)

#define CR1_RE             (1U << 2)

#define CR1_TE             (1U << 3)

#define CR1_UE             (1U << 13)

#define SysClk             16000000UL

#define PeriphClk          SysClk

#define  CR1_RXNEIE        (1U << 5)

// The RXNE flag can also be cleared by writing a zero to it.

void uart_init (USART_TypeDef *USARTx, uint32_t Baudrate) {


	// enable clock acess to USART1

      RCC->APB2ENR |= USARTEN ;

	// configure baud rate in USART2_BRR

     //uart_set_baudrate(USARTx, Baudrate);

     BaudeRate(USARTx, Baudrate);


     // disable global interrupts

     __disable_irq();

     // enable interrupt for uart receiver

     USARTx->CR1 |=  CR1_RXNEIE ;

	// enable usart receiver and transmitter

      USARTx->CR1 |= ( CR1_RE | CR1_TE) ;

      // Enable USARTx interrupt  in NVIC

      	  if( USARTx == USART1) {
      		  NVIC_EnableIRQ(USART1_IRQn);
      	  }

      	  else if ( USARTx ==  USART2) {
              NVIC_EnableIRQ(USART2_IRQn);
      	  }

      	 else if ( USARTx ==  USART6) {
      	              NVIC_EnableIRQ(USART6_IRQn);
      	      	  }

      	  else {
    	      printf("No valid USART peripheral is selected\n");

      	  }


      // enable global interrtupts

      __enable_irq();


    // enable usart periph

      USARTx->CR1 |= CR1_UE;


}


char uart_read(USART_TypeDef *USARTx) {

    // wait till character is received in data register

	// data register is not empty

	while (!( USARTx->SR & SR_RXNE )) {};

	// read received data register

	return USARTx->DR;

}


void uart_write(USART_TypeDef *USARTx, char ch){

	 // wait till character is transmitted from data register

	// data register is empty

	while (!( USARTx->SR & SR_TXE )) {};

	// write data to data register

	USARTx->DR |= ch;


}

void GPIO_Init(void){

	// enable clock acess for port B

	RCC->AHB1ENR |=  (GPIOBEN | GPIODEN );

	// set pin PB7 mode to alternate (0x2)

	GPIOB->MODER &=~ GPIOB_MODER_1;

	GPIOB->MODER |= GPIOB_MODER_2;

	// set pin PB6 mode to alternate (0x2)

	GPIOB->MODER &=~ GPIOB_MODER_3;

	GPIOB->MODER |= GPIOB_MODER_4;

	// set alternate function to AF7

	GPIOB->AFR[0] |= (AF7_Rx |  AF7_Tx );

	// set PD12 pin mode to digital output : 01

	GPIOD->MODER |= GPIOD_MODER_1;

	GPIOD->MODER &= ~GPIOD_MODER_2;

}

/*
 * USARTDiv = fclck/(Baude Rate * 16)
 * Exp : for baud rate = 9600 bps
 * USARTDiv= 104.166
 * Mantissa = 104 [4:12]
 * Fraction = 0.166 * 16 = 3 [0:3]
 * Baude Rate = {4800, 9600, 115200} ;
 *
 */

void  BaudeRate(USART_TypeDef *USARTx, uint32_t baudrate) {



	if (baudrate == 4800) {

		USARTx->BRR |= (1U << 8) | (1U << 10) | (1U << 11);

		USARTx->BRR |=  (1U << 1);
	}

	else if (baudrate == 9600) {

		USARTx->BRR |= (1U << 7) | (1U << 9 ) | (1U << 10);

		USARTx->BRR |= (1U << 0) | (1U << 1);
	}

	else if (baudrate == 115200) {

		USARTx->BRR |= (1U << 7);

		USARTx->BRR |= (1U << 0) | (1U << 1) | (1U << 3);
	}

	else {

		printf("Select baud rate in {4800, 9600, 115200}\n");
	}
}



