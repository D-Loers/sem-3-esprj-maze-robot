#include "MotorController.hpp"

#define DUTY_CYCLE_CCW_MIN 767  // Counterclockwise slowest
#define DUTY_CYCLE_CCW_MAX 1277 // Counterclockwise fastest
#define DUTY_CYCLE_STOP_MAX 766 // Stop upper limit
#define DUTY_CYCLE_STOP_MIN 736 // Stop lower limit
#define DUTY_CYCLE_CW_MAX 735   // Clockwise slowest
#define DUTY_CYCLE_CW_MIN 226   // Clockwise fastest

MotorController::MotorController(IServoMotorDriver &rightMotor, IServoMotorDriver &leftMotor, Utils &utils)
    : rightMotor(rightMotor), leftMotor(leftMotor), utils(utils) {}

void MotorController::TurnRight()
{
    rightMotor.SetTargetAngle(rightMotor.GetAngularPosition() + 180, 1);
    leftMotor.SetTargetAngle(leftMotor.GetAngularPosition() + 180, 1);
}

void MotorController::TurnLeft()
{
    rightMotor.SetTargetAngle(rightMotor.GetAngularPosition() - 180, 0);
    leftMotor.SetTargetAngle(leftMotor.GetAngularPosition() - 180, 0);
}

void MotorController::MoveForward(int pidOutput)
{
    int leftMotorCCR, rightMotorCCR;

    if (pidOutput > 100)
        pidOutput = 100;
    if (pidOutput < 0)
        pidOutput = 0;

    if (pidOutput < 2)
    {
        leftMotorCCR = (DUTY_CYCLE_STOP_MAX + DUTY_CYCLE_STOP_MIN) / 2;
        rightMotorCCR = (DUTY_CYCLE_STOP_MAX + DUTY_CYCLE_STOP_MIN) / 2;
    }
    else
    {
        leftMotorCCR = utils.map(pidOutput, 0, 100, DUTY_CYCLE_CCW_MIN, DUTY_CYCLE_CCW_MAX);
        rightMotorCCR = utils.map(pidOutput, 0, 100, DUTY_CYCLE_CW_MAX, DUTY_CYCLE_CW_MIN);
    }

    rightMotor.Move(rightMotorCCR);
    leftMotor.Move(leftMotorCCR);
}

void MotorController::MoveBackward()
{
    rightMotor.Move(1277);
    leftMotor.Move(226);
}

void MotorController::Stop()
{
    rightMotor.Stop();
    leftMotor.Stop();
}

void MotorController::Calibrate()
{
    rightMotor.SetTargetAngle(180, 1);
    leftMotor.SetTargetAngle(180, 1);
}