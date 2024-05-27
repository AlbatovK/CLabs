#include "graph.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "utils.h"

#include "queue.h" 

#define INT_MAX 1000 * 1000 * 10

void freeGraph(AdjacencyList * list) {

	if (list == NULL)
		return;

	AdjacencyListHead * head = list -> head;
	while (head) {

		AdjacencyNode * node = head -> list;
		while (node) {

			AdjacencyNode * nTmp = node;
			node = node -> next;
			free(nTmp -> name);
			free(nTmp);
		}
		
		AdjacencyListHead * tmp = head;
		head = head -> next;
		free(tmp -> name);
		free(tmp);
	}

	free(list);
}

AdjacencyNode * createAdjacencyNode(char * name, int weight) {
	AdjacencyNode * node = (AdjacencyNode *) malloc(sizeof(AdjacencyNode) * 1);
	node -> name = strdup(name);
	node -> weight = weight;
	node -> next = NULL;
	return node;
}

AdjacencyListHead * createAdjacencyListHead(char * headName) {
	AdjacencyListHead * head = (AdjacencyListHead *) malloc(sizeof(AdjacencyListHead) * 1);
	head -> list = NULL;
	head -> name = strdup(headName);
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

int addVertex(AdjacencyList * list, char * name) {

	if (list == NULL)
		return 0;

	AdjacencyListHead * head = list -> head;

	if (head == NULL) {
		list -> head = createAdjacencyListHead(name);
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
	
	head -> next = createAdjacencyListHead(name);
	list -> vCount++;
	return 1;
	
}

void freeAdjacencyNode(AdjacencyNode * node) {

	if (node == NULL)
		return;
		
	free(node -> name);
	free(node);
}

void deleteEdge(AdjacencyList * list, char * from, char * to) {

	if (list == NULL)
		return;

	AdjacencyNode * toFree = NULL;

	AdjacencyListHead * head = list -> head;
	while (head) {
		if (strcmp(head -> name, from) == 0) {
			AdjacencyNode * node = head -> list;
			AdjacencyNode * pred = NULL;
			while (node) {
				if (strcmp(node -> name, to) == 0) {
					if (pred == NULL) {
						head -> list = node -> next;
						toFree = node;
					} else {
						pred -> next = node -> next;
						toFree = node;
					}
				}

				pred = node;
				node = node -> next;
			}
		}

	    freeAdjacencyNode(toFree);
		toFree = NULL;

		if (strcmp(head -> name, to) == 0) {
			AdjacencyNode * node = head -> list;
			AdjacencyNode * pred = NULL;
			while (node) {
				if (strcmp(node -> name, from) == 0) {
					if (pred == NULL) {
						head -> list = node -> next;
						toFree = node;
					} else {
						pred -> next = node -> next;
						toFree = node;
					}
				}

				pred = node;
				node = node -> next;
			}
		}

	    freeAdjacencyNode(toFree);
		toFree = NULL;
		head = head -> next;
	}
}

void freeAdjacencyListHead(AdjacencyListHead * head) {

	if (head == NULL)
		return;

	AdjacencyNode * node = head -> list;
	while (node) {
		AdjacencyNode * tmp = node;
		node = node -> next;
		freeAdjacencyNode(tmp);
	}

	free(head -> name);
	free(head);
}

void deleteVertex(AdjacencyList * list, char * name) {

	if (list == NULL)
		return;

	AdjacencyListHead * head = list -> head;
	AdjacencyListHead * pred = NULL;
	AdjacencyListHead * toFree = NULL;
	while (head) {
		if (strcmp(head -> name, name) == 0) {
			if (pred == NULL) {
				toFree = list -> head;
				list -> head = head -> next;
				list -> vCount--;
			} else {
				pred -> next = head -> next;
				toFree = head;
				list -> vCount--;
			}
		} else {
			deleteEdge(list, head -> name, name);
		}
	
		pred = head;
		head = head -> next;
		freeAdjacencyListHead(toFree);
		toFree = NULL;
	}
}

int addEdge(AdjacencyList * list, char * from, char * to, int weight) {

	if (list == NULL || verticeIndex(list, from) == -1 || verticeIndex(list, to) == -1)
		return 0;

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
	printf("-------------------------\n");
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
	printf("-------------------------\n");
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
		free(line);
	}

	free(line);

	fclose(filePtr);

	return graph;
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

Queue * findShortestPath(AdjacencyList * list, char * f, char * t, int * res) {

	if (list == NULL || verticeIndex(list, f) == -1 || verticeIndex(list, t) == -1) {
		printf("Graph is not initialized or vertice is not present in graph.\n");
		return NULL;
	}

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
					return NULL;
				}
				
				node = node -> next;
			}
			
			head = head -> next;
		}
			
	}

	int toI = verticeIndex(list, t);
	* res = d[toI];
	if (* res == INT_MAX)
		return NULL;

	Queue * q = createQueue();


	int cur = toI;		
	while (cur != -1) {
		insertQueue(q, cur);
		cur = p[cur];	
	}

	free(d);
	free(p);

	return q;
}

