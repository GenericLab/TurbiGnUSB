/*---------------------------------------------------------------------------------------------

  CocoKeyboard Library 2016 by Iyok
  install the Coconut from https://cocomake7.github.io/

  The following code is for use with the TurbdityGnUSB, a photometer/turbidity meter.
  see more: https://github.com/GenericLab/TurbiGnUSB
  
 */

#include "CocoKeyboard.h"

int sensorValue;
int buttonState = 0;         // variable for reading the pushbutton status

const int analogInPin = A2;  // Analog input pin that the potentiometer is attached to
const int buttonPin = 2;     // the number of the pushbutton pin
const int SensorLEDPin = 1;     // the number of the pushbutton pin
const int LEDPin = 0;     // the number of the pushbutton pin


void setup() {
  
    pinMode(buttonPin, INPUT);
    digitalWrite(buttonPin, HIGH);
    pinMode(SensorLEDPin, OUTPUT);
    pinMode(LEDPin, OUTPUT);

    digitalWrite(LEDPin, HIGH);
    digitalWrite(SensorLEDPin, LOW);   // turn the LED on (HIGH is the voltage level)
    CocoKeyboard.delay(100);
    digitalWrite(LEDPin, LOW);
    digitalWrite(SensorLEDPin, HIGH);
    CocoKeyboard.delay(100);
    digitalWrite(LEDPin, HIGH);
    digitalWrite(SensorLEDPin, LOW);
    CocoKeyboard.delay(100);
    digitalWrite(LEDPin, LOW);
    digitalWrite(SensorLEDPin, HIGH);
    CocoKeyboard.delay(100);
    
  
  // don't need to set anything up to use CocoKeyboard
}


void loop() {
  
  buttonState = digitalRead(buttonPin);

    if (buttonState == LOW) {

          digitalWrite(LEDPin, HIGH);
          digitalWrite(SensorLEDPin, LOW); // turn the LED on
          CocoKeyboard.delay(50);
          sensorValue = analogRead(analogInPin);
          CocoKeyboard.delay(50);
          digitalWrite(LEDPin, LOW);
          digitalWrite(SensorLEDPin, LOW); // Leave the LED on
    // Type out this string letter by letter on the computer (assumes US-style
    // keyboard)
  
    CocoKeyboard.println(sensorValue);
  
    // It's better to use CocoKeyboard.delay() over the regular Arduino delay()
    // if doing keyboard stuff because it keeps talking to the computer to make
    // sure the computer knows the keyboard is alive and connected
    CocoKeyboard.delay(10);
  
    }
}
