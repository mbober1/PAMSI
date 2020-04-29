#pragma once
#include "utils.h"
#define LIST_GRAPH 0
#define MATRIX_GRAPH 1

class Graph {
public:
  int verticesCount, edgesCount, startVertex, type;

  Graph() {
    this->edgesCount = 0;
  }

  Graph(int size, int start) {
    this->verticesCount = size;
    this->edgesCount = 0;
    this->startVertex = start;
  }

  ~Graph() {
    // printf("~Graph\n");
  }

  // virtual Edge** operator[](std::size_t idx) = 0;
  virtual void addEdge(int src, int dest, int weight) = 0;
  virtual List<Edge*> *getNeighbours(int id) = 0;
  virtual bool hasEdge(int src, int dst) = 0;

  float density() {
    return (float)(2*this->edgesCount)/(this->verticesCount*(this->verticesCount-1));
  }

  template<typename T>
  static T* generate_random(int vetrices_count, int min_weight, int max_weight, float density) {
    int edges_count = (vetrices_count*(vetrices_count-1)*density)/2;
    // printf("Generating %d edges...\n", edges_count);
    T* graf = new T(vetrices_count, random<int>(0,vetrices_count-1));
    if(density == 1) {
      for(int i = 0; i < vetrices_count; ++i) {
        for(int j = i+1; j < vetrices_count; ++j) {
          // printf("i: %d, j: %d \n",i,j);
          int weight = random<int>(min_weight,max_weight);
          graf->addEdge(i, j, weight);
        }
      }
    }
    else {
      while (edges_count) {
          int source = random<int>(0,vetrices_count-1);
          int destination = random<int>(0,vetrices_count-1);
          if (graf->hasEdge(source, destination)) continue;
          int weight = random<int>(min_weight,max_weight);
          graf->addEdge(source, destination, weight);
          edges_count--;
      }
    }
    
    return graf;
  }

};