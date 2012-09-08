#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <cmath>

#include "lwcppgl/display.hpp"

#include "vertex.hpp"

#define CHUNK_SIZE (16)
#define VERTICES (CHUNK_SIZE * CHUNK_SIZE * 4)
#define INDICES (VERTICES)

class Quadtree {
  public:
    Quadtree(GLdouble, GLdouble, GLdouble, GLdouble);
    ~Quadtree();
    void render();

  private:
    Vertex *vertices;
    GLdouble *box;
    /*
    GLuint vertexbuffer;
    GLuint indexbuffer;
    */
    GLuint list;
};

#endif // QUADTREE_HPP
