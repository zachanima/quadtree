#include "game.hpp"

size_t Game::ticks = 0;
Camera Game::camera;



void Game::initialize() {
  camera.x = 0.;
  camera.y = 0.;
  camera.z = 8.;
}

void Game::update() {
  const size_t delta = SDL_GetTicks() - ticks;
  ticks = SDL_GetTicks();

  if (Keyboard::isKeyDown(KEY_W)) {
    camera.z -= 0.000005 * (GLdouble)ticks;
  }
  if (Keyboard::isKeyDown(KEY_S)) {
    camera.z += 0.000005 * (GLdouble)ticks;
  }
}

void Game::render() {
  static GLdouble rotation = 0.;
  rotation += 0.1;
  Display::perspective();
  glTranslated(-camera.x, -camera.y, -camera.z);
  glRotated(rotation, 0., 1., 0.);
  glColor3d(1., 1., 1.);
  glBegin(GL_TRIANGLES);
  glVertex3d(-1., -1., 0.);
  glVertex3d( 1., -1., 0.);
  glVertex3d( 0.,  1., 0.);
  glEnd();
}
