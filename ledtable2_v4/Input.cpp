#include "Input.h"

//USB and Xbox gamepad library
#include <XBOXUSB.h>
#include <usbhub.h>
#include <spi4teensy3.h>

USB Usb;
USBHub USBHub(&Usb);
XBOXUSB xboxController[4] = {
  XBOXUSB(&Usb),
  XBOXUSB(&Usb),
  XBOXUSB(&Usb),
  XBOXUSB(&Usb)
};

boolean usbInitialized = false;

void initializeUsb()
{
  #ifndef DISABLE_USB

  Serial.println("Initialize USB");
  //Init USB
  if (Usb.Init() == -1) {
    Serial.println(F("\r\nOSC did not start"));
    while (1); //halt
  } else { 
    Serial.println(F("\r\nUSB init successfull"));
  }
  usbInitialized = true;
  
  #endif
}

void UsbTask(){
  Serial.print("running UsbTask");
  Serial.println((int)&Usb);
  Usb.Task();
}

Input::Input(int controllerIndex) : controllerIndex(controllerIndex) 
{
}

void Input::init()
{
  if(!usbInitialized) 
  {
    initializeUsb(); 
  }
}


uint8_t Input::read(){
  Serial.print("read controller ");
  Serial.println((int)xboxController);
  if (xboxController[controllerIndex].Xbox360Connected) {
    if (xboxController[controllerIndex].getButtonPress(B) || xboxController[controllerIndex].getButtonPress(RIGHT)) 
    {
      curControl = BTN_RIGHT;
    }
    else if (xboxController[controllerIndex].getButtonPress(X) || xboxController[controllerIndex].getButtonPress(LEFT))
    {
      curControl = BTN_LEFT;
    }
    else if (xboxController[controllerIndex].getButtonPress(Y) || xboxController[controllerIndex].getButtonPress(UP))
    {
      curControl = BTN_UP;
    }
    else if (xboxController[controllerIndex].getButtonPress(A) || xboxController[controllerIndex].getButtonPress(DOWN))
    {
      curControl = BTN_DOWN;
    }
    else if (xboxController[controllerIndex].getButtonPress(START) || xboxController[controllerIndex].getButtonPress(XBOX))
    {
      curControl = BTN_START;
    }
      
    if (curControl == prevControl)
      curControl = BTN_NONE;
    else
      prevControl = curControl;
  }
  return curControl;
}


