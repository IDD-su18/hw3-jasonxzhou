//distance sensor => note selection 
//joystick axis 1 => pitch bend
//joystick axis 2 => unassigned (return to midpoint)
//potentiometer => unassigned 

void setup() {
  Serial.begin(31250);
}

void loop() {
for (int note = 0x1E; note < 0x5A; note ++) {
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    //pitch bend noteOn(0xE0, 0, 50);
    noteOn(0x90, note, 0x45);
    delay(100);
  
    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
    noteOn(0x90, note, 0x00);
    delay(100);
    
  }

}

// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
