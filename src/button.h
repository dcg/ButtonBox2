#include "Arduino.h"

#define buttonRowA PA2
#define buttonRowB PA3
#define switchA PA4
#define switchB PA5

int a2 = 0;
int a3 = 0;
bool d4 = 0;
bool d5 = 0;
int stateA2 = 0;
int stateA3 = 0;
int keyA = KEY_NOOP;
int keyB = KEY_NOOP;

void statemachineA2(int val)
{
    switch (stateA2)
    {
    case 0:
        if (val < 8)
        {
            stateA2 = 1;
            keyA = KEY0;
            writeKey(keyA);
        }
        else if (val > 8 && val < 12)
        {
            stateA2 = 1;
            keyA = KEY1;
            writeKey(keyA);
        }
        else if (val > 25 && val < 35)
        {
            stateA2 = 1;
            keyA = KEY2;
            writeKey(keyA);
        }
        else if (val > 110 && val < 125)
        {
            stateA2 = 1;
            keyA = KEY3;
            writeKey(keyA);
        }
        else if (val > 215 && val < 225)
        {
            stateA2 = 1;
            keyA = KEY4;
            writeKey(keyA);
        }
        else if (val > 228 && val < 438)
        {
            stateA2 = 1;
            keyA = KEY5;
            writeKey(keyA);
        }
        else if (val > 600 && val < 690)
        {
            stateA2 = 1;
            keyA = KEY6;
            writeKey(keyA);
        }

        break;
    case 1:
    {
        if (val > 1020)
        {
            stateA2 = 0;
           // Keyboard.write(keyA);
            keyA = KEY_NOOP;
        }
        break;
    }
    }
}

void statemachineA3(int val)
{
    switch (stateA3)
    {
    case 0:
        if (val < 8)
        {
            stateA3 = 1;
            keyB = KEY7;
            writeKey(keyB);
        }
        else if (val > 8 && val < 12)
        {
            stateA3 = 1;
            keyB = KEY8;
            writeKey(keyB);
        }
        else if (val > 25 && val < 35)
        {
            stateA3 = 1;
            keyB = KEY9;
            writeKey(keyB);
        }
        else if (val > 110 && val < 125)
        {
            stateA3 = 1;
            keyB = KEY10;
            writeKey(keyB);
        }
        else if (val > 215 && val < 225)
        {
            stateA3 = 1;
            keyB = KEY11;
            writeKey(keyB);
        }
        else if (val > 228 && val < 438)
        {
            stateA3 = 1;
            keyB = KEY12;
            writeKey(keyB);
        }
        else if (val > 600 && val < 690)
        {
            stateA3 = 1;
            keyB = KEY13;
            writeKey(keyB);
        }
        break;
    case 1:
    {
        if (val > 1020)
        {
            stateA3 = 0;
          //  Keyboard.write(keyB);
            keyB = KEY_NOOP;
        }
        break;
    }
    }
}
void setupButton()
{
    pinMode(buttonRowA, INPUT_PULLDOWN);
    pinMode(buttonRowB, INPUT_PULLDOWN);

    pinMode(switchA, INPUT_PULLUP);
    pinMode(switchB, INPUT_PULLUP);
}
void loopButton()
{

    a2 = analogRead(buttonRowA);
    a3 = analogRead(buttonRowB);
    d4 = digitalRead(switchA);
    d5 = digitalRead(switchB);
    //KEY6 KEY12
    if (a3 > 228 && a3 < 438 && a2 > 600 && a2 < 690) {
        bootloader_jump();
        return;
    }
 
    if (d4 == LOW)
    {
        setKeyState(KEY_STATE_LEFT);
    }
    else if (d5 == LOW)
    {
        setKeyState(KEY_STATE_RIGHT);
    }
    else
    {
        setKeyState(KEY_STATE_NEUTRAL);
    }
    statemachineA2(a2);
    statemachineA3(a3);
}
