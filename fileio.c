#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileio.h"
#include "graph.h"

#define MAX_LINE 10000

//am Anfang zeigt p auf das Leerzeichen nach dem Liniennamen und dem Doppelpunkt der Zeile
static char* readStation(char* p, char* station) {
    while (*p == ' ') {
        p++;
    }

    if (*p != '"') {
        return NULL;//da ein StationName immer mit Anfühungsyeichen beginnt
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
        return NULL;//da ein StationName immer mit Anfühungszeichen beendet
    }

    p++;

    return p;//zeigt auf das Leerzeichen nachdem StationName und dem zweiten Anfühungszeichen
}

//Ablauf
//wien.txt lesen
//→ Aus jeder Zeile den Namen der Linie auslesen
//→ Bahnhofsnamen und Kosten nacheinander auslesen
//→ Knoten und Kanten zum Graphen hinzufügen
Graph* readGraphFile(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }

    Graph* graph = createGraph(1000);//1000->capacity

    char line[MAX_LINE];//ein char-Array für die aktuelle Zeile in wien.txt

    while (fgets(line, sizeof(line), file)) {//Zeile für Zeile einlesen und in line[] speichen
        char lineName[MAX_LINE_LENGTH];//z.B. U1, U2, 5, D...

        char* colon = strchr(line, ':');//":" suchen
        if (colon == NULL) {
            continue;
        }

        int lineLength = colon - line;//in den Fall mit "U2", lineLength = 2
        strncpy(lineName, line, lineLength);
        lineName[lineLength] = '\0';

        char* p = colon + 1;//p zeigt auf das Leerzeichen nach dem Doppelpunkt

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

            //beide Richtung
            addEdge(graph, from, to, cost, lineName);
            addEdge(graph, to, from, cost, lineName);

            strcpy(previousStation, currentStation);
        }
    }

    fclose(file);
    return graph;
}