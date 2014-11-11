#ifndef _KOELNTURM_H_
#define _KOELNTURM_H_

#include <Arduino.h>

#include "App.h"

class Koelnturm : public App {
private:
  unsigned long startTime;
  unsigned long timeCode;
public:
  Koelnturm(size_t width, size_t height);
  virtual void handleInput(Input& input);
  virtual void run(unsigned long tick);
  virtual void render(Canvas& canvas);
  void reset();
  void renderAnimation1(Canvas& canvas, unsigned long timeCode);
  void renderAnimation2(Canvas& canvas, unsigned long timeCode);
  void renderAnimation3(Canvas& canvas, unsigned long timeCode);
  void renderAnimation4(Canvas& canvas, unsigned long timeCode);
  void renderAnimation5(Canvas& canvas, unsigned long timeCode);
  void renderAnimation6(Canvas& canvas, unsigned long timeCode);
  void renderAnimation7(Canvas& canvas, unsigned long timeCode);
};

#endif

