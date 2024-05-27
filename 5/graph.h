#ifndef GRAPH_H

#define GRAPH_H

#define INT_MAX 1000 * 1000 * 10

#include "queue.h"

typedef struct Edge {
	char * src;
	char * dest;
	int weight;
} Edge;

typedef struct Vertex {
	char * name;
} Vertex;

typedef struct AdjacencyNode {
	char * name;
	int weight;
	struct AdjacencyNode * next;	
} AdjacencyNode;

typedef struct AdjacencyListHead {
	char * name;
	AdjacencyNode * list;
	struct AdjacencyListHead * next;
} AdjacencyListHead;

typedef struct AdjacencyList {
	AdjacencyListHead * head;
	int vCount;
	int eCount;
} AdjacencyList;

AdjacencyListHead * getVerticeByIndex(AdjacencyList * list, int index);

void freeGraph(AdjacencyList * list);

AdjacencyList * createAdjacencyList();

void bfsTask(AdjacencyList * list, char * start);

AdjacencyList * importFromFile(char * filename);

void outputAdjacencyList(AdjacencyList * list);

Queue * findShortestPath(AdjacencyList * list, char * f, char * t, int * res);

void dotPrintGraph(AdjacencyList * list, char * filename);

int addVertex(AdjacencyList * list, char * name);

int addEdge(AdjacencyList * list, char * from, char * to, int weight);

void deleteEdge(AdjacencyList * list, char * from, char * to);

void deleteVertex(AdjacencyList * list, char * name);

AdjacencyListHead * floydWarshall(AdjacencyList * graph, char * name, int * res);

void bellmanFord(AdjacencyList * list, char * f);

#endif
