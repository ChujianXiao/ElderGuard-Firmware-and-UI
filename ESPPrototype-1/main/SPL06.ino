// #include <SPI.h>

// #define MOSI_PIN PA7    // Adjust according to your hardware
// #define MISO_PIN PA6
// #define SCLK_PIN PA5
// #define CS_PIN   PD14

// SPIClass etx_spi(MOSI_PIN, MISO_PIN, SCLK_PIN);

// struct CalibrationData {
//   int16_t c0, c1;
//   int32_t c00, c10;
//   int16_t c01, c11, c20, c21, c30;
// } calib;

// const float kT = 7864320.0; // Temperature scaling factor (oversampling x8)
// const float kP = 7864320.0; // Pressure scaling factor (oversampling x8)

// void initSPL06() {
//   Serial.println("Initializing SPL06...");
  
//   // Initialize SPI
//   etx_spi.begin();
//   etx_spi.setDataMode(SPI_MODE3); // SPL06-001 uses SPI Mode 3
//   etx_spi.setBitOrder(MSBFIRST);
//   etx_spi.setClockDivider(SPI_CLOCK_DIV8);

//   pinMode(CS_PIN, OUTPUT);
//   digitalWrite(CS_PIN, HIGH);
//   Serial.println("SPI Initialized.");

//   // Verify Device ID
//   uint8_t device_id = readRegister(0x0D);
//   Serial.print("Device ID: 0x");
//   Serial.println(device_id, HEX);

//   if (device_id != 0x10) {
//     Serial.println("Invalid Device ID! Check sensor wiring or configuration.");
//     while (1); // Stop execution if device ID is invalid
//   }

//   Serial.println("Device ID verified. Configuring sensor...");
//   configureSensor();
//   readCalibrationCoefficients();
//   Serial.println("SPL06 initialization complete.");
// }

// void readSPL06(lv_timer_t *timer) {

//   // Read raw temperature
//   int32_t raw_temp = readRawData(0x03);
//   // Read raw pressure
//   int32_t raw_pressure = readRawData(0x00);

//   // Scale raw data
//   float Traw_sc = raw_temp / kT; // Scaled temperature
//   float Praw_sc = raw_pressure / kP; // Scaled pressure

//   // Compensated temperature
//   float Tcomp = calib.c0 * 0.5 + calib.c1 * Traw_sc;

//   // Compensated pressure
//   float Pcomp = calib.c00
//               + Praw_sc * (calib.c10 + Praw_sc * (calib.c20 + Praw_sc * calib.c30))
//               + Traw_sc * calib.c01
//               + Traw_sc * Praw_sc * (calib.c11 + Praw_sc * calib.c21);
  
//   // Update the UI
//   char buf[32];
//   snprintf(buf, sizeof(buf), "%d °C", Tcomp);
//   lv_label_set_text(ui_BodyTemp, buf); // ui_BodyTemp is defined in ui.c

//   char buf2[32];
//   snprintf(buf, sizeof(buf), "%d Pa", Pcomp);
//   lv_label_set_text(ui_Atmosphere, buf); // ui_Atmosphere is defined in ui.c

//   // Print results
//   //Serial.println("=== Sensor Data ===");
//   Serial.print("Raw Temperature: ");
//   Serial.println(raw_temp);
//   Serial.print("Raw Pressure: ");
//   Serial.println(raw_pressure);
//   Serial.print("Temperature: ");
//   Serial.print(Tcomp);
//   Serial.println(" °C");
//   Serial.print("Pressure: ");
//   Serial.print(Pcomp);
//   Serial.println(" Pa");
// }

// void configureSensor() {
//   writeRegister(0x06, 0x03); // Pressure configuration (oversampling x8)
//   writeRegister(0x07, 0x83); // Temperature configuration (oversampling x8)
//   writeRegister(0x08, 0xC7); // Continuous measurement mode
//   Serial.println("Sensor configuration complete.");
// }

// void readCalibrationCoefficients() {
//   uint8_t raw[18];

//   // Read all calibration registers (0x10 to 0x21)
//   for (uint8_t i = 0; i < 18; i++) {
//     raw[i] = readRegister(0x10 + i);
//   }

//   // Parse coefficients
//   calib.c0 = ((int16_t)raw[0] << 4) | (raw[1] >> 4);
//   if (calib.c0 & 0x0800) calib.c0 |= 0xF000;

//   calib.c1 = ((int16_t)(raw[1] & 0x0F) << 8) | raw[2];
//   if (calib.c1 & 0x0800) calib.c1 |= 0xF000;

//   calib.c00 = ((int32_t)raw[3] << 12) | ((int32_t)raw[4] << 4) | (raw[5] >> 4);
//   if (calib.c00 & 0x080000) calib.c00 |= 0xFFF00000;

//   calib.c10 = ((int32_t)(raw[5] & 0x0F) << 16) | ((int32_t)raw[6] << 8) | raw[7];
//   if (calib.c10 & 0x080000) calib.c10 |= 0xFFF00000;

//   calib.c01 = ((int16_t)raw[8] << 8) | raw[9];
//   calib.c11 = ((int16_t)raw[10] << 8) | raw[11];
//   calib.c20 = ((int16_t)raw[12] << 8) | raw[13];
//   calib.c21 = ((int16_t)raw[14] << 8) | raw[15];
//   calib.c30 = ((int16_t)raw[16] << 8) | raw[17];
// }

// int32_t readRawData(uint8_t start_register) {
//   uint8_t buf[3];
//   for (int i = 0; i < 3; i++) {
//     buf[i] = readRegister(start_register + i);
//   }

//   int32_t raw_data = ((uint32_t)buf[0] << 16) | ((uint32_t)buf[1] << 8) | buf[2];
//   if (raw_data & 0x800000) {
//     raw_data -= 0x1000000; // Two's complement for 24-bit
//   }

//   return raw_data;
// }

// uint8_t readRegister(uint8_t reg) {
//   uint8_t value;
//   digitalWrite(CS_PIN, LOW);
//   etx_spi.transfer(0x80 | reg); // Set MSB for read operation
//   value = etx_spi.transfer(0x00);
//   digitalWrite(CS_PIN, HIGH);
//   return value;
// }

// void writeRegister(uint8_t reg, uint8_t value) {
//   digitalWrite(CS_PIN, LOW);
//   etx_spi.transfer(reg & 0x7F); // Clear MSB for write operation
//   etx_spi.transfer(value);
//   digitalWrite(CS_PIN, HIGH);
// }
