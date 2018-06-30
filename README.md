# hw3-jasonxzhou
Physical & Mechanical Design: Theo Fedronic  
Electronic & Software Design: Jason Zhou   
IDD Summer 2018  

## I. Electronic & Software Implementation	

### A. Custom Signal Routing Chain
![alt text](https://github.com/IDD-su18/hw3-jasonxzhou/blob/master/misc/routing-1.jpg)

First, the Adafruit Feather sets up its own WiFi web server. Whenever a client request is sent to the web server, the Feather polls all analog sensor values, and with some manipulation, converts the analog sensor values into four separate MIDI signals; the four signals are encoded into a single 96-bit number and sent to the web server as a response to the client request. This portion of the software is contained in "server.ino". 

The client (likely a laptop) will be running the client-side software, contained in "parser.py". The client must have 2 virtual COM/Serial ports open (using Eltima), and 1 virtual MIDI port open (using loopMIDI). Then, using urllib2 and BeautifulSoup, the python script will continously poll the Feather server at a rate of approximately 10Hz, and will continously scrap the 96-bit number. With more manipulation, the 96-bit number is decoded back into the 4 original distinct MIDI signals. Using pySerial, the 4 MIDI signals are written into one of the two virtual serial ports, and the data is routed out through the other virtual serial port into the program Hairless MIDI <-> Serial Bridge. From Hairless, the serial data is sent through the virtual MIDI port into our digital-audio workstation Ableton, which is hosting the synthesizer Serum. Upon receiving the MIDI signals, Serum then generates the desired audio output.

### B. Custom Batch MIDI Protocol  
We developed a simple variation specific for our purposes. 


## II. Physical & Mechanical Design


## III. Misc. Documentation

### A. Setting up & Launching
Upload and launch server.ino onto the feather.  
Launch Hairless <-> MIDI bridge, set serial port to "COM1 -> COM2".  
Launch loopMIDI, Ableton, and Serum.  
Connect laptop to wifi server "idd".      
Run python script parser.py to begin.  

### B. Circuit Schematic

### C. Synthesizer Control Scheme
Serum by XferRecords is the soft synth that we will be controlling with our device. It's a highly versatile, 2-oscillator wavetable synthesizer.
The control scheme is as follows:  
Distance sensor => note selection  
Pressure sensor => note velocity & activation     
Joystick axis 1 => master pitch bend  
Joystick axis 2 => osc-1 wavetable position (mapped using mod wheel)  
Potentiometer => filter cutoff (mapped using MIDI-learn)  
  
### D. Raw Sensor Value Ranges  
2-axis joystick: [1, 1023]  
Distance sensor: [0, 500]  
Touch/Pressure Sensor: [700, 80]  
10K Potentiometer: [1, 1023]  
 
