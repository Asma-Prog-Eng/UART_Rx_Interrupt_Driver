

#ifndef UART_H_
#define UART_H_

#define LED_ON    		(1U << 12)

#define SR_RXNE            (1U << 5)

void uart_init(USART_TypeDef *USARTx, uint32_t Baudrate) ;

char uart_read (USART_TypeDef *USARTx);

void uart_write(USART_TypeDef *USARTx, char ch);

void  BaudeRate(USART_TypeDef *USARTx, uint32_t baudrate);


void GPIO_Init(void);

#endif /* UART_H_ */
