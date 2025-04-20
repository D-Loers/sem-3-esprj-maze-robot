#include "ParallaxFeedback360Driver.hpp"

#define DUTY_CYCLE_MIN 2.9f
#define DUTY_CYCLE_MAX 91.7f

#define DUTY_CYCLE_CCW_MIN 767  // Counterclockwise slowest
#define DUTY_CYCLE_CCW_MAX 1277 // Counterclockwise fastest
#define DUTY_CYCLE_STOP_MAX 766 // Stop upper limit
#define DUTY_CYCLE_STOP_MIN 736 // Stop lower limit
#define DUTY_CYCLE_CW_MIN 735   // Clockwise slowest
#define DUTY_CYCLE_CW_MAX 226   // Clockwise fastest

ParallaxFeedback360Driver::ParallaxFeedback360Driver(Motor motorSide, Utils &utils)
    : motorSide(motorSide), utils(utils)
{
    switch (motorSide)
    {
    case Motor::RIGHT_MOTOR:
    {
        ConfigureAlternateFunctionsRightMotor();
        break;
    }
    case Motor::LEFT_MOTOR:
    {
        ConfigureAlternateFunctionsLeftMotor();
        break;
    }
    default:
    {
        break;
    }
    }

    ConfigureServoMotorControlPin();
    ConfigureServoMotorFeedbackPin();
}

void ParallaxFeedback360Driver::Move(int CCR)
{
    switch (motorSide)
    {
    case Motor::RIGHT_MOTOR:
    {
        TIM3->CCR1 = CCR;
        break;
    }
    case Motor::LEFT_MOTOR:
    {
        TIM3->CCR2 = CCR;
        break;
    }
    default:
        break;
    }
}

void ParallaxFeedback360Driver::Stop()
{
    switch (motorSide)
    {
    case Motor::RIGHT_MOTOR:
    {
        TIM3->CCR1 = DUTY_CYCLE_STOP_MAX;
        break;
    }
    case Motor::LEFT_MOTOR:
    {
        TIM3->CCR2 = DUTY_CYCLE_STOP_MAX;
        break;
    }
    }
}

void ParallaxFeedback360Driver::SetTargetAngle(int targetAngle, int direction)
{
    int currentAngle = 0;
    int error = 0;
    int angleTolerance = 2;
    int outputDuty = 0;

    targetAngle = targetAngle % FULL_CIRCLE_UNITS;
    if (targetAngle < 0)
        targetAngle += FULL_CIRCLE_UNITS;

    while (true)
    {
        currentAngle = GetAngularPosition();

        if (direction == 1)
        {
            error = -utils.abs(targetAngle - currentAngle);
        }
        else if (direction == 0)
        {
            error = utils.abs(targetAngle - currentAngle);
        }

        if (utils.abs(error) <= angleTolerance)
        {
            Stop();
            break;
        }

        if (error > 0) // Turn clockwise
        {
            outputDuty = utils.map(utils.abs(error), 0, FULL_CIRCLE_UNITS, DUTY_CYCLE_CW_MIN, DUTY_CYCLE_CW_MAX);
            outputDuty = utils.constrain(outputDuty, DUTY_CYCLE_CW_MAX, DUTY_CYCLE_CW_MIN);
        }
        else // Turn counterclockwise
        {
            outputDuty = utils.map(utils.abs(error), 0, FULL_CIRCLE_UNITS, DUTY_CYCLE_CCW_MIN, DUTY_CYCLE_CCW_MAX);
            outputDuty = utils.constrain(outputDuty, DUTY_CYCLE_CCW_MIN, DUTY_CYCLE_CCW_MAX);
        }

        Move(outputDuty); 
    }
}

