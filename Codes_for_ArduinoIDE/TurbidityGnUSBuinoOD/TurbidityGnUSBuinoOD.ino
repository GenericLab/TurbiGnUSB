#include "CocoKeyboard.h"

//cocokeyboard Turbidity Measurement


float sensorValue=0;
float refValue=0;

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

    digitalWrite(SensorLEDPin, LOW);   // turn the LED on (HIGH is the voltage level)

  
  // don't need to set anything up to use CocoKeyboard
}


void loop() {
  

  buttonState = digitalRead(buttonPin);

    if (buttonState == LOW) {

    digitalWrite(LEDPin, HIGH);   // turn the LED on (HIGH is the voltage level)

    sensorValue = analogRead(analogInPin);


  // Type out this string letter by letter on the computer (assumes US-style
  // keyboard)
  
  if (refValue==0)
  CocoKeyboard.println(sensorValue); else CocoKeyboard.println(log10(refValue/(1024-sensorValue))); 
  
  
  // It's better to use CocoKeyboard.delay() over the regular Arduino delay()
  // if doing keyboard stuff because it keeps talking to the computer to make
  // sure the computer knows the keyboard is alive and connected
  CocoKeyboard.delay(200);
  
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW)   
  {refValue = 1024-analogRead(analogInPin);

  while(buttonState==LOW) buttonState = digitalRead(buttonPin);
  }
  
  digitalWrite(LEDPin, LOW);   // turn the LED on (HIGH is the voltage level)

    }
}
