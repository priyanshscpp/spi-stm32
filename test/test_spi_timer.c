/**
 * @file test_spi_timer.c
 * @brief Test suite for SPI & Timer drivers (simulation)
 * @author Priyanshu Yadav  
 */
#include <stdio.h>
#include "../include/SPI.h"
#include "../include/Timer.h"

int main(void) {
    printf("[TEST] Initializing SPI and Timer...\n");
    SPI_Init();
    Timer_Init();

    printf("[TEST] SPI transfer simulation...\n");
    uint8_t tx = 0x55;
    uint8_t rx = SPI_Transfer(tx);
    if (rx == tx) {
        printf("[PASS] SPI echo test: sent 0x%02X, received 0x%02X\n", tx, rx);
    } else {
        printf("[FAIL] SPI echo test: sent 0x%02X, received 0x%02X\n", tx, rx);
    }

    printf("[TEST] Timer delay simulation (200ms)...\n");
    Timer_DelayMs(200);
    printf("[PASS] Timer delay completed.\n");

    return 0;
}
