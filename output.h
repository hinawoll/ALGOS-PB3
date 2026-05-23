#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED
#include "dijkstra.h"
#include "graph.h"

Edge* searchforEdge(Graph* graph, int from, int to);
void printPath(Graph* graph, DijkstraResult dijkstra);
void printLineChanges(Graph* graph, DijkstraResult dijkstra);


#endif // OUTPUT_H_INCLUDED
