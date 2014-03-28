#include "Timer.h"

namespace Train2Game
{

	Timer::Timer()
	{
		//What's the frequency of our system timer?
		QueryPerformanceFrequency(&frequency);

		//t1 is our last updated time
		QueryPerformanceCounter(&t1);

		//store this as our start time, too.
		start = t1;

		//Zero our delta time too, just in case
		timeDelta = 0;
	}
	double Timer::Update()
	{
		//Lets get the current time
		LARGE_INTEGER t2;
		QueryPerformanceCounter(&t2);

		//Calculate the delta (time since last update)
		timeDelta = t2.QuadPart-t1.QuadPart;

		//Store the new time
		t1 = t2;

		//Convert the value into seconds
		return ((double)timeDelta * 1000.0 / (double)frequency.QuadPart) / 1000.0;
	}
	double Timer::LastDelta()
	{
		//Convert the last delta into seconds and return
		return ((double)timeDelta * 1000.0 / (double)frequency.QuadPart) / 1000.0;
	}
	double Timer::Total()
	{
		//Get the current time
		LARGE_INTEGER t2;
		QueryPerformanceCounter(&t2);

		//Calculate the total time since start 
		long long total = t2.QuadPart - start.QuadPart;

		//Convert it into seconds and return
		return ((double)total * 1000.0 / (double)frequency.QuadPart) / 1000.0;
	}
}