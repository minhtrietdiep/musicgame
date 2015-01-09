#include "SerialReceiver.h"

SerialReceiver::SerialReceiver()
{
	SerialReceiver(9600);
}

SerialReceiver::SerialReceiver(int speed)
{
	Serial.begin(speed);
	Buffer = "";
	LastMessage = "";
	Receiving = false;
}

void SerialReceiver::Receive()
{
	if (Serial.available() > 0)
	{
		Receiving = true;
		Buffer += Serial.read();
	}

	if (Buffer.endsWith(";"))
	{
		Serial.write("ACK");
		LastMessage = Buffer;
		Buffer = "";
		Receiving = false;
		Serial.flush();
	}
}

SerialReceiver::~SerialReceiver()
{
}
