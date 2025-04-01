#define BATTERY_SENSOR_PIN 7 // GPIO04

float readBatteryVoltage() {
  float sensorValue = 0;

  sensorValue = analogRead(BATTERY_SENSOR_PIN);

  float voltage = sensorValue * (3.3 / 4095.0); //Assuming 12 bit ADC and 3.3V reference
  float actualVoltage = voltage *2; //100k-100k voltage divider
  return actualVoltage;
}

