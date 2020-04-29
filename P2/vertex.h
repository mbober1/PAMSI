#pragma once

class Vertex {
public:
  int distance;
  int id;
  int preVertex = -1;

  Vertex(int id, int distance) {
    this->id = id;
    this->distance = distance;
  }

  ~Vertex() {
    // printf("~Vertex %d\n", id);
  }
};
