#pragma once
#include "graph.h"
#include "vertex.h"
#include "utils.h"
#include <stdio.h>
#include <limits.h>

class DijkstraResults {
public:
  Vertex** paths;
  int verticesCount;
  DijkstraResults(Vertex** paths, int verticesCount) {
    this->paths = paths;
    this->verticesCount = verticesCount;
  }

  ~DijkstraResults() {
    // printf("~DijkstraResults (%d) \n", verticesCount);
    for (int i=0; i < verticesCount; ++i) {
      delete paths[i];
    }
    delete[] paths;
  }

  Vertex* findVertex(int id) const {
    for (int j = 0; j < this->verticesCount; ++j) {
      if (this->paths[j]->id == id) return this->paths[j];
    }
    return nullptr;
  }

  friend std::ostream & operator<<(std::ostream & out, const DijkstraResults & r)
  {
    for(int i = 0; i < r.verticesCount; ++i) {
      Vertex* v = r.paths[i];
      out << v->distance;
      while(v = r.findVertex(v->preVertex)) out << "\t" << v->id;
      out << "\n";
    }
    return out;
  }

};


DijkstraResults* dijkstra(Graph *g, int dest = -1) {
  Vertex** arr = new Vertex*[g->verticesCount];
  for (int i=0; i < g->verticesCount; ++i) {
    arr[i] = new Vertex(i, i == g->startVertex ? 0 : INT_MAX);
  }
  VertexHeap* heap = new VertexHeap(arr, g->verticesCount);
  heap->heap_build(0);

  while (heap->heap_size) {      
    Vertex* u = heap->pop();
    List<Edge*>* list = nullptr;
    list = g->getNeighbours(u->id);
    ListItem<Edge*>* currItem = list->head;
    while (currItem) 
    {
      Edge* edge = currItem->data;
      if (edge) {
        Vertex* v = heap->search(edge->destination);

        if (v) {
          if(u->distance != INT_MAX && edge->weight + u->distance < v->distance) {
            v->distance = u->distance + edge->weight;
            v->preVertex = u->id;
          }

          if (v->id == dest) {
            if (g->type == MATRIX_GRAPH) delete list;
            delete heap;
            return new DijkstraResults(arr, g->verticesCount);
          }
        }
        currItem = currItem->next;
      } else printf("DUPA\n");
    }
    heap->heap_restore(0, 0);
    if (g->type == MATRIX_GRAPH) delete list;
  }
  delete heap;
  return new DijkstraResults(arr, g->verticesCount);
}
