#ifndef _CONFIG_HPP
#define _CONFIG_HPP

#define HARDWARE_UART_ENABLE
//#define DEBUG_LED_ENABLE
//#define LED_INDICATION_ENABLE
#define ST7735_INDICATION_ENABLE
#define BME_280_ENABLED
#define TEMP_FROM_MH_Z

#include <stdint.h>
#include <Arduino.h>
#include <MCU_Mega_328.hpp>
#include <SoftwareSerial.h>
#include <MHZ.h>
#include <Wire.h>

#ifdef ST7735_INDICATION_ENABLE
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#endif //ST7735_INDICATION_ENABLE

#ifdef BME_280_ENABLED
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#endif //BME_280_ENABLED

#include <TaskManager.hpp>
#include "Tasks.hpp"
#include "texts.hpp"

using pin_number = const uint8_t;
using addr_8bit = const uint8_t;
using TaskManager_delay = const uint16_t;
using ppm = const uint16_t;
using celsius = const uint8_t;
using percent = const float;
using hPa = const float;

namespace LED_pin
{
	pin_number normal = 4;
	pin_number warning = 7;
	pin_number danger = 8;

  pin_number debug = LED_BUILTIN;
}

#ifdef ST7735_INDICATION_ENABLE
namespace Display_pin
{
  pin_number cs = 4;
  pin_number dc = 7;
  pin_number rst = 8;
  pin_number mosi = 11;
  pin_number sck = 13;
}
#endif //ST7735_INDICATION_ENABLE

namespace MHZ_pin
{
  pin_number RX = 0;
  pin_number TX = 2;
  pin_number sensor_pwm = 3;
}
const uint16_t CO2_sensor_range = MHZ::MeasuringRange::RANGE_5K;

namespace Delays
{
  
  TaskManager_delay co2_check = 3750 * 2; //2min
  TaskManager_delay led_interval = 62;

  TaskManager_delay debug_led_on = 6;
  TaskManager_delay debug_led_off = 186;
  
  #ifdef ST7735_INDICATION_ENABLE
  TaskManager_delay reset_display = 186;
  TaskManager_delay display_renew = 3;
  #endif // ST7735_INDICATION_ENABLE

  TaskManager_delay now = 0;
  TaskManager_delay MHZ_preheating = 11250;
}

//__________________________CO2 Sensor settings________________________________
namespace CO2
{
   namespace OutHome
  {
    ppm village = 350;
    ppm small_city = 375;
    ppm big_city = 400;
  }

  namespace Threshold
  {
    ppm normal = 600 + OutHome::village;
    ppm warning = 800 + OutHome::village;
    ppm danger = 1000 + OutHome::village;
    ppm critical = 2000; 
  }
  const int8_t temp_offset = 3;
  extern const uint16_t& offset;
}
//_____________________________________________________________________________

namespace Temperature
{
  namespace Threshold
  {
    celsius green = 23;
    celsius blue = 21;
    celsius red = 25;
  } 
  const float default_temp = 23;
}

#ifdef BME_280_ENABLED
namespace Humidity
{

  namespace Threshold
  {
    percent low = 30.0;
    percent high = 45.0;
  }
  const float default_humidity = 50.0;
}

namespace Pressure
{
  namespace Threshold
  {
    hPa low  = 99.99;
    hPa blue = 101.05;
    hPa yellow = 101.65;
    hPa high = 101.99;
  }
const float atm_pressure = 1013.25;
const float press_divider = 1000.0;
}
#endif //#ifdef BME_280_ENABLED

#ifdef ST7735_INDICATION_ENABLE
namespace Text_settings
{
  namespace Size
  {
    const uint8_t measure_name = 2;

    #ifndef BME_280_ENABLED
    const uint8_t CO2 = 4;
    const uint8_t temp = 6;
    #else 
    const uint8_t CO2 = 2;
    const uint8_t temp = 2;
    const uint8_t hum = 2;
    const uint8_t press = 2;
    #endif
  }

  namespace Color
  {
    const uint16_t measure_name = ST7735_CYAN;
    const uint16_t red = ST7735_RED;
    const uint16_t orange = ST7735_ORANGE;
    const uint16_t yellow = ST7735_YELLOW;
    const uint16_t green = ST7735_GREEN;
    const uint16_t cyan = ST7735_CYAN;
    const uint16_t blue = ST7735_BLUE;
    const uint16_t magenta = ST7735_MAGENTA;
    const uint16_t black = ST7735_BLACK;
    const uint16_t white = ST7735_WHITE;
  }

  namespace Pos
  {
    //___________________________space 6 lines_________________________________
    const uint8_t line_1 = 10;
    const uint8_t line_2 = 18;
    const uint8_t line_3 = 30;
    const uint8_t line_4 = 42;
    const uint8_t line_5 = 56;
    const uint8_t line_6 = 68;
    const uint8_t line_7 = 80;
    const uint8_t line_8 = 92;
    const uint8_t line_9 = 104;
    const uint8_t line_10 = 116;


    const uint8_t column_1 = 0;
    const uint8_t column_2 = 47;
    const uint8_t column_3 = 123;
  }
}
#endif

//------------------HARDWARE_UART config---------------------------------------------
const uint16_t Serial_baudrate = 9600;

//------------------TaskManager config----------------------------------------
const uint8_t TaskQueue_Size = 5;

#endif // _CONFIG_HPP