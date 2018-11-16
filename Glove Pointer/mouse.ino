/*
Code of Arduino to Control Mouse pointer from Hand Glove
*/

#include <SoftwareSerial.h>

//Pin config for the HC-05 module
#define RxD 6
#define TxD 7 

SoftwareSerial BTSerial(RxD, TxD);

const uint8_t xPin   = A0; //Pin for Input from x-axis of accelerometer
const uint8_t yPin   = A1; //Pin for Input from y-axis of accelerometer
const uint8_t zPin   = A2; //Pin for Input from z-axis of accelerometer
const uint8_t flex1 = A15; //Taking Input from flex of first finger 
const uint8_t flex2 = A8; //Taking Input from flex of middle finger

void setup() {
  //setting mode for pins
  pinMode(xPin,INPUT);
  pinMode(yPin,INPUT);
  pinMode(zPin,INPUT);
  pinMode(flex1, INPUT);
  pinMode(flex2, INPUT);

	BTSerial.flush();
	delay(500);

	BTSerial.begin(9600);

  Serial.begin(9600);
  delay(100);
}

void loop() {
  int32_t x = analogRead(xPin); //Reading Input from x-axis of accelerometer
  int32_t y = analogRead(yPin); //Reading Input from y-axis of accelerometer
  int32_t z = analogRead(zPin); //Reading Input from z-axis of accelerometer
  int32_t f1 = analogRead(flex1); //Reading Input from flex sensor on first finger
  int32_t f2 = analogRead(flex2); //Reading Input from flex sensor on middle finger
  
  if(y>370){
    BTSerial.write("L"); //Printing L to move mouse pointer to left
  }
  else if(y<300){
    BTSerial.write("R"); //Printing R to move mouse pointer to right
  }
  else if(x>370){
    BTSerial.write("U"); //Printing U to move mouse pointer to up
  }
  else if(x<300){
    BTSerial.write("D"); //Printing D to move mouse pointer to down
  }
  else if(f1>300){
    BTSerial.write("C"); //Printing C to left click
  }
  else if(f2>150){
    BTSerial.write("E"); //Printing E to right click
  }
  delay(100);
}
