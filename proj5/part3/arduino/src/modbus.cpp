#include <modbus.h>


Modbus::Modbus()
{
    ledPin = 13; // LED with PWM brightness control
    led_val = 0;
}
// Set chosen pin to input
uint16_t Modbus::ModRTU_CRC(uint8_t buf[], int len)
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

bool Modbus::handle_crc(uint8_t msg[])
{
    uint16_t crc_arduino;
    crc_arduino = ModRTU_CRC(msg, MSG_LEN-2);
          
    uint16_t crc_pi;
    crc_pi = MAKE_16(msg[6],msg[7]);

    return crc_arduino == crc_pi;
}

void Modbus::setCrc(uint8_t* packet, size_t length)
{
    uint16_t crc;

    crc = ModRTU_CRC(packet, length - 2);

    // Big endian
    packet[length - 2] = (char)HIGHER_8(crc);
    packet[length - 1] = (char)LOWER_8(crc);
}

uint8_t Modbus::verifyCrc(char* packet, size_t length)
{
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

void Modbus::handle_read(uint8_t msg[])
{
    /*get register*/
    uint16_t first_register;
    first_register = MAKE_16(msg[2], msg[3]);
    
    /*get register count*/
    uint16_t register_count;
    register_count = MAKE_16(msg[4], msg[5]);

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
}

void Modbus::handle_write(uint8_t msg[])
{
    /*get register*/
    uint16_t first_register;
    first_register = MAKE_16(msg[2], msg[3]);

    /*get register value*/
    uint16_t register_value;
    register_value = MAKE_16(msg[4], msg[5]);

    if(first_register == 0)
    {

    }
    else if (first_register == 2)
    {
        if (register_value >= 0 && register_value <= 255)
        {                              // is it in range?
            led_val = register_value;
            analogWrite(ledPin, led_val);       

            uint8_t packet[MSG_LEN] = {MODBUS_ADDRESS,
                    6,
                    HIGHER_8(first_register),
                    LOWER_8(first_register),
                    0,
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
}

void Modbus::handle_input()
{
    static_assert(MODBUS_ADDRESS != -1, "Modbus is not available");
    
    uint8_t msg[MSG_LEN];                            
    Serial.readBytes(msg, MSG_LEN); // binary messages have fixed length and no terminating \0.

    /*check device number*/
    if (msg[0] == MODBUS_ADDRESS)
    {
        if(handle_crc(msg) == true)
        {     
            /*check function number*/
            if(msg[1] == 03)
            {
                handle_read(msg);
            }
            else if(msg[1] == 06)
            {
                handle_write(msg);
            }
            else
            {
                char packet[2] = {'\x80', // Invalid Function
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