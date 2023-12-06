#ifndef TASKS_HPP
#define TASKS_HPP

#include "variables.hpp"

namespace Tasks
{
    namespace System
    {
        void periph_power_on (void);
        void periph_power_off(void);
        void sleep(void);
        void wakeUp_Prepare(void);
    }

    namespace Display
    {
        void print_time(void);
        void print_date(void);
        void print_temperature(void);
        void print_humidity(void);
        void print_pressure(void);
        void print_CO2(void);
    }

    namespace Sensors
    {
        void get_CO2(void);
        void get_temp(void);
        void get_hum(void);
        void get_press(void);
    }
}

#endif //TASKS_HPP