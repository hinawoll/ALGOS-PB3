#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "fileio.h"
// später:
// #include "dijkstra.h"
// #include "output.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Bitte geben Sie so ein: %s filename_graph start ziel\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];//z.B. wien.txt
    char* startName = argv[2];//z.B.Karlsplatz
    char* targetName = argv[3];//z.B.Praterstern

    //ein Graph erstellen
    //Zeile für Zeile einlesen und in line[] speichen
    Graph* graph = readGraphFile(filename);

    if (graph == NULL) {
        printf("Error: Could not read graph file.\n");
        return 1;
    }

    Node* startNode = findNode(graph, startName);
    Node* targetNode = findNode(graph, targetName);

    if (startNode == NULL) {
        printf("Error: Start station '%s' not found.\n", startName);
        freeGraph(graph);
        return 1;
    }

    if (targetNode == NULL) {
        printf("Error: Target station '%s' not found.\n", targetName);
        freeGraph(graph);
        return 1;
    }

    printf("Graph successfully loaded.\n");
    printf("Start: %s\n", startName);
    printf("Target: %s\n", targetName);

    // Nur zum Testen / Debugging:
    printGraph(graph);

    /*
    Später kommt hier Dijkstra rein, z.B.:

    int startIndex = getNodeIndex(graph, startName);
    int targetIndex = getNodeIndex(graph, targetName);

    dijkstra(graph, startIndex, targetIndex);
    printPath(graph, startIndex, targetIndex);
    */

    freeGraph(graph);

    return 0;
}