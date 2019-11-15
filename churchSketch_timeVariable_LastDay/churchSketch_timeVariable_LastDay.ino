
#include <dummy.h>

#include <Arduino.h>
#include <analogWrite.h>

#define pirInputPin     27
#define motorPinL       5
#define motorPinR       18
#define poti1InputPin   34
#define poti2InputPin   35
#define endStopPin      25

const long maxMotorDistance = 700;
const long minMotorDistance = 200;
const int maxMotorTime = 72;
const int minMotorTime = 13;
const int waitingTime = 60;

int motorTime;
int motorSpeed = 2000;
long motorDistance  = 1000;
boolean motorDirection = true;
boolean movement = false;
boolean endStop = false;



void setup() {
  pinMode(endStopPin, INPUT_PULLDOWN);
  pinMode(pirInputPin, INPUT);
  Serial.begin(9600);
  initializing();
}

void loop() {
  //endStop = false;
  endStopper();
  //Serial.println(endStop);

  movement = pirRead(pirInputPin);
  if (movement) {
    //Serial.println("MOVEMENT!");
    motorDirection = true;
    BalloonRiseAndFall();
    

  }
}


void endStopper() {
  //endStop = false;
  if (digitalRead(endStopPin) == HIGH) {
    endStop = true;
    //Serial.println("ENDSTOP");
    stopMotor();
    setStartPosition();    
  }else if (digitalRead(endStopPin) == LOW) {
    endStop = false;
  }
}

void setDistance() {
  //motorDistance = map(analogRead(poti1InputPin), 1, 4094, minMotorDistance, maxMotorDistance);
  motorDistance = map(analogRead(poti1InputPin), 0, 4094, minMotorDistance, maxMotorDistance);
}
void setMotorTime() {
  motorTime = map(analogRead(poti1InputPin), 0, 4095, minMotorTime, maxMotorTime);
}

void initializing() {
  //Serial.println("initializing....");
  driveMotor(1, 1, 255);
  //driveMotor(0,3,200);
  stopMotor();
  while (endStop == false) {
    driveMotor(0, 1, 255);
  }
}

void driveMotor(boolean dir, int duration, int tempo) {
  //Serial.println("DRIVE");
  duration = duration * 1000;
  if (dir == 1) {
    for (int i = 0; i <= duration; i++) {
      endStopper();
      if (endStop == true) {  
        //setStartPosition();
        i = duration;
      }
      analogWrite(motorPinR, 0);
      analogWrite(motorPinL, tempo);

      delay(1);
    }
  }
  if (dir == 0) {
    for (int k = 0; k <= duration; k++) {
      endStopper();
      if (endStop == true) {       
        //setStartPosition();
        k = duration;
      }
      analogWrite(motorPinL, 0);
      analogWrite(motorPinR, tempo);
     
      delay(1);
    }
  }
}

void BalloonRiseAndFall() {
  //Serial.println("START TO RISE");
  motorDirection = 1;
  //setDistance();
  //motorSpeed = calculateSpeed(motorTime, motorDistance);
  setMotorTime();
  motorSpeed = 180;
  //Serial.println(motorSpeed);
  driveMotor(1, motorTime, motorSpeed);
  stopMotor();
  delay(waitingTime * 1000);
  while(pirRead(pirInputPin)){
    delay(waitingTime*1000);
  }
  //Serial.println("START TO FALL");
  motorDirection = !motorDirection;
  //driveMotor(0, motorTime*1.5, motorSpeed);
  while (endStop == false) {
    driveMotor(0, 1, motorSpeed);
  }
  stopMotor();
  //setStartPosition();
  //Serial.println("BACK TO BOTTOM");
  motorDirection = !motorDirection;
  //delay(waitingTime * 1000);
}

boolean pirRead(int PinToRead) {
  if (digitalRead(PinToRead) == HIGH) {
    return true;
  } else {
    return false;
  }
}

//int calculateSpeed(int duration, int distance) {
//  int calculatedSpeed = distance / duration;
//  Serial.println("Speed: "+calculatedSpeed);
//  return map(calculatedSpeed, minMotorDistance / duration, maxMotorDistance / duration, 150, 254);
//}

void stopMotor() {
  //driveMotor(0, 0, 0);
  analogWrite(motorPinR, 0);
  analogWrite(motorPinL, 0);
}

void setStartPosition() {
  //if (endStop) {
    //Serial.println("correction");
    
    for (int e=0;e<50;e++){     
      analogWrite(motorPinR, 0);
      analogWrite(motorPinL, 255);
      delay(1);
    }
  
      analogWrite(motorPinR, 0);
      analogWrite(motorPinL, 0);
      delay(1000);
      //endStop = true;
      //delay(waitingTime * 1000);
    //delay(500);
    //endStop = false;
    //loop();
    
    //driveMotor(1, 5, 200);
  //}
}


