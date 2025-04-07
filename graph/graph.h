#ifndef GRAPH_H
#define GRAPH_H

typedef struct Graph Graph;

Graph* construct_graph(int vertices_count);
void add_edge(Graph* graph, int source_index, int target_index);
void free_graph(Graph* graph);
void breadth_first_search(Graph* graph, int start_index);
void depth_first_search(Graph* graph, int start_index);

#endif