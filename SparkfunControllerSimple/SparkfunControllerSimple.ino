
#define L_TRIG 6        // Pin used for left trigger
#define R_TRIG 3        // Pin used for right trigger
#define L_JOYSTICK A3   // Pin used for left joystick
#define R_JOYSTICK A0   // Pin used for right joystick


void setup() {  
  Serial1.begin(9600); // Start serial communication with XBee at 9600 baud
  delay(10);
  Serial1.print("W7001\r\n"); // Set the bit in enable register 0x70 to 0x01
}

void loop() {
  int16_t leftStick, rightStick;    // We'll store the the analog joystick values here

  // Read joysticks
  // Convert analog value range to motor speeds (in %)
  leftStick = analogRead(L_JOYSTICK); //~1023 up, ~7-9 down
  rightStick = analogRead(R_JOYSTICK); //~1023 up, ~7-9 down

   if (leftStick > 1000 && rightStick > 1000) {
      SerialUSB.println("Forward");
      Serial1.print('A');
    }
    else if ( leftStick > 1000 && rightStick < 400) {
     SerialUSB.println("Turn Right");
      Serial1.print('B');
    }
    else if (leftStick < 400 && rightStick < 400) {
      SerialUSB.println("Reverse");
      Serial1.print('C');
    }
    else if (leftStick < 400 && rightStick > 1000) {
      SerialUSB.println("Turn Left");
      Serial1.print('D');
    }
    else {
      SerialUSB.println("Stop");
      Serial1.print('E');
    }
    delay(50);
}//end loop
