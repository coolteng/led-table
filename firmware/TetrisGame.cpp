/* LedTable for Teensy3
 *
 * Written by: Klaas De Craemer, 2013
 * https://sites.google.com/site/klaasdc/led-table
 * 
 * Main code for the Tetris game
 */

#include "TetrisGame.h"


//Brick "library"
AbstractBrick brickLib[7] = {
  {
      1,//yoffset when adding brick to field
      4,
      { {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
      }
  },
  {
      0,
      4,
      { {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0}
      }
  },
  {
      1,
      3,
      { {0,0,0,0},
        {1,1,1,0},
        {0,0,1,0},
        {0,0,0,0}
      }
  },
  {
      1,
      3,
      { {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
      }
  },
  {
      1,
      3,
      { {0,0,0,0},
        {1,1,1,0},
        {0,1,0,0},
        {0,0,0,0}
      }
  },
  {
      1,
      3,
      { {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
      }
  },
  {
      1,
      3,
      { {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
      }
  }
};


#define field(x,y) field[(x)+(y)*width]

TetrisGame::TetrisGame(size_t width, size_t height)
  : App(width, height), brickSpeed(INIT_SPEED), prevControl(BTN_NONE), curControl(BTN_NONE)
{
  field = new Field[width*(height+1)];
  clearField();
  brickSpeed = INIT_SPEED;
  
  newActiveBrick();
}

TetrisGame::~TetrisGame()
{
  delete[] field;
}

void TetrisGame::handleInput(Input &input){
  curControl = input.read();
  if(curControl != prevControl) 
  {
    switch(curControl){
      case BTN_LEFT:
        shiftActiveBrick(DIR_LEFT);
        break;
      case BTN_RIGHT:
        shiftActiveBrick(DIR_RIGHT);
        break;
      case BTN_DOWN:
        shiftActiveBrick(DIR_DOWN);
        break;
      case BTN_UP:
        rotateActiveBrick();
        break;
      case BTN_START:
        ended = true;
        break;
    }
    prevControl = curControl;
  }
}

void TetrisGame::run(unsigned long currentTime){
  if(currentTime - prevUpdateTime > brickSpeed)
  {
    if (activeBrick.enabled){
      shiftActiveBrick(DIR_DOWN);
    } else {
      //Active brick has "crashed", check for full lines
      //and create new brick at top of field
      checkFullLines();
      newActiveBrick();
    }
    prevUpdateTime = currentTime;
  }
}

void TetrisGame::render(Canvas &canvas){
  int x,y;
  for (x=0;x<width;x++){
    for (y=0;y<height;y++){
      uint8_t activeBrickPix = 0;
      if (activeBrick.enabled){//Only draw brick if it is enabled
        //Now check if brick is "in view"
        if ((x>=activeBrick.xpos) && (x<(activeBrick.xpos+(activeBrick.siz)))
            && (y>=activeBrick.ypos) && (y<(activeBrick.ypos+(activeBrick.siz)))){
          activeBrickPix = (activeBrick.pix)[x-activeBrick.xpos][y-activeBrick.ypos];
        }
      }
      if (field(x,y).pix == 1){
        canvas.setPixel(x,y, field(x,y).color);
      } else if (activeBrickPix == 1){
        canvas.setPixel(x,y, activeBrick.color);
      } else {
        canvas.setPixel(x,y, 0x000000);
      }
    }
  }
  canvas.show();
}

/* *** Game functions *** */

void TetrisGame::newActiveBrick(){
//  uint8_t selectedBrick = 3;
  uint8_t selectedBrick = random(7);
  uint8_t selectedColor = random(6);

  //Set properties of brick
  activeBrick.siz = brickLib[selectedBrick].siz;
  activeBrick.yOffset = brickLib[selectedBrick].yOffset;
  activeBrick.xpos = width/2 - activeBrick.siz/2;
  activeBrick.ypos = BRICKOFFSET-activeBrick.yOffset;
  activeBrick.enabled = true;
  
  //Set color of brick
  activeBrick.color = colorLib[selectedColor];
  
  //Copy pix array of selected Brick
  uint8_t x,y;
  for (y=0;y<MAX_BRICK_SIZE;y++){
    for (x=0;x<MAX_BRICK_SIZE;x++){
      activeBrick.pix[x][y] = (brickLib[selectedBrick]).pix[x][y];
    }
  }
  
  //Check collision, if already, then game is over
  if (checkFieldCollision(&activeBrick)){
    ended = true;
  }
}

//Check collision between bricks in the field and the specified brick
boolean TetrisGame::checkFieldCollision(struct Brick* brick){
  uint8_t bx,by;
  uint8_t fx,fy;
  for (by=0;by<MAX_BRICK_SIZE;by++){
    for (bx=0;bx<MAX_BRICK_SIZE;bx++){
      fx = (*brick).xpos + bx;
      fy = (*brick).ypos + by;
      if (( (*brick).pix[bx][by] == 1) 
            && ( field(fx,fy).pix == 1)){
        return true;
      }
    }
  }
  return false;
}

//Check collision between specified brick and all sides of the playing field
boolean TetrisGame::checkSidesCollision(struct Brick* brick){
  //Check vertical collision with sides of field
  uint8_t bx,by;
  uint8_t fx,fy;
  for (by=0;by<MAX_BRICK_SIZE;by++){
    for (bx=0;bx<MAX_BRICK_SIZE;bx++){
      if ( (*brick).pix[bx][by] == 1){
        fx = (*brick).xpos + bx;//Determine actual position in the field of the current pix of the brick
        fy = (*brick).ypos + by;
        if (fx<0 || fx>=width){
          return true;
        }
      }
    }
  }
  return false;
}


void TetrisGame::rotateActiveBrick(){
  Brick tmpBrick;
  //Copy active brick pix array to temporary pix array
  uint8_t x,y;
  for (y=0;y<MAX_BRICK_SIZE;y++){
    for (x=0;x<MAX_BRICK_SIZE;x++){
      tmpBrick.pix[x][y] = activeBrick.pix[x][y];
    }
  }
  tmpBrick.xpos = activeBrick.xpos;
  tmpBrick.ypos = activeBrick.ypos;
  tmpBrick.siz = activeBrick.siz;
  
  //Depending on size of the active brick, we will rotate differently
  if (activeBrick.siz == 3){
    //Perform rotation around center pix
    tmpBrick.pix[0][0] = activeBrick.pix[0][2];
    tmpBrick.pix[0][1] = activeBrick.pix[1][2];
    tmpBrick.pix[0][2] = activeBrick.pix[2][2];
    tmpBrick.pix[1][0] = activeBrick.pix[0][1];
    tmpBrick.pix[1][1] = activeBrick.pix[1][1];
    tmpBrick.pix[1][2] = activeBrick.pix[2][1];
    tmpBrick.pix[2][0] = activeBrick.pix[0][0];
    tmpBrick.pix[2][1] = activeBrick.pix[1][0];
    tmpBrick.pix[2][2] = activeBrick.pix[2][0];
    //Keep other parts of temporary block clear
    tmpBrick.pix[0][3] = 0;
    tmpBrick.pix[1][3] = 0;
    tmpBrick.pix[2][3] = 0;
    tmpBrick.pix[3][3] = 0;
    tmpBrick.pix[3][2] = 0;
    tmpBrick.pix[3][1] = 0;
    tmpBrick.pix[3][0] = 0;
    
  } else if (activeBrick.siz == 4){
    //Perform rotation around center "cross"
    tmpBrick.pix[0][0] = activeBrick.pix[0][3];
    tmpBrick.pix[0][1] = activeBrick.pix[1][3];
    tmpBrick.pix[0][2] = activeBrick.pix[2][3];
    tmpBrick.pix[0][3] = activeBrick.pix[3][3];
    tmpBrick.pix[1][0] = activeBrick.pix[0][2];
    tmpBrick.pix[1][1] = activeBrick.pix[1][2];
    tmpBrick.pix[1][2] = activeBrick.pix[2][2];
    tmpBrick.pix[1][3] = activeBrick.pix[3][2];
    tmpBrick.pix[2][0] = activeBrick.pix[0][1];
    tmpBrick.pix[2][1] = activeBrick.pix[1][1];
    tmpBrick.pix[2][2] = activeBrick.pix[2][1];
    tmpBrick.pix[2][3] = activeBrick.pix[3][1];
    tmpBrick.pix[3][0] = activeBrick.pix[0][0];
    tmpBrick.pix[3][1] = activeBrick.pix[1][0];
    tmpBrick.pix[3][2] = activeBrick.pix[2][0];
    tmpBrick.pix[3][3] = activeBrick.pix[3][0];
  } else {
    Serial.println("Brick size error");
  }
  
  //Now validate by checking collision.
  //Collision possibilities:
  //      -Brick now sticks outside field
  //      -Brick now sticks inside fixed bricks of field
  //In case of collision, we just discard the rotated temporary brick
  if ((!checkSidesCollision(&tmpBrick)) && (!checkFieldCollision(&tmpBrick))){
    //Copy temporary brick pix array to active pix array
    for (y=0;y<MAX_BRICK_SIZE;y++){
      for (x=0;x<MAX_BRICK_SIZE;x++){
        activeBrick.pix[x][y] = tmpBrick.pix[x][y];
      }
    }
  }
}

//Shift brick left/right/down by one if possible
void TetrisGame::shiftActiveBrick(int dir){
  //Change position of active brick (no copy to temporary needed)
  if (dir == DIR_LEFT){
    activeBrick.xpos--;
  } else if (dir == DIR_RIGHT){
    activeBrick.xpos++;
  } else if (dir == DIR_DOWN){
    activeBrick.ypos++;
  }
  
  //Check position of active brick
  //Two possibilities when collision is detected:
  //    -Direction was LEFT/RIGHT, just revert position back
  //    -Direction was DOWN, revert position and fix block to field on collision
  //When no collision, keep activeBrick coordinates
  if ((checkSidesCollision(&activeBrick)) || (checkFieldCollision(&activeBrick))){
    //Serial.println("coll");
    if (dir == DIR_LEFT){
      activeBrick.xpos++;
    } else if (dir == DIR_RIGHT){
      activeBrick.xpos--;
    } else if (dir == DIR_DOWN){
      activeBrick.ypos--;//Go back up one
      addActiveBrickToField();
      activeBrick.enabled = false;//Disable brick, it is no longer moving
    }
  }
}

//Copy active pixels to field, including color
void TetrisGame::addActiveBrickToField(){
  uint8_t bx,by;
  uint8_t fx,fy;
  for (by=0;by<MAX_BRICK_SIZE;by++){
    for (bx=0;bx<MAX_BRICK_SIZE;bx++){
      fx = activeBrick.xpos + bx;
      fy = activeBrick.ypos + by;
      
      if (fx>=0 && fy>=0 && fx<width && fy<height && activeBrick.pix[bx][by]){//Check if inside playing field
        //field.pix[fx][fy] = field.pix[fx][fy] || activeBrick.pix[bx][by];
        field(fx,fy).pix = activeBrick.pix[bx][by];
        field(fx,fy).color = activeBrick.color;
      }
    }
  }
}

//Move all pix from te field above startRow down by one. startRow is overwritten
void TetrisGame::moveFieldDownOne(uint8_t startRow){
  if (startRow == 0){//Topmost row has nothing on top to move...
    return;
  }
  uint8_t x,y;
  for (y=startRow-1; y>0; y--){
    for (x=0;x<width; x++){
      field(x,y+1).pix = field(x,y).pix;
      field(x,y+1).color = field(x,y).color;
    }
  }
}

void TetrisGame::checkFullLines(){
  int x,y;
  int minY = 0;
  for (y=(height-1); y>=minY; y--){
    uint8_t rowSum = 0;
    for (x=0; x<width; x++){
      rowSum = rowSum + (field(x,y).pix);
    }
    if (rowSum>=width){
      //Found full row, animate its removal
      for (x=0;x<width; x++){
        field(x,y).pix = 0;
//        printField();
//        delay(100);
      }
      //Move all upper rows down by one
      moveFieldDownOne(y);
      y++; minY++;
//      printField();
//      delay(100);
      
      nbRowsThisLevel++; nbRowsTotal++;
      if (nbRowsThisLevel >= LEVELUP){
        nbRowsThisLevel = 0;
        brickSpeed = brickSpeed - SPEED_STEP;
        if (brickSpeed<200){
          brickSpeed = 200;
        }
      }
    }
  }
}

void TetrisGame::clearField(){
  uint8_t x,y;
  for (y=0;y<height;y++){
    for (x=0;x<width;x++){
      field(x,y).pix = 0;
      field(x,y).color = 0;
    }
  }
  for (x=0;x<width;x++){//This last row is invisible to the player and only used for the collision detection routine
    field(x,height).pix = 1;
  }
}


