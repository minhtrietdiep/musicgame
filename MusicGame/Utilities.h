#ifndef Utilities_h
#define Utilities_h
#include <Arduino.h>

inline int GetIndex(char *input, char character)
{
	for (int i = 0; i < strlen(input) - 1; i++)
	{
		if (input[i] == character)
		{
			return i;
		}
	}
	return -1;
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