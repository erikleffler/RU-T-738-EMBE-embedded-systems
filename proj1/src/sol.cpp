#include "Arduino.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void busy_wait(int iter) {
	double c = 2;
	for(int i = 0; i < iter; i++) {
		for(int j = 0; j < iter; j++) {
			for(int k = 0; k < iter; k++) {
				c /= (i + j + k);
			}
		}
	}
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);

  // wait for a second
  busy_wait(1000);

  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);

   // wait for a second
  busy_wait(1000);
}
