#include <string>
#include <SDL2/SDL.h>
// #include <SDL.h>

const double PI = 3.1415926535897;
const double DEG2RAD = PI/180;

class Draw{
public:
  Draw(SDL_Renderer*, SDL_Window*, int, int, std::string);
  double deg2rad(double x);
  void drawCircle(SDL_Point center, int radius, SDL_Color color);
  void drawWheel(SDL_Point center, int radius1, int radius2);
  void drawBars(SDL_Color color);
  void drawPedals();
  void drawHandle();
  void drawSeat();
  void drawCycle(SDL_Color color);
  void genFrame();
  const std::string getTitle() const;
  int getWidth() const;
  int getHeight() const;
private:
  SDL_Renderer* renderer;
  SDL_Window*  window;
  const int WIDTH;
  const int HEIGHT;
  const std::string TITLE;
};

  std::ostream& operator <<(std::ostream& os, const Draw& d); 