#pragma once

class PIDController
{
public:
    PIDController(double dT, double kP, double kI, double kD, double max, double min);
    ~PIDController() = default;

    double Calculate(double setPoint, double feedback);

private:
    double dT;
    double kP;
    double kI;
    double kD;
    double integral;
    double previousError;
    double max;
    double min;
};