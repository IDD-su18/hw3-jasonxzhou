#include <SPI.h>
#include <WiFi101.h>

char ssid[] = "idd";
int status;
WiFiServer server(80);

void setup() {
  WiFi.setPins(8,7,4,2);
  Serial.begin(9600);
  while (!Serial) {
  }
  status = WiFi.beginAP(ssid);
  delay(10000);
  server.begin();
  printWiFiStatus();
}


void loop() {
  if (status != WiFi.status()) {
    status = WiFi.status();
    if (status == WL_AP_CONNECTED) {
      byte remoteMac[6];
      Serial.print("Device connected to AP, MAC address: ");
      WiFi.APClientMacAddress(remoteMac);
      Serial.print(remoteMac[5], HEX);
      Serial.print(":");
      Serial.print(remoteMac[4], HEX);
      Serial.print(":");
      Serial.print(remoteMac[3], HEX);
      Serial.print(":");
      Serial.print(remoteMac[2], HEX);
      Serial.print(":");
      Serial.print(remoteMac[1], HEX);
      Serial.print(":");
      Serial.println(remoteMac[0], HEX);
    }
  }
  
  WiFiClient client = server.available();   
  if (client && client.connected()) {                                  
      client.println("HTTP/1.1 200 OK");
      client.println("Content-type:text/html");
      client.println();
      int i = 0;
      while (true) {
        client.println(i);
        i++;





              
      }
  }
}

void printWiFiStatus() {
  IPAddress ip = WiFi.localIP();
  Serial.print("Server '" + String(WiFi.SSID()) + "' @ ");
  Serial.print(ip);
  Serial.println(" with strength " + String(WiFi.RSSI()) + "dBm");
}
