#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define NeoPixelPIn     6
#define NUMPIXELS      16

#define SoundMix_0      0
#define SoundMix_1      1
#define SoundMix_2      2

#define StartBtn        2
#define SoundChange_0   3
#define SoundChange_1   4
#define SoundChange_2   5

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NeoPixelPIn, NEO_GRB + NEO_KHZ800);

void BackgroundNeoPixel();
void CheckSensor();
void SensorInitialze();

long CurrentMillis = 0;
long ExNeopixcelMillis = 0;
long ExSensorMillis = 0;



////////////////////////Sensor Value
int SoundMixValue_0;
int SoundMixValue_1;
int SoundMixValue_2;
int Ex_SoundMixValue_0;
int Ex_SoundMixValue_1;
int Ex_SoundMixValue_2;


int SoundChangeValue_0;
int SoundChangeValue_1;
int SoundChangeValue_2;
int Ex_SoundChangeValue_0;
int Ex_SoundChangeValue_1;
int Ex_SoundChangeValue_2;

int StartBtnValue;
int Ex_StartBtnValue;

void setup() {

	Serial.begin(9600);
	pinMode(StartBtn, INPUT);
	pinMode(SoundChange_0, INPUT);
	pinMode(SoundChange_1, INPUT);
	pinMode(SoundChange_2, INPUT);

	pinMode(SoundMix_0, INPUT);
	pinMode(SoundMix_1, INPUT);
	pinMode(SoundMix_2, INPUT);

#if defined (__AVR_ATtiny85__)
	if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

	pixels.begin(); // This initializes the NeoPixel library.
	long StartMillis = millis();
	CurrentMillis = StartMillis;
	ExNeopixcelMillis = StartMillis;
	ExSensorMillis = StartMillis;

	SensorInitialze();
}

void loop()
{
	if (Serial.available())
	{
		char str = Serial.read();
		Serial.print(str);
	}
	CurrentMillis = millis();
	CheckSensor();
}

void SensorInitialze()
{
	SoundMixValue_0 = (int)(analogRead(SoundMix_0) / 10.24);
	SoundMixValue_1 = (int)(analogRead(SoundMix_1) / 10.24);
	SoundMixValue_2 = (int)(analogRead(SoundMix_2) / 10.24);

	Ex_SoundMixValue_0 = SoundMixValue_0;
	Ex_SoundMixValue_1 = SoundMixValue_1;
	Ex_SoundMixValue_2 = SoundMixValue_2;

	SoundChangeValue_0 = digitalRead(SoundChange_0);
	SoundChangeValue_1 = digitalRead(SoundChange_1);
	SoundChangeValue_2 = digitalRead(SoundChange_2);

	Ex_SoundChangeValue_0 = SoundChangeValue_0;
	Ex_SoundChangeValue_1 = SoundChangeValue_1;
	Ex_SoundChangeValue_2 = SoundChangeValue_2;

	StartBtnValue = digitalRead(StartBtn);
	Ex_StartBtnValue = StartBtn;

}

void CheckSensor()
{
	if (CurrentMillis - ExSensorMillis >= 100)
	{
		SoundMixValue_0 = (int)(analogRead(SoundMix_0) / 10.24);
		SoundMixValue_1 = (int)(analogRead(SoundMix_1) / 10.24);
		SoundMixValue_2 = (int)(analogRead(SoundMix_2) / 10.24);

		SoundChangeValue_0 = digitalRead(SoundChange_0);
		SoundChangeValue_1 = digitalRead(SoundChange_1);
		SoundChangeValue_2 = digitalRead(SoundChange_2);

		StartBtnValue = digitalRead(StartBtn);

		if (SoundMixValue_0 != Ex_SoundMixValue_0)
		{
			Serial.println(SoundMixValue_0);
			Ex_SoundChangeValue_0 = SoundChangeValue_0;
		}

		if (SoundMixValue_1 != Ex_SoundMixValue_1)
		{
			Serial.println(SoundMixValue_1);
			Ex_SoundChangeValue_1 = SoundChangeValue_1;
		}

		if (SoundMixValue_2 != Ex_SoundMixValue_2)
		{
			Serial.println(SoundMixValue_2);
			Ex_SoundChangeValue_2 = SoundChangeValue_2;
		}

		if (SoundChangeValue_0 < Ex_SoundChangeValue_0)
		{
			Serial.println("C0");
			Ex_SoundChangeValue_0 = SoundChangeValue_0;
		}

		if (SoundChangeValue_1 < Ex_SoundChangeValue_1)
		{
			Serial.println("C1");
			Ex_SoundChangeValue_1 = SoundChangeValue_1;
		}
		if (SoundChangeValue_2 < Ex_SoundChangeValue_2)
		{
			Serial.println("");
			Ex_SoundChangeValue_2 = SoundChangeValue_2;
		}

		if (StartBtnValue < Ex_StartBtnValue)
		{
			Serial.println("S");
			Ex_SoundChangeValue_2 = SoundChangeValue_2;
		}

		Serial.println("a");
		ExSensorMillis = CurrentMillis;
	}
}


void BackgroundNeoPixel()
{

}