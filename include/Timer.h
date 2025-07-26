/**
 * @file Timer.h
 * @brief Portable Timer driver header for ARM Cortex-M / Qualcomm platforms
 * @author Your Name
 */
#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/**
 * @brief Initialize Timer peripheral
 */
void Timer_Init(void);

/**
 * @brief Delay for ms milliseconds
 * @param ms Milliseconds to delay
 */
void Timer_DelayMs(uint32_t ms);

#endif // TIMER_H
