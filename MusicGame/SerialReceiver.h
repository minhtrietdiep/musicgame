#ifndef SerialReceiver_h
#define SerialReceiver_h
#include <Arduino.h>

class SerialReceiver
{
private:
	String Buffer;
public:
	String LastMessage;
	boolean Receiving;
	SerialReceiver();
	~SerialReceiver();
	SerialReceiver(int speed);
	void Receive(void);
};

#endif
