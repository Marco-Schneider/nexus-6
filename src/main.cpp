#include <Arduino.h>
#include <nexus.h>
#include <PID.h>
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

QTRSensors lineSensor;

Motor leftMotor = Motor(AIN1, AIN2, PWMA, 1, STBY);
Motor rightMotor = Motor(BIN1, BIN2, PWMB, 1, STBY);

PIDController pid;

BluetoothSerial SerialBT;
#define BLUETOOTH_NAME "Nexus-6"

uint16_t lineSensorReadings[8];

void setup() {
    SerialBT.begin(BLUETOOTH_NAME);
    
    configureLineSensor(lineSensor);

    pid.updateConstants(0, 0, 0);
    pid.updateSetpoint(0.0);
}

void loop() {

    if(SerialBT.available()) {
        String serialInput = SerialBT.readString();
        Serial.println(serialInput);
        delay(3000);

        if(serialInput == "a") {
            SerialBT.print("//---Calibration started---//");
            calibrateLineSensor(lineSensor);
            SerialBT.print("//---Calibration finished---//");
        }
        else if(serialInput == "b") {
            SerialBT.println("//---Starting track---//");
            SerialBT.println("//---Turning off the bluetooth---//");
            // SerialBT.flush();
            // SerialBT.disconnect();
            // SerialBT.end();
            digitalWrite(2, LOW);
            delay(1000);

            pid.getStartTime(esp_timer_get_time());
            for(;;) {
                float linePosition = mapLinePosition(
                    lineSensor.readLineWhite(lineSensorReadings),
                    0.0,
                    7000.0,
                    -1.0,
                    1.0
                );
                float correction = pid.calculateCorrection(linePosition);
                SerialBT.print("linePosition: ");
                SerialBT.println(linePosition);
                SerialBT.print("Correction: ");
                SerialBT.println(correction);
            }

            SerialBT.begin(BLUETOOTH_NAME);
            SerialBT.println("//---Restarted the bluetooth---//");
            delay(1000);
            digitalWrite(2, HIGH);
        }
        else if(serialInput == "c") {
            SerialBT.println("//---Testing Motors---//");
            SerialBT.println("//---Turning off the bluetooth---//");
            SerialBT.flush();
            SerialBT.disconnect();
            SerialBT.end();
            digitalWrite(2, LOW);
            delay(1000);

            leftMotor.drive(100);
            rightMotor.drive(100);
            delay(10000);

            leftMotor.drive(-100);
            rightMotor.drive(-100);
            delay(10000);

            SerialBT.begin(BLUETOOTH_NAME);
            SerialBT.println("//---Restarted the bluetooth---//");
            delay(1000);
            digitalWrite(2, HIGH);
        }
        else if(serialInput == "e") {
        //   SerialBT.println("//---Printing track information---//");
        //   track.printTrackInformation(SerialBT);
        }
        else if(serialInput == "Cliente Conectado!" || serialInput ==  "Cliente Desconectado!"){
        //   SerialBT.println(serialInput);
        //   SerialBT.print("\nTotal time (s): ");
        //   SerialBT.println((totalLapTime/1000)%60);
        }
        else {
            //formato do dado recebido
            //           kP     ki      kD     Vel
            //        d;000.000;000.000;000.000;000
            //Carac.     2-9     10-17   18-25   26-29

            SerialBT.println("//---Configuring PID constants---//");

            String rawKp = serialInput.substring(2,9);
            double kP = rawKp.toDouble();

            String rawKi = serialInput.substring(10,17);
            double kI = rawKi.toDouble();

            String rawKd = serialInput.substring(18,25);
            double kD = rawKd.toDouble();

            String rawSpeed = serialInput.substring(26,29);
            int speed = rawSpeed.toInt();

            pid.updateConstants(kP, kI, kD);

        }
    }
}