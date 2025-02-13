#include <Wifi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Replace with your WIFI credentials
const char* ssid = "uOttawa Trash";
const char* password = "meiyoumima";

// Replace with your server URL (including the appropriate port and path)
//const char* serverUrl = "http://yourserver.com/api/sensordata";

// Declare struct to store sensor's data
typedef struct {
    float uvData[2];
    float bmp280Data[2];
    int mpu6050Data[2];
    float gy511Data;
    int max3010Data[2];
  } SensorData;

// Fucntion to send sensor data to the backend
void sendSensorData(SensorData sensorData) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverUrl); // Specify destination for HTTP POST
      http.addHeader("Content-Type", "application/json");
  
      // Create a JSON document (adjust capacity if needed)
      StaticJsonDocument<256> doc;
  
      // Populate JSON document with sensor data
      JsonArray uvArray = doc.createNestedArray("uvData");
      uvArray.add(sensorData.uvData[0]);
      uvArray.add(sensorData.uvData[1]);
  
      JsonArray bmpArray = doc.createNestedArray("bmp280Data");
      bmpArray.add(sensorData.bmp280Data[0]);
      bmpArray.add(sensorData.bmp280Data[1]);
  
      JsonArray mpuArray = doc.createNestedArray("mpu6050Data");
      mpuArray.add(sensorData.mpu6050Data[0]);
      mpuArray.add(sensorData.mpu6050Data[1]);
  
      doc["gy511Data"] = sensorData.gy511Data;
  
      JsonArray maxArray = doc.createNestedArray("max3010Data");
      maxArray.add(sensorData.max3010Data[0]);
      maxArray.add(sensorData.max3010Data[1]);
  
      // Serialize JSON document to a string
      String jsonStr;
      serializeJson(doc, jsonStr);
  
      // Debug: print JSON payload
      Serial.println("JSON Payload:");
      Serial.println(jsonStr);
  
      // Send the HTTP POST request
      int httpResponseCode = http.POST(jsonStr);
  
      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String response = http.getString();
        Serial.println("Response: " + response);
      } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }
  
      http.end(); // Close connection
    } else {
      Serial.println("WiFi not connected.");
    }
  }