#ifndef __WHEEL_H__
#define __WHEEL_H__

#include "Constants.hpp"
#include <complex>
#include "Twist.hpp"
#include <iostream>

class Falcon // Standin for proper library
{
    int channel;

public:
    Falcon([[maybe_unused]] int can_channel)
        : channel { can_channel }
    {
        // std::cerr << "setup falcon on channel " << can_channel << '\n';
    }
    void SetPosition([[maybe_unused]] double val)
    {
        // std::cerr << "falcon on channel " << channel << "set to position " << val << '\n';
    }
    void SetVelocity([[maybe_unused]] double val)
    {
        // std::cerr << "falcon on channel " << channel << "set to velocity " << val << '\n';
    }
    void setupPID([[maybe_unused]] double P, [[maybe_unused]] double I, [[maybe_unused]] double D);
};

using namespace std::complex_literals; // makes '1i' work

class Wheel
{
    using float_t = double;
    Falcon driver, turner;

    float_t const alpha, beta, l, radius;

    // helper values
    std::complex<float_t> const eia  = std::exp(1i * alpha);
    std::complex<float_t> const ieia = 1.0 / eia;

    struct polar_velocity
    {
        float_t speed;
        float_t direction;
    };
    polar_velocity get_vector_for(Twist_R const &twist);
    polar_velocity check_alternate_direction(polar_velocity const &angle);

public:
    Wheel(CONSTANTS::WHEELS::WheelInfo const &wheel_info)
        : driver { wheel_info.driver }
        , turner { wheel_info.turner }
        , alpha { wheel_info.alpha }
        , beta { wheel_info.beta }
        , l { wheel_info.l }
        , radius { wheel_info.radius }
    { }
    Wheel(int drive_can_channel, int turn_can_channel, float_t a, float_t b, float_t l_, float_t r)
        : driver { drive_can_channel }
        , turner { turn_can_channel }
        , alpha { a }
        , beta { b }
        , l { l_ }
        , radius { r }
    { }

    float_t get_angle();
    void drive(Twist_R const &twist);
};
#endif // __WHEEL_H__