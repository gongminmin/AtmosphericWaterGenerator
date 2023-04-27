#include <LiquidCrystal.h>

constexpr float Voltage = 5;
constexpr int AdcLevels = 1023;
constexpr int RThermistor = 10 * 1000;
constexpr int Beta = 3950;
constexpr int RSeries = 10 * 1000;
constexpr float Kelvin0 = 273.15;
constexpr float RoomTemperature = 25 + Kelvin0;

constexpr int HistoryLength = 10;
float temperature_history[HistoryLength];
int temperature_history_size = 0;
int temperature_history_write_index = 0;

constexpr int Rs = 12, E = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(Rs, E, D4, D5, D6, D7);

void setup()
{
  lcd.begin(16, 2);
}

void loop()
{
  float vi = analogRead(A0) * (Voltage / AdcLevels);
  float r = (Voltage - vi) * RSeries / vi;
  float temperature =  1 / ((1 / RoomTemperature) + ((log(r / RThermistor)) / Beta)) - Kelvin0;

  temperature_history[temperature_history_write_index] = temperature;
  temperature_history_write_index = (temperature_history_write_index + 1) % HistoryLength;
  temperature_history_size = min(temperature_history_size + 1, HistoryLength);

  float avg_temperature = 0;
  for (uint32_t i = 0; i < temperature_history_size; ++i)
  {
    avg_temperature += temperature_history[i];
  }
  avg_temperature /= temperature_history_size;

  lcd.setCursor(0, 0);
  lcd.print(avg_temperature);
  lcd.setCursor(8, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000.0f);

  delay(100);
}
