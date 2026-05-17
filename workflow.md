## Sicherer Workflow für die Teamarbeit

### 1. main-Branch aktualisieren
```bash
git checkout main
git pull
````

### 2. In den eigenen Branch wechseln und main mergen

```bash
git checkout branchname
git merge main
```

### 3. Arbeiten

Code schreiben / Änderungen vornehmen

### 4. Änderungen hinzufügen und committen

```bash
git add .
git commit -m "Beschreibung der Änderungen"
```

### 5. Änderungen pushen

```bash
git push
```

### 6. Vor dem Pull Request erneut synchronisieren

```bash
git checkout main
git pull
git checkout branchname
git merge main
git push
```

### 7. Pull Request erstellen und mergen

Merge nur durchführen, wenn keine Konflikte vorhanden sind
