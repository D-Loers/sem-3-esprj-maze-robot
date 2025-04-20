// #include "Navigator.hpp"
// #include "TestMotorController.hpp"
// #include "TestDistanceSensor.hpp"
// #include <iostream>
// #include <cassert>

// void testPathClear() {
//     TestMotorController motorController;
//     TestDistanceSensor frontSensor;

//     Navigator navigator(motorController, frontSensor, 10, true); // Prioritize left turns

//     // Path clear ahead
//     frontSensor.setSimulatedDistance(20); // No obstacle ahead
//     navigator.navigate();

//     assert(motorController.actions.back() == "MoveForward");
//     std::cout << "Test Passed: Path Clear -> MoveForward\n";
// }

// void testObstacleDetectedTurnLeft() {
//     TestMotorController motorController;
//     TestDistanceSensor frontSensor;

//     Navigator navigator(motorController, frontSensor, 10, true); // Prioritize left turns

//     // Obstacle detected ahead
//     frontSensor.setSimulatedDistance(5); // Obstacle ahead
//     navigator.navigate();

//     assert(motorController.actions.back() == "TurnLeft");
//     std::cout << "Test Passed: Obstacle Detected -> TurnLeft\n";
// }

// void testObstacleDetectedTurnRight() {
//     TestMotorController motorController;
//     TestDistanceSensor frontSensor;

//     Navigator navigator(motorController, frontSensor, 10, false); // Prioritize right turns

//     // Obstacle detected ahead
//     frontSensor.setSimulatedDistance(5); // Obstacle ahead
//     navigator.navigate();

//     assert(motorController.actions.back() == "TurnRight");
//     std::cout << "Test Passed: Obstacle Detected -> TurnRight\n";
// }

// int main() {
//     testPathClear();
//     testObstacleDetectedTurnLeft();
//     testObstacleDetectedTurnRight();

//     std::cout << "All tests passed!" << std::endl;
//     return 0;
// }
