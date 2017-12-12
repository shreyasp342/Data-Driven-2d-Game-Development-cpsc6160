#ifndef ENEMY__H
#define ENEMY__H

#include "multisprite.h"
#include "drawable.h"

class Enemy : public MultiSprite {
public:
  Enemy(const std::string&);
  Enemy(const Enemy&);
  virtual void update(Uint32 ticks);

  void collided() { collision = true; }
  void missed() { collision = false; }
  Enemy& operator=(const Enemy&);

  void right();
  void left();
  void up();
  void down();
  void stop();

  enum FACE {LEFT, RIGHT};
  FACE getPlayerDirection() const { return facing; }

protected:
  std::vector<Image *> imagesRight;
  std::vector<Image *> imagesLeft;
  
private:
  bool collision;
  Vector2f initialVelocity;
  float initialX;
  FACE facing;
};
#endif
