#ifndef GAME_HPP
#define GAME_HPP

#include <cmath>

#include "lwcppgl/display.hpp"
#include "lwcppgl/keyboard.hpp"

#include "camera.hpp"

class Game {
  public:
    static void initialize();
    static void update();
    static void render();

  private:
    static size_t ticks;
    static Camera camera;
};

#endif // GAME_HPP
