#include "Arduino.h"
#include "Keyboard.h"
#define ec1_encoderPinA PB1 // PB14
#define ec1_encoderPinB PB0 // PB15
#define ec1_encoderPinBTN PA8
int ec1_btn_state;
int ec1_enc_state = 0;
#define ec2_encoderPinA PA9
#define ec2_encoderPinB PA10
#define ec2_encoderPinBTN PB4
int ec2_btn_state;
int ec2_enc_state = 0;

#define ec3_encoderPinA PA15
#define ec3_encoderPinB PB5
#define ec3_encoderPinBTN PB3
int ec3_btn_state;
int ec3_enc_state = 0;

void handleBTN(int pin, int key, int *btnState)
{
    int btn = digitalRead(pin);
    if (btn == LOW && *btnState == 0)
    {
        writeKey(key);
        *btnState = 1;
    }
    else if (btn == HIGH)
    {
        *btnState = 0;
    }
}


int stateMachine(int state, bool CLK, bool DT)
{
    switch (state)
    {
    case 100:
    case 200:
    case 0:
        if (!CLK && DT)
        {
            return 1;
        }
        if( CLK && !DT)
        {
            return 4;
        }
        break;
    case 1:
        if (!CLK && !DT)
        {
            return 2;
        }
        break;
    case 2:
        if (CLK && !DT)
        {
            return 3;
        }
        break;

    case 3:
        if (CLK && DT)
        {
            return 100;
        }
        break;

    case 4:
        if(!CLK & !DT) {
            return 5;
        }
        break;

    case 5:
    if(!CLK && DT) { return 6;}
        break;
    case 6:
    if(CLK && DT) {
        return 200;
    }
        break;
    }
    return state;
}

void handleRotation(int CLK_PIN, int DT_PIN, int *ec_state, int CW_KEY, int CCW_KEY) 
{
    bool CLK = digitalRead(CLK_PIN);
    bool DT = digitalRead(DT_PIN);
    int newState = stateMachine(*ec_state, CLK, DT);
    if(newState == 200) {
        writeKey(CCW_KEY);
        newState = 0;
    }
    if(newState == 100) {
        writeKey(CW_KEY);
        newState = 0;
    }
    *ec_state = newState;

}

void setupNewEncoder()
{
    pinMode(ec1_encoderPinA, INPUT_PULLUP);
    pinMode(ec1_encoderPinB, INPUT_PULLUP);
    pinMode(ec1_encoderPinBTN, INPUT_PULLUP);

    pinMode(ec2_encoderPinA, INPUT_PULLUP);
    pinMode(ec2_encoderPinB, INPUT_PULLUP);
    pinMode(ec2_encoderPinBTN, INPUT_PULLUP);

    pinMode(ec3_encoderPinA, INPUT_PULLUP);
    pinMode(ec3_encoderPinB, INPUT_PULLUP);
    pinMode(ec3_encoderPinBTN, INPUT_PULLUP);
}

void loopNewEncoder()
{
    handleBTN(ec1_encoderPinBTN, KEY16, &ec1_btn_state);
    handleBTN(ec2_encoderPinBTN, KEY19, &ec2_btn_state);
    handleBTN(ec3_encoderPinBTN, KEY22, &ec3_btn_state);

    handleRotation(ec1_encoderPinA, ec1_encoderPinB, &ec1_enc_state, KEY14, KEY15);
    handleRotation(ec2_encoderPinA, ec2_encoderPinB, &ec2_enc_state, KEY17, KEY18);
    handleRotation(ec3_encoderPinA, ec3_encoderPinB, &ec3_enc_state, KEY20, KEY21);

}