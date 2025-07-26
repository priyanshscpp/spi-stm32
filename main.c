
#include<stm32f4xx.h>
#include<SPI.h>
#include<Timer.h>

int main (void){

	// MPU 9250 is used to validate driver

	// MPU9250 Address
	uint8_t data[4] = {184,188,189,190};

	// Storing received data
	uint8_t rxd = 0;

	// Initiate timer
	initTim2();

	// Set up SPI
	initSPI();

	while(1){

		// Write to SPI
		rxd = transferSPI(data[0]);

		// Delay in ms
		delay(50);
	}

}

