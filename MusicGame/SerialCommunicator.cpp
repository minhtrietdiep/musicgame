#include "SerialCommunicator.h"

SerialCommunicator::SerialCommunicator()
{
	SerialCommunicator(9600);
}

SerialCommunicator::SerialCommunicator(int speed)
{
	Serial.begin(speed);
	Buffer = "";
	LastMessage = "";
	Receiving = false;
}

void SerialCommunicator::Receive(void)
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

Command SerialCommunicator::Parse(String &data)
{
	return Parse(LastMessage, data);
}

Command SerialCommunicator::Parse(String input, String &data)
{
	String *substrings;
	char *commandString;
	SplitString(input, substrings, ':');

	substrings[0].toCharArray(
		commandString, 
		substrings[0].length());

	Command returnCommand = UnknownCommand;

	if (strcmp(commandString, "SelectSong") == 0)
	{
		returnCommand = SelectSongCommand;
	}
	else if (strcmp(commandString, "CreateSong") == 0)
	{
		returnCommand =  CreateSongCommand;
	}
	else if (strcmp(commandString, "Reset") == 0)
	{
		returnCommand = ResetCommand;
	}
	else if (strcmp(commandString, "Start") == 0)
	{
		returnCommand = StartCommand;
	}
	else if (strcmp(commandString, "GameOver") == 0)
	{
		returnCommand = GameOverCommand;
	}

	int length = sizeof(substrings) / sizeof(*substrings);
	for (int i = 1; i < length; i++)
	{
		data += substrings[i];
	}

	delete[] substrings;
	return returnCommand;
}

void SerialCommunicator::SplitString(String input, String *output, char separator)
{
	int length = input.length();
	int count = 0;
	for (int i = 0; i < length; i++)
	{
		if (input[i] == separator)
		{
			count++;
		}
	}

	if (count == 0)
	{
		return;
	}

	int *occurences = new int[count + 1];

	for (int i = 0; i < count; i++)
	{
		if (i != 0)
		{
			occurences[i] = input.indexOf(
				separator,
				occurences[i - 1]);
		}
		else
		{
			occurences[i] = input.indexOf(
				separator);
		}
	}

	occurences[count + 1] = length;

	output = new String[count];

	for (int i = 0; i < count - 1; i++)
	{
		output[i] = input.substring(
			occurences[i], 
			occurences[i + 1]);
	}

	delete[] occurences;
}

SerialCommunicator::~SerialCommunicator()
{
}
