#ifndef _TETRIS_GAME_H_
#define _TETRIS_GAME_H_

#include "App.h"
#include "TetrisCommon.h"

class TetrisGame : public App {

private:
  unsigned long prevUpdateTime;
  input_t curControl;
  uint16_t brickSpeed;
  uint8_t nbRowsThisLevel;
  uint16_t nbRowsTotal;
  Field *field;
  Brick activeBrick;
  
  boolean checkFieldCollision(struct Brick* brick);
  boolean checkSidesCollision(struct Brick* brick);
  void newActiveBrick();
  void rotateActiveBrick();
  void shiftActiveBrick(int dir);
  void addActiveBrickToField();
  void moveFieldDownOne(uint8_t startRow);
  void checkFullLines();
  void clearField();
public:
  TetrisGame(size_t width, size_t height);
  virtual ~TetrisGame();
  virtual void handleInput(Input &input);
  virtual void run(unsigned long tick);
  virtual void render(Canvas &canvas);
  
};

#endif

