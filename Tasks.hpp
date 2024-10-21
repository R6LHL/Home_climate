#ifndef _TASKS_HPP
#define _TASKS_HPP

#include "variables.hpp"

namespace Tasks
{
  //--------------------------------------------------------------------------
	namespace Sensor
  {
    namespace CO2
    {
      void preheat_Awaiting(void);
      void read(void);
      void read_Temp(void);
    }

    namespace BME
    {
      void read(void);
    }
  }
//----------------------------------------------------------------------------
  namespace Output
  {
    namespace Print
    {
      namespace UART
      {
        void preheating(void);
        void mh_z(void);
        void bme(void);
      }

      namespace TFT_display
      {
        void mh_z(void);
        void bme(void);
        void preheating(void);
      }
    }  
    namespace LED
    {
      void green_Only(void);
      void yellow_Only(void);
      void red_Only(void);
      void all_Off(void);
      void blinking_red(void);
      void select(void);
    }
  }
}

#endif //_TASKS_HPP