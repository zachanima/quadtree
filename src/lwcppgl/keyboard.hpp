#ifndef LWCPPGL_KEYBOARD_HPP
#define LWCPPGL_KEYBOARD_HPP

#include <SDL/SDL.h>

enum {
  KEY_ESCAPE,
  KEY_A,
  KEY_D,
  KEY_LEFT,
  KEY_RIGHT,
  KEYS
};

class Keyboard {
  public:
    static void update();
    static bool isKeyDown(int code);

    static bool key[KEYS];
};

#endif // LWCPPGL_KEYBOARD_HPP
