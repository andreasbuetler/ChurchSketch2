#include <dummy.h>

#include <Arduino.h>
#include <analogWrite.h>

#define pirInputPin     25
#define motorPinL       32
#define motorPinR       27
#define poti1InputPin   34
#define poti2InputPin   35
#define endStopPin      19

const int maxMotorTime = 5;
int motorSpeed = 200;
int motorTime = 3;
boolean motorDirection;
boolean movement = false;
boolean endStop = false;



void setup() {
  pinMode(endStopPin, INPUT);
  pinMode(pirInputPin, INPUT);
  initializing();
  Serial.begin(9600);
}

void loop() {
  movement = pirRead(pirInputPin);
  if (movement){
    //Serial.println("MOVEMENT!");
    }
  setMotorTime();
  setMotorSpeed();
  endStopper();
  if (endStop == false) {
    driveMotor(motorDirection, motorTime, motorSpeed);
    delay(3000);
    motorDirection = !motorDirection;
    driveMotor(motorDirection, motorTime, motorSpeed);
  } else {
    motorDirection = !motorDirection;
    driveMotor(motorDirection, 0, 0);
  }
  Serial.println(digitalRead(endStopPin));
}


void endStopper() {
  if (digitalRead(endStopPin) == LOW) {
    endStop = false;
  } else if (digitalRead(endStopPin) == HIGH) {
    endStop = true;
  }
}

void setMotorTime() {
  motorTime = map(analogRead(poti1InputPin), 0, 4095, 0, maxMotorTime);
}
void setMotorSpeed() {
  motorSpeed = map(analogRead(poti2InputPin), 0, 4095, 0, 255);
}

void initializing() {
}

void driveMotor(boolean dir, int duration, int tempo) {
  if (dir == true) {
    for (int i = 0; i <= duration * 1000; i++) {
      analogWrite(motorPinL, tempo);
      analogWrite(motorPinR, 0);
      delay(1);
    }
  } else if (dir == false) {
    for (int k = 0; k <= duration * 1000; k++) {
      analogWrite(motorPinR, tempo);
      analogWrite(motorPinL, 0);
      delay(1);
    }
  }
}

boolean pirRead(int PinToRead) {
  if (digitalRead(PinToRead) == LOW) {
    return true;
  } else {
    return false;
  }
}

