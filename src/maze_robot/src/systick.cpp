#include "systick.hpp"

void SysTick_Init(void)
{
    _runningTimeInMilliSeconds = 0;
    
    NVIC_EnableIRQ(SysTick_IRQn);  
    NVIC_SetPriority(SysTick_IRQn, 0b01); 

    SysTick->LOAD = (SystemCoreClock / SINGLE_KHZ);
    SysTick->VAL = 0b0;
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; 
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  
}

uint64_t Millis(void)
{
    return _runningTimeInMilliSeconds;
}

void Delay(int duration)
{
    uint64_t passedTime = Millis();

    while (Millis() - passedTime <= (unsigned)duration)
    {
    }
}

extern "C" void SysTick_Handler(void)
{
    _runningTimeInMilliSeconds++;
}