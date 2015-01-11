#ifndef SerialCommunicator_h
#define SerialCommunicator_h
#include <Arduino.h>
#include "MemoryFree.h"

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
	static const int MAX_BUFFER_SIZE = 16;
	Stream *SerialCom;
	char Buffer[MAX_BUFFER_SIZE];
	char CommandData[MAX_BUFFER_SIZE - 4];
	long MemoryLastTime;
public:
	SerialCommunicator();
	SerialCommunicator(Stream &serial);
	void Receive(void);
	Command Parse(void);
	void PrintFreeMemory(int interval);
};

#endif
