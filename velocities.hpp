
#include <cmath>
#include <complex>
struct polar_velocity;

struct cartesian_velocity
{
    double dx, dy;
    constexpr operator polar_velocity() const;
};

struct polar_velocity
{
    double velocity, direction;
    constexpr operator cartesian_velocity() const;
};

constexpr cartesian_velocity::operator polar_velocity() const
{
    std::complex<double> d;
}

constexpr polar_velocity::operator cartesian_velocity() const
{
}