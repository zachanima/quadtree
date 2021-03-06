#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <cmath>

#include "lwcppgl/display.hpp"

#include "vertex.hpp"
#include "simplex.hpp"

#define CHUNK_SIZE (16)
#define VERTICES (CHUNK_SIZE * CHUNK_SIZE * 4)
#define INDICES (VERTICES)

enum {
  FRONT,
  BACK,
  TOP,
  BOTTOM,
  LEFT,
  RIGHT
};

class Quadtree {
  public:
    static GLdouble distance;

    Quadtree(GLdouble, GLdouble, GLdouble, GLdouble, size_t, unsigned int);
    ~Quadtree();
    void update(GLdouble, GLdouble, GLdouble);
    void render();

  private:
    Vertex *vertices;
    GLdouble *box;
    Quadtree *children[4];
    size_t level;
    unsigned int face;
    GLuint vertexbuffer;
    GLuint indexbuffer;
    void divide();
    GLdouble distance2(GLdouble, GLdouble, GLdouble);
};

#endif // QUADTREE_HPP
