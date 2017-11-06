#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include <vector>
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"

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
  Viewport& viewport;

  std::vector <Drawable*> sprites;
  int currentSprite;

  bool makeVideo;
  bool showHud;

  void draw() const;
  void drawHud() const;
  void update(Uint32);
  void printScales() const;
  void checkForCollisions();
};
