#include "game.hpp"

size_t Game::ticks = 0;
Camera Game::camera;



void Game::initialize() {
  camera.z = 8.;
}

void Game::update() {
  const size_t delta = SDL_GetTicks() - ticks;
  ticks = SDL_GetTicks();

  if (Keyboard::isKeyDown(KEY_W)) {
    camera.x += sin(camera.b) * cos(camera.a) * 0.000002 * ticks;
    camera.y -= sin(camera.a)                 * 0.000002 * ticks;
    camera.z -= cos(camera.b) * cos(camera.a) * 0.000002 * ticks;
  }
  if (Keyboard::isKeyDown(KEY_S)) {
    camera.x -= sin(camera.b) * cos(camera.a) * 0.000002 * ticks;
    camera.y += sin(camera.a)                 * 0.000002 * ticks;
    camera.z += cos(camera.b) * cos(camera.a) * 0.000002 * ticks;
  }
  if (Keyboard::isKeyDown(KEY_UP))    { camera.a -= 0.0000002 * ticks; }
  if (Keyboard::isKeyDown(KEY_DOWN))  { camera.a += 0.0000002 * ticks; }
  if (Keyboard::isKeyDown(KEY_A))     { camera.b -= 0.0000002 * ticks; }
  if (Keyboard::isKeyDown(KEY_D))     { camera.b += 0.0000002 * ticks; }
}

void Game::render() {
  Display::perspective();

  glRotated(camera.a * 360. / 6.28, 1., 0., 0.);
  glRotated(camera.b * 360. / 6.28, 0., 1., 0.);
  glRotated(camera.c * 360. / 6.28, 0., 0., 1.);
  glTranslated(-camera.x, -camera.y, -camera.z);

  glColor3d(1., 1., 1.);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_TRIANGLES);
  glVertex3d(-1., -1., 0.);
  glVertex3d( 1., -1., 0.);
  glVertex3d( 0.,  1., 0.);
  glEnd();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
