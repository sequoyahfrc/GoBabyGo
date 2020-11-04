#include <Servo.h>

#define PIN_L 6
#define PIN_R 5
// Example 5 - Receive with start- and end-markers combined with parsing
Servo left;      // Left Motor Servo Object
Servo right;     // Right Motor Servo Object

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

      // variables to hold the parsed data
char messageFromPC[numChars] = {0};
int leftMotor = 0;
int rightMotor = 0;

boolean newData = false;

//============

void setup() {
  left.attach(PIN_L);
  right.attach(PIN_R);
    Serial.begin(9600);
    Serial.println("This demo expects 3 pieces of data - text, an integer and a floating point value");
    Serial.println("Enter data in this style <HelloWorld, 12, 24.7>  ");
    Serial.println();
    left.writeMicroseconds(1500);          //right motor driver code
  right.writeMicroseconds(1500);  //left motor driver code
  pinMode(52, OUTPUT);
  pinMode(53, OUTPUT);
}

//============

void loop() {
  digitalWrite(52, HIGH);
  digitalWrite(53, HIGH);
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        showParsedData();
        newData = false;
    }
}

//============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC
 
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    leftMotor = atoi(strtokIndx);     // convert this part to an integer

    strtokIndx = strtok(NULL, ",");
    rightMotor = atoi(strtokIndx);     // convert this part to a float

}

//============

void showParsedData() {
    int leftMap = map(leftMotor,0,1023,1200,1800);
    int rightMap = map(rightMotor,0,1023,1800,1200);
    Serial.print("Message ");
    Serial.println(messageFromPC);
    Serial.print("Left ");
    Serial.println(leftMap);
    Serial.print("Right ");
    Serial.println(rightMap);


    left.writeMicroseconds(leftMap);
    right.writeMicroseconds(rightMap);
    
    
}
