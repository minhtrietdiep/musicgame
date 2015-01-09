#ifndef Slider_h
#define Slider_h
#include <Arduino.h>

class Slider
{
private:
	byte Pin;
	long FromLow;
	long FromHigh;
	long ToLow;
	long ToHigh;
	boolean Mapped;
public:
	Slider();
	~Slider();
	Slider(byte pin);
	void Map(long fromLow, long fromHigh, long toLow, long toHigh);
	void Unmap(void);
	int GetValue(void);
};

#endif


