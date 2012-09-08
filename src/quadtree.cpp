#include "quadtree.hpp"



Quadtree::Quadtree(GLdouble a1, GLdouble b1, GLdouble a2, GLdouble b2) {
  const GLdouble L = (a2 - a1) / CHUNK_SIZE;
  box = new GLdouble[4];
  box[0] = a1;
  box[1] = b1;
  box[2] = a2;
  box[3] = b2;

  vertices = new Vertex[VERTICES];

  // Generate cube.
  size_t i = 0;
  for (size_t b = 0; b < CHUNK_SIZE; b++) {
    for (size_t a = 0; a < CHUNK_SIZE; a++) {
      vertices[i].position[0] = a1 + L * (a + 0);
      vertices[i].position[1] = b1 + L * (b + 0);
      vertices[i].position[2] = 1.;
      i++;

      vertices[i].position[0] = a1 + L * (a + 1);
      vertices[i].position[1] = b1 + L * (b + 0);
      vertices[i].position[2] = 1.;
      i++;

      vertices[i].position[0] = a1 + L * (a + 1);
      vertices[i].position[1] = b1 + L * (b + 1);
      vertices[i].position[2] = 1.;
      i++;

      vertices[i].position[0] = a1 + L * (a + 0);
      vertices[i].position[1] = b1 + L * (b + 1);
      vertices[i].position[2] = 1.;
      i++;
    }
  }
}



Quadtree::~Quadtree() {
  delete box;
  delete vertices;
}



void Quadtree::render() {
  glBegin(GL_QUADS);
  for (size_t i = 0; i < INDICES; i++) {
    glVertex3d(
      vertices[i].position[0],
      vertices[i].position[1],
      vertices[i].position[2]
    );
  }
  glEnd();
}
