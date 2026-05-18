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

### Funktionen

```c id="o59p04"
Graph* createGraph();
Node* addNode(Graph* graph, char* stationName);
void addEdge(Graph* graph, char* from, char* to, int cost, char* line);
Node* findNode(Graph* graph, char* stationName);

void readGraphFile(char* filename, Graph* graph);
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

### Funktionen

```c id="9j50fz"
void dijkstra(Graph* graph, char* start, char* target);
Node* getShortestDistanceNode(Graph* graph);
void updateDistances(Node* current);
void reconstructPath(Node* target);
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
* `main.c`
* `test.c`

### Funktionen

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
typedef struct Edge {
    int to;
    int cost;
    char line[50];
    struct Edge* next;
} Edge;

typedef struct Node {
    char name[100];
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

## 4. Modulaufteilung

Zum Beispiel:

```text
graph.h / graph.c
parser.h / parser.c
dijkstra.h / dijkstra.c
output.h / output.c
main.c
```
