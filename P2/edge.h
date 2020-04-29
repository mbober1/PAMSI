
class Edge {
public:
  int weight;
  int destination;

  Edge(int destination, int weight) {
    this->destination = destination;
    this->weight = weight;
  }

  ~Edge() {
    // printf("~Edge (%d)->%d\n", weight, destination);
  }
};
