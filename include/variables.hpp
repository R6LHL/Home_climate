#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include "config.hpp"

typedef TaskManager<TASK_QUEUE_SIZE> TaskManager5;

extern TaskManager5 OS;

extern BME::Bosch_BME280 bme;
extern LiquidCrystal_I2C lcd;
extern RotaryEncoder encoder;
typedef Menu_Item<uint8_t>Menu_u8;

uint16_t CO2;
float temp;
uint8_t hum;
uint16_t press;

uint8_t day;
uint8_t month;
uint8_t year;
uint8_t hour;
uint8_t minute;
uint8_t second;

#endif //VARIABLES_HPP