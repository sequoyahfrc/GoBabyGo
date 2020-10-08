//A delay of 1000 to 1460 Microseconds is Proportional Reverse
//A delay of 1460 to 1540 Microseconds is neutral
//A delay of 1540 to 2000 Microseconds is Proportional Forward
//A delay of 2000 Microseconds is Full Forward

#include <Servo.h>


int LeftPin = 6;      //Left Motor pin
Servo LeftMotor;           //Left Motor Servo Object

int RightPin = 5;      //Right Motor pin
Servo RightMotor;           //Right Motor Servo Object

int L, R;

void setup()
{
  // Tells each of the servo objects which pin it should output to
  LeftMotor.attach(LeftPin);
  RightMotor.attach(RightPin);

  Serial.begin(9600);
  LeftMotor.writeMicroseconds(1500);          //right motor driver code
  RightMotor.writeMicroseconds(1500);          //left motor driver code
  L = 1500;
  R = 1500;
}

void loop() {
  if(Serial.available() > 0){
    int xbee = Serial.read();
    
    if(xbee == 0x46){ //F
      L = (1800);          //right motor driver code
      R = (1800);          //left motor driver code
      //Serial.println("Forward");
    }
    else if(xbee == 0x52){ //R
      L = (1800);          //right motor driver code
      R = (1200);          //left motor driver code
      //Serial.println("Turn Right");
    }
    else if(xbee == 0x42){ //B
      L = (1200);          //right motor driver code
      R = (1200);          //left motor driver code
      //Serial.println("Backward");
    }
    else if(xbee == 0x4C){ //L
      L = (1200);          //right motor driver code
      R = (1800);          //left motor driver code
      //Serial.println("Turn Left");
    }
    else if (xbee == 0x53) { //S
      L = (1500);          //right motor driver code
      R = (1500);          //left motor driver code
      //Serial.println("Stop");
    }
    delay(25);
  }
  LeftMotor.writeMicroseconds(L);
  RightMotor.writeMicroseconds(R);
}
