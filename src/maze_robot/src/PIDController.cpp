#include "PIDController.hpp"

#define FULL_CIRCLE_UNITS 360
#define DUTY_CYCLE_CCW_MIN 767  // Counterclockwise slowest
#define DUTY_CYCLE_CCW_MAX 1277 // Counterclockwise fastest
#define DUTY_CYCLE_STOP_MAX 766 // Stop upper limit
#define DUTY_CYCLE_STOP_MIN 736 // Stop lower limit
#define DUTY_CYCLE_CW_MIN 735   // Clockwise slowest
#define DUTY_CYCLE_CW_MAX 226   // Clockwise fastest

#define MAXIMUM_INTEGRAL_CONTRIBUTION 0.5 * (DUTY_CYCLE_CCW_MAX - DUTY_CYCLE_CCW_MIN)

PIDController::PIDController(double dT, double kP, double kI, double kD, double max, double min)
    : dT(dT), kP(kP), kI(kI), kD(kD), integral(0), previousError(0), max(max), min(min) {}

double PIDController::Calculate(double setPoint, double feedback)
{
    double error = setPoint - feedback;

    double proportionalOut = error * kP;    

    integral += error * dT;

    double maximumIntegralValue = MAXIMUM_INTEGRAL_CONTRIBUTION / kI;

    if (integral > maximumIntegralValue)
        integral = maximumIntegralValue;
    else if (integral < -maximumIntegralValue)
        integral = -maximumIntegralValue;

    double integralOut = integral * kI;

    double derivative = (error - previousError) / dT;
    double derivativeOutput = derivative * kD;

    double output = proportionalOut + integralOut + derivativeOutput;

    if (output > max)
        output = max;
    else if (output < min)
        output = min;

    previousError = error;

    return output;
}