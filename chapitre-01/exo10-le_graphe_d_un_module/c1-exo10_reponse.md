 Analyse complète du fichier `.jenga` du projet **NKCanvas**,  a realiser  sous forme de rapport d'architecture et graphe de dépendances.

---

# Analyse des dépendances de NKCanvas

Ce document présente les dépendances directes et sous-jacentes du projet **NKCanvas**, ainsi qu'un graphe textuel sur deux niveaux d'immersion et l'ordre de compilation requis.

## . commande de compilation et resultat:
```bash
jenga build --target NKCanvas
```

```bash
╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.4.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (17 projects):
  1. NKPlatform [STATIC_LIB] → 
  2. NKGlad [STATIC_LIB] → 
  3. NKCore [STATIC_LIB] (depends: NKPlatform) → 
  4. NKMemory [STATIC_LIB] (depends: NKCore, NKPlatform) → 
  5. NKContainers [STATIC_LIB] (depends: NKCore, NKMemory, NKPlatform) → 
  6. NKThreading [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform) → 
  7. NKMath [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform) → 
  8. NKLogger [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform, NKThreading) → 
  9. NKFileSystem [STATIC_LIB] (depends: NKContainers, NKCore, NKLogger, NKMemory, NKPlatform, NKThreading) → 
  10. NKTime [STATIC_LIB] (depends: NKContainers, NKCore, NKLogger, NKMemory, NKPlatform, NKThreading) → 
  11. NKFont [STATIC_LIB] (depends: NKContainers, NKCore, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading) → 
  12. NKStream [STATIC_LIB] (depends: NKContainers, NKCore, NKFileSystem, NKLogger, NKMemory, NKPlatform, NKThreading) → 
  13. NKEvent [STATIC_LIB] (depends: NKContainers, NKCore, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading, NKTime) → 
  14. NKImage [STATIC_LIB] (depends: NKContainers, NKCore, NKFileSystem, NKLogger, NKMath, NKMemory, NKPlatform, NKStream, NKThreading) → 
  15. NKWindow [STATIC_LIB] (depends: NKContainers, NKCore, NKEvent, NKFileSystem, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading, NKTime) → 
  16. NKUI [STATIC_LIB] (depends: NKContainers, NKCore, NKEvent, NKFileSystem, NKFont, NKImage, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading) → 
  17. NKCanvas [STATIC_LIB] (depends: NKContainers, NKCore, NKEvent, NKFileSystem, NKFont, NKGlad, NKImage, NKLogger, NKMath, NKMemory, NKPlatform, NKStream, NKThreading, NKTime, NKUI, NKWindow)


 

```
## . Dépendances Directes 


### 1. Analyse des Dépendances Directes (Niveau 1)

Dans le fichier script `NKCanvas.jenga`, la déclaration de dépendances s'effectue dynamiquement via la liste `_canvasDeps` :

```python
_canvasDeps = ["NKWindow", "NKFont", "NKImage", "NKStream", "NKTime", "NKGlad", "NKThreading"]

if USE_CANVAS_NKUI:
    _canvasDeps.append("NKUI")

```

#### Résultat :

* **Dépendances de base (7 modules) :** `NKWindow`, `NKFont`, `NKImage`, `NKStream`, `NKTime`, `NKGlad`, `NKThreading`.
* **Dépendance conditionnelle (1 module) :** `NKUI` (ajoutée uniquement si le flag `USE_CANVAS_NKUI` est activé).
* **Dépendances système/externe (Inline/Link) :**




---

### 2. Différence constatée entre le journal de Build (17 projets) et le script Jenga

* **Journal de build global :** Listait **16 dépendances directes** car le système de résolution à plat ,  Jenga remonte et fusionne toutes les sous-dépendances des sous-systèmes (ex: `NKContainers`, `NKCore`, `NKMemory`, `NKPlatform`, `NKMath`, `NKLogger`, `NKFileSystem`, `NKEvent`).
* **Script `NKCanvas.jenga` :** Déclare explicitement **7 dépendances fondamentales (ou 8 si `USE_CANVAS_NKUI` est vrai)**. Le reste des briques (`NKCore`, `NKMemory`, etc.) est hérité transitivement par `nkentseudependson()`.

---


