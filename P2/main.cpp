#include <stdio.h>
#include "heap.cpp"
#include <iostream>
#include <fstream>
#include "listItem.h"
#include "edge.h"
#include "list.h"
#include "array.h"
#include "graph.h"
#include "dijkstra.h"
#include "timer.h"

class MatrixGraph: public Graph {
  public:
  Edge*** adjacencyMatrix;

  MatrixGraph(): Graph() {
    type = MATRIX_GRAPH;
  }

  ~MatrixGraph() {
    // printf("~MatrixGraph\n");
    // for(int i = 0; i < this->verticesCount ; ++i) {
    //   printf("|");
    //   for(int j = 0; j < this->verticesCount ; ++j) {
    //     Edge* e = this->adjacencyMatrix[i][j];
    //     if (e) printf("%2d ", e->destination);
    //     else printf("   ");
    //   }
    //   printf("|\n");
    // }
    // printf("\n");

    for(int i = 0; i < this->verticesCount ; ++i) {
      for(int j = 0; j < this->verticesCount ; ++j) {
        delete this->adjacencyMatrix[i][j];
        // this->adjacencyMatrix[i][j] = nullptr;
      }
      delete [] this->adjacencyMatrix[i];
      // this->adjacencyMatrix[i] = nullptr;
    }
    delete[] this->adjacencyMatrix;
  }

  MatrixGraph(int size, int start): Graph(size, start) {
    type = MATRIX_GRAPH;
    adjacencyMatrix = new Edge**[verticesCount];

    for(int i = 0; i < verticesCount; ++i) {
      adjacencyMatrix[i] = new Edge*[verticesCount];
      for(int j = 0; j < this->verticesCount ; ++j) {
        adjacencyMatrix[i][j] = nullptr;
      }
    }
  }

  void addEdge(int src, int dest, int weight) {
    Edge *e1 = new Edge(dest,weight);
    adjacencyMatrix[src][dest] = e1;
    e1 = nullptr;

    if (src != dest) {
      Edge *e2 = new Edge(src,weight);
      adjacencyMatrix[dest][src] = e2;
      e2 = nullptr;
    }

    edgesCount++;
    // for(int i = 0; i < this->verticesCount ; ++i) {
    //   for(int j = 0; j < this->verticesCount ; ++j) {
    //     Edge* e = this->adjacencyMatrix[i][j];
    //     printf("%2d ", e ? e->destination : -1);
    //   }
    //   printf("\n");
    // }
    // printf("\n");
  }

  bool hasEdge(int src, int dst) {
    return adjacencyMatrix[src][dst] != nullptr;
  }

  List<Edge*> *getNeighbours(int id) {
    List<Edge*> *list = new List<Edge*>;

    for(int i = 0; i < verticesCount ; ++i) {
      if(adjacencyMatrix[id][i]) {
        Edge *e = adjacencyMatrix[id][i];
        list->append(e);
      }
    }
    return list;
  }

  Edge** operator[](std::size_t idx) {
    return adjacencyMatrix[idx];
  }
  
  friend std::istream & operator>>(std::istream & in, MatrixGraph & g)
  {
    int edges;
    in >> edges >> g.verticesCount >> g.startVertex;

    g.adjacencyMatrix = new Edge**[g.verticesCount];

    for(int i = 0; i < g.verticesCount; ++i) {
      g.adjacencyMatrix[i] = new Edge*[g.verticesCount];
      for(int j = 0; j < g.verticesCount ; ++j) {
        g.adjacencyMatrix[i][j] = nullptr;
      }
    }

    for(int i = 0; i < edges; ++i) {
      int start, end, weight;
      in >> start >> end >> weight;
      g.addEdge(start, end, weight);
    }
    return in;
  }

};


class ListGraph: public Graph {
  public:
  List<Edge*>* adjacencyLists;


  ListGraph(): Graph() {
    type = LIST_GRAPH;
  }

  ListGraph(int size, int start): Graph(size, start) {
    // printf("ListGraph\n");
    type = LIST_GRAPH;
    adjacencyLists = new List<Edge*>[size];
  }
  
  ~ListGraph() {
    for (int i=0; i < verticesCount; ++i) {
      ListItem<Edge*>* tmp = adjacencyLists[i].head;
      while(tmp) {
        delete tmp->data;
        tmp = tmp->next;
      }
    }

    delete[] this->adjacencyLists;
  }

  List<Edge*> operator[](std::size_t idx) {
    return adjacencyLists[idx];
  }
  
  List<Edge*> *getNeighbours(int id) {
    return &adjacencyLists[id];
  }

  void addEdge(int src, int dest, int weight) {
    adjacencyLists[src].append(new Edge(dest, weight));
    adjacencyLists[dest].append(new Edge(src, weight));
    edgesCount++;
  }

  bool hasEdge(int src, int dst) {
    ListItem<Edge*>* tmp = adjacencyLists[src].head;
    while(tmp) {
      if (tmp->data->destination == dst) return true;
      tmp = tmp->next;
    }
    return false;
  }


  friend std::istream & operator>>(std::istream & in, ListGraph & g)
  {
    int edges;
    in >> edges >> g.verticesCount >> g.startVertex;
    g.adjacencyLists = new List<Edge*>[g.verticesCount];

    for(int i = 0; i < edges; ++i) {
      int start, end, weight;
      in >> start >> end >> weight;
      g.addEdge(start, end, weight);
    }
    return in;
  }
};

template<typename T>
void Test(int *graphSize, float *graphDensity, int testCount) {
  T* g;
  for(int d = 0; d < 4; ++d) { // gęstość grafu
    for(int i = 0; i < 5; ++i) { // wielkość grafu
      int time = 0;
      printf("Wielkość: %4d  Gęstość grafu: %3d%%  Postęp: [", graphSize[i], (int)(graphDensity[d]*100));
      for(int j = 0; j < testCount; ++j) {  // j ilość testów
        g = Graph::generate_random<T>(graphSize[i], 1, 20, graphDensity[d]);

        Timer timer;
        DijkstraResults* results = dijkstra(g, g->verticesCount-1);
        time = time + timer.elapsed();
        std::cout << "|" << std::flush; 
        
        delete results;
        delete g;
      }
      // printf("]  Średni czas: %d \n", time/testCount);
      printf("]  Łączny czas: %d \n", time);
    }
  }
}


int main()
{
  int graphSize[] = {250, 400, 500, 600, 750};
  float graphDensity[] = {0.2, 0.5, 0.75, 1};
  printf("Test Macierz\n");
  Test<MatrixGraph>(graphSize, graphDensity, 100);
  printf("Test Lista\n");
  Test<ListGraph>(graphSize, graphDensity, 100);




  ////////////////////////PRZYKŁAD WCZYTYWANIA/ZAPISYWANIA DO PLIKU ////////////////////////////
  // std::ifstream file("data.graf");
  // ListGraph g;
  // file >> g;

  // DijkstraResults* results = dijkstra(&g);

  // std::ofstream plik("results.txt");
  // plik << *results;
  // delete results;

  return 0;
}