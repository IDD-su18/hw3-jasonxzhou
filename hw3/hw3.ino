//distance sensor => note selection (value range: 0mm to 500mm, i2c connection)
//pressure sensor => note velocity (value range: 1023 resting, 80 hard push, 700 soft push)
//joystick axis 1 => pitch bend (value range: 1 to 1023)
//joystick axis 2 => wavetable position (mod wheel mapped; value range: 1 to 1023)
//potentiometer => cutoff (midi learn; value range: 1 to 1023)

#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  //Setting baud rate
  Serial.begin(115200);
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
  
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  
  pinMode(A5, INPUT);
  pinMode(10, INPUT);
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
    
  delay(100);


  
  
}

//Sends MIDI signal
void sendMIDI(int firstByte, int secondByte, int thirdByte) {
  Serial.write(firstByte);
  Serial.write(secondByte);
  Serial.write(thirdByte);
}

/* notes    
    //notes range 0x1E to 0x5A
    //pitch bend
    //test
    noteOn(0xE0, 0x00, 50);
 \\
  
    //mod wheel
    noteOn(0xB0, 0x01, i);
    
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    noteOn(0x90, note, 0x00);
    
    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
    noteOn(0x90, note, 0x45);

    //midi learn to set any parameter might have to manually do this upon launching serum everytime though
    sendMIDI(0xB0, 0x10, 1);
  }*/

