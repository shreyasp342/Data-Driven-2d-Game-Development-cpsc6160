#include <iostream>
#include <string>
#include <sstream>
#include <SDL.h>
#include "hud.h"


Hud& Hud::getInstance() {
  static Hud instance;
  return instance;
}
Hud::Hud() :
  io( IOmod::getInstance() ),
  gdata( Gamedata::getInstance() ) {
}

Hud::~Hud(){}

void Hud::win(SDL_Renderer * const renderer){
  SDL_Rect box;
  box.x = 40;
  box.y = 60;
  box.w = 430;
  box.h = 180;
  int borderThickness = gdata.getXmlInt("hud/border/thickness");
  SDL_Color borderColor;
  borderColor.r = gdata.getXmlInt("hud/border/Color/red");
  borderColor.g = gdata.getXmlInt("hud/border/Color/green");
  borderColor.b = gdata.getXmlInt("hud/border/Color/blue");
  borderColor.a = gdata.getXmlInt("hud/border/Color/alpha");
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  for(int i =1; i<=borderThickness; i++){
    SDL_RenderDrawRect(renderer, &box);
    box.x += 1;
    box.y += 1;
    box.w -= 2;
    box.h -= 2;
  }
  SDL_Color background;
  background.r = gdata.getXmlInt("hud/hudColor/red");
  background.g = gdata.getXmlInt("hud/hudColor/green");
  background.b = gdata.getXmlInt("hud/hudColor/blue");
  background.a = gdata.getXmlInt("hud/hudColor/alpha");
  SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
  SDL_RenderFillRect(renderer, &box);
  
  SDL_Color textColor;
  textColor.r = gdata.getXmlInt("hud/textColor/red");
  textColor.g = gdata.getXmlInt("hud/textColor/green");
  textColor.b = gdata.getXmlInt("hud/textColor/blue");
  textColor.a = gdata.getXmlInt("hud/textColor/alpha");
  
  io.writeText("   Your wish has been granted!!     ", box.x+=15, box.y+=30, textColor);
  io.writeText("          Press 'R' to Restart       ", box.x, box.y+=30, textColor);
  io.writeText("                        or                 ", box.x, box.y+=30, textColor);
  io.writeText("Press 'Esc' or 'Q' to Quit the Game", box.x, box.y+=30, textColor); 

}

void Hud::gameover(SDL_Renderer * const renderer){
  SDL_Rect box;
  box.x = 280;
  box.y = 200;
  box.w = 430;
  box.h = 180;
  int borderThickness = gdata.getXmlInt("hud/border/thickness");
  SDL_Color borderColor;
  borderColor.r = gdata.getXmlInt("hud/border/Color/red");
  borderColor.g = gdata.getXmlInt("hud/border/Color/green");
  borderColor.b = gdata.getXmlInt("hud/border/Color/blue");
  borderColor.a = gdata.getXmlInt("hud/border/Color/alpha");
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  for(int i =1; i<=borderThickness; i++){
    SDL_RenderDrawRect(renderer, &box);
    box.x += 1;
    box.y += 1;
    box.w -= 2;
    box.h -= 2;
  }
  SDL_Color background;
  background.r = gdata.getXmlInt("hud/hudColor/red");
  background.g = gdata.getXmlInt("hud/hudColor/green");
  background.b = gdata.getXmlInt("hud/hudColor/blue");
  background.a = gdata.getXmlInt("hud/hudColor/alpha");
  SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
  SDL_RenderFillRect(renderer, &box);
  
  SDL_Color textColor;
  textColor.r = gdata.getXmlInt("hud/textColor/red");
  textColor.g = gdata.getXmlInt("hud/textColor/green");
  textColor.b = gdata.getXmlInt("hud/textColor/blue");
  textColor.a = gdata.getXmlInt("hud/textColor/alpha");
  
  io.writeText("                Goku is Dead!!          ", box.x+=15, box.y+=30, textColor);
  io.writeText("              Press 'R' to Restart       ", box.x, box.y+=30, textColor);
  io.writeText("                                or                 ", box.x, box.y+=30, textColor);
  io.writeText("Press 'Esc' or 'Q' to Quit the Game", box.x, box.y+=30, textColor); 
}

