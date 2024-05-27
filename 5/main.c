#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "utils.h"

#include <time.h>

#include "queue.h"

#include "graph.h"

#define ACTION_EXIT 1

#define ACTION_ADD_VRT 2

#define ACTION_ADD_EDG 3

#define ACTION_DEL_V 4

#define ACTION_DEL_E 5

#define ACTION_OUT 6

#define ACTION_DOT 7

#define ACTION_BFS 8

#define ACTION_IND_SHORTEST 9

#define ACTION_VERTEX_FLOYD 10

#define ACTION_IMPORT 11

#define GEN_SIZE 300

void generateRandom() {
	srand(time(0));
	FILE * file = fopen("names.txt", "r");
	char * names[1000];

	char * line;
	int i = 0;
	while (strlen((line = file_readline(file)))) {

		char * dup = (char *) malloc(sizeof(char) * strlen(line));
		for (int i = 0; i < (int) strlen(line); i++) {
			dup[i] = line[i];
		}

		dup[strlen(line) - 1] = '\0';
		
		names[i] = dup;
		i++;
		free(line);
	}
	
	free(line);	

	fclose(file);

	file = fopen("generated.csv", "w");

	for (int i = 0; i < GEN_SIZE; i++) {
		int j = rand() % GEN_SIZE;
		int k = rand() % GEN_SIZE;

		int w = rand() % 10;

		fprintf(file, "%s;%s;%d\n", names[j], names[k], w);		
		
	}

	fclose(file);

	for (int i = 0; i < 1000; i++) {
		free(names[i]);
	}

}


int main(void) {

	generateRandom();

	AdjacencyList * graph = createAdjacencyList();
	int action = 0;
	while (action != ACTION_EXIT) {
		printf("Enter action.\n");
		printf("%d - exit, %d - add vertex, %d - add edge, %d - import from file.\n", ACTION_EXIT, ACTION_ADD_VRT, ACTION_ADD_EDG, ACTION_IMPORT);
		printf("%d - delete vertex, %d - delete edge, %d - output graph, %d - write to dot\n", ACTION_DEL_V, ACTION_DEL_E, ACTION_OUT, ACTION_DOT);
		printf("%d - Special Breadth-First Search (find chains from person with positive weight).\n", ACTION_BFS);
		printf("%d - Special Bellman-Ford (find chain between two people with minimal weight).\n", ACTION_IND_SHORTEST);
		printf("%d - Special Floyd-Warshall (find person with maximum chain weight from another person).\n", ACTION_VERTEX_FLOYD);

		char * pr = "";
		do {
			printf("%s", pr);
			getInt(&action);
			pr = "No such action. Try again.\n";
		} while (action < 1 || action > 11);

		switch(action) {

			case ACTION_EXIT:
				freeGraph(graph);
				break;

			case ACTION_ADD_VRT:
				printf("Enter vertex to add:\n");
				char * vertexToAdd = readline();
				int res = addVertex(graph, vertexToAdd);
				free(vertexToAdd);
				if (res) {
					printf("Successfully added new vertex.\n");
				} else {
					printf("Vertex already exists.\n");
				}
				
				break;

			case ACTION_ADD_EDG:
				printf("Enter `from` vertex:\n");
				char * fromV = readline();
				printf("Enter `to` vertex:\n");
				char * toV = readline();
				printf("Enter weight (-10 - 10): ");
				int w;
				scanf("%d", &w);
				int r = addEdge(graph, fromV, toV, w);
				if (r) {
					printf("Successfully added edge.\n");
				} else {
					printf("Vertecies do not exist.\n");
				}
				
				free(fromV);
				free(toV);
				break;

			case ACTION_OUT:
				outputAdjacencyList(graph);
				break;

			case ACTION_IMPORT:
				printf("Enter file name: \n");
				char * fileName = readline();
				AdjacencyList * list = importFromFile(fileName);
				if (list == NULL) {
					printf("Unable to import.\n");
					free(fileName);
					break;
				}

				freeGraph(graph);
				graph = list;
				free(fileName);
				break;

			case ACTION_DEL_V:
				printf("Enter vertex to delete: ");
				char * vertexToDelete = readline();
				deleteVertex(list, vertexToDelete);
				free(vertexToDelete);
				break;

			case ACTION_DEL_E:
				printf("Enter `from` vertex: ");
				char * fromD = readline();
				printf("Enter `to` vertex: ");
				char * fromT = readline();
				deleteEdge(list, fromD, fromT);	
				free(fromD);
				free(fromT);
				break;
				
			case ACTION_DOT:
				printf("Enter dot file name: ");
				char * dotName = readline();
				dotPrintGraph(list, dotName);
				printf("Wrote to file.\n");
				free(dotName);
				break;

			case ACTION_BFS:
				printf("Enter person to search from: ");
				char * pName = readline();
				bfsTask(graph, pName);
				free(pName);
				break;

			case ACTION_VERTEX_FLOYD:
				printf("Enter name: \n");
				char * flName = readline();
				int fRes = 0;
				AdjacencyListHead * head = floydWarshall(graph, flName, &fRes);
				if (head == NULL) {
					printf("Negative cycles or graph is empty or no edges.\n");
				} else {
					printf("Found vertex with name: %s and chain sum: %d.\n", head -> name, fRes);
				}
				free(flName);
				break;

			case ACTION_IND_SHORTEST:
				printf("Enter names of people to find shortest path: \n");
				char * first = readline();
				char * second = readline();
				int sum = 0;
				bellmanFord(graph, first);
				Queue * q = findShortestPath(graph, first, second, &sum);
				if (q == NULL) {
					printf("Cannot build path - negative cycles or no way.\n");
				} else {
					printf("Found path with sum: %d\n", sum);
					printf("end <- ");
					while (queueSize(q) != 0) {
						int i = popQueue(q);
						AdjacencyListHead * head = getVerticeByIndex(graph, i);
						printf("%s <- ", head -> name);
					}
					printf("start.\n");
					eraseQueue(q);
				}
				
				free(first);
				free(second);
				break;
		}
	}
}
