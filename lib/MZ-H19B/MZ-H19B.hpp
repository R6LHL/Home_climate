#ifndef MZ_H19B_HPP

#include <avr/pgmspace.h>

namespace 
{

    const uint8_t BUFFER_LENGHT = 8;
    const char read_CO2[] PROGMEM = {0xff,0x01,0x86};
    const char zero_Cal[] PROGMEM = {0xff,0x01,0x87};
    const char span_Cal[] PROGMEM = {0xff,0x01,0x88};
    const char toggle_Sels_Cal[] PROGMEM = {0xff,0x01,0x79};
    const char set_Range[] PROGMEM = {0xff,0x01,0x99};

    uint8_t buffer[BUFFER_LENGHT];
    uint8_t crc;

    uint8_t get_CRC(uint8_t hi_byte, uint8_t lo_byte);
}
#endif //MZ_H19B_HPP