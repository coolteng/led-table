
#include "Koelnturm.h"

const unsigned long ANIMATION_LENGTH = 288000;
const unsigned long FIRST_ANIMATION_ROUNDS = 8;
const unsigned long FIRST_ANIMATION_START = 0;
const unsigned long FIRST_ANIMATION_LENGTH = 36000;
const unsigned long FIRST_ANIMATION_ROUND_LENGTH = FIRST_ANIMATION_LENGTH / FIRST_ANIMATION_ROUNDS;

const unsigned long SECOND_ANIMATION_ROUNDS = 10;
const unsigned long SECOND_ANIMATION_START = 36000;
const unsigned long SECOND_ANIMATION_LENGTH = 36000;
const unsigned long SECOND_ANIMATION_STATES = 16;
const unsigned long SECOND_ANIMATION_ROUND_LENGTH = SECOND_ANIMATION_LENGTH / SECOND_ANIMATION_ROUNDS;

const unsigned long THIRD_ANIMATION_ROUNDS = 6;
const unsigned long THIRD_ANIMATION_START = 72000;
const unsigned long THIRD_ANIMATION_LENGTH = 30000;
const unsigned long THIRD_ANIMATION_ROUND_LENGTH = THIRD_ANIMATION_LENGTH / THIRD_ANIMATION_ROUNDS;

const unsigned long FOURTH_ANIMATION_ROUNDS = 2;
const unsigned long FOURTH_ANIMATION_START = 102000;
const unsigned long FOURTH_ANIMATION_LENGTH = 53000;
const unsigned long FOURTH_ANIMATION_ROUND_LENGTH = 30000;
const unsigned long FOURTH_ANIMATION_OFFSET = 6000;

const unsigned long FIFTH_ANIMATION_ROUNDS = 11;
const unsigned long FIFTH_ANIMATION_START = 155000;
const unsigned long FIFTH_ANIMATION_LENGTH = 55000;
const unsigned long FIFTH_ANIMATION_ROUND_LENGTH = FIFTH_ANIMATION_LENGTH / FIFTH_ANIMATION_ROUNDS;

const unsigned long SIXTH_ANIMATION_ROUNDS = 2;
const unsigned long SIXTH_ANIMATION_START = 210000;
const unsigned long SIXTH_ANIMATION_LENGTH = 48000;
const unsigned long SIXTH_ANIMATION_ROUND_LENGTH = SIXTH_ANIMATION_LENGTH / SIXTH_ANIMATION_ROUNDS;

const unsigned long SEVENTH_ANIMATION_ROUNDS = 19;
const unsigned long SEVENTH_ANIMATION_START = 258000;
const unsigned long SEVENTH_ANIMATION_LENGTH = 30000;
const unsigned long SEVENTH_ANIMATION_ROUND_LENGTH = SEVENTH_ANIMATION_LENGTH / SEVENTH_ANIMATION_ROUNDS;

Koelnturm::Koelnturm(size_t width, size_t height) 
  : App(width, height), startTime(millis()), timeCode(0)
{
}

void Koelnturm::handleInput(Input& input)
{

}

void Koelnturm::reset()
{
  startTime = millis();
}

void Koelnturm::run(unsigned long curTime)
{
  timeCode = (curTime-startTime) % ANIMATION_LENGTH;
}

void Koelnturm::render(Canvas& canvas)
{
  if(timeCode >= FIRST_ANIMATION_START && timeCode < FIRST_ANIMATION_START+FIRST_ANIMATION_LENGTH) {
    renderAnimation1(canvas, timeCode-FIRST_ANIMATION_START);
  }
  if(timeCode >= SECOND_ANIMATION_START && timeCode < SECOND_ANIMATION_START+SECOND_ANIMATION_LENGTH) {
    renderAnimation2(canvas, timeCode-SECOND_ANIMATION_START);
  }
  if(timeCode >= THIRD_ANIMATION_START && timeCode < THIRD_ANIMATION_START+THIRD_ANIMATION_LENGTH) {
    renderAnimation3(canvas, timeCode-THIRD_ANIMATION_START);
  }
  if(timeCode >= FOURTH_ANIMATION_START && timeCode < FOURTH_ANIMATION_START+FOURTH_ANIMATION_LENGTH) {
    renderAnimation4(canvas, timeCode-FOURTH_ANIMATION_START+FOURTH_ANIMATION_OFFSET);
  }
  if(timeCode >= FIFTH_ANIMATION_START && timeCode < FIFTH_ANIMATION_START+FIFTH_ANIMATION_LENGTH) {
    renderAnimation5(canvas, timeCode-FIFTH_ANIMATION_START);
  }
  if(timeCode >= SIXTH_ANIMATION_START && timeCode < SIXTH_ANIMATION_START+SIXTH_ANIMATION_LENGTH) {
    renderAnimation6(canvas, timeCode-SIXTH_ANIMATION_START);
  }
  if(timeCode >= SEVENTH_ANIMATION_START && timeCode < SEVENTH_ANIMATION_START+SEVENTH_ANIMATION_LENGTH) {
    renderAnimation7(canvas, timeCode-SEVENTH_ANIMATION_START);
  }
}

