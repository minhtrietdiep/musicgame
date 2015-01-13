#ifndef SerialCommunicator_h
#define SerialCommunicator_h
#include <Arduino.h>
#include "MemoryFree.h"
#include "Utilities.h"

typedef enum
{
	ProcessingMessage = 1,
	EndOfMessage = 2
} MessageState;

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
	static const int MAX_BUFFER_SIZE = 64;
	static const int MAX_QUEUE_SIZE = 64;
	static const int COMMAND_SIZE = 5;
	static const char StartChar = '>';
	static const char TermChar = ';';

	Stream *SerialCom;

	char Buffer[MAX_BUFFER_SIZE];
	char CommandBuffer[COMMAND_SIZE];
	int CommandBufferIndex;

	Command LastCommand;
	char LastCommandData[MAX_BUFFER_SIZE - COMMAND_SIZE];
	int CommandDataIndex;
	MessageState CurrentState;

	char Queue[MAX_QUEUE_SIZE];
	bool NewQueue;

	long MemoryLastTime;

	void AddToQueue(char *message);
	void BuildMessage(char *output, int outputsize, char *command, char *data);

	MessageState ToCommandBuffer(char received);

	void CommandToString(Command input, char *output);
	Command Parse(void);
public:
	SerialCommunicator();
	SerialCommunicator(Stream &serial);
	void Receive(void);
	void Send(void);

	void PrintFreeMemory(int interval);
	void WriteButtonState(int identifier, bool status);
	void RequestReset(void);
	void SendGameOver(int score);

	int GetLastCommand(void);
	bool GetLastData(char *output);
};

#endif
