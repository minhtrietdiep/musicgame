#ifndef ButtonDebouncer_h
#define ButtonDebouncer_h

class ButtonDebouncer
{
private:
	static const int DEBOUNCE_TIME = 10;
	byte Button;
	byte previousState;
	byte currentState;
	long lastTime;
	boolean IsButtonPressed;
public:
	ButtonDebouncer();
	~ButtonDebouncer();
	ButtonDebouncer(byte button, byte inputmode);
	boolean GetButtonState();
};

#endif