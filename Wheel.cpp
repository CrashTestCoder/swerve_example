#include "Wheel.hpp"

Wheel::polar_velocity Wheel::get_vector_for(Twist_R const &twist)
{
    // get angle
    auto const itl = 1i * l * twist.dtheta;

    auto const top    = itl + (twist.dx + 1i * twist.dy) * ieia;
    auto const bottom = itl + (-twist.dx + 1i * twist.dy) * eia;

    double const angle = std::real(-1i * log(top / bottom)) / 2 + beta;

    // get velocity
    double const velocity = (twist.dx * std::sin(alpha + angle) + twist.dy * std::cos(alpha + angle) + l * twist.dtheta * std::cos(angle)) / radius;

    return { velocity, angle };
}

Wheel::float_t Wheel::get_angle()
{
    return pi / 2; // return turner encoder converted to radians
}

Wheel::polar_velocity Wheel::check_alternate_direction(Wheel::polar_velocity const &dir)
{
    auto alt = dir.direction;
    if(alt < 0)
        alt += pi;
    else
        alt -= pi;

    auto const angle = get_angle();
    if((alt - angle) < (dir.direction - angle))
        return { -dir.speed, alt };
    else
        return dir;
}

void Wheel::drive(Twist_R const &twist)
{
    auto const vect = check_alternate_direction(get_vector_for(twist));
    driver.SetVelocity(vect.speed);
    turner.SetPosition(vect.direction);
}
