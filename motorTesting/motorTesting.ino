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



//Analog read pins
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;

//The minimum and maximum values that came from
//the accelerometer while standing still
//You very well may need to change these
int minVal =270;
int maxVal =440;

//to hold the caculated values
double x;
double y;
double z;

void armSpeedControler() {
	Serial.println("Sending lowest throttle to all motors");
        for (int i=0;i<4;i++) {
          motor[i].writeMicroseconds(1000);
        }
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

void startUpSequence() {
	static int speed = 1050;
	constantSpeed(speed);
	speed+=100;
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
	timer.setTimeout(1000, startUpSequence);
	timer.setTimeout(3000, startUpSequence);
	timer.setTimeout(5000, startUpSequence);
	timer.setTimeout(7000, startUpSequence);
	timer.setTimeout(9000, killAllMotors);
}

void readAccelerometer() {
   //read the analog values from the accelerometer
  int xRead = analogRead(xPin);
  int yRead = analogRead(yPin);
  int zRead = analogRead(zPin);

  //convert read values to degrees -90 to 90 - Needed for atan2
  int xAng = map(xRead, minVal, maxVal, -90, 90);
  int yAng = map(yRead, minVal, maxVal, -90, 90);
  int zAng = map(zRead, minVal, maxVal, -90, 90);

  //Caculate 360deg values like so: atan2(-yAng, -zAng)
  //atan2 outputs the value of -PI to PI (radians)
  //We are then converting the radians to degrees
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  //Output the caculations
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" | y: ");
  Serial.print(y);
  Serial.print(" | z: ");
  Serial.println(z);
}

void loop() {
	timer.run();
        readAccelerometer();
	for (int i=0;i<4;i++) {
		motor[i].writeMicroseconds(motorVelocities[i]);
	}
	delay(100);
}
