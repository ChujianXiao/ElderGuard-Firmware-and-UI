#include <WiFi.h>
extern "C" {
  #include "esp_wifi.h"
}

// Replace with your Wi-Fi credentials
const char* ssid = "uOttawa Trash";
const char* password = "meiyoumima";

IPAddress serverIP;
const char* server = "https://api.peakxel.net"; 

void setupWiFi() {
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Check Cloudflare proxy IP resolution
  if (WiFi.hostByName(server, serverIP)) {
        Serial.print("Resolved Direct Server IP: ");
        Serial.println(serverIP);
  } else {
        Serial.println("[ERROR] Direct Server DNS Resolution Failed!");
  }

  //Set maximum modem sleep to save power
  esp_wifi_set_ps(WIFI_PS_MAX_MODEM);
}
