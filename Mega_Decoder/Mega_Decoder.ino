#include <Servo.h>

//constants

#define MOTORL 5
#define MOTORR 6
#define MESSAGE_LEN 6

//servos
Servo left;
Servo right;

void setup() {

  //init serial

  Serial.begin(9600); //debug log
  Serial3.begin(9600); //x bee

  //attach servos
  do {
    left.attach(MOTORL);
    right.attach(MOTORR);
  }
  while (!left.attached() || !right.attached());
  Serial.println("Attached all servos!");

  // set pin 52 and 53 to high (power for PWM motors)
  for (int i = 52; i <= 53; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  Serial.println("Starting");
}

char message[MESSAGE_LEN];
int offset = 0;

//main loop

void loop() {

  //reset offset once we get to the end of a message

  if (offset == MESSAGE_LEN) {

    //see if we recieved a left motor set

    bool setLeft = message[0] == 'L';

    //if the first character is NOT 'L', make sure it is an 'R'

    if (!setLeft) {
      if (message[0] != 'R') {

        //invalid data was recieved, so exit

        return;
      }
    } else {
      if (message[0] != 'L') {

        //invalid data was recieved, so exit

        return;
      }
    }

    //read values
    //strstr takes 2 parameters
    //the first is the string to search
    //the second is the string to search for
    //returns NULL if it cant find it
    //For example, strstr("L+123", "+") returns "+123"
    //However, strstr("L+123", "-") returns NULL!

    char *val = strstr(message, "+");

    //check if val is null

    if (val == NULL) {
      val = strstr(message, "-");
    }

    //check to see if val is still NULL
    //only happens if there is a data corruption

    if (val == NULL) {

    }

    //atoi() converts a string to an integer
    //For example, atoi("-123") returns -123,
    //However, atoi("123abc456") returns 123!
    //atoi() reads until the first non number or the end

    int speed = atoi(val);

    //Next, limit speed from -100 to 100
    //This is in case we get data corruption and we get "L+999" as our message

    //constrain() takes 3 values
    //the first is the value you want to limit
    //the second is the minimum value
    //the thrid is the maximum value
    //For example, constrain(12345678900, -100, 100) should return 100
    //However, since 12345678900 is WAY more than the 32-bit-signed integer limit (2,147,483,648)
    //it will actually return -100!
    //when 12345678900 is converted to a 32 bit integer, it becomes -539222988
    //in binary, 12345678900 is:
    //1011011111110111000001110000110100
    //in binary, -539222988 is:
    //11011111110111000001110000110100
    //if you line them up you get:
    //1011011111110111000001110000110100 = 12345678900
    //  11011111110111000001110000110100 =  -539222988
    //When converting, it chops off all of the extra bits,
    //and because the left most bit in -539222988 is a 1,
    //that means that it is a negative!
    //if that one bit was flipped, it would be positive

    speed = constrain(speed, -100, 100);

    //Then, convert speed to a PWM value

    speed = getPWMSpeed(speed);

    //Finally, set the motors

    if (setLeft) {
      left.writeMicroseconds(speed);
    } else {
      right.writeMicroseconds(speed);
    }

    //set offset back to 0 to start a new message

    offset = 0;
  }

  //if data is available

  if (Serial3.available()) {

    //read one byte from Serial3

    message[offset] = Serial3.read();

    //check for sync issues!
    //we want the first character of our message to be 'L' or 'R',
    //so if it isnt we can have issues.
    //this code block reads to the end of the message and waits for a new one!
    //the end of our message is a '\n' (line feed)

    if (offset == 0 && (message[0] != 'L' || message[0] != 'R')) {

      //wait for \n (end of message)

      char b = '\0';

      while (b != '\n') {
        if (Serial3.available()) {
          b = Serial3.read();
        }
      }

      //exit loop and wait for next message

      return;
    }

    //increase offset

    offset++;
  }
}

//this converts a value between -100 and 100 to valid PWM values

int getPWMSpeed(int x) {

  //make x positive but remeber if it was negative
  boolean neg = x < 0;
  x = abs(x);

  if (x == 0) {
    return 1500;
  }

  //1000 to 1460 = reverse
  //1500 = stop
  //1540 to 2000 = forward
  //scaled is out PWM value

  double scaled = ((x / 100.0) * 460.0) + 1540.0;

  //if it was negative, shift range from 1540 to 2000 to 1000 to 1540

  if (neg) {
    scaled -= 540.0;
  }

  //return PWM value

  return (int)scaled;
}

//this skips the next incoming byte

void dump() {

  //loop until you recieve a byte and then read it

  while (!Serial3.available());
  Serial3.read();
}
