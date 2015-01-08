#include "ButtonDebouncer.h"

ButtonDebouncer::ButtonDebouncer()
{
	ButtonDebouncer(2, INPUT);
}

ButtonDebouncer::ButtonDebouncer(byte button, byte inputmode)
{
	Button = button;
	previousState = LOW;
	currentState = LOW;
	lastTime = 0;
	IsPressed = false;
	pinMode(button, inputmode);
}

void ButtonDebouncer::GetButtonState()
{
	if ((lastTime + DEBOUNCE_TIME) > millis())
	{
		return;
	}

	currentState = digitalRead(Button);

	if (currentState == previousState)
	{
		IsPressed = !currentState;
	}
	previousState = currentState;
	lastTime = millis();
}

ButtonDebouncer::~ButtonDebouncer()
{
	// nothing to do here
}
