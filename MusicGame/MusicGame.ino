#include "ButtonDebouncer.h"
#include "MusicFile.h"
#include "MusicListBuilder.h"
#include "Pitches.h"
#include "SerialCommunicator.h"
#include "LED.h"
#include "Slider.h"

static const int MAX_MUSIC = 20;

static const int connectionSpeed = 115200;

static const byte buzzerPin = 3;

static const byte ButtonOne = 10;
static const byte ButtonTwo = 11;
static const byte ButtonThree = 12;

static const byte SliderOne = A2;
static const byte SliderTwo = A1;
static const byte SliderThree = A0;

static const byte LEDOne = 5;
static const byte LEDTwo = 6;

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

MusicFile MusicFiles[MAX_MUSIC];
MusicListBuilder Builder;
SerialCommunicator Receiver;

int difference;
int currentMusicTone;
int currentUserTone;

void setup()
{
	Builder = MusicListBuilder(
		MAX_MUSIC,
		MAX_NOTES, 
		buzzerPin);

	Builder.Build(MusicFiles);

	Receiver = SerialCommunicator(connectionSpeed);

	for (int i = 0; i < (sizeof(Sliders) / sizeof(*Sliders)); i++)
	{
		Sliders[i].Map(
			0,
			1024,
			Pitches[0],
			Pitches[MAX_PITCHES]);
	}
}

void loop()
{
	// get button input like this:
	// first, check the state:
	// buttons[0].GetButtonState();
	// IsButtonOnePressed = button[0].IsPressed;

	// turn LED's on and of with e.g.
	// LEDs[0].On() and LEDs[0].Off()
	// or
	// LEDs[0].Fade(-5, 30)

	Receiver.Receive();

	// stuff to respond on serial stuff, check on >STUFF;
	// play music based on serial message, 
	// set music file var
	if (!Receiver.Receiving)
	{
		// do stuff with Receiver.LastMessage
	}
	

	/* This doesnt work anymore because of 
	   the new ButtonDebouncer
	for (int i = 0; i < sizeof(songArray); i++)
	{
		while (digitalRead(button1) == HIGH)
		{
			currentUserTone = map(analogRead(slider1), 0, 1023, 200, 600);
		}
		difference += abs(currentUserTone - currentMusicTone);
	}
	*/
}
