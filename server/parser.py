import urllib2
import serial
from bs4 import BeautifulSoup
quote_page = 'http://192.168.1.1/'
ser = serial.Serial('COM2', 9600, timeout=None, parity = serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)

while(True):
	page = urllib2.urlopen(quote_page)
	soup = BeautifulSoup(page, 'html.parser')
	message = chr(int(str(soup)) & 0xFF0000 >> 16) + chr(int(str(soup)) & 0xFF00 >> 8) + chr(int(str(soup)) & 0xFF)
	x = ser.write(message)
