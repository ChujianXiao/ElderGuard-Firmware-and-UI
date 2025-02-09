#define UV_SENSOR_PIN 4 // GPIO04

// Initialize the UV sensor pin
void initUVSensor() {
  pinMode(UV_SENSOR_PIN, INPUT);
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

void readUVSensor(float uvData[2]) {
  int sensorValue = 0;

  sensorValue = analogRead(UV_SENSOR_PIN);

  float voltage = sensorValue * (3.3 / 1023.0); // Convert sensor value to voltage
  uvData[0] = voltage;
  uvData[1] = getUVIndex(voltage);
}

void updateUI_UVSensor(lv_timer_t *timer) {
  //Fetch the latest UV sensor data
  int uvIndex = 0;
  if (xSemaphoreTake(dataMutex, portMAX_DELAY)) {
      uvIndex = (int)latestSensorData.uvData[1]; // latestSensorData intialized in main.ino
      xSemaphoreGive(dataMutex);  // Release the mutex
  }

  //Update the UI
  char buf[32];
  snprintf(buf, sizeof(buf), "UV Level: %d", uvIndex);
  lv_label_set_text(ui_UVRays, buf);
}


