# import serial
# import pyautogui
#  ser = serial.Serial('/dev/ttyACM0', 9600) #Connecting to the Arduino by giving it's port address
#  #counters to make sure user actually wants to click
# count1 = 0 
# count2 = 0
#  while True:
#     a = ser.readline() #Reading what Arduino code is printing on serial monitor
#     b= str(a)
#     print(b[2])
#     #Performing operation using pyautogui library according to character printed on serial monitor
#     if b[2] == "D" :  
#         pyautogui.moveRel(0, 10, duration = 0.01) 
#     if b[2] == "R" :
#         pyautogui.moveRel(10, 0, duration = 0.01)  
#     if b[2] == "U" :
#         pyautogui.moveRel(0, -10, duration = 0.01) 
#     if b[2] == "L" :
#         pyautogui.moveRel(-10,0, duration = 0.01)
#     if b[2] == "C" :
#         count1= count1+1
#         if(count1==10): #clicking only when we get character corresponding to click 10 times to make sure user actually wants to click
#             pyautogui.click()
#             count1=0
#     if b[2] == "E" :
#         count2=  count2 + 1
#         if(count2==10): #clicking only when we get character corresponding to click 10 times to make sure user actually wants to click
#             pyautogui.click(button='right')
#             count2=0
import bluetooth
import sys
import pyautogui

# Bluetooth address of the HC-05 module
bd_addr = "00:18:E4:34:EB:E6"

port = 1
sock = bluetooth.BluetoothSocket( bluetooth.RFCOMM )
# Connecting to the bluetooth address on the given port
sock.connect((bd_addr, port))
print 'Connected'

count1 = 0 
count2 = 0


while True:
    # Receiving data
    data = sock.recv(12)
    #Performing operation using pyautogui library according to character printed on serial monitor
    print(data.decode("utf-8"))
    if data.decode("utf-8")[0] == "D" :  
        pyautogui.moveRel(0, 10, duration = 0.01) 
    if data.decode("utf-8")[0] == "R" :
        pyautogui.moveRel(10, 0, duration = 0.01)  
    if data.decode("utf-8")[0] == "U" :
        pyautogui.moveRel(0, -10, duration = 0.01) 
    if data.decode("utf-8")[0] == "L" :
        pyautogui.moveRel(-10,0, duration = 0.01)
    if data.decode("utf-8")[0] == "C" :
        count1= count1+1
        if(count1==10): #clicking only when we get character corresponding to click 10 times to make sure user actually wants to click
            pyautogui.click()
            count1=0
    if data.decode("utf-8")[0] == "E" :
        count2=  count2 + 1
        if(count2==10): #clicking only when we get character corresponding to click 10 times to make sure user actually wants to click
            pyautogui.click(button='right')
            count2=0

sock.close()