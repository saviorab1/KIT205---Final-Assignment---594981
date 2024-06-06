/*KIT205
@author LE HOANG ANH DINH
@studentID 594981*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <float.h>
#include "graph.h"

// Function to create a new adjacency list node
AdjListNode* newAdjListNode(int dest, float weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}


// Function to create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// Function to add an edge to a graph
void addEdge(Graph* graph, int src, int dest, float weight) {
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    // Since the graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to print the graph
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d(%f)", pCrawl->dest, pCrawl->weight);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// Utility function to find the vertex with minimum distance value
int minDistance(float dist[], bool sptSet[], int V) {
    float min = FLT_MAX;
    int min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Function to print the constructed distance array
void printSolution(float dist[], int V) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %f\n", i, dist[i]);
}

// Function to implement Dijkstra's shortest path algorithm for a graph
void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    float dist[MAX_VERTICES];
    bool sptSet[MAX_VERTICES];

    for (int i = 0; i < V; i++) {
        dist[i] = FLT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = true;

        for (AdjListNode* pCrawl = graph->array[u].head; pCrawl != NULL; pCrawl = pCrawl->next) {
            int v = pCrawl->dest;
            if (!sptSet[v] && dist[u] != FLT_MAX && dist[u] + pCrawl->weight < dist[v])
                dist[v] = dist[u] + pCrawl->weight;
        }
    }

    printSolution(dist, V);
}
