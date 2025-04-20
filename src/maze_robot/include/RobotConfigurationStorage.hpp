#pragma once

#include "IStorage.hpp"
#include "RobotConfigurationSettings.hpp"
#include "map"

class RobotConfigurationStorage : public IStorage {
public:
    RobotConfigurationStorage() = default;
    ~RobotConfigurationStorage() = default;

    void Write(const RobotConfigurationSettings, const int) override;
    int Read(const RobotConfigurationSettings) override;
    int NumberOfSettings(void) override;

private:
    std::map<RobotConfigurationSettings, int> settings;
};
