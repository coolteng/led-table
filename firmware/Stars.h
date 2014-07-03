#ifndef _STARS_H_
#define _STARS_H_

#include <Arduino.h>

#include "App.h"

class Stars : public App {
private:
  unsigned long prevUpdateTime;
  unsigned long prevStarsCreationTime;
  boolean needsRendering;
  boolean createNewStars;
public:
  Stars(size_t width, size_t height);
  virtual void handleInput(Input& input);
  virtual void run(unsigned long tick);
  virtual void render(Canvas& canvas);
};

#endif

