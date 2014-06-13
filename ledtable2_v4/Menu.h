#ifndef _MENU_H_
#define _MENU_H_

#include <Arduino.h>

#include "App.h"

class Menu : public App {
private:
  int textPosition;
  unsigned int curSelection;
  unsigned long prevUpdateTime;
  boolean selectionChanged;
  boolean runSelection;
  void checkSelectionRange();
  
public:
  Menu(size_t width, size_t height);
  virtual void handleInput(Input& input);
  virtual void run(unsigned long tick);
  virtual void render(Canvas& canvas);
  virtual void controlFlow(AppController& appController);
};

#endif

