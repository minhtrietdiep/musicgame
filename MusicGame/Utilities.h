#ifndef Utilities_h
#define Utilities_h
#include <Arduino.h>

inline bool HasIntervalPassed(long &lasttime, int interval)
{
	if ((lasttime + interval) > millis())
	{
		return false;
	}

	lasttime = millis();
	return true;
}

#endif