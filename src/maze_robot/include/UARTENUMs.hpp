#pragma once

enum class UARTCommand {
    TurnLeft,
    TurnRight,
    MoveForward,
    MoveBackward,
    Stop,
    Invalid // For unsupported or unrecognized commands
};
