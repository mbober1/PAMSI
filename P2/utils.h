
#pragma once
#include "vertex.h"
#include <random>
std::mt19937 generator{std::random_device{}()};


template<typename T>
T random(T min, T max) {
    return std::uniform_int_distribution<T>{min, max}(generator);
}


class VertexHeap: public Heap<Vertex*> {
    using Heap::Heap;

    public:
      bool compare(int i, int j) {
          return this->heap[i]->distance > this->heap[j]->distance;
      }

      Vertex* search(int id) {
        for(int i = 0; i < this->heap_size; ++i){
          if(this->heap[i]->id == id) return this->heap[i];
        }
        // printf("dupa nic nie znalazlem\n");
        return nullptr;
      }

};

