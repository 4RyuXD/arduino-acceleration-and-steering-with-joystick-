// Include required libraries
#include <Servo.h>
// Allows us to use the Servo library functions
Servo steer;

// Initialize L293D Chip pins as variables
const int enable = 9;
const int dircont1 = 2;
const int dircont2 = 3;

// Initialize Servo motor pin and joystick pins
const int serv = 7;
const int joyX = A0;
const int joyY = A1;

void setup() {
  // Uncomment this line for joystick trouble shooting
  //Serial.begin(9600); 

  // Set pinModes to allow for accurate OUTPUTS and Inputs
  pinMode(enable, OUTPUT);
  pinMode(dircont1, OUTPUT);
  pinMode(dircont2, OUTPUT);

  // Intialize Servo Motor
  steer.attach(serv);

}

void loop() {
  // Create variables for joystick values
  int x = analogRead(joyX);
  int y = analogRead(joyY);

  // Intializing variable to determine whether joystick is in motion or stationary
  bool stationary = (y >= 480 && y <= 540) && (x >= 480 && x <= 540);
  // Uncomment this as well for joystick troubleshooting
  //Serial.println(y);

  // Convert joystick values into steering angles
  int ang = map(x, 0, 1023, 0, 120);

  // Update servo motor with steering angle
  steer.write(ang);

  // Move DC motor when it is pushed only right or left
  if (x > 550 && y >= 480 && y <= 540) {
    digitalWrite(dircont1, HIGH);
    digitalWrite(dircont2, LOW);

    // Convert joystick values into motor speed and apply speed
    analogWrite(enable, map(x, 0, 1023, 0, 255));
  } else if (x < 470 && y >= 480 && y <= 540) {
    digitalWrite(dircont1, HIGH);
    digitalWrite(dircont2, LOW);

    // Convert joystick values into motor speed and apply speed
    analogWrite(enable, map(x, 0, 1023, 255, 0));
  }

  // Move DC motor when joystick is pushed front or back
  if (y < 470) {
    digitalWrite(dircont1, HIGH);
    digitalWrite(dircont2, LOW);

    // Convert joystick values into motor speed and apply speed
    analogWrite(enable, map(y, 0, 1023, 255, 0));
  } else if (y > 550) {
    digitalWrite(dircont1, LOW);
    digitalWrite(dircont2, HIGH);

    // Convert joystick values into motor speed and apply speed
    analogWrite(enable, map(y, 0, 1023, 0, 255));

    // Turn off DC motor if the joystick is not moving
  } else if (stationary == true) {
    digitalWrite(dircont1, LOW);
    digitalWrite(dircont2, LOW);
    analogWrite(enable, 0);
  }
  // Delay corresponding to buffer
  delay(15);
}
