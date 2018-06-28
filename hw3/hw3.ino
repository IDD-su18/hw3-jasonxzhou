//distance sensor => note selection
//pressure sensor => note velocity 
//joystick axis 1 => pitch bend
//joystick axis 2 => wavetable position (mod wheel mapped)
//potentiometer => cutoff (midi learn)

void setup() {
  Serial.begin(31250);
}

void loop() {

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

    //mod wheel
    noteOn(0xB0, 0x01, i);
    
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    noteOn(0x90, note, 0x00);
    
    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
    noteOn(0x90, note, 0x45);

    //midi learn to set any parameter might have to manually do this upon launching serum everytime though
    sendMIDI(0xB0, 0x10, 1);
  }*/

