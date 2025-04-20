#pragma once

#include "stm32f303xe.h"
#include <stdio.h>

#define SINGLE_KHZ 1000

static volatile uint64_t _runningTimeInMilliSeconds;

void SysTick_Init(void);
uint64_t Millis(void);
void Delay(int duration);
