#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include <vector>
#include <ctime>
#include "smartSprite.h"
#include "subjectSprite.h"
#include "sprite.h"
#include "multisprite.h"
// #include "twowaysprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
#include "player.h"
#include "hud.h"
#include "collisionStrategy.h"
#include "shootingSprite.h"
#include "enemyshooting.h"

Engine::~Engine() { 
  for(auto sprite : dragonballs){
  	delete sprite;
  }
  for(auto sprite : enemies){
    delete sprite;
  }
  for(auto sprite : sprites){
    delete sprite;
  }
  delete player;
  for ( CollisionStrategy* strategy : strategies ) {
    delete strategy;
  }
  delete shenron;

  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  sky("sky", Gamedata::getInstance().getXmlInt("sky/factor") ),
  sky2("sky2", Gamedata::getInstance().getXmlInt("sky2/factor") ),
  city("city", Gamedata::getInstance().getXmlInt("city/factor") ),
  land("land", Gamedata::getInstance().getXmlInt("land/factor") ),
  dragonballs(),
  sprites(),
  collected(),
  player(new ShootingSprite("goku")),
  shenron(new Sprite("shenron")),
  enemies(),
  strategies(),
  currentStrategy(0),
  collision(false),
  viewport( Viewport::getInstance() ),
  currentSprite(0),
  makeVideo( false ),
  showHud( false ),
  sound(),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  counter(0)
{
  srand(time(0));
  Vector2f pos = player->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();
  dragonballs.push_back( new SmartSprite("Ball1", pos, w, h) );
  dragonballs.push_back( new SmartSprite("Ball2", pos, w, h) );
  dragonballs.push_back( new SmartSprite("Ball3", pos, w, h) );
  dragonballs.push_back( new SmartSprite("Ball4", pos, w, h) );
  dragonballs.push_back( new SmartSprite("Ball5", pos, w, h) );
  dragonballs.push_back( new SmartSprite("Ball6", pos, w, h) );
  dragonballs.push_back( new SmartSprite("Ball7", pos, w, h) );
  for (unsigned int i = 0; i < dragonballs.size(); ++i) {
    player->attach( dragonballs[i] );
  }

  std::cout << "Limiter: " << player->getLimiter() << std:: endl;

  for (unsigned int i = 0; i < 3; ++i) {
    std::string name = "cycle";
    int px = player->getLimiter() + 200;
    int py = rand()%worldHeight;
    // int py = Gamedata::getInstance().getXmlInt(name+"/startLoc/y");
    int vx = Gamedata::getInstance().getXmlInt(name+"/speedX");
    if(vx !=0) vx = (vx * (rand()%2?1:-1)) + (rand()%50 * (rand()%2?1:-1));
    int vy = Gamedata::getInstance().getXmlInt(name+"/speedY");
    if(vy !=0) vy = (vy * (rand()%2?1:-1)) + (rand()%50 * (rand()%2?1:-1));
    std::cout << px << ", " << py << ", " << vx << ", " << vy << ", " << rand()%2 << std::endl;
    enemies.push_back(new EnemyShooting(name.c_str(), px, py, vx, vy));
  }

  for (unsigned int i = 0; i < 5; ++i) {
    std::string name = "valor";
    int px = rand()%worldWidth * (rand()%2?1:-1);
    // int y = rand()%worldHeight;
    int py = Gamedata::getInstance().getXmlInt(name+"/startLoc/y");
    int vx = Gamedata::getInstance().getXmlInt(name+"/speedX");
    if(vx !=0) vx = (vx * (rand()%2?1:-1)) + (rand()%50 * (rand()%2?1:-1));
    int vy = Gamedata::getInstance().getXmlInt(name+"/speedY");
    if(vy !=0) vy = (vy * (rand()%2?1:-1)) + (rand()%50 * (rand()%2?1:-1));
    // std::cout << px << ", " << py << ", " << vx << ", " << vy << ", " << rand()%2 << std::endl;
    sprites.push_back(new MultiSprite(name.c_str(), px, py, vx, vy));
  }
  // sprites.push_back(new MultiSprite("valor"));
  // sprites.push_back(new twowaySprite("cycle"));
  // sprites.push_back(new EnemyShooting("cycle"));
  // std::cout << dragonballs[0]->getName() << std::endl;
  // collected.push_back(dragonballs[0]->getName());
  // std::cout << collected[0] << std::endl;
  
  strategies.push_back( new PerPixelCollisionStrategy );
  strategies.push_back( new RectangularCollisionStrategy );
  strategies.push_back( new MidPointCollisionStrategy );

  // Viewport::getInstance().setObjectToTrack(player);
  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  SDL_Color textColor;
  textColor.r = Gamedata::getInstance().getXmlInt("font/red");
  textColor.g = Gamedata::getInstance().getXmlInt("font/green");
  textColor.b = Gamedata::getInstance().getXmlInt("font/blue");
  textColor.a = Gamedata::getInstance().getXmlInt("font/alpha");
  
  sky.draw();
  if (dragonballs.size() <= 0){
    sky2.draw();
  }
  city.draw();
  for(auto sprite : dragonballs){
    if ( !(sprite->exploded()) ) sprite->draw();
  }
  if (dragonballs.size() <= 0){
    shenron->setScale(0.45);
    shenron->draw();
  }
  land.draw();
  for(auto sprite : sprites){
    sprite->draw();
  }
  player->draw();
  // player->setObstruct(collected.size());

  for(auto sprite : enemies){
    if ( !(sprite->exploded()) ) sprite->draw();
  }
  // auto it = enemies.begin();
  // while ( it != enemies.end() ) {
  //   if ( (*it)->exploded() ) {
  //     delete (*it);
  //     it = enemies.erase(it);
  //   }
  //   else{
  //     (*it)->draw();
  //     ++it;
  //   } 
  // }
  std::cout << enemies.size() << std::endl;

  for(auto ball : collected){ 
    int x = Gamedata::getInstance().getXmlInt(ball+"/collected/x");
    int y = Gamedata::getInstance().getXmlInt(ball+"/collected/y"); 
    IOmod::getInstance().writeImage(ball, x, y);
  }

  if (dragonballs.size() > 0){
    std::stringstream strm;
    strm << dragonballs.size() << " Dragon Balls Remaining";
    IOmod::getInstance().writeText(strm.str(), 500, 120, textColor);
  } else {
    SDL_Color textColor1;
    textColor1.r = Gamedata::getInstance().getXmlInt("hud/border/Color/red");
    textColor1.g = Gamedata::getInstance().getXmlInt("hud/border/Color/blue");
    textColor1.b = Gamedata::getInstance().getXmlInt("hud/border/Color/green");
    textColor1.a = Gamedata::getInstance().getXmlInt("hud/border/Color/alpha");
    IOmod::getInstance().writeText(" All 7 Dragon Balls Collected", 250, 120, textColor1);
    IOmod::getInstance().writeText(" Summon Shendron", 250, 150, textColor1);
  }

  strategies[currentStrategy]->draw();
  if ( collision ) {
    IOmod::getInstance().writeText("Oops: Collision", 500, 60, textColor);
  }

  drawHud();
  viewport.draw();  
  SDL_RenderPresent(renderer);
}

void Engine::checkForCollisions() {
  collision = false;
  for ( const Drawable* d : sprites ) {
    if ( strategies[currentStrategy]->execute(*player, *d) ) {
      collision = true;
    }
  }

  // if ( strategies[currentStrategy]->execute(*player, *enemy) ) {
  //   collision = true;
  //   player->up();  
  //   // dragonballs.push_back( new SmartSprite("Ball1", pos, w, h) );
  // }

  if ( strategies[currentStrategy]->execute(*sprites[0], *player) ) {
    collision = true;
    player->explode();
  }
  // for ( const auto d : player->getBullets() ) {
  //   if ( strategies[currentStrategy]->execute(*sprites[0], d) ) {
  //     collision = true;
  //     sprites[0]->explode();
  //   }
  // }
  for ( const auto d : player->getBullets() ) {
    auto it = enemies.begin();
    while ( it != enemies.end() ) {
      // if ( (*it)->exploded() ) {
      //   delete (*it);
      //   it = enemies.erase(it);
      // } 
      // else if ( strategies[currentStrategy]->execute(d, **it) ) {
      if ( strategies[currentStrategy]->execute(d, **it) ) {
        (*it)->explode();
        it++;
      }
      else ++it;
    }
  }

  auto it = dragonballs.begin();
  // while ( it != dragonballs.end() ) {
  //   if ( strategies[currentStrategy]->execute(*player, **it) ) {
  //     (*it)->explode();
  //     it++;
  //   }
  //   else ++it;
  // }
  // it = dragonballs.begin();
  while ( it != dragonballs.end() ) {
    // if ( (*it)->exploded() ) {
    if ( strategies[currentStrategy]->execute(*player, **it) ) {
      collected.push_back((*it)->getName());
      // std::cout << (*it)->getName() << std::endl;
      SmartSprite* doa = *it;
      player->detach(doa);
      delete doa;
      it = dragonballs.erase(it);
    }
    else ++it;
  }

  if ( collision ) {
    player->collided();
  }
  else {
    player->missed();
    collision = false;
  }
}

void Engine::update(Uint32 ticks) {
    std::cout << counter << ", " << player->getLimiter() << std::endl;
    player->setObstruct(counter);
  if(enemies.size()<=0 && counter < 7){
    player->setObstruct(++counter);
    std::cout << counter << ", " << player->getLimiter() << std::endl;
    for (unsigned int i = 0; i < 3; ++i) {
      std::string name = "cycle";
      int px = player->getLimiter() + 200;
      int py = rand()%worldHeight;
      // int py = Gamedata::getInstance().getXmlInt(name+"/startLoc/y");
      int vx = Gamedata::getInstance().getXmlInt(name+"/speedX");
      if(vx !=0) vx = (vx * (rand()%2?1:-1)) + (rand()%50 * (rand()%2?1:-1));
      int vy = Gamedata::getInstance().getXmlInt(name+"/speedY");
      if(vy !=0) vy = (vy * (rand()%2?1:-1)) + (rand()%50 * (rand()%2?1:-1));
      std::cout << px << ", " << py << ", " << vx << ", " << vy << ", " << rand()%2 << std::endl;
      enemies.push_back(new EnemyShooting(name.c_str(), px, py, vx, vy));
    }
  }
  // player->update(ticks);
  // if(enemies.size()<=0){
  //   player->setObstruct(++counter);
  //   std::cout << counter << ", " << player->getLimiter() << std::endl;
  //   for (unsigned int i = 0; i < 5; ++i) {
  //     std::string name = "cycle";
  //     int px = player->getLimiter() + 200;
  //     int py = rand()%worldHeight;
  //     // int py = Gamedata::getInstance().getXmlInt(name+"/startLoc/y");
  //     int vx = Gamedata::getInstance().getXmlInt(name+"/speedX");
  //     if(vx !=0) vx = (vx * (rand()%2?1:-1)) + (rand()%50 * (rand()%2?1:-1));
  //     int vy = Gamedata::getInstance().getXmlInt(name+"/speedY");
  //     if(vy !=0) vy = (vy * (rand()%2?1:-1)) + (rand()%50 * (rand()%2?1:-1));
  //     std::cout << px << ", " << py << ", " << vx << ", " << vy << ", " << rand()%2 << std::endl;
  //     enemies.push_back(new EnemyShooting(name.c_str(), px, py, vx, vy));
  //   }
  // }

  auto it = enemies.begin();
  while ( it != enemies.end() ) {
    if ( (*it)->exploded() ) {
      delete (*it);
      it = enemies.erase(it);
    }
    else{
      (*it)->update(ticks);
      ++it;
    } 
  }
  for(auto sprite : dragonballs){
  	sprite->update(ticks);
  }
  for(auto sprite : sprites){
    sprite->update(ticks);
  }
  // for(auto sprite : enemies){
  //   sprite->update(ticks);
  // }
  player->update(ticks);
  // enemy->update(ticks);
  if (dragonballs.size() <= 0){
    shenron->update(ticks);
  }
  checkForCollisions();
  sky.update();
  city.update();
  land.update();
  viewport.update(); // always update viewport last
}

void Engine::drawHud() const {
  unsigned int freelistSize = player->getFreeList();
  unsigned int bulletlistSize = player->getBulletList();
  
  if (showHud || clock.getSeconds() <= 3){
  	Hud::getInstance().draw(renderer);
    Hud::getInstance().drawPool(renderer, bulletlistSize, freelistSize);

  }
 }

bool Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_R] ) {
          clock.unpause();
          return true;
        }
        if ( keystate[SDL_SCANCODE_SPACE] ) {
            player->shoot();
        }
        if ( keystate[SDL_SCANCODE_G] ) {
            counter = 8;
        }
        if ( keystate[SDL_SCANCODE_M] ) {
          currentStrategy = (1 + currentStrategy) % strategies.size();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
        if (keystate[SDL_SCANCODE_F1] && !showHud) {
          showHud = true;
        }
        else if (keystate[SDL_SCANCODE_F1] && showHud) {
          showHud = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      if (keystate[SDL_SCANCODE_A]) {
        player->left();
      }
      if (keystate[SDL_SCANCODE_D]) {
        player->right();
      }
      if (keystate[SDL_SCANCODE_W]) {
        player->up();
      }
      if (keystate[SDL_SCANCODE_S]) {
        player->down();
      }
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
  return false;
}