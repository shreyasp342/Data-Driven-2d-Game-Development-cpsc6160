#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include <vector>
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "smartSprite.h"
#include "shootingSprite.h"

// class SubjectSprite;
// class ShootingSprite;
class CollisionStrategy;

class Engine {
public:
  Engine ();
  ~Engine ();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  void play();
  void switchSprite();

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World sky;
  World city;
  World land;

  std::vector <SmartSprite*> dragonballs;
  std::vector <Drawable*> sprites;
  // SubjectSprite* player;
  ShootingSprite* player;
  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;
  bool collision;

  Viewport& viewport;
  int currentSprite;

  bool makeVideo;
  bool showHud;
  bool shoot;

  void draw() const;
  void drawHud() const;
  void update(Uint32);
  void printScales() const;
  void checkForCollisions();
};
