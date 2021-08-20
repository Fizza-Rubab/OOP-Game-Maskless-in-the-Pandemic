
#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

/**
 *  \brief This class is used for generating the timer for level 2 and for slides which specifies for how much tume an action has to be performed/
 */

class Timer
{
	Uint32 timeLimit; //for storing the time limit for each level
	Uint32 timerStart;//for storing the starting time for each timer object
    public:
	/**
	 * This is a contructor which initializes a timer with an integer limit passed as a parameter.
	 */
	Timer(int);
	/**
	 * This is a default constructor for the timer.
	 */
	Timer();
	/**
	 * This method begins teh timer and starts SDL_getTicks()
	 */
	void startTimer();
	/**
	 * This method stops the timer.
	 */
	void stopTimer();
	/**
	 * This method checks if the current time passed as a paramter is equal to the timers limit and decides if the timer should stop or not.
	 */
	bool shouldStop(Uint32);
	/**
	 * This method gets the current time.
	 */
	Uint32 getTime();
	/**
	 * This method is a destructor that is ysed to delete any dynamically allocated memory.
	 */
	~Timer();
};
