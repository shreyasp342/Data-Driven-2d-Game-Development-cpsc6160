#ifndef PLAYER__H
#define PLAYER__H

#include "twowaysprite.h"

class ExplodingSprite;

class Player : public twowaySprite {
public:
  Player(const std::string&);
  Player(const Player&);
  ~Player();

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  void collided() { collision = true; }
  void missed() { collision = false; }
  Player& operator=(const Player&);

  void right();
  void left();
  void up();
  void down();
  void stop();
  virtual void explode();
private:
  bool collision;
  Vector2f initialVelocity;
  ExplodingSprite* explosion;
};
#endif
