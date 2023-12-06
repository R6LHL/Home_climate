#ifndef MENU_ITEM_BASE_HPP
#define MENU_ITEM_BASE_HPP

#include <Arduino.h>
#include <avr/pgmspace.h>

/*! @brief                      Класс, описывающий строку для отображения на дисплее
*   @param[in] T_VALUE_TYPE     Тип значения
*   @param[in] text             Указатель на const char[]PROGMEM - строку
*/
class Menu_Item_Base
{

public:
    Menu_Item_Base(const char* text)
    {
        _text = (const __FlashStringHelper*)text;
    }

    enum Action{
        Down,
        Up,
        Enter,
        Escape,
    };

protected:
    const __FlashStringHelper* _text;    
};


#endif // MENU_ITEM_BASE_HPP