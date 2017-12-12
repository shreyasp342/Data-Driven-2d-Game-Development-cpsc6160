#include "enemy.h"
#include "renderContext.h"

Enemy::Enemy( const std::string& name) :
  MultiSprite(name),
  imagesRight( RenderContext::getInstance()->getImages(name) ),
  imagesLeft( RenderContext::getInstance()->getImages(name+"Left") ),
  collision(false),
  initialVelocity(getVelocity()),
  initialX(getX()),
  facing(RIGHT)
  {
    MultiSprite::images = imagesRight;
  }

Enemy::Enemy(const Enemy& s) :
  MultiSprite(s), 
  imagesRight(s.imagesRight),
  imagesLeft(s.imagesLeft),
  // images(s.images),
  collision(s.collision),
  initialVelocity(s.getVelocity()),
  initialX(s.getX()),
  facing(s.facing)
  { 
    MultiSprite::images = imagesRight;
  }

Enemy& Enemy::operator=(const Enemy& s) {
  MultiSprite::operator=(s);
  imagesRight = (s.imagesRight);
  imagesLeft = (s.imagesLeft);
  MultiSprite::images = imagesRight;
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  initialX = s.initialX;
  facing = s.facing;
  return *this;
}

void Enemy::stop() { 
  setVelocity(Vector2f(0,0));
}

void Enemy::right() { 
  if ( getX() < worldWidth-getScaledWidth() - 20) {
    setVelocityX(initialVelocity[0]);
    MultiSprite::images = imagesRight;
    facing = RIGHT;
  }
} 
void Enemy::left()  { 
  if ( getX() > 20) {
    setVelocityX(-initialVelocity[0]);
    MultiSprite::images = imagesLeft;
    facing = LEFT;
  }
} 
void Enemy::up()    { 
  if ( getY() > -25) {
    setVelocityY( -initialVelocity[1] );
  }
} 
void Enemy::down()  { 
  if ( getY() < worldHeight-getScaledHeight() +5) {
    setVelocityY( initialVelocity[1] );
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
    MultiSprite::images = imagesRight;
  }
  if ( getX() > initialX + 200) {
    setVelocityX( -fabs( getVelocityX() ) );
    MultiSprite::images = imagesLeft;
  }
}

