#include "quadtree.hpp"



Quadtree::Quadtree(GLdouble a1, GLdouble b1, GLdouble a2, GLdouble b2) {
  const GLdouble L = (a2 - a1) / CHUNK_SIZE;

  box = new GLdouble[4];
  box[0] = a1;
  box[1] = b1;
  box[2] = a2;
  box[3] = b2;

  children[0] = NULL;
  children[1] = NULL;
  children[2] = NULL;
  children[3] = NULL;

  // Generate cube.
  vertices = new Vertex[VERTICES];
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

  // Spherize cube.
  for (size_t i = 0; i < VERTICES; i++) {
    const GLdouble x2 = vertices[i].position[0] * vertices[i].position[0];
    const GLdouble y2 = vertices[i].position[1] * vertices[i].position[1];
    const GLdouble z2 = vertices[i].position[2] * vertices[i].position[2];
    vertices[i].position[0] *= sqrt(1 - y2 / 2 - z2 / 2 + y2 * z2 / 3);
    vertices[i].position[1] *= sqrt(1 - x2 / 2 - z2 / 2 + x2 * z2 / 3);
    vertices[i].position[2] *= sqrt(1 - x2 / 2 - y2 / 2 + x2 * y2 / 3);
  }

  // Compile display list.
  /*
  list = glGenLists(1);
  glNewList(list, GL_COMPILE);
  glBegin(GL_QUADS);
  for (size_t i = 0; i < VERTICES; i++) {
    glVertex3d(
      vertices[i].position[0],
      vertices[i].position[1],
      vertices[i].position[2]
    );
  }
  glEnd();
  glEndList();
  */

  // Compile vertex buffer object.
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, VERTICES * sizeof(Vertex), vertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

  GLuint *indices = new GLuint[INDICES];
  for (size_t i = 0; i < INDICES; i++) {
    indices[i] = i;
  }
  glGenBuffers(1, &indexbuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);
  delete indices;
}



Quadtree::~Quadtree() {
  delete box;
  delete vertices;
  /*
  glDeleteLists(list, 1);
  */
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteBuffers(1, &indexbuffer);
}



void Quadtree::update(GLdouble x, GLdouble y, GLdouble z) {
  bool split = distance2(x, y, z) < (box[2] - box[0]) * (box[2] - box[0]) * 4.;

  if (split) {
    if (children[0] == NULL) {
      divide();
    }
    children[0]->update(x, y, z);
    children[1]->update(x, y, z);
    children[2]->update(x, y, z);
    children[3]->update(x, y, z);
  } else if (children[0] != NULL) {
    delete children[0];
    delete children[1];
    delete children[2];
    delete children[3];
    children[0] = NULL;
    children[1] = NULL;
    children[2] = NULL;
    children[3] = NULL;
  }
}



void Quadtree::render() {
  if (children[0] == NULL) {
    /*
    glCallList(list);
    */
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
    glDrawElements(GL_QUADS, INDICES, GL_UNSIGNED_INT, (void *)0);
  } else {
    for (size_t i = 0; i < 4; i++) {
      children[i]->render();
    }
  }
}



void Quadtree::divide() {
  GLdouble ca = 0.5 * (box[0] + box[2]); // Center A.
  GLdouble cb = 0.5 * (box[1] + box[3]); // Center B.
  children[0] = new Quadtree(box[0], box[1], ca,     cb);
  children[1] = new Quadtree(ca,     box[1], box[2], cb);
  children[2] = new Quadtree(box[0], cb,     ca,     box[3]);
  children[3] = new Quadtree(ca,     cb,     box[2], box[3]);
}



GLdouble Quadtree::distance2(GLdouble x, GLdouble y, GLdouble z) {
  return
    pow(x - 0.5 * vertices[0].position[0] - 0.5 * vertices[VERTICES - 1].position[0], 2) +
    pow(y - 0.5 * vertices[0].position[1] - 0.5 * vertices[VERTICES - 1].position[1], 2) +
    pow(z - 0.5 * vertices[0].position[2] - 0.5 * vertices[VERTICES - 1].position[2], 2);
}
