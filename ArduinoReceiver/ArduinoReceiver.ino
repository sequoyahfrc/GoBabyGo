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
    if(Serial.read()== 76){ //Looks for letter L
      int input = Serial.parseInt();  // keep other operations outside the constrain function
      int constrainedInput = constrain(input, 0, 2000);
      leftMotor.writeMicroseconds(constrainedInput);
    }
    else if(Serial.read()== 82){ //Looks for letter R
      int input = Serial.parseInt();  // keep other operations outside the constrain function
      int constrainedInput = constrain(input, 0, 2000);
      rightMotor.writeMicroseconds(constrainedInput);
    }
    else{ // No letters, turns off the motors
        leftMotor.writeMicroseconds(1500);          //sets to neutral
        rightMotor.writeMicroseconds(1500); 
    }
  }
}