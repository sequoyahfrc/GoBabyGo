#include <Servo.h>  

#define MOTORL 5
#define MOTORR 6

char incomingByte[10];  
int loc = 0;
Servo left;
Servo right;
int motors[2];

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial.println("Starting");
  do {
    left.attach(MOTORL);
    right.attach(MOTORR);
  }
  while (!left.attached() || !right.attached());
  Serial.println("Attached all servos!");
}

int lStick = 0;
int rStick = 0;
String code = "";
int time = 0;

void loop() {
  for (int i = 52; i <= 53; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  if(Serial3.available()){
    incomingByte[loc] = Serial3.read();
    String debug = "";
    if (incomingByte[loc] < 32 && incomingByte[loc] < 127) {
      debug = "Control character: " + String((int)incomingByte[loc]);
    } else {
      debug = "Character \'" + String(incomingByte[loc]) + "\'";
    }
    //Serial.println("Got " + debug);
    code = String(code + incomingByte[loc]);
    loc++;
  }
  if (incomingByte[loc - 1] == 'W')  { // skip 6 more bytes
    int v = -1;
    for (int i = 0; i <= 5; i++) {
      dump();
      //Serial.println("Skipping init code");
    }
    incomingByte[0] = '\0';
    loc = 0;
    code = "";
  }
  if (incomingByte[loc - 1] == 13) { //end of transmission
    //decode
    dump();
    loc = 0;
    int stickID = incomingByte[1] - 48;
    //Serial.println("Decoding for stick " + String(stickID));
    String digits = "";
    boolean forward = incomingByte[2] == 'F';
    for (int i = 3; incomingByte[i] != '\r'; i++) {
       digits += incomingByte[i];
    }
    int s = digits.toInt();
    if (s > 100) {
      s = 100;
    }
    if (forward) { //F and R are switched!
      s *= -1;
    }
    for (int i = 0; i < strlen(incomingByte); i++) {
      incomingByte[i] = 0;
    }
    motors[1 - stickID] = s;
    time++;
  }
  if (time == 2) {
    time = 0; 
    left.writeMicroseconds(getPWMSpeed(motors[0]));
    right.writeMicroseconds(getPWMSpeed(motors[1]));
    Serial.println("Left: " + String(motors[0]) + " Right: " + String(motors[1]) + " PWML: " + String(getPWMSpeed(motors[0]))
    + " PWMR: " + String(getPWMSpeed(motors[1])) + " Motor L: " + String(left.read()) + " Motor R: " + String(right.read()));
  }
}
int getPWMSpeed(int x) {
  boolean neg = x < 0;
  if (neg) {
    x *= -1;
  }
  if (x == 0) {
    return 1500;
  }
  //1000 to 1460 = reverse
  //1500 = stop
  //1540 to 2000 = forward
  double scaled = ((x / 100.0) * 460.0) + 1540.0;
  if (neg) {
    scaled -= 540.0;
  }
  return (int)scaled;
}
void dump() {
  while (Serial3.read() < 0);
}
