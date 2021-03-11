#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <cmath>

constexpr double pi = 3.1415926;

namespace ngr // North Gwinnett Robotics
{
    [[nodiscard]] constexpr bool value_in_range(double value, double min, double max)
    {
        return value > min && value < max;
    }
    static_assert(value_in_range(1, 0, 2) == true);
    static_assert(value_in_range(0, 0, 1) == false);
    static_assert(value_in_range(1, 0, 1) == false);
    static_assert(value_in_range(2, 0, 1) == false);
    static_assert(value_in_range(-1, 0, 1) == false);

    // it compiled fine with std::fabs this, but this got rid of red squigles
    [[nodiscard]] constexpr static double fabs(double value)
    {
        if(value < 0)
            return -value;
        else
            return value;
    }
    static_assert(fabs(1) == 1);
    static_assert(fabs(-1) == 1);
    static_assert(fabs(0) == 0);

    // floating point comparison at compile time
    [[nodiscard]] constexpr static bool is_close_to(double value,
                                                    double target,
                                                    double tol = 0.00001)
    {
        return fabs(value - target) < tol;
    }
    static_assert(is_close_to(.5, .500000001) == true);
    static_assert(is_close_to(.1, .999989) == false);
    static_assert(is_close_to(.1, .10002) == false);

    [[nodiscard]] constexpr static double scaleOutput(double inputMin, double inputMax, double outputMin, double outputMax, double input)
    {
        return ((input - inputMin) / (inputMax - inputMin)) * ((outputMax - outputMin)) + outputMin;
    }
    static_assert(is_close_to(scaleOutput(0, 1, -1, 1, 0), -1));
    static_assert(is_close_to(scaleOutput(0, 1, -1, 1, 1), 1));
    static_assert(is_close_to(scaleOutput(0, 1, -1, 1, .5), 0));

    [[nodiscard]] constexpr static double deg2rad(double deg)
    {
        return deg * pi / 180;
    }
    static_assert(is_close_to(deg2rad(360), 2 * pi));
    static_assert(is_close_to(deg2rad(0), 0));

    [[nodiscard]] constexpr static double rad2deg(double rad)
    {
        return rad * 180 / pi;
    }
    static_assert(is_close_to(rad2deg(pi), 180));
    static_assert(is_close_to(rad2deg(0), 0));

} // namespace ngr

namespace CONSTANTS
{
    namespace WHEELS
    {
        struct WheelInfo
        {
            // stored in radians and inches
            int driver, turner;
            double alpha, beta, l, radius;

            // inputs in degrees and inches
            constexpr WheelInfo(int d, int t, double a_d, double b_d, double l_in, double d_in)
                : driver { d }
                , turner { t }
                , alpha { ngr::deg2rad(a_d) }
                , beta { ngr::deg2rad(b_d) }
                , l { l_in }
                , radius { d_in / 2 }
            { }
        };
        constexpr WheelInfo WHEEL_1 { 1, 5, 45, -45, 16, 2 };
        constexpr WheelInfo WHEEL_2 { 2, 6, 135, -135, 16, 2 };
        constexpr WheelInfo WHEEL_3 { 3, 7, -135, 135, 16, 2 };
        constexpr WheelInfo WHEEL_4 { 4, 8, -45, 45, 16, 2 };
    } // namespace WHEELS
} // namespace CONSTANTS

#endif // __CONSTANTS_H__