void bfs(AdjacencyList * list, char * start) {

	if (list == NULL || verticeIndex(list, start) == -1) {
		printf("Graph is not initialized or vertice is not present in graph.\n");
		return;
	}

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

	if (list == NULL || verticeIndex(list, start) == -1) {
		printf("Graph is not initialized or vertice is not present in graph.\n");
		return;
	}

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

	eraseQueue(q);
	free(color);
	free(pred);
	free(d);	
}


void bellmanFord(AdjacencyList * list, char * f) {

	if (list == NULL || verticeIndex(list, f) == -1) {
		printf("Graph is not initialized or vertice is not present in graph.\n");
		return;
	}

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

	free(d);
	free(p);
	
}

int * * getMatrixFromAdjacencyList(AdjacencyList * list) {
	int * * matrix = (int * *) malloc(sizeof(int *) * list -> vCount);
	for (int i = 0; i < list -> vCount; i++) {
		matrix[i] = (int *) malloc(sizeof(int) * list -> vCount);
		for (int j = 0; j < list -> vCount; j++) {
			matrix[i][j] = INT_MAX;
		}
	}

	for (int i = 0; i < list -> vCount; i++) {
		AdjacencyListHead * head = getVerticeByIndex(list, i);
		AdjacencyNode * node = head -> list;
		while (node) {
			int j = verticeIndex(list, node -> name);
			matrix[i][j] = node -> weight;
			node = node -> next;
		}
	}

	return matrix;
}

AdjacencyListHead * floydWarshall(AdjacencyList * graph, char * name, int * res) {

	if (graph == NULL || verticeIndex(graph, name) == -1)
		return NULL;

	printf("Formed matrix: \n");
	int * * m = getMatrixFromAdjacencyList(graph);
	for (int i = 0; i < graph -> vCount; i++) {
		for (int j = 0; j < graph -> vCount; j++) {
			printf("%d\t", m[i][j] == INT_MAX ? 0 : m[i][j]);
		}
		printf("\n");
	}

	for (int k = 0; k < graph -> vCount; k++) {
		for (int i = 0; i < graph -> vCount; i++) {
			for (int j = 0; j < graph -> vCount; j++) {
				m[i][j] = m[i][j] > m[i][k] + m[k][j] ? m[i][k] + m[k][j] : m[i][j];
			}
		}
	}

	for (int i = 0; i < graph -> vCount; i++) {
		if (m[i][i] < 0) {
			for (int i = 0; i < graph -> vCount; i++) {
				free(m[i]);
			}
	
			free(m);
			return NULL;
		}
	}

	int max = -INT_MAX;
	int fromI = verticeIndex(graph, name);
	AdjacencyListHead * fMax = NULL;
	for (int i = 0; i < graph -> vCount; i++) {
		if (m[fromI][i] > max && m[fromI][i] != INT_MAX) {
			fMax = getVerticeByIndex(graph, i);
			max = m[fromI][i];
		}
	}

	*res = max;

	for (int i = 0; i < graph -> vCount; i++) {
		free(m[i]);
	}
	
	free(m);

	return fMax;
} 
