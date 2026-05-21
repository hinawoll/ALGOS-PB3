## Commands ##
 
  ```c
gcc main.c graph.c fileio.c dijkstra.c output.c -o find_path
  ```

*Bsp1: ohne Umsteigen (von Karlsplatz bis Praterstern)
  ```c
./find_path wien.txt Karlsplatz Praterstern
  ```
```c
find_path.exe wien.txt Karlsplatz Praterstern
```

* erwartete Ausgebe:
```c
Graph successfully loaded.

Start: Karlsplatz
Target: Praterstern

Shortest path:

Karlsplatz
-> Stephansplatz (U1, 2 min)
-> Schwedenplatz (U1, 1 min)
-> Nestroyplatz (U1, 1 min)
-> Praterstern (U1, 1 min)

Total cost: 5 min
```

*Bsp2: mit Umsteigen (von Karlsplatz bis Westbahnhof)
  ```c
./find_path wien.txt Karlsplatz Westbahnhof
  ```
```c
find_path.exe wien.txt Karlsplatz Westbahnhof
```

* erwartete Ausgebe:
```c
Graph successfully loaded.

Start: Karlsplatz
Target: Westbahnhof

Shortest path:

Karlsplatz
-> Museumsquartier (U2, 1 min)
-> Volkstheater (U2, 1 min)

Change at Volkstheater: U2 -> U3

Volkstheater
-> Neubaugasse (U3, 2 min)
-> Zieglergasse (U3, 1 min)
-> Westbahnhof (U3, 1 min)

Total cost: 6 min
```