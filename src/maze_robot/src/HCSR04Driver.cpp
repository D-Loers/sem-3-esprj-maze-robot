#include "HCSR04Driver.hpp"

/* Constructor */

HCSR04::HCSR04(TIM_TypeDef *tTimer, GPIO_TypeDef *tPort, const int tPin, const AlternateFunctions tAF, TIM_TypeDef *eTimer, GPIO_TypeDef *ePort, const int ePin, const AlternateFunctions eAF)
    : triggerTimer(tTimer), triggerPort(tPort), triggerPin(tPin), triggerPinAlternateFunction(tAF), echoTimer(eTimer), echoPort(ePort), echoPin(ePin), echoPinAlternateFunction(eAF) {

    // Trigger pin configuration
    EnablePort(tPort);
    ConfigureGPIO(tPort, tPin, tAF);
    EnableTimer(tTimer);
    ConfigureOutputTimer(tTimer);

    // Echo pin configuration
    EnablePort(ePort);
    ConfigureGPIO(ePort, ePin, eAF);
    EnableTimer(eTimer);
    ConfigureInputTimer(eTimer);
}

/* Public methods */

int HCSR04::GetDistance(void) {
    return (this->echoTimer->CCR2 / 58);
}

/* Private methods */

void HCSR04::EnableTimer(TIM_TypeDef *timer) {
    if (timer == TIM1) {
        RCC->APB2ENR |= RCC_APB2ENR_TIM1EN_Msk;
    } else if(timer == TIM2) {
        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN_Msk;
    } else if(timer == TIM3) {
        RCC->APB1ENR |= RCC_APB1ENR_TIM3EN_Msk;
    } else if(timer == TIM4) {
        RCC->APB1ENR |= RCC_APB1ENR_TIM4EN_Msk;
    } else if(timer == TIM8) {
        RCC->APB2ENR |= RCC_APB2ENR_TIM8EN_Msk;
    } else if(timer == TIM15) {
        RCC->APB2ENR |= RCC_APB2ENR_TIM15EN_Msk;
    } else if(timer == TIM16) {
        RCC->APB2ENR |= RCC_APB2ENR_TIM16EN_Msk;
    } else if(timer == TIM17) {
        RCC->APB2ENR |= RCC_APB2ENR_TIM17EN_Msk;
    } else if(timer == TIM20) {
        RCC->APB2ENR |= RCC_APB2ENR_TIM20EN_Msk;
    } else {
        throw std::invalid_argument("Invalid timer given.");
    }
}

void HCSR04::EnablePort(GPIO_TypeDef *port) {
    if (port == GPIOA) {
        RCC->AHBENR |= RCC_AHBENR_GPIOAEN_Msk;
    } else if (port == GPIOB) {
        RCC->AHBENR |= RCC_AHBENR_GPIOBEN_Msk;
    } else if (port == GPIOC) {
        RCC->AHBENR |= RCC_AHBENR_GPIOCEN_Msk;
    } else if (port == GPIOF) {
        RCC->AHBENR |= RCC_AHBENR_GPIOFEN_Msk;
    } else {
        throw std::invalid_argument("Invalid port given.");
    }
}

void HCSR04::ConfigureOutputTimer(TIM_TypeDef *timer) {
    if (timer != TIM6 && timer != TIM7) { 
        timer->PSC = _CONFIGURES_TIMER_PRESCALER_TO_1MHZ;
        timer->CCER |= _BITMASK_CONFIGURES_CCER_CC1E_TO_ENABLE_OUTPUT;

        if (timer != TIM2 && timer != TIM3 && timer != TIM4) {
            timer->BDTR |= _BITMASK_CONFIGURES_BDTR_MOE_TO_ENABLE_OUTPUT;
        }

        timer->CCMR1 |= _BITMASK_CONFIGURES_CHANNEL_1_TO_PWM_MODE_1; 
        timer->CCR1 = this->valueToSetDutyCycleTo10us;
        timer->CR1 |= _BITMASK_ENABLES_TIMER_COUNTER;
    } else {
        throw std::invalid_argument("Invalid timer given.");
    }
}

void HCSR04::ConfigureInputTimer(TIM_TypeDef *timer) {
    if (timer != TIM6 && timer != TIM7) {
        timer->PSC = _CONFIGURES_TIMER_PRESCALER_TO_1MHZ;
        timer->CCMR1 |= _BITMASK_CONFIGURES_CCMR1_CC1S_AS_INPUT_WITH_IC1_MAPPED_ON_TI2;
        timer->CCER &= _BITMASK_CONFIGURES_CCER_CC1P_TO_TRIGGER_ON_RISING_EDGE;
        timer->CCER &= _BITMASK_CONFIGURES_CCER_CC1NP_IN_CONJUCTION_WITH_CC1P;
        timer->CCER |= _BITMASK_ENABLES_INPUT_CAPTURE_ON_CHANNEL_1;

        timer->CCMR1 |= _BITMASK_CONFIGURES_CCMR1_CC2S_AS_INPUT_WITH_IC2_MAPPED_ON_TI1;
        timer->CCER &= _BITMASK_CONFIGURES_CCER_CC2NP_IN_CONJUCTION_WITH_CC2P;
        timer->CCER |= _BITMASK_CONFIGURES_CCER_CC2P_TO_TRIGGER_ON_FALLING_EDGE;
        timer->CCER |= _BITMASK_CONFIGURES_CCER_CC2E_TO_ENABLES_INPUT_CAPTURE_ON_CHANNEL_2;
        timer->SMCR |= _BITMASK_CONFIGURES_SMCR_TS_TO_ENABLES_FILTERED_INPUT;
        timer->SMCR |= _BITMASK_CONFIGURES_SMCR_SMS_TO_ENABLES_RESET_MODE;

        timer->CR1 |= _BITMASK_ENABLES_TIMER_COUNTER;
    } else {
        throw std::invalid_argument("Invalid timer given.");
    }
}

void HCSR04::ConfigureGPIO(GPIO_TypeDef *port, const int pin, const AlternateFunctions alternateFunction) {
    port->MODER |= this->bitmaskAlternateFunctionMode << pin * 2;

    if (pin < 8) {
        port->AFR[0] |= (uint8_t)alternateFunction << ((pin % 8) * 4);
    } else {
        port->AFR[1] |= (uint8_t)alternateFunction << ((pin % 8) * 4);
    }
}