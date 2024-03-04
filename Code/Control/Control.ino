#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

constexpr uint32_t DisplayAddr = 0x3C;

constexpr int TemperatureSensorReadPin = A0;
constexpr int SensorsPowerPin = 7;
constexpr int CoolingPlatePin = 6;

Adafruit_SSD1306& GetDisplay()
{
  constexpr uint32_t ScreenWidth = 128;
  constexpr uint32_t ScreenHeight = 64;
  constexpr int OledReset = -1;

  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
  static Adafruit_SSD1306 display(ScreenWidth, ScreenHeight, &Wire, OledReset);
  return display;
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
  Adafruit_SSD1306& display = GetDisplay();

  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, DisplayAddr)) {
    Serial.println("SSD1306 allocation failed");
    for (;;)
    {
    }
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.display();

  pinMode(CoolingPlatePin, OUTPUT);

  pinMode(SensorsPowerPin, OUTPUT);
  digitalWrite(SensorsPowerPin, LOW);
}

void loop()
{
  Adafruit_SSD1306& display = GetDisplay();

  digitalWrite(SensorsPowerPin, HIGH);
  delay(10);

  int temperature_sensor = analogRead(TemperatureSensorReadPin);

  digitalWrite(SensorsPowerPin, LOW);

  float temperature = ReadTemperature(temperature_sensor);

  display.clearDisplay();
  display.setCursor(0, 8);
  display.print(temperature);
  display.print(static_cast<char>(247));
  display.print("C");

  display.setCursor(0, 40);
  display.print(millis() / 1000.0f);
  display.display();

  constexpr float temperature_lower_bound = 14;
  constexpr float temperature_upper_bound = temperature_lower_bound + 5;
  static bool cooling_plate_on = true;
  cooling_plate_on = TriggerState(temperature, temperature_lower_bound, temperature_upper_bound, cooling_plate_on); 
  digitalWrite(CoolingPlatePin, cooling_plate_on ? HIGH : LOW);

  delay(500);
}
