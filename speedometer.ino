#include <EEPROM.h>

#define HALL_SENSOR_PIN 2   // Hall Effect Sensor on digital pin 2 (Interrupt)
#define WHEEL_CIRCUMFERENCE 2.1  // in meters (adjust based on actual wheel size)
#define LOG_INTERVAL 1000   // Log data every 1 second (1000 ms)
#define EEPROM_ADDR 0       // EEPROM Start Address for logging

volatile int pulseCount = 0;
unsigned long lastTime = 0;
float speed = 0;
int logIndex = 0;

// Interrupt service routine (ISR) for counting pulses
void countPulses() {
    pulseCount++;
}

void setup() {
    Serial.begin(115200);  // Baud rate for communication with Raspberry Pi
    pinMode(HALL_SENSOR_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), countPulses, RISING);
}

void loop() {
    unsigned long currentTime = millis();
    
    // Calculate speed every second
    if (currentTime - lastTime >= LOG_INTERVAL) {
        detachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN)); // Stop counting temporarily

        float timeElapsed = (currentTime - lastTime) / 1000.0;  // Convert to seconds
        float wheelRPM = (pulseCount / timeElapsed) * 60;       // Convert to RPM
        speed = (wheelRPM * WHEEL_CIRCUMFERENCE * 60) / 1000;   // Speed in km/h

        // Send speed data to Raspberry Pi via Serial
        Serial.print("Speed: ");
        Serial.print(speed);
        Serial.println(" km/h");

        // Store speed in EEPROM
        if (logIndex < EEPROM.length() - sizeof(float)) { // Prevent overflow
            EEPROM.put(logIndex, speed);
            logIndex += sizeof(float);
        }

        // Reset for next cycle
        pulseCount = 0;
        lastTime = currentTime;
        
        attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), countPulses, RISING);
    }
}
