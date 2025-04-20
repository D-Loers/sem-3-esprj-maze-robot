#pragma once
#include "IDistanceSensor.hpp"
#include "HCSR04Macros.hpp"
#include "stm32f303xe.h"
#include <stdexcept>
#include <stdint.h>

enum class AlternateFunctions {
    AF0,
    AF1,
    AF2,
    AF3,
    AF4,
    AF5,
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15,
};

class HCSR04 : public IDistanceSensor {
public:
    HCSR04(TIM_TypeDef *, GPIO_TypeDef *, const int, const AlternateFunctions, TIM_TypeDef *, GPIO_TypeDef *, const int, const AlternateFunctions);
    ~HCSR04() = default;
    int GetDistance(void) override;

private:
    void EnableTimer(TIM_TypeDef *);
    void EnablePort(GPIO_TypeDef *);
    void ConfigureOutputTimer(TIM_TypeDef *);
    void ConfigureInputTimer(TIM_TypeDef *);
    void ConfigureGPIO(GPIO_TypeDef *, const int, const AlternateFunctions);

    TIM_TypeDef *triggerTimer;
    GPIO_TypeDef *triggerPort;
    const int triggerPin;
    const AlternateFunctions triggerPinAlternateFunction;
    TIM_TypeDef *echoTimer;
    GPIO_TypeDef *echoPort;
    const int echoPin;
    const AlternateFunctions echoPinAlternateFunction;

    const int valueToSetDutyCycleTo10us = 10;
    const int bitmaskAlternateFunctionMode = 0b10;
};