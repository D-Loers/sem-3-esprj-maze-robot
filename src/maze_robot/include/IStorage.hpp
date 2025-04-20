#pragma once

#include "RobotConfigurationSettings.hpp"

class IStorage{
public:
    virtual ~IStorage() = default;
    virtual void Write(const RobotConfigurationSettings, const int) = 0;
    virtual int Read(const RobotConfigurationSettings) = 0;
    virtual int NumberOfSettings(void) = 0;
};

