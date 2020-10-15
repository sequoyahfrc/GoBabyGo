// 1000 is full reverse
// 1500 is neutral
// 2000 is full forward

#include <Servo.h>

#define IS_SEPERATOR(v) IS_L(v) || IS_R(v)
#define IS_L(v) v == 0x4C // ASCII for L
#define IS_R(v) v == 0x52 // ASCII for R


#define PIN_L 6
#define PIN_R 5
#define MESSAGE_SIZE 3

<<<<<<< HEAD
Servo leftMotor;      // Left Motor Servo Object
Servo rightMotor;     // Right Motor Servo Object

<<<<<<< HEAD
int L, R;
unsigned char* data = (unsigned char*)malloc(MESSAGE_SIZE); // Use malloc to get 3 bytes of RAM; Data: L/R + high + low

=======
>>>>>>> parent of 5994b76... Merge branch 'master' of https://github.com/sequoyahfrc/mobility-wheelchair into master
=======
>>>>>>> parent of 5994b76... Merge branch 'master' of https://github.com/sequoyahfrc/mobility-wheelchair into master
void setup()
{
  // Tells each of the servo objects which pin it should output to
  leftMotor.attach(PIN_L);
  rightMotor.attach(PIN_R);

<<<<<<< HEAD
  Serial.begin(9600); // Init serial
  // Set default values because 0 means full reverse
  L = 1500;
  R = 1500;

  memset(data, 0x00, MESSAGE_SIZE);
}

void loop() {
  if(Serial.available() >= MESSAGE_SIZE){
    Serial.readBytes(data, MESSAGE_SIZE);

    // Only read message if start is 'L' or 'R'
    if (IS_SEPERATOR(data[0])) {
      int high = data[1];
      int low = data[2];
      //HHHHHHHHLLLLLLLL
      int pwm = constrain(((high << 8) | low) - 512, -500, 500) + 1500; // Clamp between -500 and 500, then add 1500 to put it in range
      if (IS_L(data[0])) { // Set left
        L = pwm;
      } else if (IS_R(data[0])) { // Set right
        R = pwm;
      }
    } else {
      unsigned char* temp = (unsigned char *)malloc(1); // Get 1 byte of RAM
      while (!IS_SEPERATOR(temp[0])) {
        temp = Serial.readBytes(temp, 1);
      }
      free(temp); // Clean up RAM because we don't need it anymore
    }

    // Use memset to copy MESSAGE_SIZE 0x00's to data
    // Just sets all the values in data to 0x00 (which is zero)
    memset(data, 0x00, MESSAGE_SIZE); // Reset message data
  }
  leftMotor.writeMicroseconds(L);
  rightMotor.writeMicroseconds(R);
}
=======
  Serial.begin(9600);
  LeftMotor.writeMicroseconds(1500);          //right motor driver code
  RightMotor.writeMicroseconds(1500);          //left motor driver code
}

void loop() {
  if(Serial.available() > 0){
    int xbee=Serial.read();
    
    if(xbee == 65){
      LeftMotor.writeMicroseconds(1800);          //right motor driver code
      RightMotor.writeMicroseconds(1800);          //left motor driver code
      Serial.println("Forward");
    }
    else if(xbee == 66){
      LeftMotor.writeMicroseconds(1800);          //right motor driver code
      RightMotor.writeMicroseconds(1200);          //left motor driver code
      Serial.println("Turn Right");
    }
    else if(xbee == 67){
      LeftMotor.writeMicroseconds(1200);          //right motor driver code
      RightMotor.writeMicroseconds(1200);          //left motor driver code
      Serial.println("Reverse");
    }
    else if(xbee == 68){
      LeftMotor.writeMicroseconds(1200);          //right motor driver code
      RightMotor.writeMicroseconds(1800);          //left motor driver code
      Serial.println("Turn Left");
    }
    else if(xbee == 69){
      LeftMotor.writeMicroseconds(1500);          //right motor driver code
      RightMotor.writeMicroseconds(1500);          //left motor driver code
      Serial.println("Stop");
    }
    else{
      Serial.println("Out of Range");
    }
  }
<<<<<<< HEAD
}
>>>>>>> parent of 5994b76... Merge branch 'master' of https://github.com/sequoyahfrc/mobility-wheelchair into master
=======
}
>>>>>>> parent of 5994b76... Merge branch 'master' of https://github.com/sequoyahfrc/mobility-wheelchair into master
