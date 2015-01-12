#include "SerialCommunicator.h"
#include "Utilities.h"

SerialCommunicator::SerialCommunicator()
{
}

SerialCommunicator::SerialCommunicator(Stream &serial)
{
	SerialCom = &serial;
	MemoryLastTime = millis();
}

void SerialCommunicator::AddToQueue(char *message)
{
	strcat(Queue, message);
	NewQueue = true;
}

void SerialCommunicator::BuildMessage(char *output, int outputsize, char *command, char *data)
{
	int size = strlen(command) + strlen(data) + 3;
	if (size < outputsize)
	{
		return;
	}

	output[0] = StartChar;
	output[1] = '\0';

	strcat(output, command);	
	strcat(output, data);

	char end[] = { TermChar, '\0' };
	strcat(output, end);
}

void SerialCommunicator::Receive(void)
{
	while (SerialCom->available())
	{
		size_t bytesAvailable = min(SerialCom->available(), MAX_BUFFER_SIZE);
		SerialCom->readBytes(Buffer, bytesAvailable);
	}
}

void SerialCommunicator::Send(void)
{
	if (NewQueue)
	{
		Serial.print(Queue);

		for (int i = 0; i < strlen(Queue); i++)
		{
			Queue[i] = NULL;
		}
		NewQueue = false;
	}
}

Command SerialCommunicator::Parse(void)
{
	char command[4];
	for (int i = 0; i < 4; i++)
	{
		command[i] = Buffer[i];
	}

	for (int i = 4; i < MAX_BUFFER_SIZE; i++)
	{
		CommandData[i] = Buffer[i];
	}

	if (strcmp(command, "SLTS"))
	{
		return SelectSongCommand;
	}
	else if (strcmp(command, "CRTS"))
	{
		return CreateSongCommand;
	}
	else if (strcmp(command, "RSTC"))
	{
		return ResetCommand;
	}
	else if (strcmp(command, "STRT"))
	{
		return StartCommand;
	}
	else if (strcmp(command, "GOVR"))
	{
		return GameOverCommand;
	}
	
	return UnknownCommand;
}

void SerialCommunicator::PrintFreeMemory(int interval)
{
	if (!HasIntervalPassed(MemoryLastTime, interval))
	{
		return;
	}

	char cmd[] = "FMEM";
	char dat[5];
	snprintf(dat, 5, "%ld", freeMemory());
	char msg[11];
	BuildMessage(msg, 11, cmd, dat);

	AddToQueue(msg);
}

void SerialCommunicator::WriteButtonState(int identifier, bool status)
{
	if (identifier > 9)
	{
		return;
	}

	char cmd[5];
	strcpy(cmd, "BTN");
	char id[2];
	snprintf(id, 2, "%d", identifier);
	strcat(cmd, id);

	char dat[2];
	if (status)
	{
		dat[0] = '1';
	}
	else
	{
		dat[0] = '0';
	}
	dat[1] = '\0';

	char msg[16];
	BuildMessage(msg, 8, cmd, dat);

	AddToQueue(msg);
}
