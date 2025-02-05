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

void readMPU6050(lv_timer_t *timerUI) {
  mpu6050.update();

  if (millis() - timer > 1000) {
    Serial.print("\tAcceleration Y: ");
    Serial.print(mpu6050.getAccY());
    timer = millis(); // Reset the timer
  }

  if (abs(mpu6050.getAccY()) > 0.05) {
    steps += 1;
    delay(350); // Prevent double-counting of steps
  }

  distance = steps * distanceinonestep / 100; // Calculate distance in meters

  // Update the UI
  char buf[16];
  snprintf(buf, sizeof(buf), "%d", distance);
  lv_label_set_text(ui_Distance, buf); // ui_Distance is defined in ui.c

  char buf2[16];
  snprintf(buf2, sizeof(buf2), "%d", steps);
  lv_label_set_text(ui_Steps, buf2); // ui_Steps is defined in ui.c

  Serial.print("Steps: ");
  Serial.println(steps);

  Serial.print("Distance: ");
  Serial.println(distance,2); // Print distance with 2 decimal places
}
