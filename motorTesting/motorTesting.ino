//Calibrates the electronic speed controler (esc) and send different speeds to the motors
#include <Servo.h>
#include <SimpleTimer.h>

#define PIN_MOTOR_0	3
#define PIN_MOTOR_2	5
#define PIN_MOTOR_1	9
#define PIN_MOTOR_3	11

SimpleTimer timer;
Servo motor[4];

int motorVelocities[4] = {0};

/* Diagram for motor number assignments
           0
           |
           |
          ###
3 --------###-------- 1
          ###
           |
           |
           2
*/
//Analog read pins
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;

//accelerometer calibration
const int minVal = 180;
const int maxVal = 481;

//accelerometer data
int x;
int y;
int z;

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
	motor[0].attach(PIN_MOTOR_0);
	motor[1].attach(PIN_MOTOR_1);
	motor[2].attach(PIN_MOTOR_2);
	motor[3].attach(PIN_MOTOR_3);
	Serial.println("ESC calibration started"); 
	armSpeedControler();
	Serial.println("ESC calibration completed");
        startUpSequence();
/*	timer.setTimeout(1000, startUpSequence);
	timer.setTimeout(3000, startUpSequence);
	timer.setTimeout(5000, startUpSequence);
	timer.setTimeout(7000, startUpSequence);
	timer.setTimeout(9000, killAllMotors);
*/
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

void balance() {
  if (x > 180) { //increase power to motor 3, decrease to motor 1
    motorVelocities[3] += 360-x;
    motorVelocities[1] -= 360-x;
  } else {  //increase power to motor 1, decrease to motor 3
    motorVelocities[1] += x;
    motorVelocities[3] -= x;
  }
  if (y > 180) { //increase power to motor 0, decrease to motor 2
    motorVelocities[0] += 360 - x;
    motorVelocities[2] -= 360 - x;    
  } else {  //increase power to motor 2, decrease to motor 0
    motorVelocities[2] += x;
    motorVelocities[0] -= x;
  }
}
void loop() {
	timer.run();
        readAccelerometer();
        balance();
	for (int i=0;i<4;i++) {
		motor[i].writeMicroseconds(motorVelocities[i]);
                Serial.print(i);
                Serial.print(": ");
                Serial.print(motorVelocities[i]);
                Serial.print(" | ");
	}
        Serial.println("");
	delay(100);
}
