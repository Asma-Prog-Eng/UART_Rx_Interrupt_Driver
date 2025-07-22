Bare metal implementation  of a  UART Receiver Interrupt driver for STM32 development board 
## Features
UART1 initialization with configurable baud rates (4800, 9600 ,115200) and peripheral clock = 16MHz.
## Requirements
### Hardware
- Discovery STM32 development board (STM32F411x series)
- Multimeter (optional for debugging)
- External LED connected to PD12 (Optional , User LED can be used)
- Bread Board (Optional if  User LED will be used)
  
### Software
- STM32CubeIDE or compatible toolchain
- RealTerm
  
## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/Asma-Prog-Eng/UART_Rx_Interrupt_Driver
   
2. Import project into STM32CubeIDE:
File → Import... → Existing Projects into Workspace

3. Update the include path directories ,  to CMSIS folder ( under Project properties -> C/C++ General -> Includes : delete existing CMSIS path directory and  add the path to CMSIS folder <br />,
   that is included in the project, : Add -> File System <br />

4. Rebuild project dependenciesFile 

## Usage
Initialization : uart_init(USART1, 4800) <br />
Transmitting Data : a character is entered through RealTerm terminal <br />
UART receiver interrupt is generated : USART1_IRQHandler() 
LED4 is toggled :  usart_callback()
received character can be displayed, in debugging mode : key = ->  key = USART1->DR // in function usart_callback() 

## Project Structure

├── Core<br />
├── Inc<br />  → uart.h <br />
├── Src<br /> → uart.c<br /> → main.c

## Troubleshooting

No data received: <br />
- Verify baud rate settings <br />
- Check RX pin connections <br />
- Ensure correct clock configuration <br />

## Known Limitations
Limited to 8-bit data words

## Contributing
Pull requests are welcome. For major changes, open an issue first.

## License
MIT License <br />
Copyright (c) [2025] [Asma Askri]
