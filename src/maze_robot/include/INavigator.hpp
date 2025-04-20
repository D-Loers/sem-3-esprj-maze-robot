#pragma once

class INavigator {
public:
    virtual ~INavigator() = default;
    virtual void navigate() = 0;
};
