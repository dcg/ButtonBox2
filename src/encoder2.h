/*#include "Arduino.h"
#include "Keyboard.h"
#define ec2_encoderPinA PA9
#define ec2_encoderPinB PA10
#define ec2_encoderPinBTN PB4

int16_t ec2_inputDelta = 0; // Counts up or down depending which way the encoder is turned
bool ec2_printFlag = false; // Flag to indicate that the value of inputDelta should be printed
void ec2_encoderInterrupt();
volatile char ec2_nextKey = 0;

void setupEncoder2()
{
    pinMode(ec2_encoderPinA, INPUT_PULLUP);
    pinMode(ec2_encoderPinB, INPUT_PULLUP);
    //pinMode(ec2_encoderPinBTN, INPUT_PULLUP);

   // attachInterrupt(ec2_encoderPinA, ec2_encoderInterrupt, CHANGE);
   // attachInterrupt(ec2_encoderPinB, ec2_encoderInterrupt, CHANGE);
}
int ec2_btnState = 0;

void loopEncoder2(){
    ec2_encoderInterrupt();
     if(ec2_printFlag){
        while(abs(ec2_inputDelta) > 0 ){
            if(ec2_inputDelta > 0) {
                writeKey(KEY17);
                ec2_inputDelta--;
            }
            if(ec2_inputDelta < 0) {
                writeKey(KEY18);
                ec2_inputDelta++;
            }
        }

        }
    int btn = digitalRead(ec2_encoderPinBTN);
    if(btn == LOW && ec2_btnState == 0){
       writeKey(KEY19);
       ec2_btnState =1;
    } else if(btn == HIGH) {
        ec2_btnState = 0;
    }       

}

volatile int ec2_state = 0;
int ec2_stateMachine(bool CLK, bool DT)
{
    switch (ec2_state)
    {
    case 0: // Idle state, encoder not turning
        if (!CLK)
        { // Turn clockwise and CLK goes low first
            ec2_state = 1;
        }
        else if (!DT)
        { // Turn anticlockwise and DT goes low first
            ec2_state = 4;
        }
        break;
    // Clockwise rotation
    case 1:
        if (!DT)
        { // Continue clockwise and DT will go low after CLK
            ec2_state = 2;
        }
        break;
    case 2:
        if (CLK)
        { // Turn further and CLK will go high first
            ec2_state = 3;
        }
        break;
    case 3:
        if (CLK && DT)
        { // Both CLK and DT now high as the encoder completes one step clockwise
            ec2_state = 0;
            ++ec2_inputDelta;
            ec2_nextKey = 'D';
            ec2_printFlag = true;
        }
        break;
    // Anticlockwise rotation
    case 4: // As for clockwise but with CLK and DT reversed
        if (!CLK)
        {
            ec2_state = 5;
        }
        break;
    case 5:
        if (DT)
        {
            ec2_state = 6;
        }
        break;
    case 6:
        if (CLK && DT)
        {
            ec2_state = 0;
            --ec2_inputDelta;
            ec2_nextKey='E';
            ec2_printFlag = true;
        }
        break;
    }
    return ec2_state;
}

void ec2_encoderInterrupt()
{
    bool CLK = digitalRead(ec2_encoderPinA);
   // CLK = digitalRead(ec2_encoderPinA);
    bool DT = digitalRead(ec2_encoderPinB);
   // DT = digitalRead(ec2_encoderPinB);
    int ec2_state = ec2_stateMachine(DT, CLK);
}