#include "SerialCommunicator.h"

SerialCommunicator::SerialCommunicator()
{
}

SerialCommunicator::SerialCommunicator(Stream &serial)
{
	SerialCom = &serial;
	MemoryLastTime = millis();
}

void SerialCommunicator::Receive(void)
{
	while (SerialCom->available())
	{
		size_t bytesAvailable = min(SerialCom->available(), MAX_BUFFER_SIZE);
		SerialCom->readBytes(Buffer, bytesAvailable);
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
	if ((MemoryLastTime + interval) > millis())
	{
		return;
	}

	SerialCom->print(">FMEM");
	SerialCom->print(String(freeMemory()));
	SerialCom->print(';');

	MemoryLastTime = millis();
}

void SerialCommunicator::WriteButtonState(int identifier, bool status)
{
	SerialCom->print(">BTN");
	SerialCom->print(String(identifier));
	if (status)
	{
		SerialCom->print('1');
	}
	else
	{
		SerialCom->print('0');
	}

	SerialCom->print(";");
}
