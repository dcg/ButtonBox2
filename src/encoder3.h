/*#include "Arduino.h"
#include "Keyboard.h"
#define ec3_encoderPinA PA15
#define ec3_encoderPinB PB5
#define ec3_encoderPinBTN PB3

int16_t ec3_inputDelta = 0; // Counts up or down depending which way the encoder is turned
bool ec3_printFlag = false; // Flag to indicate that the value of inputDelta should be printed
void ec3_encoderInterrupt();
volatile char ec3_nextKey = 0;

void setupEncoder3()
{
    pinMode(ec3_encoderPinA, INPUT_PULLUP);
    pinMode(ec3_encoderPinB, INPUT_PULLUP);
    pinMode(ec3_encoderPinBTN, INPUT_PULLUP);

//    attachInterrupt(ec3_encoderPinA, ec3_encoderInterrupt, CHANGE);
//    attachInterrupt(ec3_encoderPinB, ec3_encoderInterrupt, CHANGE);
}
int ec3_btnState = 0;

void loopEncoder3(){
  ec3_encoderInterrupt();
  if(ec3_printFlag){
        while(abs(ec3_inputDelta) > 0 ){
            if(ec3_inputDelta > 0) {
                writeKey(KEY20);
                ec3_inputDelta--;
            }
            if(ec3_inputDelta < 0) {
                writeKey(KEY21);
                ec3_inputDelta++;
            }
        }

        }
    int btn = digitalRead(ec3_encoderPinBTN);
    if(btn == LOW && ec3_btnState == 0){
       writeKey(KEY22);
       ec3_btnState =1;
    } else if(btn == HIGH) {
        ec3_btnState = 0;
    }       
     

}

volatile int ec3_state = 0;
int ec3_stateMachine(bool CLK, bool DT)
{
    switch (ec3_state)
    {
    case 0: // Idle state, encoder not turning
        if (!CLK)
        { // Turn clockwise and CLK goes low first
            ec3_state = 1;
        }
        else if (!DT)
        { // Turn anticlockwise and DT goes low first
            ec3_state = 4;
        }
        break;
    // Clockwise rotation
    case 1:
        if (!DT)
        { // Continue clockwise and DT will go low after CLK
            ec3_state = 2;
        }
        break;
    case 2:
        if (CLK)
        { // Turn further and CLK will go high first
            ec3_state = 3;
        }
        break;
    case 3:
        if (CLK && DT)
        { // Both CLK and DT now high as the encoder completes one step clockwise
            ec3_state = 0;
            ++ec3_inputDelta;
            ec3_nextKey = 'G';
            ec3_printFlag = true;
        }
        break;
    // Anticlockwise rotation
    case 4: // As for clockwise but with CLK and DT reversed
        if (!CLK)
        {
            ec3_state = 5;
        }
        break;
    case 5:
        if (DT)
        {
            ec3_state = 6;
        }
        break;
    case 6:
        if (CLK && DT)
        {
            ec3_state = 0;
            --ec3_inputDelta;
            ec3_nextKey='H';
            ec3_printFlag = true;
        }
        break;
    }
    return ec3_state;
}

void ec3_encoderInterrupt()
{
    bool CLK = digitalRead(ec3_encoderPinA);
  //  CLK = digitalRead(ec3_encoderPinA);
    bool DT = digitalRead(ec3_encoderPinB);
  //  DT = digitalRead(ec3_encoderPinB);
    int ec3_state = ec3_stateMachine(DT, CLK);
}