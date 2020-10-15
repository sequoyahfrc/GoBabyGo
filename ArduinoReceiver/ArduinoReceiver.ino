// 1000 is full reverse
// 1500 is neutral
// 2000 is full forward

#include <Servo.h>

#define PIN_L 6
#define PIN_R 5

Servo leftMotor;      // Left Motor Servo Object
Servo rightMotor;     // Right Motor Servo Object


void setup()
{
  // Tells each of the servo objects which pin it should output to
  leftMotor.attach(PIN_L);
  rightMotor.attach(PIN_R);

  Serial.begin(9600); // Init serial
  // Set default values because 0 means full reverse
  leftMotor.writeMicroseconds(1500);          //right motor driver code
  rightMotor.writeMicroseconds(1500);          //left motor driver code
}

void loop() {
  if(Serial.available() > 0){
    int xbee=Serial.read();
    
    if(xbee == 65){
      leftMotor.writeMicroseconds(1800);          //right motor driver code
      rightMotor.writeMicroseconds(1800);          //left motor driver code
      Serial.println("Forward");
    }
    else if(xbee == 66){
      leftMotor.writeMicroseconds(1800);          //right motor driver code
      rightMotor.writeMicroseconds(1200);          //left motor driver code
      Serial.println("Turn Right");
    }
    else if(xbee == 67){
      leftMotor.writeMicroseconds(1200);          //right motor driver code
      rightMotor.writeMicroseconds(1200);          //left motor driver code
      Serial.println("Reverse");
    }
    else if(xbee == 68){
      leftMotor.writeMicroseconds(1200);          //right motor driver code
      rightMotor.writeMicroseconds(1800);          //left motor driver code
      Serial.println("Turn Left");
    }
    else if(xbee == 69){
      leftMotor.writeMicroseconds(1500);          //right motor driver code
      rightMotor.writeMicroseconds(1500);          //left motor driver code
      Serial.println("Stop");
    }
    else{
      Serial.println("Out of Range");
    }
  }
}