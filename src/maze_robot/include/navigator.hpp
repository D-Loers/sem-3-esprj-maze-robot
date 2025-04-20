#pragma once
#include "INavigator.hpp"
#include "IMotorController.hpp"
#include "IDistanceSensor.hpp"
#include "PIDController.hpp"
#include "IStorage.hpp"

class Navigator : public INavigator{
private:
    IMotorController& motorController;
    IDistanceSensor& frontSensor;
    IDistanceSensor& sideSensor;
    PIDController& pid;
    IStorage& storage; // Add this as a member variable
    int distanceThreshold;
    int sideDistanceThreshold;
    bool followLeftWall;

public:
    Navigator(IMotorController& motorCtrl, IDistanceSensor& front, IDistanceSensor& side, PIDController& pid, 
              IStorage& storage, int frontThreshold = 10, int sideThreshold = 5, bool followLeftWall = true);

    void navigate() override;

    // Setters and getters
    void setDistanceThreshold(int threshold);
    int getDistanceThreshold() const;

    void setSideDistanceThreshold(int threshold);
    int getSideDistanceThreshold() const;

    void setFollowLeftWall(bool followLeft);
    bool isFollowingLeftWall() const;
};
