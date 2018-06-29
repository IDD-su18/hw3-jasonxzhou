# hw3-jasonxzhou
Theo Fedronic & Jason Zhou  
IDD Summer 2018  

## Documentation: Signal Routing Chain  
For this project, we are aiming to do the following signal routing:  
Sensor Control Signals => Adafruit Feather M0 => Hairless MIDI Serial Bridge => loopMIDI virtual MIDI port => Ableton Live DAW => Serum Synthesizer  
  
Note: The active Serial => Midi bridge must be disabled before uploading a program to the Adafruit Feather (due to serial port conflicts), and re-enabled after the program has been uploaded. 

## Documentation: Serum Synthesizer
Serum by XferRecords is the soft synth that we will be controlling with our device. It's a highly versatile, 2-oscillator wavetable synthesizer.
The control scheme is as follows:  
Distance sensor => note selection  
Pressure sensor => note velocity & activation     
Joystick axis 1 => master pitch bend  
Joystick axis 2 => osc-1 wavetable position (mapped using mod wheel)  
Potentiometer => filter cutoff (mapped using MIDI-learn)  
  
## Documentation: Sensor Value Ranges  
2-axis joystick: [1, 1023]  
Distance sensor: [0, 500]  
Touch/Pressure Sensor: [700, 80]  
10K Potentiometer: [1, 1023]  
 