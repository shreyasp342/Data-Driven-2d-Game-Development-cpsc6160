#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include <vector>
#include "sprite.h"
#include "multisprite.h"
#include "twowaysprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"

Engine::~Engine() { 
  for(auto sprite : sprites){
  	delete sprite;
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
  viewport( Viewport::getInstance() ),
  currentSprite(0),
  makeVideo( false )
{
  
  sprites.push_back(new Sprite("dragonBall")),
  sprites.push_back(new MultiSprite("valor")),
  sprites.push_back(new twowaySprite("cycle")),
  sprites.push_back(new twowaySprite("sanji")),
  sprites.push_back(new twowaySprite("zoro")),

  Viewport::getInstance().setObjectToTrack(sprites.at(currentSprite));
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  sky.draw();
  city.draw();
  land.draw();
  for(auto sprite : sprites){
  	sprite->draw();
  }

  viewport.draw();
  SDL_Color textColor;
  textColor.r = Gamedata::getInstance().getXmlInt("font/red");
  textColor.g = Gamedata::getInstance().getXmlInt("font/green");
  textColor.b = Gamedata::getInstance().getXmlInt("font/blue");
  textColor.a = Gamedata::getInstance().getXmlInt("font/alpha");
  
  std::stringstream fps;
  fps << "Frame Rate: " << clock.getFps() << " fps" << std::endl;
  io.writeText(fps.str(), 30, 60, textColor);
  
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for(auto sprite : sprites){
  	sprite->update(ticks);
  }
  sky.update();
  city.update();
  land.update();
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % sprites.size();
  Viewport::getInstance().setObjectToTrack(sprites.at(currentSprite));
  
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
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
