#include <EEPROM.h>

#define HALL_SENSOR_PIN 2   
#define WHEEL_CIRCUMFERENCE 2.1  
#define LOG_INTERVAL 1000   
#define EEPROM_ADDR 0       

volatile int pulseCount = 0;
unsigned long lastTime = 0;
float speed = 0;
int logIndex = 0;


void countPulses() {
    pulseCount++;
}

void setup() {
    Serial.begin(115200);  
    pinMode(HALL_SENSOR_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), countPulses, RISING);
}

void loop() {
    unsigned long currentTime = millis();
    
    
    if (currentTime - lastTime >= LOG_INTERVAL) {
        detachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN)); 

        float timeElapsed = (currentTime - lastTime) / 1000.0;  
        float wheelRPM = (pulseCount / timeElapsed) * 60;       
        speed = (wheelRPM * WHEEL_CIRCUMFERENCE * 60) / 1000;   

        
        Serial.print("Speed: ");
        Serial.print(speed);
        Serial.println(" km/h");

        
        if (logIndex < EEPROM.length() - sizeof(float)) { 
            EEPROM.put(logIndex, speed);
            logIndex += sizeof(float);
        }

        
        pulseCount = 0;
        lastTime = currentTime;
        
        attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), countPulses, RISING);
    }
}
