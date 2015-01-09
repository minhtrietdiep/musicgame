#include "LED.h"


LED::LED()
{
	LED(13);
}

LED::LED(byte pin)
{
	Pin = pin;
	pinMode(pin, OUTPUT);
	LastTime = millis();
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
	if ((LastTime + pause) < millis())
	{
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
	}

	analogWrite(Pin, Brightness);

	LastTime = millis();
}

LED::~LED()
{
}
