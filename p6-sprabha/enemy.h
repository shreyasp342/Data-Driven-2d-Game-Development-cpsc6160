#ifndef ENEMY__H
#define ENEMY__H

#include "multisprite.h"
#include "drawable.h"

class Enemy : public MultiSprite {
public:
  Enemy(const std::string&);
  Enemy(const std::string&, int, int, int, int);
  Enemy(const Enemy&);
  virtual void update(Uint32 ticks);

  void collided() { collision = true; }
  void missed() { collision = false; }
  Enemy& operator=(const Enemy&);

  void explode();
  void setHealth(int x) { health = x; }
  int getHealth() const { return health; }

  enum FACE {LEFT, RIGHT};
  FACE getPlayerDirection() const { return facing; }
  
private:
  bool collision;
  Vector2f initialVelocity;
  float initialX;
  FACE facing;
  int health;
};
#endif
