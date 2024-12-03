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

void readMAX3010(lv_timer_t *timer) {
  for (byte i = 0; i < 100; i++) {
    while (!particleSensor.available()) particleSensor.check();
    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
    particleSensor.nextSample();
  }

  // Update the UI
  char buf[16];
  snprintf(buf, sizeof(buf), "%d", heartRate);
  lv_label_set_text(ui_HeartRate, buf); // ui_HeartRate is defined in ui.c

  char buf2[16];
  snprintf(buf2, sizeof(buf2), "%d", spo2);
  lv_label_set_text(ui_BloodOxygen, buf2); // ui_BloodOxygen is defined in ui.c

  maxim_heart_rate_and_oxygen_saturation(irBuffer, 100, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
  Serial.print("Heart Rate: ");
  Serial.print(heartRate);
  Serial.print(" bpm, SpO2: ");
  Serial.print(spo2);
  Serial.println("%");
}
