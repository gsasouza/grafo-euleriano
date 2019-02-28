//teste
#include <stdio.h>
#include <stdlib.h>

#define VERTEX_COUNT 6

typedef struct graph {
    int vertex_count_max;
    int current_vertices;
    int** adjacency_matrix;
} Graph;

typedef struct linkedListNode {
    int value;
    struct linkedListNode* next;
} LinkedListNode;

typedef struct linkedList {
    LinkedListNode* head;
} LinkedList;

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

void add_item_list(LinkedList* list, int value) {
    LinkedListNode* new_item = (LinkedListNode*) malloc(sizeof(LinkedListNode*));
    new_item->next = list->head;
    new_item->value = value;
    list->head = new_item;
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

int solve (Graph* graph, int** visited_matrix, LinkedList* path, int current_vertex) {
    if (compare_matrix(graph->current_vertices, graph->adjacency_matrix, visited_matrix)) {
        return 1;
    }
    for (int i = 0; i < graph->current_vertices; i++) {
        if (graph->adjacency_matrix[current_vertex][i] && !visited_matrix[current_vertex][i]){ // tem o edge, mas ainda nào foi visitado
            visited_matrix[current_vertex][i] = 1;
            if (solve(graph, visited_matrix, path, i)) {
                add_item_list(path, i);
                return 1;
            }
        }
    }
    return 0;
}

void print_list (LinkedList* list) {
    LinkedListNode* current_node = list->head;
    while(current_node) {
        printf("%d", current_node->value);
        current_node = current_node->next;
    }
}

LinkedList* solve_eleurian_path (Graph* graph, int initial_vertex) {
    if (!is_eleurian(graph)) printf ("o grafo não é euleriano");
    int ** visited_matrix = create_matrix(graph->current_vertices);
    LinkedList* path = (LinkedList *) malloc(sizeof(LinkedList*));
    solve(graph, visited_matrix, path, initial_vertex);
    return path;
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
    LinkedList* path = solve_eleurian_path(graph, 0);
    print_list(path);
    return 0;
};
