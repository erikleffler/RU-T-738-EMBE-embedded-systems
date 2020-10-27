#include <Arduino.h>

#ifndef MODBUS_ADDRESS
#define MODBUS_ADDRESS -1
#endif

/*
slave number 0 | unit address 1 | fn code 2 | first register | amount of registers | (crc)
byte | byte | 2 bytes | 2  bytes | (2 bytes)


char packet[6] = {
		(char) address,
		'\x03',
		(char) HIGHER_8(first_register),
		(char) LOWER_8(first_register),
		(char) HIGHER_8(register_count),
		(char) LOWER_8(register_count)
	};
*/

const size_t MSG_LEN = 6;
char msg[MSG_LEN];

uint8_t slave_number;
uint8_t function_number;
uint8_t first_register_higher;
uint8_t first_register_lower;
uint16_t first_register;
uint8_t register_count_higher;
uint8_t register_count_lower;
uint16_t register_count;

int ledPin = 13; // LED with PWM brightness control

void setup()
{
   // A baud rate of 115200 (8-bit with No parity and 1 stop bit)
   Serial.begin(115200, SERIAL_8N1);
   pinMode(ledPin, OUTPUT); // the LED is an output
}

void loop()
{
   if (Serial.available() > 0)        // bytes received
   {                                  
      Serial.readBytes(msg, MSG_LEN); // binary messages have fixed length and no terminating \0.
      slave_number = int(msg[0]);
      function_number = int(msg[1]);

      if (slave_number == MODBUS_ADDRESS)
      {
          if(function_number == 03)
          {
              handle_read();
          }
          else if(function_number == 06)
          {
              handle_write();
          }
        }
   }
}

void handle_read()
{
    first_register_higher = uint8_t(msg[2]);
    first_register_lower = uint8_t(msg[3]);
    first_register = first_register_higher << 8 | first_register_lower;

    register_count_higher = int(msg[4]);
    register_count_lower = int(msg[5]);
    register_count = register_count_higher << 8 | register_count_lower;

    if(first_register == 1 && register_count == 1)
    {
        //success
        Serial.write('\x03');
    }
    else
    {
        //fail
        Serial.write('\x86');
    }
}

void handle_write() 
{
    /*
    int level = msg[1];
    if (level >= 0 && level <= 255)
    {                              // is it in range?
        analogWrite(ledPin, level); // yes, write out
        sprintf(buffer, "Set brightness to %d", level);
    }
    else
    { // no, error message back
        sprintf(buffer, "Error: %d is out of range", level);
    }
    */
}