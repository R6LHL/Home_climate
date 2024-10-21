#include "HardwareSerial.h"
#include "Tasks.hpp"

void Tasks::Output::LED::select(void)
{
  if (co2_ppm <= CO2::Threshold::normal)
  {
    // (3*) Отключение мигания красным
    //OS.DeleteTask_(Tasks::Output::LED::blinking_red);
    OS.SetTask_(Tasks::Output::LED::green_Only, Delays::now);
  }
  else if ((co2_ppm > CO2::Threshold::normal) && (co2_ppm < CO2::Threshold::danger))
  {
    // (3*) Отключение мигания красным
    //OS.DeleteTask_(Tasks::Output::LED::blinking_red);
    OS.SetTask_(Tasks::Output::LED::yellow_Only, Delays::now);
  }
  else 
  {
    // (3*) Отключение мигания красным
    //OS.DeleteTask_(Tasks::Output::LED::blinking_red);
    OS.SetTask_(Tasks::Output::LED::red_Only, Delays::now);
  }
}

void Tasks::Output::Print::UART::preheating(void)
{
  uint8_t ex = 0;
  Serial.println(PREHEATING_TEXT);
}

#ifdef LED_INDICATION_ENABLE
void Tasks::Output::LED::green_Only(void)
{
  digitalWrite(LED_pin::normal, HIGH);
  digitalWrite(LED_pin::warning, LOW);
  digitalWrite(LED_pin::danger, LOW);
}

void Tasks::Output::LED::yellow_Only(void)
{
  digitalWrite(LED_pin::warning, HIGH);
  digitalWrite(LED_pin::normal, LOW);
  digitalWrite(LED_pin::danger, LOW);
}

void Tasks::Output::LED::red_Only(void)
{
  digitalWrite(LED_pin::danger, HIGH);
  digitalWrite(LED_pin::warning, LOW);
  digitalWrite(LED_pin::normal, LOW);
}

void Tasks::Output::LED::all_Off(void)
{
  digitalWrite(LED_pin::normal, LOW);
  digitalWrite(LED_pin::warning, LOW);
  digitalWrite(LED_pin::danger, LOW);
}

void Tasks::Output::LED::blinking_red(void)
{
  OS.SetTask_(Tasks::Output::LED::red_Only, (Delays::led_interval)/4);
  OS.SetTask_(Tasks::Output::LED::all_Off, (Delays::led_interval)/2);
}
#endif //LED_INDICATION_ENABLE

void Tasks::Output::Print::UART::mh_z(void)
{  
  if (co2_ppm == STATUS_NOT_READY) 
  {
    Serial.println(F("!!! Sensor is not ready !!!"));
    co2_ppm = co2_ppm_pwm;
  }
  else if (co2_ppm == STATUS_NO_RESPONSE)
  {
    Serial.println(F("!!! Sensor is not responding !!!"));
    co2_ppm = co2_ppm_pwm;
  }
  else if (co2_ppm == STATUS_INCOMPLETE)
  {
    Serial.println(F("!!! Incomplete data !!!"));
    co2_ppm = co2_ppm_pwm;
  }
  else if (co2_ppm == STATUS_CHECKSUM_MISMATCH)
  {
    Serial.println(F("!!! Bad CRC !!!"));
    co2_ppm = co2_ppm_pwm;
  }
  else
  {
    #ifndef BME_280_ENABLED
    Serial.print(co2_ppm);
    Serial.print(SPACE_TEXT);
    Serail.println(temperature);
    #else
    Serial.print(co2_ppm);
    Serial.print(SPACE_TEXT);
    #endif
  }

  #ifndef BME_280_ENABLED
  //(2) Возврат на точку входа за новыми показаниями
  OS.SetTask_(Tasks::Sensor::CO2::read, Delays::co2_check);
  #else
  OS.SetTask_(Tasks::Output::Print::UART::bme, Delays::now);
  #endif
}

void Tasks::Output::Print::UART::bme(void)
{
  Serial.print(temperature);
  Serial.print(SPACE_TEXT);
  Serial.print(humidity);
  Serial.print(SPACE_TEXT);
  Serial.println(pressure);
  OS.SetTask_(Tasks::Sensor::CO2::read, Delays::co2_check);
}

void Tasks::Output::Print::TFT_display::preheating(void)
{
  display.setCursor(0, 12);
  display.setTextSize(1);
  display.setTextColor(ST7735_ORANGE);
  display.print(PREHEATING_TEXT);
}

