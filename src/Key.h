#include <Keyboard.h>
#include <Mouse.h>
#define KEY_STATE_LEFT 0
#define KEY_STATE_NEUTRAL 1
#define KEY_STATE_RIGHT 2
#define KEY_NOOP 9999
#define KEY0 0 // BTN L1
#define KEY1 1 // BTN L2
#define KEY2 2 // BTN L3
#define KEY3 3 // BTN L4
#define KEY4 4 // SW 3U
#define KEY5 5 // SW 2 U
#define KEY6 6 // SW 2 U
#define KEY7 7 // BTN U1
#define KEY8 8 // BTN U2
#define KEY9 9 // BTN U3
#define KEY10 10 // BTN U4
#define KEY11 11 // SW 3L
#define KEY12 12 // SW 1L
#define KEY13 13 // SW 1U
#define KEY14 14 //ENC1_L
#define KEY15 15 //ENC1_R
#define KEY16 16 //ENC1_BTN

#define KEY17 17 //ENC1_BTN
#define KEY18 18 //ENC1_BTN
#define KEY19 19 //ENC1_BTN

#define KEY20 20 //ENC1_BTN
#define KEY21 21 //ENC1_BTN
#define KEY22 22 //ENC1_BTN
int KeyState = 0;
void left(int k);
void neutral(int k);
void right(int k);

void setKeyState(int i)
{
    KeyState = i;
}
void writeKey(int k)
{
    if (KeyState == KEY_STATE_LEFT)
    {
        left(k);
    }
      if (KeyState == KEY_STATE_NEUTRAL)
    {
        neutral(k);
    }
      if (KeyState == KEY_STATE_RIGHT)
    {
        right(k);
    }
}


  

void dfu_run_bootloader()
{

}


void left(int k)
{
    
    switch (k) {
     case KEY0: Keyboard.write('a'); break; // L1
     case KEY1: Keyboard.write('b'); break; // L2
     case KEY2: Keyboard.write('c'); break; // L3
     case KEY3: Keyboard.write('d'); break; // L4
     case KEY4: Keyboard.write('e'); break; //SW3 L
     case KEY5: Keyboard.write('f'); break; //SW2 U
     case KEY6: Keyboard.write('g'); break; // SW2 L
     case KEY7: Keyboard.write('h'); break; // BTN U1
     case KEY8: Keyboard.write('i'); break; // BTN U2
     case KEY9: Keyboard.write('j'); break;// BTN U3
     case KEY10: Keyboard.write('k'); break;// BTN U4
     case KEY11: Keyboard.write('l'); break; // SW 3 L 
     case KEY12: Keyboard.write('m'); break;// SW 1 L
     case KEY13: Keyboard.write('n'); break; // SW 1 U
     case KEY14: Keyboard.write('o'); break; // ENC1_L
     case KEY15: Keyboard.write('p'); break; // ENC1_R
     case KEY16: Keyboard.write('q'); break; // ENC1_BTN
     case KEY17: Keyboard.write('r'); break; //ENC2_R
     case KEY18: Keyboard.write('s'); break; //ENC2_L
     case KEY19: Keyboard.write('t'); break; //ENC2_BTN
     case KEY20: Keyboard.write('u'); break; //ENC3_R
     case KEY21: Keyboard.write('v'); break;  //ENC3_L
     case KEY22: Keyboard.write('w'); break;  //ENC3_BTN

    }
}

