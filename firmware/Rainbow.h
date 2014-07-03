#ifndef _RAINBOW_H_
#define _RAINBOW_H_

#include <Arduino.h>

#include "App.h"

class Rainbow : public App {
private:
  unsigned long prevUpdateTime;
  int colorIndex;
  boolean needsRendering;
public:
  Rainbow(size_t width, size_t height);
  virtual void handleInput(Input& input);
  virtual void run(unsigned long tick);
  virtual void render(Canvas& canvas);
};

#endif

