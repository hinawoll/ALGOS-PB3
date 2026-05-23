#ifndef ALGOS_PB3_DIJKSTRA_H
#define ALGOS_PB3_DIJKSTRA_H
#include "graph.h"

void dijkstra(Graph* graph, int start, int target);
int getMinDistanceNode(int dist[], int visited[], int nodeCount);
void updateDistances(Graph* graph, int current, int dist[], int prev[], int visited[]);
int reconstructPath(int prev[], int start,int target, int path[]);

#endif //ALGOS_PB3_DIJKSTRA_H