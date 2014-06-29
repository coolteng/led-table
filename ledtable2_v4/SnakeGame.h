#include "App.h"

class SnakeGame : public App {

private:
  //Snake start position and direction & initialise variables
  int curLength;//Curren length of snake
  int xs[127];//Array containing all snake segments,
  int ys[127];// max snake length is array length
  int dir;//Current Direction of snake
  int score;
  
  int ax;//Apple x position
  int ay;//Apple y position
  int acolor;
  
  int gameSpeed;
  
  unsigned long prevUpdateTime;

  boolean collide(int x1, int x2, int y1, int y2, int w1, int w2, int h1, int h2);
  void snakeInit();
  void runSnake();
  void setDirection(input_t curControl);
  void die();
public:
  SnakeGame(size_t width, size_t height);
  virtual void handleInput(Input &input);
  virtual void run(unsigned long tick);
  virtual void render(Canvas &canvas);
  
};
