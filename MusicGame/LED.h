#ifndef LED_h
#define LED_h
#include <Arduino.h>

class LED
{
private:
	byte Pin;
public:
	boolean IsOn;
	LED();
	LED(byte pin);
	~LED();
	void On(void);
	void Off(void);
	void Fade(int amount, int pause);
};

#endif

