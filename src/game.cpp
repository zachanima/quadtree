#include "game.hpp"

void Game::initialize() {
}

void Game::update() {
}

void Game::render() {
  static GLdouble rotation = 0.;
  rotation += 0.1;
  Display::perspective();
  glTranslated(0.0, 0.0, -8.0);
  glRotated(rotation, 0., 1., 0.);
  glColor3d(1., 1., 1.);
  glBegin(GL_TRIANGLES);
  glVertex3d(-1., -1., 0.);
  glVertex3d( 1., -1., 0.);
  glVertex3d( 0.,  1., 0.);
  glEnd();
}
