//A delay of 1000 to 1460 Microseconds is Proportional Reverse
//A delay of 1460 to 1540 Microseconds is neutral
//A delay of 1540 to 2000 Microseconds is Proportional Forward
//A delay of 2000 Microseconds is Full Forward

#include <Servo.h>

#define IS_SEPERATOR(v) IS_L(v) || IS_L(v)
#define IS_L(v) v == 0x4C // ASCII for L
#define IS_R(v) v == 0x52 // ASCII for R


#define PIN_L 6
#define PIN_R 5
#define MESSAGE_SIZE 3

Servo leftMotor;      // Left Motor Servo Object
Servo rightMotor;     // Right Motor Servo Object

int L, R;
unsigned char* data = (unsigned char*)malloc(MESSAGE_SIZE); // Use malloc to get 3 bytes; Data: L/R + high + low

void setup()
{
  // Tells each of the servo objects which pin it should output to
  leftMotor.attach(PIN_L);
  rightMotor.attach(PIN_R);

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
      
    }
    
    memset(data, 0x00, MESSAGE_SIZE); // Reset message data
  }
  leftMotor.writeMicroseconds(L);
  rightMotor.writeMicroseconds(R);
}
