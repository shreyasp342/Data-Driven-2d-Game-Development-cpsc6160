#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include <vector>
#include "smartSprite.h"
#include "subjectSprite.h"
#include "sprite.h"
#include "multisprite.h"
#include "twowaysprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
#include "player.h"
#include "hud.h"
#include "collisionStrategy.h"

Engine::~Engine() { 
  for(auto sprite : dragonballs){
  	delete sprite;
  }
  for(auto sprite : sprites){
    delete sprite;
  }
  delete player;
  for ( CollisionStrategy* strategy : strategies ) {
    delete strategy;
  }

  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  sky("sky", Gamedata::getInstance().getXmlInt("sky/factor") ),
  city("city", Gamedata::getInstance().getXmlInt("city/factor") ),
  land("land", Gamedata::getInstance().getXmlInt("land/factor") ),
  dragonballs(),
  sprites(),
  player(new SubjectSprite("goku")),
  strategies(),
  currentStrategy(0),
  collision(false),
  viewport( Viewport::getInstance() ),
  currentSprite(0),
  makeVideo( false ),
  showHud( false )
{
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

  sprites.push_back(new MultiSprite("valor"));
  sprites.push_back(new twowaySprite("cycle"));
  
  strategies.push_back( new PerPixelCollisionStrategy );
  strategies.push_back( new RectangularCollisionStrategy );
  strategies.push_back( new MidPointCollisionStrategy );

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
  city.draw();
  land.draw();

  for(auto sprite : sprites){
    sprite->draw();
  }

  for(auto sprite : dragonballs){
  	sprite->draw();
  }
  if (dragonballs.size() > 0){
    std::stringstream strm;
    strm << dragonballs.size() << " Dragon Balls Remaining";
    IOmod::getInstance().writeText(strm.str(), 500, 120, textColor);
  }else{
    SDL_Color textColor1;
    textColor1.r = Gamedata::getInstance().getXmlInt("hud/border/Color/red");
    textColor1.g = Gamedata::getInstance().getXmlInt("hud/border/Color/blue");
    textColor1.b = Gamedata::getInstance().getXmlInt("hud/border/Color/green");
    textColor1.a = Gamedata::getInstance().getXmlInt("hud/border/Color/alpha");
  
    IOmod::getInstance().writeText(" All 7 Dragon Balls Collected", 500, 120, textColor1);
    IOmod::getInstance().writeText(" Summon Shendron", 500, 150, textColor1);
  }

  strategies[currentStrategy]->draw();
  if ( collision ) {
    IOmod::getInstance().writeText("Oops: Collision", 500, 60, textColor);
  }

  player->draw();
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

  auto it = dragonballs.begin();
  while ( it != dragonballs.end() ) {
    if ( strategies[currentStrategy]->execute(*player, **it) ) {
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
  checkForCollisions();
  for(auto sprite : dragonballs){
  	sprite->update(ticks);
  }
  for(auto sprite : sprites){
    sprite->update(ticks);
  }
  sky.update();
  city.update();
  land.update();
  player->update(ticks);
  viewport.update(); // always update viewport last
}

void Engine::drawHud() const {
  if (showHud || clock.getSeconds() <= 3){
  	Hud::getInstance().draw(renderer);
  }
 }

void Engine::play() {
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
        if ( keystate[SDL_SCANCODE_E] ) {
          for(unsigned int i = 0; i< sprites.size();i++){
            sprites[i]->explode();
          }
          for(unsigned int i = 0; i< dragonballs.size();i++){
            dragonballs[i]->explode();
          }
          player->explode();
        }
        if ( keystate[SDL_SCANCODE_SPACE] ) {
          static_cast<ShootingSprite*>(player)->shoot();
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
}