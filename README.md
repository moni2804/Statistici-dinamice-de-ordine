### Arbore de Statistică de Ordine
----
### Descriere
Acest proiect implementează un **arbore de statistică de ordine** utilizând un **arbore binar de căutare echilibrat**. Fiecare nod conține un câmp `size`, reprezentând dimensiunea sub-arborelui său.

## Operații Implementate

### 1. BUILD_TREE(n)
- Construiește un arbore echilibrat cu cheile `{1, 2, ..., n}` folosind metoda **divide et impera**.
- **Complexitate:** `O(n)`

### 2. OS-SELECT(tree, i)
- Returnează elementul cu a `i`-a cea mai mică cheie.
- **Complexitate:** `O(log n)` pentru un arbore echilibrat.

### 3. OS-DELETE(tree, i)
- Șterge elementul fără a dezechilibra arborele, actualizând corect `size`.
- **Complexitate:** `O(log n)` pentru un arbore echilibrat, dar poate ajunge la `O(n)` în cel mai rău caz (arbore complet dezechilibrat).

## Cerințe
### 1. Afișarea arborelui pentru `n = 11`.
### 2. Testarea **OS-SELECT** pe cel puțin 3 valori aleatorii.
### 3. Testarea **OS-DELETE** după fiecare **OS-SELECT** pentru 3 valori.
### 4. Evaluarea performanței pentru `n ∈ [100, 10000]` cu analiza operațiilor (BUILD, SELECT, DELETE) și reprezentare grafică.
