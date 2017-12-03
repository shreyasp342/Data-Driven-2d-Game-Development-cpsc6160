#include "twowaysprite.h"
#include "gamedata.h"
#include "renderContext.h"
#include "explodingSprite.h"

void twowaySprite::advanceFrame(Uint32 ticks) {
  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
    timeSinceLastFrame = 0;
  }
}

twowaySprite::~twowaySprite( ) { if (explosion) delete explosion; }

twowaySprite::twowaySprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  imagesRight( RenderContext::getInstance()->getImages(name) ),
  imagesLeft( RenderContext::getInstance()->getImages(name+"Left") ),
  images( RenderContext::getInstance()->getImages(name) ),
  explosion(nullptr),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

twowaySprite::twowaySprite(const twowaySprite& s) :
  Drawable(s), 
  imagesRight(s.imagesRight),
  imagesLeft(s.imagesLeft),
  images(s.images),
  explosion(s.explosion),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight )
  { }

twowaySprite& twowaySprite::operator=(const twowaySprite& s) {
  Drawable::operator=(s);
  imagesRight = (s.imagesRight);
  imagesLeft = (s.imagesLeft);
  images = (s.images);
  explosion = s.explosion;
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  return *this;
}

void twowaySprite::explode() {
  if ( !explosion ) {
    Sprite 
    sprite(getName(), getPosition(), getVelocity(), images[currentFrame]);
    explosion = new ExplodingSprite(sprite);
  }
}

void twowaySprite::draw() const { 
  if ( explosion ) explosion->draw();
  else images[currentFrame]->draw(getX(), getY(), getScale());
}

void twowaySprite::update(Uint32 ticks) { 
  if ( getX() < 0) {
    images = imagesRight;
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    images = imagesLeft;
  }  
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

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
  }  
}
