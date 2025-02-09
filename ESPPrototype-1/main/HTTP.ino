#include <WiFi.h>
#include <HttpClient.h>

// Backend server details
const char* serverName = "192.168.2.45";
const int serverPort = 11434; // Port number for the backend API
const char* apiPath = "/api/generate";

// HTTPClient requires a WiFiClient instance
WiFiClient wifiClient;

// Function to send HTTP POST request
void sendHttpRequest(const String& prompt) {
    HttpClient httpClient(wifiClient);

    // Start connection to the server
    httpClient.beginRequest();
    httpClient.post(serverName, serverPort, apiPath);

    // Construct the JSON payload
    String payload = "{\"prompt\": \"" + prompt + "\", \"model\": \"llama3.2:latest\", \"stream\": true}";

    // Add headers and send the payload
    httpClient.sendHeader("Content-Type", "application/json");
    httpClient.sendHeader("Content-Length", payload.length());
    httpClient.print(payload);
    httpClient.endRequest();

    // Read and print the response
    int statusCode = httpClient.responseStatusCode();
    Serial.print("HTTP Status Code: ");
    Serial.println(statusCode);

    Serial.print("Response: ");
    while (httpClient.available()) {
        char c = httpClient.read();
        Serial.print(c);
    }
    Serial.println();

    // Close the connection
    httpClient.stop();
}