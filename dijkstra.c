//du kannst die Funktion "getNodeIndex" aus graph.h/.c hier so z.B. verwenden
// int startIndex = getNodeIndex(graph, startName);
// int targetIndex = getNodeIndex(graph, targetName);
#include "dijkstra.h";
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
//-1 markiert unendliche Distanz zwischen zwei Nodes

void dijkstra(Graph* graph, int start, int target)
{
    if (graph == NULL || graph->nodeCount == 0) return;
    int dist[graph->nodeCount];
    int visited[graph->nodeCount];
    int prev[graph->nodeCount];
    int path[graph->nodeCount];
    int current = -1;
    for (int i = 0; i < graph->nodeCount; i++)  //alle arrays füllen
    {
        dist[i] = -1;
        visited[i] = 0;
        prev[i] = -1;
    }
    dist[start] = 0;
    while (1)
    {
        current = getMinDistanceNode(dist, visited, graph->nodeCount);
        if (current < 0) break;
        visited[current] = 1;
        if (current == target) break;
        updateDistances(graph, current, dist, prev, visited);
    }
    if (dist[target] == -1)
    {
        printf("Path not possible");
        return;
    }
    int pathLength = reconstructPath(prev, start, target, path);
}

int getMinDistanceNode(int dist[], int visited[], int nodeCount)
{
    int min = INT_MAX;
    int minIndex = -1;
    int i = 0;
    for (; i < nodeCount; i++)
    {
        if (dist[i] >= 0 && dist[i] < min && visited[i] == 0)
        {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void updateDistances(Graph* graph, int current, int dist[], int prev[], int visited[])
{
    Edge* currentEdge = graph->nodes[current].edges;
    while (currentEdge != NULL)
    {
        int neighbour = currentEdge->to;
        int newDistance = dist[current] + currentEdge->cost;
        if (visited[neighbour] != 1 && (dist[neighbour] < 0 || (dist[neighbour] > newDistance)))    //wenn dist < 0, dann noch unbekannt
        {
            prev[neighbour] = current;
            dist[neighbour] = newDistance;
        }
        currentEdge = currentEdge->next;
    }
}

int reconstructPath(int prev[], int start,int target, int path[])
{

}