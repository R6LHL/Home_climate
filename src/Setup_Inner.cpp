#include "Setup.hpp"
#include <MCU_Mega_328.hpp>

/*! @brief Включение питания нужной внутренней периферии контроллера
*/
void Setup::Inner_periph::Power::Up_Used(void){
    uint8_t byte_ = MCU::Core::PRR_::Get();
    byte_ &= ~(1<<PRTWI)|(1<<PRUSART0)|(1<<PRTIM0);
    MCU::Core::PRR_::Set(byte_);
}

/*! @brief Отключение питания ненужной внутренней периферии контроллера
*/
void Setup::Inner_periph::Power::Down_Unused(void){
    MCU::Core::PRR_::Set((1<<PRTIM2)|(1<<PRTIM1)|(1<<PRTIM0)|(1<<PRUSART0));
    MCU::AC_::powerDown();
}

/*! @brief Настройка TWI на частоту SCL 100кГц
*/
void Setup::Inner_periph::TWI(void){
    MCU::TWI_::TWBR_::Set(72);
    MCU::TWI_::Prescaler::Set_1(); // scl 100 kHz
}

/*! @brief Настройка Watchdog на прерывание каждые 16мс
*/
void Setup::Inner_periph::WDT(void){
    MCU::Watchdog::System_reset_disable();
    MCU::Watchdog::Prescaler::set_2048();
    MCU::Watchdog::Mode::interrupt();
    MCU::Watchdog::Interrupt_Enable();
}

/*! @brief Защитная задержка для возможности перепрошивки
            на случай, если питание USART где-то отключается совсем
*/
void Protective_startup_delay(void){
    MCU::Core::powerUp_All_Peripherials();
    delay(100);
    Serial.begin(USART_BAUDRATE);
    Serial.println();
    Serial.println(F("You can reprogramm it now..."));
    delay(STARTUP_DELAY_MS);
    Serial.println(F("Ok, let's work..."));
}

/*! @brief Настройка вызова внешних прерываний от низкого уровня
*/
void Setup::Inner_periph::EXINT(void){
    MCU::EXINT_::INT0_Mode::low_level();
    MCU::EXINT_::INT1_Mode::low_level();
}