#pragma once
#include "stm32f303xe.h"

/* Misc configuration macro's */

#define _BITMASK_ENABLES_TIMER_COUNTER 0b1 << TIM_CR1_CEN_Pos
#define _CONFIGURES_TIMER_PRESCALER_TO_1MHZ (SystemCoreClock / 1000000) - 1

/* Trigger pin (PB8) configuration macro's*/

#define _BITMASK_CONFIGURES_CCER_CC1E_TO_ENABLE_OUTPUT 0b1 << TIM_CCER_CC1E_Pos
#define _BITMASK_CONFIGURES_BDTR_MOE_TO_ENABLE_OUTPUT 0b1 << TIM_BDTR_MOE_Pos
#define _BITMASK_CONFIGURES_CHANNEL_1_TO_PWM_MODE_1 TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2
#define _BITMASK_CONFIGURES_PIN_8_AS_AF_MODE 0b10 << GPIO_MODER_MODER8_Pos
#define _BITMASK_CONFIGURES_PIN_8_MODE_AS_AF1 0b0001 << GPIO_AFRH_AFRH0_Pos

/* Echo pin (PB14) configuration macro's*/
/* Channel 1 TIMER 15 configuration */

#define _BITMASK_CONFIGURES_CCMR1_CC1S_AS_INPUT_WITH_IC1_MAPPED_ON_TI2 0b01 << TIM_CCMR1_CC1S_Pos
#define _BITMASK_CONFIGURES_CCER_CC1P_TO_TRIGGER_ON_RISING_EDGE ~0b1 << TIM_CCER_CC1P_Pos
#define _BITMASK_CONFIGURES_CCER_CC1NP_IN_CONJUCTION_WITH_CC1P ~0b1 << TIM_CCER_CC1NP_Pos
#define _BITMASK_ENABLES_INPUT_CAPTURE_ON_CHANNEL_1 0b1 << TIM_CCER_CC1E_Pos

/* Channel 2 TIMER 15 configuration */

#define _BITMASK_CONFIGURES_CCMR1_CC2S_AS_INPUT_WITH_IC2_MAPPED_ON_TI1 0b10 << TIM_CCMR1_CC2S_Pos
#define _BITMASK_CONFIGURES_CCER_CC2P_TO_TRIGGER_ON_FALLING_EDGE 0b1 << TIM_CCER_CC2P_Pos
#define _BITMASK_CONFIGURES_CCER_CC2NP_IN_CONJUCTION_WITH_CC2P ~0b1 << TIM_CCER_CC2NP_Pos
#define _BITMASK_CONFIGURES_CCER_CC2E_TO_ENABLES_INPUT_CAPTURE_ON_CHANNEL_2 0b1 << TIM_CCER_CC2E_Pos
#define _BITMASK_CONFIGURES_SMCR_TS_TO_ENABLES_FILTERED_INPUT 0b101 << TIM_SMCR_TS_Pos
#define _BITMASK_CONFIGURES_SMCR_SMS_TO_ENABLES_RESET_MODE TIM_SMCR_SMS_2

#define _BITMASK_CONFIGURES_MODER_MODER14_TO_ENABLE_AF_MODE 0b10 << GPIO_MODER_MODER14_Pos
#define _BITMASK_CONFIGURES_AFRH_AFR13_TO_ENABLE_AF1 0b0001 << GPIO_AFRH_AFRH6_Pos