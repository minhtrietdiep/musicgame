#include "ButtonDebouncer.h"
#include <Arduino.h>

ButtonDebouncer::ButtonDebouncer()
{
}

ButtonDebouncer::ButtonDebouncer(int *buttons)
{
	int size = sizeof(buttons) / sizeof(*buttons);

	Buttons = (int *)malloc(sizeof(int) * size);
	Buttons = buttons;
}


ButtonDebouncer::~ButtonDebouncer()
{
}
