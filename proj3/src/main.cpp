#include <Arduino.h>
#include <states.h>

constexpr int MAX_COMMAND_LENGTH = 20;

Context context;

void setup() {

	context = Context(new Initialization());
	context.do_work();

}

void loop() {

	delay(100);

	char command = 0;
	if(Serial.available()) {
		command = Serial.read();
	}
	if(command = 'r') {
	
		Serial.println("r");
	}

}

/*
void loop() {

	char command[MAX_COMMAND_LENGTH + 1] = {0};

	Serial.print("Enter command: ");

	for(int i = 0; i < MAX_COMMAND_LENGTH; i++) {

		while(!Serial.available()) {
			delay(100);
			context.do_work(); // do work until input available
		}

		command[i] = Serial.read();
		Serial.print(command[i]);

		if(command[i] == '\n') {
			command[i] = 0; 
			break;
		}
	}

	context.process_cmd(command);

}*/
