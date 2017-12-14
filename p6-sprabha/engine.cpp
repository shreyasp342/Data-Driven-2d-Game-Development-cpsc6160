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
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
#include "player.h"
#include "hud.h"
#include "collisionStrategy.h"
#include "shootingSprite.h"
#include "enemyshooting.h"

class SpriteLess {
public:
  bool operator()(const twowaySprite* lhs, const twowaySprite* rhs) const {
    return lhs->getScale() < rhs->getScale();
  }
};

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

   std::vector<twowaySprite*>::iterator it = painters.begin();
  while ( it != painters.end() ) {
    delete *it;
    ++it;
  }

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
  invoke (false),
  godmode(false),
  sound(),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  counter(0),
  painters()
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

  for (unsigned int i = 0; i < 1; ++i) {
    std::string name = "blah";
    int px = player->getLimiter() + 200;
    int py = rand()%worldHeight;
    int vx = Gamedata::getInstance().getXmlInt(name+"/speedX");
    if(vx !=0) vx = (vx * (rand()%2?1:-1)) + (rand()%50 * (rand()%2?1:-1));
    int vy = Gamedata::getInstance().getXmlInt(name+"/speedY");
    if(vy !=0) vy = (vy * (rand()%2?1:-1)) + (rand()%50 * (rand()%2?1:-1));
    enemies.push_back(new EnemyShooting(name.c_str(), px, py, vx, vy));
  }

  for (unsigned int i = 0; i < 5; ++i) {
    std::string name = "valor";
    int px = rand()%worldWidth * (rand()%2?1:-1);
    int py = Gamedata::getInstance().getXmlInt(name+"/startLoc/y");
    int vx = Gamedata::getInstance().getXmlInt(name+"/speedX");
    if(vx !=0) vx = (vx * (rand()%2?1:-1)) + (rand()%50 * (rand()%2?1:-1));
    int vy = Gamedata::getInstance().getXmlInt(name+"/speedY");
    if(vy !=0) vy = (vy * (rand()%2?1:-1)) + (rand()%50 * (rand()%2?1:-1));
    sprites.push_back(new MultiSprite(name.c_str(), px, py, vx, vy));
  }
  
  strategies.push_back( new PerPixelCollisionStrategy );
  strategies.push_back( new RectangularCollisionStrategy );
  strategies.push_back( new MidPointCollisionStrategy );

  unsigned int n = Gamedata::getInstance().getXmlInt("numberOfStars");
  for ( unsigned int i = 0; i < n; ++i ) {
    twowaySprite* s = new twowaySprite("crow");
    float scale = Gamedata::getInstance().getRandFloat(0.25,0.65);
    s->setScale(scale);
    painters.push_back(s);
  }
  std::vector<twowaySprite*>::iterator ptr = painters.begin();
  ++ptr;
  sort(ptr, painters.end(), SpriteLess());

  unsigned int i = 0;
  for (auto sprite : painters) {
    unsigned int offset = 50;
    std::string name = sprite->getName();
    int px = rand()%worldWidth + (rand()%offset * (rand()%2?1:-1));
    int py = Gamedata::getInstance().getXmlInt(name+"/startLoc/y") + (rand()%offset * (rand()%2?1:-1));

    if(i < painters.size()/3) offset = 25;
    else if(i < (2*painters.size())/3) offset = 375;
    else offset = 700;

    int vx = Gamedata::getInstance().getXmlInt(name+"/speedX");
    if(vx !=0) vx = (vx * (rand()%2?1:-1)) + (rand()%offset * (rand()%2?1:-1));
    int vy = Gamedata::getInstance().getXmlInt(name+"/speedY");
    if(vy !=0) vy = (vy * (rand()%2?1:-1)) + (rand()%offset * (rand()%2?1:-1));
    sprite->setVelocity(Vector2f(vx,vy));
    sprite->setPosition(Vector2f(px,py));
  }

  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  sky.draw();
  if (invoke){
    sky2.draw();
  }
  city.draw();
  for(auto sprite : dragonballs){
    if ( !(sprite->exploded()) ) sprite->draw();
  }
  if (invoke){
    shenron->setScale(0.45);
    shenron->draw();
    Hud::getInstance().win(renderer);
    // clock.pause();
  }
  else{
    for(auto* s : painters) s->draw();
    for(auto sprite : sprites){
      sprite->draw();
    }  
    for(auto ball : collected){ 
      int x = Gamedata::getInstance().getXmlInt(ball+"/collected/x");
      int y = Gamedata::getInstance().getXmlInt(ball+"/collected/y"); 
      IOmod::getInstance().writeImage(ball, x, y);
    }
  }
  if(godmode){
    SDL_Color textColor;
    textColor.r = Gamedata::getInstance().getXmlInt("hud/textColor/red");
    textColor.g = Gamedata::getInstance().getXmlInt("hud/textColor/green");
    textColor.b = Gamedata::getInstance().getXmlInt("hud/textColor/blue");
    textColor.a = Gamedata::getInstance().getXmlInt("hud/textColor/alpha");
    io.writeText("GodMode ON!", 430, 30, textColor);
    io.writeText("Goku is now Invincible", 400, 60, textColor);
  }

  land.draw();
  player->draw();

  for(auto sprite : enemies){
    if ( !(sprite->exploded()) ) sprite->draw();
  }

  if (dragonballs.size() <= 0){
    if(!invoke) Hud::getInstance().summon(renderer);
  }

  drawHud();

  if ( player->exploded() ) {
    Hud::getInstance().gameover(renderer);
  }
  viewport.draw();  
  SDL_RenderPresent(renderer);
}

