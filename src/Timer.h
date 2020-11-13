//
// Created by Games Machine on 11/13/2020.
//

#ifndef ANAGRAM_SOLVER_TIMER_H
#define ANAGRAM_SOLVER_TIMER_H


#include <chrono>

class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _start;

public:
    void Start();

    double Stop();
};

#endif //ANAGRAM_SOLVER_TIMER_H
