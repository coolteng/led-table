
#include "Canvas.h"

#include "config.h"

#ifdef HORIZONTAL_LEFT_TO_RIGHT
#define MAP_POSITION_TO_PIXEL(x, y) (y+yOffset)*rowLength+(x+xOffset)
#endif
#ifdef HORIZONTAL_LEFT_TO_RIGHT_AND_REVERSE
#define MAP_POSITION_TO_PIXEL(x, y) (y*rowLength +(y%2 ?  x : ((FIELD_HEIGHT-1)-x))
#endif

//  #ifdef ORIENTATION_HORIZONTAL_UPSIDEDOWN
//  setPixel(63 - (y%2 ? y*FIELD_WIDTH + x : y*FIELD_WIDTH + ((FIELD_HEIGHT-1)-x)),color);
//    #ifdef USE_CONSOLE_OUTPUT
//      setTablePixelConsole(y,x,color);
//    #endif
//  #else
//  #ifdef ORIENTATION_HORIZONTAL
//  setPixel(y%2 ? y*FIELD_WIDTH + x : y*FIELD_WIDTH + ((FIELD_HEIGHT-1)-x),color);
//    #ifdef USE_CONSOLE_OUTPUT
//      setTablePixelConsole(y,x,color);
//    #endif
//  #else
//  setPixel(x%2 ? x*FIELD_WIDTH + ((FIELD_HEIGHT-1)-y) : x*FIELD_WIDTH + y,color);
//    #ifdef USE_CONSOLE_OUTPUT
//      setTablePixelConsole(x,y,color);
//    #endif
//  #endif
//  #endif

Canvas::Canvas(uint8_t width, uint8_t height, uint8_t xOffset, uint8_t yOffset, uint8_t rowLength, LEDDriver& ledDriver)
  : width(width), height(height), xOffset(xOffset), yOffset(yOffset), rowLength(rowLength), ledDriver(ledDriver)
{
  
}

void Canvas::setPixel(uint8_t x, uint8_t y, color_t color)
{
  ledDriver.setPixel(MAP_POSITION_TO_PIXEL(x, y), color);
}

color_t Canvas::getPixel(uint8_t x, uint8_t y)
{
  return ledDriver.getPixel(MAP_POSITION_TO_PIXEL(x, y));
}

void Canvas::clear()
{
  ledDriver.clearPixels();
}

void Canvas::show()
{
  ledDriver.showPixels();
}



/* *** text helper methods *** */
#include "font.h"
uint8_t charBuffer[8][8];

boolean Canvas::printText(char* text, unsigned int textLength, int xoffset, int yoffset, int color)
{
  uint8_t curLetterWidth = 0;
  int curX = width;
  boolean finished = true;
  //Loop over all the letters in the string
  for (int i=0; i<textLength; i++){
    //Determine width of current letter and load its pixels in a buffer
    curLetterWidth = loadCharInBuffer(text[i]);
    //Loop until width of letter is reached
    for (int lx=0; lx<curLetterWidth; lx++){
      //Now copy column per column to field (as long as within the field
      if (curX>=width+xoffset){//If we are to far to the right, stop loop entirely
        break;
      } else if (curX-xoffset>=0){//Draw pixels as soon as we are "inside" the drawing area
        for (int ly=0; ly<8; ly++){//Finally copy column
          setPixel(curX-xoffset,yoffset+ly,charBuffer[lx][ly]*color);
        }
        finished = false;
      }
      curX++;
    }
  }
  return finished;
}

//Load char in buffer and return width in pixels
uint8_t Canvas::loadCharInBuffer(char letter)
{
  uint8_t* tmpCharPix;
  uint8_t tmpCharWidth;
  
  int letterIdx = (letter-32)*8;
  
  int x=0; int y=0;
  for (int idx=letterIdx; idx<letterIdx+8; idx++){
    for (int x=0; x<8; x++){
      charBuffer[x][y] = ((font[idx]) & (1<<(7-x)))>0;
    }
    y++;
  }
  
  tmpCharWidth = 8;
  return tmpCharWidth;
}

void Canvas::scrollTextBlocked(char* text, int textLength, int color){
/*  unsigned long prevUpdateTime = 0;
  Serial.println(-textLength);
  
  for (int x=FIELD_WIDTH; x>-(textLength*8); x--){
    printText(text, textLength, x, 2, color);
    //Read buttons
    unsigned long curTime;
    do{
      readInput();
      curTime = millis();
    } while (((curTime - prevUpdateTime) < TEXTSPEED) && (curControl == BTN_NONE));//Once enough time  has passed, proceed
    
    prevUpdateTime = curTime;
  }
*/
}



/* *********************************** */

void Canvas::fadeOut(){
  //Select random fadeout animation
  int selection = random(3);
  
  switch(selection){
    case 0:
    case 1:
    {
      //Fade out by dimming all pixels
      for (int i=0; i<100; i++){
        dimLeds(0.97);
        show();
        delay(10);
      }
      break;
    }
    case 2:
    {
      //Fade out by swiping from left to right with ruler
      const int ColumnDelay = 10;
      int curColumn = 0;
      for (int i=0; i<width*ColumnDelay; i++){
        dimLeds(0.97);
        if (i%ColumnDelay==0){
          //Draw vertical line
          for (int y=0;y<height;y++){
            setPixel(curColumn, y, COLOR_GREEN);
          }
          curColumn++;
        }
        show();
        delay(5);
      }
      //Sweep complete, keep dimming leds for short time
      for (int i=0; i<100; i++){
        dimLeds(0.9);
        show();
        delay(5);
      }
      break;
    }
  }
}

void Canvas::dimLeds(float factor){
  //Reduce brightness of all LEDs, typical factor is 0.97
  for (uint8_t y=0;y<height;y++){
    for (uint8_t x=0;x<width;x++){
      int curColor = getPixel(x,y);
      //Derive the tree colors
      int r = ((curColor & 0xFF0000)>>16);
      int g = ((curColor & 0x00FF00)>>8);
      int b = (curColor & 0x0000FF);
      //Reduce brightness
      r = r*factor;
      g = g*factor;
      b = b*factor;
      //Pack into single variable again
      curColor = (r<<16) + (g<<8) + b;
      //Set led again
      setPixel(x,y,curColor);
    }
  }
}

//For debugging, allow field to be printed on serial console
#ifdef USE_CONSOLE_OUTPUT
void Canvas::outputToConsole(){
  Serial.write(27);       // escape command
  Serial.print("[2J");    // clear screen command
  Serial.write(27);       // escape command
  Serial.print("[H");     // cursor to home command
  uint8_t x,y;
  for (y=0;y<height;y++){
    Serial.print("|");
    for (x=0;x<width;x++){
      if (getPixel(x,y) == 0){
        Serial.print(" ");
      } else {
        Serial.print("X");
      }
    }
    Serial.println("|");
  }
  Serial.print("------------");
}
#endif

