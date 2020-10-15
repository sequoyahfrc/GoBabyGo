
<<<<<<< HEAD
#define PIN_L A3   // Pin used for left joystick
#define PIN_R A0   // Pin used for right joystick

#define MESSAGE_SIZE 3

unsigned char* data = (unsigned char*)malloc(MESSAGE_SIZE); // Get 3 bytes of RAM
=======
#define L_TRIG 6        // Pin used for left trigger
#define R_TRIG 3        // Pin used for right trigger
#define L_JOYSTICK A3   // Pin used for left joystick
#define R_JOYSTICK A0   // Pin used for right joystick

<<<<<<< HEAD
>>>>>>> parent of 5994b76... Merge branch 'master' of https://github.com/sequoyahfrc/mobility-wheelchair into master
=======
>>>>>>> parent of 5994b76... Merge branch 'master' of https://github.com/sequoyahfrc/mobility-wheelchair into master

void setup() {  
  Serial1.begin(9600); // Start serial communication with XBee at 9600 baud
  delay(10);
  Serial1.print("W7001\r\n"); // Set the bit in enable register 0x70 to 0x01

  memset(data, 0x00, MESSAGE_SIZE); // Reset data to all zeroes
}

void loop() {1
  int L, R;

  // Read joysticks
<<<<<<< HEAD
  L = analogRead(PIN_L);
  R = analogRead(PIN_R);

  // Send data
  
  data[0] = 'L';
  // HHHHHHHHLLLLLLLL
  data[1] = L & (0xFF << 8); // get only H
  data[2] = L & 0xFF; // get only L

  Serial1.write(data, MESSAGE_SIZE);
  memset(data, 0x00, MESSAGE_SIZE); // Reset data, redundant but just to be safe

  data[0] = 'R';
  data[1] = R & (0xFF << 8);
  data[2] = R & 0xFF;

  Serial1.write(data, MESSAGE_SIZE);
  
  delay(25); // Delay to not overload xbee

  memset(data, 0x00, MESSAGE_SIZE); // Reset data to all zeroes
}
=======
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
>>>>>>> parent of 5994b76... Merge branch 'master' of https://github.com/sequoyahfrc/mobility-wheelchair into master
