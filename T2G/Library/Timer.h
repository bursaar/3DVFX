#pragma once
//Ultra high accuracy timer for our game loop
#include <iostream>
#include <windows.h>  
using namespace std;

namespace Train2Game
{
	class Timer
	{
		public:
			Timer();
			double Update();
			double Total();
			double LastDelta();

		private:
			//This is the timer frequency. We use this to convert the timer value into a known time
			LARGE_INTEGER frequency; 

			//The number of "ticks" of the timer since the last update
			long long timeDelta;

			//T1 is the time at our last update
			LARGE_INTEGER t1;

			//start is the time we started
			LARGE_INTEGER start;
	};
}