void Engine::checkForCollisions() {
  collision = false;
  
  for(const auto enemy : enemies){
    for (const auto d : enemy->getBullets() ) {
      if ( strategies[currentStrategy]->execute(d, *player) ) {
        (player)->explode();
      }
    }
  }

  for ( const auto d : player->getBullets() ) {
    auto it = enemies.begin();
    while ( it != enemies.end() ) {
      if ( strategies[currentStrategy]->execute(d, **it) ) {
        (*it)->explode();
        it++;
      }
      else ++it;
    }
  }

  auto it = dragonballs.begin();
  while ( it != dragonballs.end() ) {
    if ( strategies[currentStrategy]->execute(*player, **it) ) {
      collected.push_back((*it)->getName());
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
  if(godmode){
    auto it = enemies.begin();
    while ( it != enemies.end() ) {
      delete (*it);
      it = enemies.erase(it);
    }
    counter = 8;
  }
  if (invoke){
    auto it = sprites.begin();
    while ( it != sprites.end() ) {
        delete (*it);
        it = sprites.erase(it);
    }
    auto it1 = painters.begin();
    while ( it1 != painters.end() ) {
        delete (*it1);
        it1 = painters.erase(it1);
    }
    sky2.update();
  }
  player->setObstruct(counter);
  if(enemies.size()<=0 && counter < 7){
    player->setObstruct(++counter);
    if(counter < 7){
      for (unsigned int i = 0; i < 1; ++i) {
        std::string name;
        switch(counter){
          case 0: name = "blah"; break;
          case 1: name = "piccolo"; break;
          case 2: name = "raditz"; break;
          case 3: name = "nappa"; break;
          case 4: name = "rakoom"; break;
          case 5: name = "ginyu"; break;
          case 6: default: name = "frieza"; break;
        }
        int px = player->getLimiter() + 200;
        int py = rand()%worldHeight;
        int vx = Gamedata::getInstance().getXmlInt(name+"/speedX");
        if(vx !=0) vx = (vx * (rand()%2?1:-1)) + (rand()%50 * (rand()%2?1:-1));
        int vy = Gamedata::getInstance().getXmlInt(name+"/speedY");
        if(vy !=0) vy = (vy * (rand()%2?1:-1)) + (rand()%50 * (rand()%2?1:-1));
        enemies.push_back(new EnemyShooting(name.c_str(), px, py, vx, vy));
      }
    }
    
  }

  if ( player->exploded() ) {
    clock.pause();
  }

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

  for(auto* s : painters) s->update(ticks);

  for(auto sprite : dragonballs){
  	sprite->update(ticks);
  }
  for(auto sprite : sprites){
    sprite->update(ticks);
  }
  player->update(ticks);
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
  int x = 10;
  int y = 10;
  int w = 506;
  int h = 20;
  int multiplier = w/100;
  Hud::getInstance().healthBar(renderer, x, y, w, h, player->getHealth()*multiplier);
  
  x = 1024;
  for(auto sprite : enemies){
    Hud::getInstance().healthBar(renderer, x-=30, y, w, h, sprite->getHealth()*multiplier);
  }
  if (showHud || clock.getSeconds() <= 3){
  	Hud::getInstance().draw(renderer);
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
        if ( keystate[SDL_SCANCODE_RETURN] && dragonballs.size() == 0) {
          invoke = true;
        }
        if ( keystate[SDL_SCANCODE_SPACE] ) {
            player->shoot();
        }
        if ( keystate[SDL_SCANCODE_G] ) {
          godmode = ~godmode;
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