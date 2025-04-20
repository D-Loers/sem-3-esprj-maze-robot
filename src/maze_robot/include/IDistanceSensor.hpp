#pragma once

class IDistanceSensor
{
public:
    virtual ~IDistanceSensor() = default;
    virtual int GetDistance(void) = 0;
};
