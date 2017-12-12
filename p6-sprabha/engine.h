#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include <vector>
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "smartSprite.h"
#include "sound.h"
// #include "shootingSprite.h"

// class SubjectSprite;
class ShootingSprite;
class EnemyShooting;
class CollisionStrategy;

class Engine {
public:
  Engine ();
  ~Engine ();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  bool play();
  void switchSprite();

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World sky;
  World sky2;
  World city;
  World land;

  std::vector <SmartSprite*> dragonballs;
  std::vector <Drawable*> sprites;
  std::vector <std::string> collected;
  ShootingSprite* player;
  EnemyShooting* enemy;
  std::vector <EnemyShooting*> enemies;
  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;
  bool collision;

  Viewport& viewport;
  int currentSprite;

  bool makeVideo;
  bool showHud;
  SDLSound sound;
  // bool shoot;

  void draw() const;
  void drawHud() const;
  void update(Uint32);
  void printScales() const;
  void checkForCollisions();

  int worldWidth;
  int worldHeight;
  int counter;
  

};
