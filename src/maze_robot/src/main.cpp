#include "stm32f303xe.h"
#include <stdio.h>
#include <string.h>
#include <systick.hpp>
#include "MotorController.hpp"
#include "ParallaxFeedback360Driver.hpp"
#include "Utils.hpp"
#include "PIDController.hpp"
#include "Navigator.hpp"
#include "HCSR04Driver.hpp"
#include "Storage.hpp"

Navigator *navigator;
MotorController *motorController;
HCSR04 *frontDistanceSensor;
HCSR04 *leftDistanceSensor;
ParallaxFeedback360Driver *rightMotor;
ParallaxFeedback360Driver *leftMotor;
PIDController *pid;
Storage *storage;

int main(void)
{

    Utils utils;
    rightMotor = new ParallaxFeedback360Driver(Motor::RIGHT_MOTOR, utils);
    leftMotor = new ParallaxFeedback360Driver(Motor::LEFT_MOTOR, utils);

    motorController = new MotorController(*rightMotor, *leftMotor, utils);

    frontDistanceSensor = new HCSR04(TIM16, GPIOB, 8, AlternateFunctions::AF1, TIM15, GPIOB, 14, AlternateFunctions::AF1);
    leftDistanceSensor = new HCSR04(TIM17, GPIOB, 9, AlternateFunctions::AF1, TIM1, GPIOA, 8, AlternateFunctions::AF2);

    motorController->Calibrate();

    while (1)
    {
        motorController->TurnRight();
    }
}
