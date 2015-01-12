#include "Game.h"


Game::Game()
{
	Playable = false;
}

void Game::Start(void)
{
	if (Playable)
	{
		Playing = true;
	}
}

void Game::Reset(void)
{
	CurrentNote = 0;
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

Game::~Game()
{
}
