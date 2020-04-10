#include <stdio.h>
#include <limits.h>
#include "heap.cpp"
#include <iostream>

class Vertex {
public:
  int distance;
  int id;

  Vertex(int id, int distance) {
    this->id = id;
    this->distance = distance;
  }
};

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
        return nullptr;
      }

};

class Edge {
public:
  int weight;
  int destination;

  Edge(int destination, int weight) {
    this->destination = destination;
    this->weight = weight;
  }
};

template<typename T>
class ListItem {
public:
  T* data;
  ListItem<T> *next = nullptr;

  ListItem<T>(T* data) {
    this->data = data;
  }
};

template<typename T>
class List {
public:
  ListItem<T>* head = nullptr;

  ListItem<T>* addItem(T* data) {
    ListItem<T>* elem = new ListItem<T>(data);
    if (!this->head) this->head = elem;
    else {
      ListItem<T>* tmp = this->head;
      while (tmp->next) tmp = tmp->next;
      tmp->next = elem;
    }
    return this->head;
  }
};



class Graph {
public:
  int verticesCount;
  List<Edge>* adjacencyLists;
  bool directed;

  Graph(int size, bool directed = false) {
    this->verticesCount = size;
    this->directed = directed;
    adjacencyLists = new List<Edge>[size];
  }

  void addEdge(int src, int dest, int weight) {
    adjacencyLists[src].addItem(new Edge(dest, weight));
    if (!this->directed) adjacencyLists[dest].addItem(new Edge(src, weight));
  }

  Vertex** shortestPaths(int src, int dest = -1) {
    Vertex** arr = new Vertex*[this->verticesCount];
    for (int i=0; i < this->verticesCount; ++i) {
      arr[i] = new Vertex(i, i == src ? 0 : INT_MAX);
    }
    VertexHeap* heap = new VertexHeap(arr, this->verticesCount);
    heap->heap_build(0);

    while (heap->heap_size) {
      Vertex* u = heap->pop();
      printf("Wierzchołek [%d]\n", u->id);
      auto head = this->adjacencyLists[u->id].head;
      while (head)
      {
        Edge* edge = head->data;
        printf("DEST: %d\n", edge->destination);
        Vertex* v = heap->search(edge->destination);
        printf("vertex: %d\n", v->id);

        // if(v && u->distance != INT_MAX && edge->weight + u->distance < v->distance) {
        //   v->distance = u->distance + edge->weight;
        // }

        head = head->next;
      }
      printf("------------------------------\n");
      // Sum fucking magic 🧙‍♂️🧙‍♂️
    }
    // for(int i=0; i<heap->heap_size; i++) {
    //   std::cout << (heap->heap[i]->id);
    // }

    return arr;
  }
};



int main()
{
  int numOfVertices = 4;
  Graph* g = new Graph(numOfVertices, true);
  g->addEdge(0, 1, 1);
  g->addEdge(0, 2, 1);
  g->addEdge(2, 3, 1);

  // for (int i=0; i < g->verticesCount; ++i) {
  //   auto x = g->adjacencyLists[i].head;
  //   printf("Wierzchołek %d -> ", i);
  //   while (x) {
  //     printf("%d, ", x->data->destination);
  //     x = x->next;
  //   }
  //   printf("\n");
  // }
  

  int sourceVertex = 0;
  Vertex** paths = g->shortestPaths(sourceVertex);

  // for (int i=0; i < numOfVertices; ++i) {
  //   printf("Minimalna odległość od wierzchołka %d do %d to: %d\n", sourceVertex, i, paths[i]->distance);
  // }

  return 666;
}