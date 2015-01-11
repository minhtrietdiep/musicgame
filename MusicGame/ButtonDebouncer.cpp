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

	if (inputmode == INPUT_PULLUP)
	{
		StatePressed = LOW;
		StateReleased = HIGH;
	}
	else
	{
		StatePressed = HIGH;
		StateReleased = LOW;
	}
}

void ButtonDebouncer::GetButtonState(void)
{
	JustReleased = false;
	JustPressed = false;

	if ((lastTime + DEBOUNCE_TIME) > millis())
	{
		return;
	}

	lastTime = millis();

	currentState = digitalRead(Button);

	if (currentState == previousState)
	{
		if (!IsPressed &&
			currentState == StatePressed)
		{
			JustPressed = true;
		}
		else if (IsPressed &&
			     currentState == StateReleased)
		{
			JustReleased = true;
		}

		IsPressed = !currentState;
	}
	previousState = currentState;
}
