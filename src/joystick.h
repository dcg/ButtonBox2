#include "Arduino.h"
#include "Mouse.h"
#define JOYSTICK_A PA0
#define JOYSTICK_B PA1
#define JOYSTICK_BTN1 PB12
#define JOYSTICK_BTN2 PB13
int range = 20;            // output range of X or Y movement
int rangeFast = 40;            // output range of X or Y movement

int responseDelay = 5;     // response delay of the mouse, in ms
int threshold = 2; // resting threshold
int center = range / 2;
int centerFast = rangeFast / 2;

bool mouseIsActive = false; // whether or not to control the mouse




// https://stm32f4-discovery.net/2017/04/tutorial-jump-system-memory-software-stm32/

   /* detachInterrupt(PB1);
    detachInterrupt(PB0);
    detachInterrupt(PA9);
    detachInterrupt(PA10);
    detachInterrupt(PA15);
    detachInterrupt(PB5);
*/




int readAxis(int thisAxis)
{
    int smoothed = 0;
     for(int i = 0 ;i <5; i++){
     smoothed = smoothed + analogRead(thisAxis);
    }
    smoothed = smoothed / 5;

    // read the analog input:
    //int reading = analogRead(thisAxis);
    //reading = analogRead(thisAxis);
    int reading = smoothed;
   // Serial.println(reading);
    /*if(reading > 527 || reading < 497) {
        return 0;
    }*/
    //Serial.println(reading);
    // map the reading from the analog input range to the output range:
    //reading = map(reading, 497, 527, 0, range);
    int distance = 0;
    if(MOUSE_FAST){
       reading = map(reading, 494, 527, 0, rangeFast);
       distance = reading - centerFast;

    } else {
        reading = map(reading, 494, 527, 0, range);
        distance = reading - center;
    }

    // if the output reading is outside from the rest position threshold, use it:
   // int distance = reading - center;

    if (abs(distance) < threshold)
    {
        distance = 0;
    }

    // return the distance for this axis:
    return distance;
}

void joystickSetup(){
    pinMode(JOYSTICK_A, INPUT);

    pinMode(JOYSTICK_B, INPUT_PULLDOWN);
    pinMode(JOYSTICK_BTN1, INPUT_PULLUP); // the switch pin
    pinMode(JOYSTICK_BTN2, INPUT_PULLUP); // the switch pin
 Mouse.begin();


}

int loopDelay = 0;
unsigned long last_read = 0;
unsigned long time_now = 0;
int period = 1;
bool mouseClicked = false;
void joystickLoop(){
   /* time_now = millis();
    if(!(time_now > last_read + period)){
        return;
    }
    last_read = time_now;
*/
   
    if(MOUSE) {
    // read and scale the two axes:
    int xReading = readAxis(JOYSTICK_A);
    int yReading = readAxis(JOYSTICK_B);
    bool btnA = digitalRead(JOYSTICK_BTN1);
    bool btnB = digitalRead(JOYSTICK_BTN2);

    if(btnB == LOW) {
        Mouse.press(MOUSE_LEFT); // JOYSTICK
        mouseClicked=true;
    }
    if(btnB == HIGH) {
        Mouse.release();
        mouseClicked=false;
    }
    if(btnA == LOW) {
        Mouse.click(MOUSE_RIGHT); // PUSH BUTTON
    }
   Mouse.move(xReading, yReading, 0);
    }
    
}