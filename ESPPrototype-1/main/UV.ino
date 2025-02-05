void initUVSensor() {
  // No specific initialization required for analog UV sensor
  Serial.println("UV sensor initialized.");
}

void readUVSensor(lv_timer_t *timer) {
  int sensorValue = analogRead(A0); // Assuming UV sensor is connected to analog pin A0
  float voltage = sensorValue * (3.3 / 1023.0); // Convert sensor value to voltage
  int uvIndex = getUVIndex(voltage);

  // Update the UI
  char buf[32];
  snprintf(buf, sizeof(buf), "%d Lvl", uvIndex);
  lv_label_set_text(ui_UVRays, buf); // ui_UVRays is defined in ui.c

  Serial.print("UV Index: ");
  Serial.print(uvIndex);
  Serial.print(", Voltage: ");
  Serial.print(voltage, 3);
  Serial.println(" V");
}

int getUVIndex(float voltage) {
  if (voltage < 0.05) return 0;
  else if (voltage < 0.227) return 1;
  else if (voltage < 0.318) return 2;
  else if (voltage < 0.408) return 3;
  else if (voltage < 0.503) return 4;
  else if (voltage < 0.606) return 5;
  else if (voltage < 0.696) return 6;
  else if (voltage < 0.795) return 7;
  else if (voltage < 0.881) return 8;
  else if (voltage < 0.976) return 9;
  else if (voltage < 1.079) return 10;
  else return 11; // UV index beyond 10
}
