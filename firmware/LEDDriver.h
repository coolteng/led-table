#ifndef _LEDDRIVER_H_
#define _LEDDRIVER_H_

#include <Arduino.h>

#include "config.h"

typedef unsigned int color_t;

/* *** LED color table *** */
#define  COLOR_OFF       0x000000
#define  COLOR_GREEN     0x00FF00
#define  COLOR_RED       0xFF0000
#define  COLOR_BLUE      0x0000FF
#define  COLOR_YELLOW    0xFFFF00
#define  COLOR_LBLUE     0x00FFFF
#define  COLOR_PURPLE    0xFF00FF
#define  COLOR_WHITE     0XFFFFFF
extern color_t colorLib[6];
#define DIM(x) ( (((x&0xFF0000)>>18)<<16) | (((x&0x00FF00)>>10)<<8) | ((x&0x0000FF)>>2) )


class LEDDriver {
public:
  virtual void initPixels();
  virtual void setPixel(int pixel, color_t color);
  virtual color_t getPixel(int pixel);
  virtual void clearPixels();
  virtual void showPixels();
};


#ifdef USE_OCTOWS2811

#define MAX_NUMBER_STRIPS 8
#ifndef _OCTOWS2811_H_
#include <OctoWS2811.h>
#endif

extern DMAMEM int displayMemory[LEDS_CHANNEL_1*6];
extern int drawingMemory[LEDS_CHANNEL_1*6];
extern const int config;
extern OctoWS2811 octoleds;

template<int ledsPerStrip>
class OctoWS2811Driver : public LEDDriver {
public:
  virtual void initPixels();
  virtual void setPixel(int pixel, color_t color);
  virtual color_t getPixel(int pixel);
  virtual void clearPixels();
  virtual void showPixels();
};

template<int ledsPerStrip>
void OctoWS2811Driver<ledsPerStrip>::initPixels(){
  octoleds.begin();
}

template<int ledsPerStrip>
void OctoWS2811Driver<ledsPerStrip>::setPixel(int n, color_t color){
  octoleds.setPixel(n, color);  
}

template<int ledsPerStrip>
color_t OctoWS2811Driver<ledsPerStrip>::getPixel(int n){
  return octoleds.getPixel(n);  
}

template<int ledsPerStrip>
void OctoWS2811Driver<ledsPerStrip>::clearPixels(){
  for(int n=0; n<ledsPerStrip; ++n) 
  {
    octoleds.setPixel(n, 0);
  }
}

template<int ledsPerStrip>
void OctoWS2811Driver<ledsPerStrip>::showPixels(){
  octoleds.show(); 
}

#endif

#ifdef USE_FAST_LED

#include <FastLED.h>

template<int numberOfLeds>
class FAST_LEDDriver : public LEDDriver {
private:
  CRGB leds[numberOfLeds];

public:
  virtual void initPixels();
  virtual void setPixel(int pixel, color_t color);
  virtual color_t getPixel(int pixel);
  virtual void clearPixels();
  virtual void showPixels();
};

