#include "enemy.h"
#include "renderContext.h"

Enemy::Enemy( const std::string& name) :
  MultiSprite(name),
  collision(false),
  initialVelocity(getVelocity()),
  initialX(getX()),
  facing(RIGHT),
  health(100)
  { }

Enemy::Enemy( const std::string& name, int px, int py, int vx, int vy) :
  MultiSprite(name, px, py, vx, vy),
  collision(false),
  initialVelocity(getVelocity()),
  initialX(getX()),
  facing(RIGHT),
  health(100)
  { }

Enemy::Enemy(const Enemy& s) :
  MultiSprite(s), 
  collision(s.collision),
  initialVelocity(s.getVelocity()),
  initialX(s.getX()),
  facing(s.facing),
  health(s.health)
  { }

Enemy& Enemy::operator=(const Enemy& s) {
  MultiSprite::operator=(s);
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  initialX = s.initialX;
  facing = s.facing;
  health = s.health;
  return *this;
}

void Enemy::explode() {
  setHealth(getHealth() - 5);
  if(getHealth() <= 0){
    MultiSprite::explode();
  }
}

void Enemy::update(Uint32 ticks) {
    advanceFrame(ticks);
    MultiSprite::update(ticks);

    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    setPosition(getPosition() + incr);
    // stop();
    if ( getX() < initialX - 200) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > initialX + 200) {
    setVelocityX( -fabs( getVelocityX() ) );
  }
}

