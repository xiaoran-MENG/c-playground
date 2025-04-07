#include "graph.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    Graph* graph = construct_graph(6);

    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 1, 4);
    add_edge(graph, 2, 4);
    add_edge(graph, 3, 5);
    add_edge(graph, 4, 5);

    breadth_first_search(graph, 0);
    depth_first_search(graph, 0);

    free_graph(graph);
    return 0;
}
