#include "Utils.hpp"

int Utils::abs(int value)
{
    return (value < 0) ? -value : value;
}

int Utils::map(int x, int in_min, int in_max, int out_min, int out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int Utils::constrain(int value, int min, int max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}