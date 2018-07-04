# jason zhou 
# idd summer 2018
# Python script to parse the number sent to 192.168.1.1 by the Feather into four MIDI messages (using some bit twiddling)
# Note: this script will continously poll 192.168.1.1 

import urllib2
import serial
import time
from bs4 import BeautifulSoup
quote_page = 'http://192.168.1.1/'
ser = serial.Serial('COM2', 9600, timeout=None, parity = serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)
lastNote = 0

while(True):
	# scraps html page
	page = urllib2.urlopen(quote_page)
	soup = BeautifulSoup(page, 'html.parser')
	
	# separates html value into 4 numbers (chopping by every 8 digits)
	soup1 = int(int(str(soup)) % 100000000)
	soup2 = int(int(str(soup)) // 100000000 % 100000000)
	soup3 = int(int(str(soup)) // 100000000 // 100000000 % 100000000)
	soup4 = int(int(str(soup)) // 100000000 // 100000000 // 100000000 % 100000000)
	
	# converts those 4 numbers into properly formatted MIDI values
	message1 = chr((soup1 & 0xFF0000) >> 16) + chr((soup1 & 0xFF00) >> 8) + chr(soup1 & 0xFF)
	message2 = chr((soup2 & 0xFF0000) >> 16) + chr((soup2 & 0xFF00) >> 8) + chr(soup2 & 0xFF)
	message3 = chr((soup3 & 0xFF0000) >> 16) + chr((soup3 & 0xFF00) >> 8) + chr(soup3 & 0xFF)
	message4 = chr((soup4 & 0xFF0000) >> 16) + chr((soup4 & 0xFF00) >> 8) + chr(soup4 & 0xFF)
	
	#if velocity 0, send all notes shut off signal
	if ((soup4 & 0xFF) == 0): 
		ser.write((chr(0b10110000) + chr(0x7B) + chr(0))) 
	else: 
		#otherwise write normal message
		ser.write(message1)
	
	#write remaining 4 MIDI messages
	ser.write(message2)
	ser.write(message3)
	ser.write(message4)
	
	#small polling delay
	time.sleep(0.1)

