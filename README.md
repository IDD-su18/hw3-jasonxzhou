# hw3-jasonxzhou
Theo Fedronic & Jason Zhou
IDD Summer 2018

## Documentation: Signal Routing Chain  
For this project, we are aiming to do the following signal routing:  
Sensor Control Signals => Adafruit Feather M0 => Hairless MIDI Serial Bridge => loopMIDI virtual MIDI port => Ableton Live DAW => Serum Synthesizer  
  
Note: The active Serial => Midi bridge must be disabled before uploading a program to the Adafruit Feather (due to serial port conflicts), and re-enabled after the program has been uploaded. 
  