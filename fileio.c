#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileio.h"
#include "graph.h"

#define MAX_LINE 1024

Graph* readGraphFile(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }

    Graph* graph = createGraph(100);//100->capacity

    char line[MAX_LINE];

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);

    return graph;
}