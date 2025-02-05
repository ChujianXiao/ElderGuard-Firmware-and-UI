/*Don't forget to set Sketchbook location in File/Preferences to the path of this project (the parent foder of this INO file)*/

#include <Wire.h>
#include <SPI.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>

void setup() {
  Serial.begin(115200);
  Wire.begin(8,9); //I2C Ports defined at 8 and 9

  // Initialize Wi-Fi
  //setupWiFi();
  Serial.println("Checking default SPI bus...");

  //Initialize all sensors
  initGY511();
  delay(500);
  initMAX3010();
  initMPU6050();
  //initBMP280();
  //initUVSensor();
  //Initialize the UI
  initUI();
}

void loop() {
  //testCompass();
  // Read and display data from each sensor
  // readGY511();
  // readMAX3010();
  // readMPU6050();
  // //readSPL06();
  // //readUVSensor();
  lv_task_handler(); // Handle LVGL tasks

  delay(50); // General delay for stability
}
