#ifndef MusicFile_h
#define MusicFile_h
#include <Arduino.h>
#include "NewTone.h"

static const int MAX_NOTES = 3;

class MusicFile
{
private:
	int *Notes;
	byte BuzzerPin;
public:
	MusicFile();
	~MusicFile();
	MusicFile(const int *notes, byte buzzerpin);
	void Play(void);
	String ToString(void);
};

#endif
