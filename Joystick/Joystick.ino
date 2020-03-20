#define L_JOYSTICK A0   // Pin used for left joystick
#define R_JOYSTICK A3   // Pin used for right joystick

//You can tweak this value to your liking!

#define SEND_DELAY 50

void setup() {  
  Serial1.begin(9600); // Start serial communication with XBee at 9600 baud
}

void loop() {

  //temporary values
  
  short leftStick;
  short rightStick;
  char buf0[6];
  char buf1[6];

  //joystick values go from 930 to 0
  //full reverse is 930, full forward is 0
  //divide by 930 to get a value between -1 and 0
  //multiply by -200 to convert it to a value betwee -200 and 0
  //add 100 to shift range to be between -100 and 100
  
  leftStick = ((analogRead(L_JOYSTICK) / 930) * -200) + 100;
  rightStick = ((analogRead(R_JOYSTICK) / 930) * -200) + 100;

  //add a '+' or a '-' to tell if the number is positive or negative
  //instead of using an if statement here, I used an inline if
  //the syntax for an inline if is as follows:
  //condition ? value if true : value if false
  //For example, the code 2 + 2 == 4 ? "yes" : "no"
  //would be "yes" because the condition "2 + 2 == 4" is true
  
  char isLeftPositive = leftStick >= 0 ? '+' : '-';
  char isRightPositive = rightStick >= 0 ? '+' : '-';

  //put values in buffer
  //sprinf() takes at least 2 paramaters
  //the first is the buffer you want to write to
  //the second is the format string you want to write to the buffer
  //see http://www.cplusplus.com/reference/cstdio/printf/ for format charatcers
  
  sprintf(buf0,"L%s%03d\n", isLeftPositive, abs(leftStick));
  sprintf(buf1,"R%s%03d\n", isRightPositive, abs(rightStick));

  // Send motor speeds
  delay(SEND_DELAY);
  Serial1.print(buf0);
  delay(SEND_DELAY);
  Serial1.print(buf1);
}
