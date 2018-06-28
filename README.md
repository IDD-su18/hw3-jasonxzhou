# hw3-jasonxzhou

# MIDI Chain Technical Documentation  
  
For this project, we are aiming to do the following signal routing:  
  
Sensor Control Signals => Adafruit Feather M0 => Hairless MIDI Serial Bridge => loopMIDI virtual MIDI port => Ableton Live DAW => Serum Synthesizer  
  
Note that the active Serial => Midi bridge must be disabled before uploading a program to the Adafruit Feather (due to serial port conflicts), and re-enabled after the program has been uploaded. 
  
 
# Progress 06/27
=> Signal routing done  
=> 4 sensors decided, first physical prototype made

