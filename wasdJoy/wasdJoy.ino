/*****************************************************************************
HID WASD Joystick
by: Ryan Young
https://github.com/ryanayoung/wasdJoy
Date: 9/21/2018
Based on HID Joystick Mouse Example by Jim Lindblom
license: MIT License - Feel free to use this code for any purpose.
   No restrictions. Just keep this license if you go on to use this
   code in your future endeavors! Reuse and share.


*****************************************************************************/

//INCLUDES
#if (ARDUINO > 10605)
  #include <Keyboard.h>
  #include <Mouse.h>
#endif
#include "keyboard_keys.h"

/************KEY DEFINITION************************************************
 * Change these to select what actions happen. 
 ************************************************************************/
#define upKey 'w'
#define downKey 's'
#define leftKey 'a'
#define rightKey 'd'
#define pressKey ' ' //space is ' '
/********************************************************************/


//Pin declaration
int horizontalPin    = A1;
int verticalPin     = A0;
int selectPin       = A2;

//Variable declaration
int horizontalINIT, verticalINIT;
int horizontalVAL, verticalVAL;
int selectVAL;
int lastSelectState;
bool wPressed, aPressed, sPressed, dPressed = false;
int upperThreshold = 711;//on an analogRead scale of 0 - 1023 with a center of roughly 511
int lowerThreshold = 311;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

//setup
void setup()
{
    Serial.begin(9600);
    pinMode(horizontalPin, INPUT);  // Set joystick horizontal analog pin as input
    pinMode(verticalPin, INPUT);  // Set joystick vertical analog pin as input
    pinMode(selectPin, INPUT);  // set button select pin as input
    digitalWrite(selectPin, HIGH);  // Pull button select pin high
    delay(1000);  // short delay to let outputs settle
    verticalINIT = analogRead(verticalPin);  // get the initial values
    horizontalINIT = analogRead(horizontalPin);  // Joystick should be in neutral position when reading these
    Serial.print("joystick initial /n");
    Serial.print(verticalINIT + " " + horizontalINIT);
    Keyboard.begin();
}


//main loop
void loop()
{
    horizontalVAL   = analogRead(horizontalPin);
    verticalVAL     = analogRead(verticalPin);
    int reading = digitalRead(selectPin);
//keypress joystick-click
  if (reading != lastSelectState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != selectVAL) {
      selectVAL = reading;
        if(selectVAL == HIGH){
          Keyboard.release(pressKey);
        }
        else
        {                                                                                                                                                                                                                                                                    
          Keyboard.press(pressKey);
        }
      }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastSelectState = reading;

//keypress left-'a'
    if((horizontalVAL >= upperThreshold) && !aPressed)
    {
        Keyboard.press(leftKey);
        aPressed = true;
    }
    else
    {
        Keyboard.release(leftKey);
        aPressed = false;
    }

//keypress right-'d'
    if((horizontalVAL <= lowerThreshold) && !dPressed)
    {
        Keyboard.press(rightKey);
        dPressed = true;
    }
    else
    {
        Keyboard.release(rightKey);
        dPressed = false;
    }

//keypress up-'w'
    if((verticalVAL >= upperThreshold) && !wPressed)
    {
        Keyboard.press(upKey);
        wPressed = true;
    }
    else
    {
        Keyboard.release(upKey);
        wPressed = false;
    }
//keypress down-'s'
    if((verticalVAL <= lowerThreshold) && !sPressed)
    {
        Keyboard.press(downKey);
        sPressed = true;
    }
    else
    {
        Keyboard.release(downKey);
        sPressed = false;
    }

    
    Serial.print("horizontalVAL = " + horizontalVAL);
    Serial.print("verticalVAL = " + verticalVAL);


}
