/*Don't forget to set Sketchbook location in File/Preferences to the path of this project (the parent foder of this INO file)*/

#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>

// Task prototypes
void SensorTask(void *pvParameters);
void WiFiTask(void *pvParameters);
void UITask(void *pvParameters);
void BackendTask(void *pvParameters);

// Declare struct to store sensor's data
typedef struct {
    float uvData[2];
    float bmp280Data[2];
    int mpu6050Data[2];
    float gy511Data;
    int max3010Data[2];
} SensorData;

//Global variable for storing sensor data
SensorData latestSensorData;
SemaphoreHandle_t dataMutex; //We need a mutex for this variable as multiple tasks could be accessing at same time

char macStr[18];  // Buffer for MAC address string

void setup() {
  Serial.begin(115200);
  Wire.begin(8,9); //I2C Ports defined at 8 and 9

  //Initialize Wi-Fi
  //WARNING !!! Sensors will not be initialized until WiFi connected, can bypass this function for testing
  setupWiFi();

  //Get the mac address
  uint8_t mac[6];
  WiFi.macAddress(mac);
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.print("Stored MAC Address: ");
  Serial.println(macStr);

  //Initialize all sensors
  initGY511();
  delay(500);
  initMAX3010();
  initMPU6050();
  initBMP280();
  initUVSensor();
  //Initialize the UI
  initUI();

  //Create mutexes
  dataMutex = xSemaphoreCreateMutex();

  //Create tasks
  //Task creation template
  xTaskCreate(
    SensorTask, "SensorTask"  // A name just for humans
    ,
    2000  // Stack size in words, use uxTaskGetStackHighWaterMark() to check actual size in use
    ,
    NULL  // No parameter is used
    ,
    2  // Priority, we're using high priority for sensor reading to make sure data is up-to-date
    ,
    NULL  // Task handle is not used here
  );
  xTaskCreate(UITask, "UI Task", 4000, NULL, 1, NULL);
  xTaskCreate(WiFiTask, "Wifi Task", 4000, NULL, 1, NULL);
  xTaskCreate(BackendTask, "Backend Task", 8000, NULL, 1, NULL);
}

void loop() {
  // FreeRTOS handles task scheduling
}

// Task to read sensors and write data to the queue
void SensorTask(void *pvParameters) {
  for (;;) {
    SensorData data;
    
    //Fetch sensor data and store it in the struct
    readUVSensor(data.uvData);
    readBMP280(data.bmp280Data);
    readMPU6050(data.mpu6050Data);
    readGY511(&data.gy511Data); //Only float (not array) for gy511, so to pass by reference we need a pointer
    //readMAX3010(data.max3010Data); //MAX3010 algorithm needs to be re-implemented, as current one takes up too much runtime

    //Lock the mutex before updating the global variable
    if (xSemaphoreTake(dataMutex, portMAX_DELAY)) {
        latestSensorData = data;
        xSemaphoreGive(dataMutex);  // Release the mutex
    }

  //check how much space is left in the stack
    UBaseType_t stackLeft = uxTaskGetStackHighWaterMark(NULL);
    //Serial.print("Sensor task stack high water mark: ");
    //Serial.println(stackLeft);

    //Reading interval
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void UITask(void *pvParameters) {
  for (;;) {
    lv_task_handler();

    //check how much space is left in the stack
    UBaseType_t stackLeft = uxTaskGetStackHighWaterMark(NULL);
    //Serial.print("UI task stack high water mark: ");
    //Serial.println(stackLeft);

    //Run every 50 ms
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void WiFiTask(void *pvParameters) {
  for (;;) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Wi-Fi disconnected! Reconnecting...");
        setupWiFi();
    }
    //Run every 3000 ms
    vTaskDelay(3000 / portTICK_PERIOD_MS);
  }
}


void BackendTask(void *pvParameters) {
  for (;;) {
    //Lock the mutex before accessing the global variable
    if (xSemaphoreTake(dataMutex, portMAX_DELAY)) {
        sendSensorData(latestSensorData);
        xSemaphoreGive(dataMutex);  // Release the mutex
    }
    //Run every 5000 ms
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}