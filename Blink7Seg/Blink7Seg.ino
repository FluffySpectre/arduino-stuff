#include <Servo.h>
Servo servo;

#include <SevSeg.h>
SevSeg sevseg;

char eyesOpen[] = { '*', ' ', ' ', '*' };
char eyesClosed[] = { '-', ' ', ' ', '-' };
bool isBlinking;
int nextBlink, endBlink;
int mil;
int lightCal;
int lightVal;

int ledPin= 17;
int sensorPin = 16;
byte mode = 0;
bool incrMode;
bool modeChanged;
int modeChangeTime;

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};

  bool resistorsOnSegments = false;
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

  pinMode(ledPin, OUTPUT);

  lightCal = analogRead(sensorPin);
}

void loop() {
  lightVal = analogRead(sensorPin);
  
  if (lightVal < lightCal - 50) {
    incrMode = true;
    modeChangeTime = millis();
    
    analogWrite(ledPin, 255);
  } else {
    analogWrite(ledPin, 0);

    if (incrMode && millis() > modeChangeTime + 100) {
      incrMode = false;
      mode++;
      if (mode > 1) mode = 0;
      modeChanged = true;
    }
  }
  
  mil = millis();

  if (mode == 0) {
    if (modeChanged) {
      modeChanged = false;
      isBlinking = false;  
    }
    if (!isBlinking && mil > nextBlink) {
      isBlinking = true;
      
      endBlink = mil + 150;
    }
  
    if (isBlinking && mil > endBlink) {
      isBlinking = false;
      nextBlink = mil + random(100, 4000);   
    }
  
    // sevseg.setNumber(1234, 4);
    sevseg.setChars(isBlinking ? eyesClosed : eyesOpen);
  } else if (mode == 1) {
    if (modeChanged) {
      modeChanged = false;  
    }
    sevseg.setNumber(lightVal);
  }
  
  sevseg.refreshDisplay();
}
