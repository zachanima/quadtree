#ifndef GAME_HPP
#define GAME_HPP

#include "lwcppgl/display.hpp"

class Game {
  public:
    static void initialize();
    static void update();
    static void render();

  private:
    static size_t ticks;
};

#endif // GAME_HPP
