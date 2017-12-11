#include "player.h"
#include "renderContext.h"

Player::Player( const std::string& name) :
  MultiSprite(name),
  imagesRight( RenderContext::getInstance()->getImages(name) ),
  imagesLeft( RenderContext::getInstance()->getImages(name+"Left") ),
  collision(false),
  initialVelocity(getVelocity()),
  facing(RIGHT)
  {
    MultiSprite::images = imagesRight;
  }

Player::Player(const Player& s) :
  MultiSprite(s), 
  imagesRight(s.imagesRight),
  imagesLeft(s.imagesLeft),
  // images(s.images),
  collision(s.collision),
  initialVelocity(s.getVelocity()),
  facing(s.facing)
  { 
    MultiSprite::images = imagesRight;
  }

Player& Player::operator=(const Player& s) {
  MultiSprite::operator=(s);
  imagesRight = (s.imagesRight);
  imagesLeft = (s.imagesLeft);
    MultiSprite::images = imagesRight;
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  facing = s.facing;
  return *this;
}

void Player::stop() { 
  setVelocity(Vector2f(0,0));
}

void Player::right() { 
  if ( getX() < worldWidth-getScaledWidth() - 20) {
    setVelocityX(initialVelocity[0]);
    MultiSprite::images = imagesRight;
    facing = RIGHT;
  }
} 
void Player::left()  { 
  if ( getX() > 20) {
    setVelocityX(-initialVelocity[0]);
    MultiSprite::images = imagesLeft;
    facing = LEFT;
  }
} 
void Player::up()    { 
  if ( getY() > -25) {
    setVelocityY( -initialVelocity[1] );
  }
} 
void Player::down()  { 
  if ( getY() < worldHeight-getScaledHeight() +5) {
    setVelocityY( initialVelocity[1] );
  }
}

void Player::update(Uint32 ticks) {
    advanceFrame(ticks);
    MultiSprite::update(ticks);

    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    setPosition(getPosition() + incr);
    stop();
}