void right(int k)
{
    
    switch (k) {
     case KEY0: Keyboard.press(KEY_F1); Keyboard.releaseAll();  break; // L1
     case KEY1: Keyboard.press(KEY_F2); Keyboard.releaseAll();  break; // L2
     case KEY2: Keyboard.press(KEY_F3); Keyboard.releaseAll();  break; // L3
     case KEY3: Keyboard.press(KEY_F4); Keyboard.releaseAll();  break; // L4
     case KEY4: MOUSE=!MOUSE;  break; //SW3 L
     case KEY5: MOUSE_FAST=!MOUSE_FAST; break; //SW2 U
     case KEY6: Keyboard.releaseAll(); break; // SW2 L
     case KEY7: Keyboard.press(KEY_F6); Keyboard.releaseAll();  break; // BTN U1
     case KEY8: Keyboard.press(KEY_F7); Keyboard.releaseAll();  break; // BTN U2
     case KEY9: Keyboard.press(KEY_F8); Keyboard.releaseAll();  break;// BTN U3
     case KEY10: Keyboard.press(KEY_F9); Keyboard.releaseAll();  break;// BTN U4
     case KEY11: Keyboard.press(KEY_F10); Keyboard.releaseAll();  break; // SW 3 L 
     case KEY12: 
        Keyboard.press(KEY_LEFT_CTRL);  // press and hold Shift
        Keyboard.press(' ');          // press and hold space
        Keyboard.releaseAll(); 
         break;// SW 1 L
     case KEY13: Keyboard.press(KEY_ESC); Keyboard.releaseAll(); 
break; // SW 1 U
     case KEY14: Keyboard.press(KEY_LEFT_ARROW); Keyboard.releaseAll(); break; // ENC1_L
     case KEY15: Keyboard.press(KEY_RIGHT_ARROW); Keyboard.releaseAll(); break; // ENC1_R
     case KEY16: Keyboard.press(KEY_HOME); Keyboard.releaseAll(); break; // ENC1_BTN
     case KEY17: Keyboard.press(KEY_UP_ARROW); Keyboard.releaseAll(); break; //ENC2_R
     case KEY18: Keyboard.press(KEY_DOWN_ARROW); Keyboard.releaseAll(); break; //ENC2_L
     case KEY19: Keyboard.press(KEY_DELETE); Keyboard.releaseAll(); break; //ENC2_BTN
     case KEY20: Mouse.move(0,0,1); Keyboard.releaseAll(); break; //ENC3_R
     case KEY21: Mouse.move(0,0,-1); Keyboard.releaseAll(); break; //ENC3_L
     case KEY22: Keyboard.press(KEY_INSERT); Keyboard.releaseAll(); break;  //ENC3_BTN

    }
}
void neutral(int k)
{
    
    switch (k) {
     case KEY0: Keyboard.write('x'); break; // L1
     case KEY1: Keyboard.write('y'); break; // L2
     case KEY2: Keyboard.write('z'); break; // L3
     case KEY3: Keyboard.write('1'); break; // L4
     case KEY4: Keyboard.write('2'); break; //SW3 L
     case KEY5: Keyboard.write('3'); break; //SW2 U
     case KEY6: Keyboard.write('4'); break; // SW2 L
     case KEY7: Keyboard.write('5'); break; // BTN U1
     case KEY8: Keyboard.write('6'); break; // BTN U2
     case KEY9: Keyboard.write('7'); break;// BTN U3
     case KEY10: Keyboard.write('8'); break;// BTN U4
     case KEY11: Keyboard.write('9'); break; // SW 3 L 
     case KEY12: Keyboard.write('0'); break;// SW 1 L
     case KEY13: Keyboard.write('<'); break; // SW 1 U
     case KEY14: Keyboard.write('>'); break; // ENC1_L
     case KEY15: Keyboard.write(','); break; // ENC1_R
     case KEY16: Keyboard.write('.'); break; // ENC1_BTN
     case KEY17: Keyboard.write('-'); break; //ENC2_R
     case KEY18: Keyboard.write('_'); break; //ENC2_L
     case KEY19: Keyboard.write('#'); break; //ENC2_BTN
     case KEY20: Keyboard.write('+'); break; //ENC3_R
     case KEY21: Keyboard.write('*'); break;  //ENC3_L
     case KEY22: Keyboard.write('?'); break;  //ENC3_BTN

    }
}


