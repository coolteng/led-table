/* LedTable for Teensy3
 *
 * Written by: Klaas De Craemer, 2013
 * https://sites.google.com/site/klaasdc/led-table
 * 
 * Main file with common methods and defines, such as button reading from USB controller
 * or setting pixels on the LED area
 */

#include "config.h"

/*
 * Include libraries used in the project
 * Needs all libraries used in all .cpp files, otherwise they won't be found.
 * The explanation is that only the .ino files are scanned for libraries and the 
 * there found libraries are copied to the build directory prior to compilation.
 */
#ifdef USE_FAST_LED
#include <FastLED.h>
#endif
#ifdef USE_OCTOWS2811
#define _OCTOWS2811_H_
#include <OctoWS2811.h>
#endif
#include <XBOXUSB.h>
#include <spi4teensy3.h>
#include <usbhub.h>


#include "LEDDriver.h"
#include "Canvas.h"
#include "App.h"
#include "Input.h"


#ifdef USE_FAST_LED
FAST_LEDDriver<LEDS_CHANNEL_1+LEDS_CHANNEL_2+LEDS_CHANNEL_3+LEDS_CHANNEL_4+LEDS_CHANNEL_5+LEDS_CHANNEL_6+LEDS_CHANNEL_7+LEDS_CHANNEL_8> leds;
#endif

#ifdef USE_OCTOWS2811
OctoWS2811Driver<LEDS_CHANNEL_1+LEDS_CHANNEL_2+LEDS_CHANNEL_3+LEDS_CHANNEL_4+LEDS_CHANNEL_5+LEDS_CHANNEL_6+LEDS_CHANNEL_7+LEDS_CHANNEL_8> leds;
#endif

#define CONCURRENT_APPS 4

Canvas canvas[CONCURRENT_APPS] = {
  Canvas(13, 11, 0, 0, 52, leds),
  Canvas(13, 11, 13, 0, 52, leds),
  Canvas(13, 11, 26, 0, 52, leds),
  Canvas(13, 11, 39, 0, 52, leds)
};
Input input;

AppController* appController[CONCURRENT_APPS];

USB Usb;
//USBHub USBHub(&Usb);
XBOXUSB Xbox(&Usb);

void setup(){
  Serial.begin(115200);

  //Initialise led driver
//  Serial.println("Initialize pixels");
  leds.initPixels();
//  leds.clearPixels();
//  Serial.println("Show pixels");
//  leds.showPixels();
//  Serial.println("Pixels shown");
  
  for(int appIndex = 0; appIndex <CONCURRENT_APPS; ++appIndex) {
    appController[appIndex] = new AppController(13,11);
    appController[appIndex]->startMenu();
  }
  

  //Init random number generator
  randomSeed(millis());
  
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  delay(5000);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXBOX USB Library Started"));
//  delay(2000);

}


void loop(){
/*  static int offset = 0;
  int allPixels = NUMBER_ALL_LEDS;
  int redOffset = allPixels / 3;
  int blueOffset = allPixels / 3 * 2;
  for(int i=0; i<NUMBER_ALL_LEDS;++i) {
    if(i>= offset && i<offset+13) {
      leds.setPixel(i,GREEN);
    } else if(i>= (offset+redOffset)%allPixels && i<(offset+redOffset)%allPixels+13) {
      leds.setPixel(i,RED);
    } else if(i>= (offset+blueOffset)%allPixels && i<(offset+blueOffset)%allPixels+13) {
      leds.setPixel(i,BLUE);
    } else {
      leds.setPixel(i,OFF);
    }
  } 
  leds.showPixels();
  delay(50);
  offset = (offset+1)%(NUMBER_ALL_LEDS);
*/
/*  static unsigned long lastFPSUpdate = 0;
  static unsigned long renderedFrames = 0;
  unsigned long currentTick = millis();
  for(int appIndex = 0; appIndex < CONCURRENT_APPS; ++appIndex) {
    appController[appIndex]->process(currentTick, input, canvas[appIndex]);
  }
  leds.showPixels();
  ++renderedFrames;
  if(currentTick - lastFPSUpdate > 1000) {
//    Serial.print("Frames per second:");
//    Serial.println(renderedFrames);
    lastFPSUpdate = currentTick;
    renderedFrames = 0;
  }
*/

  Usb.Task();
  if (Xbox.Xbox360Connected) {
    if (Xbox.getButtonPress(L2) || Xbox.getButtonPress(R2)) {
      Serial.print("L2: ");
      Serial.print(Xbox.getButtonPress(L2));
      Serial.print("\tR2: ");
      Serial.println(Xbox.getButtonPress(R2));
      Xbox.setRumbleOn(Xbox.getButtonPress(L2), Xbox.getButtonPress(R2));
    } else
      Xbox.setRumbleOn(0, 0);

    if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500 || Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500 || Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500 || Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
      if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500) {
        Serial.print(F("LeftHatX: "));
        Serial.print(Xbox.getAnalogHat(LeftHatX));
        Serial.print("\t");
      }
      if (Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500) {
        Serial.print(F("LeftHatY: "));
        Serial.print(Xbox.getAnalogHat(LeftHatY));
        Serial.print("\t");
      }
      if (Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500) {
        Serial.print(F("RightHatX: "));
        Serial.print(Xbox.getAnalogHat(RightHatX));
        Serial.print("\t");
      }
      if (Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
        Serial.print(F("RightHatY: "));
        Serial.print(Xbox.getAnalogHat(RightHatY));
      }
      Serial.println();
    }

    if (Xbox.getButtonClick(UP)) {
      Xbox.setLedOn(LED1);
      Serial.println(F("Up"));
    }
    if (Xbox.getButtonClick(DOWN)) {
      Xbox.setLedOn(LED4);
      Serial.println(F("Down"));
    }
    if (Xbox.getButtonClick(LEFT)) {
      Xbox.setLedOn(LED3);
      Serial.println(F("Left"));
    }
    if (Xbox.getButtonClick(RIGHT)) {
      Xbox.setLedOn(LED2);
      Serial.println(F("Right"));
    }

    if (Xbox.getButtonClick(START)) {
      Xbox.setLedMode(ALTERNATING);
      Serial.println(F("Start"));
    }
    if (Xbox.getButtonClick(BACK)) {
      Xbox.setLedBlink(ALL);
      Serial.println(F("Back"));
    }
    if (Xbox.getButtonClick(L3))
      Serial.println(F("L3"));
    if (Xbox.getButtonClick(R3))
      Serial.println(F("R3"));

    if (Xbox.getButtonClick(L1))
      Serial.println(F("L1"));
    if (Xbox.getButtonClick(R1))
      Serial.println(F("R1"));
    if (Xbox.getButtonClick(XBOX)) {
      Xbox.setLedMode(ROTATING);
      Serial.println(F("Xbox"));
    }

    if (Xbox.getButtonClick(A))
      Serial.println(F("A"));
    if (Xbox.getButtonClick(B))
      Serial.println(F("B"));
    if (Xbox.getButtonClick(X))
      Serial.println(F("X"));
    if (Xbox.getButtonClick(Y))
      Serial.println(F("Y"));
  }
  delay(1);
}






