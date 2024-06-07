/*KIT205
@author LE HOANG ANH DINH
@studentID 594981*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "graph.h"

// Function to create a new adjacency list node
AdjListNode* newAdjListNode(int dest, int weight) {
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
void addEdge(Graph* graph, int src, int dest, int weight) {
    // Add an edge from src to dest. A new node is added to the adjacency list of src.
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    // Since graph is undirected, add an edge from dest to src also
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
            printf("-> %d(%d)", pCrawl->dest, pCrawl->weight);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// Utility function to find the vertex with minimum distance value
int minDistance(int dist[], bool sptSet[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Function to print the constructed distance array
void printSolution(int dist[], int V) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Function to implement Dijkstra's shortest path algorithm for a graph
void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int dist[MAX_VERTICES];
    bool sptSet[MAX_VERTICES];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = true;

        for (AdjListNode* pCrawl = graph->array[u].head; pCrawl != NULL; pCrawl = pCrawl->next) {
            int v = pCrawl->dest;
            if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + pCrawl->weight < dist[v])
                dist[v] = dist[u] + pCrawl->weight;
        }
    }

    printSolution(dist, V);
}

// Function to perform a BFS search for Ford-Fulkerson
bool bfs(int rGraph[MAX_VERTICES][MAX_VERTICES], int V, int s, int t, int parent[]) {
    bool visited[MAX_VERTICES];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    int queue[MAX_VERTICES], front = 0, rear = 0;
    queue[rear++] = s;
    visited[s] = true;
    parent[s] = -1;

    while (front < rear) {
        int u = queue[front++];
        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];
}

// Function to implement Ford-Fulkerson algorithm for finding the maximum flow
int fordFulkerson(Graph* graph, int s, int t) {
    int u, v;
    int V = graph->V;
    int rGraph[MAX_VERTICES][MAX_VERTICES];

    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = 0;

    for (u = 0; u < V; u++) {
        for (AdjListNode* pCrawl = graph->array[u].head; pCrawl != NULL; pCrawl = pCrawl->next) {
            rGraph[u][pCrawl->dest] = pCrawl->weight;
        }
    }

    int parent[MAX_VERTICES];
    int max_flow = 0;

    while (bfs(rGraph, V, s, t, parent)) {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = path_flow < rGraph[u][v] ? path_flow : rGraph[u][v];
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}
