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
    void update(GLdouble, GLdouble, GLdouble);
    void render();

  private:
    Vertex *vertices;
    GLdouble *box;
    Quadtree *children[4];
    GLuint vertexbuffer;
    GLuint indexbuffer;
    /*
    GLuint list;
    */
    void divide();
    GLdouble distance2(GLdouble, GLdouble, GLdouble);
};

#endif // QUADTREE_HPP
