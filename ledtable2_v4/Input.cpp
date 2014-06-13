#include "Input.h"


//USB and Xbox gamepad library


//USB Usb;
//USBHub USBHub(&Usb);
//XBOXUSB Xbox(&Usb);


void UsbTask(){
//  Usb.Task();
}
/*
void Input::init()
{
  #ifndef DISABLE_USB
    Serial.println("Initialize USB");
  //Init USB
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  } else { 
    Serial.print(F("\r\nUSB init successfull"));
  }
  
  #endif
}
*/

uint8_t curControl = BTN_NONE;
uint8_t prevControl = BTN_NONE;
uint8_t Input::read(){
  return curControl = BTN_NONE;
  /*
//  Serial.println("Check Connected");
  if (Xbox.Xbox360Connected) {
//    Serial.println("Check Buttons");
    if (Xbox.getButtonPress(B) || Xbox.getButtonPress(RIGHT)) 
    {
      curControl = BTN_RIGHT;
    }
    else if (Xbox.getButtonPress(X) || Xbox.getButtonPress(LEFT))
    {
      curControl = BTN_LEFT;
    }
    else if (Xbox.getButtonPress(Y) || Xbox.getButtonPress(UP))
    {
      curControl = BTN_UP;
    }
    else if (Xbox.getButtonPress(A) || Xbox.getButtonPress(DOWN))
    {
      curControl = BTN_DOWN;
    }
    else if (Xbox.getButtonPress(START) || Xbox.getButtonPress(XBOX))
    {
      curControl = BTN_START;
    }
//    Serial.println("Buttons checked");
      
    if (curControl == prevControl)
      curControl = BTN_NONE;
    else
      prevControl = curControl;
  }
  return curControl;
  */
}


