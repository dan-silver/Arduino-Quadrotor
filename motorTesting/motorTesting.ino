//Calibrates the electronic speed controler (esc) and send different speeds to the motors
#include <Servo.h>

Servo motor[4];

#define PIN_MOTOR_1	3
#define PIN_MOTOR_2	5
#define PIN_MOTOR_3	9
#define PIN_MOTOR_4	11

void armSpeedControler() {
	delay(3000);
	Serial.println("Sending lowest throttle to all motors");
	motor[0].writeMicroseconds(1000);
	motor[1].writeMicroseconds(1000);
	motor[2].writeMicroseconds(1000);
	motor[3].writeMicroseconds(1000);
	delay(2000);
	Serial.println("Low throttle sent");
}

//holds all motors at a constant speed
void constantSpeed(int speed) {
	motor[0].writeMicroseconds(speed);
	motor[1].writeMicroseconds(speed);
	motor[2].writeMicroseconds(speed);
	motor[3].writeMicroseconds(speed);
	Serial.print("Running motors at ");
	Serial.println(speed);
}

void setup() {
	Serial.begin(9600);
	motor[0].attach(PIN_MOTOR_1);
	motor[1].attach(PIN_MOTOR_2);
	motor[2].attach(PIN_MOTOR_3);
	motor[3].attach(PIN_MOTOR_4);
	Serial.println("ESC calibration started"); 
	armSpeedControler();
	Serial.println("ESC calibration completed");
}

void loop() {
	constantSpeed(1050);
/**	for (int i=1000;i<=1150;i+=5) {
		motor[0].writeMicroseconds(i);
		motor[1].writeMicroseconds(i);
		motor[2].writeMicroseconds(i);
		motor[3].writeMicroseconds(i);
		Serial.println(i);
		delay(100);
	}
	for (int i=1150;i>=1000;i-=5) {
		motor[0].writeMicroseconds(i);
		motor[1].writeMicroseconds(i);
		motor[2].writeMicroseconds(i);
		motor[3].writeMicroseconds(i);
		Serial.println(i);
		delay(100);
	}
**/
	delay(100);
}
