#include "player.h"
#include "renderContext.h"

Player::Player( const std::string& name) :
  MultiSprite(name),
  imagesRight( RenderContext::getInstance()->getImages(name) ),
  imagesLeft( RenderContext::getInstance()->getImages(name+"Left") ),
  collision(false),
  initialVelocity(getVelocity()),
  facing(RIGHT),
  health(100),
  limiter(400)
  {
    MultiSprite::images = imagesRight;
  }

Player::Player(const Player& s) :
  MultiSprite(s), 
  imagesRight(s.imagesRight),
  imagesLeft(s.imagesLeft),
  collision(s.collision),
  initialVelocity(s.getVelocity()),
  facing(s.facing),
  health(s.getHealth()),
  limiter(400)
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
  health = s.health;
  limiter = s.limiter;
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

void Player::explode() {
  setHealth(getHealth() - 2);
  if(getHealth() <= 0){
    MultiSprite::explode();
  }
}

void Player::setObstruct(const int obstruct){
  switch(obstruct){
      case 0: limiter = 400; break;
      case 1: limiter = 1050; break;
      case 2: limiter = 1700; break;
      case 3: limiter = 2350; break;
      case 4: limiter = 3000; break;
      case 5: limiter = 3650; break;
      case 6: limiter = 4300; break;
      case 7: default: limiter = 4500; break;
    }
}

void Player::update(Uint32 ticks) {
    advanceFrame(ticks);
    MultiSprite::update(ticks);
    
    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    if(getX() > limiter){
      setX(limiter);
    }
    setPosition(getPosition() + incr);
    stop();
}

