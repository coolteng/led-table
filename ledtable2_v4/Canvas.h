#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <Arduino.h>

#include "LEDDriver.h"

class Canvas {
private:
  uint8_t width;
  uint8_t height;
  uint8_t xOffset;
  uint8_t yOffset;
  uint8_t rowLength;
  LEDDriver& ledDriver;
  uint8_t loadCharInBuffer(char letter);
#ifdef USE_CONSOLE_OUTPUT
  outputToConsole();
#endif
  
public:
  Canvas(uint8_t width, uint8_t height, uint8_t xOffset, uint8_t yOffset, uint8_t rowLength, LEDDriver& ledDriver);
  void setPixel(uint8_t x, uint8_t y, color_t color);
  color_t getPixel(uint8_t x, uint8_t y);
  boolean printText(char* text, size_t textLength, int xoffset, int yoffset, int color);
  void scrollTextBlocked(char* text, int textLength, int color);
  void clear();
  void show();
  void fadeOut();
  void dimLeds(float factor);
};

#endif

