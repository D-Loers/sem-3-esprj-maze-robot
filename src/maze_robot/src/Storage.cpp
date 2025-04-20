#include "Storage.hpp"

Storage::Storage() {}

void Storage::Write(const RobotConfigurationSettings setting, const int value) {
    this->settings[setting] = value;
}

int Storage::Read(const RobotConfigurationSettings setting) {
    return this->settings[setting];
}

int Storage::NumberOfSettings(void) {
    return this->settings.size();
}