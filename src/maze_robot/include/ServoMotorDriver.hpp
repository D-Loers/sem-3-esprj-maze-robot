#pragma once
#include "IServoMotorDriver.hpp"
#ifdef STM32
#include "stm32f303xe.h"
#endif
#include <stdio.h>
#include <string.h>

enum class Motor{
RIGHT_MOTOR,
LEFT_MOTOR,
};

class ServoMotorDriver: public IServoMotorDriver
{
public:
    ServoMotorDriver(Motor);

    void Move(int) override;
private:
    void ConfigureServoMotorFeedbackPin();
    void ConfigureServoMotorControlPin();
    void ConfigureAlternateFunctionsRightMotor();
    void ConfigureAlternateFunctionsLeftMotor();
};
