int leftMotor = 5;
int rightMotor = 6;

void setup() {
  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);
  
 Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0){
    int xbee = Serial.read();
    
    if(xbee == 65){
      analogWrite(leftMotor, 255);
      analogWrite(rightMotor, 255);
      Serial.println("Forward");
    }
    else if(xbee == 66){
      analogWrite(leftMotor, 255);
      analogWrite(rightMotor, 100);
      Serial.println("Turn Right");
    }
    else if(xbee == 67){
      analogWrite(leftMotor, 100);
      analogWrite(rightMotor, 100);
      Serial.println("Reverse");
    }
    else if(xbee == 68){
      analogWrite(leftMotor, 100);
      analogWrite(rightMotor, 255);
      Serial.println("Turn Left");
    }
    else if(xbee == 69){
      analogWrite(leftMotor, 150);
      analogWrite(rightMotor, 150);
      Serial.println("Stop");
    }
    else{
      Serial.println("Out of Range");
    }
  }
}
