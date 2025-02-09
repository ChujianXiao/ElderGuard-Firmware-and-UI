#include <MPU6050_tockn.h>
#include <Wire.h>

// MPU6050 Variables
MPU6050 mpu6050(Wire);
long timer = 0;
int steps = 0;
int distanceinonestep = 71; // Change it according to your stride length in cm
int distance;

void initMPU6050() {
  Serial.println("Initializing MPU6050...");
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  Serial.println("MPU6050 initialized.");
}

void readMPU6050(int mpuData[2]) {
  mpu6050.update();

  if (abs(mpu6050.getAccY()) > 0.2) {
    steps += 1;
    delay(350); // Prevent double-counting of steps
  }
  distance = steps * distanceinonestep / 100; // Calculate distance in meters

  mpuData[0] = steps;
  mpuData[1] = distance;
}

void updateUI_MPU6050(lv_timer_t *timer) {
  //Fetch the latest BMP280 data
  if (xSemaphoreTake(dataMutex, portMAX_DELAY)) {
      float steps = latestSensorData.mpu6050Data[0]; // latestSensorData intialized in main.ino
      int distance = latestSensorData.mpu6050Data[1];
      xSemaphoreGive(dataMutex);  //Release the mutex
  }

  // Update the UI
  char buf[16];
  snprintf(buf, sizeof(buf), "%.1f℃", steps);
  lv_label_set_text(ui_Steps, buf); // ui_BodyTemp is defined in ui.c

  char buf2[16];
  snprintf(buf2, sizeof(buf2), "%d", distance);
  lv_label_set_text(ui_Distance, buf2); // Didn't change UI element to altitude yet, placeholder
}