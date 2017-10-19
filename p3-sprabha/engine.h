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
  World background;
  // World clouds;
  World mountain;
  // World trees1;
  // World trees2;
  World trees3;
  Viewport& viewport;

  std::vector <Drawable*> sprites;
  // Drawable* star;
  // Drawable* spinningStar;
  int currentSprite;

  bool makeVideo;

  void draw() const;
  void update(Uint32);
  void printScales() const;
  void checkForCollisions();
};
