## Commands ##
 
  ```c
gcc main.c graph.c fileio.c dijkstra.c output.c -o find_path
  ```

*case1: von Karlsplatz bis Praterstern
  ```c
./find_path wien.txt Karlsplatz Praterstern
  ```
```c
find_path.exe wien.txt Karlsplatz Praterstern
```

* dann soll die Ausgebe so sein:
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

Total cost: 5
```
