/**
 * @file main.c
 * @brief Example application for SPI & Timer drivers (Qualcomm/ARM portable)
 * @author Priyanshu Yadav
 * @note This application demonstrates basic SPI transfer and Timer delay functionality.
 *       It is intended for simulation purposes and should be replaced with actual hardware-specific code in production use.
 */
#include <stdio.h>
#include "SPI.h"
#include "Timer.h"

int main(void) {
    SPI_Init();
    Timer_Init();

    uint8_t tx_data = 0xA5;
    uint8_t rx_data = 0;

    for (int i = 0; i < 10; ++i) {
        rx_data = SPI_Transfer(tx_data);
        printf("SPI sent: 0x%02X, received: 0x%02X\n", tx_data, rx_data);
        Timer_DelayMs(100);
    }
    return 0;
}
