#include "LED.h"
#include "Utilities.h"

LED::LED()
{
	// on the Arduino Uno there is a
	// LED on pin 13
	LED(13);
}

LED::LED(byte pin)
{
	Pin = pin;
	pinMode(pin, OUTPUT);
	Off();
}

void LED::On(void)
{
	digitalWrite(Pin, HIGH);
	IsOn = true;
	Brightness = 255;
}

void LED::Off(void)
{
	digitalWrite(Pin, LOW);
	IsOn = false;
	Brightness = 0;
}

void LED::Fade(int amount, int pause)
{
	if (!HasIntervalPassed(FadeLastTime, pause))
	{
		return;
	}

	if (amount > 0 &&
		(Brightness + amount) < 255)
	{
		Brightness += amount;
	}
	else if (amount < 0 &&
		     (Brightness - amount) > 0)
	{
		Brightness -= amount;
	}
	else
	{
		return;
	}

	analogWrite(Pin, Brightness);
}

void LED::IntervalToggle(int interval)
{
	if (!HasIntervalPassed(ToggleLastTime, interval))
	{
		return;
	}

	Toggle();
}

void LED::Toggle(void)
{
	Toggle(IsOn);
}

void LED::Toggle(bool state)
{
	if (!state)
	{
		On();
	}
	else
	{
		Off();
	}
}

LED::~LED()
{
}
