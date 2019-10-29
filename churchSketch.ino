#include <dummy.h>

#include <Arduino.h>
#include <analogWrite.h>

#define pirInputPin 25
#define motorPinL 32
#define motorPinR 27
#define poti1InputPin 34
#define poti2InputPin 35
#define endStopPin 19

const int maxMotorTime = 5;
int motorSpeed = 200;
int motorTime = 3;
boolean motorDirection;
boolean movement = false;
boolean endStop = false;

//test




void setup() {
  pinMode(endStopPin, INPUT);
  //pinMode(motorPin, OUTPUT);
  initializing();
  Serial.begin(9600);

}

void loop() {
  //setMotorTime();
  //setMotorSpeed();
  //endStopper();
  //if(endStop == false){
  driveMotor(motorDirection, motorTime, motorSpeed);
  //Serial.println("driven");
  //driveMotor(motorDirection,0,0);
  //delay(3000);

  motorDirection = !motorDirection;
  Serial.println(motorDirection);
  driveMotor(motorDirection, motorTime, motorSpeed);

 //driveMotor(1,3,100);
 //driveMotor(0,3,100);

  //}

  //Serial.println(endStop);

}


void endStopper() {
  if (digitalRead(endStopPin) == LOW) {
    endStop = false;
  } else if (digitalRead(endStopPin) == HIGH) {
    endStop = true;
  }
}

void setMotorTime() {
  motorTime = analogRead(poti1InputPin);//map(analogRead(poti1InputPin),0,4095,0,maxMotorTime);
}
void setMotorSpeed() {
  motorSpeed = map(analogRead(poti2InputPin), 0, 4095, 0, 255);
}

void initializing() {

}

void driveMotor(boolean dir, int duration, int tempo) {
  //Serial.println(dir);

  if (dir == true) {
    Serial.println("LINKS");
    for (int i = 0; i <= duration*1000; i++) {
      analogWrite(motorPinL,tempo);
      analogWrite(motorPinR, 0);
      delay(1);
    }
  }else if (dir == false){
    Serial.println("RECHTS");
    for (int k = 0; k <= duration*1000; k++) {
      analogWrite(motorPinR, tempo);
      analogWrite(motorPinL, 0);
      delay(1);
      
    }
  }
  //tempo = map(tempo,0,4092,0,255);


}