void Hud::summon(SDL_Renderer * const renderer){
  SDL_Rect box;
  box.x = 280;
  box.y = 200;
  box.w = 460;
  box.h = 100;
  int borderThickness = gdata.getXmlInt("hud/border/thickness");
  SDL_Color borderColor;
  borderColor.r = gdata.getXmlInt("hud/border/Color/red");
  borderColor.g = gdata.getXmlInt("hud/border/Color/green");
  borderColor.b = gdata.getXmlInt("hud/border/Color/blue");
  borderColor.a = gdata.getXmlInt("hud/border/Color/alpha");
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  for(int i =1; i<=borderThickness; i++){
    SDL_RenderDrawRect(renderer, &box);
    box.x += 1;
    box.y += 1;
    box.w -= 2;
    box.h -= 2;
  }
  SDL_Color background;
  background.r = gdata.getXmlInt("hud/hudColor/red");
  background.g = gdata.getXmlInt("hud/hudColor/green");
  background.b = gdata.getXmlInt("hud/hudColor/blue");
  background.a = gdata.getXmlInt("hud/hudColor/alpha");
  SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
  SDL_RenderFillRect(renderer, &box);
  
  SDL_Color textColor;
  textColor.r = gdata.getXmlInt("hud/textColor/red");
  textColor.g = gdata.getXmlInt("hud/textColor/green");
  textColor.b = gdata.getXmlInt("hud/textColor/blue");
  textColor.a = gdata.getXmlInt("hud/textColor/alpha");
  
  io.writeText("   All 7 Dragon Balls collected   ", 300, 220, textColor);
  io.writeText("Press 'Enter' key to Summon Shenron", 300, 250, textColor);  
}

void Hud::healthBar(SDL_Renderer * const renderer, unsigned int x, unsigned int y, unsigned int w, unsigned int h, int value){
  SDL_Rect box;
  box.x = x;
  box.y = y;
  box.w = h;
  box.h = w;
  int borderThickness = 3;
  SDL_Color borderColor;
  borderColor.r = 0;
  borderColor.g = 0;
  borderColor.b = 0;
  borderColor.a = 255;
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  for(int i =1; i<=borderThickness; i++){
    SDL_RenderDrawRect(renderer, &box);
    box.x += 1;
    box.y += 1;
    box.w -= 2;
    box.h -= 2;
  }
  if(value<0) value = 0;
  box.h = value;
  SDL_Color background;
  background.r = gdata.getXmlInt("hud/hudColor/red");
  background.g = gdata.getXmlInt("hud/hudColor/green");
  background.b = gdata.getXmlInt("hud/hudColor/blue");
  background.a = 255;
  SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
  SDL_RenderFillRect(renderer, &box);
}

void Hud::draw(SDL_Renderer * const renderer){
  SDL_Rect box;
  box.x = gdata.getXmlInt("hud/posX");
  box.y = gdata.getXmlInt("hud/posY");
  box.w = gdata.getXmlInt("hud/width");
  box.h = gdata.getXmlInt("hud/height");
  int borderThickness = gdata.getXmlInt("hud/border/thickness");
  SDL_Color borderColor;
  borderColor.r = gdata.getXmlInt("hud/border/Color/red");
  borderColor.g = gdata.getXmlInt("hud/border/Color/green");
  borderColor.b = gdata.getXmlInt("hud/border/Color/blue");
  borderColor.a = gdata.getXmlInt("hud/border/Color/alpha");
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  for(int i =1; i<=borderThickness; i++){
    SDL_RenderDrawRect(renderer, &box);
    box.x += 1;
    box.y += 1;
    box.w -= 2;
    box.h -= 2;
  }
  SDL_Color background;
  background.r = gdata.getXmlInt("hud/hudColor/red");
  background.g = gdata.getXmlInt("hud/hudColor/green");
  background.b = gdata.getXmlInt("hud/hudColor/blue");
  background.a = gdata.getXmlInt("hud/hudColor/alpha");
  SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
  SDL_RenderFillRect(renderer, &box);
  SDL_Color textColor;
  textColor.r = gdata.getXmlInt("hud/textColor/red");
  textColor.g = gdata.getXmlInt("hud/textColor/green");
  textColor.b = gdata.getXmlInt("hud/textColor/blue");
  textColor.a = gdata.getXmlInt("hud/textColor/alpha");
  io.writeText(gdata.getXmlStr("hud/text").c_str(), box.x+=15, box.y+=15, textColor);
  io.writeText(gdata.getXmlStr("hud/up").c_str(), box.x, box.y+=30, textColor);
  io.writeText(gdata.getXmlStr("hud/left").c_str(), box.x, box.y+=30, textColor);
  io.writeText(gdata.getXmlStr("hud/right").c_str(), box.x, box.y+=30, textColor);
  io.writeText(gdata.getXmlStr("hud/down").c_str(), box.x, box.y+=30, textColor);
  io.writeText(gdata.getXmlStr("hud/hudshow").c_str(), box.x, box.y+=30, textColor);
  io.writeText(gdata.getXmlStr("hud/restart").c_str(), box.x, box.y+=30, textColor);
  io.writeText(gdata.getXmlStr("hud/godmode").c_str(), box.x, box.y+=30, textColor);
}