void Tasks::Output::Print::TFT_display::mh_z(void)
{
  //(2.3)
  display.fillScreen(ST7735_BLACK);

  #ifndef  BME_280_ENABLED
  display.setCursor(0, 12);
  display.setTextSize(2);
  display.setTextColor(ST7735_CYAN);
  display.print(CO2_TEXT);
  display.setCursor(0, 24);
  display.print(PPM_TEXT);

  display.setTextSize(4);
  //..................CO2___Color selection..................................................
  if (co2_ppm <= CO2::Threshold::normal){display.setTextColor(ST7735_GREEN);}
  else if ((co2_ppm > CO2::Threshold::normal) && (co2_ppm < CO2::Threshold::danger))
  {display.setTextColor(ST7735_YELLOW);}
  else {display.setTextColor(ST7735_RED);}
  //....................................................................................
  display.setCursor(54, 12);
  display.print(co2_ppm);

  #else
  display.setCursor(Text_settings::Pos::column_1, Text_settings::Pos::line_1);
  display.setTextSize(Text_settings::Size::measure_name);
  display.setTextColor(Text_settings::Color::measure_name);
  display.print(CO2_TEXT);
  display.setCursor(Text_settings::Pos::column_3, Text_settings::Pos::line_1);
  display.print(PPM_TEXT);

  display.setTextSize(Text_settings::Size::CO2);
  display.setCursor(Text_settings::Pos::column_2, Text_settings::Pos::line_1);

  //..................CO2___Color selection..................................................
  if (co2_ppm <= CO2::Threshold::normal){display.setTextColor(Text_settings::Color::green);}
  else if ((co2_ppm > CO2::Threshold::normal) && (co2_ppm < CO2::Threshold::danger))
  {display.setTextColor(Text_settings::Color::yellow);}
  else {display.setTextColor(Text_settings::Color::red);}
  display.print(co2_ppm);
  #endif // BME_280_ENABLED

  //(2.3)
  #ifdef TEMP_FROM_MH_Z
  display.setCursor(Text_settings::Pos::column_1, Text_settings::Pos::line_4);
  display.setTextSize(Text_settings::Size::measure_name);
  display.setTextColor(Text_settings::Color::measure_name);
  display.print(TEMP_TEXT);
  display.setCursor(Text_settings::Pos::column_3, Text_settings::Pos::line_4);
  display.print(dC_TEXT);
  display.setTextSize(Text_settings::Size::temp);
  //..................Temperature___Color selection.....................................
  if(temperature < Temperature::Threshold::blue) {display.setTextColor(Text_settings::Color::blue);}
  else if (temperature >= Temperature::Threshold::red){display.setTextColor(Text_settings::Color::red);}
  else {display.setTextColor(Text_settings::Color::green);}
  //....................................................................................
  display.setCursor(Text_settings::Pos::column_2, Text_settings::Pos::line_4);
  display.print(temperature);
  //(2)Возврат на точку входа за новыми показаниями
  OS.SetTask_(Tasks::Sensor::CO2::read, Delays::co2_check);
  #endif

  #ifndef BME_280_ENABLED
    OS.SetTask_(Tasks::Sensor::CO2::read, Delays::co2_check);
    #if defined (TEMP_FROM_MH_Z)
    OS.SetTask_(Tasks::Output::Print::TFT_display::bme, Delays::now);
    #endif //defined (TEMP_FROM_MH_Z)
  #else 
  OS.SetTask_(Tasks::Output::Print::TFT_display::bme, Delays::now);
  #endif //BME_280_ENABLED
}

void Tasks::Output::Print::TFT_display::bme(void)
{
  // Temperature print
  display.setTextSize(Text_settings::Size::temp);
  display.setTextColor(Text_settings::Color::measure_name);
  display.setCursor(Text_settings::Pos::column_1, Text_settings::Pos::line_4);
  display.print(TEMP_TEXT);
  display.setCursor(Text_settings::Pos::column_3, Text_settings::Pos::line_4);
  display.print(dC_TEXT);

  display.setTextSize(Text_settings::Size::temp);
  //..................Temperature___Color selection.....................................
  if(temperature < Temperature::Threshold::blue) {display.setTextColor(Text_settings::Color::blue);}
  else if (temperature >= Temperature::Threshold::red){display.setTextColor(Text_settings::Color::red);}
  else {display.setTextColor(Text_settings::Color::green);}
  //....................................................................................
  display.setCursor(Text_settings::Pos::column_2, Text_settings::Pos::line_4);
  display.print(temperature);

  // Humidity print
  display.setTextSize(Text_settings::Size::temp);
  display.setTextColor(Text_settings::Color::measure_name);
  display.setCursor(Text_settings::Pos::column_1, Text_settings::Pos::line_6);
  display.print(HUM_TEXT);
  display.setCursor(Text_settings::Pos::column_3, Text_settings::Pos::line_6);
  display.print(PRECENT_TEXT);

  display.setTextSize(Text_settings::Size::hum);
  //..................Humidity___Color selection.....................................
  if(humidity < Humidity::Threshold::low) {display.setTextColor(Text_settings::Color::orange);}
  else if (humidity >= Humidity::Threshold::high){display.setTextColor(Text_settings::Color::blue);}
  else {display.setTextColor(Text_settings::Color::green);}
  //....................................................................................
  display.setCursor(Text_settings::Pos::column_2, Text_settings::Pos::line_6);
  display.print(humidity);

  //Pressure print
  display.setTextSize(Text_settings::Size::temp);
  display.setTextColor(Text_settings::Color::measure_name);
  display.setCursor(Text_settings::Pos::column_1, Text_settings::Pos::line_8);
  display.print(PRS_TEXT);
  display.setCursor(Text_settings::Pos::column_3, Text_settings::Pos::line_8);
  display.print(KPA_TEXT);

  display.setTextSize(Text_settings::Size::hum);
  //..................Pressure___Color selection.....................................
  if(pressure < Pressure::Threshold::low) {display.setTextColor(Text_settings::Color::magenta);}
  else if ((pressure <= Pressure::Threshold::blue) && (pressure >= Pressure::Threshold::low))
                                            {display.setTextColor(Text_settings::Color::blue);}
  else if ((pressure >= Pressure::Threshold::yellow) && (pressure <= Pressure::Threshold::high))
                                            {display.setTextColor(Text_settings::Color::yellow);}
  else if (pressure >= Pressure::Threshold::high){display.setTextColor(Text_settings::Color::red);}
  else {display.setTextColor(Text_settings::Color::green);}
  //....................................................................................
  display.setCursor(Text_settings::Pos::column_2, Text_settings::Pos::line_8);
  display.print(pressure);

  OS.SetTask_(Tasks::Sensor::CO2::read, Delays::co2_check);
}