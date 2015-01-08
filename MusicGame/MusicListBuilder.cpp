#include "MusicListBuilder.h"


MusicListBuilder::MusicListBuilder()
{
	MusicListBuilder(1, 1, 2);
}

MusicListBuilder::MusicListBuilder(int maxitems, const int maxnotes, byte buzzerpin)
{
	MaxItems = maxitems;
	MaxNotes = maxnotes;
	Notes = new int[maxnotes];
	BuzzerPin = buzzerpin;
}

void MusicListBuilder::Build(MusicFile *target)
{
	for (int i = 0; i < MaxItems; i++)
	{
		for (int n = 0; n < MaxNotes; n++)
		{
			Notes[n] = random(0, MAX_PITCHES);
		}

		target[i] = MusicFile(Notes, BuzzerPin);
	}
}

MusicListBuilder::~MusicListBuilder()
{
}