template<int numberOfLeds>
void FAST_LEDDriver<numberOfLeds>::initPixels()
{
#if LEDS_CHANNEL_1 > 0
#ifdef FAST_LED_CHANNEL_1_CHIPSET_WITH_CLOCK
  FastLED.addLeds<FAST_LED_CHANNEL_1_CHIPSET, FAST_LED_CHANNEL_1_DATA_PIN, FAST_LED_CHANNEL_1_CLOCK_PIN, RGB>(leds, LEDS_CHANNEL_1);
#else
  FastLED.addLeds<FAST_LED_CHANNEL_1_CHIPSET, FAST_LED_CHANNEL_1_DATA_PIN, RGB>(leds, LEDS_CHANNEL_1);
#endif
#endif
#if LEDS_CHANNEL_2 > 0
#ifdef FAST_LED_CHANNEL_2_CHIPSET_WITH_CLOCK
  FastLED.addLeds<FAST_LED_CHANNEL_2_CHIPSET, FAST_LED_CHANNEL_2_DATA_PIN, FAST_LED_CHANNEL_2_CLOCK_PIN, RGB>(leds, LEDS_CHANNEL_2);
#else
  FastLED.addLeds<FAST_LED_CHANNEL_2_CHIPSET, FAST_LED_CHANNEL_2_DATA_PIN, RGB>(leds, LEDS_CHANNEL_2);
#endif
#endif
#if LEDS_CHANNEL_3 > 0
#ifdef FAST_LED_CHANNEL_3_CHIPSET_WITH_CLOCK
  FastLED.addLeds<FAST_LED_CHANNEL_3_CHIPSET, FAST_LED_CHANNEL_3_DATA_PIN, FAST_LED_CHANNEL_3_CLOCK_PIN, RGB>(leds, LEDS_CHANNEL_3);
#else
  FastLED.addLeds<FAST_LED_CHANNEL_3_CHIPSET, FAST_LED_CHANNEL_3_DATA_PIN, RGB>(leds, LEDS_CHANNEL_3);
#endif
#endif
#if LEDS_CHANNEL_4 > 0
#ifdef FAST_LED_CHANNEL_4_CHIPSET_WITH_CLOCK
  FastLED.addLeds<FAST_LED_CHANNEL_4_CHIPSET, FAST_LED_CHANNEL_4_DATA_PIN, FAST_LED_CHANNEL_4_CLOCK_PIN, RGB>(leds, LEDS_CHANNEL_4);
#else
  FastLED.addLeds<FAST_LED_CHANNEL_4_CHIPSET, FAST_LED_CHANNEL_4_DATA_PIN, RGB>(leds, LEDS_CHANNEL_4);
#endif
#endif
#if LEDS_CHANNEL_5 > 0
#ifdef FAST_LED_CHANNEL_5_CHIPSET_WITH_CLOCK
  FastLED.addLeds<FAST_LED_CHANNEL_5_CHIPSET, FAST_LED_CHANNEL_5_DATA_PIN, FAST_LED_CHANNEL_5_CLOCK_PIN, RGB>(leds, LEDS_CHANNEL_5);
#else
  FastLED.addLeds<FAST_LED_CHANNEL_5_CHIPSET, FAST_LED_CHANNEL_5_DATA_PIN, RGB>(leds, LEDS_CHANNEL_5);
#endif
#endif
#if LEDS_CHANNEL_6 > 0
#ifdef FAST_LED_CHANNEL_6_CHIPSET_WITH_CLOCK
  FastLED.addLeds<FAST_LED_CHANNEL_6_CHIPSET, FAST_LED_CHANNEL_6_DATA_PIN, FAST_LED_CHANNEL_6_CLOCK_PIN, RGB>(leds, LEDS_CHANNEL_6);
#else
  FastLED.addLeds<FAST_LED_CHANNEL_6_CHIPSET, FAST_LED_CHANNEL_6_DATA_PIN, RGB>(leds, LEDS_CHANNEL_6);
#endif
#endif
#if LEDS_CHANNEL_7 > 0
#ifdef FAST_LED_CHANNEL_7_CHIPSET_WITH_CLOCK
  FastLED.addLeds<FAST_LED_CHANNEL_7_CHIPSET, FAST_LED_CHANNEL_7_DATA_PIN, FAST_LED_CHANNEL_7_CLOCK_PIN, RGB>(leds, LEDS_CHANNEL_7);
#else
  FastLED.addLeds<FAST_LED_CHANNEL_7_CHIPSET, FAST_LED_CHANNEL_7_DATA_PIN, RGB>(leds, LEDS_CHANNEL_7);
#endif
#endif
#if LEDS_CHANNEL_8 > 0
#ifdef FAST_LED_CHANNEL_8_CHIPSET_WITH_CLOCK
  FastLED.addLeds<FAST_LED_CHANNEL_8_CHIPSET, FAST_LED_CHANNEL_8_DATA_PIN, FAST_LED_CHANNEL_8_CLOCK_PIN, RGB>(leds, LEDS_CHANNEL_8);
#else
  FastLED.addLeds<FAST_LED_CHANNEL_8_CHIPSET, FAST_LED_CHANNEL_8_DATA_PIN, RGB>(leds, LEDS_CHANNEL_8);
#endif
#endif
}

template<int numberOfLeds>
void FAST_LEDDriver<numberOfLeds>::setPixel(int n, color_t color)
{
  leds[n] = CRGB(color);
}

template<int numberOfLeds>
color_t FAST_LEDDriver<numberOfLeds>::getPixel(int n)
{
  return (leds[n].r << 16) + (leds[n].g << 8) + leds[n].b;  
}

template<int numberOfLeds>
void FAST_LEDDriver<numberOfLeds>::showPixels()
{
  FastLED.show();
}

template<int numberOfLeds>
void FAST_LEDDriver<numberOfLeds>::clearPixels()
{
  for(int n=0; n<numberOfLeds; ++n) 
  {
    leds[n] = CRGB(0);
  }
}

#endif

#endif
