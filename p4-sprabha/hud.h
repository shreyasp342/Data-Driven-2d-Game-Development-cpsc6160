#ifndef HUD_H_
#define HUD_H_

#include <string>
// #include <SDL2/SDL.h>
#include "ioMod.h"
#include "gamedata.h"
#include <SDL.h>

class Hud{
public:
  Hud();
  static Hud& getInstance();
  void draw(SDL_Renderer * const);
private:
	const IOmod& io;
  const Gamedata& gdata;

};

#endif