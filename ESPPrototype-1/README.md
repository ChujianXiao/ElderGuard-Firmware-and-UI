# ESP32 Firmware

### Description
This folder contains the firmware for the ESP32 microcontroller, responsible for managing the UI and sensor data collection.

---

## Hardware Requirements
- **Microcontroller:** Tested using the ESP32-S3 WROOM1.
- **Power Supply:** 3.3V regulated
- **Peripherals:** 
  - Display - Using TFT_eSPI library, so only supports SPI displays. Tested using ST7789V2 display, with dimensions WIDTH 240* HEIGHT 280. If you want to use a different SPI display please adjust User_Setup.h and User_Setup_Select.h in the TFT_eSPI library to match your own device configurations.
  - Sensors - all sensors connected via I2C
    - GY511
    - MAX3010
    - MPU6050
    - BMP280
    - UV Sensor, model unknown

## Software Requirements
- **Toolchain:** Arduino IDE