#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXPATHLENGTH 100
#include "output.h"

void printPath(Graph* graph, DijkstraResult dijkstra)
{
    for(int i = 0; i < dijkstra.pathLength; i++)
    {
        printf("%s", graph->nodes[dijkstra.path[i]].name);
        if(i < dijkstra.pathLength - 1)
        {
            printf(" ---> ");
        }
    }
    printf("\n");
    printf("GesamtFahrzeit: %d min\n", dijkstra.totalCost);

}

void printLineChanges(Graph* graph, DijkstraResult dijkstra)
{

    char* currentline = NULL;

    for(int i = 0; i < dijkstra.pathLength-1; i++)
    {
        int from = dijkstra.path[i];
        int to = dijkstra.path[i+1];
        Edge* route = searchforEdge(graph, from, to);

        if(route == NULL)
        {
            continue;
        }
        if(currentline == NULL)
        {
            printf("Linie: %s\n", route->line);
        }
        else if(strcmp(currentline, route->line) != 0)
        {
            printf("%s : Linienwechsel von %s auf %s\n",
                   graph->nodes[from].name,
                   currentline,
                   route->line);
        }
        currentline = route->line;

    }
}

Edge* searchforEdge(Graph* graph, int from, int to)
{
    Edge* temp = graph->nodes[from].edges;

    while(temp != NULL)
    {
        if(temp->to == to)
        {
            //printf("Linie: %s\n", temp->line); nur Hilfsfunktion ohne Output
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}
