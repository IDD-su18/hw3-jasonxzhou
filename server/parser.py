# Python script to parse the number sent to 192.168.1.1 by the Feather into four MIDI messages (using some bit twiddling)
# Note: this script will continously poll 192.168.1.1 

import urllib2
import serial
from bs4 import BeautifulSoup
quote_page = 'http://192.168.1.1/'
ser = serial.Serial('COM2', 9600, timeout=None, parity = serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)

while(True):
	page = urllib2.urlopen(quote_page)
	soup = BeautifulSoup(page, 'html.parser')
	soup1 = (int(str(soup)) & 0xFFFFFF 000000 000000 000000) >> 72
	soup2 = (int(str(soup)) & 0xFFFFFF 000000 000000) >> 48
	soup3 = (int(str(soup)) & 0xFFFFFF 000000) >> 24
	soup4 = int(str(soup)) & 0xFFFFFF 
	message1 = chr(soup1 & 0xFF0000 >> 16) + chr(soup1 & 0xFF00 >> 8) + chr(soup1 & 0xFF)
	message2 = chr(soup2 & 0xFF0000 >> 16) + chr(soup2 & 0xFF00 >> 8) + chr(soup2 & 0xFF)
	message3 = chr(soup3 & 0xFF0000 >> 16) + chr(soup3 & 0xFF00 >> 8) + chr(soup3 & 0xFF)
	message4 = chr(soup4 & 0xFF0000 >> 16) + chr(soup4 & 0xFF00 >> 8) + chr(soup4 & 0xFF)
	x = ser.write(message1)
	x = ser.write(message2)
	x = ser.write(message3)
	x = ser.write(message4)
