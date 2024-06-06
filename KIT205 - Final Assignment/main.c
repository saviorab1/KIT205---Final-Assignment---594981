/*KIT205
@author LE HOANG ANH DINH
@studentID 594981*/
#include <stdio.h>
#include "graph.h"

int main() {
    int V = 6;
    Graph* graph = createGraph(V);
    addEdge(graph, 0, 1, 16);
    addEdge(graph, 0, 2, 13);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 1, 3, 12);
    addEdge(graph, 2, 1, 4);
    addEdge(graph, 2, 4, 14);
    addEdge(graph, 3, 2, 9);
    addEdge(graph, 3, 5, 20);
    addEdge(graph, 4, 3, 7);
    addEdge(graph, 4, 5, 4);

    // Print the adjacency list representation of the graph
    printGraph(graph);
    // Find the shortest path from vertex 0
    printf("\nDijkstra's Algorithm:\n");
    dijkstra(graph, 0);
    return 0;
}