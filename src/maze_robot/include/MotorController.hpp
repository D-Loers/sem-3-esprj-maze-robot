#pragma once
#include "IMotorController.hpp"
#include "IServoMotorDriver.hpp"
#include "MotorSide.hpp"
#include "Utils.hpp"

class MotorController: public IMotorController
{
public:
    /// @brief Constructor of the MotorController.
    /// @param rightMotor Object for the right motor.
    /// @param leftMotor Object for the left motor.
    MotorController(IServoMotorDriver&, IServoMotorDriver&, Utils &utils);

    /// @brief Turns the robot to the right.
    void TurnRight() override;

    /// @brief Turns the robot to the left.
    void TurnLeft() override;

    /// @brief Moves the robot forward.
    void MoveForward(int pidOutput) override;

    /// @brief Moves the robot backward.
    void MoveBackward() override;

    /// @brief Stops the robot.d
    void Stop() override;

    /// @brief Calibrates the robot so that the default value for the angular position is overwritten.
    void Calibrate() override;
private:
    IServoMotorDriver& rightMotor;
    IServoMotorDriver& leftMotor;
    Utils& utils;
};