int ParallaxFeedback360Driver::GetAngularPosition()
{
    uint32_t tHigh = 0;
    uint32_t tCycle = 0;

    tHigh = TIM2->CCR2;
    tCycle = TIM2->CCR1;

    if (motorSide == Motor::RIGHT_MOTOR)
    {
        tHigh = TIM2->CCR2;
        tCycle = TIM2->CCR1;
    }
    else if (motorSide == Motor::LEFT_MOTOR)
    {
        tHigh = TIM4->CCR2;
        tCycle = TIM4->CCR1;
    }

    if (tCycle < 1000 || tCycle > 1200)
    {
        return -1;
    }

    uint32_t dutyCycle = (100 * tHigh) / tCycle;

    if (dutyCycle < DUTY_CYCLE_MIN)
        dutyCycle = DUTY_CYCLE_MIN;
    if (dutyCycle > DUTY_CYCLE_MAX)
        dutyCycle = DUTY_CYCLE_MAX;

    int angularPosition = (int)(((dutyCycle - DUTY_CYCLE_MIN) * FULL_CIRCLE_UNITS) / ((DUTY_CYCLE_MAX - DUTY_CYCLE_MIN) + 1));

    if (angularPosition < 0)
        angularPosition = 0;
    if (angularPosition >= FULL_CIRCLE_UNITS)
        angularPosition = FULL_CIRCLE_UNITS - 1;

    return angularPosition;
}

void ParallaxFeedback360Driver::ConfigureServoMotorFeedbackPin()
{
    // Step 1
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM4EN; // Enabling the timer clock

    // Step 2
    TIM2->PSC = (SystemCoreClock / 1000000) - 1; // PSC = 71 // Clock = 1 MHz
    TIM4->PSC = (SystemCoreClock / 1000000) - 1;

    // Step 3
    TIM2->CCMR1 &= ~TIM_CCMR1_CC1S;  // Clearing the CC1S bits of the CCMR1 register to configure CC1 channel as input
    TIM2->CCMR1 |= TIM_CCMR1_CC1S_0; // Setting CC1 channel as input with IC1 mapped on TI1
    TIM4->CCMR1 &= ~TIM_CCMR1_CC1S;  // Clearing the CC1S btis of the CCMR2 register to configure CC1 channel as input
    TIM4->CCMR1 |= TIM_CCMR1_CC1S_0; // Setting CC1 channel as input with IC1 mapped on TI1

    // Step 4
    TIM2->CCER &= ~TIM_CCER_CC1NP; // Clearing these bits to set them to noninverted/rising edge for channel 1
    TIM2->CCER &= ~TIM_CCER_CC1P;  // Clearing these bits to set them to noninverted/rising edge for channel 1
    TIM4->CCER &= ~TIM_CCER_CC1NP; // Clearing these bits to set them to noninverted/rising edge for channel 1
    TIM4->CCER &= ~TIM_CCER_CC1P;  // Clearing these bits to set them to noninverted/rising edge for channel 1

    // Step 5
    TIM2->CCER |= TIM_CCER_CC1E; // Setting the CC1E bit to enable Capture/Compare 1 capture
    TIM4->CCER |= TIM_CCER_CC1E; // Setting the CC3E bit to enable Capture/Compare 1 capture

    // Step 6
    TIM2->CCMR1 &= ~TIM_CCMR1_CC2S;  // Clearing the CC2S bits of the CCMR1 register to configure CC2 channel as input
    TIM2->CCMR1 |= TIM_CCMR1_CC2S_1; // Setting CC2 channel as input with IC1 mapped on TI1
    TIM4->CCMR1 &= ~TIM_CCMR1_CC2S;  // Clearing the CC4S bits of the CCMR2 register to configure CC2 channel as input
    TIM4->CCMR1 |= TIM_CCMR1_CC2S_1; // Setting CC2 channel as input with IC1 mapped on TI1

    // Step 7
    TIM2->CCER &= ~TIM_CCER_CC2NP; // Clearing the CC2NP bit to set it to inverted/falling edge
    TIM2->CCER |= TIM_CCER_CC2P;   // Setting the CC2P bit to set it to inverted/falling edge
    TIM4->CCER &= ~TIM_CCER_CC2NP; // Clearing the CC1NP bit to set it to inverted/falling edge
    TIM4->CCER |= TIM_CCER_CC2P;   // Setting the CC1P bit to set it to inverted/falling edge

    // Step 8
    TIM2->CCER |= TIM_CCER_CC2E; // Setting the CC2E bit to enable Capture/Compare 2 capture
    TIM4->CCER |= TIM_CCER_CC2E; // Setting the CC2E bit to enable Capture/Compare 2 capture

    // Step 9
    TIM2->SMCR &= ~TIM_SMCR_TS;             // Clearing the TS bits of the SMCR register to configure the trigger selection
    TIM2->SMCR |= 0b101 << TIM_SMCR_TS_Pos; // Setting the TS bits to 101 to set the trigger selection to Filtered Timer Input 1
    TIM4->SMCR &= ~TIM_SMCR_TS;             // Clearing the TS bits of the SMCR register to configure the trigger selection
    TIM4->SMCR |= 0b101 << TIM_SMCR_TS_Pos; // Setting the TS bits to 101 to set the trigger selection to Filtered Timer Input 1

    // Step 10
    TIM2->SMCR &= ~TIM_SMCR_SMS;  // Clearing the SMS bits of the SMCR register to configure the slave mode selection
    TIM2->SMCR |= TIM_SMCR_SMS_2; // Setting the third SMS bit to 1 to set the slave mode selection to reset mode
    TIM4->SMCR &= ~TIM_SMCR_SMS;  // Clearing the SMS bits of the SMCR register to configure the slave mode selection
    TIM4->SMCR |= TIM_SMCR_SMS_2; // Setting the third SMS bit to 1 to set the slave mode selection to reset mode

    // Step 11
    TIM2->CR1 |= TIM_CR1_CEN; // Enabling the timer counter
    TIM4->CR1 |= TIM_CR1_CEN; // Enabling the timer counter
}

