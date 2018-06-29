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

//Polls all sensors, sends 4 MIDI signals as 1 integer, converted to string
void getMIDI(int msgs[4]) {
  msgs[0] = 0x905A45;
  msgs[1] = 0x905A00;
  msgs[2] = 0x905A45;
  msgs[3] = 0x905A00;
}

//returns number of digits in a number's base10 representation
int digitCount(int countNumber) {
  int counter = 0;
  while (countNumber > 10) {
    countNumber = floor(countNumber/10);
    counter++;
  }
  return counter + 1;
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
  
  WiFiClient client = server.available(); //begin request
  if (client) {                             
    Serial.println("new client");           
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            
            int msgs[4] = {0, 0, 0, 0};
            getMIDI(msgs);
            for (int i = 0; i < 4; i++) {
              
              //have to print the appropriate number of zeroes in front of each message
              //according to the value of the message; the "largest" possible MIDI msg
              //is 0xFFFFFF, which takes up 8 digits, so print zeroes in front of each
              //number to reach 8.
              int digitCountSize = digitCount(msgs[i]);
              for(int i = 0; i < (8 - digitCountSize); i++) {
                client.print(0);
              }

              client.print(msgs[i]);
            }
             //polling analog sensors
            
            client.println();
            break;
          }
          else {
            currentLine = "";
          }
        }
        else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop(); //end request
  }
}

void printWiFiStatus() {
  IPAddress ip = WiFi.localIP();
  Serial.print("Server '" + String(WiFi.SSID()) + "' @ ");
  Serial.print(ip);
  Serial.println(" with strength " + String(WiFi.RSSI()) + "dBm");
}
