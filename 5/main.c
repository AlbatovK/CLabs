#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "utils.h"

#include "queue.h"

#define INT_MAX 100000000

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

AdjacencyNode * createAdjacencyNode(char * name, int weight) {
	AdjacencyNode * node = (AdjacencyNode *) malloc(sizeof(AdjacencyNode) * 1);
	node -> name = name;
	node -> weight = weight;
	node -> next = NULL;
	return node;
}

AdjacencyListHead * createAdjacencyListHead(char * headName) {
	AdjacencyListHead * head = (AdjacencyListHead *) malloc(sizeof(AdjacencyListHead) * 1);
	head -> list = NULL;
	head -> name = headName;
	head -> next = NULL;
	return head;
}

AdjacencyList * createAdjacencyList() {
	AdjacencyList * list = (AdjacencyList *) malloc(sizeof(AdjacencyList) * 1);
	list -> head = NULL;
	list -> vCount = 0;
	list -> eCount = 0;
	return list;
}

int addVertex(AdjacencyList * list, char * name) {
	AdjacencyListHead * head = list -> head;

	AdjacencyListHead * new = createAdjacencyListHead(name);
	if (head == NULL) {
		list -> head = new;
		list -> vCount++;
		return 1;
	}
	
	while (head -> next) {
		if (strcmp(head -> name, name) == 0) {
			return 0;
		}
		
		head = head -> next;
	}

	if (strcmp(head -> name, name) == 0) {
		return 0;
	}
	
	head -> next = new;
	list -> vCount++;
	return 1;
	
}

int addEdge(AdjacencyList * list, char * from, char * to, int weight) {
	AdjacencyListHead * head = list -> head;

	while (head) {
		if (strcmp(head -> name, from) == 0 || strcmp(head -> name, to) == 0) {
			AdjacencyNode * node = head -> list;
			while (node) {
				if (strcmp(node -> name, from) == 0 || strcmp(node -> name, to) == 0) {
					return 0;
				}
				node = node -> next;
			}
		}

		head = head -> next;
	}

	head = list -> head;
	
	while (head) {
	
		if (strcmp(head -> name, from) == 0 || strcmp(head -> name, to) == 0) {
			AdjacencyNode * start = head -> list;
			AdjacencyNode * new = createAdjacencyNode( (strcmp(head -> name, from) == 0) ? to : from, weight);
			head -> list = new;
			new -> next = start;	
		}
		
		head = head -> next;
	}

	list -> eCount++;
	return 1;
}

void outputAdjacencyList(AdjacencyList * list) {
	AdjacencyListHead * cur = list -> head;
	while (cur) {
		printf("%s: ", cur -> name);
		AdjacencyNode * node = cur -> list;
		while (node) {
			printf("%s (%d) -> ", node -> name, node -> weight);
			node = node -> next;
		}
		printf("end.\n");
		cur = cur -> next;
	}
}

void dotPrintGraph(AdjacencyList * list, char * filename) {
	FILE * out = fopen(filename, "w");
	if (out == NULL) {
		return;
	}

	fprintf(out, "strict graph relations {\n");
	fprintf(out, "	node [fontname=\"Mono\"];\n");

	AdjacencyListHead * head = list -> head;
	while (head) {
		AdjacencyNode * node = head -> list;
		while (node) {
			fprintf(out, "	%s -- %s [label=%d];\n", head -> name, node -> name, node -> weight);
			node = node -> next;
		}
		head = head -> next;
	}

	fprintf(out, "}\n");
	fclose(out);
}

AdjacencyList * importFromFile(char * filename) {
	AdjacencyList * graph = createAdjacencyList();

	FILE * filePtr = fopen(filename, "r");
	if (filePtr == NULL) {
		return graph;
	}

	char * line;
	while (strlen((line = file_readline(filePtr)))) {
		char * from = strtok(line, ";");
		char * to = strtok(NULL, ";");
		char * sWeight = strtok(NULL, ";");
		int weight = atoi(sWeight);
		addVertex(graph, from);
		addVertex(graph, to);
		addEdge(graph, from, to, weight);
	}

	fclose(filePtr);

	return graph;
}

int verticeIndex(AdjacencyList * list, char * name) {
	int i = 0;
	AdjacencyListHead * head = list -> head;
	while (head) {
		if (strcmp(head -> name, name) == 0) {
			return i;
		}
		head = head -> next;
		i++;
	}

	return -1;
}

AdjacencyListHead * getVerticeByIndex(AdjacencyList * list, int index) {
	AdjacencyListHead * head = list -> head;
	int i = 0;
	while (head) {
		if (i == index) {
			return head;
		}
		head = head -> next;
		i++;
	}
	
	return NULL;
}


