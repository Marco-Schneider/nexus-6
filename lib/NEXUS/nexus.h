#ifndef _NEXUS_H_
#define _NEXUS_H_

#include <stdint.h>

#define LED_BUILTIN 2

// TB6612FNG pinout
#define AIN1 18
#define BIN1 21
#define AIN2 5
#define BIN2 22
#define PWMA 2
#define PWMB 23
#define STBY 19

#define SPEED 255

const uint8_t numberOfSensors = 8;
uint8_t lineSensorPins[numberOfSensors] = {34, 35, 32, 33, 25, 26, 27, 14};

#define RIGHT_SENSOR 36
#define LEFT_SENSOR 39

#endif