#include <LiquidCrystal.h>

constexpr int TemperatureSensorReadPin = A0;
constexpr int SensorsPowerPin = 7;
constexpr int CoolingPlatePin = 6;

LiquidCrystal& GetLcd()
{
  constexpr int Rs = 12, En = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
  static LiquidCrystal lcd(Rs, En, D4, D5, D6, D7);
  return lcd;
}

float ReadTemperature(int temperature_sensor)
{
  constexpr float Voltage = 5;
  constexpr int AdcLevels = 1023;
  constexpr int RNominal = 10 * 1000;
  constexpr int Beta = 3950;
  constexpr int RSeries = 10 * 1000;
  constexpr float Kelvin0 = 273.15;
  constexpr float TNominal = 25 + Kelvin0;

  float vi = temperature_sensor * (Voltage / AdcLevels);
  float r = (Voltage - vi) * RSeries / vi;
  float temperature =  1 / (1 / TNominal + log(r / RNominal) / Beta) - Kelvin0;

  constexpr int HistoryLength = 8;
  static float temperature_history[HistoryLength];
  static int temperature_history_size = 0;
  static int temperature_history_write_index = 0;

  temperature_history[temperature_history_write_index] = temperature;
  temperature_history_write_index = (temperature_history_write_index + 1) % HistoryLength;
  temperature_history_size = min(temperature_history_size + 1, HistoryLength);

  float avg = 0;
  for (uint32_t i = 0; i < temperature_history_size; ++i)
  {
    avg += temperature_history[i];
  }
  avg /= temperature_history_size;

  return avg;
}

bool TriggerState(float value, float lower_bound, float upper_bound, bool curr_state)
{
  if (curr_state)
  {
    if (value <= lower_bound)
    {
      curr_state = false;
    }
  }
  else
  {
    if (value > upper_bound)
    {
      curr_state = true;
    }
  }

  return curr_state;
}

void setup()
{
  GetLcd().begin(16, 2);

  pinMode(CoolingPlatePin, OUTPUT);

  pinMode(SensorsPowerPin, OUTPUT);
  digitalWrite(SensorsPowerPin, LOW);
}

void loop()
{
  LiquidCrystal& lcd = GetLcd();

  digitalWrite(SensorsPowerPin, HIGH);
  delay(10);

  int temperature_sensor = analogRead(TemperatureSensorReadPin);

  digitalWrite(SensorsPowerPin, LOW);

  float temperature = ReadTemperature(temperature_sensor);

  lcd.setCursor(0, 0);
  lcd.print(temperature);
  lcd.setCursor(8, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000.0f);

  constexpr float temperature_lower_bound = 14;
  constexpr float temperature_upper_bound = temperature_lower_bound + 5;
  static bool cooling_plate_on = true;
  cooling_plate_on = TriggerState(temperature, temperature_lower_bound, temperature_upper_bound, cooling_plate_on); 
  digitalWrite(CoolingPlatePin, cooling_plate_on ? HIGH : LOW);

  delay(200);
}
