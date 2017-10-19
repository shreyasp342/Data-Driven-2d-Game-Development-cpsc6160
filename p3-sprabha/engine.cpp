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
  // delete star;
  // delete spinningStar;
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
  background("background", Gamedata::getInstance().getXmlInt("background/factor") ),
  // clouds("clouds", Gamedata::getInstance().getXmlInt("clouds/factor") ),
  mountain("mountain", Gamedata::getInstance().getXmlInt("mountain/factor") ),
  // trees1("trees1", Gamedata::getInstance().getXmlInt("trees1/factor") ),
  // trees2("trees2", Gamedata::getInstance().getXmlInt("trees2/factor") ),
  trees3("trees3", Gamedata::getInstance().getXmlInt("trees3/factor") ),
  viewport( Viewport::getInstance() ),
  // star(new Sprite("YellowStar")),
  // spinningStar(new MultiSprite("SpinningStar")),
  currentSprite(0),
  makeVideo( false )
{
  
  sprites.push_back(new twowaySprite("zoro")),
  sprites.push_back(new Sprite("YellowStar")),
  sprites.push_back(new MultiSprite("SpinningStar")),

  Viewport::getInstance().setObjectToTrack(sprites.at(currentSprite));
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  background.draw();
  // clouds.draw();
  mountain.draw();
  // trees1.draw();
  // trees2.draw();
  trees3.draw();

  // star->draw();
  // spinningStar->draw();
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
  // io.writeText("Tracking: "+objectToTrack->getName(), 30, 30, textColor);
  io.writeText(fps.str(), 30, 60, textColor);
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  // star->update(ticks);
  // spinningStar->update(ticks);

  for(auto sprite : sprites){
  	sprite->update(ticks);
  }

  background.update();
  // clouds.update();
  mountain.update();
  // trees1.update();
  // trees2.update();
  trees3.update();
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % sprites.size();
  // if ( currentSprite ) {
  //   Viewport::getInstance().setObjectToTrack(sprites.at(currentSprite));
  // }
  // else {
  //   Viewport::getInstance().setObjectToTrack(sprites.at(currentSprite));
  // }
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
