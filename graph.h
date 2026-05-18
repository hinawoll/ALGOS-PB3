#ifndef PB3_GRAPH_H
#define PB3_GRAPH_H

Graph* createGraph();
Node* addNode(Graph* graph, char* stationName);
void addEdge(Graph* graph, char* from, char* to, int cost, char* line);
Node* findNode(Graph* graph, char* stationName);

#endif //PB3_GRAPH_H