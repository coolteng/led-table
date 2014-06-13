
#include "LEDDriver.h"

#if defined(USE_OCTOWS2811) && defined(USE_FAST_LED)
#error "Only one of USE_OCTOWS2811 and USE_FAST_LED can be defined"
#endif

#ifdef USE_OCTOWS2811

DMAMEM int displayMemory[LEDS_CHANNEL_1*6];
int drawingMemory[LEDS_CHANNEL_1*6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 octoleds(LEDS_CHANNEL_1, displayMemory, drawingMemory, config);

#endif

color_t colorLib[6] = {RED, GREEN, BLUE, YELLOW, LBLUE, PURPLE};

#define MAP_POSITION_TO_PIXEL(x, y)  
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

