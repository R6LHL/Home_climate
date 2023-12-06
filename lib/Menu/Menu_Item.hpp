#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include <RotaryEncoder.h>
#include <LiquidCrystal_I2C.h>
#include "Menu_Item_Base.hpp"
#include "Menu_Item_Value.hpp"

/*! @brief                      Класс, описывающий строку для отображения на дисплее
*                               и действия с переменной, связанной с ней.
*   @param[in] T_VALUE_TYPE     Тип значения
*   @param[in,out]  enc         Указатель на энкодер
*   @param[in,out]  lcd         Указатель на дисплей с I2C-интерфейсом
*   @param[in]      text        Указатель на const char[]PROGMEM - строку
*   @param[in,out]  val         Ссылка на переменную
*   @param[in]      min         Минимальное значение переменной
*   @param[in]      max         Максимальное значение переменной
*/
template <typename T_VALUE_TYPE>
class Menu_Item : public Menu_Item_Value<T_VALUE_TYPE>, public Menu_Item_Base
{

public:
    Menu_Item(RotaryEncoder* enc, LiquidCrystal_I2C* lcd, const char* text, T_VALUE_TYPE &val,
        const T_VALUE_TYPE min, const T_VALUE_TYPE max) : 
        Menu_Item_Value<T_VALUE_TYPE>(val, min, max),
        Menu_Item_Base(text)
    {
        _encoder = enc;
        _lcd = lcd;
    }

/*! @brief          Функция вывода строки на дисплей
*   @param[in] y    Y-Координата строки на дисплее
*/     
    void print(uint8_t y)
    {
        _lcd->setCursor(y,0);
        _lcd->print(_text);
        _lcd->print(Menu_Item_Value<T_VALUE_TYPE>::_value);
    }

protected:

    RotaryEncoder* _encoder;
    LiquidCrystal_I2C* _lcd;
};


#endif //MENU_ITEM_HPP