#include "MusicFile.h"


MusicFile::MusicFile()
{
	const int array[] = { 0, 0, 0 };
	MusicFile(array, 2);
}

MusicFile::MusicFile(const int *notes, byte buzzerpin)
{
	Notes = new int[MAX_NOTES];
	for (int i = 0; i < MAX_NOTES; i++)
	{
		Notes[i] = notes[i];
	}

	BuzzerPin = buzzerpin;
}

void MusicFile::Play()
{
	for (int i = 0; i < MAX_NOTES; i++)
	{
		tone(BuzzerPin, Notes[i], 1500);
	}
}

String MusicFile::ToString()
{
	String output = "MusicFile:";

	for (int i = 0; i < MAX_NOTES; i++)
	{
		output += String(Notes[i]);

		if (i < MAX_NOTES - 1)
		{
			output += ':';
		}
	}

	return output;
}


MusicFile::~MusicFile()
{
}
