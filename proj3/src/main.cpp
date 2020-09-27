#include <Arduino.h>
#include <states.h>

constexpr int MAX_COMMAND_LENGTH = 20;

Context context;

void setup() {

	context = Context(new Initialization());

}

void loop() {


	char command[MAX_COMMAND_LENGTH + 1] = {0};

	Serial.print("Enter command: ");
	delay(1000);
	Serial.print(millis());

	for(int i = 0; i < MAX_COMMAND_LENGTH; i++) {
		Serial.flush();

		while(!Serial.available()) {
			delay(100);
			context.do_work(); // do work until input available
			Serial.flush();
		}

		command[i] = Serial.read();
		Serial.print(command[i]);

		if(command[i] == '\n') {
			command[i] = 0; 
			break;
		}
	}


	context.process_cmd(command);


}
