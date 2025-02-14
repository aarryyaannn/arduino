// Motor control pins for BTS7960 #1
#define IN1_M1 6  // PWM pin for Motor 1 direction 1
#define IN2_M1 7  // PWM pin for Motor 1 direction 2
#define IN1_M2 8  // PWM pin for Motor 2 direction 1
#define IN2_M2 9  // PWM pin for Motor 2 direction 2

// Motor control pins for BTS7960 #2
#define IN1_M3 10  // PWM pin for Motor 3 direction 1
#define IN2_M3 11  // PWM pin for Motor 3 direction 2
#define IN1_M4 12  // PWM pin for Motor 4 direction 1
#define IN2_M4 13  // PWM pin for Motor 4 direction 2

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set motor control pins as output
  pinMode(IN1_M1, OUTPUT);
  pinMode(IN2_M1, OUTPUT);
  pinMode(IN1_M2, OUTPUT);
  pinMode(IN2_M2, OUTPUT);
  pinMode(IN1_M3, OUTPUT);
  pinMode(IN2_M3, OUTPUT);
  pinMode(IN1_M4, OUTPUT);
  pinMode(IN2_M4, OUTPUT);
}

void loop() {
  // Check if data is available from Bluetooth
  if (Serial.available() > 0) {
    char command = Serial.read(); // Read the incoming command

    // Control motors based on the command
    switch (command) {
      case 'F': // Move forward
        // Set all motors to move forward
        analogWrite(IN1_M1, 255); // Full speed
        analogWrite(IN2_M1, 0);
        analogWrite(IN1_M2, 255); // Full speed
        analogWrite(IN2_M2, 0);
        analogWrite(IN1_M3, 255); // Full speed
        analogWrite(IN2_M3, 0);
        analogWrite(IN1_M4, 255); // Full speed
        analogWrite(IN2_M4, 0);
        break;
      case 'B': // Move backward
        // Set all motors to move backward
        analogWrite(IN1_M1, 0);
        analogWrite(IN2_M1, 255); // Full speed
        analogWrite(IN1_M2, 0);
        analogWrite(IN2_M2, 255); // Full speed
        analogWrite(IN1_M3, 0);
        analogWrite(IN2_M3, 255); // Full speed
        analogWrite(IN1_M4, 0);
        analogWrite(IN2_M4, 255); // Full speed
        break;
      case 'L': // Turn left
        // Set left motors to move backward and right motors to move forward
        analogWrite(IN1_M1, 0);
        analogWrite(IN2_M1, 255); // Full speed
        analogWrite(IN1_M2, 0);
        analogWrite(IN2_M2, 255); // Full speed
        analogWrite(IN1_M3, 255); // Full speed
        analogWrite(IN2_M3, 0);
        analogWrite(IN1_M4, 255); // Full speed
        analogWrite(IN2_M4, 0);
        break;
      case 'R': // Turn right
        // Set left motors to move forward and right motors to move backward
        analogWrite(IN1_M1, 255); // Full speed
        analogWrite(IN2_M1, 0);
        analogWrite(IN1_M2, 255); // Full speed
        analogWrite(IN2_M2, 0);
        analogWrite(IN1_M3, 0);
        analogWrite(IN2_M3, 255); // Full speed
        analogWrite(IN1_M4, 0);
        analogWrite(IN2_M4, 255); // Full speed
        break;
      case 'S': // Stop
        // Stop all motors
        analogWrite(IN1_M1, 0);
        analogWrite(IN2_M1, 0);
        analogWrite(IN1_M2, 0);
        analogWrite(IN2_M2, 0);
        analogWrite(IN1_M3, 0);
        analogWrite(IN2_M3, 0);
        analogWrite(IN1_M4, 0);
        analogWrite(IN2_M4, 0);
        break;
    }
  }
}