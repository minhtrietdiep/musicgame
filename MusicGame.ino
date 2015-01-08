const long connectionSpeed = 115200;
const int buzzerPin = 3;
const int slider1 = A2;
const int slider2 = A1;
const int slider3 = A0;
const int button1 = 10;
const int button2 = 11;
const int button3 = 12;
const int led5 = 5;
const int led6 = 6;

int difference;
int currentMusicTone;
int currentUserTone;
int[] songArray;

void setup()
{
	Serial.begin(connectionSpeed);
	pinMode(led5, OUTPUT);
	pinMode(led6, OUTPUT);
	pinMode(button1, INPUT_PULLUP);
	pinMode(button2, INPUT_PULLUP);
	pinMode(button3, INPUT_PULLUP);
}

void loop()
{
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

	for (int i = 0; i < sizeof(songArray); i++) 
	{
		while (digitalRead(button1) == HIGH) 
		{
			currentUserTone = map(analogRead(slider1), 0, 1023, 200, 600);
		}
		difference += abs(currentUserTone - currentMusicTone)
	}
}
