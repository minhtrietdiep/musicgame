#include "ButtonDebouncer.h"
#include <Arduino.h>

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
	IsButtonPressed = false;
	pinMode(button, inputmode);
}

boolean ButtonDebouncer::GetButtonState()
{
	if ((lastTime + DEBOUNCE_TIME) > millis())
	{
		return;
	}

	currentState = digitalRead(Button);

	if (currentState == previousState)
	{
		IsButtonPressed = !currentState;
	}
	previousState = currentState;
	lastTime = millis();
}

ButtonDebouncer::~ButtonDebouncer()
{
	// nothing to do here
}
