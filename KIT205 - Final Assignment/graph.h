#pragma once
/*KIT205
@author LE HOANG ANH DINH
@studentID 594981*/
#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100 // Define a maximum number of vertices

// Define the structure for an adjacency list node
typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

// Define the structure for an adjacency list
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

// Define the structure for a graph
typedef struct Graph {
    int V;
    AdjList* array;
} Graph;

// Function to create a new adjacency list node
AdjListNode* newAdjListNode(int dest, int weight);

// Function to create a graph with V vertices
Graph* createGraph(int V);

// Function to add an edge to a graph
void addEdge(Graph* graph, int src, int dest, int weight);

// Function to print the graph
void printGraph(Graph* graph);

#endif
