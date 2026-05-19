# Rollenaufteilung und Archtektur

## Hina — Datei & Graphaufbau

### Aufgaben

* Input-Datei einlesen
* Parser für das Dateiformat implementieren
* Stationen und Linien verarbeiten
* Graph-Datenstruktur erstellen
* Knoten und Kanten speichern
* Hilfsfunktionen für den Graphen implementieren

### Dateien

* `graph.c`
* `graph.h`
* `fileio.c`
* `fileio.h`

### Funktionen in graph.h

```c id="o59p04"
Graph* createGraph(int capacity);
void freeGraph(Graph* graph);
Node* findNode(Graph* graph, const char* stationName);
Node* addNode(Graph* graph, const char* stationName);
void addEdge(Graph* graph, int from, int to, int cost, const char* line);

//zum Debugging
void printGraph(Graph* graph);
```

### Funktionen in fileio.h

```c id="o59p04"
Graph* readGraphFile(const char* filename);
```

---

## Sophia — Shortest-Path-Algorithmus

### Aufgaben

* Dijkstra-Algorithmus implementieren
* Distanzverwaltung
* Besuchte Knoten verwalten
* Vorgänger speichern
* Kürzesten Pfad rekonstruieren
* Fehlerfälle behandeln

### Dateien

* `dijkstra.c`
* `dijkstra.h`

### Funktionen (Beispiel)

```c id="9j50fz"
void dijkstra(Graph* graph, int start, int target);
int getMinDistanceNode(
    int dist[],
    int visited[],
    int nodeCount
);
void updateDistances(
    Graph* graph,
    int current,
    int dist[],
    int prev[],
    int visited[]
);
void reconstructPath(
    int prev[],
    int start,
    int target
);
```

---

## Michael — Linienlogik, Output & Tests

### Aufgaben

* Linienwechsel erkennen
* Übersichtliche Ausgabe erzeugen
* Gesamtkosten berechnen
* Testfälle erstellen
* Debugging unterstützen
* Integration der Module
* Verarbeitung der Kommandozeilenargumente implementieren

### Dateien

* `output.c`
* `output.h`
* `test.c`(optional)

### Funktionen (Beispiel)

```c id="tklgdc"
void printPath(Path* path);
void printLineChanges(Path* path);
int calculateTotalCost(Path* path);

void parseArguments(int argc, char* argv[]);
void runTests();
```

---

# die Schnittstellen und Datenstrukturen 

## 1. Datenstruktur


```c
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
```

Also: **Adjazenzliste**, nicht Adjazenzmatrix.
Das ist für Verkehrsnetze praktischer, weil nicht jede Station mit jeder anderen verbunden ist.

## 2. Stations-IDs

Intern sollte jede Station eine Nummer bekommen:

```text
"Karlsplatz" -> 0
"Stephansplatz" -> 1
"Schwedenplatz" -> 2
```

Dann kann Dijkstra leichter mit Arrays arbeiten:

```c
int dist[nodeCount];
int prev[nodeCount];
int visited[nodeCount];
```

## 3. Richtung der Kanten

Bei U-Bahn/Straßenbahn ist die Verbindung normalerweise in beide Richtungen nutzbar.

Wenn in der Datei steht:

```text
"A" 3 "B"
```

dann speichert ihr:

```text
A -> B Kosten 3
B -> A Kosten 3
```
