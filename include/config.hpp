#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <Arduino.h>
#include <TaskManager.hpp>
#include <MCU_Mega_328.hpp>
#include <DS3231_RTC.hpp>
#include <Bosch_BME280_Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>
#include <Menu_Item.hpp>
#include "texts.hpp"
#include "Setup.hpp"
#include "Tasks.hpp"

using pin_number = const uint8_t;
using addr_8bit = const uint8_t;
using TaskManager_delay = const uint16_t;

//Config TaskManager
const uint8_t TASK_QUEUE_SIZE       = 5;
const uint8_t TIMESLOT_MS           = 16;

//Config pins
pin_number SENS_PWR_CTRL_PIN        = 13;
pin_number CO2_SENS_PWR_CTRL_PIN    = 12;
pin_number RTC_INT0_PIN             = 2;
pin_number ENCODER_BUTTON_INT1_PIN  = 3;
pin_number ENCODER_A_PIN            = 4;
pin_number ENCODER_B_PIN            = 5;

//Config USART baudrate
const uint16_t USART_BAUDRATE       = 9600;

//Config dummy delays
const uint16_t STARTUP_DELAY_MS     = 3000;

//Config TaskManager delays (x16ms)
TaskManager_delay DO_NOW            = 0;
TaskManager_delay POWER_UP_DELAY    = (uint16_t)(1600/TIMESLOT_MS);

//Config i2s addresses;
addr_8bit DS3231_I2C_ADDR           = 0x68;
addr_8bit BME280_I2C_ADDR           = 0x76;
addr_8bit LCD_I2C_ADDR              = 0x27;

//Config BME280

const float ALTITUDE                = 13.0F;
const float SEA_LEVEL_PRESSURE      = 249.67F;


//Config RTC
const uint16_t ALARM1_YEAR          = 0;
const uint16_t ALARM1_MONTH         = 0;
const uint16_t ALARM1_DATE          = 0;
const uint16_t ALARM1_HOUR          = 0;
const uint16_t ALARM1_MINUTE        = 0;
const uint16_t ALARM1_SECOND        = 0;

const uint16_t ALARM2_YEAR          = 0;
const uint16_t ALARM2_MONTH         = 0;
const uint16_t ALARM2_DATE          = 0;
const uint16_t ALARM2_HOUR          = 0;
const uint16_t ALARM2_MINUTE        = 30;

//Menu config
const uint8_t END_MENU_ITEM         =   1;
const uint8_t CLOCK_MENU_ITEMS      =   7;


#endif //#ifndef CONFIG_HPP