#include <Arduino.h>

constexpr uint8_t led_pin = 11;

void setup() {
    Serial.begin(115200, SERIAL_8N1);
    pinMode(led_pin, OUTPUT);
}

void loop() {
    char packet[3];
    char buffer[100];
    uint8_t level;

    if (Serial.available() > 0) {
        if (Serial.readBytes(packet, sizeof(packet)) != sizeof(packet)) {
            snprintf(buffer, sizeof(buffer), "Failed to read packet\n");
            goto end_loop;
        }

        if (packet[0] != '\x42' || packet[2] != '\x42') {
            snprintf(buffer, sizeof(buffer),
                     "Malformed packet, received: %02x%02x%02x\n", packet[0],
                     packet[1], packet[2]);
            goto end_loop;
        }

        level = packet[1];
        analogWrite(led_pin, level);
        snprintf(buffer, sizeof(buffer), "Set brightness to %d\n", level);

    end_loop:
        Serial.print(buffer);
    }
}
