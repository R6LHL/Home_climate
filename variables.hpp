#ifndef __VARIABLES_HPP
#define __VARIABLES_HPP

#include "config.hpp"

extern volatile int co2_ppm;
extern volatile int co2_ppm_pwm;


extern volatile int8_t temperature;

#ifdef BME_280_ENABLED
extern volatile float humidity;
extern volatile float pressure;
extern Adafruit_BME280 bme280;
#endif // 
extern uint32_t iteration;


extern Adafruit_ST7735 display;

typedef TaskManager <TaskQueue_Size> TaskManager10;
extern TaskManager10 OS;

extern MHZ co2_sensor;


#endif //__VARIABLES_HPP;
