//teste
#include <stdio.h>
#include <stdlib.h>

#define VERTEX_COUNT 20

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

void add_unidirectional_edge (Graph* graph, int source, int destination) {
    if (graph->current_vertices == 0) return;
    graph->adjacency_matrix[source][destination] = 1;
};

void add_bidirectional_edge (Graph* graph, int source1, int source2) {
    if (graph->current_vertices == 0) return;
    graph->adjacency_matrix[source1][source2] = 1;
    graph->adjacency_matrix[source2][source1] = 1;
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

//a mudanca feita foi para verificar se todos os nodes possuem grau par
int has_eulerian_tour (Graph* graph) {
    int total_odd = 0;

    int* node_degree_count = (int*) malloc(sizeof(int)*(graph->current_vertices));
    
    for (int i = 0; i < graph->current_vertices; ++i) {
        for (int j = 0; j < graph->current_vertices; ++j) {
            if (graph->adjacency_matrix[i][j]){
                node_degree_count[i]++;
            }
        }
    }

    for (int i = 0; i < graph->current_vertices; ++i){
        if(node_degree_count[i]%2 != 0) return 0;
    }

    if (total_odd == 1 || total_odd >2) return 1;
    
    return 1;
};

/*
a alternativa que encontrei para a resolver o problema da copia 
 de matrizes durante os estados da recursao foi utilizar uma unica matriz compartilhada entre os estados 
*/
int solve (Graph* graph, int** visited_matrix, LinkedList* path, int current_vertex) {
    
    if (compare_matrix(graph->current_vertices, graph->adjacency_matrix, visited_matrix)) {
        
        add_item_list(path, current_vertex);
        
        return 1;
    }
    
    for (int i = 0; i < graph->current_vertices; i++) {
        
        if (graph->adjacency_matrix[current_vertex][i] && !visited_matrix[current_vertex][i]){ // tem o edge, mas ainda nào foi visitado
            
            //marca como visitado esse caminho 
            visited_matrix[current_vertex][i] = 1;
            visited_matrix[i][current_vertex] = 1;
            
            if (solve(graph, visited_matrix, path, i)) {
                
                
                add_item_list(path, current_vertex);
                
                return 1;
            }
            
            /*
            Se chegamos aqui, quer dizer que não encontramos o caminho ainda. Como a matriz de visitados está
            sendo compartilhada com todos os estagios da recursao, precisamos fingir que nunca passamos por essa aresta [current_vertex][i],
            para que ela possa ser utilizada posteriormente por um outro estado da recursão. Por esse motivo, colocamos 0 de volta.
            
            A ideia eh fazer com que os caminhos visitados por um estado fiquem visíveis apenas para os proximos estados da recursao. Um estado anterior nao pode saber dos
            caminhos pelos quais o estado posterior passou, a não ser que o caminho euleriano teha sido alcançado.
            */
            
            visited_matrix[current_vertex][i] = 0;//no retorno, a matriz volta do jeito que entrou
            visited_matrix[i][current_vertex] = 0;//no retorno, a matriz volta do jeito que entrou
            
        }
    }
    
    
    return 0;
}

void print_list (LinkedList* list) {
    
    if(list == NULL)
        return;

    LinkedListNode* current_node = list->head;
    while(current_node) {
        printf("%d ", current_node->value);
        current_node = current_node->next;
    }
    printf("\n");
}

LinkedList* solve_eleurian_path (Graph* graph, int initial_vertex) {
    
    if (!has_eulerian_tour(graph)) {
        printf ("o grafo não é euleriano");
        return NULL;
    }
    
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
    add_node(graph);
    add_node(graph);
    add_bidirectional_edge(graph, 6, 5);
    add_bidirectional_edge(graph, 6, 4);
    add_bidirectional_edge(graph, 6, 3);
    add_bidirectional_edge(graph, 6, 2);
    add_bidirectional_edge(graph, 5, 4);
    add_bidirectional_edge(graph, 5, 3);
    add_bidirectional_edge(graph, 5, 2);
    add_bidirectional_edge(graph, 4, 0);
    add_bidirectional_edge(graph, 4, 1);
    add_bidirectional_edge(graph, 4, 2);
    add_bidirectional_edge(graph, 4, 3);
    add_bidirectional_edge(graph, 3, 2);
    add_bidirectional_edge(graph, 1, 0);
    // add_unidirectional_edge(graph,0,1);
    // add_unidirectional_edge(graph,1,2);
    // add_unidirectional_edge(graph,3,2);
    // add_unidirectional_edge(graph,2,0);
    // printf("%d",has_eulerian_tour(graph));
    LinkedList* path = solve_eleurian_path(graph, 3);
    print_list(path);
    return 0;
};
