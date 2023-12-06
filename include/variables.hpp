#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include "config.hpp"

typedef TaskManager<TASK_QUEUE_SIZE> TaskManager5;

extern TaskManager5 OS;

#ifdef BME280_ENABLE
extern BME::Bosch_BME280 bme;
#endif //BME280_ENABLE

#ifdef LCD_ENABLE
extern LiquidCrystal_I2C lcd;
#endif //LCD_ENABLE

#ifdef ENCODER_ENABLE
extern RotaryEncoder encoder;
#endif //ENCODER_ENABLE

#ifdef MENU_ENABLE
typedef Menu_Item<uint8_t> Menu_u8;
#endif //MENU_ENABLE

#ifdef CO2_ENABLE
extern uint16_t CO2;
#endif //CO2_ENABLE

#ifdef BME280_ENABLE
extern float temp;
extern uint8_t hum;
extern uint16_t press;
#endif //BME280_ENABLE

#ifdef DS3231_ENABLE
extern uint8_t day;
extern uint8_t month;
extern uint8_t year;
extern uint8_t hour;
extern uint8_t minute;
extern uint8_t second;
#endif //DS3231_ENABLE

#endif //VARIABLES_HPP