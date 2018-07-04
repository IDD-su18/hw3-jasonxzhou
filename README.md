# hw3-jasonxzhou
![alt text](https://github.com/IDD-su18/hw3-jasonxzhou/blob/master/misc/image037.jpg)
**Physical & Mechanical Design:** Theo Fedronic  
**Electronic & Software Design:** Jason Zhou   
**Demo Video**: https://youtu.be/ytvsIRv0k3Y

## I. Electronic & Software Implementation	
### A. Circuit Overview
![alt text](https://github.com/IDD-su18/hw3-jasonxzhou/blob/master/misc/circuit.png)

The microcontroller used is the Adafruit Feather M0. The sensors used are the Adafruit VL53L0X distance sensor, the Adafruit 2-axis analog joystick, a 10K potentiometer, and a force-resistive sensor. The distance sensor uses an I2C connection to the SCL/SDA pins, while all other sensors use the generic analog input pins on the Feather.

### B. Custom Signal Routing Chain Overview
![alt text](https://github.com/IDD-su18/hw3-jasonxzhou/blob/master/misc/routing-1.jpg)

First, the Adafruit Feather sets up its own WiFi web server. Whenever a client request is sent to the web server, the Feather polls all analog sensor values, and with some manipulation, converts the analog sensor values into four separate MIDI signals (essentially a linear conversion from a known range of input values into a known acceptable range of output values); the four signals are encoded into a single 96-bit number and sent to the web server as a response to the client request. This portion of the software is contained in "server.ino". 

The client (likely a laptop) will be running the client-side software, contained in "parser.py". The client must have 2 virtual COM/Serial ports open (using Eltima), and 1 virtual MIDI port open (using loopMIDI). Then, using urllib2 and BeautifulSoup, the python script will continously poll the Feather server at a rate of approximately 10Hz, and will continously scrap the 96-bit number. With more manipulation, the 96-bit number is decoded back into the 4 original distinct MIDI signals. Using pySerial, the 4 MIDI signals are written into one of the two virtual serial ports, and the data is routed out through the other virtual serial port into the program Hairless MIDI <-> Serial Bridge. From Hairless, the serial data is sent through the virtual MIDI port into our digital-audio workstation Ableton, which is hosting the synthesizer Serum. Upon receiving the MIDI signals, Serum then generates the desired audio output. The above diagram illustrates the entire signal routing process.

### C. Custom Batch MIDI Protocol
Because of the number of parameters we are controlling, and to reduce latency and increase responsiveness, we decided to send a batch of 4 MIDI signals at each poll, which required us to develop a simple encoding method.  
Each MIDI signal consists of three bytes, such as 0x9A0540. This means that all MIDI signals are between the values 0 (0x000000) and 16777215 (0xFFFFFF). To send 4 MIDI signals at once, we could simply append each signal onto the end of the previous one (i.e. to send the four signals 0x9A0540, 0x9A0500, 0xE00001, 0xB00500, we could simply send 0x9A05409A0500E00001B00500). As a side note, this value is much too large to be sent as one long or one int, so internally this is done by passing a 4 element integer array around.  
However, this "appending" method breaks when there are leading zeroes in any of the four signals, as leading zeroes are omitted when using the client sending function, meaning the four MIDI signals are no longer guaranteed to be aligned to every 6 bytes (and there's no way to know whether alignment has been preserved or not during decoding). Thus, (and for ease of computation the next steps are done in decimal instead of hex), we manually prepend all MIDI signals such that they are of the same length as the largest possible MIDI signal, 0xFFFFFF; in other words, all MIDI signals are zero-padded to 8 digits (by printing the appropriate number of 0's). After zero-padding, the "appending" method is guaranteed to produce aligned signals, which also makes the decoding process in the python script (parser.py) quite easy. The table below illustrates the aforementioned examples: 

![alt text](https://github.com/IDD-su18/hw3-jasonxzhou/blob/master/misc/zeropad.png)

## II. Physical & Mechanical Implementation
Fabrication Materials:
- 7 3D printed parts
- 48 cumulative hours of printing
- 16 self-tapping screws

Encasing Design Objectives:
- Wearable / portable functionality
- Ergonomic & Small
- Easy to assemble / disassemble
- Good looking
In order to meet these objectives, the focus was on using screws and snap-fits for securing all electronics, and all components together.  
![alt text](https://github.com/IDD-su18/hw3-jasonxzhou/blob/master/misc/image001.jpg)
![alt text](https://github.com/IDD-su18/hw3-jasonxzhou/blob/master/misc/image008.jpg)
![alt text](https://github.com/IDD-su18/hw3-jasonxzhou/blob/master/misc/image015.jpg)
![alt text](https://github.com/IDD-su18/hw3-jasonxzhou/blob/master/misc/image017.jpg)
![alt text](https://github.com/IDD-su18/hw3-jasonxzhou/blob/master/misc/image019.jpg)

## III. Misc. Documentation

### A. Installation & Set-up Instructions
Install: Ableton (or DAW of your choice), Serum (or synth of your choice), Hairless <-> MIDI bridge, Eltima, and loopMIDI.  
Open your DAW; select your synth inside the DAW.  
Launch Eltima, add two virtual serial ports (COM1, COM2). 
Launch Hairless <-> MIDI bridge, set serial port to "COM1 -> COM2".  
Launch loopMIDI, set loopMIDI input to be Hairless output.   
Upload and launch server.ino onto the Adafruit Feather.  
Connect laptop to wifi server "idd".      
Run python script parser.py to begin.  

### B. Synthesizer Control Scheme
Serum by XferRecords is the soft synth that we will be controlling with our device. It's a highly versatile, 2-oscillator wavetable synthesizer.
The control scheme is as follows:  
Distance sensor => note selection  
Pressure sensor => note velocity & activation     
Joystick axis 1 => master pitch bend  
Joystick axis 2 => osc-1 wavetable position (mapped using mod wheel)  
Potentiometer => filter cutoff (mapped using MIDI-learn)  
  
### C. Raw Sensor Value Ranges  
2-axis joystick: [1, 1023]  
Distance sensor: [0, 500]  
Touch/Pressure Sensor: [700, 80]  
10K Potentiometer: [1, 1023]  
 
