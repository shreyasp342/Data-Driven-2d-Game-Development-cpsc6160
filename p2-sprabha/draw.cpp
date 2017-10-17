#include <iostream>
#include <string>
#include "draw.h"
#include "frameGenerator.h"

Draw::Draw(SDL_Renderer* rend, SDL_Window*  win, int w, int h, std::string t) :
renderer(rend), window(win), WIDTH(w),HEIGHT(h),TITLE (t){
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
  SDL_SetWindowTitle(window, TITLE.c_str());
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
  SDL_RenderClear(renderer);
}

double Draw::deg2rad(double x){
  return x *DEG2RAD;
}

void Draw::drawCircle(SDL_Point center, int radius, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}

void Draw::drawWheel(SDL_Point center, int radius1, int radius2){
  SDL_Color black = {0,0,0,255};
  drawCircle(center, radius2, black);
  SDL_Color white = {255,255,255,255};
  drawCircle(center, radius1, white);
  SDL_Color gray = {105, 105, 105, 255};
  SDL_SetRenderDrawColor(renderer, gray.r, gray.g, gray.b, gray.a);
  for(int theta = 0; theta<360; theta+=20){
    double x = center.x+radius1*cos(deg2rad(theta));
    double y = center.y+radius1*sin(deg2rad(theta));
    SDL_RenderDrawLine(renderer, x, y, center.x, center.y);
  }
}

void Draw::drawBars(SDL_Color color){
  SDL_Rect r = {198, 143, 210, 15};
  SDL_Color black = {0, 0, 0, 255};
  SDL_Color gray = {105, 105, 105, 255};
  SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);

  // Main Bar
  SDL_RenderDrawRect(renderer, &r);
  //Main bar to flywheel
  SDL_RenderDrawLine(renderer, 408, 140, 368, 325);
  SDL_RenderDrawLine(renderer, 388, 140, 348, 325);
  //Main Bar to Rear Wheel
  SDL_RenderDrawLine(renderer, 408, 150, 508, 293);
  SDL_RenderDrawLine(renderer, 392, 150, 492, 293);
  //Rear Wheel to Flywheel
  SDL_RenderDrawLine(renderer, 348, 315, 490, 290);
  SDL_RenderDrawLine(renderer, 368, 325, 510, 300);
  //Flywheel to Handle
  SDL_RenderDrawLine(renderer, 187, 173, 347, 325);
  SDL_RenderDrawLine(renderer, 202, 173, 362, 325);
  //Front Wheel to Handle
  SDL_RenderDrawLine(renderer, 145, 300, 205, 120);
  SDL_RenderDrawLine(renderer, 157, 300, 217, 120);


  SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a);
  //Main Bar
  SDL_RenderFillRect( renderer, &r );
  // Mainbar to Flywheel
  for(int i = 349; i < 368; i++){
      SDL_RenderDrawLine(renderer, i+40, 140, i, 325);
  }
  //Main bar to rear wheel
  for(int i = 493; i < 508; i++){
      SDL_RenderDrawLine(renderer, i-100, 150, i, 293);
  }
  //Rear wheel to flywheel
  for(int i = 291; i <= 300; i++){
    for(int j = 349; j <= 368;j++){
      SDL_RenderDrawLine(renderer, j, i+25, j+142, i);
      SDL_RenderDrawLine(renderer, j, i+25, j+142, i);
    }
  }
  //Flywheel to Handle
  for(int i = 188; i < 202; i++){
      SDL_RenderDrawLine(renderer, i, 173, i+160, 325);
  }
  //Front wheel to Handle
  for(int i = 146; i < 157; i++){
      SDL_RenderDrawLine(renderer, i, 300, i+60, 120);
  }

  int radius = 18;
  SDL_Point center = {498, 295};
  drawCircle(center, radius, gray);
  center = {358, 320};
  drawCircle(center, radius, black);
  radius = 10;
  center = {150, 300};
  drawCircle(center, radius, black);
  radius = 12;
  center = {498, 295};
  drawCircle(center, radius, black);

  // SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

}

void Draw::drawPedals(){
  SDL_Color gray = {105, 105, 105, 255};
  SDL_SetRenderDrawColor(renderer, gray.r, gray.g, gray.b, gray.a);
  for(int i = 340; i <= 345; i++){
      SDL_RenderDrawLine(renderer, i, 280, i+30, 360);
  }
  SDL_Color black = {0, 0, 0, 255};
  SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
  SDL_Rect pedal1 = {327, 280, 33, 5};
  SDL_RenderFillRect(renderer, &pedal1);
  SDL_Rect pedal2 = {357, 360, 33, 5};
  SDL_RenderFillRect(renderer, &pedal2);
}


void Draw::drawSeat(){
  SDL_Color black = {0, 0, 0, 255};
  SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
  for(int i = 388; i <=398 ; i++){
    SDL_RenderDrawLine(renderer, i, 140, i+5, 130);
  }
  for(int i = 407; i >=398 ; i--){
    SDL_RenderDrawLine(renderer, i, 140, i-5, 130);
  }
  SDL_Color gray = {105, 105, 105, 255};
  SDL_SetRenderDrawColor(renderer, gray.r, gray.g, gray.b, gray.a);
  SDL_Rect seatBar = {393, 110, 10, 20};
  SDL_RenderFillRect(renderer, &seatBar);
  SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
  for(int i = 345; i <=430 ; i++){
    SDL_RenderDrawLine(renderer, i, 90, 398, 115);
  }
  SDL_Rect seat = {345, 85, 86, 5};
  SDL_RenderFillRect(renderer, &seat);
}

void Draw::drawHandle(){
  SDL_Color gray = {105, 105, 105, 255};
  SDL_SetRenderDrawColor(renderer, gray.r, gray.g, gray.b, gray.a);
  SDL_Rect bearing = {202, 120, 16, 5};
  SDL_RenderFillRect(renderer, &bearing);
  SDL_Color black = {0,0,0,255};
  SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
  SDL_Rect handleBar = {205, 85, 10, 35};
  SDL_RenderFillRect(renderer, &handleBar);
  handleBar = {203, 75, 50, 10};
  SDL_RenderFillRect(renderer, &handleBar);
}

void Draw::drawCycle(SDL_Color color) {
  int radius1 = 85;
  int radius2 = 100;
  SDL_Point wheelCenter = {150, 300};
  drawWheel(wheelCenter, radius1, radius2);
  wheelCenter = {500, 300};
  drawWheel(wheelCenter, radius1, radius2);
  // SDL_Color color = {0,0,255,255};
  drawPedals();
  drawBars(color);
  drawHandle();
  drawSeat();
  SDL_RenderPresent(renderer);
}

void Draw::genFrame(){
  FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, 
    "sprabha");
  frameGen.makeFrame();
}

const std::string Draw::getTitle() const {return TITLE;}

int Draw::getWidth() const {return WIDTH;}

int Draw::getHeight() const {return HEIGHT;}

std::ostream& operator<<(std::ostream& os, const Draw& d){
  return os <<"Rendering " << d.getTitle()<< " on a "<< d.getWidth() << "x" << d.getHeight() << " window \nHAPPY RIDING!\n";
} 

