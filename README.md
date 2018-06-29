# hw3-jasonxzhou
Theo Fedronic & Jason Zhou  
IDD Summer 2018  

## Documentation: Signal Routing Chain  
![alt text](https://github.com/IDD-su18/hw3-jasonxzhou/blob/master/routing-1.jpg)

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
 
