#include "variables.hpp"

TaskManager5 OS;
BME::Bosch_BME280 bme(-1, -1, BME280_I2C_ADDR, SEA_LEVEL_PRESSURE, true);
LiquidCrystal_I2C lcd(LCD_I2C_ADDR, 16, 2);
RotaryEncoder encoder(ENCODER_A_PIN, ENCODER_B_PIN, RotaryEncoder::LatchMode::FOUR0);

uint8_t h=0;
Menu_u8 Hours(&encoder, &lcd, HOURS_SET_MENU_TEXT, h, static_cast<uint8_t>(0),static_cast<uint8_t>(23));
Menu_u8 Minutes(&encoder, &lcd, MINUTES_SET_MENU_TEXT, h, static_cast<uint8_t>(0),static_cast<uint8_t>(59));

ISR(WDT_vect){OS.TimerTaskService_();}
ISR(INT0_vect){Tasks::System::wakeUp_Prepare();}
ISR(INT1_vect){Tasks::System::wakeUp_Prepare();}

void setup() {
  Protective_startup_delay();
  Setup::Inner_periph::Power::Down_Unused();
  Setup::Inner_periph::EXINT();
  Setup::Outer_periph::IO_pins();
  
  OS.SetTask_(Tasks::System::periph_power_on, DO_NOW);
}

void loop() {
  OS.ProcessTaskQueue_();
  encoder.tick();
  Hours.print(0);
}

