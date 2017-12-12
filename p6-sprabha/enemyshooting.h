#ifndef ENEMYSHOOTING__H
#define ENEMYSHOOTING__H
#include <string>
#include <iostream>
#include <list>
#include "sprite.h"
#include "bullet.h"
#include "enemy.h"

class EnemyShooting : public Enemy {
public:
  EnemyShooting(const std::string& n);
  EnemyShooting(const std::string& n, int, int, int, int);
  EnemyShooting(const EnemyShooting& s);

  virtual void update(Uint32 ticks);
  virtual void draw() const;

  std::list<Bullet> getBullets() {return bullets;};
  unsigned int getBulletList();
  unsigned int getFreeList();

  void shoot();

private:
  std::string bulletName;
  std::list<Bullet> bullets;
  std::list<Bullet> freelist;
  float minSpeed;
  float bulletInterval;
  float timeSinceLastFrame;
  EnemyShooting& operator=(const EnemyShooting&);
};

#endif