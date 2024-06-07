/*KIT205
@author LE HOANG ANH DINH
@studentID 594981*/
#include <stdio.h>
#include "graph.h"
int main() {
    const char* filename = "inf-USAir97.mtx";
    Graph* graph = parseMTXFile(filename);

    // Print the adjacency list representation of the graph
    printGraph(graph);

    // Find the shortest path from vertex 0
    printf("\nDijkstra's Algorithm:\n");
    dijkstra(graph, 0);

    // Find the maximum flow from vertex 0 to vertex 5
    printf("\nFord-Fulkerson Algorithm:\n");
    int max_flow = fordFulkerson(graph, 0, 5);
    printf("The maximum possible flow is %d\n", max_flow);
    
    getchar();
    return 0;
}