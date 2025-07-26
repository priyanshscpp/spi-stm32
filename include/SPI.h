/**
 * @file SPI.h
 * @brief Portable SPI driver header for ARM Cortex-M / Qualcomm platforms
 * @author Your Name
 */
#ifndef SPI_H
#define SPI_H

#include <stdint.h>

/**
 * @brief Initialize SPI peripheral
 */
void SPI_Init(void);

/**
 * @brief Transfer a byte over SPI
 * @param tx_data Data to transmit
 * @return Received data
 */
uint8_t SPI_Transfer(uint8_t tx_data);

#endif // SPI_H
