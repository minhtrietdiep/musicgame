#ifndef ButtonDebouncer_h
#define ButtonDebouncer_h
#include <Arduino.h>

class ButtonDebouncer
{
private:
	static const int DEBOUNCE_TIME = 10;

	byte StatePressed;
	byte StateReleased;
	byte Button;
	byte previousState;
	byte currentState;
	long lastTime;
public:
	bool IsPressed;
	bool JustPressed;
	bool JustReleased;

	ButtonDebouncer();
	ButtonDebouncer(byte button, byte inputmode);
	void GetButtonState(void);
};

#endif