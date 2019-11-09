#include <EEPROM.h>

int outputPin = 12;
int powerPin = 11;
int colorSelectPin = 10;
byte currentColor = 0;
byte maxColors = 7;
int buttonState = 0;
int lastButtonState = 0;

void setup() {
  pinMode(outputPin, OUTPUT);
  pinMode(powerPin, OUTPUT);
  pinMode(colorSelectPin, INPUT);
  digitalWrite(outputPin, HIGH);

  powerOn();
  restoreColor();
}

void loop() {
  // listen to color change button presses, track the current color
  // and save it to the eeprom
  buttonState = digitalRead(colorSelectPin);
  
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      currentColor++;
      if (currentColor > maxColors)
        currentColor = 0;
      EEPROM.write(0, currentColor);
    }
  }

  lastButtonState = buttonState;
  
  delay(100);
}

void powerOn() {
  digitalWrite(powerPin, LOW);
  delay(150);
  digitalWrite(powerPin, HIGH);
}

void restoreColor() {
  currentColor = EEPROM.read(0);
  for (byte i=0; i<=currentColor; i++) {
    digitalWrite(outputPin, LOW);
    delay(150);
    digitalWrite(outputPin, HIGH);
    delay(150);
  }
}
