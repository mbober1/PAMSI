#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.cpp"
 
using namespace std;


class Edge {
    public:
        int vertex;
        int weight;
};

class Vertex {
    public:
        Edge **edges;
        int edges_len;
        int edges_size;
        int dist;
        int prev;
        int visited;
};
 
class Graph {
    public:
        Vertex **vertices;
        int vertices_len;
        int vertices_size;

        void add_vertex (int i) {
            if (this->vertices_size < i + 1) {
                int size = this->vertices_size * 2 > i ? this->vertices_size * 2 : i + 4;
                this->vertices = realloc(this->vertices, size * sizeof (Vertex *));
                for (int j = this->vertices_size; j < size; j++)
                    this->vertices[j] = NULL;
                this->vertices_size = size;
            }
            if (!this->vertices[i]) {
                this->vertices[i] = calloc(1, sizeof (Vertex));
                this->vertices_len++;
            }
        }

        void add_edge (int a, int b, int w) {
            a = a - 'a';
            b = b - 'a';
            add_vertex(a);
            add_vertex(b);
            Vertex *v = this->vertices[a];
            if (v->edges_len >= v->edges_size) {
                v->edges_size = v->edges_size ? v->edges_size * 2 : 4;
                v->edges = realloc(v->edges, v->edges_size * sizeof (Edge *));
            }
            Edge *e = calloc(1, sizeof (Edge));
            e->vertex = b;
            e->weight = w;
            v->edges[v->edges_len++] = e;
        }
};
 
// typedef struct {
//     int *data;
//     int *prio;
//     int *index;
//     int len;
//     int size;
// } heap_t;
 

 

 
// heap_t *create_heap (int n) {
//     heap_t *h = calloc(1, sizeof (heap_t));
//     h->data = calloc(n + 1, sizeof (int));
//     h->prio = calloc(n + 1, sizeof (int));
//     h->index = calloc(n, sizeof (int));
//     return h;
// }
 
// void push_heap (heap_t *h, int v, int p) {
//     int i = h->index[v] == 0 ? ++h->len : h->index[v];
//     int j = i / 2;
//     while (i > 1) {
//         if (h->prio[j] < p)
//             break;
//         h->data[i] = h->data[j];
//         h->prio[i] = h->prio[j];
//         h->index[h->data[i]] = i;
//         i = j;
//         j = j / 2;
//     }
//     h->data[i] = v;
//     h->prio[i] = p;
//     h->index[v] = i;
// }
 
// int min (heap_t *h, int i, int j, int k) {
//     int m = i;
//     if (j <= h->len && h->prio[j] < h->prio[m])
//         m = j;
//     if (k <= h->len && h->prio[k] < h->prio[m])
//         m = k;
//     return m;
// }
 
// int pop_heap (heap_t *h) {
//     int v = h->data[1];
//     int i = 1;
//     while (1) {
//         int j = min(h, h->len, 2 * i, 2 * i + 1);
//         if (j == h->len)
//             break;
//         h->data[i] = h->data[j];
//         h->prio[i] = h->prio[j];
//         h->index[h->data[i]] = i;
//         i = j;
//     }
//     h->data[i] = h->data[h->len];
//     h->prio[i] = h->prio[h->len];
//     h->index[h->data[i]] = i;
//     h->len--;
//     return v;
// }
 
void dijkstra (Graph *g, int a, int b) {
    int i, j;
    a = a - 'a';
    b = b - 'a';
    for (i = 0; i < g->vertices_len; i++) {
        Vertex *v = g->vertices[i];
        v->dist = INT_MAX;
        v->prev = 0;
        v->visited = 0;
    }
    Vertex *v = g->vertices[a];
    v->dist = 0;
    Heap *h = create_heap(g->vertices_len);
    push_heap(h, a, v->dist);
    while (h->len) {
        i = pop_heap(h);
        if (i == b)
            break;
        v = g->vertices[i];
        v->visited = 1;
        for (j = 0; j < v->edges_len; j++) {
            Edge *e = v->edges[j];
            Vertex *u = g->vertices[e->vertex];
            if (!u->visited && v->dist + e->weight <= u->dist) {
                u->prev = i;
                u->dist = v->dist + e->weight;
                push_heap(h, e->vertex, u->dist);
            }
        }
    }
}
 
void print_path (Graph *g, int i) {
    int n, j;
    Vertex *v, *u;
    i = i - 'a';
    v = g->vertices[i];
    if (v->dist == INT_MAX) {
        printf("no path\n");
        return;
    }
    for (n = 1, u = v; u->dist; u = g->vertices[u->prev], n++)
        ;
    char *path = malloc(n);
    path[n - 1] = 'a' + i;
    for (j = 0, u = v; u->dist; u = g->vertices[u->prev], j++)
        path[n - j - 2] = 'a' + u->prev;
    printf("%d %.*s\n", v->dist, n, path);
}
 
int main () {
    Graph *g = calloc(1, sizeof (Graph));
    add_edge(g, 'a', 'b', 7);
    add_edge(g, 'a', 'c', 9);
    add_edge(g, 'a', 'f', 14);
    add_edge(g, 'b', 'c', 10);
    add_edge(g, 'b', 'd', 15);
    add_edge(g, 'c', 'd', 11);
    add_edge(g, 'c', 'f', 2);
    add_edge(g, 'd', 'e', 6);
    add_edge(g, 'e', 'f', 9);
    dijkstra(g, 'a', 'e');
    print_path(g, 'e');
    return 0;
}

