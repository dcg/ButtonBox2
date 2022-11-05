#include "Arduino.h"
#include "Keyboard.h"
#define encoderPinA PB1 //PB14
#define encoderPinB PB0 // PB15
#define encoderPinBTN PA8

int16_t inputDelta = 0; // Counts up or down depending which way the encoder is turned
bool printFlag = false; // Flag to indicate that the value of inputDelta should be printed
void ec1_encoderInterrupt();
volatile char nextKey = 0;

void setupEncoder()
{
    pinMode(encoderPinA, INPUT_PULLUP);
    pinMode(encoderPinB, INPUT_PULLUP);
    pinMode(encoderPinBTN, INPUT_PULLUP);

    attachInterrupt(encoderPinA, ec1_encoderInterrupt, CHANGE);
    attachInterrupt(encoderPinB, ec1_encoderInterrupt, CHANGE);
}

int btnState = 0;
void loopEncoder(){
    if(printFlag){
        while(abs(inputDelta) > 0 ){
            if(inputDelta > 0) {
                writeKey(KEY14);
                inputDelta--;
            }
            if(inputDelta < 0) {
                writeKey(KEY15);
                inputDelta++;
            }
        }

        }
    int btn = digitalRead(encoderPinBTN);
    if(btn == LOW && btnState == 0){
       writeKey(KEY16);
       btnState =1;
    } else if(btn == HIGH) {
        btnState = 0;
    }      

}

volatile int state = 0;
volatile unsigned long lastRun = 0;
unsigned long PER =  200;
int stateMachine(bool CLK, bool DT)
{
    unsigned long now = millis();
    if(lastRun + PER < now){
        state = 0;
    }
    lastRun = now;
    switch (state)
    {
    case 0: // Idle state, encoder not turning
        if (!CLK)
        { // Turn clockwise and CLK goes low first
            state = 1;
        }
        else if (!DT)
        { // Turn anticlockwise and DT goes low first
            state = 4;
        }
        break;
    // Clockwise rotation
    case 1:
        if (!DT)
        { // Continue clockwise and DT will go low after CLK
            state = 2;
        }
        break;
    case 2:
        if (CLK)
        { // Turn further and CLK will go high first
            state = 3;
        }
        break;
    case 3:
        if (CLK && DT)
        { // Both CLK and DT now high as the encoder completes one step clockwise
            state = 0;
            ++inputDelta;
            //nextKey = 'A';
            printFlag = true;
        }
        break;
    // Anticlockwise rotation
    case 4: // As for clockwise but with CLK and DT reversed
        if (!CLK)
        {
            state = 5;
        }
        break;
    case 5:
        if (DT)
        {
            state = 6;
        }
        break;
    case 6:
        if (CLK && DT)
        {
            state = 0;
            --inputDelta;
            //nextKey='B';
            printFlag = true;
        }
        break;
    }
    return state;
}

void ec1_encoderInterrupt()
{
    bool CLK = digitalRead(encoderPinA);
    CLK = digitalRead(encoderPinA);
    bool DT = digitalRead(encoderPinB);
    DT = digitalRead(encoderPinB);
    int state = stateMachine(DT, CLK);
}