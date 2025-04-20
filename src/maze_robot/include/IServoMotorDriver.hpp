#pragma once

#define FULL_CIRCLE_UNITS 360

class IServoMotorDriver
{
public:
    virtual void Move(int CCR);
    virtual void Stop();
    virtual void SetTargetAngle(int targetAngle, int direction);
    virtual int GetAngularPosition();

private:
};
