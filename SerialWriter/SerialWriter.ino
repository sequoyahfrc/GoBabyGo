/* Wireless Joystick Tank Steering Robot Example
 * by: Alex Wende
 * SparkFun Electronics
 * date: 9/28/16
 * 
 * license: Creative Commons Attribution-ShareAlike 4.0 (CC BY-SA 4.0)
 * Do whatever you'd like with this code, use it for any purpose.
 * Please attribute and keep this license.
 * 
 * This is example code for the Wireless Joystick to control a robot
 * using XBee. Plug the first Xbee into the Wireless Joystick board,
 * and connect the second to the SparkFun Serial Motor Driver.
 * 
 * Moving the left and right joystick up and down will change the
 * speed and direction of motor 0 and motor 1. The left trigger will
 * reduce the maximum speed by 5%, while the right trigger button
 * will increase the maximum speed by 5%.
 * 
 * Connections to the motor driver is as follows:
 * XBee - Motor Driver
 *   5V - VCC
 *  GND - GND
 * DOUT - RX
 * 
 * Power the motor driver with no higher than 11V!
 */

#define L_JOYSTICK A3   // Pin used for left joystick
#define R_JOYSTICK A0   // Pin used for right joystick
int16_t leftStick, rightStick;    // We'll store the the analog joystick values here

void setup() {
  Serial1.begin(9600);  
}
void loop() {
  leftStick = analogRead(L_JOYSTICK);
  rightStick = analogRead(R_JOYSTICK);
  Serial1.println("<M,");
  Serial1.print(leftStick);
  Serial1.print(",");
  Serial1.print(rightStick);
  Serial1.println(">");
  delay(100);
}
