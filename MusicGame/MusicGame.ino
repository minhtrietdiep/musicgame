#include "NewTone.h"
#include "SerialCommunicator.h"
#include "MusicListBuilder.h"
#include "ButtonDebouncer.h"
#include "LED.h"
#include "Slider.h"

//#include "Game.h"

#define DEBUG

static const int MAX_MUSIC = 20;

static const long connectionSpeed = 38400;

static const byte buzzerPin = 3;

static const byte ButtonOne = 10;
static const byte ButtonTwo = 11;
static const byte ButtonThree = 12;

static const byte SliderOne = A2;
static const byte SliderTwo = A1;
static const byte SliderThree = A0;

static const byte LEDOne = 5;
static const byte LEDTwo = 6;

#define LATCH 7
#define CLOCK 8
#define DATA 4

static const byte ledCharSet[16] = {
	B00111111, B00000110, B01011011,
	B01001111, B01100110, B01101101,
	B01111101, B00000111, B01111111,
	B01101111, B01110111, B01111100,
	B01011000, B01011110, B01111001,
	B01110001
};
static const byte ledIdleSet[8] = {
	B00000001, B00000010, B01000000,
	B00010000, B00001000, B00000100,
	B01000000, B00100000
};

ButtonDebouncer Buttons[] =
{
	ButtonDebouncer(ButtonOne, INPUT_PULLUP),
	ButtonDebouncer(ButtonTwo, INPUT_PULLUP),
	ButtonDebouncer(ButtonThree, INPUT_PULLUP)
};

Slider Sliders[] =
{
	Slider(SliderOne),
	Slider(SliderTwo),
	Slider(SliderThree)
};

LED LEDs[] =
{
	LED(LEDOne),
	LED(LEDTwo)
};

long lastTime = 50;
int SliderValues[3];
int Score;
int GameState;
int LevelState;
int CurrentNote;
int ToneCounter;
MusicFile *CurrentMusicFile;
int counter = 0;
bool play = false;

//int melody[] = { 262, 196, 196, 220, 196, 0, 247, 262 };
int melody[3]; // = { 200, 400, 800 };

MusicFile MusicFiles[MAX_MUSIC];
MusicListBuilder Builder;
SerialCommunicator SComm;
//Game GameObj;

void setup()
{
	Serial.begin(connectionSpeed);
	SComm = SerialCommunicator(Serial);
	//GameObj = Game();
	GameState = 0;
	Score = 0;

	Builder = MusicListBuilder(
		MAX_MUSIC,
		MAX_NOTES,
		buzzerPin);

	Builder.Build(MusicFiles);

	for (int i = 0; i < (sizeof(Sliders) / sizeof(*Sliders)); i++)
	{
		Sliders[i].Map(0, 1023, NOTE_B0, NOTE_DS8);
	}

	pinMode(LATCH, OUTPUT);
	pinMode(CLOCK, OUTPUT);
	pinMode(DATA, OUTPUT);
}

void loop()
{
	SComm.Receive();

	int CurrentCommand;
	CurrentCommand = SComm.GetLastCommand();

	// Update button and slider states every loop
	for (int i = 0; i< (sizeof(Buttons) / sizeof(*Buttons)); i++)
	{
		Buttons[i].GetButtonState();
	}
	for (int i = 0; i < (sizeof(Sliders) / sizeof(*Sliders)); i++) 
	{
		SliderValues[i] = Sliders[i].GetValue();
	}

	if (ToneCounter >= (sizeof(melody) / sizeof(*melody)))
	{
		//SComm.SendGameOver(Score);
		Serial.print(">GOVR");
		Serial.print(Score);
		Serial.print(";");
		GameState = 2;
	}

	if (GameState == 0)
	{
		LEDs[1].IntervalToggle(200);
		
		Set7Seg(1, counter);
		if (HasIntervalPassed(lastTime, 100))
		{
			counter++;
		}
		if (counter >= 8)
		{
			counter = 0;
		}
	}

	if (GameState == 2)
	{
		Set7Seg(0, counter);
		if (HasIntervalPassed(lastTime, 100))
		{
			counter++;
		}
		if (counter >= 16)
		{
			counter = 0;
		}

		ToneCounter = 0;
	}

	if (Buttons[1].JustPressed && GameState == 0 ||
		(CurrentCommand == StartCommand && GameState == 0))
	{
		StartGame();
		PlaySong();
	}

	if (Buttons[2].JustPressed &&
		GameState == 2)
	{
		ResetGame();
	}

	if (CurrentCommand == ResetCommand)
	{
		ResetGame();
	}

	if (Buttons[2].JustPressed && GameState == 1) 
	{
		SComm.RequestReset();
	}

	if (Buttons[0].IsPressed &&
		GameState == 1)
	{
		NewTone(buzzerPin, SliderValues[0]);
	}
	else
	{
		noNewTone(buzzerPin);
	}

	if (Buttons[0].JustReleased &&
		GameState == 1)
	{		
		CalculateScore(
			SliderValues[0],
			melody[ToneCounter]);
		Set7Seg(0, Score);
		ToneCounter++;
	}

	SComm.Send();
	
#	ifdef DEBUG
	// SComm.PrintFreeMemory(2000);
	// if the LED on D5 toggles once a second,
	// we know the Arduino hasnt crashed
	LEDs[0].IntervalToggle(1000);
#	endif
}

void ResetGame()
{
	Score = 0;
	CurrentNote = 0;
	CurrentMusicFile = 0;
	GameState = 0;
	ToneCounter = 0;
}

void StartGame()
{
	Set7Seg(0, Score);
	GameState = 1;
	for (int i = 0; i <= 2; i++)
	{
		melody[i] = random(NOTE_B0, NOTE_DS8);
	}
}

void PlaySongTemp()
{
	for (int i = 0; i < (sizeof(melody) / sizeof(*melody)); i++)
	{
		NewTone(buzzerPin, melody[i], 300);
		delay(400);
	}
}

void PlaySong()
{
	for (int i = 0; i < (sizeof(melody) / sizeof(*melody)); i++)
	{
		NewTone(buzzerPin, melody[i], 300);
		delay(400);
	}
}

void CalculateScore(int slider, int CurrentNote)
{

	if (CurrentNote > abs(slider - CurrentNote - 2000) && CurrentNote < abs(slider - CurrentNote + 2000))
	{
		Score++;
	}

	if (CurrentNote > abs(slider - CurrentNote - 1000) && CurrentNote < abs(slider - CurrentNote + 1000))
	{
		Score += 2;
	}
	
	if (CurrentNote > abs(slider - CurrentNote - 100) && CurrentNote < abs(slider - CurrentNote + 100))
	{
		Score += 3;
	}
}

void Set7Seg(int mode, int score)
{
	if (mode == 0)
	{
		digitalWrite(LATCH, LOW);
		shiftOut(DATA, CLOCK, MSBFIRST, ~(ledCharSet[score]));
		digitalWrite(LATCH, HIGH);
	}
	if (mode == 1)
	{
		digitalWrite(LATCH, LOW);
		shiftOut(DATA, CLOCK, MSBFIRST, ~(ledIdleSet[score]));
		digitalWrite(LATCH, HIGH);
	}
}
