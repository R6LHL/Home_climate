#include "variables.hpp"

const uint16_t& offset = CO2::OutHome::village;

volatile int co2_ppm = offset;
volatile int co2_ppm_pwm = offset;

volatile int8_t temperature = 23;

#ifdef BME_280_ENABLED
volatile float humidity = Humidity::default_humidity;
volatile float pressure = Pressure::atm_pressure;
Adafruit_BME280 bme280;
#endif // BME

volatile uint8_t reset_reason = 0;

Adafruit_ST7735 display(Display_pin::cs, Display_pin::dc, Display_pin::mosi,
 Display_pin::sck, Display_pin::rst);

TaskManager10 OS;
MHZ co2_sensor(MHZ_pin::RX, MHZ_pin::TX,MHZ_pin::sensor_pwm, MHZ19B);

//////////////////////////////////////////////////////////////////////////////
//--------------------------INTERRUPTS--------------------------------------//
ISR(WDT_vect) 
{
  OS.TimerTaskService_();
  MCU::Watchdog::Mode::interrupt();
  MCU::Watchdog::System_reset_disable();
  MCU::Watchdog::Interrupt_Enable();
}
//////////////////////////////////////////////////////////////////////////////
//----------------------------SETUP-----------------------------------------//
//////////////////////////////////////////////////////////////////////////////
void setup() {

  MCU::Core::powerUp_All_Peripherials();
  MCU::AC_::powerDown();
  MCU::ADC_::powerDown();

  #ifndef ST7735_INDICATION_ENABLE
  MCU::SPI_::powerDown();
  #endif //ST7735_INDICATION_ENABLE

  #ifndef BME_280_ENABLED
  MCU::TWI_::powerDown();
  MCU::TC1_::powerDown();
  MCU::TC2_::powerDown();
  #endif

  #ifndef HARDWARE_UART_ENABLE
  MCU::USART_::powerDown();
  #endif //HARDWARE_UART_ENABLE 

  //Setup Serial
  #ifdef HARDWARE_UART_ENABLE
  Serial.begin(Serial_baudrate);
  #endif //HARDWARE_UART_ENABLE
  //Setup WDT
  MCU::Watchdog::Mode::interrupt();
  MCU::Watchdog::System_reset_disable();
  MCU::Watchdog::Prescaler::set_2048();
  MCU::Watchdog::Interrupt_Enable();
  //Setup pins
  #ifdef LED_INDICATION_ENABLE
  pinMode(LED_pin::normal, OUTPUT);
  digitalWrite(LED_pin::normal, LOW);

  pinMode(LED_pin::warning, OUTPUT);
  digitalWrite(LED_pin::warning, LOW);

  pinMode(LED_pin::danger, OUTPUT);
  digitalWrite(LED_pin::danger, LOW);

  #ifdef DEBUG_LED_ENABLE
  pinMode(LED_pin::debug, OUTPUT);
  digitalWrite(LED_pin::debug, LOW);
  #endif //DEBUG_LED_ENABLE
  #endif //LED_INDICATION_ENABLE

  //Setup CO2_sensor
  co2_sensor.setAutoCalibrate(false);
  co2_sensor.setRange(CO2_sensor_range);

  #ifdef BME_280_ENABLED
  bme280.begin(0x76, &Wire);
  bme280.setSampling(Adafruit_BME280::MODE_NORMAL,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X1, // humidity
                    Adafruit_BME280::FILTER_OFF   );
  #endif //
  
  reset_reason = MCU::Core::MCUSR_::Get();
  MCU::Core::MCUSR_::Set(0);

  #ifdef HARDWARE_UART_ENABLE
  Serial.print(RESET_REASON);
  Serial.println(reset_reason);
  #endif // HARDWARE_UART_ENABLE

  #ifdef ST7735_INDICATION_ENABLE
  display.initR(INITR_BLACKTAB);
  display.setRotation(1);
  display.setFont();
  display.fillScreen(ST7735_BLACK);
  display.setTextColor(ST7735_GREEN);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(RESET_REASON);
  display.println(reset_reason);
  #endif //ST7735_INDICATION_ENABLE

  // WAITING FOR SENSOR PREHEATING WITH FUNNY LEDS
  // (0)ENTER POINT INTO TASKS!!!
  OS.SetTask_(Tasks::Sensor::CO2::preheat_Awaiting, Delays::reset_display);

  #ifdef LED_INDICATION_ENABLE
  #ifdef DEBUG_LED_ENABLE
  OS.SetTask_(Tasks::Output::LED::debug_on, Delays::led_interval);
  #endif // DEBUG_LED_ENABLE
  #endif //LED_INDICATION_ENABLE
}

void loop() {OS.ProcessTaskQueue_();}
