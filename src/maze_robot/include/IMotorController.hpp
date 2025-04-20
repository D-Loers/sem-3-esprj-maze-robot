#pragma once

class IMotorController
{
public:
    virtual void TurnRight();
    virtual void TurnLeft();
    virtual void MoveForward(int pidOutput);
    virtual void MoveBackward(void);
    virtual void Stop(void);
    virtual void Calibrate(void);

private:

};
