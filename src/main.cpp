#include "Arduino.h"
#include "./mybootloader.h"

bool MOUSE = false;
bool MOUSE_FAST =false;
#include "Key.h"

//#include <SemihostingStream.h>
#include "./newEncoder.h"


#include "./button.h"
#include "./joystick.h"

//SemihostingStream sh;
// extern "C" void initialise_monitor_handles(void);

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13
// build_flags =
// -D PIO_FRAMEWORK_ARDUINO_ENABLE_CDC
//    -D USBCON



//int16_t inputDelta = 0; // Counts up or down depending which way the encoder is turned
//bool printFlag = false; // Flag to indicate that the value of inputDelta should be printed
void initVariant(void) {
  enter_bootloader_mode_if_requested();

 // stm32_clock_init();
}

void setup()
{

  delay(1000);

   
    joystickSetup();
   // setupEncoder();
   // setupEncoder2();
   // setupEncoder3();
   setupNewEncoder();
    setupButton();
    
}
int count = 0;
bool led = LOW;
void loop()
{


    joystickLoop();
   //loopEncoder();
   // loopEncoder2();
   // loopEncoder3();
   loopNewEncoder();
    loopButton();
}