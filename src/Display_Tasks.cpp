#include "Tasks.hpp"

#ifdef LCD_ENABLE

#ifdef DS3231_ENABLE
void Tasks::Display::print_time(void)
{
    uint8_t hours = DS3231_RTC::Hours::get_Value();
    uint8_t minutes = DS3231_RTC::Minutes::get_Value();
    uint8_t seconds = DS3231_RTC::Seconds::get_Value();

    if (hours < 10)
    {
        Serial.print(F("0"));
    }
    Serial.print(hours);
    Serial.print(F(":"));

    if (minutes < 10)
    {
        Serial.print(F("0"));
    }
    
    Serial.print(minutes);
    Serial.print(F(":"));

    if (seconds < 10)
    {
        Serial.print(F("0"));
    }
    Serial.println(DS3231_RTC::Seconds::get_Value());

    OS.SetTask_(print_date, DO_NOW);
}

void Tasks::Display::print_date(void)
{
    uint8_t day = DS3231_RTC::Date::get_Value();
    uint8_t month = DS3231_RTC::Century_Month::get_Value();
    uint8_t year = DS3231_RTC::Year::get_Value();

    if (day < 10)
    {
        Serial.print(F("0"));
    }

    Serial.print(day);
    Serial.print(F("-"));

    if (month < 10)
    {
        Serial.print(F("0"));
    }

    Serial.print(month);
    Serial.print(F("-"));

    Serial.print(F("20"));
    Serial.println(year);

    OS.SetTask_(System::periph_power_off, DO_NOW);
}

#endif //DS3231_ENABLE

#ifdef CO2_ENABLE
void Tasks::Display::print_CO2(void)
{
    
}
#endif //CO2_ENABLE
#endif //LCD_ENABLE