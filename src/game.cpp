#include "game.hpp"

size_t Game::ticks = 0u;
Camera Game::camera;
Quadtree *Game::quadtree[6] = { NULL, NULL, NULL, NULL, NULL, NULL };



void Game::initialize() {
  quadtree[0] = new Quadtree(-1., -1., 1., 1.);
  camera.z = 8.;
}



void Game::update() {
  const size_t delta = SDL_GetTicks() - ticks;
  ticks = SDL_GetTicks();

  if (Keyboard::isKeyDown(KEY_W)) {
    quadtree[0]->update(camera.x, camera.y, camera.z);
    camera.x += sin(camera.b) * cos(camera.a) * 0.002 * delta;
    camera.y -= sin(camera.a)                 * 0.002 * delta;
    camera.z -= cos(camera.b) * cos(camera.a) * 0.002 * delta;
  }
  if (Keyboard::isKeyDown(KEY_S)) {
    quadtree[0]->update(camera.x, camera.y, camera.z);
    camera.x -= sin(camera.b) * cos(camera.a) * 0.002 * delta;
    camera.y += sin(camera.a)                 * 0.002 * delta;
    camera.z += cos(camera.b) * cos(camera.a) * 0.002 * delta;
  }
  if (Keyboard::isKeyDown(KEY_UP))    { camera.a += 0.0002 * delta; }
  if (Keyboard::isKeyDown(KEY_DOWN))  { camera.a -= 0.0002 * delta; }
  if (Keyboard::isKeyDown(KEY_A))     { camera.b -= 0.0002 * delta; }
  if (Keyboard::isKeyDown(KEY_D))     { camera.b += 0.0002 * delta; }
}



void Game::render() {
  Display::perspective();

  glRotated(camera.a * 360. / 6.28, 1., 0., 0.);
  glRotated(camera.b * 360. / 6.28, 0., 1., 0.);
  glRotated(camera.c * 360. / 6.28, 0., 0., 1.);
  glTranslated(-camera.x, -camera.y, -camera.z);

  glColor3d(1., 1., 1.);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  quadtree[0]->render();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
