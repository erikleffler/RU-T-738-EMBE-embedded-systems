#include <Arduino.h>
#include <stdint.h>

#ifndef MODBUS_ADDRESS
#define MODBUS_ADDRESS -1
#endif
#define MSG_LEN 8

#define HIGHER_8(x) (x >> (8 * sizeof(x) - 8))
#define LOWER_8(x) (x & 0xff)
#define MAKE_16(higher, lower) (((uint16_t)higher << 8) | (uint16_t)lower)

int ledPin = 13; // LED with PWM brightness control
uint8_t led_val = 0;


// Compute the MODBUS RTU CRC
uint16_t ModRTU_CRC(uint8_t buf[], int len)
{
    uint16_t crc = 0xFFFF;

    for (int pos = 0; pos < len; pos++) {
        crc ^= (uint16_t)buf[pos]; // XOR byte into least sig. byte of crc

        for (int i = 8; i != 0; i--) { // Loop over each bit
            if ((crc & 0x0001) != 0) { // If the LSB is set
                crc >>= 1; // Shift right and XOR 0xA 001
                crc ^= 0xA001;
            }
            else // Else LSB is not set
                crc >>= 1; // Just shift right
        }
    }
    // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
    return crc;
}

bool handle_crc(uint8_t msg[])
{   
    uint16_t crc_arduino;
    crc_arduino = ModRTU_CRC(msg, MSG_LEN-2);
          
    /*get register count*/
    uint8_t crc_higher;
    uint8_t crc_lower;
    uint16_t crc_pi;

    crc_higher = int(msg[6]);
    crc_lower = int(msg[7]);
    crc_pi = crc_higher << 8 | crc_lower;

    return crc_arduino == crc_pi;
}

void setCrc(uint8_t* packet, size_t length) {
    uint16_t crc;

    crc = ModRTU_CRC(packet, length - 2);

    // Big endian
    packet[length - 2] = (char)HIGHER_8(crc);
    packet[length - 1] = (char)LOWER_8(crc);
}

uint8_t verifyCrc(char* packet, size_t length) {
    uint16_t crc, recv_crc;

    // Big endian
    recv_crc = MAKE_16(packet[length - 2], packet[length - 1]);

    crc = ModRTU_CRC((uint8_t*)packet, length - 2);

    if (crc != recv_crc) {
        fprintf(stderr, "Crc invalid. Expected: %02x %02x, got: %02x %02x\n",
                HIGHER_8(crc), LOWER_8(crc), HIGHER_8(recv_crc),
                LOWER_8(recv_crc));
        return -1;
    }
    return 0;
}


void handle_read(uint8_t msg[])
{
    /*get register count*/
    uint8_t register_count_higher;
    uint8_t register_count_lower;
    uint16_t register_count;

    register_count_higher = int(msg[4]);
    register_count_lower = int(msg[5]);
    register_count = register_count_higher << 8 | register_count_lower;
    //Serial.write(register_count);

    /*get the register*/
    uint8_t first_register_higher;
    uint8_t first_register_lower;
    uint16_t first_register;

    first_register_higher = uint8_t(msg[2]);
    first_register_lower = uint8_t(msg[3]);
    first_register = first_register_higher << 8 | first_register_lower;



    pinMode(PD1, OUTPUT);
    if(first_register == 1 && register_count == 1)
    {
        uint8_t packet[7] = {MODBUS_ADDRESS,
                uint8_t(3),
                uint8_t(register_count*2),
                uint8_t(0),
                led_val,
                0,
                0};
        
        setCrc(packet,sizeof(packet));

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

void handle_write(uint8_t msg[]) 
{    

    /*get register value*/
    uint8_t register_value_higher;
    uint8_t register_value_lower;
    uint16_t register_value;

    register_value_higher = int(msg[4]);
    register_value_lower = int(msg[5]);
    register_value = register_value_higher << 8 | register_value_lower;

    /*get register*/
    uint8_t first_register_higher;
    uint8_t first_register_lower;
    uint16_t first_register;

    first_register_higher = uint8_t(msg[2]);
    first_register_lower = uint8_t(msg[3]);
    first_register = first_register_higher << 8 | first_register_lower;

    pinMode(PD1, OUTPUT);
    if (first_register == 1)
    {
        if (register_value >= 0 && register_value <= 255)
        {                              // is it in range?
            led_val = register_value;
            analogWrite(ledPin, led_val);       

            uint8_t packet[MSG_LEN] = {MODBUS_ADDRESS,
                    uint8_t(6),
                    first_register_higher,
                    first_register_lower,
                    uint8_t(0),
                    led_val,
                    0,
                    0};
        
            setCrc(packet,sizeof(packet));

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
        uint8_t msg[MSG_LEN];                            
        Serial.readBytes(msg, MSG_LEN); // binary messages have fixed length and no terminating \0.
        
        uint8_t slave_number;
        slave_number = uint8_t(msg[0]);

        if (slave_number == MODBUS_ADDRESS)
        {
            if(handle_crc(msg) == true)
            {
                uint8_t function_number;
                function_number = uint8_t(msg[1]);  // get the function -> read or write
                
                if(function_number == 03)
                {
                    handle_read(msg);
                }
                else if(function_number == 06)
                {
                    handle_write(msg);
                }
                else
                {
                    char packet[2] = {'\x80', // Invalid Function --> does not matter what is inside here
                                    '\x01'};
                    Serial.write(packet);
                }
            }
            else
            {
                char packet[2] = {'\x80', // Ilegal data value --> crc is incorrect
                                '\x03'};
                Serial.write(packet);
            }         
        }
    }
}

