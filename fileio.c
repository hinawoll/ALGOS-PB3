#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileio.h"
#include "graph.h"

#define MAX_LINE 1024

Graph* readGraphFile(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }

    Graph* graph = createGraph(100);//100->capacity

    char line[MAX_LINE];//eine Zeile von wien.txt

    while (fgets(line, sizeof(line), file)) {//Zeile für Zeile einlesen und in line[] speichen
        char lineName[MAX_LINE_LENGTH];

        char* colon = strchr(line, ':');
        if (colon == NULL) {
            continue;
        }

        int lineLength = colon - line;
        //lineName nach line kopieren
        strncpy(lineName, line, lineLength);
        lineName[lineLength] = '\0';

        char* p = colon + 1;

        char station1[MAX_NAME_LENGTH];
        char station2[MAX_NAME_LENGTH];
        int cost;

        while (sscanf(p, " \"%[^\"]\" %d \"%[^\"]\"", station1, &cost, station2) == 3) {
            Node* node1 = findNode(graph, station1);
            if (node1 == NULL) {
                node1 = addNode(graph, station1);
            }

            Node* node2 = findNode(graph, station2);
            if (node2 == NULL) {
                node2 = addNode(graph, station2);
            }

            int from = getNodeIndex(graph, station1);
            int to = getNodeIndex(graph, station2);

            //da jede Kante ungerichtet sind
            addEdge(graph, from, to, cost, lineName);
            addEdge(graph, to, from, cost, lineName);

            char* nextStation = strstr(p + 1, station2);
            if (nextStation == NULL) {
                break;
            }

            p = nextStation + strlen(station2) + 1;
        }
    }

    fclose(file);

    return graph;
}