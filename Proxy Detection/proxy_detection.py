import os
import sys
import subprocess
import RPi.GPIO as GPIO
from datetime import date

import SimpleMFRC522

# RFID reader up 
reader = SimpleMFRC522.SimpleMFRC522()

# Setting GPIO pins.
GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(17, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(27, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

#Loop which keeps on capturing images 
while(1):
    #Read input from pin 
4    x=GPIO.input(4)     
    # x==1 implies user is ready to mark attendance      
    if(x==1):
        print("Mark your attendance")             
        id, text = reader.read()     	#Read RFID's id and text
        print(id)						#Print ID of the seat
        #Capture the image from webcamera and store it in the folder "unknown"
        os.system('fswebcam -p YUYV -d /dev/video0 -r 640x480 /home/pi/unknown/'+str(id)+'.jpeg')
        #Keep on waiting until next person is ready to mark attendance.
        while(x==1):
            x=GPIO.input(4)
    #y==1 implies everyone has marked their attendance.        
    y=GPIO.input(17)
    if(y==1):
        print("All images taken")
        break
    
#Processing starts.
#System compares all the images stored in "unknown" folder with images in "images" folder amd storing result in a.txt
os.system('face_recognition ./images/ ./unknown > a.txt')
print("Processing Done")
#Initialising parameters
index=0
a=[]
b=[]
#Opening file a.txt to sort results
f=open("a.txt", "r")
f1=f.read().split("\n")
#Reading line by line.
for x in f1:
    if x=="":
        continue
    xy=x.split(",")
    #If image doesn't match to anyone, ignored the result; else stored in arrays
    if xy[1].find("no_persons_found")==-1 and xy[1].find("unknown_person")==-1 :
        print(xy[0])
        #Array a contain RFID number and b contains person's name.
        a.append(xy[0][10:-5])
        b.append(xy[1])
        print("Write done!")
        index=index+1
#Attendance of all the students stored in arrays 
print("Read done")        
i=0
#Saving the filename by date of that day
date=date.today()
print (date)
#Saving all the records in folder record.
os.system('cd ./records')
os.system('touch ' +str(date)+'.txt')
f.close()
f=open(str(date)+".txt", "w+")
#Writting the data of arrays in the file and saving it.
for i in range ( 0,index):
    first=a[i]
    second=b[i]
    f.write(first+ " - "+second+'\n')
    
print("write done")    
f.close()

#z==1 implies attendance for the day is taken and result is stored, now reset data
z=GPIO.input(27)
while(z==0):
    z=GPIO.input(27)
#Empty the files of folder "unknown"
os.system('rm- rf ./unknown')
os.system('mkdir unknown')
    

 
