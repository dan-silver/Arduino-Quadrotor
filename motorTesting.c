//Calibrates the electronic speed controler (esc) and send different speeds to the motors
#include <Servo.h>

Servo motor[2];

#define PIN_MOTOR_1	9
#define PIN_MOTOR_2	10

void armSpeedControler() {
	delay(5000);
	Serial.println("Sending lowest throttle to all motors");
	motor[0].writeMicroseconds(1000);
	motor[1].writeMicroseconds(1000);
	delay(2000);
	Serial.println("Low throttle sent");
}

//holds all motors at a constant speed
void constantSpeed(int speed) {
	motor[0].writeMicroseconds(speed);
	motor[1].writeMicroseconds(speed);
	Serial.print("Running motors at ");
	Serial.println(speed);
}

void setup() {
	Serial.begin(9600);
	motor[0].attach(PIN_MOTOR_1);
	motor[1].attach(PIN_MOTOR_2);
	Serial.println("ESC calibration started"); 
	armSpeedControler();
	Serial.println("ESC calibration completed");
}

void loop() {
	constantSpeed(1050);
/**	for (int i=1000;i<=1350;i+=5) {
		motor[0].writeMicroseconds(i);
		motor[1].writeMicroseconds(i);
		Serial.println(i);
		delay(100);
	}
	for (int i=1350;i>=1000;i-=5) {
		motor[0].writeMicroseconds(i);
		motor[1].writeMicroseconds(i);
		Serial.println(i);
		delay(100);
	}
**/
	delay(100);
}