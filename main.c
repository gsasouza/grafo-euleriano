#include <stdio.h>
#include <stdlib.h>

#define VERTEX_COUNT 6

typedef struct graph {
    int vertex_count_max;
    int current_vertices;
    int** adjacency_matrix;
} Graph;

int** create_matrix (int size) {
    int** matrix = malloc(sizeof(int*) * size);
    for (int i = 0; i < size; ++i) {
        matrix[i] = malloc(sizeof(int) * size);
    }
    return matrix;
};

Graph* create_graph() {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->vertex_count_max = VERTEX_COUNT;
    graph->current_vertices = 0;
    graph->adjacency_matrix = create_matrix(VERTEX_COUNT);

    for (int i = 0; i < VERTEX_COUNT; i++) {
        for (int j = 0; j < VERTEX_COUNT; j++) {
            graph->adjacency_matrix[i][j] = 0;
        }
    }
    return graph;
}

void add_node (Graph* graph) {
    graph->current_vertices++;
};

void add_edge (Graph* graph, int source, int destination) {
    if (graph->current_vertices == 0) return;
    graph->adjacency_matrix[source][destination] = 1;
};

void remove_edge (Graph* graph, int source, int destination) {
    if (graph->current_vertices == 0) return;
    graph->adjacency_matrix[source][destination] = 0;
};

void print_matrix(Graph* graph) {
    for (int i = 0; i < graph->current_vertices; ++i) {
        for (int j = 0; j < graph->current_vertices; j++) {
            printf("%d ", graph->adjacency_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

int compare_matrix (int size, int** matrix1, int** matrix2) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; ++j) {
            if (matrix1[i][j] != matrix2[i][j]) return 0;
        }
    }
    return 1;
};

int is_eleurian (Graph* graph) {
    int total_odd = 0;
    for (int i = 0; i < graph->current_vertices; ++i) {
        int edges = 0;
        for (int j = 0; j < graph->current_vertices; ++j) {
            if (graph->adjacency_matrix[i][j]) edges++;
        }
        if (edges % 2 != 0) total_odd++;
        if (total_odd > 2) return 0;
    }
    if (total_odd == 1) return 0;
    return 1;
};

int solve (Graph* graph, int** visited_matrix) {
    if (compare_matrix(graph->current_vertices, graph->adjacency_matrix, visited_matrix)) {
        return 1;
    }

}

void solve_eleuria_path (Graph* graph) {
    if (!is_eleurian(graph)) printf ("o grafo não é euleriano");
    int ** visited_matrix = create_matrix(graph->current_vertices);
};

int main() {
    Graph* graph = create_graph();
    add_node(graph);
    add_node(graph);
    add_node(graph);
    add_node(graph);
    add_node(graph);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 3);
//    print_matrix(graph);
    int x = is_eleurian(graph);

//    int** visited_matrix = create_matrix(graph->current_vertices);
//    int x  = compare_matrix(graph->current_vertices, visited_matrix, graph->adjacency_matrix);
    printf("%d", x);
    return 0;
};
