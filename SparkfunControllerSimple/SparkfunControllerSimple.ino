
#define PIN_L A3   // Pin used for left joystick
#define PIN_R A0   // Pin used for right joystick

#define MESSAGE_SIZE 3

unsigned char* data = (unsigned char*)malloc(MESSAGE_SIZE); // Get 3 bytes of RAM

void setup() {  
  Serial1.begin(9600); // Start serial communication with XBee at 9600 baud
  delay(10);
  Serial1.print("W7001\r\n"); // Set the bit in enable register 0x70 to 0x01

  memset(data, 0x00, MESSAGE_SIZE); // Reset data to all zeroes
}

void loop() {1
  int L, R;

  // Read joysticks
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
