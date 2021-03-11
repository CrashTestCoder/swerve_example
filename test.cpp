#include "drivetrain.hpp"
#include <chrono>
#include <complex>
#include <iostream>

using namespace std::complex_literals;

int main()
{
    Drivetrain dt;

    auto const start = std::chrono::high_resolution_clock().now(); // timer setup

    dt.drive({ 1, 1, 1 }); // drive robot move robot 1ft/s in the x axis, 1ft/s in the y axis, while spinning at 1 radian/s

    auto const end          = std::chrono::high_resolution_clock().now();
    auto const time_elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::printf("time: %lius\n", time_elapsed.count());
}