#include <Arduino.h>
#include "variables.hpp"
#include "Setup.hpp"
#include <DS3231_RTC.hpp>

/*! @brief Отключение питания датчиков, кроме СО2
*/
void Setup::Outer_periph::Power::Sens_Down(void){
    digitalWrite(SENS_PWR_CTRL_PIN, LOW);
}

/*! @brief Включение питания датчиков, кроме СО2
*/
void Setup::Outer_periph::Power::Sens_Up(void){
    digitalWrite(SENS_PWR_CTRL_PIN, HIGH);
}

/*! @brief Выключение питания датчика СО2
*/
void Setup::Outer_periph::Power::CO2_Sens_Down(void){
    digitalWrite(CO2_SENS_PWR_CTRL_PIN, LOW);
}

/*! @brief Включение питания датчика СО2
*/
void Setup::Outer_periph::Power::CO2_Sens_Up(void){
    digitalWrite(CO2_SENS_PWR_CTRL_PIN, HIGH);
}

/*! @brief Настройка пинов контроллера
*/
void Setup::Outer_periph::IO_pins(void){
    pinMode(CO2_SENS_PWR_CTRL_PIN, OUTPUT);
    pinMode(SENS_PWR_CTRL_PIN, OUTPUT);
    pinMode(RTC_INT0_PIN, INPUT_PULLUP);
    pinMode(ENCODER_BUTTON_INT1_PIN, INPUT_PULLUP);
    pinMode(ENCODER_A_PIN, INPUT_PULLUP);
    pinMode(ENCODER_B_PIN, INPUT_PULLUP);
}

/*! @brief Установка часов на прерывание в 00 и 30 минут каждый час
*/
void Setup::Outer_periph::RTC(void){
    DS3231_RTC::Control::disable_A1_INT();
    DS3231_RTC::Control::disable_A2_INT();
    DS3231_RTC::Control::disable_BBSQW();
    DS3231_RTC::Control::disable_EOSC();
    DS3231_RTC::Control_Status::disable_32kHz();
    
    #ifdef DEBUG_TIME_SET
    DS3231_RTC::Year::set_Value(22);
    DS3231_RTC::Century_Month::set_Value(0, BUILD_MONTH);
    DS3231_RTC::Date::set_Value(BUILD_DAY);

    DS3231_RTC::Hours::set_24_mode();
    DS3231_RTC::Hours::set_Value(14);

    DS3231_RTC::Minutes::set_Value(0);
    DS3231_RTC::Seconds::set_Value(0);
    #endif //DEBUG_TIME_SET

    DS3231_RTC::Alarm1Day_Date::set_a1m4();
    DS3231_RTC::Alarm1Hours::set_a1m3();

    DS3231_RTC::Alarm1Minutes::set_Value(0);
    DS3231_RTC::Alarm1Minutes::clear_a1m2();
    //DS3231_RTC::Alarm1Minutes::set_a1m2();

    DS3231_RTC::Alarm1Seconds::set_Value(0);
    //DS3231_RTC::Alarm1Seconds::set_a1m1();
    DS3231_RTC::Alarm1Seconds::clear_a1m1();

    DS3231_RTC::Alarm2Day_Date::clear_a2m4();
    DS3231_RTC::Alarm2Hours::clear_a2m3();

    DS3231_RTC::Alarm2Minutes::clear_a2m2();
    DS3231_RTC::Alarm1Minutes::set_Value(30);

}