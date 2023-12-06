#ifndef SETUP_HPP
#define SETUP_HPP

#include <Arduino.h>
#include "variables.hpp"

namespace Setup
{
    namespace Inner_periph
    {
        namespace Power
        {
            void Up_Used(void);
            void Down_Unused(void);
        }

        void TWI(void);
        void USART(void);
        void WDT(void);
        void EXINT(void);
    }

    namespace Outer_periph
    {
        namespace Power
        {
            void Sens_Down(void);
            void Sens_Up(void);
            void CO2_Sens_Up(void);
            void CO2_Sens_Down(void);
        }

        void IO_pins(void);
        void RTC(void);
        
    }
}

void Protective_startup_delay(void);

#endif // SETUP_HPP
