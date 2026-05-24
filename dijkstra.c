#include "dijkstra.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
//-1 markiert unendliche Distanz zwischen zwei Nodes

DijkstraResult dijkstra(Graph* graph, int start, int target)
{
    DijkstraResult result;
    result.path = NULL;
    result.pathLength = 0;
    result.totalCost = -1;

    //edge cases
    if (graph == NULL || graph->nodeCount == 0) return result;
    if(start < 0 || target < 0 || start >= graph->nodeCount || target >= graph->nodeCount) return result;

    //initialisierungen
    int dist[graph->nodeCount];
    int visited[graph->nodeCount];
    int prev[graph->nodeCount];
    int* path = malloc(sizeof(int) * graph->nodeCount);
    if (path == NULL) return result;
    int current = -1;
    for (int i = 0; i < graph->nodeCount; i++)  //alle arrays füllen
    {
        dist[i] = -1;
        visited[i] = 0;
        prev[i] = -1;
    }

    //dijkstra start
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
        free(path);
        return result;
    }

    //Pfad rekonstruieren und Rückgabe vorbereiten
    int pathLength = reconstructPath(prev, start, target, path);
    result.path = path;
    result.pathLength = pathLength;
    result.totalCost = dist[target];
    return result;
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

int reconstructPath(int prev[], int start, int target, int path[])
{
    int length = 0;
    int current = target;
    while (current != -1)
    {
        path[length] = current;
        length++;

        if (current == start) break;

        current = prev[current];
    }
    if (path[length-1] != start) return 0; //wenn Start nicht erreicht wurd

    //Pfad umdrehen
    for (int i = 0; i < length/2; i++)
    {
        int temp = path[i];
        path[i] = path[length - 1 - i];
        path[length - 1 - i] = temp;
    }
    return length;
}