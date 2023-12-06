#include "Tasks.hpp"
#ifdef POWER_MANAGEMENT_ENABLE
void Tasks::System::periph_power_on(void)
{
    Serial.println(F("Wake up Neo..."));
    digitalWrite(SENS_PWR_CTRL_PIN, HIGH);

    OS.SetTask_(Tasks::Display::print_time, POWER_UP_DELAY);
}

void Tasks::System::periph_power_off(void)
{
    Serial.println(F("Sleeping..."));
    Serial.println();
    
    digitalWrite(SENS_PWR_CTRL_PIN, LOW);

    OS.SetTask_(sleep, DO_NOW);
}

void Tasks::System::sleep(void)
{
    DS3231_RTC::Control::enable_A1_INT();
    DS3231_RTC::Control::enable_A2_INT();

    MCU::Core::powerDown_All_Peripherials();
    MCU::Core::BrownOut_Disable();

    //MCU::Watchdog::Interrupt_Disable();
    MCU::Watchdog::Mode::stop();

    MCU::EXINT_::INT0_Enable();
    MCU::EXINT_::INT1_Enable();
    MCU::Sleep_::Enable();
    MCU::Sleep_::Go();
}

void Tasks::System::wakeUp_Prepare(void)
{
    MCU::Sleep_::Disable();
    MCU::EXINT_::INT0_Disable();
    MCU::EXINT_::INT1_Disable();
    MCU::Watchdog::Mode::interrupt();
    //MCU::Watchdog::Interrupt_Enable();
    Setup::Inner_periph::Power::Up_Used();
    DS3231_RTC::Control::disable_A1_INT();
    DS3231_RTC::Control::disable_A2_INT();
    DS3231_RTC::Control_Status::clear_Alarm_Events();

    OS.SetTask_(Tasks::System::periph_power_on, POWER_UP_DELAY);
}
#endif //POWER_MANAGEMENT_ENABLE