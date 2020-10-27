#include <Arduino.h>
int ledPin = 13;

void setup() {
    Serial.begin(115200, SERIAL_8N1);
    pinMode(ledPin, OUTPUT);
}

void loop() {
    char buffer[100];
    uint8_t value;

    if (Serial.available() > 0) {
        value = Serial.read();
        if (value >= 0 && value <= 255) {
            analogWrite(ledPin, value);
            snprintf(buffer, sizeof(buffer), "Set brightness to %d", value);
        } else {
            snprintf(buffer, sizeof(buffer), "Error: %d is out of range",
                     value);
        }
        Serial.print(buffer);
    }
}
