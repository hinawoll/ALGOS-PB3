#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

//ein Graph erstellen
//ohne Knoten, aber mit Speicherplatz für 1000 Knoten
Graph* createGraph(int capacity) {//capacity ist in fileio.c als 1000 definiert
    Graph* graph = malloc(sizeof(Graph));

    if (graph == NULL) {
        return NULL;
    }

    //Es wird Speicherplatz für 1000 Knoten reserviert
    //*nodes zeigt die erste adresse auf
    //*nodes ist ein Array = nodes[0], nodes[1], nodes[2]
    //um bei Dijkstra auf die Knoten effektiv zugreifen zu können
    graph->nodes = malloc(sizeof(Node) * capacity);

    if (graph->nodes == NULL) {
        free(graph);
        return NULL;
    }

    graph->nodeCount = 0;
    graph->capacity = capacity;

    return graph;
}

void freeGraph(Graph* graph) {
    if (graph == NULL) {
        return;
    }

    for (int i = 0; i < graph->nodeCount; i++) {
        Edge* current = graph->nodes[i].edges;

        while (current != NULL) {
            Edge* next = current->next;
            free(current);
            current = next;
        }
    }

    free(graph->nodes);
    free(graph);
}


//einen Knoten ohne kante erstellen
Node* addNode(Graph* graph, const char* stationName) {
    if (graph == NULL || stationName == NULL) {
        return NULL;
    }

    if (graph->nodeCount >= graph->capacity) {
        printf("Error: Graph capacity reached.\n");
        return NULL;
    }

    Node* node = &graph->nodes[graph->nodeCount];//(wenn nodeCount = 0, node = &graph->nodes[0] )

    //stationName nach node->name kopieren
    strncpy(node->name, stationName, MAX_NAME_LENGTH - 1);
    node->name[MAX_NAME_LENGTH - 1] = '\0';//am Ende ist 0
    node->edges = NULL;

    graph->nodeCount++;

    return node;
}

//eine Kante erstellen
void addEdge(Graph* graph, int from, int to, int cost, const char* line) {
    if (graph == NULL || line == NULL) {
        return;
    }

    if (from < 0 || to < 0 || from >= graph->nodeCount || to >= graph->nodeCount) {
        return;
    }

    Edge* edge = malloc(sizeof(Edge));

    if (edge == NULL) {
        return;
    }

    edge->to = to;
    edge->cost = cost;

    //line nach edge->line kopieren
    strncpy(edge->line, line, MAX_LINE_LENGTH - 1);
    edge->line[MAX_LINE_LENGTH - 1] = '\0';

    edge->next = graph->nodes[from].edges;
    graph->nodes[from].edges = edge;
}

Node* findNode(Graph* graph, const char* stationName) {
    if (graph == NULL || stationName == NULL) {
        return NULL;
    }

    for (int i = 0; i < graph->nodeCount; i++) {
        //String vergleichen und wenn zusammenpassen, den Stationsnamen zurückgeben
        if (strcmp(graph->nodes[i].name, stationName) == 0) {
            return &graph->nodes[i];
        }
    }

    return NULL;
}


int getNodeIndex(Graph* graph, const char* stationName) {
    if (graph == NULL || stationName == NULL) {
        return -1;
    }

    for (int i = 0; i < graph->nodeCount; i++) {
        if (strcmp(graph->nodes[i].name, stationName) == 0) {
            return i;
        }
    }

    return -1;
}

//zum debugging. alle Stationen und alle Verbindungen werden ausgegeben
void printGraph(Graph* graph) {
    if (graph == NULL) {
        return;
    }

    for (int i = 0; i < graph->nodeCount; i++) {
        printf("%s:\n", graph->nodes[i].name);

        Edge* current = graph->nodes[i].edges;

        while (current != NULL) {
            printf("  -> %s (%s, %d)\n",
                   graph->nodes[current->to].name,
                   current->line,
                   current->cost);

            current = current->next;
        }
    }
}