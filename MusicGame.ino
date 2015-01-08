#include "ButtonDebouncer.h"
#include "MusicFile.h"
#include "MusicListBuilder.h"
#include "Pitches.h"

static const int BUTTON_AMOUNT = 3;
static const int MAX_MUSIC = 20;

static const int connectionSpeed = 115200;

static const int buzzerPin = 3;
static const int slider1 = A2;
static const int slider2 = A1;
static const int slider3 = A0;
static const int led5 = 5;
static const int led6 = 6;

ButtonDebouncer buttons[BUTTON_AMOUNT] =
{
	ButtonDebouncer(10, INPUT_PULLUP),
	ButtonDebouncer(11, INPUT_PULLUP),
	ButtonDebouncer(12, INPUT_PULLUP)
};

MusicFile MusicFiles[MAX_MUSIC];
MusicListBuilder Builder;

int difference;
int currentMusicTone;
int currentUserTone;
String s;

void setup()
{
	Builder = MusicListBuilder(MAX_MUSIC, MAX_NOTES, buzzerPin);
	Builder.Build(MusicFiles);

	Serial.begin(connectionSpeed);
	pinMode(led5, OUTPUT);
	pinMode(led6, OUTPUT);
}

void loop()
{
	// get button input like this:
	// first, check the state:
	// buttons[0].GetButtonState();
	// IsButtonOnePressed = button[0].IsPressed;

	// simply builds the string
	if (Serial.available() > 0)
	{
		s += (char)Serial.read();
	}

	// stuff to respond on serial stuff, check on >STUFF;
	// play music based on serial message, set music file var

	// disposes of string once message has been completed and parsed
	if (s.endsWith(";")) 
	{
		Serial.println(s);
		s = "";
	}

	/* This doesnt work anymore because of the new ButtonDebouncer
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
