/* Things to implement/problems:
    - endStopper: Tempo, Stops when Endstopper == true
    - reading pir when on the Top >> if movmement add delay
    - set position after endStop() == true
    - set final variables
*/





#include <dummy.h>

#include <Arduino.h>
#include <analogWrite.h>

#define pirInputPin     27
#define motorPinL       5
#define motorPinR       18
#define poti1InputPin   34
#define poti2InputPin   35
#define endStopPin      25

const int maxMotorDistance = 5000;
const int motorTime = 10;
const int waitingTime = 3;

int motorSpeed = 2000;
int motorDistance  = 1000;
boolean motorDirection = true;
boolean movement = false;
boolean endStop = false;



void setup() {
  pinMode(endStopPin, INPUT_PULLDOWN);
  pinMode(pirInputPin, INPUT);
  Serial.begin(9600);
  initializing();
  Serial.println("SETUP!");
}

void loop() {
  endStopper();
  //Serial.println(endStop);

  movement = pirRead(pirInputPin);
  if (movement) {
    Serial.println("MOVEMENT!");
    motorDirection = true;
    BalloonRiseAndFall();
    delay(waitingTime * 1000);

  }
}


void endStopper() {
  endStop = false;
  if (digitalRead(endStopPin) == LOW) {
    endStop = false;
  }
  if (digitalRead(endStopPin) == HIGH) {
    endStop = true;
    Serial.println("ENDSTOP");
  }
}

void setDistance() {
  motorDistance = map(analogRead(poti1InputPin), 0, 4095, 0, maxMotorDistance);
}
//void setMotorSpeed() {
//  motorSpeed = map(analogRead(poti1InputPin), 0, 4095, 0, 255);
//}

void initializing() {
  Serial.println("initializing....");
  driveMotor(1, 3, 200);
  //driveMotor(0,3,200);
  stopMotor();
  while (endStop == false) {
    driveMotor(0, 1, 200);
  }
}

void driveMotor(boolean dir, int duration, int tempo) {
  Serial.println("DRIVE");
  duration = duration * 1000;
  if (dir == true) {
    for (int i = 0; i <= duration; i++) {
      endStopper();
      if (endStop == true) {
        i = duration;
      }

      analogWrite(motorPinR, 0);
      analogWrite(motorPinL, tempo);
      delay(1);
    }
  } else if (dir == false) {
    for (int k = 0; k <= duration; k++) {
      endStopper();
      if (endStop == true) {
        k = duration;
      }
      analogWrite(motorPinL, 0);
      analogWrite(motorPinR, tempo);
      delay(1);
    }
  }
}

void BalloonRiseAndFall() {
  Serial.println("START TO RISE");
  setDistance();
  motorSpeed = calculateSpeed(motorTime, motorDistance);
  Serial.println(motorSpeed);
  driveMotor(motorDirection, motorTime, motorSpeed);
  stopMotor();
  delay(waitingTime * 1000);
  Serial.println("START TO FALL");
  motorDirection = !motorDirection;
  driveMotor(motorDirection, motorTime, motorSpeed);
  stopMotor();
  Serial.println("BACK TO BOTTOM");
  motorDirection = !motorDirection;
}

boolean pirRead(int PinToRead) {
  if (digitalRead(PinToRead) == HIGH) {
    return true;
  } else {
    return false;
  }
}

int calculateSpeed(int duration, int distance) {
  int calculatedSpeed = distance / duration;
  Serial.println(calculatedSpeed);
  return map(calculatedSpeed, 0, maxMotorDistance / duration, 0, 255);
}

void stopMotor() {
  driveMotor(motorDirection, 0, 0);
}

void setStartPosition() {
  if (endStop) {
    driveMotor(1, 1, 200);
  }
}