void Koelnturm::renderAnimation1(Canvas& canvas, unsigned long timeCodeInAnimation)
{
  unsigned long timeCodeInCurrentRound = timeCodeInAnimation % FIRST_ANIMATION_ROUND_LENGTH;
  int shownRows = timeCodeInCurrentRound / (FIRST_ANIMATION_ROUND_LENGTH / height);
  for(int y=0; y<height; ++y) {
    for(int x=0; x<width; ++x) {
      if(shownRows >= y) {
        canvas.setPixel(x, height-y-1, COLOR_WHITE);
      } else {
        canvas.setPixel(x, height-y-1, COLOR_OFF);
      }
    }
  }
}

void setPixelGroup(int x, int y, Canvas& canvas, color_t color) {
  switch(x) {
  case 0:
    canvas.setPixel(0, y, color);
    canvas.setPixel(1, y, color);
    canvas.setPixel(2, y, color);
    canvas.setPixel(3, y, color);
    break;
  case 1:
    canvas.setPixel(4, y, color);
    canvas.setPixel(5, y, color);
    canvas.setPixel(6, y, color);
    canvas.setPixel(7, y, color);
    break;
  case 2:
    canvas.setPixel(8, y, color);
    canvas.setPixel(9, y, color);
    canvas.setPixel(10, y, color);
    canvas.setPixel(11, y, color);
    canvas.setPixel(12, y, color);
    break;
  case 3:
    canvas.setPixel(13, y, color);
    canvas.setPixel(14, y, color);
    canvas.setPixel(15, y, color);
    canvas.setPixel(16, y, color);
    break;
  case 4:
    canvas.setPixel(17, y, color);
    canvas.setPixel(18, y, color);
    canvas.setPixel(19, y, color);
    canvas.setPixel(20, y, color);
    break;
  }
}

void Koelnturm::renderAnimation2(Canvas& canvas, unsigned long timeCodeInAnimation)
{
  static color_t states[SECOND_ANIMATION_STATES] = { DIM(COLOR_WHITE), COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, DIM(COLOR_WHITE), DIM(DIM(COLOR_WHITE)), COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, DIM(DIM(COLOR_WHITE))};
  unsigned long timeCodeInCurrentRound = timeCodeInAnimation % SECOND_ANIMATION_ROUND_LENGTH;
  
  int stateInRound = timeCodeInCurrentRound / (SECOND_ANIMATION_ROUND_LENGTH / SECOND_ANIMATION_STATES);
  for(int y=0; y<height; ++y) {
    int stateAtFirst = (stateInRound+(((y%2)*(SECOND_ANIMATION_STATES/2)+(y/2)*1)))%SECOND_ANIMATION_STATES;
    for(int group=0; group<5; ++group) {
      setPixelGroup(group, height-1-y, canvas, states[(stateAtFirst+4-group)%SECOND_ANIMATION_STATES]);
    }
  }
}

void Koelnturm::renderAnimation3(Canvas& canvas, unsigned long timeCodeInAnimation)
{
  unsigned long timeCodeInCurrentRound = timeCodeInAnimation % THIRD_ANIMATION_ROUND_LENGTH;
  int currentRow = timeCodeInCurrentRound / (THIRD_ANIMATION_ROUND_LENGTH / height);
  for(int y=0; y<height; ++y) {
    for(int x=0; x<width; ++x) {
      if(currentRow == y) {
        canvas.setPixel(x, y, COLOR_WHITE);
      } else {
        canvas.setPixel(x, y, DIM(DIM(COLOR_WHITE)));
      }
    }
  }
}

