#include "Game.h"


Game::Game()
{
	Playable = false;
	Score = 0;
	SelectedNote = 0;
}

void Game::Start(void)
{
	if (Playable)
	{
		Playing = true;
	}
	else
	{
		Playing = false;
	}
}

void Game::Reset(void)
{
	Score = 0;
	CurrentNote = 0;
	Playable = false;
}

void Game::SetMusicFile(MusicFile &target)
{
	CurrentMusicFile = &target;
	Playable = true;
}

void Game::PlayExample(void)
{
	if (Playing)
	{
		CurrentMusicFile->Play();
	}
}

void Game::JustReleased(int slider)
{
	if (Playing)
	{
		SelectedNote = map(slider, 0, 1023, 37, 4978);
		if (SelectedNote < CurrentNote - 100 && SelectedNote > CurrentNote + 100)
		{
			Score++;
		}
		if (SelectedNote < CurrentNote - 50 && SelectedNote > CurrentNote + 50)
		{
			Score++;
		}
	}
}