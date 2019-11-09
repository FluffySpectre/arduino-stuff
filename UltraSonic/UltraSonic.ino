#define trigPin 14
#define echoPin 15

#include <SevSeg.h>
SevSeg sevseg;

int nextChirp = 0;
float distance = 0;
float duration = 0;

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};

  bool resistorsOnSegments = false;
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Serial.begin(9600);
}

void loop() {
  if (millis() > nextChirp) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) * 0.0344;

    if (distance < 2) distance = 2;
    if (distance > 400) distance = 400;

    // if (distance >= 400 || distance <= 2) {
      //Serial.print("Distance = ");
      //Serial.println("Out of range");
    // }

    nextChirp = millis() + 100;
  }

  // display the distance on the 7 seg display
  sevseg.setNumber(distance, 1);
  sevseg.refreshDisplay();
}
