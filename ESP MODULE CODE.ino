#include <WiFi.h>

const char* ssid = "your_wifi_name";
const char* password = "your_wifi_password";
const char* host = "maker.ifttt.com";

void setup() {
  Serial.begin(115200);
  Serial.println("Email");
  delay(100);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);-
  WiFiClient client;
  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }

  if (Serial.available()) {
    String receivedData = Serial.readStringUntil('\n');
    Serial.println("Received data from Arduino: " + receivedData);

    if (receivedData != "CLOSED") {
      int switchState = digitalRead(2); // Read the state of the switch connected to Arduino pin 2
      if (switchState == LOW) {
        String url = "/trigger/Security_System/json/with/key/pFn1yCwY5VMC00bMk67OMzsjOjFqNOoMZciJOCd0Swk";
        Serial.print("Requesting URL: ");
        Serial.println(url);
        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "Connection: close\r\n\r\n");
      } else {
        Serial.println("Switch is not activated. Try again when the switch is closed.");
      }
    } else {
      Serial.println("Invalid input. Expected 'OPEN'. Try again");
    }
  }
  
  delay(1000);
}
