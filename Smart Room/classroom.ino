#include <Servo.h>


const uint8_t pingDoor1 = 7;    // Trigger Pin of Ultrasonic Sensor of gate
const uint8_t echoDoor1 = 6;    // Echo Pin of Ultrasonic Sensor of gate
const uint8_t pingDoor2 = 8;    // Trigger Pin of Ultrasonic Sensor of gate
const uint8_t echoDoor2 = 9;    // Echo Pin of Ultrasonic Sensor of gate
const uint8_t pingChair1 = 3;   // Trigger Pin of Ultrasonic Sensor of seat
const uint8_t echoChair1 = 2;   // Echo Pin of Ultrasonic Sensor of seat
const uint8_t pingChair2=5;     // Trigger Pin of Ultrasonic Sensor of seat
const uint8_t echoChair2=4;     // Echo Pin of Ultrasonic Sensor of seat
Servo servo_test;         // Initialize a servo object for the connected servo  
int32_t angle = 0;            // Initialize angle of door=0
int32_t opengate = 0;         // Variable which tells if the gate is open or not.
int32_t count=0;
int32_t stand3=0,sit3=0,stand4=0,sit4=0,flag3=0,flag4=0;

uint8_t pirPin = 52;               // choose the input pin (for PIR sensor)
int32_t pirState = LOW;             // we start, assuming no motion detected
int32_t val = 0;                    // variable for reading the pin status
uint8_t backled = 53;              // the PWM pin back LEDs are attached to
uint8_t frontled = 12;            //the Analog pin front LEDs are connected to

uint8_t servoPin = 13;
uint8_t b_servo = 11;
uint8_t mode_switch = 22;
uint8_t board_switch = 24; 
int32_t count1 = 0;
// Create a servo object 
Servo Servo1;
Servo board_servo;
int32_t dir = 1; 

void setup() {
  Serial.begin(9600);
  servo_test.attach(10);         // attach the signal pin of servo to pin9 of arduino
  pinMode(pirPin, INPUT);     // declare sensor as input
  pinMode(frontled, OUTPUT);    //declare front LEDs as output.
  pinMode(backled, OUTPUT);     //declare back LEDs as output.
  servo_test.write(0);
  Servo1.attach(servoPin);
   board_servo.attach(b_servo);
   Servo1.write(0);
   board_servo.write(0); 
}


long ultrasonicReading(int pingPin, int echoPin){
  long duration,cm;     
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  return cm;
}

void loop() {
  //Initializing variables.
  long duration1, inches, cm,duration2, cm1, cm2; 
  
  //getting distance from ultra sonic of gate.
  cm1 = ultrasonicReading(pingDoor1,echoDoor1);
  cm2 = ultrasonicReading(pingDoor2,echoDoor2);

  cm=cm1;                //Taking the minimum of the two for comparison
  if(cm2<cm1){
      cm=cm2;   
  }
  //Threshold for distance=16
  //If there is obstacle and gate is not open
  if(opengate==1 && count<2){
    count++;
  }
  else{
      count = 0;
      if (cm < 16 && opengate == 0) {
        for (angle = 0; angle <= 90; angle += 5)    //Command to move from 0 degrees to 90 degrees 
        {
          servo_test.write(angle);                 //Command to rotate the servo to the specified angle
          delay(5);
        }
        opengate = 1;
    //    delay(2000);
      }
      else if (opengate==1 && cm>16) {
        for (angle = 90; angle >=0; angle -= 5)    //Command to move from 0 degrees to 180 degrees 
        {
         
          servo_test.write(angle);                 //Command to rotate the servo to the specified angle
          delay(5);
//          cm1 = microsecondsToCentimeters(duration1);
//          cm2 = microsecondsToCentimeters(duration2);
//          cm=cm1;                                 //Taking the minimum of the two for comparison
//          if(cm2<cm1){
//              cm=cm2;   
//          }
//          //Obstacle arrives while gate is about to close.
//          if(cm<16){
//            int a1;
//            for ( a1=angle; a1 <= 90; angle += 5)    // command to move from 0 degrees to 180 degrees 
//              {
//                servo_test.write(angle);                 //command to rotate the servo to the specified angle
//                delay(5);
//              }
//              servo_test.write(90-a1);
//              break;
//            }
        }
        opengate = 0;
      }
  }
  
   //Initializing variables
   long duration3, cm3,cm4,duration4;
   //getting distance from ultra sonic of seats
   cm3 = ultrasonicReading(pingChair1,echoChair1);
   cm4 = ultrasonicReading(pingChair2,echoChair2);

   

  val = digitalRead(pirPin);  // read input value of PIR
  if (val == HIGH) {            // check if the input is HIGH
    if(digitalRead(mode_switch)==HIGH){
       digitalWrite(backled,HIGH);
       analogWrite(frontled,255);  
   }
   // Make servo go to 90 degrees 
   else{
       digitalWrite(backled,HIGH);
       analogWrite(frontled,100);
   }  
    if (pirState == LOW) {
      digitalWrite(backled,HIGH);     //Turning on the LEDs
      analogWrite(frontled, 255);
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    if (pirState == HIGH){           //Turning off the LEDs
      digitalWrite(backled,LOW);
      analogWrite(frontled, 0);
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }

  //Threshold for ultrasonic if a person seats is 45
   if(cm3>45){              // Person is standing
       stand3++;
   }
   else{
      sit3++;
      if(sit3>45){          //If person sits again, initializing to zero
        sit3 = 0;
        stand3 = 0;
      }
   }
   if(stand3>400){          //Person wasn't sitting there for a long time
    flag3 = 3;
   }
    if(flag3 == 3){
    Serial.print("N");      //Printing "N" if seat is empty
   }
   else{
      Serial.print("Y");    //Printing "Y" if seat is full
   }
    if(cm4>45){             // Person is standing
      stand4++;
    }
    else{
      sit4++;
      if(sit4>45){      //If person sits again, initializing to zero
        sit4 = 0;
        stand4 = 0;
      }
    }
    if(stand4>400){       //Person wasn't sitting there for a long time
      flag4 = 3;
    } 
    if(flag4 == 3){  
     Serial.println("N");   //Printing "N" if seat is empty
   }else{
      Serial.println("Y");  //Printing "Y" if seat is full
   }

  if(digitalRead(mode_switch)==HIGH){
       Servo1.write(0);
  }else{
       Servo1.write(70);  
  }
     
   if(digitalRead(board_switch)==HIGH){
        if(count1%2==0){
          board_servo.write(0);
          count1=1;
        }
        if(count1%2==1){
          board_servo.write(180);
          count1=0;
        }   
   }
  
    delay(100);
}

//Function for converting microsecinds to Centimeters.
long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
