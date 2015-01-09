#include "Slider.h"


Slider::Slider()
{
	Slider(A0);
}

Slider::Slider(byte pin)
{
	Pin = pin;
	Mapped = false;
}

void Slider::Map(long fromLow, long fromHigh, long toLow, long toHigh)
{
	Mapped = true;
	FromLow = fromLow;
	FromHigh = fromHigh;
	ToLow = toLow;
	ToHigh = toHigh;
}

void Slider::Unmap()
{
	Mapped = false;
}

int Slider::GetValue()
{
	if (Mapped)
	{
		int value = analogRead(Pin);
		return map(value, FromLow, FromHigh, ToLow, ToHigh);
	}

	return analogRead(Pin);
}

Slider::~Slider()
{
}
