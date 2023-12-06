#include "variables.hpp"
#include <Wire.h>

TaskManager5 OS;

#ifdef BME280_ENABLE
BME::Bosch_BME280 bme(-1, -1, BME280_I2C_ADDR, SEA_LEVEL_PRESSURE, true);
#endif //BME280_ENABLE

#ifdef LCD_ENABLE
LiquidCrystal_I2C lcd(LCD_I2C_ADDR, 16, 2);
#endif //LCD_ENABLE

#ifdef ENCODER_ENABLE
RotaryEncoder encoder(ENCODER_A_PIN, ENCODER_B_PIN, RotaryEncoder::LatchMode::FOUR0);
#endif //ENCODER_ENABLE

#ifdef DS3231_ENABLE
uint8_t h=0;
Menu_u8 Hours(&encoder, &lcd, HOURS_SET_MENU_TEXT, h, static_cast<uint8_t>(0),static_cast<uint8_t>(23));
Menu_u8 Minutes(&encoder, &lcd, MINUTES_SET_MENU_TEXT, h, static_cast<uint8_t>(0),static_cast<uint8_t>(59));
#endif //DS3231_ENABLE

ISR(WDT_vect){OS.TimerTaskService_();}

#ifdef POWER_MANAGEMENT_ENABLE
ISR(INT0_vect){Tasks::System::wakeUp_Prepare();}
ISR(INT1_vect){Tasks::System::wakeUp_Prepare();}
#endif //POWER_MANAGEMENT_ENABLE

void setup() {

  Protective_startup_delay();
  
  Setup::Inner_periph::EXINT();
  Setup::Outer_periph::IO_pins();

  #ifdef POWER_MANAGEMENT_ENABLE
  Setup::Inner_periph::Power::Down_Unused();
   
  OS.SetTask_(Tasks::System::periph_power_on, DO_NOW);
  #endif // POWER_MANAGEMENT_ENABLE

  #ifdef CO2_ENABLE
  Serial.begin(USART_BAUDRATE);
  OS.SetTask_(Tasks::Sensors::get_CO2, DO_NOW);
  #endif //CO2_ENABLE
}

void loop() {
  OS.ProcessTaskQueue_();

  #ifdef ENCODER_ENABLE
  encoder.tick();
  #endif // ENCODER_ENABLE

  #ifdef DS3231_ENABLE
  Hours.print(0);
  #endif
}

