/*---------------------------------------------------------------------------------------------

  Coco MIDI Library 2012 by Michael Egger and update 2016 by Iyok
  install the Coconut from https://cocomake7.github.io/

  The following code is for use with the TurbdityGnUSB, a photometer/turbidity meter.
  see more: https://github.com/GenericLab/TurbiGnUSB
  
 */
 
#include <CocoMidi.h>
MIDIMessage midimsg;

const int SensorLEDPin = 1;    //the LED inside the TurbiGnUSB is on when the pin is LOW
const int LEDonBoardPin = 0;
const int sensorPin = A2;

int averaging = 1; //used to be 4
int measuringON = 1;

int averagingDelay = 8; //used to be 40
int sample_delay = 8; //used to be 1000
int MIDI_delay = 4;

int LEDstate = 1;
long sensorValue = 0;         // variable to store the value coming from the sensor
int sensorValueTMP = 0;
uint8_t sensorValueHB = 0;         // HighByte for seperating the midi-message
uint8_t sensorValueLB = 0;         // LowByte for seperating the midi-message

void usb_poll()
{
    usbPoll();
}

void setup() {
    CocoMidi.init();
    
    pinMode (SensorLEDPin, OUTPUT);
    pinMode (LEDonBoardPin, OUTPUT);
    
    digitalWrite(SensorLEDPin,1);              // Blink a bit to show that it's ready
    digitalWrite(LEDonBoardPin,1);
    CocoMidi.delay(100);
    digitalWrite(SensorLEDPin,0);
    digitalWrite(LEDonBoardPin,0);
    CocoMidi.delay(100);
    digitalWrite(SensorLEDPin,1);
    digitalWrite(LEDonBoardPin,1);
    CocoMidi.delay(100);
    digitalWrite(SensorLEDPin,0);
    digitalWrite(LEDonBoardPin,0);
    CocoMidi.delay(100);
    digitalWrite(SensorLEDPin,1);
    CocoMidi.delay(100);
}


void loop() {
  
  sensorValue = 0;
  sensorValueTMP = analogRead(sensorPin);
  
  if (measuringON) {
    for(int c = 0 ; c < averaging; c +=1) { 
      digitalWrite(SensorLEDPin,!LEDstate);
      digitalWrite(LEDonBoardPin,LEDstate);
      CocoMidi.delay(averagingDelay);
      sensorValueTMP = analogRead(sensorPin);   // analogRead returns 0-1023
      sensorValue = sensorValue + sensorValueTMP;
      digitalWrite(SensorLEDPin,1);
      digitalWrite(LEDonBoardPin,0);
      CocoMidi.delay(averagingDelay);
    }
  
  digitalWrite(SensorLEDPin,1);
  sensorValue = sensorValue / (averaging);
  
  sensorValueHB = sensorValue >> 3;
  sensorValueLB = sensorValue & 0x7;

        CocoMidi.send(MIDI_CONTROLCHANGE,1,sensorValueHB);     // put new control change message into MIDI sending queue
        CocoMidi.delay(MIDI_delay);
        
        CocoMidi.send(MIDI_CONTROLCHANGE,2,sensorValueLB);     // put new control change message into MIDI sending queue
        CocoMidi.delay(MIDI_delay);              // give some time for sending, otherwhise the MIDI queue could fill up
  
  }      

  if (CocoMidi.read(&midimsg)) {
      
        switch(midimsg.command) {
                      
            case MIDI_CONTROLCHANGE: 
               switch(midimsg.key) {
                 case 0:
                   LEDstate = midimsg.value;
                   break;
                 
                 case 1:
                   averaging = midimsg.value;
                   break;  
                 
                 case 2: 
                   averagingDelay = (midimsg.value); 
                   break;                       
                 
                 case 3:
                   sample_delay = (midimsg.value * 50);
                   break;
                   
                 case 10:
                   measuringON = midimsg.value; 
                   break;
 
               }
        }
    }
   
   if (sample_delay > (averaging * 2 * averagingDelay)) {
     CocoMidi.delay(sample_delay - (averaging * 2 * averagingDelay));
   }
   
   CocoMidi.update();
   CocoMidi.delay(1);

}

