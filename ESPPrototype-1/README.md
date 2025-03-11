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

## Versions
Current version: **v2.2.1**

### Version History
- **v2.0** - Migrated to ESP32 Microcontroller for its on-chip Wi-FI functionality, created separate folder.

- **v2.1** - Implemented FreeRTOS, separated tasks for sensors, UI and Wi-Fi. Sensors now read data to global variable, which can be accessed by the UI.
    - Created semaphores to manage global data access
    - Introduced new sensor, the BMP280, to calculate the temperature and altitude
    - Added HTTP Client
    - Fixed majority of bugs related to new RTOS implementation
    - Removed some unused libraries

- **v2.2** - Created the Backend Task to send the sensor data to the databse
    - The backend task uses an HTTP post to send a JSON package, which is received by the database.

- **v2.2.1** - Updated MAX3010 algorithm and created a separate task, as the previous implementation was blocking all the other sensors from updating and all the other tasks from running.
    - MAX3010 now updates the global variable in a separate task.
    - As the MAX3010 takes a long time to read all the 100 samples that it requires, we poll it occasionally and only update the buffer if there is new data. If there is no new data, we block the task for a few milliseconds so that other tasks can run instead.

## To Be Done
- Create function to update time in the UI.
- UI updating is currently done in one function. Consider separating into dynamic UI and static UI to update separately, which can save power.