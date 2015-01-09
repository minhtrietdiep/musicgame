#include "LED.h"


LED::LED()
{
	LED(13);
}

LED::LED(byte pin)
{
	Pin = pin;
	pinMode(pin, OUTPUT);
	Off();
}

void LED::On()
{
	digitalWrite(Pin, HIGH);
	IsOn = true;
}

void LED::Off()
{
	digitalWrite(Pin, LOW);
	IsOn = false;
}

void LED::Fade(int amount, int pause)
{
	analogWrite(Pin, amount);
	delay(pause);
}

LED::~LED()
{
}
