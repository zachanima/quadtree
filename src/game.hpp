#ifndef GAME_HPP
#define GAME_HPP

#include "lwcppgl/display.hpp"

class Game {
  public:
    static void initialize();
    static void update();
    static void render();
};

#endif // GAME_HPP
