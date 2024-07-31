#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>

//Update To Yours
const char* ssid = "Bramah";
const char* password = "123456789";
const char* serverUrl = "http://10.21.125.162:3000/update_mac";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    String macAddress = WiFi.macAddress();
    String payload = "{\"mac_address\":\"" + macAddress + "\"}";

    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.printf("Error: %d\n", httpResponseCode);
    }

    http.end();
  }

  delay(5000); // Send update every 5 seconds
}
