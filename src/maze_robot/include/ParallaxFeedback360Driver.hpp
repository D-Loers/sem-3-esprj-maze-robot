#pragma once

#include "IServoMotorDriver.hpp"
#include "MotorSide.hpp"
#include "stm32f303xe.h"
#include "Utils.hpp"

class ParallaxFeedback360Driver: public IServoMotorDriver
{
public:
    /// @brief Constructor of the ParallaxFeedback360Driver. Calls the configuration functions.
    /// @param motorSide Determines which motor the constructor is for. E.g. RIGHT_MOTOR.
    /// @param utils Class for helpful mathematical functions for the control of the motors.
    ParallaxFeedback360Driver(Motor, Utils&);

    /// @brief Sets the pulse width to the given CCR value aka the pulse width to determine the direction and the speed of the motor.
    /// @param CCR The CCR value aka the pulse width to set the motor to.
    void Move(int CCR) override;

    /// @brief Stops the motor by setting the pulse width to the appropriate value.
    void Stop() override;

    /// @brief Changes the angular position of the motor to the given target angle with turning to the given direction.
    /// @param targetAngle The angle the motor will turn to.
    /// @param direction The direction the motor is going to turn to depending on the given integer value.
    ///                  1: right
    ///                  2: left
    void SetTargetAngle(int targetAngle, int direction) override;

    /// @brief Gets the angular position of the motor at the moment with the feedback pin.
    /// @return Returns the angular position in degrees. E.g. 180, 360.
    int GetAngularPosition() override;

private:
    Motor motorSide;
    Utils& utils;

    /// @brief Configures the timers 2 and 4 for the feedback pins for both motors.
    void ConfigureServoMotorFeedbackPin();

    /// @brief Configures the timer 3 for the control pins for both motors.
    void ConfigureServoMotorControlPin();

    /// @brief Configures the alternate functions for the control and feedback pins of the right motor.
    void ConfigureAlternateFunctionsRightMotor();

    /// @brief Configures the alternate functions for the control and feedback pins of the left motor.
    void ConfigureAlternateFunctionsLeftMotor();
};