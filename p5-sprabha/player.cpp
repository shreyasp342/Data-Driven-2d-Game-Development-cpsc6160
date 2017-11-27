#include "player.h"
#include "explodingSprite.h"

Player::~Player( ) { if (explosion) delete explosion; }

Player::Player( const std::string& name) :
  twowaySprite(name),
  collision(false),
  initialVelocity(getVelocity()),
  explosion(nullptr)
{ }

Player::Player(const Player& s) :
  twowaySprite(s), 
  collision(s.collision),
  initialVelocity(s.getVelocity()),
  explosion(s.explosion)
  { }

Player& Player::operator=(const Player& s) {
  twowaySprite::operator=(s);
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  explosion = s.explosion;
  return *this;
}

void Player::explode() {
  if ( !explosion ) {
    Sprite 
    sprite(getName(), getPosition(), getVelocity(), images[currentFrame]);
    explosion = new ExplodingSprite(sprite);
  }
}

void Player::draw() const { 
  if ( explosion ) explosion->draw();
  else images[currentFrame]->draw(getX(), getY(), getScale());
}

void Player::stop() { 
  setVelocity(Vector2f(0,0));
}

void Player::right() { 
  if ( getX() < worldWidth-getScaledWidth() +20) {
    setVelocityX(initialVelocity[0]);
    images = imagesRight;
  }
} 
void Player::left()  { 
  if ( getX() > -30) {
    setVelocityX(-initialVelocity[0]);
    images = imagesLeft;
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
  if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
    }
    return;
  }

    advanceFrame(ticks);
    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    setPosition(getPosition() + incr);
    stop();
}

