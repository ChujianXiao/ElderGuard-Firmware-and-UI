#include <Wire.h>
#include <DFRobot_BMP280.h>
#include <WiFi.h>

// BMP280 initialization
typedef DFRobot_BMP280_IIC BMP;
BMP bmp(&Wire, BMP::eSdoLow);
#define SEA_LEVEL_PRESSURE 1015.0f

// Forward declaration
void printBMPStatus(BMP::eStatus_t eStatus);

void initBMP280() {
    bmp.reset();
    Serial.println("Initializing BMP280...");
    while (bmp.begin() != BMP::eStatusOK) {
        Serial.println("BMP280 initialization failed.");
        printBMPStatus(bmp.lastOperateStatus);
    }
    Serial.println("BMP280 initialization successful.");
}

void readBMP280(float bmpData[2]) {
    bmpData[0] = bmp.getTemperature();
    uint32_t press = bmp.getPressure();
    bmpData[1] = bmp.calAltitude(1015.0, press);
}

void updateUI_BMP280(lv_timer_t *timer) {
  //Fetch the latest BMP280 data
  float temperature = 0.0;
  int altitude = 0;
  if (xSemaphoreTake(dataMutex, portMAX_DELAY)) {
      temperature = latestSensorData.bmp280Data[0]; // latestSensorData intialized in main.ino
      altitude = (int)latestSensorData.bmp280Data[1];
      xSemaphoreGive(dataMutex);  //Release the mutex
  }

  // Update the UI
  char buf[16];
  snprintf(buf, sizeof(buf), "%.1f°C", temperature);
  lv_label_set_text(ui_BodyTemp, buf); // ui_BodyTemp is defined in ui.c

  char buf2[16];
  snprintf(buf2, sizeof(buf2), "%d", altitude);
  lv_label_set_text(ui_Atmosphere, buf2); // Didn't change UI element to altitude yet, placeholder
}

void printBMPStatus(BMP::eStatus_t eStatus) {
    switch (eStatus) {
    case BMP::eStatusOK:
        Serial.println("Status: OK");
        break;
    case BMP::eStatusErr:
        Serial.println("Status: Unknown Error");
        break;
    case BMP::eStatusErrDeviceNotDetected:
        Serial.println("Status: Device Not Detected");
        break;
    case BMP::eStatusErrParameter:
        Serial.println("Status: Parameter Error");
        break;
    default:
        Serial.println("Status: Unknown");
        break;
    }
}
