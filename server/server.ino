//jason zhou
//idd summer 2018

#include <SPI.h>
#include <WiFi101.h>
#include "Adafruit_VL53L0X.h"

char ssid[] = "idd";
int status;
int lastNote = 0;
WiFiServer server(80);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

//setting all pins for wifi & sensors to function
void setup() {
  WiFi.setPins(8,7,4,2);
  Serial.begin(9600);
  while (!Serial) {
    delay(1);
  }

  //distance sensor boot
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }

  //resistive touch boot
  pinMode(A3, INPUT);

  //potentiometer boot
  pinMode(9, INPUT);
  
  //joystick boot
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
  //wifi server boot
  status = WiFi.beginAP(ssid);
  delay(10000);
  server.begin();
  printWiFiStatus();
}

//client request loop
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
            //polling all sensors for MIDI message
            getMIDI(msgs); 
            
            for (int i = 0; i < 4; i++) {
              
              //we have to print the appropriate number of zeroes in front of each message
              //according to the value of the message; the "largest" possible MIDI msg
              //is 0xFFFFFF, which takes up 8 digits, so print zeroes in front of each
              //number to reach 8.
              int digitCountSize = digitCount(msgs[i]);
              for(int i = 0; i < (8 - digitCountSize); i++) {
                client.print(0);
              }
              client.print(msgs[i]);
            }
            
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
    //end request
    client.stop(); 
  }
}

//displays WIFI status
void printWiFiStatus() {
  IPAddress ip = WiFi.localIP();
  Serial.print("Server '" + String(WiFi.SSID()) + "' @ ");
  Serial.print(ip);
  Serial.println(" with strength " + String(WiFi.RSSI()) + "dBm");
}

//returns number of digits in a number's base10 representation
//used for 0 padding MIDI signals
int digitCount(int countNumber) {
  int counter = 0;
  while (countNumber > 10) {
    countNumber = floor(countNumber/10);
    counter++;
  }
  return counter + 1;
}

//Polls all sensors, sends 4 MIDI signals as 1 integer, converted to string
void getMIDI(int msgs[4]) {

  //reading distance sensor
  //will use notes 60 to 72 for C4-C5
  VL53L0X_RangingMeasurementData_t measure;
  int distance = 0;
  
  int note;
  lox.rangingTest(&measure, false);
  //phase failure check
  if (measure.RangeStatus != 4) { 
    distance = measure.RangeMilliMeter;
    
    //sometimes sensor outputs 8191 instead of out of range
    if (distance == 8191) { 
      distance = -1;
    }
  } else {
    distance = -1;
  }

  if (distance == -1) {
    note = lastNote;
  } else {
    //converting to 60 to 72 for C4-C5
    note = (distance / 54.2 + 60); 
    lastNote = note;
  }
  
  Serial.print("note: ");
  Serial.println(note);
  

  //reading resistive touch; harder touch, louder sound
  int touch = analogRead(A3);

  //converting to 1-127 value
  int velocity = 127 - ((touch - 80) / 7.45); 
  if (note < 60) {
    //dont play note if less than 60
    velocity = 0; 
    
    //then turn off last note
    note = lastNote;
  } 
  Serial.print("velocity: ");
  Serial.println(velocity);

  //reading potentiometer
  int pot = analogRead(9);
  
  //converting to 1-127 value
  int cutoff = pot / 8.1; 
  Serial.print("cutoff: ");
  Serial.println(cutoff);

  //reading joystick
  int x = analogRead(A0);
  int y = analogRead(A1);
  
  //unassigned
  int sel = analogRead(A2); 
  int pitchBend = x / 8.1;
  int modWheel = y / 8.1;
  Serial.print("pitchbend ");
  Serial.print(pitchBend);
  Serial.print("modwheel ");
  Serial.println(modWheel);

  //loading the four MIDI messages
  msgs[0] = 0x900000 + note*16*16 + velocity; //note & velocity, need the 16^2 to get it into the middle 2 bytes
  msgs[1] = 0xB01000 + cutoff; //cutoff
  msgs[2] = 0xE00000 + pitchBend; //pitch bend msg
  msgs[3] = 0xB00100 + modWheel; //mod wheel
}