void Koelnturm::renderAnimation4(Canvas& canvas, unsigned long timeCodeInAnimation)
{
  unsigned long timeCodeInCurrentRound = timeCodeInAnimation % FOURTH_ANIMATION_ROUND_LENGTH;
  color_t color = COLOR_OFF;
  if(timeCodeInCurrentRound >= 9000 && timeCodeInCurrentRound < 10000) {
    byte brightness = (timeCodeInCurrentRound - 9000)/4;
    color = brightness | brightness << 8 | brightness << 16;
  } else if(timeCodeInCurrentRound >= 10000 && timeCodeInCurrentRound < 29000) {
    color = COLOR_WHITE;
  } else if(timeCodeInCurrentRound >= 29000 && timeCodeInCurrentRound < 30000) {
    byte brightness = 255-(timeCodeInCurrentRound - 29000)/4;
    color = brightness | brightness << 8 | brightness << 16;
  }
  for(int y=0; y<height; ++y) {
    for(int x=0; x<width; ++x) {
      canvas.setPixel(x, y, color);
    }
  }
}

void Koelnturm::renderAnimation5(Canvas& canvas, unsigned long timeCodeInAnimation)
{
  unsigned long timeCodeInCurrentRound = timeCodeInAnimation % FIFTH_ANIMATION_ROUND_LENGTH;
  color_t color = COLOR_WHITE;
  if(timeCodeInCurrentRound >= 0 && timeCodeInCurrentRound < 1000) {
    byte brightness = 255-timeCodeInCurrentRound/4;
    color = brightness | brightness << 8 | brightness << 16;
  } else if(timeCodeInCurrentRound >= 1000 && timeCodeInCurrentRound < 1500) {
    byte brightness = 255-1000/4;
    color = brightness | brightness << 8 | brightness << 16;
  } else if(timeCodeInCurrentRound >= 1500 && timeCodeInCurrentRound < 2500) {
    byte brightness = 255-(2500-timeCodeInCurrentRound)/4;
    color = brightness | brightness << 8 | brightness << 16;
  }
  for(int y=0; y<height; ++y) {
    for(int x=0; x<width; ++x) {
      canvas.setPixel(x, y, color);
    }
  }
}

void Koelnturm::renderAnimation6(Canvas& canvas, unsigned long timeCodeInAnimation)
{
  unsigned long timeCodeInCurrentRound = timeCodeInAnimation % SIXTH_ANIMATION_ROUND_LENGTH;
  int steps = width*height*3;
  int currentStep = timeCodeInCurrentRound * steps / SIXTH_ANIMATION_ROUND_LENGTH;
  for(int y=0; y<height; ++y) {
    for(int x=0; x<width; ++x) {
      if((width-x)+y*width < currentStep && (width-x)+y*width + width*height*2 > currentStep) {
        canvas.setPixel(x, y, COLOR_WHITE);
      } else {
        canvas.setPixel(x, y, COLOR_OFF);
      }
    }
  }
}

void Koelnturm::renderAnimation7(Canvas& canvas, unsigned long timeCodeInAnimation)
{
  unsigned long timeCodeInCurrentRound = timeCodeInAnimation % SEVENTH_ANIMATION_ROUND_LENGTH;
  color_t colors[2];
  if(timeCodeInCurrentRound >= 0 && timeCodeInCurrentRound < SEVENTH_ANIMATION_ROUND_LENGTH/4) {
    byte brightness = timeCodeInCurrentRound*255/(SEVENTH_ANIMATION_ROUND_LENGTH/4);
    colors[0] = brightness | brightness << 8 | brightness << 16;
    colors[1] = (255-brightness) | (255-brightness) << 8 | (255-brightness) << 16;
  } else if(timeCodeInCurrentRound >= SEVENTH_ANIMATION_ROUND_LENGTH/4 && timeCodeInCurrentRound < SEVENTH_ANIMATION_ROUND_LENGTH/2) {
    colors[0] = COLOR_WHITE;
    colors[1] = COLOR_OFF;
  } else if(timeCodeInCurrentRound >= SEVENTH_ANIMATION_ROUND_LENGTH/2 && timeCodeInCurrentRound < SEVENTH_ANIMATION_ROUND_LENGTH*3/4) {
    byte brightness = (timeCodeInCurrentRound-SEVENTH_ANIMATION_ROUND_LENGTH/2)*255/(SEVENTH_ANIMATION_ROUND_LENGTH/4);
    colors[0] = (255-brightness) | (255-brightness) << 8 | (255-brightness) << 16;
    colors[1] = brightness | brightness << 8 | brightness << 16;
  } else {
    colors[0] = COLOR_OFF;
    colors[1] = COLOR_WHITE;
  }
  for(int y=0; y<height; ++y) {
    for(int group=0; group<5; ++group) {
      setPixelGroup(group, y, canvas, colors[(group+y*5)%2]);
    }
  }
}


