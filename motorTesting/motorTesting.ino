//Calibrates the electronic speed controler (esc) and send different speeds to the motors
#include <Servo.h>
#include <SimpleTimer.h>

SimpleTimer timer;
Servo motor[4];

int motorVelocities[4] = {1000};

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
	for (int i=0;i<4;i++) {
		motorVelocities[i] = speed;
	}
	Serial.print("Running all motors at ");
	Serial.println(speed);
}

//sets a specific motor to a certain velocity
void setVelocity(int motor, int velocity) {
	motorVelocities[motor] = velocity;
	Serial.print("Motor ");
	Serial.print(motor);
	Serial.print(" is running at ");
	Serial.println(velocity);
}

//stops all motors
void killAllMotors() {
	constantSpeed(1000);
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
	constantSpeed(1200);
	timer.setTimeout(4000, killAllMotors);
}

void loop() {
	timer.run();
	for (int i=0;i<4;i++) {
		motor[i].writeMicroseconds(motorVelocities[i]);
	}
	delay(100);
}
