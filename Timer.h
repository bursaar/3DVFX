#ifndef __TIMER_H__
#define __TIMER_H__

/**
 * This class handles the reading of the high performance counters
 */
class Timer
{
public:
	/**
	 * Constructor
	 */
						Timer();
	/**
	 * Destructor
	 */
						~Timer();
	/**
	 * Returns the frequency of the timer (the count per second)
	 */
	unsigned __int64	GetFrequency() const;
	/**
	 * Returns the current time
	 */
	unsigned __int64	GetTime() const;
};

#endif //__TIMER_H__
