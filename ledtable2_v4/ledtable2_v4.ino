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


#include "LEDDriver.h"
#include "Canvas.h"
#include "App.h"
#include "Input.h"

//USB and Xbox gamepad library
#ifdef TRULALALA
#include <XBOXUSB.h>
#include <spi4teensy3.h>
#endif

#ifdef USE_FAST_LED
FAST_LEDDriver<LEDS_CHANNEL_1+LEDS_CHANNEL_2+LEDS_CHANNEL_3+LEDS_CHANNEL_4+LEDS_CHANNEL_5+LEDS_CHANNEL_6+LEDS_CHANNEL_7+LEDS_CHANNEL_8> leds;
#endif

#ifdef USE_OCTOWS2811
OctoWS2811Driver<LEDS_CHANNEL_1+LEDS_CHANNEL_2+LEDS_CHANNEL_3+LEDS_CHANNEL_4+LEDS_CHANNEL_5+LEDS_CHANNEL_6+LEDS_CHANNEL_7+LEDS_CHANNEL_8> leds;
#endif

Canvas canvas[CONCURRENT_APPS] = {
  Canvas(FIELD_WIDTH, FIELD_HEIGHT, 0, 0, FIELD_WIDTH*CONCURRENT_APPS, leds),
#if CONCURRENT_APPS > 1
  Canvas(FIELD_WIDTH, FIELD_HEIGHT, FIELD_WIDTH*1, 0, FIELD_WIDTH*CONCURRENT_APPS, leds),
#endif
#if CONCURRENT_APPS > 2
  Canvas(FIELD_WIDTH, FIELD_HEIGHT, FIELD_WIDTH*2, 0, FIELD_WIDTH*CONCURRENT_APPS, leds),
#endif
#if CONCURRENT_APPS > 3
  Canvas(FIELD_WIDTH, FIELD_HEIGHT, FIELD_WIDTH*3, 0, FIELD_WIDTH*CONCURRENT_APPS, leds),
#endif
};
Input input[CONCURRENT_APPS] = {
  Input(0),
#if CONCURRENT_APPS > 1
  Input(1),
#endif
#if CONCURRENT_APPS > 2
  Input(2),
#endif
#if CONCURRENT_APPS > 3
  Input(3)
#endif
};

AppController appController[CONCURRENT_APPS] = {
  AppController(FIELD_WIDTH, FIELD_HEIGHT),
#if CONCURRENT_APPS > 1
  AppController(FIELD_WIDTH, FIELD_HEIGHT),
#endif
#if CONCURRENT_APPS > 2
  AppController(FIELD_WIDTH, FIELD_HEIGHT),
#endif
#if CONCURRENT_APPS > 3
  AppController(FIELD_WIDTH, FIELD_HEIGHT),
#endif
};


void setup(){
  Serial.begin(115200);

  //Initialise led driver
  Serial.println("Initialize pixels");
  leds.initPixels();
  
  for(int appIndex = 0; appIndex <CONCURRENT_APPS; ++appIndex) {
    input[appIndex].init();
    appController[appIndex].startMenu();
  }
  
  //Init random number generator
  randomSeed(millis());
}


void loop(){
  static unsigned long lastFPSUpdate = 0;
  static unsigned long renderedFrames = 0;
  UsbTask();
  unsigned long currentTick = millis();
  for(int appIndex = 0; appIndex < CONCURRENT_APPS; ++appIndex) {
    appController[appIndex].process(currentTick, input[appIndex], canvas[appIndex]);
  }
  leds.showPixels();
  ++renderedFrames;
  if(currentTick - lastFPSUpdate > 1000) {
    // get random number, to make the first game different
    random(8);
    
    Serial.print("Frames per second:");
    Serial.println(renderedFrames);
    lastFPSUpdate = currentTick;
    renderedFrames = 0;
  }
}






