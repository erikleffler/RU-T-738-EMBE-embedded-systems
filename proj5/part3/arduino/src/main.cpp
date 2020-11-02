#include <Arduino.h>
#include <analog_out.h>
#include <analog_in.h>
#include <filter.h>
#include <context.h>
#include <init.h>
#include <timer.h>
#include <modbus.h>

// Create Objects
Analog_out led(PD5);
Analog_in photocell(PC0);
Filter filter;
Context *context;
Timer timer;
Modbus modbus;

// Application
void setup()
{
  // A baud rate of 115200 (8-bit with No parity and 1 stop bit)
  Serial.begin(115200, SERIAL_8N1);
  
  //Setup of CANopen state machine
  context = new Context(new Initialization_state);
}

ISR(TIMER1_COMPA_vect) {
	led.toggle();
}

void loop()
{
  uint8_t command = 0;

  delay(100);

  context->getobjects(&photocell, &led, &filter, &timer);
  modbus.get_context(context);
  context->do_work();

  if (Serial.available())
    command = modbus.handle_input();
    
/*
  if(command == 1)
    context->command_operation();
  else if (command == 2)
    context->command_stop();
  else if(command == 80)
    context->command_preoperation();
  else if (command == 81)
    context->command_reset();   
  else if(command == 10)
    context->is_reader = true;
  else if(command == 11)
    context->is_reader = false;
  else if(command == 12)
    context->command_config_low();
  else if(command == 13)
    context->command_config_high();
  else if(command == 14)
    context->command_config_ambient();
  //else if(command == 20)
    // set led val
  //else if(command == 30)
    // read photocellval
  //else if(command == 255)
    // error occured
    */
}