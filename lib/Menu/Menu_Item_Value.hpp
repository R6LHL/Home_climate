#ifndef MENU_ITEM_VALUE_HPP
#define MENU_ITEM_VALUE_HPP

/*! @brief                          Класс, описывающий переменную и её предельные значения
*   @param[in]      T_VALUE_TYPE    Тип значения
*   @param[in,out]  val             Ссылка на переменную
*   @param[in]      min             Минимальное значение переменной
*   @param[in]      max             Максимальное значение переменной
*/
template <typename T_VALUE_TYPE>
class Menu_Item_Value
{

public:
    Menu_Item_Value(T_VALUE_TYPE &val, const T_VALUE_TYPE min, const T_VALUE_TYPE max)
    {
        _value = val;
        _min_value = min;
        _max_value = max;
    }

    //T_VALUE_TYPE getValue(void)const{return _value;}
    
protected:
    T_VALUE_TYPE _value;
    T_VALUE_TYPE _min_value;
    T_VALUE_TYPE _max_value;

};

#endif //MENU_ITEM_VALUE_HPP