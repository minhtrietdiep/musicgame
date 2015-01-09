#ifndef MusicListBuilder_h
#define MusicListBuilder_h
#include "MusicFile.h"
#include "Pitches.h"
#include <Arduino.h>

class MusicListBuilder
{
private:
	int MaxItems;
	int MaxNotes;
	int *Notes;
	byte BuzzerPin;
public:
	MusicListBuilder();
	~MusicListBuilder();
	MusicListBuilder(int maxitems, int maxnotes, byte buzzerpin);
	void Build(MusicFile *target);
};

#endif