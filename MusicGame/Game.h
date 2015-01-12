#ifndef Game_h
#define Game_h
#include <Arduino.h>
#include "MusicFile.h"

class Game
{
private:
	MusicFile *CurrentMusicFile;
	byte CurrentNote;
	
	bool Playing;
	bool Playable;
public:
	Game();
	~Game();
	void Start(void);
	void Reset(void);
	void SetMusicFile(MusicFile &target);
	void PlayExample(void);
};

#endif
