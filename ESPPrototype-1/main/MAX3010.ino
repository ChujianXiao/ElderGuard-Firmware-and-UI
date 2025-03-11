#include "MAX30105.h"
#include "spo2_algorithm.h"

MAX30105 particleSensor;
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
uint16_t irBuffer[100], redBuffer[100];
#else
uint32_t irBuffer[100], redBuffer[100];
#endif
int32_t spo2, heartRate;
int8_t validSPO2, validHeartRate;

void initMAX3010() {
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30105 not found. Check wiring/power.");
    while (1);
  }
  particleSensor.setup(60, 4, 2, 100, 411, 4096);
}

//TO BE DONE -- ALGORITHM NEEDS TO BE UPDATED FOR EFFICIENCY PURPOSES
void readMAX3010(int maxData[2]) {
  int sampleCount = 0;
  const int totalSamples = 100;
  int roundStartSample = 0;

  while (sampleCount < totalSamples) {
      //Check how many samples are available in the sensor's FIFO buffer
      roundStartSample = sampleCount;
      //Loop to read all samples currently available in the FIFO
      while (particleSensor.available()) {
          redBuffer[sampleCount] = particleSensor.getRed();
          irBuffer[sampleCount] = particleSensor.getIR();
          particleSensor.nextSample();
          sampleCount++;

          if (sampleCount >= totalSamples)
              break;  // Stop once we have collected 100 samples
      }

      //Testing: see how many samples are collected per round
      int numSamples = sampleCount - roundStartSample;
      if(numSamples > 0){
        Serial.print("MAX3010 Sample Count Per Round:");
        Serial.println(numSamples);
        Serial.print("Total Sample Count:");
        Serial.println(sampleCount);
      }

      //If we haven't collected enough samples, check again after a short delay
      if (sampleCount < totalSamples) {
          particleSensor.check();  // Update sensor state
          vTaskDelay(pdMS_TO_TICKS(30));  // Yield to allow other tasks to run
      }
  }

  //Use algorithm from library
  maxim_heart_rate_and_oxygen_saturation(irBuffer, 100, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
  
  maxData[0] = heartRate;
  maxData[1] = spo2;
}

void updateUI_MAX3010(lv_timer_t *timer) {
  //Fetch the latest BMP280 data
  if (xSemaphoreTake(dataMutex, portMAX_DELAY)) {
      int heartRate = latestSensorData.max3010Data[0]; // latestSensorData intialized in main.ino
      int spo2 = latestSensorData.max3010Data[1];
      xSemaphoreGive(dataMutex);  //Release the mutex
  }

  // Update the UI
  char buf[16];
  snprintf(buf, sizeof(buf), "%d", heartRate);
  lv_label_set_text(ui_HeartRate, buf); // ui_HeartRate is defined in ui.c

  char buf2[16];
  snprintf(buf2, sizeof(buf2), "%d", spo2);
  lv_label_set_text(ui_BloodOxygen, buf2); // ui_BloodOxygen is defined in ui.c
}