#include "Arduino.h"
#include "Tasks.hpp"

void Tasks::Sensor::CO2::preheat_Awaiting(void)
{
 //(1)Точка входа в светодиодную индикацию прогрева датчика
 #ifdef HARDWARE_UART_ENABLE
 OS.SetTask_(Tasks::Output::Print::UART::preheating, Delays::now);
 #endif //HARDWARE_UART_ENABLE
  
 #ifdef ST7735_INDICATION_ENABLE
 //(1.1)ТОчка входа на индикацию на дисплее
 OS.SetTask_(Tasks::Output::Print::TFT_display::preheating, Delays::now);
 #endif // 

 #ifdef LED_INDICATION_ENABLE
 OS.SetTask_(Tasks::Output::LED::green_Only, Delays::now);
 ex++;
 OS.SetTask_(Tasks::Output::LED::yellow_Only, Delays::led_interval * ex);
 ex++;
 OS.SetTask_(Tasks::Output::LED::red_Only, Delays::led_interval * ex);
 ex++;
 OS.SetTask_(Tasks::Output::LED::all_Off, Delays::led_interval * ex);
 #endif // LED_INDICATION_ENABLE

 //(2) Точка входа в чтение показаний СО2
 OS.SetTask_(Tasks::Sensor::CO2::read, Delays::MHZ_preheating);
}

void Tasks::Sensor::CO2::read(void)
{
  OS.DeleteTask_(Tasks::Output::Print::UART::preheating);
  
  co2_ppm = co2_sensor.readCO2UART();

  #ifndef BME_280_ENABLED
  temperature = co2_sensor.getLastTemperature() + ::CO2::temp_offset;
  #endif

  #ifdef TEMP_FROM_MH_Z
  temperature = co2_sensor.getLastTemperature() + ::CO2::temp_offset;
  #endif

  co2_ppm_pwm = co2_sensor.readCO2PWM();
  //co2_ppm = (co2_ppm + co2_ppm_pwm) / 2;
  //(2.1) Точка входа в отображение показаний СО2
  #ifdef HARDWARE_UART_ENABLE
  OS.SetTask_(Tasks::Output::Print::UART::mh_z, Delays::now);
  #endif // HARDWARE_UART_ENABLE
  
  //(2.2) Точка входа в отображение показаний СО2
  #ifdef LED_INDICATION_ENABLE
  OS.SetTask_(Tasks::Output::LED::select, Delays::now);
  #endif // LED_INDICATION_ENABLE

  #ifdef ST7735_INDICATION_ENABLE
  //(2.3) Точка входа в отображение показаний СО2
  #ifdef BME_280_ENABLED
  OS.SetTask_(Tasks::Sensor::BME::read, Delays::now);
  OS.SetTask_(Tasks::Output::Print::TFT_display::mh_z, Delays::now + 1);
  #else
  OS.SetTask_(Tasks::Output::Print::TFT_display::mh_z, Delays::now);
  #endif // BME_280_ENABLED
  #endif // ST7735_INDICATION_ENABLE
}

void Tasks::Sensor::BME::read(void)
{
  #ifndef TEMP_FROM_MH_Z
  temperature = bme280.readTemperature();
  #endif
  humidity = bme280.readHumidity();
  pressure = bme280.readPressure() / Pressure::press_divider;
  
  OS.SetTask_(Tasks::Output::Print::TFT_display::bme, Delays::now);
}