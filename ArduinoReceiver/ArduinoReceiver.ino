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

Servo leftMotor;      // Left Motor Servo Object
Servo rightMotor;     // Right Motor Servo Object

int L, R;
unsigned char* data = (unsigned char*)malloc(MESSAGE_SIZE); // Use malloc to get 3 bytes of RAM; Data: L/R + high + low

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
      int high = data[1];
      int low = data[2];
      //HHHHHHHHLLLLLLLL
      int pwm = (high << 8) | low;
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
