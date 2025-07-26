
#include<stm32f4xx.h>
#include<SPI.h>


void initClocks(void){
	RCC->AHB1RSTR |= ((1u<<1) 			// Enable GPIOA Clock
					 |(1u<<0));			// Enable GPIOB Clock
	RCC->APB2ENR |= (1u<<12);			// Enable SPI1 Clock

}

// Setting the pins to alternate function
void setPinMode(void){

	// Reset register bits
	GPIOA->MODER &= ((3u << (2 * 4))	// Clear PA4
					|(3u << (2 * 5))	// Clear PA5
					|(3u << (2 * 6))	// Clear PA6
					|(3u << (2 * 7))	// Clear PA7
					);

	// Set register bits
	GPIOA->MODER &= ((2u << (2 * 4))	// Set PA4
					|(2u << (2 * 5))	// Set PA5
					|(2u << (2 * 7))	// Set PA7
					|(2u << (2 * 6))	// Set PA6
					);

}

// Selecting the correct AF to SPI1
void setAF(void){

	// Reset register bits
	GPIOA->AFR[0] &= ~((15u << (4*4))  	// Clear AFRL4
					  |(15u << (4*5))		// Clear AFRL5
					  |(15u << (4*6))		// Clear AFRL6
					  |(15u << (4*7))		// Clear AFRL7
					  );

	// Set register bits
	GPIOA->AFR[0] &= ~((5u << (4*4))  	// Set AFRL4
					  |(5u << (4*5))		// Set AFRL5
					  |(5u << (4*6))		// Set AFRL6
					  |(55u << (4*7))		// Set AFRL7
					  );
}

// Configuring SPI_CR! register
void configSPI(void){

	// Configure SPI1_CR1
	// Clear register bits
	SPI1->CR1 &= ~((1u << 15)			// Full Duplex Mode
				  |(1u << 13)			// Disable CRC
				  |(1u << 11)			// Clearing date frame size
				  |(1u << 10)			// Disabling simplex
				  |(1u << 9)			// Hardware slave management
				  |(1u << 7)			// MSB First
				  |(7u << 3)			// Reset clock divider
	              );

	// Set register bits
	SPI1->CR1 &= ~((5u << 3)			// Set clock divide to /64
				  |(1u << 11)			// Set date frame to 16 bit mode
			 	  |(1u << 2)			// Master mode
				  |(1u << 1)			// Clock polarity of 1
				  |(1u << 0)			// Clock phase of 1
				  );

	// Configure SPI_CR2
	// Clear register bits
	SPI1->CR2 &= ~((1u << 7)			// Disable interrupt
				  |(1u << 4)			// SPI in motorola mode
				  |(3u << 0)			// Disable DMA functionality
			);


}

// Helper function to config SPI
void initSPI(void){

	initClocks();
	setPinMode();
	setAF();
	configSPI();
}

// Function to handle sending and receiving data
uint8_t transferSPI(uint8_t tx_data){
	uint8_t rx_data = 0;

	// Enable SPI
	SPI1->CR1 |= (1u << 6);

	// Write data and dummy byte into data register
	SPI1->DR = (uint16_t)(tx_data << 8);

	// Wait until SPI not busy and RX buffer not empty
	while( ((SPI1->SR)&(1u << 7))||(!((SPI1->SR)&(1u << 0)))) ;

	// Read a byte from the RX buffer
	rx_data = (uint8_t)SPI1->DR;

	// Disable SPI
	SPI1->CR1 |= ~(1u << 6);

	return rx_data;

}