void ParallaxFeedback360Driver::ConfigureServoMotorControlPin()
{
    // Step 1
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // Enabling the timer clock

    // Step 2
    TIM3->PSC = (SystemCoreClock / 500000) - 1; // Setting the prescaler to scale down the clock // PSC = 143 // Clock = 500000 Hz

    // Step 3
    TIM3->ARR = 10000; // Setting the auto-relaod value //

    // Step 4 and 5
    TIM3->CCMR1 &= ~TIM_CCMR1_OC1M;                     // Clearing the OC1M bits of the CCMR1 register to configure the Output/Compare 1 mode
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // Setting the second and third bit of OC1M to 1 to set the Output/Compare 1 to PWM mode 1
    TIM3->CCMR1 &= ~TIM_CCMR1_OC2M;
    TIM3->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;

    // Step 6
    TIM3->CCR1 = 0; // Setting the Capture/Compare count at 0
    TIM3->CCR2 = 0;

    // Step 7
    TIM3->CCER |= TIM_CCER_CC1E; // Setting the CC1E bit of the CCER register to enable the Capture/Compare output
    TIM3->CCER |= TIM_CCER_CC2E;

    // Step 8
    TIM3->CR1 |= TIM_CR1_CEN; // Enabling the timer counter
}

void ParallaxFeedback360Driver::ConfigureAlternateFunctionsRightMotor()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER &= ~GPIO_MODER_MODER0;  // Reset the PA0 bits
    GPIOA->MODER |= GPIO_MODER_MODER0_1; // Set the PA0 bits for alternate function
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL0);
    GPIOA->AFR[0] |= (0b0001 << GPIO_AFRL_AFRL0_Pos);

    GPIOA->MODER &= ~GPIO_MODER_MODER6;  // Reset the PA6 bits
    GPIOA->MODER |= GPIO_MODER_MODER6_1; // Set the PA6 bits for alternate function
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL6);
    GPIOA->AFR[0] |= (0b0010 << GPIO_AFRL_AFRL6_Pos);
}

void ParallaxFeedback360Driver::ConfigureAlternateFunctionsLeftMotor()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;
    GPIOB->MODER &= ~GPIO_MODER_MODER6;  // Reset the PB6 bits
    GPIOB->MODER |= GPIO_MODER_MODER6_1; // Set the PB6 bits for alternate function
    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL6);
    GPIOB->AFR[0] |= (0b0010 << GPIO_AFRL_AFRL6_Pos);

    GPIOA->MODER &= ~GPIO_MODER_MODER7;  // Reset the PA7 bits
    GPIOA->MODER |= GPIO_MODER_MODER7_1; // Set the PA7 bits for alternate function
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL7);
    GPIOA->AFR[0] |= (0b0010 << GPIO_AFRL_AFRL7_Pos);
}

// Dangerous pins : PA2, PA3, PA13, PA14, PB3