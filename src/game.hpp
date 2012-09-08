#ifndef GAME_HPP
#define GAME_HPP

#include <cmath>

#include "lwcppgl/display.hpp"
#include "lwcppgl/keyboard.hpp"

#include "camera.hpp"
#include "quadtree.hpp"

class Game {
  public:
    static void initialize();
    static void update();
    static void render();

  private:
    static size_t ticks;
    static Camera camera;
    static Quadtree *quadtree[6];
};

#endif // GAME_HPP
