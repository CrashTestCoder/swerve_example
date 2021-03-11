#ifndef __DRIVETRAIN_H__
#define __DRIVETRAIN_H__

#include "Wheel.hpp"
#include "Twist.hpp"

class Drivetrain
{
    Wheel wheels[4] = {
        { CONSTANTS::WHEELS::WHEEL_1 },
        { CONSTANTS::WHEELS::WHEEL_2 },
        { CONSTANTS::WHEELS::WHEEL_3 },
        { CONSTANTS::WHEELS::WHEEL_4 }
    };

public:
    double get_angle(); // pull from rio
    void drive(Twist_I const &twist);
};

#endif // __DRIVETRAIN_H__