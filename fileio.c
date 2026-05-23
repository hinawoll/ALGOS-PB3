#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileio.h"
#include "graph.h"

#define MAX_LINE 10000

static char* readStation(char* p, char* station) {
    while (*p == ' ') {
        p++;
    }

    if (*p != '"') {
        return NULL;
    }

    p++;

    int i = 0;
    while (*p != '"' && *p != '\0' && i < MAX_NAME_LENGTH - 1) {
        station[i] = *p;
        i++;
        p++;
    }

    station[i] = '\0';

    if (*p != '"') {
        return NULL;
    }

    p++;

    return p;
}

Graph* readGraphFile(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }

    Graph* graph = createGraph(1000);//1000->capacity

    char line[MAX_LINE];//ein Array für Zeilen in wien.txt

    while (fgets(line, sizeof(line), file)) {//Zeile für Zeile einlesen und in line[] speichen
        char lineName[MAX_LINE_LENGTH];

        char* colon = strchr(line, ':');
        if (colon == NULL) {
            continue;
        }

        int lineLength = colon - line;
        strncpy(lineName, line, lineLength);
        lineName[lineLength] = '\0';

        char* p = colon + 1;

        char previousStation[MAX_NAME_LENGTH];
        char currentStation[MAX_NAME_LENGTH];
        int cost;

        p = readStation(p, previousStation);
        if (p == NULL) {
            continue;
        }

        if (findNode(graph, previousStation) == NULL) {
            addNode(graph, previousStation);
        }

        while (sscanf(p, " %d", &cost) == 1) {
            while (*p == ' ') {
                p++;
            }

            while (*p >= '0' && *p <= '9') {
                p++;
            }

            p = readStation(p, currentStation);
            if (p == NULL) {
                break;
            }

            if (findNode(graph, currentStation) == NULL) {
                addNode(graph, currentStation);
            }

            int from = getNodeIndex(graph, previousStation);
            int to = getNodeIndex(graph, currentStation);

            addEdge(graph, from, to, cost, lineName);
            addEdge(graph, to, from, cost, lineName);

            strcpy(previousStation, currentStation);
        }
    }

    fclose(file);
    return graph;
}