```markdown


## 3. Dépendances Directes (Niveau 1)

### A. Déclarées explicitement dans `NKCanvas.jenga` (7 à 8 modules) avec leur role observer dans les differnt fichier
1. **`NKWindow`** — Fenêtrage et contextes de rendu
2. **`NKFont`** — Rendu et métriques de polices
3. **`NKImage`** — Décodage et gestion des textures/images
4. **`NKStream`** — Entrées/sorties et flux de données
5. **`NKTime`** — Gestion du temps et des chronomètres
6. **`NKGlad`** — Layer/Loader OpenGL
7. **`NKThreading`** — Gestion du multithreading
8. **`NKUI`** *(Conditionnel via `USE_CANVAS_NKUI=True`)*


---

## 3. Dépendances Indirectes Transitives (Niveau 2)

Les modules de base sont hérités automatiquement par l'intermédiaire des dépendances directes :
```
| Dépendance Directe (N1) | Sous-dépendances Transitives (N2) |
|---|--|
| **`NKWindow`** | `NKContainers`, `NKCore`, `NKEvent`, `NKFileSystem`, `NKLogger`, `NKMath`, `NKMemory`, `NKPlatform`, `NKThreading`, `NKTime` |
| **`NKFont`** | `NKContainers`, `NKCore`, `NKLogger`, `NKMath`, `NKMemory`, `NKPlatform`, `NKThreading` |
| **`NKImage`** | `NKContainers`, `NKCore`, `NKFileSystem`, `NKLogger`, `NKMath`, `NKMemory`, `NKPlatform`, `NKStream`, `NKThreading` |
| **`NKStream`** | `NKContainers`, `NKCore`, `NKFileSystem`, `NKLogger`, `NKMemory`, `NKPlatform`, `NKThreading` |
| **`NKTime`** | `NKContainers`, `NKCore`, `NKLogger`, `NKMemory`, `NKPlatform`, `NKThreading` |
| **`NKGlad`** | *(Module feuille / Loader indépendant)* |
| **`NKThreading`** | `NKContainers`, `NKCore`, `NKMemory`, `NKPlatform` |
| **`NKUI`** | `NKContainers`, `NKCore`, `NKEvent`, `NKFileSystem`, `NKFont`, `NKImage`, `NKLogger`, `NKMath`, `NKMemory`, `NKPlatform`, `NKThreading` |
```
---

## 4. Graphe Structural des Dépendances


```

```
                                                        [ NKCanvas ]
                                                              │
      ┌─────────────────┬─────────────────┬───────────────────┼───────────────────┬─────────────────┬─────────────────┬─────────────────┐
      │                 │                 │                   │                   │                 │                 │                 │
┌─────┴──────┐    ┌─────┴──────┐    ┌─────┴──────┐      ┌─────┴──────┐      ┌─────┴──────┐    ┌─────┴──────┐    ┌─────┴──────┐    ┌─────┴──────┐
│  NKWindow  │    │   NKFont   │    │  NKImage   │      │  NKStream  │      │   NKTime   │    │   NKGlad   │    │ NKThreading│    │    NKUI    │ * (Si option)
└─────┬──────┘    └─────┬──────┘    └─────┬──────┘      └─────┬──────┘      └─────┬──────┘    └────────────┘    └─────┬──────┘    └─────┬──────┘
      ├─ NKEvent        ├─ NKContainers   ├─ NKContainers     ├─ NKContainers     ├─ NKContainers                     ├─ NKContainers   ├─ NKWindow
      ├─ NKFileSystem   ├─ NKCore         ├─ NKCore           ├─ NKCore           ├─ NKCore                           ├─ NKCore         ├─ NKFont
      ├─ NKLogger       ├─ NKLogger       ├─ NKFileSystem     ├─ NKFileSystem     ├─ NKLogger                         ├─ NKMemory       ├─ NKImage
      ├─ NKMath         ├─ NKMath         ├─ NKLogger         ├─ NKLogger         ├─ NKMemory                         └─ NKPlatform     ├─ NKEvent
      ├─ NKMemory       ├─ NKMemory       ├─ NKMath           ├─ NKMemory         ├─ NKPlatform                                         ├─ NKFileSystem
      ├─ NKPlatform     ├─ NKPlatform     ├─ NKMemory         ├─ NKPlatform       └─ NKThreading                                        ├─ NKLogger
      ├─ NKThreading    └─ NKThreading    ├─ NKPlatform       └─ NKThreading                                                            ├─ NKMath
      └─ NKTime                           ├─ NKStream                                                                                   ├─ NKMemory
                                          └─ NKThreading                                                                                ├─ NKPlatform
                                                                                                                                        └─ NKThreading
```


---

## 5. Ordre de Build 

Pour que `NKCanvas` puisse être lié, l'ordre exact d'assemblage des 16 modules internes du workspace est le suivant :

1. `NKPlatform`
2. `NKGlad`
3. `NKCore`
4. `NKMemory`
5. `NKContainers`
6. `NKThreading`
7. `NKMath`
8. `NKLogger`
9. `NKFileSystem`
10. `NKTime`
11. `NKFont`
12. `NKStream`
13. `NKEvent`
14. `NKImage`
15. `NKWindow`
16. `NKUI`

---

## 6. Synthèse Comparative

| Critère | Déclaration `.jenga` | Résolution Complète (Build Log) |
| :--- | :--- | :--- |
| **Dépendances explicites** | 7 modules (+1 si NKUI activé) | 16 modules (transitivité ) |

