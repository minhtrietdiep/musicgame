#ifndef SerialCommunicator_h
#define SerialCommunicator_h
#include <Arduino.h>

typedef enum
{
	SelectSongCommand,
	CreateSongCommand,
	ResetCommand,
	StartCommand,
	GameOverCommand,
	UnknownCommand
} Command;

class SerialCommunicator
{
private:
	String Buffer;
	void SplitString(String input, String *output, char separator);
public:
	String LastMessage;
	boolean Receiving;
	SerialCommunicator();
	~SerialCommunicator();
	SerialCommunicator(int speed);
	void Receive(void);
	Command Parse(String input, String &data);
	Command Parse(String &data);
};

#endif
