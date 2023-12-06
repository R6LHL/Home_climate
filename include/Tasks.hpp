#ifndef TASKS_HPP
#define TASKS_HPP

#include "variables.hpp"

namespace Tasks
{
    namespace System
    {
        #ifdef POWER_MANAGEMENT_ENABLE
        void periph_power_on (void);
        void periph_power_off(void);
        void sleep(void);
        void wakeUp_Prepare(void);
        #endif //POWER_MANAGEMENT_ENABLE
    }

    namespace Display
    {
        #ifdef LCD_ENABLE

        #ifdef DS3231_ENABLE
        void print_time(void);
        void print_date(void);
        #endif //DS3231_ENABLE

        #ifdef BME280_ENABLE
        void print_temperature(void);
        void print_humidity(void);
        void print_pressure(void);
        #endif //BME280_ENABLE

        #ifdef CO2_ENABLE
        void print_CO2(void);
        #endif //CO2_ENABLE

        #endif //LCD_ENABLE
    }

    namespace Sensors
    {
        //#ifdef CO2_ENABLE
        void get_CO2(void);
        //#endif // CO2_ENABLE
    
        #ifdef BME280_ENABLE
        void get_temp(void);
        void get_hum(void);
        void get_press(void);
        #endif //BME280_ENABLE
    }
}

#endif //TASKS_HPP