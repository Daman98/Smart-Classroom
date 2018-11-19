import serial
import time
import re
import requests
ser = serial.Serial('/dev/ttyACM0', 9600)

count1 = 0
count2 = 0

while True:
	a = ser.readline()
	b= str(a)
	print(b)
	data = {
		"resp":b[2]+" "+b[3]+" n n",
	}
	requests.get('http://localhost:8000/presence', params=data)