#include "nexus.h"

const uint8_t numberOfSensors = 8;
uint8_t lineSensorPins[numberOfSensors] = {34, 35, 32, 33, 25, 26, 27, 14};

void configureLineSensor(QTRSensors &lineSensor) {
    lineSensor.setTypeAnalog();
    lineSensor.setSensorPins(lineSensorPins, numberOfSensors);
    lineSensor.setTimeout(1000);
    
    delay(1000);
}

void calibrateLineSensor(QTRSensors &lineSensor) {

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
        
    for(uint16_t i=0; i<500; i++) {
        lineSensor.calibrate();
    }

    for(uint16_t i=0; i<11; i++) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(500);
    }

}

float mapLinePosition(float x, float inMin, float inMax, float outMin, float outMax) {
    return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}