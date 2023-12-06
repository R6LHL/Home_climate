#ifndef TEXTS_HPP
#define TEXTS_HPP

#include <avr/pgmspace.h>

const char DETECT_I2C_DEVICE_TEXT[] PROGMEM = "I2C found: 0x";

const char CLOCK_SET_MENU_TEXT[] PROGMEM    = "Clock set->";

const char HOURS_SET_MENU_TEXT[] PROGMEM    = "Hours: ";
const char MINUTES_SET_MENU_TEXT[] PROGMEM  = "Minutes: ";
const char SECONDS_SET_MENU_TEXT[] PROGMEM  = "Seconds: ";
const char DOW_SET_MENU_TEXT[] PROGMEM      = "Day: ";
const char DATE_SET_MENU_TEXT[] PROGMEM     = "Date: ";
const char MONTH_SET_MENU_TEXT[] PROGMEM    = "Month: ";
const char YEAR_SET_MENU_TEXT[] PROGMEM     = "Year: ";


#endif //TEXTS_HPP