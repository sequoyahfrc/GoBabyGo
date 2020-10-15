

#define PIN_L A3   // Pin used for left joystick
#define PIN_R A0   // Pin used for right joystick
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

   Serial1.print('L');
   Serial1.print(leftStick);
   Serial1.print('R');
   Serial1.print(rightStick); 
   SerialUSB.print('L');
   SerialUSB.println(leftStick);
   SerialUSB.print('R');
   SerialUSB.println(rightStick); 
    delay(500);
}//end loop
