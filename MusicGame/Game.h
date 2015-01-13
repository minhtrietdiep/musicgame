#ifndef Game_h
#define Game_h
#include <Arduino.h>
#include "MusicFile.h"

class Game
{
private:
	MusicFile *CurrentMusicFile;
	byte CurrentNote;
	int SelectedNote;
	byte Score;

	bool Playing;
	bool Playable;
public:
	Game();
	void Start(void);
	void Reset(void);
	void JustReleased(int slider);
	void SetMusicFile(MusicFile &target);
	void PlayExample(void);
};

#endif
