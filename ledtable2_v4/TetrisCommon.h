/* LedTable for Teensy3
 *
 * Written by: Klaas De Craemer, 2013
 * https://sites.google.com/site/klaasdc/led-table
 * 
 * Common code and defines for the Tetris game
 */
 
#ifndef _TETRIS_COMMON_H_
#define _TETRIS_COMMON_H_

//Maximum size of bricks. Individual bricks can still be smaller (eg 3x3)
#define  MAX_BRICK_SIZE    4
#define  BRICKOFFSET       -1 // Y offset for new bricks

#define  INIT_SPEED        1000//Initial delay in ms between brick drops
#define  SPEED_STEP        100  // Factor for speed increase between levels, default 10
#define  LEVELUP           2 //Number of rows before levelup, default 5

// Playing field
/*
struct Field{
  uint8_t pix[width][height+1];//Make field one larger so that collision detection with bottom of field can be done in a uniform way
  unsigned int color[width][height];
};
*/
struct Field{
  uint8_t pix;//Make field one larger so that collision detection with bottom of field can be done in a uniform way
  unsigned int color;
};


//Structure to represent active brick on screen
struct Brick{
  boolean enabled;//Brick is disabled when it has landed
  int xpos,ypos;
  int yOffset;//Y-offset to use when placing brick at top of field
  uint8_t siz;
  uint8_t pix[MAX_BRICK_SIZE][MAX_BRICK_SIZE];

  unsigned int color;
};

//Struct to contain the different choices of blocks
struct AbstractBrick{
  int yOffset;//Y-offset to use when placing brick at top of field
  uint8_t siz;
  uint8_t pix[MAX_BRICK_SIZE][MAX_BRICK_SIZE];
};

#endif
