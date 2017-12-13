#include "enemyshooting.h"
#include "gamedata.h"

EnemyShooting::EnemyShooting(const std::string& name) :
  Enemy(name),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets(),
  freelist(),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ),
  bulletInterval(Gamedata::getInstance().getXmlInt(bulletName+"/interval")),
  timeSinceLastFrame(0),
  shootDelay(0)
{ }

EnemyShooting::EnemyShooting(const std::string& name, int px, int py, int vx, int vy) :
  Enemy(name, px, py, vx, vy),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets(),
  freelist(),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ),
  bulletInterval(Gamedata::getInstance().getXmlInt(bulletName+"/interval")),
  timeSinceLastFrame(0),
  shootDelay(0)
{ }

EnemyShooting::EnemyShooting(const EnemyShooting& s) :
  Enemy(s),
  bulletName(s.bulletName),
  bullets(s.bullets),
  freelist(s.freelist),
  minSpeed(s.minSpeed),
  bulletInterval(s.bulletInterval),
  timeSinceLastFrame(s.timeSinceLastFrame),
  shootDelay(s.shootDelay)
{ }

unsigned int EnemyShooting::getBulletList(){
  return bullets.size();
}

unsigned int EnemyShooting::getFreeList(){
  return freelist.size();
}

void EnemyShooting::shoot() { 
  if ( timeSinceLastFrame < bulletInterval ) return;
  float deltaX = getScaledWidth() - 50;
  float deltaY = getScaledHeight()/4;
  // I need to add some minSpeed to velocity:
  // if(getPlayerDirection() == RIGHT){
  //   if(freelist.empty()) {
  //     Bullet bullet(bulletName);
  //     bullet.setPosition( getPosition() + Vector2f(deltaX, deltaY) );
  //     bullet.setVelocity( getVelocity() + Vector2f(minSpeed, 0) );
  //     bullets.push_back( bullet );
  //     timeSinceLastFrame = 0;
  //   } else{
  //     Bullet b=freelist.front();
  //     freelist.pop_front();
  //     b.reset();
  //     b.setPosition( getPosition() + Vector2f(deltaX, deltaY) );
  //     b.setVelocity( getVelocity() + Vector2f(minSpeed, 0) );
  //     bullets.push_back(b);
  //   }
  // } else{
    deltaX = deltaX - 175;
    if(freelist.empty()) {
      Bullet bullet(bulletName);
      bullet.setPosition( getPosition() + Vector2f(deltaX, deltaY) );
      bullet.setVelocity( getVelocity() - Vector2f(minSpeed, 0) );
      bullets.push_back( bullet );
      timeSinceLastFrame = 0;
    } else{
      Bullet b=freelist.front();
      freelist.pop_front();
      b.reset();
      b.setPosition( getPosition() + Vector2f(deltaX, deltaY) );
      b.setVelocity( getVelocity() - Vector2f(minSpeed, 0) );
      bullets.push_back(b);
    // }
  }

  
}

void EnemyShooting::draw() const { 
  Enemy::draw();
  for ( const Bullet& bullet : bullets ) {
    bullet.draw();
  }
}

void EnemyShooting::update(Uint32 ticks) {
  timeSinceLastFrame += ticks;
  Enemy::update(ticks);

  if (shootDelay >= 10){
    shootDelay = 0;
    shoot();
  } else shootDelay++;

  std::list<Bullet>::iterator ptr=bullets.begin();
  while(ptr!=bullets.end())
  {
    ptr->update(ticks);
    if(ptr->goneTooFar()){
      freelist.push_back(*ptr);
      ptr=bullets.erase(ptr);
    }
    else ++ptr;
  }
}

