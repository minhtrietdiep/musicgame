#ifndef Utilities_h
#define Utilities_h
#include <Arduino.h>

inline int GetIndex(char *input, char character)
{
	const char *indexptr = strchr(input, character);
	if (indexptr)
	{
		return indexptr - input;
	}
	else
	{
		return -1;
	}
}

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