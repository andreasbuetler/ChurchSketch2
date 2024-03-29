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

const long maxMotorDistance = 700000;
const long minMotorDistance = 200000;
const int motorTime = 40;
const int waitingTime = 3;

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
  //Serial.println("SETUP!");
}

void loop() {
  endStopper();
  //Serial.println(endStop);

  movement = pirRead(pirInputPin);
  if (movement) {
    //Serial.println("MOVEMENT!");
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
    //Serial.println("ENDSTOP");
    stopMotor();
    setStartPosition();
    
  }
}

void setDistance() {
  motorDistance = map(analogRead(poti1InputPin), 1, 4094, minMotorDistance, maxMotorDistance);
}
//void setMotorSpeed() {
//  motorSpeed = map(analogRead(poti1InputPin), 0, 4095, 0, 255);
//}

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
            analogWrite(motorPinR, 0);
      analogWrite(motorPinL, tempo);
      if (endStop == true) {  
        //setStartPosition();
        i = duration;
      }

      delay(1);
    }
  }
  if (dir == 0) {
    for (int k = 0; k <= duration; k++) {
      endStopper();
      analogWrite(motorPinL, 0);
      analogWrite(motorPinR, tempo);
      if (endStop == true) {       
        //setStartPosition();
        k = duration;
      }
     
      delay(1);
    }
  }
}

void BalloonRiseAndFall() {
  //Serial.println("START TO RISE");
  motorDirection = 1;
  setDistance();
  motorSpeed = calculateSpeed(motorTime, motorDistance);
  Serial.println(motorSpeed);
  driveMotor(1, motorTime, motorSpeed);
  stopMotor();
  delay(waitingTime * 1000);
  while(pirRead(pirInputPin)){
    delay(waitingTime*1000);
  }
  Serial.println("START TO FALL");
  motorDirection = !motorDirection;
  driveMotor(0, motorTime*1.2, motorSpeed);
  stopMotor();
  //Serial.println("BACK TO BOTTOM");
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
  Serial.println("Speed: "+calculatedSpeed);
  return map(calculatedSpeed, minMotorDistance / duration, maxMotorDistance / duration, 150, 254);
}

void stopMotor() {
  //driveMotor(0, 0, 0);
  analogWrite(motorPinR, 0);
  analogWrite(motorPinL, 0);
}

void setStartPosition() {
  if (endStop) {
    //Serial.println("correction");
    
    for (int e=0;e<=100;e++){     
      analogWrite(motorPinR, 0);
      analogWrite(motorPinL, 200);
    }
      analogWrite(motorPinR, 0);
      analogWrite(motorPinL, 0);
    //delay(500);
    //endStop = false;
    //loop();
    
    //driveMotor(1, 5, 200);
  }
}


