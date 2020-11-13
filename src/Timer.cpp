//
// Created by Games Machine on 11/13/2020.
//
#include <chrono>
#include "Timer.h"

void Timer::Start()
{
    _start = std::chrono::high_resolution_clock::now();
}

double Timer::Stop()
{
    auto finish = std::chrono::high_resolution_clock::now();
    double timeTaken = std::chrono::duration_cast<std::chrono::duration<double>>(finish - _start).count();
    return timeTaken;
}