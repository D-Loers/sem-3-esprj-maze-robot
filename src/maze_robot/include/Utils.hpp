#pragma once

class Utils
{
public:
    int abs(int value);
    int map(int x, int in_min, int in_max, int out_min, int out_max);
    int constrain(int value, int min, int max);
};