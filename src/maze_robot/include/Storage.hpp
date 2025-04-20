#pragma once

#include "IStorage.hpp"
#include <map>

class Storage : public IStorage
{
public:
    Storage();

    void Write(const RobotConfigurationSettings, const int) override;
    int Read(const RobotConfigurationSettings) override;
    int NumberOfSettings(void) override;

private:
    std::map<RobotConfigurationSettings, int> settings;
};