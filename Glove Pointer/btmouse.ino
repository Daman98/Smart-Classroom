/*
Code of Arduino to Control Mouse pointer from Hand Glove
*/

const int xPin   = A0; //Pin for Input from x-axis of accelerometer
const int yPin   = A1; //Pin for Input from y-axis of accelerometer
const int zPin   = A2; //Pin for Input from z-axis of accelerometer
int flex1 = A15; //Taking Input from flex of first finger 
int flex2 = A8; //Taking Input from flex of middle finger
void setup() {
  //setting mode for pins
  pinMode(xPin,INPUT);
  pinMode(yPin,INPUT);
  pinMode(zPin,INPUT);
  pinMode(flex1, INPUT);
  pinMode(flex2, INPUT);

  Serial.begin(9600);
}

void loop() {
  int x = analogRead(xPin); //Reading Input from x-axis of accelerometer
  int y = analogRead(yPin); //Reading Input from y-axis of accelerometer
  int z = analogRead(zPin); //Reading Input from z-axis of accelerometer
  int f1 = analogRead(flex1); //Reading Input from flex sensor on first finger
  int f2 = analogRead(flex2); //Reading Input from flex sensor on middle finger
  
  if(y>370){
    Serial.println("L"); //Printing L to move mouse pointer to left
  }
  else if(y<300){
    Serial.println("R"); //Printing R to move mouse pointer to right
  }
  else if(x>370){
    Serial.println("U"); //Printing U to move mouse pointer to up
  }
  else if(x<300){
    Serial.println("D"); //Printing D to move mouse pointer to down
  }
  else if(f1>300){
    Serial.println("C"); //Printing C to left click
  }
  else if(f2>150){
    Serial.println("E"); //Printing E to right click
  }
  delay(100);
}
