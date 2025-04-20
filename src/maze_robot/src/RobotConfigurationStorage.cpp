#include "RobotConfigurationStorage.hpp"

/* ---------- Public methods ---------- */

void RobotConfigurationStorage::Write(const RobotConfigurationSettings setting, const int data){
    this->settings[setting] = data;
}

int RobotConfigurationStorage::Read(const RobotConfigurationSettings setting){
    return this->settings[setting];
}

int RobotConfigurationStorage::NumberOfSettings(void) {
    return this->settings.size();
}