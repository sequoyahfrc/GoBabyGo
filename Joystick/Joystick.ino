#define L_TRIG 6        // Pin used for left trigger
#define R_TRIG 3        // Pin used for right trigger
#define L_JOYSTICK A0   // Pin used for left joystick
#define R_JOYSTICK A3   // Pin used for right joystick

int8_t speedLevel = 20; //Maximum speed (%) = speedLevel * 5 (units are percent)

void setup() {  
  Serial1.begin(9600); // Start serial communication with XBee at 9600 baud
  delay(10);
  
  Serial1.print("W7001\r\n"); // Set the bit in enable register 0x70 to 0x01

  pinMode(L_TRIG,INPUT_PULLUP); // Enable pullup resistor for left trigger
  pinMode(R_TRIG,INPUT_PULLUP); // Enable pullup resistor for right trigger
}

void loop() {
  int16_t leftStick, rightStick;    // We'll store the the analog joystick values here
  char buf0[10],buf1[10]; // character buffers used to set motor speed
  // Read joysticks
  // Convert analog value range to motor speeds (in %)
  leftStick = (5-(analogRead(L_JOYSTICK)/93))*speedLevel;
  rightStick = (5-(analogRead(R_JOYSTICK)/93))*speedLevel;
  // Build motor 0 buffer
  if(leftStick > 0)
  {
    sprintf(buf0,"M0F%d\r\n",leftStick);
  }
  else
  {
    sprintf(buf0,"M0R%d\r\n",abs(leftStick));
  }

  // Build motor 1 buffer
  if(rightStick > 0)
  {
    sprintf(buf1,"M1F%d\r\n",rightStick);
  }
  else
  {
    sprintf(buf1,"M1R%d\r\n",abs(rightStick));
  }

  // Send motor speeds
  delay(50);
  Serial1.print(buf0);
  delay(50);
  Serial1.print(buf1);
}
