#include "Arduino.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

void setup()
{
	// initialize LED digital pin as an output.
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);


}

void busy_wait(int iter) {
	int8_t c = 2;
	for(int i = 0; i < iter; i++) {
		for(int j = 0; j < iter; j++) {
			c *= 2;
		}
	}
}

void loop()
{
	int sensorValue = analogRead(A0);
	Serial.println(sensorValue);

	// turn the LED on (HIGH is the voltage level)
	digitalWrite(LED_BUILTIN, HIGH);

	// wait for a second
	busy_wait(sensorValue * 2);

	// turn the LED off by making the voltage LOW
	digitalWrite(LED_BUILTIN, LOW);

	// wait for a second
	busy_wait(sensorValue * 2);
}