void bfs(AdjacencyList * list, char * start) {
	int * color = (int *) malloc(sizeof(int) * list -> vCount);
	int * d = (int *) malloc(sizeof(int) * list -> vCount);
	int * pred = (int *) malloc(sizeof(int) * list -> vCount);

	AdjacencyListHead * head = list -> head;
	while (head) {
		int i = verticeIndex(list, head -> name);
		color[i] = 0;
		d[i] = INT_MAX;
		pred[i] = -1;

		head = head -> next;
	}	

	int sIndex = verticeIndex(list, start);
	color[sIndex] = 1;
	d[sIndex] = 0;

	Queue * q = createQueue();
	insertQueue(q, sIndex);

	while (queueSize(q) != 0) {
		int u = popQueue(q);
		AdjacencyListHead * vertice = getVerticeByIndex(list, u);
		AdjacencyNode * v = vertice -> list;
	
		while (v) {
			int vIndex = verticeIndex(list, v -> name);
			if (color[vIndex] == 0) {
				color[vIndex] = 1;
				d[vIndex] = d[u] + 1;
				pred[vIndex] = u;
				insertQueue(q, vIndex);
				
			}

			v = v -> next;
		}

		color[u] = 2;
	}
	
}

void bfsTask(AdjacencyList * list, char * start) {
	int * color = (int *) malloc(sizeof(int) * list -> vCount);
	int * d = (int *) malloc(sizeof(int) * list -> vCount);
	int * pred = (int *) malloc(sizeof(int) * list -> vCount);

	AdjacencyListHead * head = list -> head;
	while (head) {
		int i = verticeIndex(list, head -> name);
		color[i] = 0;
		d[i] = INT_MAX;
		pred[i] = -1;

		head = head -> next;
	}	

	int sIndex = verticeIndex(list, start);
	color[sIndex] = 1;
	d[sIndex] = 0;

	Queue * q = createQueue();
	insertQueue(q, sIndex);

	while (queueSize(q) != 0) {
		int u = popQueue(q);
		AdjacencyListHead * vertice = getVerticeByIndex(list, u);
		AdjacencyNode * v = vertice -> list;
	
		while (v) {
			if (v -> weight > 0) {
				int vIndex = verticeIndex(list, v -> name);
				if (color[vIndex] == 0) {
					color[vIndex] = 1;
					d[vIndex] = d[u] + 1;
					pred[vIndex] = u;
					insertQueue(q, vIndex);
				}
			}

			v = v -> next;
		}

		color[u] = 2;
	}

	for (int i = 0; i < list -> vCount; i++) {
		int cur = pred[i];
		if (cur == -1)
			continue;

		printf("%s -> ", getVerticeByIndex(list, i) -> name);
		while (cur != -1) {
			printf("%s -> ", getVerticeByIndex(list, cur) -> name);
			cur = pred[cur];
		}

		printf("end.\n");
	}	
}


void bellmanFord(AdjacencyList * list, char * f) {
	int * p = (int *) malloc(sizeof(int) * list -> vCount);
	for (int i = 0; i < list -> vCount; i++) {
		p[i] = -1;
	}

	int * d = (int *) malloc(sizeof(int) * list -> vCount);
	for (int i = 0; i < list -> vCount; i++) {
		d[i] = INT_MAX;
	}
	d[verticeIndex(list, f)] = 0;

	for (int i = 0; i < list -> vCount; i++) {
		AdjacencyListHead * head = list -> head;
		while (head) {

			AdjacencyNode * node = head -> list;
			while (node) {

				int to = verticeIndex(list, node -> name);
				int from = verticeIndex(list, head -> name);

				if (d[to] > d[from] + node -> weight) {
					d[to] = d[from] + node -> weight;
					p[to] = from;
				}
				
				node = node -> next;
			}
			
			head = head -> next;
		}
		
	}

	for (int i = 0; i < list -> vCount; i++) {
		AdjacencyListHead * head = list -> head;
		while (head) {
	
			AdjacencyNode * node = head -> list;
			while (node) {
	
				int to = verticeIndex(list, node -> name);
				int from = verticeIndex(list, head -> name);
	
				if (d[to] > d[from] + node -> weight) {
					printf("Negative weight cycle - aborting.\n");
					return;
				}
				
				node = node -> next;
			}
			
			head = head -> next;
		}
			
	}

	for (int i = 0; i < list -> vCount; i++) {
		printf("Shortest path from %s to %s costs %d.\n", f, getVerticeByIndex(list, i) -> name, d[i]);
		int cur = i;
		printf("END <- ");
		while (cur != -1) {
			printf("%s <- ", getVerticeByIndex(list, cur) -> name);
			cur = p[cur];
		}
		printf("START\n");
	}
}



int main(void) {
	char * s = readline();
	AdjacencyList * graph = importFromFile(s);
	outputAdjacencyList(graph);
	dotPrintGraph(graph, "graph.dot");
	bfsTask(graph, "Jessy");
	bellmanFord(graph, "Mike");
	return 0;
}
