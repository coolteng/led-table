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

#define CONCURRENT_APPS 4

Canvas canvas[CONCURRENT_APPS] = {
  Canvas(13, 11, 0, 0, 52, leds),
  Canvas(13, 11, 13, 0, 52, leds),
  Canvas(13, 11, 26, 0, 52, leds),
  Canvas(13, 11, 39, 0, 52, leds)
};
Input input[CONCURRENT_APPS] = {
  Input(0),
  Input(1),
  Input(2),
  Input(3)
};

AppController appController[CONCURRENT_APPS] = {
  AppController(13,11),
  AppController(13,11),
  AppController(13,11),
  AppController(13,11)
};


void setup(){
  Serial.begin(115200);

  delay(2000);
  //Initialise led driver
  Serial.println("Initialize pixels");
  leds.initPixels();
//  leds.clearPixels();
//  Serial.println("Show pixels");
//  leds.showPixels();
//  Serial.println("Pixels shown");
  
  for(int appIndex = 0; appIndex <CONCURRENT_APPS; ++appIndex) {
    input[appIndex].init();
    appController[appIndex].startMenu();
  }
  
  //Init random number generator
  randomSeed(millis());
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
    Serial.print("Frames per second:");
    Serial.println(renderedFrames);
    lastFPSUpdate = currentTick;
    renderedFrames = 0;
  }
}






