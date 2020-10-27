#include <Arduino.h>

#ifndef MODBUS_ADDRESS
#define MODBUS_ADDRESS -1
#endif


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

uint8_t register_value_higher;
uint8_t register_value_lower;
uint16_t register_value;


uint8_t led_val = 0;

int ledPin = 13; // LED with PWM brightness control


void handle_read()
{
    register_count_higher = int(msg[4]);
    register_count_lower = int(msg[5]);
    register_count = register_count_higher << 8 | register_count_lower;
    //Serial.write(register_count);

    pinMode(PD1, OUTPUT);
    if(first_register == 1 && register_count == 1)
    {
        //success
        char data = char(led_val);
        char packet[4] = {'\x03',
                      '\x02',
                      '\x00',
                       data};

        Serial.write(packet, sizeof(packet));
    }
    else
    {
        //fail
        char packet[2] = {'\x83',
                '\x02'};
        Serial.write(packet);
    }
    pinMode(PD1, INPUT);
}

void handle_write() 
{   
    register_value_higher = int(msg[4]);
    register_value_lower = int(msg[5]);
    register_value = register_value_higher << 8 | register_value_lower;

    pinMode(PD1, OUTPUT);
    if (first_register == 1)
    {
        if (register_value >= 0 && register_value <= 255)
        {                              // is it in range?
            led_val = register_value;
            analogWrite(ledPin, led_val);
            
            char data = char(led_val);
            char packet[5] = {'\x06',
                        char(first_register_higher),
                        char(first_register_lower),
                        '\x00',
                        data};

            Serial.write(packet, sizeof(packet));
        }
        else
        { // no, error message back
            char packet[2] = {'\x86',
                    '\x03'};
            Serial.write(packet);
        }
    }
    else 
    {
        //fail
        char packet[2] = {'\x86',
                '\x02'};
        Serial.write(packet);
    }
    pinMode(PD1, INPUT);
}

void setup()
{
   // A baud rate of 115200 (8-bit with No parity and 1 stop bit)
   Serial.begin(115200, SERIAL_8N1);
   //Serial.begin(9600);
   pinMode(ledPin, OUTPUT); // the LED is an output
   
   pinMode(PD1, OUTPUT);
   digitalWrite(PD1, LOW);
}

void loop()
{
    static_assert(MODBUS_ADDRESS != -1, "Modbus is not available");

    if (Serial.available() > 0)        // bytes received
    {                                  
        Serial.readBytes(msg, MSG_LEN); // binary messages have fixed length and no terminating \0.
        slave_number = uint8_t(msg[0]);
        function_number = uint8_t(msg[1]);

        if (slave_number == MODBUS_ADDRESS)
        {
            first_register_higher = uint8_t(msg[2]);
            first_register_lower = uint8_t(msg[3]);
            first_register = first_register_higher << 8 | first_register_lower;
            //Serial.write(first_register);
            
            if(function_number == 03)
            {
                handle_read();
            }
            else if(function_number == 06)
            {
                handle_write();
            }
            else
            {
                char packet[2] = {'\x86', // Invalid Function --> does not matter what is inside here
                                '\x01'};
                Serial.write(packet);
            }
            
        }
    }
}

