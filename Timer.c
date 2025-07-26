#include<stm32f401xc.h>
#include<stm32f4xx.h>
#include<Timer.h>


// Initiates general purpose timer 2
void intiTim2(void){

	// Enable TIM2 clock
	RCC->APB1ENR |= (1u << 0);

	// Set Pre-scaler value to 0
	TIM2->PSC = 0;

	// Set timer reload value
	//Default internal clk (HSI) runs at 16MHz
	// Setting auto reload register to reset every second
	TIM2->ARR = (uint32_t)16000000;

	// Set initial timer value
	TIM2->CNT = 0;

	// Enable timer 2
	TIM2->CR1 |= (1u << 0);

}

// Function creates a delay of about 1 second
void delay1sec(void){

	// Holds the count of TM2_CNT to record time elapsed
	unsigned int counter = 0;

	// Holds the count of the counter to equal 1 second
	// STM32f401CCU6 HSI has a frequency of 16MHz
	// Hence the value is 16000000
	unsigned int goalCount = 16000000;

	// Holds the recent value of TIM2_CNT
	unsigned int currentCount = 0;

	// Holds previous value of TIM2_CNT
	unsigned int prevCount = 0;

	// Holds result of remaining steps to 1 second
	unsigned int countLeft = 0;

	// Getting initial value of TIM2_CNT
	prevCount = TIM2->CNT;

	// Holds untilt the timer exceeds goal
	while(counter < goalCount){

		// Get newest value of TIM2_CNT
		currentCount = TIM2->CNT;

		// Handling reset situation
		if(currentCount < prevCount){

			// Get the last count before reset and
			// add it to count after reset
			countLeft = (16000000 - prevCount) + currentCount;
		} else {

			// Subtract current count from previous to
			// get remaining count
			countLeft = currentCount - prevCount;
		}

		// Add elapsed count to counter
		counter += countLeft;

		// Updating prevCount
		prevCount = currentCount;

	}

}

// Provides delay based on user input in ms
void delay(unsigned int ms){

	// Holds the count of TM2_CNT to record time elapsed
	unsigned int counter = 0;

	// Provides target count as a function of input and HSI scaler (16MHz)
	unsigned int goalCount = ms * 16000u;

	// Holds the recent value of TIM2_CNT
	unsigned int currentCount = 0;

	// Holds previous value of TIM2_CNT
	unsigned int prevCount = 0;

	// Holds result of remaining steps to 1 second
	unsigned int countLeft = 0;

	// Getting initial value of TIM2_CNT
	prevCount = TIM2->CNT;

	// Holds untilt the timer exceeds goal
	while(counter < goalCount){

		// Get newest value of TIM2_CNT
		currentCount = TIM2->CNT;

		// Handling reset situation
		if(currentCount < prevCount){

			// Get the last count before reset and
			// add it to count after reset
			countLeft = (16000000 - prevCount) + currentCount;
		} else {

			// Subtract current count from previous to
			// get remaining count
			countLeft = currentCount - prevCount;
		}

		// Add elapsed count to counter
		counter += countLeft;

		// Updating prevCount
		prevCount = currentCount;

	}

}

// Provides delay based on user input in us (microseconds)
void delayUS(unsigned int us){


	// Holds the count of TM2_CNT to record time elapsed
	unsigned int counter = 0;

	// Provides target count as a function of input and HSI scaler (16MHz)
	unsigned int goalCount = us * 16u;

	// Holds the recent value of TIM2_CNT
	unsigned int currentCount = 0;

	// Holds previous value of TIM2_CNT
	unsigned int prevCount = 0;

	// Holds result of remaining steps to 1 second
	unsigned int countLeft = 0;

	// Getting initial value of TIM2_CNT
	prevCount = TIM2->CNT;

	// Holds untilt the timer exceeds goal
	while(counter < goalCount){

		// Get newest value of TIM2_CNT
		currentCount = TIM2->CNT;

		// Handling reset situation
		if(currentCount < prevCount){

			// Get the last count before reset and
			// add it to count after reset
			countLeft = (16000000 - prevCount) + currentCount;
		} else {

			// Subtract current count from previous to
			// get remaining count
			countLeft = currentCount - prevCount;
		}

		// Add elapsed count to counter
		counter += countLeft;

		// Updating prevCount
		prevCount = currentCount;

	}
}
