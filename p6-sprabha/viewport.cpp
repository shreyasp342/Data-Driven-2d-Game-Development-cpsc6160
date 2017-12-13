#include <sstream>
#include "viewport.h"
#include "ioMod.h"

Viewport& Viewport::getInstance() {
  static Viewport viewport;
  return viewport;
}

Viewport::Viewport() : 
  gdata(Gamedata::getInstance()),
  position(0, 0),
  worldWidth(gdata.getXmlInt("world/width")),
  worldHeight(gdata.getXmlInt("world/height")),
  viewWidth(gdata.getXmlInt("view/width")), 
  viewHeight(gdata.getXmlInt("view/height")),
  objWidth(0), objHeight(0),
  objectToTrack(NULL) 
{}

void Viewport::setObjectToTrack(const Drawable *obj) { 
  objectToTrack = obj; 
  objWidth = objectToTrack->getScaledWidth() + 550;
  objHeight = objectToTrack->getScaledHeight();
}

void Viewport::draw() const {
  SDL_Color textColor;  
  textColor.r = Gamedata::getInstance().getXmlInt("namefont/red");
  textColor.g = Gamedata::getInstance().getXmlInt("namefont/green");
  textColor.b = Gamedata::getInstance().getXmlInt("namefont/blue");
  textColor.a = Gamedata::getInstance().getXmlInt("namefont/alpha");
  std::stringstream name;
  name << "Shreyas Prabhakar";
  IOmod::getInstance().writeText(name.str(), 30, 530, textColor);
}

void Viewport::update() {
  const float x = objectToTrack->getX();
  const float y = objectToTrack->getY();

  position[0] = (x + objWidth/2) - viewWidth/2;
  position[1] = (y + objHeight/2) - viewHeight/2;
  if (position[0] < 0) position[0] = 0;
  if (position[1] < 0) position[1] = 0;
  if (position[0] > (worldWidth - viewWidth)) {
    position[0] = worldWidth-viewWidth-250;
  }
  if (position[1] > (worldHeight - viewHeight)) {
    position[1] = worldHeight-viewHeight;
  }
}
