#include "Navigator.hpp"

// Constructor
Navigator::Navigator(IMotorController& motorCtrl, IDistanceSensor& front, IDistanceSensor& side, PIDController& pid, 
                     IStorage& storage, int frontThreshold, int sideThreshold, bool followLeftWall)
    : motorController(motorCtrl), frontSensor(front), sideSensor(side), pid(pid), storage(storage),
      distanceThreshold(storage.Read(RobotConfigurationSettings::MinimumDistanceThreshold)),
      sideDistanceThreshold(sideDistanceThreshold),
      followLeftWall(followLeftWall) {
}

// Navigate based on hand-on-wall algorithm
void Navigator::navigate() {
    int frontDistance = frontSensor.GetDistance();
    int sideDistance = sideSensor.GetDistance();

    if (frontDistance < distanceThreshold) {
        // Obstacle in front: Turn away from the wall
        if (followLeftWall) {
            motorController.Stop();
            motorController.TurnRight();
        } else {
            motorController.Stop();
            motorController.TurnLeft();
        }
    } else if (sideDistance > sideDistanceThreshold) {
        // Wall too far away: Turn toward the wall
        if (followLeftWall) {
            motorController.Stop();
            motorController.TurnLeft();
        } else {
            motorController.Stop();
            motorController.TurnRight();
        }
    } else if(frontDistance == distanceThreshold & sideDistance == sideDistanceThreshold)
    {
        motorController.MoveBackward();
    }
    else
    {
        motorController.MoveForward(pid.Calculate(frontDistance, frontSensor.GetDistance()));
    }
    
}

// Set front distance threshold
void Navigator::setDistanceThreshold(int threshold) {
    distanceThreshold = threshold;
}

// Get front distance threshold
int Navigator::getDistanceThreshold() const {
    return distanceThreshold;
}

// Set side distance threshold
void Navigator::setSideDistanceThreshold(int threshold) {
    sideDistanceThreshold = threshold;
}

// Get side distance threshold
int Navigator::getSideDistanceThreshold() const {
    return sideDistanceThreshold;
}

// Set wall-following direction
void Navigator::setFollowLeftWall(bool followLeft) {
    followLeftWall = followLeft;
}

// Get wall-following direction
bool Navigator::isFollowingLeftWall() const {
    return followLeftWall;
}
