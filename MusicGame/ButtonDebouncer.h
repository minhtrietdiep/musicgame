#ifndef ButtonDebouncer_h
#define ButtonDebouncer_h
#include <Arduino.h>

class ButtonDebouncer
{
private:
	static const int DEBOUNCE_TIME = 10;
	byte Button;
	byte previousState;
	byte currentState;
	long lastTime;
public:
	bool IsPressed;
	ButtonDebouncer();
	~ButtonDebouncer();
	ButtonDebouncer(byte button, byte inputmode);
	void GetButtonState(void);
};

#endif