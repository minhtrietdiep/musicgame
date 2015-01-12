#ifndef SerialCommunicator_h
#define SerialCommunicator_h
#include <Arduino.h>
#include "MemoryFree.h"
#include "Utilities.h"

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
	static const int MAX_QUEUE_SIZE = 64;
	static const char StartChar = '>';
	static const char TermChar = ';';

	Stream *SerialCom;

	char Buffer[MAX_BUFFER_SIZE];
	String BufferString;
	char CommandData[MAX_BUFFER_SIZE - 4];
	char Queue[MAX_QUEUE_SIZE];
	bool NewQueue;

	long MemoryLastTime;

	void AddToQueue(char *message);
	void BuildMessage(char *output, int outputsize, char *command, char *data);
	void DissectMessage(String &input, char *command, char *data);
public:
	SerialCommunicator();
	SerialCommunicator(Stream &serial);
	void Receive(void);
	void Send(void);
	Command Parse(void);
	void PrintFreeMemory(int interval);
	void WriteButtonState(int identifier, bool status);
};

#endif
