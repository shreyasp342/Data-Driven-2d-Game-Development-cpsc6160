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
  setHealth(getHealth() - 1);
  if(getHealth() <= 0){
    MultiSprite::explode();
  }
}

void Player::setObstruct(const int obstruct){
  // obstruct = x;
  switch(obstruct){
      case 0: std::cout << obstruct << 0 << std::endl; limiter = 400; break;
      case 1: std::cout << obstruct << 1 << std::endl; limiter = 1050; break;
      case 2: std::cout << obstruct << 2 << std::endl; limiter = 1700; break;
      case 3: std::cout << obstruct << 3 << std::endl; limiter = 2350; break;
      case 4: std::cout << obstruct << 4 << std::endl; limiter = 3000; break;
      case 5: std::cout << obstruct << 5 << std::endl; limiter = 3650; break;
      case 6: std::cout << obstruct << 6 << std::endl; limiter = 4300; break;
      case 7: std::cout << obstruct << 7 << std::endl; limiter = 4500; break;
      // case 7: std::cout << obstruct << 7 << std::endl; limiter = 4500; break;
      default: std::cout << obstruct << 8 << std::endl; limiter = 4500; break;
    }
}

void Player::update(Uint32 ticks) {
    advanceFrame(ticks);
    MultiSprite::update(ticks);

    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    
    // std::cout << obstruct << ", " << limiter << ", " << getX() << std::endl;;
    if(getX() > limiter){
      setX(limiter);
    }
    // std::cout << obstruct << std::endl;
    setPosition(getPosition() + incr);
    stop();
}

