#ifndef PB3_GRAPH_H
#define PB3_GRAPH_H

#define MAX_NAME_LENGTH 100
#define MAX_LINE_LENGTH 50

typedef struct Edge {
    int to;
    int cost;
    char line[MAX_LINE_LENGTH];
    struct Edge* next;
} Edge;

typedef struct Node {
    char name[MAX_NAME_LENGTH];
    Edge* edges;
} Node;

typedef struct Graph {
    Node* nodes;
    int nodeCount;
    int capacity;
} Graph;


Graph* createGraph(int capacity);

void freeGraph(Graph* graph);

Node* findNode(Graph* graph, const char* stationName);

Node* addNode(Graph* graph, const char* stationName);

void addEdge(Graph* graph, int from, int to, int cost, const char* line);

int getNodeIndex(Graph* graph, const char* stationName);


//zum Debugging
void printGraph(Graph* graph);


#endif //PB3_GRAPH_H