
#ifndef STM32f401CCU6
#define STM32f401CCU6
#include"stm32f401xc.h"
#include"stm32f4xx.h"
#endif

void initClocks(void);

void setPinMode(void);
void setAF(void);

void configSPI(void);
void initSPI(void);

uint8_t transferSPI(uint8_t tx_data);
