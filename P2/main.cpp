#include <iostream>
#include "list.cpp"
using namespace std;


class Edge {
    public:
        int weight;

};

class Vertex {
    public:
        Vertex() {
            this->edges_size = 0;
        }

        Edge **edges;
        int edges_size;

};



class Graph {
    public:
        int vertices_count;
        Vertex* vertices;
        List<Vertex*>* array;

        void add_vertex() {
            List<Vertex*>* new_list = new List<Vertex*>[vertices_count+1];
            for(int i=0; i<vertices_count; i++) {
                new_list[i] = array[i];
            }
            delete [] array;
            array = new_list;
            array[vertices_count+1] = List<Vertex*>();

            Vertex* new_vertices = new Vertex[vertices_count+1];
            for(int i=0; i<vertices_count; i++) {
                new_vertices[i] = vertices[i];
            }
            delete [] vertices;
            vertices = new_vertices;
            vertices[vertices_count+1] = Vertex() ;

            vertices_count++;
        }

        void add_edge(int a, int b, int weight) {
            
        }
};


















int main() {
    Graph graf;
    graf.add_vertex();
    graf.add_vertex();
    return 0;
}