#include "SerialCommunicator.h"
#include "Utilities.h"

SerialCommunicator::SerialCommunicator()
{
}

SerialCommunicator::SerialCommunicator(Stream &serial)
{
	SerialCom = &serial;
	MemoryLastTime = millis();
	CommandBuffer[COMMAND_SIZE] = '\0';
}

void SerialCommunicator::Receive(void)
{
	while (SerialCom->available())
	{
		size_t bytesAvailable = min(SerialCom->available(), MAX_BUFFER_SIZE);
		SerialCom->readBytes(Buffer, bytesAvailable);

		for (size_t byteNo = 0; byteNo < bytesAvailable; byteNo++)
		{
			MessageState msgState = ToCommandBuffer(Buffer[byteNo]);

			if (msgState == EndOfMessage)
			{
				LastCommand = Parse();
				char Ack[] = ">ACKN;";
				AddToQueue(Ack);
			}
		}
	}
}

MessageState SerialCommunicator::ToCommandBuffer(char received)
{
	CurrentState = ProcessingMessage;

	if (received == StartChar)
	{
		CommandBufferIndex = 0;
		for (int i = 0; i < COMMAND_SIZE - 1; i++)
		{
			CommandBuffer[i] = NULL;
		}

		CommandDataIndex = 0;
		for (int i = 0; i < (MAX_BUFFER_SIZE - COMMAND_SIZE); i++)
		{
			LastCommandData[i] = NULL;
		}
	}
	else if (received == TermChar)
	{
		CommandBuffer[CommandBufferIndex] = '\0';
		if (CommandBufferIndex > 0)
		{
			CurrentState = EndOfMessage;
		}
	}
	else if (CommandBufferIndex < 4)
	{
		CommandBuffer[CommandBufferIndex] = received;
		CommandBufferIndex++;
	}
	else
	{
		LastCommandData[CommandDataIndex] = received;
		CommandDataIndex++;
	}

	return CurrentState;
}

Command SerialCommunicator::Parse(void)
{
	Command returnCommand = UnknownCommand;

	if (strcmp(CommandBuffer, "SLTS") == 0)
	{
		returnCommand = SelectSongCommand;
	}
	else if (strcmp(CommandBuffer, "CRTS") == 0)
	{
		returnCommand = CreateSongCommand;
	}
	else if (strcmp(CommandBuffer, "RSTC") == 0)
	{
		returnCommand = ResetCommand;
	}
	else if (strcmp(CommandBuffer, "STRT") == 0)
	{
		returnCommand = StartCommand;
	}
	else if (strcmp(CommandBuffer, "GOVR") == 0)
	{
		returnCommand = GameOverCommand;
	}

	return returnCommand;
}

int SerialCommunicator::GetLastCommand(void)
{
	if (CurrentState == EndOfMessage)
	{
		return LastCommand;
	}

	return -1;
}

bool SerialCommunicator::GetLastData(char *output)
{
	if (CurrentState == EndOfMessage)
	{
		output = LastCommandData;
		return true;
	}

	return false;
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

void SerialCommunicator::RequestReset(void)
{
	char cmd[5];
	strcpy(cmd, "RSTC");

	char dat[1];
	dat[0]= '\0';

	char msg[16];
	BuildMessage(msg, 16, cmd, dat);
	AddToQueue(msg);
}

void SerialCommunicator::SendGameOver(int score)
{
	char cmd[5];
	strcpy(cmd, "GOVR");

	char dat[4];
	snprintf(dat, 4, "%ld", score);

	char msg[16];
	BuildMessage(msg, 16, cmd, dat);
	AddToQueue(msg);
}
