#include "SerialCommunicator.h"
#include "MusicListBuilder.h"
#include "ButtonDebouncer.h"
#include "LED.h"
#include "Slider.h"

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

bool knipper = false;

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
SerialCommunicator SComm;

void setup()
{
	Serial.begin(connectionSpeed);
	SComm = SerialCommunicator(Serial);

	Builder = MusicListBuilder(
		MAX_MUSIC,
		MAX_NOTES,
		buzzerPin);

	Builder.Build(MusicFiles);
}

void loop()
{
	SComm.Receive();

	if (SComm.Parse() == StartCommand) {
		knipper = true;
		SComm.WriteButtonState(1, true);
	}

	if (knipper) 
	{
		LEDs[1].IntervalToggle(50);
	}

#ifdef DEBUG
	// SComm.PrintFreeMemory(2000);
#endif

	SComm.Send();

#ifdef DEBUG
	// if the LED on D5 toggles once a second,
	// we know the Arduino hasnt crashed
	LEDs[0].IntervalToggle(1000);
#endif
}
