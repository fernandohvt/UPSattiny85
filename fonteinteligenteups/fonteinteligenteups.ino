#include <DigisparkRGB.h>
#include <TinyWireM.h>

//Primary Colors
byte RED = 0;
byte GREEN = 1;
byte BLUE = 2;


// The setup routine runs once when you press reset:
void setup()  {
 
  pinMode(3, INPUT);// Analog read from battery
  pinMode(0,OUTPUT); // Digital write for Red in RGB led.
  pinMode(1,OUTPUT); // Digital write for Green in RGB led.
  pinMode(2,OUTPUT); // Digital write for Blu in RGB led.
  pinMode(4,INPUT); // Digital Read from energy source.
  pinMode(5,OUTPUT); // Digital actuator for switch between battery and energy source
  DigisparkRGBBegin();
 
}
//Method to set a preset color in RGB led.
// 0 = RED, 1 = GREEN, 2 = BULE
void setColor( byte color){
  if( color == 0) {
    DigisparkRGB(RED, 255);
    DigisparkRGB(GREEN, 0);
    DigisparkRGB(BLUE, 0);
  }
  if( color == 1) {
    DigisparkRGB(RED, 0);
    DigisparkRGB(GREEN, 255);
    DigisparkRGB(BLUE, 0);
    }
  if( color == 2) {
      DigisparkRGB(RED, 0);
      DigisparkRGB(GREEN, 0);
      DigisparkRGB(BLUE, 255);  
  }
  if( color == 3) {
    DigisparkRGB(RED, 211);
    DigisparkRGB(GREEN, 84);
    DigisparkRGB(BLUE, 0);
  }
}
void loop ()
{
  int valBat = analogRead(3); // Read voltage from battery
  byte valSource = digitalRead(4); // Read sate from source
  if(valSource == 1){ // If source is on
    if( valBat >= 950 ){ // If battery is charged
      digitalWrite(5,LOW); // Set feed from energy source
      setColor(1);    // Set color green.
    }else{ // If battery is discharged
      setColor(2); //Set color blue
    }
  }else { // If energy running out
     if( valBat >= 950 ){ // Check if battery is charged
      digitalWrite(5,HIGH); // Switch feed from source to battery
      setColor(3);   // Set color orange
    }else{ // if no battery and no energy source power
      setColor(0); // Set color red
    }
  }

}
