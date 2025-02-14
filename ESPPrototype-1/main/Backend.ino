#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* serverUrl = "http://192.168.2.10:3001/api/sensors";

void sendSensorData(SensorData sensorData) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(serverUrl); // Specify destination for HTTP POST
        http.addHeader("Content-Type", "application/json");

        // Create a JSON document (adjust capacity if needed)
        StaticJsonDocument<256> doc;

        // Add MAC address
        doc["macAddress"] = macStr;

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