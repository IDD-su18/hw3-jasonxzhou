# hw3-jasonxzhou
Physical/Mechanical Design: Theo Fedronic  
Electronic/Software Design: Jason Zhou   
IDD Summer 2018  

## Electronic & Software Design	

## Physical & Mechanical Design

## Documentation

### Signal Routing Chain Diagram
![alt text](https://github.com/IDD-su18/hw3-jasonxzhou/blob/master/routing-1.jpg)

### Setting up & Launching
Upload and launch server.ino onto the feather.  
Launch Hairless <-> MIDI bridge, set serial port to "COM1 -> COM2".  
Launch loopMIDI, Ableton, and Serum.  
Connect laptop to wifi server "idd".      
Run python script parser.py to begin.  

### Serum Synthesizer Control Scheme
Serum by XferRecords is the soft synth that we will be controlling with our device. It's a highly versatile, 2-oscillator wavetable synthesizer.
The control scheme is as follows:  
Distance sensor => note selection  
Pressure sensor => note velocity & activation     
Joystick axis 1 => master pitch bend  
Joystick axis 2 => osc-1 wavetable position (mapped using mod wheel)  
Potentiometer => filter cutoff (mapped using MIDI-learn)  
  
### Sensor Value Ranges  
2-axis joystick: [1, 1023]  
Distance sensor: [0, 500]  
Touch/Pressure Sensor: [700, 80]  
10K Potentiometer: [1, 1023]  
 
