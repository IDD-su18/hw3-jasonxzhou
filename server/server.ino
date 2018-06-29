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

int counter = 0;
String getMIDI() {
  if(!counter){
    counter++;
    return String(0x905A45);
  } else {
    return String(0x905A00); 
  }
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
  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print(getMIDI());
            // The HTTP response ends with another blank line:
            client.println();
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    client.stop();
  }
}

void printWiFiStatus() {
  IPAddress ip = WiFi.localIP();
  Serial.print("Server '" + String(WiFi.SSID()) + "' @ ");
  Serial.print(ip);
  Serial.println(" with strength " + String(WiFi.RSSI()) + "dBm");
}
