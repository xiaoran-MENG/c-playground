#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Vertex
{
    int index;
    struct Vertex* next;
} Vertex;

struct Graph
{
    int vertices_count;
    Vertex** adjacency;
};

static Vertex* construct_vertex(int index)
{
    Vertex* vertex = malloc(sizeof(Vertex));
    
    if (vertex == NULL)
    {
        fprintf(stderr, "Failed to construct vertex\n");
        exit(EXIT_FAILURE);
    }

    vertex->index = index;
    vertex->next = NULL;

    return vertex;
}

Graph *construct_graph(int vertices_count)
{
    Graph* graph = malloc(sizeof(Graph));
    
    if (graph == NULL)
    {
        fprintf(stderr, "Failed to construct graph\n");
        exit(EXIT_FAILURE);
    }

    graph->vertices_count = vertices_count;
    graph->adjacency = malloc(vertices_count * sizeof(Vertex*));

    if (graph->adjacency == NULL)
    {
        fprintf(stderr, "Failed to construct adjacency list\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < vertices_count; i++)
    {
        graph->adjacency[i] = NULL;
    }

    return graph;
}

void add_edge(Graph *graph, int source_index, int target_index)
{
    Vertex* target = construct_vertex(target_index);
    target->next = graph->adjacency[source_index];
    graph->adjacency[source_index] = target;

    Vertex* source = construct_vertex(source_index);
    source->next = graph->adjacency[target_index];
    graph->adjacency[target_index] = source;
}

void free_graph(Graph *graph)
{
    if (graph == NULL)
    {
        return;
    }

    for (int i = 0; i < graph->vertices_count; i++)
    {
        Vertex* vertex = graph->adjacency[i];
        while (vertex)
        {
            Vertex* current = vertex;
            vertex = vertex->next;
            free(current);
        }
    }

    free(graph->adjacency);
    free(graph);
}

void breadth_first_search(Graph *graph, int start_index)
{
    int* visited = calloc(graph->vertices_count, sizeof(int));
    if (visited == NULL)
    {
        fprintf(stderr, "Failed to construct visited list\n");
        exit(EXIT_FAILURE);
    }

    int* queue = malloc(graph->vertices_count * sizeof(int));
    if (queue == NULL)
    {
        fprintf(stderr, "Failed to construct queue\n");
        exit(EXIT_FAILURE);
    }

    int front = 0, rear = 0;

    visited[start_index] = 1;
    queue[rear++] = start_index;

    while (front < rear)
    {
        int index = queue[front++];
        printf("%d ", index);

        Vertex* neighbor = graph->adjacency[index];
        while (neighbor)
        {
            if (!visited[neighbor->index])
            {
                visited[neighbor->index] = 1;
                queue[rear++] = neighbor->index;
            }

            neighbor = neighbor->next;
        }
    }
    printf("\n");

    free(visited);
    free(queue);
}

static void depth_first_search_recursive(Graph *graph, int index, int* visited)
{
    visited[index] = 1;
    printf("%d ", index);

    Vertex* neighbor = graph->adjacency[index];
    while (neighbor)
    {
        if (!visited[neighbor->index])
        {
            depth_first_search_recursive(graph, neighbor->index, visited);
        }
        neighbor = neighbor->next;
    }
}

void depth_first_search(Graph *graph, int start_index)
{
    int* visited = calloc(graph->vertices_count, sizeof(int));
    if (visited == NULL)
    {
        fprintf(stderr, "Failed to construct visited list\n");
        exit(EXIT_FAILURE);
    }

    depth_first_search_recursive(graph, start_index, visited);
}

