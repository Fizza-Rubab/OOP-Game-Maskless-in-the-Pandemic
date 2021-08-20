#include <iostream>
#include "timer.hpp"

using namespace std;

Timer::Timer()
{
    timeLimit = 0;
    timerStart = 0;
}

Timer::Timer(int time)
{
    timeLimit = time;
    timerStart = 0;
}

//starting level timer
void Timer::startTimer()
{
    timerStart = SDL_GetTicks();
}

//stopping level timer
void Timer::stopTimer()
{
    timerStart = 0;
}

//to decide whether the timer and the level should stop if the time limit has passed
bool Timer::shouldStop(Uint32 passedTime)
{
    if(passedTime>=timeLimit-500 && passedTime<=timeLimit+500)
        return true;
    return false;
}

//get current time
Uint32 Timer::getTime()
{
    return SDL_GetTicks() - timerStart;
}

Timer::~Timer()
{
    //delete this;    
}


