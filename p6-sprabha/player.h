#ifndef PLAYER__H
#define PLAYER__H

#include "multisprite.h"
#include "drawable.h"

class Player : public MultiSprite {
public:
  Player(const std::string&);
  Player(const Player&);
  virtual void update(Uint32 ticks);

  void collided() { collision = true; }
  void missed() { collision = false; }
  Player& operator=(const Player&);

  void right();
  void left();
  void up();
  void down();
  void stop();
  void explode();
  void setObstruct(const int);
  int getLimiter() const { return limiter; }
  void setHealth(int x) { health = x; }
  int getHealth() const { return health; }

  enum FACE {LEFT, RIGHT};
  FACE getPlayerDirection() const { return facing; }

protected:
  std::vector<Image *> imagesRight;
  std::vector<Image *> imagesLeft;
  
private:
  bool collision;
  Vector2f initialVelocity;
  FACE facing;
  int health;
  int limiter;
};
#endif
