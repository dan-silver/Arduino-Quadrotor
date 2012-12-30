//Calibrates the electronic speed controler (esc) and send different speeds to the motors
#include <Servo.h>

Servo motor;

#define PIN_MOTOR	9

void armSpeedControler() {
  delay(5000);
  Serial.println("Sending lowest throttle");
  motor.writeMicroseconds(1000);
  delay(2000);
  Serial.println("Low throttle sent");
}

void setup() {
  Serial.begin(9600);
  motor.attach(PIN_MOTOR);
  Serial.println("ESC calibration started"); 
  armSpeedControler();
  Serial.println("ESC calibration completed");
}

void loop() {
      for (int i=1050;i<=1450;i+=100) {
        motor.writeMicroseconds(i);	
        Serial.println(i);
        delay(2000);
      }
}