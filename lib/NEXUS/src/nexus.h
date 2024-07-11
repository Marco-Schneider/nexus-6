#ifndef _NEXUS_H_
#define _NEXUS_H_

#include <stdint.h>
#include <Arduino.h>
#include <QTRSensors.h>
#include <SparkFun_TB6612.h>

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

#define RIGHT_SENSOR 36
#define LEFT_SENSOR 39

void configureLineSensor(QTRSensors &lineSensor);
void calibrateLineSensor(QTRSensors &lineSensor);

#endif