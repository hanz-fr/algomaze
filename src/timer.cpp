#include "../include/timer.h"
#include <chrono>

using namespace std::chrono;

steady_clock::time_point start_time;

void startTimer()
{
    start_time = steady_clock::now();
}

double stopTimer() 
{
    auto end_time = steady_clock::now();
    duration<double> elapsed = end_time - start_time;
    return elapsed.count();
}
